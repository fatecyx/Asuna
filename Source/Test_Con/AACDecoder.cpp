#include "AACDecoder.h"

#include "mp4ff/mp4atom.cpp"
#include "mp4ff/mp4ff.cpp"
//#include "mp4ff/mp4meta.cpp"
#include "mp4ff/mp4sample.cpp"
//#include "mp4ff/mp4tagupdate.cpp"
#include "mp4ff/mp4util.cpp"

CAACDecoder::CAACDecoder()
{
    m_hDecoder = NULL;
    m_pvBuffer = NULL;
    ZeroMemory(&m_Mp4File, sizeof(m_Mp4File));

    *(PVOID *)&m_Mp4Callback.read = ReadCallback;
    *(PVOID *)&m_Mp4Callback.seek = SeekCallback;
    m_Mp4Callback.user_data = this;
}

CAACDecoder::~CAACDecoder()
{
    ReleaseAll();
}

BOOL CAACDecoder::ReleaseAll()
{
    BOOL Result;

    Close();
    Result = m_mem.SafeFree(&m_pvBuffer);
    m_BufferSize = 0;

    return Result;
}

PVOID CAACDecoder::AllocBuffer(ULONG Size)
{
    if (m_pvBuffer == NULL)
    {
        m_BufferSize = Size;
        m_pvBuffer = m_mem.Alloc(Size);
        return m_pvBuffer;
    }
    else if (m_BufferSize < Size)
    {
        m_BufferSize = Size;
        m_pvBuffer = m_mem.ReAlloc(m_pvBuffer, m_BufferSize);
    }

    return m_pvBuffer;
}

BOOL CAACDecoder::Open(PVOID pvBuffer, ULONG BufferSize)
{
    BOOL  Result;
    PVOID pvAudioBuffer;
    LONG  Track;

    if (!Close())
        return FALSE;

    pvAudioBuffer = AllocBuffer(BufferSize);
    if (pvAudioBuffer == NULL)
        return FALSE;

    m_StreamSize = BufferSize;
    CopyMemory(m_pvBuffer, pvBuffer, m_StreamSize);
    m_Offset.QuadPart = 0;

    ZeroMemory(&m_Mp4File, sizeof(m_Mp4File));
    m_Mp4File.stream = &m_Mp4Callback;
    parse_atoms(&m_Mp4File, 0);

    Result = FALSE;
    LOOP_ONCE
    {
        PBYTE pbConfig;
        ULONG Size;
        NeAACDecConfigurationPtr pCurConfig;

        Track = GetAACTrack();
        if (Track < 0)
            break;

        m_hDecoder = NeAACDecOpen();
        if (m_hDecoder == NULL)
            break;

        m_Info.Channels = 0;
        pbConfig = GetDecoderConfig(Track, &Size);
        if (NeAACDecInit2(m_hDecoder, pbConfig, Size, &m_Info.Rate, (PBYTE)&m_Info.Channels) < 0)
            break;

        pCurConfig = NeAACDecGetCurrentConfiguration(m_hDecoder);
        if (pCurConfig == NULL)
            break;

        switch (pCurConfig->outputFormat)
        {
            case FAAD_FMT_24BIT: m_Info.BitsPerSample = 24; break;
            case FAAD_FMT_32BIT: m_Info.BitsPerSample = 32; break;
            case FAAD_FMT_16BIT:
            default:             m_Info.BitsPerSample = 16; break;
        }

        m_Info.AACTrack = Track;
        m_Info.Profile  = PROFILE_LC;
        if (!ParseItunsmpb(&m_Info))
        {
            m_Info.Samples.QuadPart     = m_Mp4File.duration;
            m_Info.TrueStart.QuadPart   = 0;
            m_Info.TrueEnd.QuadPart     = -1;
        }

        Result = TRUE;
    }

    if (!Result)
        Close();

    return Result;
}

