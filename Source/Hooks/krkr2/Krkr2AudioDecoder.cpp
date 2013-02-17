#include "Krkr2AudioDecoder.h"

const IID IID_ITSSModule        = { 0xA938D1A5, 0x2980, 0x498B, { 0xB0, 0x51, 0x99, 0x93, 0x1D, 0x41, 0x89, 0x5D } };
const IID IID_ITSSWaveDecoder   = { 0x313864E2, 0x910E, 0x496F, { 0x8A, 0x6D, 0x43, 0x46, 0x5C, 0x10, 0x5B, 0x58 } };

/************************************************************************
  AudioModule implement
************************************************************************/

AudioModule::AudioModule(ITSSStorageProvider *StorageProvider /* = NULL */)
{
	// AACModule constructor
    m_RefCount = 1;
    m_ModuleVorbis = NULL;
    m_StorageProvider = StorageProvider;
}

AudioModule::~AudioModule()
{
    SafeReleaseT(m_ModuleVorbis);
}

HRESULT STDCALL AudioModule::QueryInterface(REFIID iid, void ** ppvObject)
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

ULONG STDCALL AudioModule::AddRef()
{
    return _InterlockedIncrement((PLONG)&m_RefCount);
}

ULONG STDCALL AudioModule::Release()
{
    ULONG Ref;

    Ref = _InterlockedDecrement((PLONG)&m_RefCount);
    if (Ref == 0)
        delete this;

    return Ref;
}

HRESULT STDCALL AudioModule::GetModuleCopyright(PWSTR buffer, ULONG buflen)
{
	// return module copyright information
    static WChar szCopyright[] = L"AAC & UCA Plug-in for TVP Sound System (C) 2010 by Amano";
    CopyMemory(buffer, szCopyright, min(buflen, sizeof(szCopyright)));
	return S_OK;
}

HRESULT STDCALL AudioModule::GetModuleDescription(PWSTR buffer, ULONG buflen)
{
	// return module description
    static WChar szDescription[] = L"AAC (*.m4a) and UCA (*.uca) decoder";
    CopyMemory(buffer, szDescription, min(buflen, sizeof(szDescription)));
	return S_OK;
}

HRESULT STDCALL AudioModule::GetSupportExts(ULONG index, PWSTR mediashortname, PWSTR buf, ULONG buflen)
{
	// return supported file extensios

    ULONG Length;
    static WChar *szShortName[] =
    {
        L"Ogg Stream Format",
#if SUPPORT_AAC_DECODE
        L"AAC Stream Format",
#endif
        L"Ultra Compact Audio",
    };
    static WChar *szExts[] =
    {
        L".ogg",
#if SUPPORT_AAC_DECODE
        L".m4a",
#endif
        L".uca",
    };

    if (index >= countof(szExts))
        return S_FALSE;

    CopyMemory(mediashortname, szShortName[index], (StrLengthW(szShortName[index]) + 1) * 2);

    Length = StrLengthW(szExts[index]) + 1;
    Length *= 2;
    CopyMemory(buf, szExts[index], min(buflen, Length));

	return S_OK;
}

HRESULT STDCALL AudioModule::GetMediaInfo(PWSTR Url, ITSSMediaBaseInfo **Info)
{
	// return media information interface
	return E_NOTIMPL; // not implemented
}

HRESULT STDCALL AudioModule::GetMediaSupport(PWSTR url )
{
	// return media support interface
	return E_NOTIMPL; // not implemented
}

