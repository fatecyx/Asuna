#ifndef _AUDIODECODER_H_1b62343d_cf2e_4d36_a1a5_d99b77198f60_
#define _AUDIODECODER_H_1b62343d_cf2e_4d36_a1a5_d99b77198f60_

#include "MyLibraryUser.h"
#include "bass/bass.h"
#include "bass/bass_aac.h"

enum EProfile
{
    PROFILE_LC, 
    PROFILE_HE, 
    PROFILE_HEV2, 
};

class NOVTABLE AudioDecoder
{
public:
    AudioDecoder();
    ~AudioDecoder();

    Bool Open(LPVoid lpStream, Bool bMem, PLarge_Integer pliLength = NULL, Bool bDecode = False);
    VOID SetLoopSection(PLarge_Integer pliStart = NULL, PLarge_Integer pliEnd = NULL);
    Bool FadeStop();
    Bool Free();
    Bool SetVolume(Long volume);
    Bool IsStreamValid() const;

    Bool Rewind();
    Bool Seek(const PLarge_Integer pliPos);
    Bool SeekBySeconds(double seconds);
    Bool SeekBySample(const PLarge_Integer pliPos);

    Bool GetPos(PLarge_Integer pliPos);
    Bool IsEndOfStream();
    Bool SeekToStartPos();
    Bool Update(UInt32 uLength);

    ULONG64 GetDataLength();
    UInt32 GetData(LPVoid lpBuffer, UInt32 uBufferSize);
    Int64  GetSamples();
    double GetTimeTotal();
    double GetTimeCurrent();

    Int32  GetErrorCode();
    BASS_CHANNELINFO* GetChannelInfo();

protected:
    Bool GetSamplesFromMetaInfo();
    Bool ThrowRubbish();
    VOID Init(Bool bDecode = TRUE);

protected:
    Bool                m_bNotFirstDecode;
    MemoryAllocator     m_mem;
    Bool                m_bInit;
    PByte               m_pbStream;
    ULong               m_StreamLength, m_BufferSize, m_ZeroPad, m_Delay, m_Profile;
    HANDLE              m_hEvent, m_hThread;
    HSTREAM             m_hStream;
    Large_Integer       m_TrueStart, m_TrueEnd, m_LoopStart, m_LoopEnd, m_SamplesTotal;
    BASS_CHANNELINFO    m_ChannelInfo;

    static UInt32 ObjectCount;
    static const UInt32 PadTable[3];
};

enum EMP4Tag
{
    MP4ODescrTag            = 0x01,
    MP4IODescrTag           = 0x02,
    MP4ESDescrTag           = 0x03,
    MP4DecConfigDescrTag    = 0x04,
    MP4DecSpecificDescrTag  = 0x05,
    MP4SLConfigDescrTag     = 0x06,
};

typedef struct {
  UInt8  version;
  UInt24 flags;

  /* 0x03 ESDescrTag */
  UInt16 ESId;
  UInt8  streamPriority;

  /* 0x04 DecConfigDescrTag */
  UInt8  objectTypeId;
  UInt8  streamType;
  /* XXX: really streamType is
   * only 6bit, followed by:
   * 1bit  upStream
   * 1bit  reserved
   */
  UInt24 bufferSizeDB;
  UInt32 maxBitrate;
  UInt32 avgBitrate;

  /* 0x05 DecSpecificDescrTag */
  UInt16  decoderConfigLen;
  UInt8 *decoderConfig;

  /* 0x06 SLConfigDescrTag */
  UInt8  SLConfigLen;
  UInt8 *SLConfig;

  /* TODO: add the missing tags,
   * I currently have no specs
   * for them and doubt they
   * are currently needed ::atmos
   */

} SEsds;

#endif // _AUDIODECODER_H_1b62343d_cf2e_4d36_a1a5_d99b77198f60_
