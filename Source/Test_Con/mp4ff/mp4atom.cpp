/*
** FAAD2 - Freeware Advanced Audio (AAC) Decoder including SBR decoding
** Copyright (C) 2003-2005 M. Bakker, Nero AG, http://www.nero.com
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software 
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
**
** Any non-GPL usage of this software or parts of this software is strictly
** forbidden.
**
** The "appropriate copyright message" mentioned in section 2c of the GPLv2
** must read: "Code from FAAD2 is copyright (c) Nero AG, www.nero.com"
**
** Commercial non-GPL licensing of this software is possible.
** For more info contact Nero AG through Mpeg4AAClicense@nero.com.
**
** $Id: mp4atom.c,v 1.29 2009/01/19 23:56:30 menno Exp $
**/

#include <stdlib.h>
#ifndef _WIN32
#include "config.h"
#else
#include <tchar.h>
#include <windows.h>
#endif
#ifdef HAVE_GETPWUID
#    include <pwd.h>
#endif
#ifdef HAVE_STRING_H
#    include <string.h>
#endif
#include "mp4ffint.h"

#define       COPYRIGHT_SYMBOL        ((int8_t)0xA9)

/* parse atom header size */
static int32_t mp4ff_atom_get_size(const int8_t *data)
{
    uint32_t result;
    uint32_t a, b, c, d;

    a = (uint8_t)data[0];
    b = (uint8_t)data[1];
    c = (uint8_t)data[2];
    d = (uint8_t)data[3];

    result = (a<<24) | (b<<16) | (c<<8) | d;
    //if (result > 0 && result < 8) result = 8;

    return (int32_t)result;
}

uint32_t mp4ff_atom_name_to_type(uint32_t atom_name)
{
    atom_name &= 0x7FFFFFFF;

    switch (atom_name)
    {
        case TAG4('moov'): return ATOM_MOOV;
        case TAG4('minf'): return ATOM_MINF;
        case TAG4('mdia'): return ATOM_MDIA;
        case TAG4('mdat'): return ATOM_MDAT;
        case TAG4('mdhd'): return ATOM_MDHD;
        case TAG4('mvhd'): return ATOM_MVHD;
        case TAG4('mp4a'): return ATOM_MP4A;
        case TAG4('mp4v'): return ATOM_MP4V;
        case TAG4('mp4s'): return ATOM_MP4S;
        case TAG4('meta'): return ATOM_META;

        case TAG4('trak'): return ATOM_TRAK;
        case TAG4('tkhd'): return ATOM_TKHD;
        case TAG4('tref'): return ATOM_TREF;
        case TAG4('trkn'): return ATOM_TRACK;
        case TAG4('tmpo'): return ATOM_TEMPO;
        case TAG4('tvnn'): return ATOM_NETWORK;
        case TAG4('tvsh'): return ATOM_SHOW;
        case TAG4('tven'): return ATOM_EPISODENAME;
        case TAG4('tvsn'): return ATOM_SEASON;
        case TAG4('tves'): return ATOM_EPISODE;

        case TAG4('stbl'): return ATOM_STBL;
        case TAG4('smhd'): return ATOM_SMHD;
        case TAG4('stsd'): return ATOM_STSD;
        case TAG4('stts'): return ATOM_STTS;
        case TAG4('stco'): return ATOM_STCO;
        case TAG4('stsc'): return ATOM_STSC;
        case TAG4('stsz'): return ATOM_STSZ;
        case TAG4('stz2'): return ATOM_STZ2;
        case TAG4('skip'): return ATOM_SKIP;
        case TAG4('sinf'): return ATOM_SINF;
        case TAG4('schi'): return ATOM_SCHI;
        case TAG4('sonm'): return ATOM_SORTTITLE;
        case TAG4('soal'): return ATOM_SORTALBUM;
        case TAG4('soar'): return ATOM_SORTARTIST;
        case TAG4('soaa'): return ATOM_SORTALBUMARTIST;
        case TAG4('soco'): return ATOM_SORTWRITER;
        case TAG4('sosn'): return ATOM_SORTSHOW;

        case TAG4(')nam'): return ATOM_TITLE;
        case TAG4(')ART'): return ATOM_ARTIST;
        case TAG4(')wrt'): return ATOM_WRITER;
        case TAG4(')alb'): return ATOM_ALBUM;
        case TAG4(')day'): return ATOM_DATE;
        case TAG4(')too'): return ATOM_TOOL;
        case TAG4(')cmt'): return ATOM_COMMENT;
        case TAG4(')gen'): return ATOM_GENRE1;
        case TAG4(')grp'): return ATOM_CONTENTGROUP;
        case TAG4(')lyr'): return ATOM_LYRICS;

        case TAG4('edts'): return ATOM_EDTS;
        case TAG4('esds'): return ATOM_ESDS;
        case TAG4('ftyp'): return ATOM_FTYP;
        case TAG4('free'): return ATOM_FREE;
        case TAG4('hmhd'): return ATOM_HMHD;
        case TAG4('vmhd'): return ATOM_VMHD;
        case TAG4('udta'): return ATOM_UDTA;
        case TAG4('ilst'): return ATOM_ILST;
        case TAG4('name'): return ATOM_NAME;
        case TAG4('data'): return ATOM_DATA;
        case TAG4('disk'): return ATOM_DISC;
        case TAG4('gnre'): return ATOM_GENRE2;
        case TAG4('covr'): return ATOM_COVER;
        case TAG4('cpil'): return ATOM_COMPILATION;
        case TAG4('ctts'): return ATOM_CTTS;
        case TAG4('drms'): return ATOM_DRMS;
        case TAG4('frma'): return ATOM_FRMA;
        case TAG4('priv'): return ATOM_PRIV;
        case TAG4('iviv'): return ATOM_IVIV;
        case TAG4('user'): return ATOM_USER;
        case TAG4('key '): return ATOM_KEY;
        case TAG4('aART'): return ATOM_ALBUM_ARTIST;
        case TAG4('desc'): return ATOM_DESCRIPTION;
        case TAG4('pcst'): return ATOM_PODCAST;
    }

    return ATOM_UNKNOWN;
}

