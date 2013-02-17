#include "neko.h"
#include "my_api.h"
#include "crt_h.h"
#include "my_crt.h"
#include "FileDisk.cpp"
#include "Mem.cpp"
#pragma comment(lib, "ntdll.lib")

CNekoPack::CNekoPack()
{
    m_neko.pDir = NULL;
}

CNekoPack::~CNekoPack()
{
    Destroy();
}

Void CNekoPack::Destroy()
{
    if (m_neko.pDir == NULL)
        return;

    for (UInt32 i = 0; i != m_neko.dirNum; ++i)
    {
        m.Free(m_neko.pDir[i].pIndex);
    }

    m.SafeFree(&m_neko.pDir);
}

Bool CNekoPack::CheckParity(UInt32 hash, UInt32 size)
{
    UInt32 v;

    hash ^= size;
    hash += 0x5D588B65;
    hash ^= size;
    hash += 0xCA62C1D6;
    v = hash;
    hash ^= size;
    hash += 0x8F1BBCDC;
    v >>= 0x1B;
    hash ^= size;
    hash += 0x6C078965;

    return _rotl(hash, v);
}

Bool CNekoPack::GetKey(PULARGE_INTEGER pKey, UInt32 seed)
{
    UInt32 v;

    v = seed;
    seed += 0x5D588B65;
    seed ^= v;
    v += 0xCA62C1D6;
    v ^= seed;
    seed += 0x8F1BBCDC;
    seed ^= v;
    v += 0x6C078965;
    v ^= seed;
    pKey->LowPart  = seed;
    pKey->HighPart = v;

    return True;
}

Bool CNekoPack::Decrypt(LPVoid lpInput, LPVoid lpOutput, UInt32 uSize, UInt32 seed)
{
    ULARGE_INTEGER key;

    GetKey(&key, seed);
    return Decrypt(lpInput, lpOutput, uSize, &key);
}

Bool CNekoPack::Decrypt(LPVoid lpInput, LPVoid lpOutput, UInt32 uSize, PULARGE_INTEGER pKey)
{
    PByte pbInput = (PByte)lpInput, pbOutput = (PByte)lpOutput;
    PByte pbEnd = pbInput + uSize;
    ULARGE_INTEGER key = *pKey;

    __asm
    {
        mov   eax, pKey;
        mov   ecx, uSize;
        movq  mm1, qword ptr [eax];
        mov   esi, pbInput;
        mov   edi, pbOutput;
DECRYPT:
        movq  mm0, [esi];
        pxor  mm0, mm1;
        paddw mm1, mm0;
        movq  [edi], mm0;
        add   esi, 8;
        add   edi, 8;
        sub   ecx, 8;
        jg    DECRYPT;
        movq  [eax], mm1;
        emms;
    }

    return True;
/*
    while (pbInput < pbEnd)
    {
        *(PUInt64)pbOutput = *(PUInt64)pbInput ^ key.QuadPart;

        PUInt16 ka = (PUInt16)&key;
        PUInt16 pa = (PUInt16)pbOutput;
        ka[0] += pa[0];
        ka[1] += pa[1];
        ka[2] += pa[2];
        ka[3] += pa[3];

        pbInput  += sizeof(UInt64);
        pbOutput += sizeof(UInt64);
    }
    *pKey = key;

    return True;
*/
}

