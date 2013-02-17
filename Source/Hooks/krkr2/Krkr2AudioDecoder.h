#ifndef _KRKR2AUDIODECODER_H_de0aa14c_c404_4b11_8c95_d87adf11bb30_
#define _KRKR2AUDIODECODER_H_de0aa14c_c404_4b11_8c95_d87adf11bb30_

#include "krkr2.h"
#include "AudioDecoder.h"

class AudioModule : public ITSSModule
{
protected:
    ULONG                m_RefCount;
    ITSSModule          *m_ModuleVorbis;
    ITSSStorageProvider *m_StorageProvider;

public:
    AudioModule(ITSSStorageProvider *StorageProvider = NULL);
    ~AudioModule();

public:
    // IUnknown
    HRESULT STDCALL QueryInterface(REFIID IID, PVOID *Object);
    ULONG   STDCALL AddRef();
    ULONG   STDCALL Release();

    // ITSSModule
    HRESULT
    STDCALL
    GetModuleCopyright(
        IN PWSTR Buffer,
        IN ULONG BufferSize
    );

    HRESULT
    STDCALL
    GetModuleDescription(
        IN PWSTR Buffer,
        IN ULONG BufferSize
    );

    HRESULT
    STDCALL
    GetSupportExts(
        IN ULONG Index,
        IN PWSTR MediaShortName,
        IN PWSTR Buffer,
        IN ULONG BufferSize
    );

    HRESULT
    STDCALL
    GetMediaInfo(
        IN  PWSTR              Url,
        OUT ITSSMediaBaseInfo**Info
    );

    HRESULT
    STDCALL
    GetMediaSupport(
        IN PWSTR Url
    );

    HRESULT
    STDCALL
    GetMediaInstance(
        IN  PWSTR     Url,
        OUT IUnknown**Instance
    );
};

class AACWaveDecoder : public ITSSWaveDecoder
{
protected:
    ULONG m_RefCount;
    ULONG m_BytesPerSample;
    PBYTE m_VoiceBuffer;
    ULONG m_VoiceSize;
    ULONG m_VoicePos;

#if SUPPORT_AAC_DECODE
    AudioDecoder m_ad;
#endif

public:
    AACWaveDecoder();
    ~AACWaveDecoder();

    // IUnkown
    HRESULT STDCALL QueryInterface(REFIID iid, PVOID *Object);
    ULONG   STDCALL AddRef();
    ULONG   STDCALL Release();

    // ITSSWaveDecoder
    HRESULT
    STDCALL
    GetFormat(
        TSSWaveFormat *Format
    );

    HRESULT
    STDCALL
    Render(
        PVOID   Buffer, 
        ULONG   SamplesToRender, 
        PULONG  SamplesRendered, 
        PULONG  Status
    );

    HRESULT
    STDCALL
    SetPosition(
        ULONG64 SamplePos
    );

    // others
    HRESULT SetStream(IStream *Stream, PWSTR Url);
};

#endif // _KRKR2AUDIODECODER_H_de0aa14c_c404_4b11_8c95_d87adf11bb30_
