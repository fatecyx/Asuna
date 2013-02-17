#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "crt_h.h"
#include "my_crt.h"
#include "my_mem.h"
#include "../Sharu.h"

static Char tag[][16] =
{
    "abmp10",
    "abmp11",
    "abmp12",
};
static Char abdata[][16] =
{
    "abdata10",
    "abdata11",
    "abdata12",
};
static Char abimage[][16] =
{
    "abimage10",
    "abimage11",
    "abimage12",
};
static Char abimgdat[][16] =
{
    "abimgdat10",
    "abimgdat11",
    "abimgdat12",
};
static Char absound[][16] =
{
    "absound10",
    "absound11",
    "absound12",
};
static Char absnddat[][16] =
{
    "absnddat10",
    "absnddat11",
    "absnddat12",
};

static Char header[16] = "QLIE B FileList";
static Char bheader[16] = "abmp12";

enum EFILETYPE { SOUND, IMAGE };

UInt32 Uncompress(LPVoid lpInputBuffer, Int32 BufferSize, LPVoid lpOutputBuffer);
UInt32 GetDataType(LPVoid lpBuffer);

PWChar GetSoundExtension(UInt32 Type)
{
    PWChar ext;

    switch (Type)
    {
        case 0:
            ext = L".wav";
            break;

        case 1:
            ext = L".ogg";
            break;

        default:
            ext = L"";
    }

    return ext;
}

PWChar GetImageExtension(UInt32 Type)
{
    PWChar ext;
    static WChar *szExtension[] =
    {
        L".bmp", L".jpg", L".png", L".png",
        L".m", L".argb", L".b",
    };

    return Type < countof(szExtension) ? szExtension[Type] : L"";

    switch (Type)
    {
        case 0:
            ext = L".bmp";
            break;

        case 1:
            ext = L".jpg";
            break;

        case 2:
        case 3:
            ext = L".png";
            break;

        case 4:
            ext = L".m";
            break;

        case 5:
            ext = L".argb";
            break;

        case 6:
            ext = L".b";
            break;

        default:
            ext = L"";
    }

    return ext;
}

