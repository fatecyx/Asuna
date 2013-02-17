#include "AudioDecoder.h"

#pragma comment(lib, "bass.lib")
#pragma comment(lib, "bass_aac.lib")

UInt32 AudioDecoder::ObjectCount = 0;
const UInt32 AudioDecoder::PadTable[3] = { 0x1000, 0x2000, 0x2000 };

AudioDecoder::AudioDecoder()
{
    m_bInit = False;
    m_hStream = 0;
}

AudioDecoder::~AudioDecoder()
{
    if (m_bInit)
    {
        Free();

        if (m_pbStream)
            m_mem.Free(m_pbStream);

        if (_InterlockedDecrement((PLONG)&ObjectCount) == 0)
            BASS_Free();
    }
}

VOID AudioDecoder::Init(Bool bDecode)
{
    m_bInit                 = True;
    m_hThread               = 0;
    m_pbStream              = 0;
    m_BufferSize            = 0;
    m_Profile               = PROFILE_LC;
    m_TrueStart.QuadPart    = 0;
    m_TrueEnd.QuadPart      = -1;

    if (_InterlockedIncrement((PLONG)&ObjectCount) == 1)
    {
        BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD, 0);
        BASS_Init(0, 44100, 0, NULL, 0);
    }
}

Bool AudioDecoder::Free()
{
    if (BASS_StreamFree(m_hStream))
        return False;

    m_hStream = 0;

    return True;
}

Bool AudioDecoder::Open(LPVoid lpStream, Bool bMem, PLarge_Integer pliLength /* = NULL */, Bool bDecode /* = False */)
{
    if (!m_bInit)
        Init(bDecode);

    Free();
    if (bMem)
    {
        m_StreamLength = pliLength->LowPart;
        if (m_pbStream)
        {
            if (m_StreamLength > m_BufferSize)
            {
                PByte pbReAlloc;
                pbReAlloc = (PByte)m_mem.ReAlloc(m_pbStream, m_StreamLength);
                if (pbReAlloc == NULL)
                    return False;
                m_BufferSize = m_StreamLength;
                m_pbStream = pbReAlloc;
            }
        }
        else
        {
            m_BufferSize = m_StreamLength;
            m_pbStream = (PByte)m_mem.Alloc(m_BufferSize);
            if (m_pbStream == NULL)
                return False;
        }

        memcpy(m_pbStream, lpStream, pliLength->LowPart);
        lpStream = m_pbStream;
    }

    m_hStream = BASS_MP4_StreamCreateFile(bMem, lpStream, 0, pliLength->QuadPart, bDecode ? BASS_STREAM_DECODE : 0);
    if (m_hStream == NULL)
        return False;

    if (!BASS_ChannelGetInfo(m_hStream, &m_ChannelInfo))
        return False;

    ULong BytesPerSample;

    BytesPerSample = !(m_ChannelInfo.flags & BASS_SAMPLE_8BITS) + 1;   // ? 1 : 2;
    BytesPerSample *= m_ChannelInfo.chans;

    GetSamplesFromMetaInfo();

    if (m_TrueStart.QuadPart)
        m_TrueStart.QuadPart *= BytesPerSample;
    if (m_TrueEnd.QuadPart != -1)
        m_TrueEnd.QuadPart *= BytesPerSample;

    m_LoopStart = m_TrueStart;
    m_LoopEnd.QuadPart = m_TrueEnd.QuadPart + m_TrueStart.QuadPart;
    if (m_Profile != PROFILE_LC)
        m_LoopEnd.QuadPart += m_TrueEnd.QuadPart;

    if (bDecode)
        ThrowRubbish();

    return True;
}

Bool AudioDecoder::ThrowRubbish()
{
    Byte buf[0x800];

    BASS_ChannelSetPosition(m_hStream, m_TrueEnd.QuadPart, BASS_POS_BYTE);
    while (GetData(buf, sizeof(buf)) != BASS_ERROR_UNKNOWN);

    return True;
}

BASS_CHANNELINFO* AudioDecoder::GetChannelInfo()
{
    if (!IsStreamValid())
        return NULL;

    return &m_ChannelInfo;
}

Bool AudioDecoder::IsStreamValid() const
{
    return !!m_hStream;
}

Bool AudioDecoder::Rewind()
{
    if (!IsStreamValid())
        return False;

    return BASS_ChannelSetPosition(m_hStream, m_TrueStart.QuadPart, BASS_POS_BYTE);
}

Bool AudioDecoder::Seek(const PLarge_Integer pliPos)
{
    if (!IsStreamValid())
        return False;

    Large_Integer liPos;

    if (pliPos && pliPos->QuadPart)
        liPos.QuadPart = pliPos->QuadPart + m_LoopStart.QuadPart;
    else
    {
        return ThrowRubbish();
    }

    return BASS_ChannelSetPosition(m_hStream, liPos.QuadPart, BASS_POS_BYTE);
}