BOOL CAACDecoder::Close()
{
    int32_t i;
    mp4ff_t *ff = &m_Mp4File;

    for (i = 0; i < ff->total_tracks; i++)
    {
        if (ff->track[i])
        {
            if (ff->track[i]->stsz_table)
                free(ff->track[i]->stsz_table);
            if (ff->track[i]->stts_sample_count)
                free(ff->track[i]->stts_sample_count);
            if (ff->track[i]->stts_sample_delta)
                free(ff->track[i]->stts_sample_delta);
            if (ff->track[i]->stsc_first_chunk)
                free(ff->track[i]->stsc_first_chunk);
            if (ff->track[i]->stsc_samples_per_chunk)
                free(ff->track[i]->stsc_samples_per_chunk);
            if (ff->track[i]->stsc_sample_desc_index)
                free(ff->track[i]->stsc_sample_desc_index);
            if (ff->track[i]->stco_chunk_offset)
                free(ff->track[i]->stco_chunk_offset);
            if (ff->track[i]->decoderConfig)
                free(ff->track[i]->decoderConfig);
            if (ff->track[i]->ctts_sample_count)
                free(ff->track[i]->ctts_sample_count);
            if (ff->track[i]->ctts_sample_offset)
                free(ff->track[i]->ctts_sample_offset);
#ifdef ITUNES_DRM
            if (ff->track[i]->p_drms)
                drms_free(ff->track[i]->p_drms);
#endif
            free(ff->track[i]);
        }
    }

#ifdef USE_TAGGING
    mp4ff_tag_delete(&(ff->tags));
#endif

    ZeroMemory(ff, sizeof(*ff));

    if (m_hDecoder != NULL)
    {
        NeAACDecClose(m_hDecoder);
        m_hDecoder = NULL;
    }

    return TRUE;
}

ULONG64 CAACDecoder::SeekBySample(ULONG64 Sample)
{
    return 0;
}

ULONG64 CAACDecoder::SeekByPos(ULONG64 Pos)
{
    return 0;;
}

ULONG CAACDecoder::Decode(PVOID pvBuffer, ULONG BufferSize, ULONG Samples)
{
    return 0;
}

PBYTE CAACDecoder::GetDecoderConfig(ULONG Track, PULONG pConfiSize)
{
    mp4ff_t *f = &m_Mp4File;

    if (pConfiSize != NULL)
        *pConfiSize = 0;

    if (Track >= f->total_tracks)
        return NULL;

    if (f->track[Track]->decoderConfig == NULL || f->track[Track]->decoderConfigLen == 0)
        return NULL;

    if (pConfiSize != NULL)
        *pConfiSize = f->track[Track]->decoderConfigLen;

    return f->track[Track]->decoderConfig;
}

ULONG CAACDecoder::GetAACTrack()
{
    mp4AudioSpecificConfig Mp4ASC;

    for (ULONG Track = 0, Count = m_Mp4File.total_tracks; Count; ++Track, --Count)
    {
        PBYTE pbBuffer;
        ULONG BufferSize;

        pbBuffer = GetDecoderConfig(Track, &BufferSize);
        if (pbBuffer != NULL && NeAACDecAudioSpecificConfig(pbBuffer, BufferSize, &Mp4ASC) >= 0)
            return Track;
    }

    return -1;
}

ULONG CAACDecoder::ReadCallback(CAACDecoder *pThis, PVOID pvBuffer, ULONG Length)
{
    Length = min(Length, pThis->m_StreamSize - pThis->m_Offset.LowPart);
    CopyMemory(pvBuffer, (PBYTE)pThis->m_pvBuffer + pThis->m_Offset.LowPart, Length);
    pThis->m_Offset.QuadPart += Length;
    return Length;
}

ULONG CAACDecoder::SeekCallback(CAACDecoder *pThis, ULONG64 Position)
{
    pThis->m_Offset.QuadPart = Position;
    return 0;
}