/* read atom header, return atom size, atom size is with header included */
uint64_t mp4ff_atom_read_header(mp4ff_t *f, uint8_t *atom_type, uint8_t *header_size)
{
    uint64_t size;
    int32_t ret;
    int8_t atom_header[8];

    ret = mp4ff_read_data(f, atom_header, 8);
    if (ret != 8)
        return 0;

    size = mp4ff_atom_get_size(atom_header);
    *header_size = 8;

    /* check for 64 bit atom size */
    if (size == 1)
    {
        *header_size = 16;
        size = mp4ff_read_int64(f);
    }

    //printf("%c%c%c%c\n", atom_header[4], atom_header[5], atom_header[6], atom_header[7]);

    *atom_type = mp4ff_atom_name_to_type(*(uint32_t *)&atom_header[4]);

    return size;
}

static int32_t mp4ff_read_stsz(mp4ff_t *f)
{
    mp4ff_read_char(f); /* version */
    mp4ff_read_int24(f); /* flags */
    f->track[f->total_tracks - 1]->stsz_sample_size = mp4ff_read_int32(f);
    f->track[f->total_tracks - 1]->stsz_sample_count = mp4ff_read_int32(f);

    if (f->track[f->total_tracks - 1]->stsz_sample_size == 0)
    {
        int32_t i;
        f->track[f->total_tracks - 1]->stsz_table =
            (int32_t*)malloc(f->track[f->total_tracks - 1]->stsz_sample_count*sizeof(int32_t));

        for (i = 0; i < f->track[f->total_tracks - 1]->stsz_sample_count; i++)
        {
            f->track[f->total_tracks - 1]->stsz_table[i] = mp4ff_read_int32(f);
        }
    }

    return 0;
}

