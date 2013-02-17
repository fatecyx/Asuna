#ifndef _AACWAVEDECODER_H_
#define _AACWAVEDECODER_H_

#include <Windows.h>
#include "tvpsnd.h"
#include "my_headers.h"

#if defined(SUPPORT_AAC_DECODE)
#include "AudioPlayback.h"
#endif

//---------------------------------------------------------------------------
class CAACModule : public ITSSModule // module interface
{
protected:
    ULong                m_RefCount;
    ITSSModule          *m_pModuleVorbis;
    ITSSStorageProvider *m_pStorageProvider;

public:
    CAACModule(ITSSStorageProvider *pStorageProvider = NULL);
    ~CAACModule();

public:
    // IUnknown
    HRESULT STDCALL QueryInterface(REFIID iid, LPVoid *ppvObject);
    ULong   STDCALL AddRef();
    ULong   STDCALL Release();

    // ITSSModule
    HRESULT STDCALL GetModuleCopyright(LPWSTR buffer, ULong buflen);
    HRESULT STDCALL GetModuleDescription(LPWSTR buffer, ULong buflen);
    HRESULT STDCALL GetSupportExts(ULong index, LPWSTR mediashortname, LPWSTR buf, ULong buflen);
    HRESULT STDCALL GetMediaInfo(LPWSTR url, ITSSMediaBaseInfo **info);
    HRESULT STDCALL GetMediaSupport(LPWSTR url);
    HRESULT STDCALL GetMediaInstance(LPWSTR url, IUnknown **instance);
};

class CAACWaveDecoder : public ITSSWaveDecoder
{
protected:
    ULong  m_RefCount, m_BytesPerSample; // reference count
    PByte  m_pbVoice;
    UInt32 m_VoiceSize, m_VoicePos;
//    CMem   m;
#if defined(SUPPORT_AAC_DECODE)
    CAudioPlayback m_ap;
#endif

public:
    CAACWaveDecoder();
    ~CAACWaveDecoder();

    // IUnkown
    HRESULT STDCALL QueryInterface(REFIID iid, LPVoid *ppvObject);
    ULong   STDCALL AddRef();
    ULong   STDCALL Release();

    // ITSSWaveDecoder
    HRESULT STDCALL GetFormat(TSSWaveFormat *format);
    HRESULT STDCALL Render(LPVoid buf, ULong bufsamplelen, PULong rendered, PULong status);
    HRESULT STDCALL SetPosition(UInt64 samplepos);

    // others
    HRESULT SetStream(IStream *stream, LPWSTR url);
};

#endif /* _AACWAVEDECODER_H_ */