HRESULT STDCALL AudioModule::GetMediaInstance(PWSTR Url, IUnknown **Instance)
{
	HRESULT         Result;
    ULONG           BytesRead;
    IStream*        AudioStream;
    LARGE_INTEGER   AudioHeader, StreamPos;

    if (Instance == NULL)
        return E_INVALIDARG;

    Result = m_StorageProvider->GetStreamForRead(Url, (IUnknown**)&AudioStream);
    if(FAILED(Result))
        return Result;

    Result = AudioStream->Read(&AudioHeader, sizeof(AudioHeader), &BytesRead);
    if (FAILED(Result))
        return Result;

    StreamPos.QuadPart = 0;
    AudioStream->Seek(StreamPos, STREAM_SEEK_SET, NULL);

    ITSSWaveDecoder *Decoder = NULL;

    if (AudioHeader.LowPart == TAG4('OggS'))
    {
        LOOP_ONCE
        {
            if (m_ModuleVorbis == NULL)
            {
                HRESULT (STDCALL *GetModuleInstance)(ITSSModule **out, ITSSStorageProvider *provider, IStream * config, HWND mainwin);

                PLDR_MODULE Module;
                UNICODE_STRING WuVorbis;

                RTL_CONST_STRING(WuVorbis, L"wuvorbis.dll");
                Module = Nt_FindLdrModuleByName(&WuVorbis);
                if (Module == NULL)
                    break;

                *(PVOID *)&GetModuleInstance = Nt_GetProcAddress(Module->DllBase, "GetModuleInstance");
                if (GetModuleInstance == NULL)
                {
                    Result = E_FAIL;
                    break;
                }

                Result = GetModuleInstance(&m_ModuleVorbis, m_StorageProvider, NULL, NULL);
                if (FAILED(Result) || m_ModuleVorbis == NULL)
                    break;
            }

            Result = m_ModuleVorbis->GetMediaInstance(Url, (IUnknown **)&Decoder);
        }
    }
    else
    {
        AACWaveDecoder *AACDecoder = new AACWaveDecoder;

        if (AACDecoder != NULL)
        {
            Result = AACDecoder->SetStream(AudioStream, Url);
            if (SUCCEEDED(Result))
                Decoder = AACDecoder;
        }
    }

    AudioStream->Release();

    if (Decoder == NULL)
        return Result;

	if(FAILED(Result))
        delete Decoder;
    else
        *Instance = (LPUNKNOWN)Decoder;

    return Result;
}


/************************************************************************
  AACWaveDecoder implement
************************************************************************/

AACWaveDecoder::AACWaveDecoder()
{
    m_RefCount      = 1;
    m_VoiceBuffer   = NULL;
    m_VoicePos      = 0;
    m_VoiceSize     = 0;
}

AACWaveDecoder::~AACWaveDecoder()
{
    if (m_VoiceBuffer != NULL)
    {
        UCAFree(m_VoiceBuffer);
    }
}

HRESULT STDCALL AACWaveDecoder::QueryInterface(REFIID iid, PVOID *Object)
{
    // IUnknown::QueryInterface

    if(Object == NULL)
        return E_INVALIDARG;

    *Object = NULL;

    if (iid == IID_IUnknown)
    {
        *Object = (IUnknown *)this;
    }
    else if (iid == IID_ITSSWaveDecoder)
    {
        *Object = (ITSSWaveDecoder *)this;
    }
    else
    {
        return E_NOINTERFACE;
    }

    AddRef();

    return S_OK;
}

ULONG STDCALL AACWaveDecoder::AddRef()
{
    return _InterlockedIncrement((PLONG)&m_RefCount);
}

ULONG STDCALL AACWaveDecoder::Release()
{
    ULONG RefCount = _InterlockedDecrement((PLONG)&m_RefCount);

    if (RefCount == 0)
        delete this;

    return RefCount;
}

HRESULT STDCALL AACWaveDecoder::GetFormat(TSSWaveFormat *WaveFormat)
{
    if (m_VoiceBuffer != NULL)
    {
        PAUDIO_WAVE_HEADER h = (PAUDIO_WAVE_HEADER)m_VoiceBuffer;

        WaveFormat->BitsPerSample   = h->BitsPerSample;
        WaveFormat->Channels        = h->Channels;
        WaveFormat->SamplesPerSec   = h->SamplesPerSec;
        WaveFormat->Seekable        = 2;
        WaveFormat->TotalTime       = h->DataSize / h->AvgBytesPerSec;
        WaveFormat->TotalSamples    = WaveFormat->TotalTime * h->SamplesPerSec;
        WaveFormat->TotalSamples    = (ULONG64)h->DataSize * h->SamplesPerSec / h->AvgBytesPerSec;
        WaveFormat->Reserved1       = 0;
        WaveFormat->Reserved2       = 0;

        return S_OK;
    }

#if SUPPORT_AAC_DECODE

    BASS_CHANNELINFO *ChannelInfo;

    ChannelInfo = m_ad.GetChannelInfo();
    if (ChannelInfo == NULL)
        return E_FAIL;

    m_BytesPerSample            = FLAG_ON(ChannelInfo->flags, BASS_SAMPLE_8BITS) ? 1 : 2;
    WaveFormat->BitsPerSample   = m_BytesPerSample * 8;
    m_BytesPerSample           *= ChannelInfo->chans;
    WaveFormat->SamplesPerSec   = ChannelInfo->freq;
    WaveFormat->Channels        = ChannelInfo->chans;
    WaveFormat->Seekable        = 2;
    WaveFormat->TotalTime       = (ULONG)m_ad.GetTimeTotal(); // total time in sec.
    WaveFormat->TotalSamples    = WaveFormat->TotalTime * WaveFormat->SamplesPerSec;
    WaveFormat->Reserved1       = 0;
    WaveFormat->Reserved2       = 0;

    return S_OK;

#else

    return E_FAIL;

#endif

}

