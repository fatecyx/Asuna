#ifndef _MY_AUDIO_H_
#define _MY_AUDIO_H_

#pragma comment(lib, "ucadec.lib")

#include <mmsystem.h>
#include "my_types.h"

typedef struct
{
    UInt32 RIFF;
    UInt32 dwSize;
    UInt32 WAVE;
    UInt32 fmt;
    UInt32 dwFormatLength;
    UInt16 wFormatTag;
    UInt16 wChannels;
    UInt32 dwSamplesPerSec;
    UInt32 dwAvgBytesPerSec;
    UInt16 wBlockAlign;
    UInt16 wBitsPerSample;
    UInt32 data;
    UInt32 dwDataSize;
} SRIFFHeader;

typedef SRIFFHeader SWaveHeader;

#if CPP_DEFINED

inline
Bool
FASTCALL
InitWaveHeader(
    SWaveHeader *pHeader,
    const WAVEFORMATEX *pWaveFormat,
    UInt32 dwWaveLength
)
{
    if (pHeader == NULL || pWaveFormat == NULL)
        return False;

    pHeader->RIFF = TAG4('RIFF');
    pHeader->fmt  = TAG4('fmt ');
    pHeader->WAVE = TAG4('WAVE');
    pHeader->data = TAG4('data');
    pHeader->dwFormatLength = 16;

    pHeader->wFormatTag = pWaveFormat->wFormatTag;
    pHeader->wChannels  = pWaveFormat->nChannels;
    pHeader->dwSamplesPerSec = pWaveFormat->nSamplesPerSec;
    pHeader->dwAvgBytesPerSec = pWaveFormat->nAvgBytesPerSec;
    pHeader->wBlockAlign = pWaveFormat->nBlockAlign;
    pHeader->wBitsPerSample = pWaveFormat->wBitsPerSample;
    pHeader->dwDataSize = dwWaveLength;
    pHeader->dwSize = dwWaveLength + sizeof(*pHeader) - 8;

    return True;
}

#endif

inline
Bool
FASTCALL
InitWaveHeader(
    SWaveHeader *pHeader,
    UInt16 wChannels,
    UInt32 dwSampleRate,
    UInt16 wBitsPerSample,
    UInt32 dwWaveLength
)
{
    if (pHeader == NULL)
        return False;

    pHeader->RIFF = TAG4('RIFF');
    pHeader->fmt  = TAG4('fmt ');
    pHeader->WAVE = TAG4('WAVE');
    pHeader->data = TAG4('data');
    pHeader->wFormatTag = WAVE_FORMAT_PCM;
    pHeader->dwFormatLength = 16;
    pHeader->wChannels = wChannels;
    pHeader->wBitsPerSample = wBitsPerSample;
    pHeader->wBlockAlign = pHeader->wChannels * wBitsPerSample / 8;
    pHeader->dwSamplesPerSec = dwSampleRate;
    pHeader->dwAvgBytesPerSec = pHeader->wBlockAlign * pHeader->dwSamplesPerSec;
    pHeader->dwDataSize = dwWaveLength;
    pHeader->dwSize = dwWaveLength + sizeof(*pHeader) - 8;

    return True;
}

EXTC_IMPORT int WINAPI UCADecode(const void *src, int srclen, void** dst, int* dstlen);
EXTC_IMPORT int WINAPI UCADecode2(const void *src, int srclen, void** dst, int* dstlen, int sample);
EXTC_IMPORT int WINAPI UCAFree(void* p);

#endif /* _MY_AUDIO_H_ */