NoInline UInt32 Split(LPVoid lpBuffer, UInt32 BufferSize, PWChar pszInputFile)
{

    PByte  pbBuffer, pbEnd;
    UInt32 ImageCount;
    PChar  pFileName;
    WChar  *p, *pName, szPath[MAX_PATH], szSubFile[MAX_PATH];
    FILE  *fp, *fbin;

    pbBuffer = (PByte)lpBuffer;
    pbEnd    = pbBuffer + BufferSize;

    if (memcmp(pbBuffer, tag[2], sizeof(*tag)))
    {
        return -1;
    }

    pbBuffer += sizeof(*tag);

    ImageCount = 0;
    wcscpy(szSubFile, pszInputFile);
    chextw(szSubFile, L".bin");
    fbin = _wfopen(szSubFile, L"wb+");
    if (!fbin)
    {
        _wperror(szSubFile);
        return 0;
    }

    fwrite(header, sizeof(header), 1, fbin);

    wcscpy(szPath, pszInputFile);
    pName = findnamew(szPath);
    p = wcslen(pName) + pName;
    *p++ = '_';
    while (pbBuffer < pbEnd)
    {
        UInt32 FileType, SubFile, Type, NameLen, DataLen, CodePage;

        if (!memcmp(pbBuffer, abdata[2], sizeof(*abdata)))
        {
            fwrite(pbBuffer, sizeof(*abdata), 1, fbin);
            pbBuffer += sizeof(*abdata);
            DataLen = *(PUInt32)pbBuffer;
            pbBuffer += 4;

            swprintf(p, L"%u.dat", ImageCount);
            NameLen = wcslen(pName) * 2;
            fwrite(&NameLen, 2, 1, fbin);
            fwrite(pName, NameLen, 1, fbin);

            fp = _wfopen(szPath, L"wb");
            if (fp)
            {
                ++ImageCount;
                fwrite(pbBuffer, DataLen, 1, fp);
                fclose(fp);
            }

            pbBuffer += DataLen;
            continue;
        }
        else if (!memcmp(pbBuffer, absound[0], sizeof(*absound)))
        {
            fwrite(pbBuffer, sizeof(*absound), 1, fbin);
            pbBuffer += sizeof(*absound);
            FileType = SOUND;
        }
        else if (!memcmp(pbBuffer, abimage[0], sizeof(*abimage)))
        {
            fwrite(pbBuffer, sizeof(*abimage), 1, fbin);
            pbBuffer += sizeof(*abimage);
            FileType = IMAGE;
        }
        else
        {
            ImageCount = -1;
            goto err;
        }

        SubFile = *pbBuffer++;
        fwrite(&SubFile, 1, 1, fbin);
        for (UInt32 i = 0; i != SubFile; ++i)
        {
            if (memcmp(pbBuffer, absnddat[1], sizeof(*absnddat)) &&
                memcmp(pbBuffer, abimgdat[1], sizeof(*abimgdat)) )
            {
                ImageCount = -1;
                goto err;
            }

            fwrite(pbBuffer, sizeof(*absnddat), 1, fbin);
            pbBuffer += sizeof(*absnddat);
            pFileName = (PChar)pbBuffer + 2;
            NameLen = *(PUInt16)pbBuffer;
            pbBuffer += NameLen + 2;            // filename
            pbBuffer += *(PUInt16)pbBuffer + 2; // hash

            Type = *pbBuffer++;
            DataLen = *(PUInt32)pbBuffer;       // data
            pbBuffer += 4;

            if (DataLen == 0)
            {
                NameLen = 0;
                fwrite(&NameLen, 2, 1, fbin);
                continue;
            }

            CodePage = IsPureShiftJIS(pFileName, NameLen) ? CP_SHIFTJIS : CP_GB2312;
            NameLen = MultiByteToWideChar(CodePage, 0, pFileName, NameLen, szSubFile, countof(szSubFile));
            szSubFile[NameLen] = 0;
            swprintf(p, L"%s%s", szSubFile, FileType == IMAGE ? GetImageExtension(Type) : GetSoundExtension(Type));

            NameLen = wcslen(pName) * 2;
            fwrite(&NameLen, 2, 1, fbin);
            fwrite(pName, NameLen, 1, fbin);
            fp = _wfopen(szPath, L"wb");
            if (fp)
            {
                ++ImageCount;
                fwrite(pbBuffer, DataLen, 1, fp);
                fclose(fp);
            }

            pbBuffer += DataLen;
        }
    }

err:

    fclose(fbin);
    return ImageCount;
}