HRESULT AACWaveDecoder::SetStream(IStream *Stream, PWSTR Url)
{
    MemoryAllocator mem;
    PVOID           Buffer;
    HRESULT         Result;
    LARGE_INTEGER   StreamPos;
    Large_Integer   BufferSize;

    Stream->AddRef();

    Buffer = NULL;
    LOOP_ONCE
    {
        StreamPos.QuadPart = 0;
        Result = Stream->Seek(StreamPos, STREAM_SEEK_END, (PULARGE_INTEGER)&BufferSize);
        if (FAILED(Result))
            break;

        Buffer = mem.Alloc(BufferSize.LowPart);
        if (Buffer == NULL)
        {
            Result = E_OUTOFMEMORY;
            break;
        }

        Stream->Seek(StreamPos, STREAM_SEEK_SET, NULL);
        Result = Stream->Read(Buffer, BufferSize.LowPart, (PULONG)&BufferSize.LowPart);
        if (FAILED(Result))
            break;

        if (((*(PULONG)Buffer) & 0xFFFFFF) == TAG3('UCA'))
        {
            m_VoiceSize = 0;
            Result = UCADecode2(Buffer, BufferSize.LowPart, (PVOID *)&m_VoiceBuffer, (PINT32)&m_VoiceSize, 48000);
            if (Result < 0)
            {
                Result = E_FAIL;
                break;
            }

            m_VoicePos = sizeof(AUDIO_WAVE_HEADER);
        }
#if SUPPORT_AAC_DECODE
        else
        {
            BufferSize.HighPart = 0;
            Result = m_ad.Open(Buffer, True, &BufferSize, True) ? S_OK : E_FAIL;
        }
#endif

    }

    Stream->Release();
    if (Buffer)
        mem.Free(Buffer);

    return Result;
}

HRESULT
STDCALL
AACWaveDecoder::
Render(
    PVOID   Buffer, 
    ULONG   SamplesToRender, 
    PULONG  SamplesRendered, 
    PULONG  Status
)
{
    // render output PCM
    ULONG SamplesDecoded;

    if (m_VoiceBuffer != NULL)
    {
        ULONG               SizeToCopy;
        PAUDIO_WAVE_HEADER  h;

        h = (PAUDIO_WAVE_HEADER)m_VoiceBuffer;

        if (m_VoicePos < m_VoiceSize)
        {
            SizeToCopy = (m_VoiceSize - m_VoicePos);
            if (SamplesToRender < SizeToCopy / h->BlockAlign)
            {
                SizeToCopy = SamplesToRender * h->BlockAlign;
            }

            CopyMemory(Buffer, m_VoiceBuffer + m_VoicePos, SizeToCopy);
            m_VoicePos += SizeToCopy;
            SizeToCopy /= h->BlockAlign;
        }
        else
        {
            SizeToCopy = 0;
        }

        if (Status != NULL)
            *Status = m_VoicePos >= m_VoiceSize ? 0 : 1;

        if (SamplesRendered != NULL)
            *SamplesRendered = SizeToCopy;

        return S_OK;
    }

#if SUPPORT_AAC_DECODE

    if (!m_ad.IsStreamValid())
        return E_FAIL;

    SamplesDecoded = m_ad.GetData(Buffer, SamplesToRender * m_BytesPerSample);    // remaining PCM (in bytes)

    if (SamplesDecoded != BASS_ERROR_UNKNOWN)
    {
        SamplesDecoded /= m_BytesPerSample;
    }
    else
    {
        SamplesDecoded = 0;
    }

    if (Status != NULL)
        *Status = SamplesDecoded < SamplesToRender ? 0 : 1; // *status will be 0 if the decoding is ended

    if (SamplesRendered != NULL)    // return renderd PCM samples
        *SamplesRendered = SamplesDecoded;

    return S_OK;

#else

    return E_FAIL;

#endif

}

HRESULT STDCALL AACWaveDecoder::SetPosition(ULONG64 SamplePos)
{
    if (m_VoiceBuffer != NULL)
    {
        PAUDIO_WAVE_HEADER h= (PAUDIO_WAVE_HEADER)m_VoiceBuffer;
        m_VoicePos = (ULONG)SamplePos * h->BlockAlign + sizeof(*h);

        return S_OK;
    }

#if SUPPORT_AAC_DECODE

    Large_Integer _SamplePos;

    _SamplePos.QuadPart = SamplePos * m_BytesPerSample;

    return m_ad.Seek(&_SamplePos) ? S_OK : E_FAIL;

#else

    return E_FAIL;

#endif

}
