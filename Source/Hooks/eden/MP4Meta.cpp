#include "MP4Meta.h"

CMP4Meta::CMP4Meta()
{
    m_pbMeta = NULL;
}

CMP4Meta::~CMP4Meta()
{
    Free();
}

Void CMP4Meta::FreeMeta(TMetaData *pMetaData)
{
    if (pMetaData)
        mem.Free(pMetaData);
}

Void CMP4Meta::Close()
{
    file.Close();
    Free();
}

Void CMP4Meta::Free()
{
    if (m_pbMeta)
    {
        mem.Free(m_pbMeta);
        m_pbMeta = NULL;
    }
}

ForceInline u32 CMP4Meta::Bswap(u32 v)
{
    __asm
    {
        mov eax, v;
        bswap eax;
    }
}

Long CMP4Meta::Open(Char *filename, u32 dwSize)
{
    Close();

    if (file.Open(filename, dwSize) == False)
        return ERR_NORMAL;

    u32 size;
    TMP4Atom atom;

    size = file.GetSize();
    if (FindAtom(TAG4('ftyp'), size, &atom, True) == False)
        return -ERR_FTYP_NOT_FOUND;
    if (FindAtom(TAG4('moov'), size - file.GetCurrentPos(), &atom, False) == False)
        return -ERR_MOOV_NOT_FOUND;

    if (FindAtom(TAG4('udta'), atom.size, &atom, False) == False)
        return -ERR_UDTA_NOT_FOUND;

    if (FindAtom(TAG4('meta'), atom.size, &atom, False) == False)
        return -ERR_UDTA_NOT_FOUND;

    file.Seek(file.Seek_Cur, 4);
    size = atom.size - 0xC;

    if (FindAtom(TAG4('ilst'), size, &atom, False) == False)
        return -ERR_ILST_NOT_FOUND;

    m_metaSize = atom.size - sizeof(atom);
    m_pbMeta = (u8 *)mem.Alloc(m_metaSize);
    if (m_pbMeta == NULL)
        return ERR_NORMAL;

    return file.Read(m_pbMeta, m_metaSize) ? ERR_SUCCESS : ERR_NORMAL;
}

Long CMP4Meta::GetMeta(TMetaData **ppMetaData, u32 *pMetaCount)
{
    u8 *pMeta, *pEnd;
    u32 count;
    TMetaData *pMetaData;

    pMeta = m_pbMeta;
    pEnd  = m_pbMeta + m_metaSize;

    count = 0;
    while (pMeta < pEnd)
    {
        ++count;
        pMeta += Bswap(*(pu32)pMeta);
    }

    *pMetaCount = count;
    pMetaData = (TMetaData *)mem.Alloc(count * sizeof(*pMetaData));
    *ppMetaData = pMetaData;
    if (pMetaData == NULL)
        return ERR_NORMAL;

    pMeta = m_pbMeta;

    s32 len, size;

    for (u32 i = 0; i != count; ++i)
    {
        pMetaData[i].data = 0;
        pMetaData[i].name = 0;

        size = Bswap(*(pu32)pMeta) - 8;
        pMeta += 4;
        switch (*(pu32)pMeta)
        {
            case 0x6F6F74A9:    // tool
                pMetaData[i].name = pMeta;
                *(pu32)pMeta = TAG4('tool');
                pMeta += 4;
                while (size > 0)
                {
                    size -= Bswap(*(pu32)pMeta);
                    pMeta += 4;
                    if (*(pu32)pMeta == TAG4('data'))
                        pMetaData[i].data = pMeta + Bswap(*(pu32)(pMeta + 4)) * 4 + 8;
                }
                break;

            case '----':
                pMeta += 4;
                do
                {
                    len = Bswap(*(pu32)pMeta);
                    size -= len;
                    pMeta[0] = 0;
                    pMeta += 4;
                    switch (*(pu32)pMeta)
                    {
                    case TAG4('name'):
                        pMetaData[i].name = pMeta + 8;
                        break;
                        
                    case TAG4('data'):
                        pMetaData[i].data = pMeta + Bswap(*(pu32)(pMeta + 4)) * 4 + 8;
                    }
                    
                    pMeta += len - 4;
                } while (size > 0);
        }
    }

    return ERR_SUCCESS;
}

Char* CMP4Meta::GetErrorString(Long r)
{
    static Char *err[] = 
    {
        "Normal error", 
        "No error", 
        "Can't find ftyp atom", 
        "Can't find moov atom", 
        "Can't find udta atom", 
        "Can't find meta atom", 
        "Can't find ilst atom", 
    };

    r = -r;
    if (r > countof(err) || r < 0)
        return NULL;

    return err[r];
}

Bool CMP4Meta::FindAtom(u32 tag, u32 section, TMP4Atom *pAtom, Bool bSeekToEndOfBlock)
{
    u32  pos, pos1;
    Bool bFound;

    pos = file.GetCurrentPos();
    section += pos;
    bFound = False;

    while ((pos1 = file.GetCurrentPos()) < section && ReadAtom(pAtom, True))
    {
        if (pAtom->tag == tag)
        {
            pos = pos1;
            bFound = True;
            break;
        }
    }

    if (bSeekToEndOfBlock == False)
        file.Seek(file.Seek_Beg, pos + sizeof(*pAtom));

    return bFound;
}

Bool CMP4Meta::ReadAtom(TMP4Atom *pAtom, Bool bSeekToEndOfBlock)
{
    if (pAtom == NULL)
        return False;

    if (file.Read(pAtom, sizeof(*pAtom)) == False)
        return False;

    pAtom->size = Bswap(pAtom->size);
    if (bSeekToEndOfBlock && file.Seek(file.Seek_Cur, pAtom->size - sizeof(*pAtom)) == False)
        return False;

    return True;
}