UInt32 CNekoPack::HashName(PChar szFile, UInt32 seed)
{
    UInt32 v;
    Char c;
    static Byte dict[] =
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x38, 0x2F, 0x33, 0x3C, 0x40, 0x3B, 0x2A, 0x2E,
        0x31, 0x30, 0x26, 0x44, 0x35, 0x28, 0x3E, 0x12, 0x02, 0x22,
        0x06, 0x20, 0x1A, 0x1C, 0x0F, 0x11, 0x18, 0x17, 0x42, 0x2B,
        0x3A, 0x37, 0x34, 0x0C, 0x41, 0x08, 0x1D, 0x07, 0x15, 0x21,
        0x05, 0x1E, 0x0A, 0x14, 0x0E, 0x10, 0x09, 0x27, 0x1F, 0x0B,
        0x23, 0x16, 0x0D, 0x01, 0x25, 0x04, 0x1B, 0x03, 0x13, 0x24,
        0x19, 0x2D, 0x12, 0x29, 0x32, 0x3F, 0x3D, 0x08, 0x1D, 0x07,
        0x15, 0x21, 0x05, 0x1E, 0x0A, 0x14, 0x0E, 0x10, 0x09, 0x27,
        0x1F, 0x0B, 0x23, 0x16, 0x0D, 0x01, 0x25, 0x04, 0x1B, 0x03,
        0x13, 0x24, 0x19, 0x2C, 0x39, 0x43, 0x36, 0x00, 0x4B, 0xA9,
        0xA7, 0xAF, 0x50, 0x52, 0x91, 0x9F, 0x47, 0x6B, 0x96, 0xAB,
        0x87, 0xB5, 0x9B, 0xBB, 0x99, 0xA4, 0xBF, 0x5C, 0xC6, 0x9C,
        0xC2, 0xC4, 0xB6, 0x4F, 0xB8, 0xC1, 0x85, 0xA8, 0x51, 0x7E,
        0x5F, 0x82, 0x73, 0xC7, 0x90, 0x4E, 0x45, 0xA5, 0x7A, 0x63,
        0x70, 0xB3, 0x79, 0x83, 0x60, 0x55, 0x5B, 0x5E, 0x68, 0xBA,
        0x53, 0xA1, 0x67, 0x97, 0xAC, 0x71, 0x81, 0x59, 0x64, 0x7C,
        0x9D, 0xBD, 0x9D, 0xBD, 0x95, 0xA0, 0xB2, 0xC0, 0x6F, 0x6A,
        0x54, 0xB9, 0x6D, 0x88, 0x77, 0x48, 0x5D, 0x72, 0x49, 0x93,
        0x57, 0x65, 0xBE, 0x4A, 0x80, 0xA2, 0x5A, 0x98, 0xA6, 0x62,
        0x7F, 0x84, 0x75, 0xBC, 0xAD, 0xB1, 0x6E, 0x76, 0x8B, 0x9E,
        0x8C, 0x61, 0x69, 0x8D, 0xB4, 0x78, 0xAA, 0xAE, 0x8F, 0xC3,
        0x58, 0xC5, 0x74, 0xB7, 0x8E, 0x7D, 0x89, 0x8A, 0x56, 0x4D,
        0x86, 0x94, 0x9A, 0x4C, 0x92, 0xB0
    };

    while (c = *szFile++)
    {
        seed ^= dict[c];
        v = seed;
        v <<= 4;
        seed += v;
        v <<= 2;
        seed += v;
    }

    return seed;
}

Bool CNekoPack::Open(Char *szFile)
{
    Destroy();
    if (file.Open(szFile) == False)
        return False;

    Bool   ret;
    LPVoid lpBuffer;
    SNekoHeader h;
    SDataEntry entry;

    file.Read(&h, sizeof(h));
//    if (*(PUInt32)h.tag != TAG4('NEKO') || *(PUInt32)(h.tag + 4) != TAG4('PACK'))
//        return False;
    if (memcmp(&h.tag, "NEKOPACK", 8))
        return False;

    m_neko.hash = h.hash;
    m_neko.ver  = h.ver;
    file.Read(&entry, sizeof(entry));
    if (CheckParity(h.hash, entry.size) != entry.hash)
        return False;

    lpBuffer = m.Alloc(entry.size);
    file.Read(lpBuffer, entry.size);

    Decrypt((PByte)lpBuffer, (PByte)lpBuffer, entry.size, entry.hash);
    ret = InitIndex(lpBuffer, entry.size);

    m.Free(lpBuffer);

    return ret;
}

UInt32 CNekoPack::ExtractAll(PChar szOutPath /* = NULL */)
{
    UInt32 count, maxbuf;
    SDataEntry entry;
    CFileDisk f;
    LPVoid lpBuffer;
    Char *ext, szPath[MAX_PATH];
    extern Bool bCtrlC;

    if (szOutPath == NULL)
        szOutPath = ".";

    count = 0;
    maxbuf = 102400;
    lpBuffer = m.Alloc(maxbuf);
    for (UInt32 i = 0; i != m_neko.dirNum && !bCtrlC; ++i)
    {
        SNekoDirIndex  *pDir = m_neko.pDir + i;
        SNekoFileIndex *pFile;

        pFile = pDir->pIndex;
        for (UInt32 j = 0, k = pDir->filenum; j != k && !bCtrlC; ++j)
        {
            file.Seek(file.Seek_Beg, pFile->offset);
            file.Read(&entry, sizeof(entry));
            if (entry.size != pFile->size)
                continue;

            if (maxbuf < entry.size)
            {
                maxbuf = entry.size;
                lpBuffer = m.ReAlloc(maxbuf, lpBuffer);
            }
            file.Read(lpBuffer, entry.size);
            Decrypt((PByte)lpBuffer, (PByte)lpBuffer, entry.size, entry.hash);

            ext = GuessExt(lpBuffer);

            sprintf(szPath, "%s\\%08X_%08X\\%08X_%08X.%s", szOutPath, i, pDir->hash, j, pFile->hash, ext);
            ext = findname(szPath) - 1;
            *ext = 0;
            MyCreateDirectoryA(szPath);
            *ext = '\\';

            f.Open(szPath, f.W, f.N);
            f.Write(lpBuffer, entry.size);
            ++pFile;
        }
    }

    m.Free(lpBuffer);

    return count;
}