static int32_t mp4ff_read_esds(mp4ff_t *f)
{
    uint8_t tag;
    uint32_t temp;

    mp4ff_read_char(f); /* version */
    mp4ff_read_int24(f); /* flags */

    /* get and verify ES_DescrTag */
    tag = mp4ff_read_char(f);
    if (tag == 0x03)
    {
        /* read length */
        if (mp4ff_read_mp4_descr_length(f) < 5 + 15)
        {
            return 1;
        }
        /* skip 3 bytes */
        mp4ff_read_int24(f);
    } else {
        /* skip 2 bytes */
        mp4ff_read_int16(f);
    }

    /* get and verify DecoderConfigDescrTab */
    if (mp4ff_read_char(f) != 0x04)
    {
        return 1;
    }

    /* read length */
    temp = mp4ff_read_mp4_descr_length(f);
    if (temp < 13) return 1;

    f->track[f->total_tracks - 1]->audioType = mp4ff_read_char(f);
    mp4ff_read_int32(f);//0x15000414 ????
    f->track[f->total_tracks - 1]->maxBitrate = mp4ff_read_int32(f);
    f->track[f->total_tracks - 1]->avgBitrate = mp4ff_read_int32(f);

    /* get and verify DecSpecificInfoTag */
    if (mp4ff_read_char(f) != 0x05)
    {
        return 1;
    }

    /* read length */
    f->track[f->total_tracks - 1]->decoderConfigLen = mp4ff_read_mp4_descr_length(f);

    if (f->track[f->total_tracks - 1]->decoderConfig)
        free(f->track[f->total_tracks - 1]->decoderConfig);
    f->track[f->total_tracks - 1]->decoderConfig = (uint8_t *)malloc(f->track[f->total_tracks - 1]->decoderConfigLen);
    if (f->track[f->total_tracks - 1]->decoderConfig)
    {
        mp4ff_read_data(f, (int8_t *)f->track[f->total_tracks - 1]->decoderConfig, f->track[f->total_tracks - 1]->decoderConfigLen);
    } else {
        f->track[f->total_tracks - 1]->decoderConfigLen = 0;
    }

    /* will skip the remainder of the atom */
    return 0;
}

static int32_t mp4ff_read_mp4a(mp4ff_t *f)
{
    uint64_t size;
    int32_t i;
    uint8_t atom_type = 0;
    uint8_t header_size = 0;

    for (i = 0; i < 6; i++)
    {
        mp4ff_read_char(f); /* reserved */
    }
    /* data_reference_index */ mp4ff_read_int16(f);

    mp4ff_read_int32(f); /* reserved */
    mp4ff_read_int32(f); /* reserved */

    f->track[f->total_tracks - 1]->channelCount = mp4ff_read_int16(f);
    f->track[f->total_tracks - 1]->sampleSize = mp4ff_read_int16(f);

    mp4ff_read_int16(f);
    mp4ff_read_int16(f);

    f->track[f->total_tracks - 1]->sampleRate = mp4ff_read_int16(f);

    mp4ff_read_int16(f);

    size = mp4ff_atom_read_header(f, &atom_type, &header_size);
    if (atom_type == ATOM_ESDS)
    {
        mp4ff_read_esds(f);
    }

    return 0;
}

