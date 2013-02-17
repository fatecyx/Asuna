#ifndef _AACDECODER_H_5961e55d_fe19_4e8d_bd98_79778a675b9a
#define _AACDECODER_H_5961e55d_fe19_4e8d_bd98_79778a675b9a

#pragma comment(lib, "libfaad2.lib")

#include "pragma_once.h"
#include "my_headers.h"
#include "E:\\Desktop\\Source\\sources\\faad2-2.7\\include\\neaacdec.h"
#include "mp4ff/mp4ffint.h"

#pragma pack(1)

typedef struct
{
    ULONG           AACTrack;
    ULONG           Profile;
    ULONG           Rate;
    ULONG           BitsPerSample;
    ULONG           Channels;
    LARGE_INTEGER   Samples;
    LARGE_INTEGER   TrueStart;
    LARGE_INTEGER   TrueEnd;
} AUDIO_INFO;

#pragma pack()

enum EAACFormatProfile
{
    PROFILE_LC, 
    PROFILE_HE, 
    PROFILE_HEV2, 
};

class CAACDecoder
{
protected:
    CMem                m_mem;
    PVOID               m_pvBuffer;
    ULONG               m_BufferSize;
    ULONG               m_StreamSize;
    LARGE_INTEGER       m_Offset;
    mp4ff_t             m_Mp4File;
    mp4ff_callback_t    m_Mp4Callback;
    NeAACDecHandle      m_hDecoder;
    AUDIO_INFO          m_Info;

public:
    CAACDecoder();
    ~CAACDecoder();

    BOOL    ReleaseAll();

    BOOL    Open(PVOID pvBuffer, ULONG BufferSize);
    ULONG64 SeekBySample(ULONG64 Sample);
    ULONG64 SeekByPos(ULONG64 Pos);
    ULONG   Decode(PVOID pvBuffer, ULONG BufferSize, ULONG Samples);
    BOOL    Close();

protected:
    PVOID AllocBuffer(ULONG Size);
    PBYTE GetDecoderConfig(ULONG Track, PULONG pConfiSize);
    ULONG GetAACTrack();
    BOOL  ParseItunsmpb(AUDIO_INFO *pAudioInfo);

    static ULONG ReadCallback(CAACDecoder *pThis, PVOID pvBuffer, ULONG Length);
    static ULONG SeekCallback(CAACDecoder *pThis, ULONG64 Position);
};

#endif // _AACDECODER_H_5961e55d_fe19_4e8d_bd98_79778a675b9a