PChar CNekoPack::GuessExt(LPVoid lpBuffer)
{
    PByte pbBuffer = (PByte)lpBuffer;
    PUInt32 puBuffer = (PUInt32)lpBuffer;
    UInt32  v;

    v = *puBuffer;
    if (v == TAG4('OggS'))
        return "ogg";
    if ((v >> 8) == TAG3('PNG'))
        return "png";
    if ((v >> 8) == TAG3('MNG'))
        return "mng";

    return "txt";
}

UInt32 CNekoPack::ExtractFile(PChar szFile, PChar szOutPath /* = NULL */)
{
    UInt32 uSize;
    Char szPath[MAX_PATH];
    PChar pFileName;
    LPVoid lpBuffer;
    SDataEntry      entry;
    SNekoDirIndex  *pDir;
    SNekoFileIndex *pFile;

    pFileName = strrchr(szFile, '\\');
    if (pFileName == NULL)
        return 0;

    *pFileName = 0;
    sprintf(szPath, "%s\\%s\\", szOutPath ? szOutPath : ".", szFile);
    pDir = FindDir(szFile);
    *pFileName = '\\';
    if (pDir == NULL)
        return 0;

    pFile = FindFile(pFileName + 1, pDir);
    if (pFile == NULL)
        return 0;

    uSize = pFile->size;
    file.Seek(file.Seek_Beg, pFile->offset);
    file.Read(&entry, sizeof(entry));
    if (entry.size != uSize)
        return 0;

    lpBuffer = m.Alloc(uSize);
    file.Read(lpBuffer, uSize);

    Decrypt((PByte)lpBuffer, (PByte)lpBuffer, entry.size, entry.hash);

    MyCreateDirectoryA(szPath);
    strcat(szPath, pFileName + 1);

    CFileDisk f;

    if (f.Open(szPath, f.W, f.N))
    {
        f.Write(lpBuffer, uSize);
    }

    m.Free(lpBuffer);

    return uSize;
}

Bool CNekoPack::InitIndex(LPVoid lpBuffer, UInt32 uSize)
{
    UInt32 offset;
    SDataEntry *pEntry, *pEnd;

    pEntry = (SDataEntry *)lpBuffer;
    pEnd   = (SDataEntry *)((PByte)lpBuffer + uSize);

    m_neko.dirNum = 0;
    for (SDataEntry *p = pEntry; p < pEnd; )
    {
        m_neko.dirNum++;
        p += p->size + 1;
    }

    m_neko.pDir = (SNekoDirIndex *)m.Alloc(m_neko.dirNum * sizeof(*m_neko.pDir));
    if (m_neko.pDir == NULL)
        return False;

    offset = uSize + sizeof(SNekoHeader) + sizeof(SDataEntry);
    for (UInt32 i = 0; i != m_neko.dirNum; ++i)
    {
        SNekoFileIndex *pFile;
        SNekoDirIndex *pDir = m_neko.pDir + i;

        pDir->filenum = pEntry->size;
        pDir->hash = pEntry->hash;
        pDir->pIndex = (SNekoFileIndex *)m.Alloc(pDir->filenum * sizeof(*pDir->pIndex));
        if (pDir == NULL)
            return False;

        ++pEntry;
        pFile = pDir->pIndex;
        for (UInt32 j = 0, k = pDir->filenum; j != k; ++j)
        {
            pFile->hash = pEntry->hash;
            pFile->size = pEntry->size;
            pFile->offset = offset;
            offset += pFile->size + sizeof(SDataEntry);
            ++pEntry;
            ++pFile;
        }
    }

    return True;
}

SNekoDirIndex* CNekoPack::FindDir(PChar szFile)
{
    UInt32 hash;
    SNekoDirIndex *pIndex;

    hash = HashName(szFile, m_neko.hash);

    pIndex = m_neko.pDir;
    for (UInt32 i = 0; i != m_neko.dirNum; ++i)
    {
        if (pIndex->hash == hash)
            return pIndex;
        ++pIndex;
    }

    return NULL;
}

SNekoFileIndex* CNekoPack::FindFile(PChar szFile, SNekoDirIndex *pDirEntry)
{
    UInt32 hash = HashName(szFile, m_neko.hash);
    SNekoFileIndex *pIndex;

    pIndex = pDirEntry->pIndex;
    for (UInt32 i = 0, j = pDirEntry->filenum; i != j; ++i)
    {
        if (pIndex->hash == hash)
            return pIndex;
        ++pIndex;
    }

    return NULL;
}