static int32_t mp4ff_read_stsd(mp4ff_t *f)
{
    int32_t i;
    uint8_t header_size = 0;

    mp4ff_read_char(f); /* version */
    mp4ff_read_int24(f); /* flags */

    f->track[f->total_tracks - 1]->stsd_entry_count = mp4ff_read_int32(f);

    for (i = 0; i < f->track[f->total_tracks - 1]->stsd_entry_count; i++)
    {
        uint64_t skip = mp4ff_position(f);
        uint64_t size;
        uint8_t atom_type = 0;
        size = mp4ff_atom_read_header(f, &atom_type, &header_size);
        skip += size;

        if (atom_type == ATOM_MP4A)
        {
            f->track[f->total_tracks - 1]->type = TRACK_AUDIO;
            mp4ff_read_mp4a(f);
        } else if (atom_type == ATOM_MP4V) {
            f->track[f->total_tracks - 1]->type = TRACK_VIDEO;
        } else if (atom_type == ATOM_MP4S) {
            f->track[f->total_tracks - 1]->type = TRACK_SYSTEM;
        } else {
            f->track[f->total_tracks - 1]->type = TRACK_UNKNOWN;
        }

        mp4ff_set_position(f, skip);
    }

    return 0;
}

static int32_t mp4ff_read_stsc(mp4ff_t *f)
{
    int32_t i;

    mp4ff_read_char(f); /* version */
    mp4ff_read_int24(f); /* flags */
    f->track[f->total_tracks - 1]->stsc_entry_count = mp4ff_read_int32(f);

    f->track[f->total_tracks - 1]->stsc_first_chunk =
        (int32_t*)malloc(f->track[f->total_tracks - 1]->stsc_entry_count*sizeof(int32_t));
    f->track[f->total_tracks - 1]->stsc_samples_per_chunk =
        (int32_t*)malloc(f->track[f->total_tracks - 1]->stsc_entry_count*sizeof(int32_t));
    f->track[f->total_tracks - 1]->stsc_sample_desc_index =
        (int32_t*)malloc(f->track[f->total_tracks - 1]->stsc_entry_count*sizeof(int32_t));

    for (i = 0; i < f->track[f->total_tracks - 1]->stsc_entry_count; i++)
    {
        f->track[f->total_tracks - 1]->stsc_first_chunk[i] = mp4ff_read_int32(f);
        f->track[f->total_tracks - 1]->stsc_samples_per_chunk[i] = mp4ff_read_int32(f);
        f->track[f->total_tracks - 1]->stsc_sample_desc_index[i] = mp4ff_read_int32(f);
    }

    return 0;
}

static int32_t mp4ff_read_stco(mp4ff_t *f)
{
    int32_t i;

    mp4ff_read_char(f); /* version */
    mp4ff_read_int24(f); /* flags */
    f->track[f->total_tracks - 1]->stco_entry_count = mp4ff_read_int32(f);

    f->track[f->total_tracks - 1]->stco_chunk_offset =
        (int32_t*)malloc(f->track[f->total_tracks - 1]->stco_entry_count*sizeof(int32_t));

    for (i = 0; i < f->track[f->total_tracks - 1]->stco_entry_count; i++)
    {
        f->track[f->total_tracks - 1]->stco_chunk_offset[i] = mp4ff_read_int32(f);
    }

    return 0;
}

static int32_t mp4ff_read_ctts(mp4ff_t *f)
{
    int32_t i;
    mp4ff_track_t * p_track = f->track[f->total_tracks - 1];

    if (p_track->ctts_entry_count) return 0;

    mp4ff_read_char(f); /* version */
    mp4ff_read_int24(f); /* flags */
    p_track->ctts_entry_count = mp4ff_read_int32(f);

    p_track->ctts_sample_count = (int32_t*)malloc(p_track->ctts_entry_count * sizeof(int32_t));
    p_track->ctts_sample_offset = (int32_t*)malloc(p_track->ctts_entry_count * sizeof(int32_t));

    if (p_track->ctts_sample_count == 0 || p_track->ctts_sample_offset == 0)
    {
        if (p_track->ctts_sample_count) {free(p_track->ctts_sample_count);p_track->ctts_sample_count=0;}
        if (p_track->ctts_sample_offset) {free(p_track->ctts_sample_offset);p_track->ctts_sample_offset=0;}
        p_track->ctts_entry_count = 0;
        return 0;
    }
    else
    {
        for (i = 0; i < f->track[f->total_tracks - 1]->ctts_entry_count; i++)
        {
            p_track->ctts_sample_count[i] = mp4ff_read_int32(f);
            p_track->ctts_sample_offset[i] = mp4ff_read_int32(f);
        }
        return 1;
    }
}

