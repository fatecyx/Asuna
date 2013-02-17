#include "AACWaveDecoder.h"
#include "krkr2/tjs2/tjsCommHead.h"
#include "my_mem.h"
#include "my_crt.h"
#include "my_audio.h"

#if defined(SUPPORT_AAC_DECODE)
#include "AudioPlayback.cpp"
#endif

// AACModule implementation

CAACModule::CAACModule(ITSSStorageProvider *pStorageProvider /* = NULL */)
{
	// AACModule constructor
    m_RefCount = 1;
    m_pModuleVorbis = NULL;
    m_pStorageProvider = pStorageProvider;
}

CAACModule::~CAACModule()
{
    if (m_pModuleVorbis != NULL)
    {
        m_pModuleVorbis->Release();
        m_pModuleVorbis = NULL;
    }
}

HRESULT STDCALL CAACModule::QueryInterface(REFIID iid, void ** ppvObject)
{
	// IUnknown::QueryInterface

    if(ppvObject == NULL)
        return E_INVALIDARG;

    *ppvObject = NULL;

    if (iid == IID_IUnknown)
        *ppvObject = (IUnknown *)this;
    else if (iid == IID_ITSSModule)
        *ppvObject = (ITSSModule *)this;
    else
        return E_NOINTERFACE;

    AddRef();

    return S_OK;
}

ULong STDCALL CAACModule::AddRef()
{
    return _InterlockedIncrement((PLong)&m_RefCount);
}

ULong STDCALL CAACModule::Release()
{
    ULong Ref;

    Ref = _InterlockedDecrement((PLong)&m_RefCount);
    if (Ref == 0)
        delete this;

    return Ref;
}

HRESULT STDCALL CAACModule::GetModuleCopyright(LPWSTR buffer, ULong buflen)
{
	// return module copyright information
    static WChar szCopyright[] = L"AAC & UCA Plug-in for TVP Sound System (C) 2010 by Amano";
    memcpy(buffer, szCopyright, min(buflen, sizeof(szCopyright)));
	return S_OK;
}

HRESULT STDCALL CAACModule::GetModuleDescription(LPWSTR buffer, ULong buflen)
{
	// return module description
    static WChar szDescription[] = L"AAC (*.m4a) and UCA (*.uca) decoder";
    memcpy(buffer, szDescription, min(buflen, sizeof(szDescription)));
	return S_OK;
}

HRESULT STDCALL CAACModule::GetSupportExts(ULong index, LPWSTR mediashortname, LPWSTR buf, ULong buflen)
{
	// return supported file extensios

    ULong Length;
    static WChar *szShortName[] =
    {
        L"Ogg Stream Format",
#if defined(SUPPORT_AAC_DECODE)
        L"AAC Stream Format",
#endif
        L"Ultra Compact Audio",
    };
    static WChar *szExts[] =
    {
        L".ogg",
#if defined(SUPPORT_AAC_DECODE)
        L".m4a",
#endif
        L".uca",
    };

    if (index >= countof(szExts))
        return S_FALSE;

    memcpy(mediashortname, szShortName[index], (StrLengthW(szShortName[index]) + 1) * 2);

    Length = StrLengthW(szExts[index]) + 1;
    Length *= 2;
    memcpy(buf, szExts[index], min(buflen, Length));

	return S_OK;
}

HRESULT STDCALL CAACModule::GetMediaInfo(LPWSTR url, ITSSMediaBaseInfo ** info )
{
	// return media information interface
	return E_NOTIMPL; // not implemented
}

HRESULT STDCALL CAACModule::GetMediaSupport(LPWSTR url )
{
	// return media support interface
	return E_NOTIMPL; // not implemented
}