Bool AudioDecoder::SeekBySeconds(double seconds)
{
    if (!IsStreamValid())
        return False;

    ULong dwBytesPerSecond;
    Large_Integer pos;

    dwBytesPerSecond = (m_ChannelInfo.flags & BASS_SAMPLE_8BITS) ? 1 : 2;
    dwBytesPerSecond *= m_ChannelInfo.chans;
    dwBytesPerSecond *= m_ChannelInfo.freq;

    pos.QuadPart = (Long64)(dwBytesPerSecond * seconds);

    return Seek(&pos);
}

Bool AudioDecoder::SeekBySample(const PLarge_Integer pliSample)
{
    if (!IsStreamValid())
        return False;

    Large_Integer liPos = m_LoopStart;

    if (pliSample)
        liPos.QuadPart += pliSample->QuadPart *
                          ((m_ChannelInfo.flags & BASS_SAMPLE_8BITS) ? 1 : 2) *
                          m_ChannelInfo.chans;

    return BASS_ChannelSetPosition(m_hStream, liPos.QuadPart, BASS_POS_BYTE);
}

Bool AudioDecoder::GetPos(PLarge_Integer pliPos)
{
    if (!IsStreamValid())
        return False;

    pliPos->QuadPart = BASS_ChannelGetPosition(m_hStream, BASS_POS_BYTE);
    return True;
}

Bool AudioDecoder::IsEndOfStream()
{
    Large_Integer liPos;

    if (!GetPos(&liPos))
        return True;

    return liPos.QuadPart >= m_LoopEnd.QuadPart;
}

Int32 AudioDecoder::GetErrorCode()
{
    return BASS_ErrorGetCode();
}

Bool AudioDecoder::SeekToStartPos()
{
    if (!IsStreamValid())
        return False;

    ThrowRubbish();
//    BASS_ChannelSetPosition(m_hStream, m_liLoopStart.QuadPart, BASS_POS_BYTE);

    return True;
}

Bool AudioDecoder::Update(UInt32 uLength)
{
    if (!IsStreamValid())
        return False;

    return BASS_ChannelUpdate(m_hStream, uLength);
}

ULONG64 AudioDecoder::GetDataLength()
{
    if (!IsStreamValid())
        return 0;

    return m_LoopEnd.QuadPart - m_LoopStart.QuadPart;
}

UInt32 AudioDecoder::GetData(LPVoid lpBuffer, UInt32 uBufferSize)
{
    if (!IsStreamValid())
        return BASS_ERROR_UNKNOWN;

    UInt32 CurPos, Length;

    Length = 0;
    CurPos = (UInt32)BASS_ChannelGetPosition(m_hStream, BASS_POS_BYTE);
    if (CurPos >= m_LoopEnd.QuadPart)
    {
        BASS_ChannelSetPosition(m_hStream, 0, BASS_POS_BYTE);
        if (!m_bNotFirstDecode)
        {
            m_bNotFirstDecode = True;
            m_LoopEnd.LowPart += PadTable[m_Profile];
            m_LoopStart.LowPart += PadTable[m_Profile];
        }

        return BASS_ERROR_UNKNOWN;
    }
    else if (CurPos == 0)
    {
        Int32 BlockSize, SizeRemain;

        SizeRemain = m_LoopStart.LowPart;
//        if (m_bNotFirstDecode)
//            SizeRemain += PadTable[m_dwCodec];

        BlockSize = min((Int32)uBufferSize, SizeRemain);
        while (SizeRemain > 0)
        {
            ULONG Length;
            Length = BASS_ChannelGetData(m_hStream, lpBuffer, min(BlockSize, SizeRemain));
            if (Length == BASS_ERROR_UNKNOWN)
                break;

            SizeRemain -= Length;
        }
    }

    if (Length != BASS_ERROR_UNKNOWN)
        Length = BASS_ChannelGetData(m_hStream, lpBuffer, uBufferSize);

    if (Length == BASS_ERROR_UNKNOWN)
    {
        BASS_ChannelSetPosition(m_hStream, 0, BASS_POS_BYTE);
        if (!m_bNotFirstDecode)
        {
            m_bNotFirstDecode = True;
            m_LoopEnd.LowPart += PadTable[m_Profile];
            m_LoopStart.LowPart += PadTable[m_Profile];
        }
        return Length;
    }

    if (CurPos + Length > m_LoopEnd.QuadPart)
    {
        Length = (UInt32)(m_LoopEnd.QuadPart - CurPos);
    }

    return Length;
}

Int64 AudioDecoder::GetSamples()
{
    if (!IsStreamValid())
        return 0;

    return m_SamplesTotal.QuadPart;
}