NoInline UInt32 Combine(LPVoid lpBuffer, UInt32 BufferSize, PWChar pszInputFile)
{
    FILE  *fp, *fin;
    UInt32 Size, Count, SkipLen;
    PByte  pbBuffer, pbEnd;
    WChar  *p, szPath[MAX_PATH];

    pbBuffer = (PByte)lpBuffer;
    pbEnd    = pbBuffer + BufferSize;

    wcscpy(szPath, pszInputFile);
    rmextw(szPath);
    SkipLen = wcslen(findnamew(szPath)) + 3;    // .b_
    wcscat(szPath, L".b");
    p = findnamew(szPath);
    fp = _wfopen(szPath, L"wb+");
    if (!fp)
    {
        _wperror(szPath);
        return 0;
    }

    *p = 0;
    if (szPath[0])
        SetCurrentDirectoryW(szPath);

    BufferSize = 1024 * 1024;
    lpBuffer = malloc(BufferSize);

    fwrite(bheader, sizeof(bheader), 1, fp);
    pbBuffer += sizeof(header);
    Count = 0;
    while (pbBuffer < pbEnd)
    {
        UInt32 NameLen;

        if (!memcmp(pbBuffer, abdata[2], sizeof(*abdata)))
        {
            fwrite(pbBuffer, sizeof(*abdata), 1, fp);
            pbBuffer += sizeof(*abdata);
            NameLen = *(PUInt16)pbBuffer;
            pbBuffer += 2;
            if (NameLen == 0)
            {
                fwrite(&NameLen, 4, 1, fp);
                continue;
            }

            memcpy(p, pbBuffer, NameLen);
            p[NameLen / 2] = 0;
            pbBuffer += NameLen;
            fin = _wfopen(szPath, L"rb");
            if (fin)
            {
                Size = fsize(fin);
                if (Size > BufferSize)
                {
                    BufferSize = Size;
                    lpBuffer = realloc(lpBuffer, BufferSize);
                }
                fread(lpBuffer, Size, 1, fin);
                fclose(fin);

                fwrite(&Size, 4, 1, fp);
                fwrite(lpBuffer, Size, 1, fp);
                ++Count;
            }
            else
            {
                _wperror(szPath);
                goto err;
            }
        }
        else if (!memcmp(pbBuffer, abimage[0], sizeof(*abimage)) ||
                 !memcmp(pbBuffer, absound[0], sizeof(*absound)) )
        {
            UInt32 SubFile;

            fwrite(pbBuffer, sizeof(*abimage), 1, fp);
            pbBuffer += sizeof(*abimage);
            SubFile = *pbBuffer++;

            fputc(SubFile, fp);
            while (SubFile-- && pbBuffer < pbEnd)
            {
                if (!memcmp(pbBuffer, abimgdat[1], sizeof(*abimgdat)) ||
                    !memcmp(pbBuffer, absnddat[1], sizeof(*absnddat)) )
                {
                    fwrite(pbBuffer, sizeof(*abimgdat), 1, fp);
                    pbBuffer += sizeof(*abimgdat);
                    NameLen = *(PUInt16)pbBuffer;
                    pbBuffer += 2;
                    if (NameLen == 0)
                    {
                        fwrite(&NameLen, 4, 1, fp);     // name len and hash len
                        fputc(1, fp);   // type
                        fwrite(&NameLen, 4, 1, fp);     // data size
                        continue;
                    }

                    memcpy(szPath, pbBuffer, NameLen);
                    NameLen /= 2;
                    szPath[NameLen] = 0;
                    fin = _wfopen(szPath, L"rb");
                    if (fin)
                    {
                        Size = fsize(fin);
                        if (Size > BufferSize)
                        {
                            BufferSize = Size;
                            lpBuffer = realloc(lpBuffer, BufferSize);
                        }
                        fread(lpBuffer, Size, 1, fin);
                        fclose(fin);
                    }
                    else
                    {
                        _wperror(szPath);
                        goto err;
                    }

                    NameLen -= SkipLen;
                    NameLen = WideCharToMultiByte(CP_SHIFTJIS, 0,
                        (PWChar)pbBuffer + SkipLen, NameLen, (LPSTR)szPath, sizeof(szPath), 0, 0);
                    ((LPSTR)szPath)[NameLen] = 0;
                    rmext((PChar)szPath);
                    NameLen = strlen((PChar)szPath);
                    fwrite(&NameLen, 2, 1, fp);
                    fwrite(szPath, NameLen, 1, fp);
                    NameLen = 0;
                    fwrite(&NameLen, 2, 1, fp);     // hash len
                    fputc(GetDataType(lpBuffer), fp);
                    fwrite(&Size, 4, 1, fp);
                    fwrite(lpBuffer, Size, 1, fp);
                    ++Count;

                    pbBuffer += *(PUInt16)(pbBuffer - 2);
                }
                else
                {
                    Count = -1;
                    goto err;
                }
            }
        }
        else
        {
            Count = -1;
            goto err;
        }
    }

err:

    fclose(fp);
    free(lpBuffer);

    return Count;
}

UInt32 GetDataType(LPVoid lpBuffer)
{
    UInt32 v = *(PUInt32)lpBuffer;

    if ((v & 0xDFDF) == TAG2('BM') || v == TAG4('RIFF') || (v & 0xFFFFFF) == TAG3('UCI'))
        return 0;
    else if ((v >> 8) == TAG3('PNG'))
        return 3;
    else if (v == TAG4('abmp'))     // b
        return 6;
    else if ((v & 0x00FFFFFF) == 0xFFD8FF || v == TAG4('OggS'))     // jpg ogg
        return 1;
    else
        return -1;
}