PBYTE FindAtom(ULONG tag, PBYTE pbStart, ULONG dwSection)
{
    PBYTE pbEnd;
    ULONG dwSize;

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

LONG mp4_read_descr_len(PBYTE &pbData)
{
    BYTE  b, numBytes = 0;
    LONG  length = 0;
    PBYTE p = pbData;

    do {
        b = *p++;
        numBytes++;
        length = (length << 7) | (b & 0x7F);
    } while ((b & 0x80) && numBytes != 4);

    pbData = p;
    return length;
}

BOOL CAACDecoder::ParseItunsmpb(AUDIO_INFO *pAudioInfo)
{
    ULONG Size, val;
    PBYTE pbStart, pbTrack, pbUdta, pbIlst;

    enum EMP4Tag
    {
        MP4ODescrTag            = 0x01,
        MP4IODescrTag           = 0x02,
        MP4ESDescrTag           = 0x03,
        MP4DecConfigDescrTag    = 0x04,
        MP4DecSpecificDescrTag  = 0x05,
        MP4SLConfigDescrTag     = 0x06,
    };

    enum
    {
        DECODER_CONFIG_LC   = 0x1012,
        DECODER_CONFIG_HE   = 0x9013,
        DECODER_CONFIG_HEV2 = 0x8813,
    };

    pAudioInfo->TrueStart.QuadPart = 0;
    pAudioInfo->TrueEnd.QuadPart  = -1;

    PBYTE pbDecoderConfig = GetDecoderConfig(pAudioInfo->AACTrack, NULL);

    if (!TEST_BITS(pbDecoderConfig[1] & 0xF0, 0x80))
    {
        pAudioInfo->Profile = PROFILE_LC;
        pAudioInfo->TrueStart.QuadPart = -0x400;
    }
    else if (TEST_BITS((pbDecoderConfig[1] & 0xF0), 0x10))
    {
        pAudioInfo->Profile = PROFILE_HE;
        pAudioInfo->TrueStart.QuadPart = -0x45A;
    }
    else if (TEST_BITS((pbDecoderConfig[1] & 0xF0), 0x80))
    {
        pAudioInfo->Profile = PROFILE_HEV2;
    }

    pbStart = (PBYTE)m_pvBuffer;

    pbStart = FindAtom(TAG4('moov'), pbStart, m_StreamSize);
    if (pbStart == NULL)
        return FALSE;

    pbTrack = FindAtom(TAG4('trak'), pbStart + 8, Bswap(*(LPDWORD)pbStart) - 8);
    if (pbTrack == NULL)
        return FALSE;

    pbUdta = FindAtom(TAG4('udta'), pbStart + 8, Bswap(*(LPDWORD)pbStart) - 8);
    if (pbUdta == NULL)
        return FALSE;

    pbIlst = FindAtom(TAG4('meta'), pbUdta + 8, Bswap(*(LPDWORD)pbUdta) - 8);
    if (pbIlst == NULL)
        return TRUE;

    pbIlst = FindAtom(TAG4('ilst'), pbIlst + 12, Bswap(*(LPDWORD)pbIlst) - 12);
    if (pbIlst == NULL)
        return TRUE;

    Size = Bswap(*(LPDWORD)pbIlst) - 8;
    pbIlst += 8;
    pbStart = pbIlst + Size;
    while (pbIlst < pbStart)
    {
        LONG len = Bswap(*(LPDWORD)pbIlst) - 8;

        pbIlst += 8;

        while (len > 0)
        {
            LONG l = Bswap(*(LPDWORD)pbIlst);

            len -= l;
            if (l == 20 &&
                *(LPDWORD)(pbIlst + 4 ) == TAG4('name')  &&
                *(LPDWORD)(pbIlst + 12) == TAG4('iTun') &&
                *(LPDWORD)(pbIlst + 16) == TAG4('SMPB'))
            {
                pbIlst += l;
                goto FOUND_ITUNSMPB;
            }

            pbIlst += l;
        }

        pbIlst += len;
    }

FOUND_ITUNSMPB:
    if (pbIlst >= pbStart)
        return TRUE;

    Size = Bswap(*(LPDWORD)pbIlst) - 0x10;
    pbIlst += 0x10;
    if (*pbIlst == ' ')
    {
        ++pbIlst;
        if (--Size <= 0)
            return TRUE;
    }

    while (Size-- > 0 && *pbIlst++ != ' ');
    if (Size <= 0)
        return TRUE;

    val = 0;
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
            return TRUE;

        val = (val << 4) | b;
    }

    // encoder delay
    if (val)
    {
        pAudioInfo->TrueStart.QuadPart += val;
    }

    if (Size <= 0)
        return TRUE;

    if (*pbIlst == ' ')
    {
        ++pbIlst;
        if (--Size <= 0)
            return TRUE;
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
        else return TRUE;
    }

    if (Size <= 0)
        return TRUE;

    // samples of the original track
    pAudioInfo->TrueEnd.QuadPart = 0;
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
            return TRUE;

        pAudioInfo->TrueEnd.QuadPart = (pAudioInfo->TrueEnd.QuadPart << 4) | b;
    }

    pAudioInfo->Samples.QuadPart = pAudioInfo->TrueEnd.QuadPart;

    return TRUE;
}
