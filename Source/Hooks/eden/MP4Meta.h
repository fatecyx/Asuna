#ifndef _MP4META_H_
#define _MP4META_H_

#include "my_common.h"
#include "FileMem.h"
#include "Mem.h"

typedef struct
{
    u32 size;
    u32 tag;
} TMP4Atom;

typedef struct
{
    u8 *name;
    u8 *data;
} TMetaData;

class CMP4Meta
{
public:
    enum ErrorCode 
    {
        ERR_NORMAL, 
        ERR_SUCCESS, 
        ERR_FTYP_NOT_FOUND, 
        ERR_MOOV_NOT_FOUND, 
        ERR_UDTA_NOT_FOUND, 
        ERR_META_NOT_FOUND, 
        ERR_ILST_NOT_FOUND, 
    };

    CMP4Meta();
    ~CMP4Meta();

    Long  Open(Char *filename, u32 dwSize);
    Long  GetMeta(TMetaData **ppMetaData, u32 *pMetaCount);
    Void  FreeMeta(TMetaData *pMetaData);
    Void  Close();
    Char* GetErrorString(Long r);

protected:
    Void Free();
    Bool FindAtom(u32 tag, u32 section, TMP4Atom *pAtom, Bool bSeekToEndOfBlock);
    Bool ReadAtom(TMP4Atom *pAtom, Bool bSeekToEndOfBlock);
    Bool SkipStream();
    ForceInline u32 Bswap(u32 v);

protected:
    u8       *m_pbMeta;
    u32       m_metaSize;
    CMem      mem;
    CFileMem  file;
};

#endif /* _MP4META_H_ */