int32_t mp4ff_read_stts(mp4ff_t *f)
{
    int32_t i;
    mp4ff_track_t * p_track = f->track[f->total_tracks - 1];

    if (p_track->stts_entry_count) return 0;

    mp4ff_read_char(f); /* version */
    mp4ff_read_int24(f); /* flags */
    p_track->stts_entry_count = mp4ff_read_int32(f);

    p_track->stts_sample_count = (int32_t*)malloc(p_track->stts_entry_count * sizeof(int32_t));
    p_track->stts_sample_delta = (int32_t*)malloc(p_track->stts_entry_count * sizeof(int32_t));

    if (p_track->stts_sample_count == 0 || p_track->stts_sample_delta == 0)
    {
        if (p_track->stts_sample_count) {free(p_track->stts_sample_count);p_track->stts_sample_count=0;}
        if (p_track->stts_sample_delta) {free(p_track->stts_sample_delta);p_track->stts_sample_delta=0;}
        p_track->stts_entry_count = 0;
        return 0;
    }
    else
    {
        for (i = 0; i < f->track[f->total_tracks - 1]->stts_entry_count; i++)
        {
            p_track->stts_sample_count[i] = mp4ff_read_int32(f);
            p_track->stts_sample_delta[i] = mp4ff_read_int32(f);
        }
        return 1;
    }
}

static int32_t mp4ff_read_mvhd(mp4ff_t *f)
{
    int32_t i;

    mp4ff_read_char(f); /* version */
    mp4ff_read_int24(f); /* flags */
    /* creation_time */ mp4ff_read_int32(f);
    /* modification_time */ mp4ff_read_int32(f);
    f->time_scale = mp4ff_read_int32(f);
    f->duration = mp4ff_read_int32(f);
    /* preferred_rate */ mp4ff_read_int32(f); /*mp4ff_read_fixed32(f);*/
    /* preferred_volume */ mp4ff_read_int16(f); /*mp4ff_read_fixed16(f);*/
    for (i = 0; i < 10; i++)
    {
        /* reserved */ mp4ff_read_char(f);
    }
    for (i = 0; i < 9; i++)
    {
        mp4ff_read_int32(f); /* matrix */
    }
    /* preview_time */ mp4ff_read_int32(f);
    /* preview_duration */ mp4ff_read_int32(f);
    /* poster_time */ mp4ff_read_int32(f);
    /* selection_time */ mp4ff_read_int32(f);
    /* selection_duration */ mp4ff_read_int32(f);
    /* current_time */ mp4ff_read_int32(f);
    /* next_track_id */ mp4ff_read_int32(f);

    return 0;
}

#if 0
static int32_t mp4ff_read_tkhd(mp4ff_t *f)
{
    uint8_t version;
    uint32_t flags;
    version = mp4ff_read_char(f); /* version */
    flags = mp4ff_read_int24(f); /* flags */
    if (version==1)
    {
        mp4ff_read_int64(f);//creation-time
        mp4ff_read_int64(f);//modification-time
        mp4ff_read_int32(f);//track-id
        mp4ff_read_int32(f);//reserved
        f->track[f->total_tracks - 1]->duration = mp4ff_read_int64(f);//duration
    }
    else //version == 0
    {
        mp4ff_read_int32(f);//creation-time
        mp4ff_read_int32(f);//modification-time
        mp4ff_read_int32(f);//track-id
        mp4ff_read_int32(f);//reserved
        f->track[f->total_tracks - 1]->duration = mp4ff_read_int32(f);//duration
        if (f->track[f->total_tracks - 1]->duration == 0xFFFFFFFF)
            f->track[f->total_tracks - 1]->duration = 0xFFFFFFFFFFFFFFFF;

    }
    mp4ff_read_int32(f);//reserved
    mp4ff_read_int32(f);//reserved
    mp4ff_read_int16(f);//layer
    mp4ff_read_int16(f);//pre-defined
    mp4ff_read_int16(f);//volume
    mp4ff_read_int16(f);//reserved

    //matrix
    mp4ff_read_int32(f); mp4ff_read_int32(f); mp4ff_read_int32(f);
    mp4ff_read_int32(f); mp4ff_read_int32(f); mp4ff_read_int32(f);
    mp4ff_read_int32(f); mp4ff_read_int32(f); mp4ff_read_int32(f);
    mp4ff_read_int32(f);//width
    mp4ff_read_int32(f);//height
    return 1;
}
#endif