ForceInline Void main2(Int argc, WChar **argv)
{
    FILE *fp;
    LPVoid lpBuffer;
    UInt32 BufferSize, FileSize;

    BufferSize = 1024 * 1024;
    lpBuffer = malloc(BufferSize);

    _wsetlocale(LC_CTYPE, L"");
    for (Int i = 1; i != argc; ++i)
    {
        fp = _wfopen(*++argv, L"rb");
        if (!fp)
        {
            _wperror(*argv);
            continue;
        }

        FileSize = fsize(fp);
        if (FileSize > BufferSize)
        {
            BufferSize = FileSize;
            lpBuffer = realloc(lpBuffer, BufferSize);
        }
        fread(lpBuffer, FileSize, 1, fp);
        fclose(fp);

        wprintf(L"Processing %s ... \n", *argv);
        if (*(PUInt32)lpBuffer == TAG4('abmp'))
        {
            UInt32 v = Split(lpBuffer, FileSize, *argv);
            if (v != -1)
                wprintf(L"Split into %u files\n\n", v);
            else
            {
                wprintf(L"unsupported format\n\n");
            }
        }
        else if (FileSize > sizeof(header) && !memcmp(lpBuffer, header, sizeof(header)))
        {
            UInt32 v = Combine(lpBuffer, FileSize, *argv);
            if (v == -1)
                wprintf(L"unsupported format\n\n");
            else
                wprintf(L"Combine %u files\n\n", v);
        }
        else
        {
            wprintf(L"unknown format\n\n");
        }
    }

    free(lpBuffer);
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}

UInt32 Uncompress(LPVoid lpInputBuffer, Int32 BufferSize, LPVoid lpOutputBuffer)
{
    Byte   dict_bak[256], dict1[256], dict2[256], dict3[256];
    PByte  pbBuffer, pbEnd, pbDecompress;
    UInt32 Flag, Size;
    SPackEntryCompressedData *pData;

    pData = (SPackEntryCompressedData *)lpInputBuffer;
    if (pData->Magic != SQLI_COMP_MAGIC)
    {
        Flag = 0;
        Size = 0;
        pbBuffer = (PByte)pData + 4;
        BufferSize -= 4;
    }
    else
    {
        if (pData->DecompressSize > 0x4000000)
            return 0;

        Flag = pData->Flag;
        Size = pData->DecompressSize;
        pbBuffer = (PByte)pData->Data;
        BufferSize -= sizeof(*pData) - sizeof(pData->Data);
    }

    pbEnd = pbBuffer + BufferSize;

    if (pbBuffer >= pbEnd)
        return 0;

    for (Int32 i = 0, j = 0x03020100; i != 256; ++i)
    {
//        dict_bak[i] = i;
        *(PUInt32)&dict_bak[i] = j;
        i += 3;
        j += 0x04040404;
    }

    pbDecompress = pbBuffer;
    pbDecompress = (PByte)lpOutputBuffer;
    while (pbBuffer < pbEnd)
    {
        Char b = *pbBuffer++;

        memcpy(dict1, dict_bak, sizeof(dict_bak));

        for (UInt32 i = 0; ;)
        {
            if (b < 0)
            {
                i += (Byte)b - 0x7F;
                b = 0;
            }
            break_if(i > 255);

            for (UInt32 j = 0, k = b + 1; j != k; ++j)
            {
                Byte by = *pbBuffer++;
                dict1[i] = by;
                if (by != i)
                    dict2[i] = *pbBuffer++;
                ++i;
            }

            break_if(i > 255);
            b = *pbBuffer++;
        }

        UInt32 j;
        if (Flag & FLAG_ENTRY_16BIT_LENGTH)
        {
            j = *(PUInt16)pbBuffer;
            pbBuffer += 2;
        }
        else
        {
            j = *(PUInt32)pbBuffer;
            pbBuffer += 4;
        }

        for (UInt32 k = 0; ; )
        {
            UInt32 Index;

            if (k)
            {
                Index = dict3[--k];
            }
            else
            {
                break_if(j == 0);
                --j;
                Index = *pbBuffer++;
            }

            if (Index == dict1[Index])
            {
                *pbDecompress++ = Index;
                continue;
            }

            dict3[k++] = dict2[Index];
            dict3[k++] = dict1[Index];
        }
    }

    return pbDecompress - (PByte)lpOutputBuffer;
}