HRESULT STDCALL CAACModule::GetMediaInstance(LPWSTR url, IUnknown **pInstance)
{
	HRESULT  hResult;
    ULong    BytesRead;
    IStream *AudioStream;
    LARGE_INTEGER AudioHeader, StreamPos;

    if (pInstance == NULL)
        return E_INVALIDARG;

    hResult = m_pStorageProvider->GetStreamForRead(url, (IUnknown**)&AudioStream);
    if(FAILED(hResult))
        return hResult;

    hResult = AudioStream->Read(&AudioHeader, sizeof(AudioHeader), &BytesRead);
    if (FAILED(hResult))
        return hResult;

    StreamPos.QuadPart = 0;
    AudioStream->Seek(StreamPos, STREAM_SEEK_SET, NULL);

    ITSSWaveDecoder *decoder = NULL;

    if (AudioHeader.LowPart == TAG4('OggS'))
    {
        do
        {
            if (m_pModuleVorbis == NULL)
            {
                typedef HRESULT (STDCALL *FGetModuleInstance)(ITSSModule **out, ITSSStorageProvider *provider, IStream * config, HWND mainwin);

                HMODULE hModule;
                FGetModuleInstance pfGetModuleInstance;

                hModule = GetModuleHandleW(L"wuvorbis.dll");
                if (hModule == NULL)
                    break;

                *(LPVoid *)&pfGetModuleInstance = GetProcAddress(hModule, "GetModuleInstance");
                if (pfGetModuleInstance == NULL)
                {
                    hResult = E_FAIL;
                    break;
                }

                hResult = pfGetModuleInstance(&m_pModuleVorbis, m_pStorageProvider, NULL, NULL);
                if (FAILED(hResult) || m_pModuleVorbis == NULL)
                    break;
            }

            hResult = m_pModuleVorbis->GetMediaInstance(url, (IUnknown **)&decoder);

        } while (0);
    }
    else
    {
        CAACWaveDecoder *AACDecoder = new CAACWaveDecoder;

        if (AACDecoder != NULL)
        {
            hResult = AACDecoder->SetStream(AudioStream, url);
            if (SUCCEEDED(hResult))
                decoder = AACDecoder;
        }
    }

    AudioStream->Release();

    if (decoder == NULL)
        return hResult;

	if(FAILED(hResult))
        delete decoder;
    else
        *pInstance = (IUnknown*)decoder;

    return hResult;
}

//---------------------------------------------------------------------------
// CAACWaveDecoder implementation
//---------------------------------------------------------------------------
CAACWaveDecoder::CAACWaveDecoder()
{
    m_RefCount  = 1;
    m_pbVoice   = NULL;
    m_VoicePos  = 0;
    m_VoiceSize = 0;
}

CAACWaveDecoder::~CAACWaveDecoder()
{
    if (m_pbVoice)
    {
        UCAFree(m_pbVoice);
        m_pbVoice = NULL;
    }
}