static int32_t mp4ff_read_mdhd(mp4ff_t *f)
{
    uint32_t version;

    version = mp4ff_read_int32(f);
    if (version==1)
    {
        mp4ff_read_int64(f);//creation-time
        mp4ff_read_int64(f);//modification-time
        f->track[f->total_tracks - 1]->timeScale = mp4ff_read_int32(f);//timescale
        f->track[f->total_tracks - 1]->duration = mp4ff_read_int64(f);//duration
    }
    else //version == 0
    {
        uint32_t temp;

        mp4ff_read_int32(f);//creation-time
        mp4ff_read_int32(f);//modification-time
        f->track[f->total_tracks - 1]->timeScale = mp4ff_read_int32(f);//timescale
        temp = mp4ff_read_int32(f);
        f->track[f->total_tracks - 1]->duration = (temp == (uint32_t)(-1)) ? (uint64_t)(-1) : (uint64_t)(temp);
    }
    mp4ff_read_int16(f);
    mp4ff_read_int16(f);
    return 1;
}
#ifdef USE_TAGGING
static int32_t mp4ff_read_meta(mp4ff_t *f, const uint64_t size)
{
    uint64_t subsize, sumsize = 0;
    uint8_t atom_type;
    uint8_t header_size = 0;

    mp4ff_read_char(f); /* version */
    mp4ff_read_int24(f); /* flags */

    while (sumsize < (size-(header_size+4)))
    {
        subsize = mp4ff_atom_read_header(f, &atom_type, &header_size);
        if (subsize <= header_size+4)
            return 1;
        if (atom_type == ATOM_ILST)
        {
            mp4ff_parse_metadata(f, (uint32_t)(subsize-(header_size+4)));
        } else {
            mp4ff_set_position(f, mp4ff_position(f)+subsize-header_size);
        }
        sumsize += subsize;
    }

    return 0;
}
#endif

int32_t mp4ff_atom_read(mp4ff_t *f, const int32_t size, const uint8_t atom_type)
{
    uint64_t dest_position = mp4ff_position(f)+size-8;
    if (atom_type == ATOM_STSZ)
    {
        /* sample size box */
        mp4ff_read_stsz(f);
    } else if (atom_type == ATOM_STTS) {
        /* time to sample box */
        mp4ff_read_stts(f);
    } else if (atom_type == ATOM_CTTS) {
        /* composition offset box */
        mp4ff_read_ctts(f);
    } else if (atom_type == ATOM_STSC) {
        /* sample to chunk box */
        mp4ff_read_stsc(f);
    } else if (atom_type == ATOM_STCO) {
        /* chunk offset box */
        mp4ff_read_stco(f);
    } else if (atom_type == ATOM_STSD) {
        /* sample description box */
        mp4ff_read_stsd(f);
    } else if (atom_type == ATOM_MVHD) {
        /* movie header box */
        mp4ff_read_mvhd(f);
    } else if (atom_type == ATOM_MDHD) {
        /* track header */
        mp4ff_read_mdhd(f);
#ifdef USE_TAGGING
    } else if (atom_type == ATOM_META) {
        /* iTunes Metadata box */
        mp4ff_read_meta(f, size);
#endif
    }

    mp4ff_set_position(f, dest_position);


    return 0;
}