double AudioDecoder::GetTimeTotal()
{
    if (!IsStreamValid())
        return 0;

    Large_Integer  liLength;
    PLarge_Integer pliLength;

    if (m_LoopEnd.QuadPart == -1)
    {
        liLength.QuadPart = BASS_ChannelGetLength(m_hStream, BASS_POS_BYTE);
        pliLength = &liLength;
    }
    else
    {
        pliLength = &m_LoopEnd;
    }

    return BASS_ChannelBytes2Seconds(m_hStream, pliLength->QuadPart) -
           BASS_ChannelBytes2Seconds(m_hStream, m_LoopStart.QuadPart);
}

double AudioDecoder::GetTimeCurrent()
{
    if (!IsStreamValid())
        return 0;

    return BASS_ChannelBytes2Seconds(m_hStream, BASS_ChannelGetPosition(m_hStream, BASS_POS_BYTE));
}

VOID AudioDecoder::SetLoopSection(PLarge_Integer pliStart /* = NULL */, PLarge_Integer pliEnd /* = NULL */)
{
    if (pliStart)
        m_LoopStart.QuadPart = m_TrueStart.QuadPart + pliStart->QuadPart;
    if (pliEnd)
        m_LoopEnd.QuadPart   = min(pliEnd->QuadPart, m_TrueEnd.QuadPart);
}

Bool AudioDecoder::SetVolume(Long volume)
{
    if (!IsStreamValid())
        return False;
    return BASS_ChannelSetAttribute(m_hStream, BASS_ATTRIB_VOL, volume / 100.f);
}

PByte FindAtom(ULong tag, PByte pbStart, ULong dwSection)
{
    PByte pbEnd;
    ULong dwSize;

    pbEnd = pbStart + dwSection;
    while (pbStart < pbEnd)
    {
        dwSize = Bswap(*(LPDWORD)pbStart);
        if (*(LPDWORD)(pbStart + 4) == tag)
            break;
        pbStart += dwSize;
    }

    if (pbStart >= pbEnd)
        return NULL;

    return pbStart;
}

Int32 mp4_read_descr_len(PByte &pbData)
{
    UInt8 b, numBytes = 0;
    Int32 length = 0;
    PByte p = pbData;

    do {
        b = *p++;
        numBytes++;
        length = (length << 7) | (b & 0x7F);
    } while ((b & 0x80) && numBytes != 4);

    pbData = p;
    return length;
}