HRESULT STDCALL CAACWaveDecoder::QueryInterface(REFIID iid, void ** ppvObject)
{
    // IUnknown::QueryInterface

    if(ppvObject == NULL)
        return E_INVALIDARG;

    *ppvObject = NULL;

    if (iid == IID_IUnknown)
        *ppvObject = (IUnknown *)this;
    else if (iid == IID_ITSSWaveDecoder)
        *ppvObject = (ITSSWaveDecoder *)this;
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

ULong STDCALL CAACWaveDecoder::AddRef()
{
    return _InterlockedIncrement((PLong)&m_RefCount);
}

ULong STDCALL CAACWaveDecoder::Release()
{
    ULong Ref = _InterlockedDecrement((PLong)&m_RefCount);

    if (Ref == 0)
        delete this;

    return Ref;
}

HRESULT STDCALL CAACWaveDecoder::GetFormat(TSSWaveFormat *WaveFormat)
{
    if (m_pbVoice)
    {
        SWaveHeader *h;
        h = (SWaveHeader *)m_pbVoice;

        WaveFormat->dwBitsPerSample  = h->wBitsPerSample;
        WaveFormat->dwChannels       = h->wChannels;
        WaveFormat->dwSamplesPerSec  = h->dwSamplesPerSec;
        WaveFormat->dwSeekable       = 2;
        WaveFormat->dwTotalTime      = h->dwDataSize / h->dwAvgBytesPerSec;
        WaveFormat->ui64TotalSamples = WaveFormat->dwTotalTime * h->dwSamplesPerSec;
        WaveFormat->ui64TotalSamples = (UInt64)h->dwDataSize * h->dwSamplesPerSec / h->dwAvgBytesPerSec;
        WaveFormat->dwReserved1      = 0;
        WaveFormat->dwReserved2      = 0;

        return S_OK;
    }

#if defined(SUPPORT_AAC_DECODE)

    const BASS_CHANNELINFO *pChannelInfo;

    pChannelInfo = m_ap.GetChannelInfo();
    if (pChannelInfo == NULL)
        return E_FAIL;

    m_BytesPerSample = (pChannelInfo->flags & BASS_SAMPLE_8BITS) ? 1 : 2;
    WaveFormat->dwBitsPerSample = m_BytesPerSample * 8;
    m_BytesPerSample *= pChannelInfo->chans;

    WaveFormat->dwSamplesPerSec = pChannelInfo->freq;
    WaveFormat->dwChannels = pChannelInfo->chans;
    WaveFormat->dwSeekable = 2;

    WaveFormat->dwTotalTime = (ULong)m_ap.GetTimeTotal(); // total time in sec.
    WaveFormat->ui64TotalSamples = WaveFormat->dwTotalTime * WaveFormat->dwSamplesPerSec;

    WaveFormat->dwReserved1 = 0;
    WaveFormat->dwReserved2 = 0;

    return S_OK;

#else

    return E_FAIL;

#endif

}

HRESULT CAACWaveDecoder::SetStream(IStream *stream, LPWSTR url)
{
    CMem   mem;
    LPVoid lpBuffer;
    HRESULT Result;
    LARGE_INTEGER liStreamPos;
    Large_Integer liBufferSize;

    stream->AddRef();

    lpBuffer = NULL;
    do
    {
        liStreamPos.QuadPart = 0;
        Result = stream->Seek(liStreamPos, STREAM_SEEK_END, (PULARGE_INTEGER)&liBufferSize);
        if (FAILED(Result))
            break;

        lpBuffer = mem.Alloc(liBufferSize.LowPart);
        if (lpBuffer == NULL)
        {
            Result = E_OUTOFMEMORY;
            break;
        }

        stream->Seek(liStreamPos, STREAM_SEEK_SET, NULL);
        Result = stream->Read(lpBuffer, liBufferSize.LowPart, (PULong)&liBufferSize.LowPart);
        if (FAILED(Result))
            break;

        if (((*(PUInt32)lpBuffer) & 0xFFFFFF) == TAG3('UCA'))
        {
            m_VoiceSize = 0;
            Result = UCADecode2(lpBuffer, liBufferSize.LowPart, (LPVoid *)&m_pbVoice, (PInt32)&m_VoiceSize, 48000);
            if (Result < 0)
            {
                Result = E_FAIL;
                break;
            }

            m_VoicePos = sizeof(SWaveHeader);
        }
#if defined(SUPPORT_AAC_DECODE)
        else
        {
            liBufferSize.HighPart = 0;
            Result = m_ap.Open(lpBuffer, True, &liBufferSize, True) ? S_OK : E_FAIL;
        }
#endif

    } while (0);

    stream->Release();
    if (lpBuffer)
        mem.Free(lpBuffer);

    return Result;
}

HRESULT
STDCALL
CAACWaveDecoder::
Render(
    LPVoid lpBuffer, 
    ULong  SamplesToRender, 
    PULong pSamplesRendered, 
    PULong pStatus
)
{
    // render output PCM
    UInt32 SamplesDecoded;

    if (m_pbVoice)
    {
        UInt32 SizeToCopy;
        SWaveHeader *h;

        h = (SWaveHeader *)m_pbVoice;

        if (m_VoicePos < m_VoiceSize)
        {
            SizeToCopy = (m_VoiceSize - m_VoicePos);
            if (SamplesToRender < SizeToCopy / h->wBlockAlign)
            {
                SizeToCopy = SamplesToRender * h->wBlockAlign;
            }

            memcpy(lpBuffer, m_pbVoice + m_VoicePos, SizeToCopy);
            m_VoicePos += SizeToCopy;
            SizeToCopy /= h->wBlockAlign;
        }
        else
            SizeToCopy = 0;

        if (pStatus)
            *pStatus = m_VoicePos >= m_VoiceSize ? 0 : 1;

        if (pSamplesRendered)
            *pSamplesRendered = SizeToCopy;

        return S_OK;
    }

#if defined(SUPPORT_AAC_DECODE)

    if (m_ap.IsStreamValid() == False)
        return E_FAIL;

    SamplesDecoded = m_ap.GetData(lpBuffer, SamplesToRender * m_BytesPerSample);    // remaining PCM (in bytes)

    if (SamplesDecoded != BASS_ERROR_UNKNOWN)
        SamplesDecoded /= m_BytesPerSample;
    else
        SamplesDecoded = 0;

    if (pStatus)
        *pStatus = SamplesDecoded < SamplesToRender ? 0 : 1; // *status will be 0 if the decoding is ended

    if (pSamplesRendered)    // return renderd PCM samples
        *pSamplesRendered = SamplesDecoded;

    return S_OK;

#else

    return E_FAIL;

#endif

}

HRESULT STDCALL CAACWaveDecoder::SetPosition(UInt64 samplepos)
{
    if (m_pbVoice)
    {
        SWaveHeader *h;

        h = (SWaveHeader *)m_pbVoice;
        m_VoicePos = (UInt32)samplepos * h->wBlockAlign + sizeof(*h);

        return S_OK;
    }

#if defined(SUPPORT_AAC_DECODE)

    Large_Integer liSamplePos;

    liSamplePos.QuadPart = samplepos * m_BytesPerSample;

    return m_ap.Seek(&liSamplePos) ? S_OK : E_FAIL;

#else

    return E_FAIL;

#endif

}