Bool AudioDecoder::GetSamplesFromMetaInfo()
{
    Int32 Size, val;
    PByte pbStart, pbTrack, pbUdta, pbEsds, pbIlst;

    pbStart = m_pbStream;
    m_SamplesTotal.QuadPart = 0;

    pbStart = FindAtom(TAG4('moov'), pbStart, m_StreamLength);
    if (pbStart == NULL)
        return False;
    pbTrack = FindAtom(TAG4('trak'), pbStart + 8, Bswap(*(LPDWORD)pbStart) - 8);
    if (pbTrack == NULL)
        return False;
    pbUdta = FindAtom(TAG4('udta'), pbStart + 8, Bswap(*(LPDWORD)pbStart) - 8);
    if (pbUdta == NULL)
        return False;

    pbTrack = FindAtom(TAG4('mdia'), pbTrack + 8, Bswap(*(LPDWORD)pbTrack) - 8);
    if (pbTrack == NULL)
        return False;
    pbTrack = FindAtom(TAG4('minf'), pbTrack + 8, Bswap(*(LPDWORD)pbTrack) - 8);
    if (pbTrack == NULL)
        return False;
    pbTrack = FindAtom(TAG4('stbl'), pbTrack + 8, Bswap(*(LPDWORD)pbTrack) - 8);
    if (pbTrack == NULL)
        return False;
    pbTrack = FindAtom(TAG4('stsd'), pbTrack + 8, Bswap(*(LPDWORD)pbTrack) - 8);
    if (pbTrack == NULL)
        return False;
    pbTrack += 0x10;
    Size = Bswap(*(LPDWORD)pbTrack);
    if (Size <= 0x24)
        return False;

    pbTrack += 0x24;
    pbEsds = FindAtom(TAG4('esds'), pbTrack, Size - 0x24);
    if (pbEsds == NULL)
        return False;

    Size = Bswap(*(LPDWORD)pbEsds);
    if (Size <= 0xC)
        return False;

    Size -= 0xC;
    pbEsds += 0xC;
    if (*pbEsds++ != MP4ESDescrTag)
        return False;

    if (mp4_read_descr_len(pbEsds) < 5 + 15)
        return False;

    pbEsds += 3;
    if (*pbEsds++ != MP4DecConfigDescrTag)
        return False;

    if (mp4_read_descr_len(pbEsds) < 15)
        return False;

    pbEsds += 13;
    if (*pbEsds++ != MP4DecSpecificDescrTag)
        return False;

    Size = mp4_read_descr_len(pbEsds);
    m_Delay = 0;

    if (Size <= 5)  // lc
    {
//        m_dwDelay = m_liTrueStart.QuadPart = 0x640;
        m_Delay = m_TrueStart.LowPart = -0x400u;
    }
    else if (Size >= 7)
    {
        if ((*(pbEsds + 1) & 0x10) && !(*(pbEsds + 6) & 0x80))
        {
//            m_dwDelay = m_liTrueStart.QuadPart = 0xA40;
            m_Delay = m_TrueStart.LowPart = 0x45A;
            m_Profile = PROFILE_HE;
        }
        else
        {
//            m_dwDelay = m_liTrueStart.QuadPart = 0xDF0;
            m_Profile = PROFILE_HEV2;
        }
    }
    else
        return False;

    pbIlst = FindAtom(TAG4('meta'), pbUdta + 8, Bswap(*(LPDWORD)pbUdta) - 8);
    if (pbIlst == NULL)
        return True;

    pbIlst = FindAtom(TAG4('ilst'), pbIlst + 12, Bswap(*(LPDWORD)pbIlst) - 12);
    if (pbIlst == NULL)
        return True;

    Size = Bswap(*(LPDWORD)pbIlst) - 8;
    pbIlst += 8;
    pbStart = pbIlst + Size;
    while (pbIlst < pbStart)
    {
        Int32 len = Bswap(*(LPDWORD)pbIlst) - 8;

        pbIlst += 8;

        while (len > 0)
        {
            Int32 l = Bswap(*(LPDWORD)pbIlst);

            len -= l;
            if (l == 20 &&
                *(LPDWORD)(pbIlst + 4 ) == TAG4('name')  &&
                *(LPDWORD)(pbIlst + 12) == TAG4('iTun') &&
                *(LPDWORD)(pbIlst + 16) == TAG4('SMPB'))
            {
                pbIlst += l;
                goto FIND_ITUNSMPB;
            }

            pbIlst += l;
        }

        pbIlst += len;
    }

FIND_ITUNSMPB:
    if (pbIlst >= pbStart)
        return True;

    Size = Bswap(*(LPDWORD)pbIlst) - 0x10;
    pbIlst += 0x10;
    if (*pbIlst == ' ')
    {
        ++pbIlst;
        if (--Size <= 0)
            return True;
    }

    while (Size-- > 0 && *pbIlst++ != ' ');
    if (Size <= 0)
        return True;

    val = 0;
    while (Size-- > 0)
    {
        BYTE b = *pbIlst++;
        if (b == ' ')
            break;
/*
        if (b >= '0' && b <= '9');
        else if (b >= 'A' && b <= 'F');
        else if (b >= 'a' && b <= 'f');
        else return True;

        continue;
*/
        if (b >= '0' && b <= '9')
            b -= '0';
        else if (b >= 'A' && b <= 'F')
            b = b - 'A' + 10;
        else if (b >= 'a' && b <= 'f')
            b = b - 'a' + 10;
        else
            return True;

        val = (val << 4) | b;
    }
    // encoder delay
    if (val)
    {
//        m_liTrueStart.QuadPart += val;
        m_TrueStart.LowPart += val;
        m_Delay += val;
    }

    if (Size <= 0)
        return True;

    if (*pbIlst == ' ')
    {
        ++pbIlst;
        if (--Size <= 0)
            return True;
    }

    --Size;
    val = 0;
    while (Size-- > 0)
    {
        BYTE b = *pbIlst++;
        if (b == ' ')
            break;

        if (b >= '0' && b <= '9');
        else if (b >= 'A' && b <= 'F');
        else if (b >= 'a' && b <= 'f');
        else return True;

        continue;
/*
        if (b >= '0' && b <= '9')
            b -= '0';
        else if (b >= 'A' && b <= 'F')
            b = b - 'A' + 10;
        else if (b >= 'a' && b <= 'f')
            b = b - 'a' + 10;
        else
            return True;

        val = (val << 4) | b;
*/
    }
    // zero padding
/*
    if (0) if (val)
    {
        m_TrueStart.LowPart += val;
        m_ZeroPad = val;
    }
*/
    if (Size <= 0)
        return True;

    // samples of the original track
    m_TrueEnd.QuadPart = 0;
    while (Size-- > 0)
    {
        BYTE b = *pbIlst++;
        if (b == ' ')
            break;

        if (b >= '0' && b <= '9')
            b -= '0';
        else if (b >= 'A' && b <= 'F')
            b = b - 'A' + 10;
        else if (b >= 'a' && b <= 'f')
            b = b - 'a' + 10;
        else
            return True;

        m_TrueEnd.QuadPart = (m_TrueEnd.QuadPart << 4) | b;
    }

    m_SamplesTotal.QuadPart = m_TrueEnd.QuadPart;

    return True;
}