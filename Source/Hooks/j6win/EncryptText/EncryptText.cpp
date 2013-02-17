#pragma comment(linker,"/ENTRY:main")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include <Windows.h>
#include "my_headers.h"
#include "sha2.h"
#include "aes.h"
#include <vector>
#include <algorithm>

#pragma comment(lib, NT6_LIB(../../crt/i386/msvcrt.lib))

using std::vector;

OVERLOAD_OP_NEW

typedef struct
{
    UInt32 Hash[8];
    UInt32 Legnth;
} STextHeader;

typedef struct
{
    STextHeader Header;
    PVoid pvText;
} STextItem;

enum EStatus
{
    STATUS_GET_SEP1,
    STATUS_GET_ORIG_TEXT,
    STATUS_GET_SEP2,
    STATUS_GET_CHS_TEXT,
};

NoInline PWChar NextLine(PWChar pText, PWChar pEnd)
{
    while (pText < pEnd && *pText++ != '\n');
    return pText;
}

NoInline UInt32 GetLine(PWChar pText, PWChar pEnd, PWChar pszBuffer, UInt32 BufferCount)
{
    PWChar pBufferBak = pszBuffer;

    pszBuffer[0] = 0;
    while (BufferCount-- && pText < pEnd)
    {
        WChar ch = *pText;

        if (ch == '\n')
        {
            ch = 0;
        }

        if (ch != '\r')
        {
            *pszBuffer++ = ch;
            if (ch == 0)
                break;
        }

        ++pText;
    }

    return pszBuffer - pBufferBak - 1;
}

UInt32 PushText(vector<STextItem> &vecText, PWChar pszFileName)
{
    UInt32 Length, Lines, OrigTextHash[8], TransTextHash[8];
    WChar szText[0x1000];
    PByte pbBuffer;
    PWChar pText, pEnd;
    EStatus Status;

    CMem mem;
    CFileDisk file;
    STextItem TextItem;

    if (!file.Open(pszFileName))
        return 0;

    if (!file.Read(&Length, 2))
        return 0;

    if ((UInt16)Length != BOM_UTF16_LE)
    {
        printf("%ws: UTF-16 LE only\n", pszFileName);
        return 0;
    }

    Length = file.GetSize() - 2;
    pbBuffer = (PByte)mem.Alloc(Length);
    if (pbBuffer == NULL)
        return 0;

    if (!file.Read(pbBuffer))
    {
        mem.Free(pbBuffer);
        return 0;
    }

    file.Close();

    pText  = (PWChar)pbBuffer;
    pEnd   = (PWChar)(pbBuffer + Length);
    Status = STATUS_GET_SEP1;
    Lines  = 0;

    while (pText < pEnd)
    {
        switch (*pText)
        {
            case ';':
                pText = NextLine(pText, pEnd);
                continue;

            case '=':
                if (Status == STATUS_GET_SEP1)
                {
                    Status = STATUS_GET_ORIG_TEXT;
                    GetLine(pText, pEnd, szText, countof(szText));
                    pText = NextLine(pText, pEnd);
                    continue;
                }
                break;

            case '-':
                if (Status == STATUS_GET_SEP2)
                {
                    Status = STATUS_GET_CHS_TEXT;
                    pText = NextLine(pText, pEnd);
                    continue;
                }
                break;
        }

        switch (Status)
        {
            case STATUS_GET_ORIG_TEXT:
                Status = STATUS_GET_SEP2;
                break;

            case STATUS_GET_CHS_TEXT:
                Status = STATUS_GET_SEP1;
                break;
        }

        if (Status == STATUS_GET_SEP2)
        {
//            sha256((PByte)szText, Length * 2, (PByte)&TextItem.Header.Hash);

            PByte  pbHash;
            UInt32 Index;
            PWChar pszTrans = szText;

            while (*pszTrans++ == '=');
            while (*pszTrans++ != ',');
            while (*pszTrans++ != ',');

            pbHash = (PByte)TextItem.Header.Hash;
            for (Index = 32; Index; --Index)
            {
                WChar ch = *pszTrans++;
                Byte  h;

                if (ch == 0)
                    break;

                if (IN_RANGE('0', ch, '9'))
                {
                    ch -= '0';
                }
                else
                {
                    ch &= 0xFFDF;
                    if (!IN_RANGE('A', ch, 'Z'))
                        break;

                    ch = ch - 'A' + 10;
                }

                h = ch << 4;

                ch = *pszTrans++;
                if (ch == 0)
                    break;

                if (IN_RANGE('0', ch, '9'))
                {
                    ch -= '0';
                }
                else
                {
                    ch &= 0xFFDF;
                    if (!IN_RANGE('A', ch, 'Z'))
                        break;

                    ch = ch - 'A' + 10;
                }

                h |= ch;

                *pbHash++ = h;
            }

            if (Index != 0)
                goto INVALID_TEXT_FILE;
        }

        Length = GetLine(pText, pEnd, szText, countof(szText));
        pText = NextLine(pText, pEnd);
        if (Length == 0 || szText[0] == 0)
            continue;

        if (Status == STATUS_GET_SEP2)
        {
            sha256(szText, Length * 2, OrigTextHash);
            continue;
        }

        // STATUS_GET_CHS_TEXT

        Length *= 2;
        sha256(szText, Length, TransTextHash);
        if (!memcmp(TransTextHash, OrigTextHash, sizeof(TransTextHash)))
            continue;

        TextItem.Header.Legnth = Length;
        Length = (Length + 3) & ~3;
        TextItem.pvText = mem.Alloc(Length + 2, HEAP_ZERO_MEMORY);
        memcpy(TextItem.pvText, szText, Length);

        vecText.push_back(TextItem);
        ++Lines;
    }

    return Lines;

INVALID_TEXT_FILE:
    printf("%ws: invalid hash\n%ws\n", pszFileName, szText);
    getch();
    return 0;
}

Bool EncryptText(vector<STextItem> &vecText)
{
    SizeT Size;
    STextItem *pTextItem;
    WChar szText[8];
    aes_encrypt_ctx ctx;

    Size = vecText.size();
    if (Size == 0)
        return False;

    pTextItem = &vecText[0];
    while (Size--)
    {
        UInt32 Length, Hash[4];
        PWChar pszText;

        Length = (pTextItem->Header.Legnth + 3) & ~3;
        pszText = (PWChar)pTextItem->pvText;

        aes_encrypt_key128((PByte)&pTextItem->Header.Hash[4], &ctx);

        Hash[0] = pTextItem->Header.Hash[0];
        Hash[1] = pTextItem->Header.Hash[1];
        Hash[2] = pTextItem->Header.Hash[2];
        Hash[3] = pTextItem->Header.Hash[3];

        while (Length >= 16)
        {
            Length -= 16;

            aes_encrypt((PByte)Hash, (PByte)Hash, &ctx);
            *((PUInt32)pszText + 0) ^= Hash[0];
            *((PUInt32)pszText + 1) ^= Hash[1];
            *((PUInt32)pszText + 2) ^= Hash[2];
            *((PUInt32)pszText + 3) ^= Hash[3];

            Hash[0] = *((PUInt32)pszText + 0);
            Hash[1] = *((PUInt32)pszText + 1);
            Hash[2] = *((PUInt32)pszText + 2);
            Hash[3] = *((PUInt32)pszText + 3);

            pszText += 8;
        }

        if (Length != 0)
        {
            memcpy(szText, pszText, Length);
            aes_encrypt((PByte)Hash, (PByte)Hash, &ctx);
            *((PUInt32)szText + 0) ^= Hash[0];
            *((PUInt32)szText + 1) ^= Hash[1];
            *((PUInt32)szText + 2) ^= Hash[2];
            *((PUInt32)szText + 3) ^= Hash[3];
            memcpy(pszText, szText, Length);
        }

        pTextItem->Header.Hash[0] ^= pTextItem->Header.Hash[4];
        pTextItem->Header.Hash[1] ^= pTextItem->Header.Hash[5];
        pTextItem->Header.Hash[2] ^= pTextItem->Header.Hash[6];
        pTextItem->Header.Hash[3] ^= pTextItem->Header.Hash[7];

        ++pTextItem;
    }

    return True;
}

int CompareHash(STextItem &t1, STextItem &t2)
{
    for (UInt32 i = 0; i != 4; ++i)
    {
        if (t1.Header.Hash[i] != t2.Header.Hash[i])
            return t1.Header.Hash[i] < t2.Header.Hash[i];
    }

    return False;
}

Bool WriteEncryptedText(vector<STextItem> &vecText, PWChar pszFileName)
{
    CFileDisk file;
    STextItem *pTextItem;

    if (!file.Open(pszFileName, file.FILE_ACCESS_WRITE, file.FILE_SHAREMODE_READ, file.FILE_CREATE_ALWAYS))
        return False;

    std::sort(vecText.begin(), vecText.end(), CompareHash);

    pTextItem = &vecText[0];
    for (SizeT i = vecText.size(); i--; ++pTextItem)
    {
        UInt32 Legnth;
        file.Write(pTextItem->Header.Hash, 4 * sizeof(pTextItem->Header.Hash[0]));
        Legnth = pTextItem->Header.Legnth ^ pTextItem->Header.Hash[0] ^ pTextItem->Header.Hash[2];
        file.Write(&Legnth, sizeof(Legnth));
        file.Write(pTextItem->pvText, (pTextItem->Header.Legnth + 3) & ~3);
    }

    return True;
}

Int32 STDCALL EnumFilesCallback(PVoid pvBuffer, LPWIN32_FIND_DATAW pFindData, PVoid pvParam)
{
    lstrcpyW((PWChar)pvBuffer, pFindData->cFileName);
    return 1;
}

ForceInline Void main2(Int argc, WChar **argv)
{
    UInt32 Lines;
    STextItem *pTextItem;
    vector<STextItem> vecText;

    Lines = 0;
    _wsetlocale(LC_CTYPE, L"");
    while (--argc)
    {
        PWChar pszPath = *++argv;

        if (GetFileAttributesW(pszPath) & FILE_ATTRIBUTE_DIRECTORY)
        {
            WChar (*szFiles)[MAX_PATH];
            Large_Integer FileCount;

            if (EnumDirectoryFiles(
                    (PVoid *)&szFiles,
                    L"*.txt",
                    sizeof(*szFiles),
                    pszPath,
                    &FileCount,
                    EnumFilesCallback,
                    NULL,
                    0))
            {
                while (FileCount.LowPart--)
                    Lines += PushText(vecText, szFiles[FileCount.LowPart]);

                EnumDirectoryFilesFree(szFiles);
            }
        }
        else
        {
            Lines += PushText(vecText, pszPath);
        }
    }

    if (EncryptText(vecText))
    {
        WChar szFile[MAX_PATH];
        lstrcpyW(szFile + GetExecuteDirectoryW(szFile, countof(szFile)), L"j6.sc");
        WriteEncryptedText(vecText, szFile);
    }

    argc = vecText.size();
    printf(
        "%d file%c\n"
        "%d line%c\n",
        argc, argc > 1 ? 's' : 0, 
        Lines, Lines > 1 ? 's' : 0);

    Sleep(500);

    CMem mem;

    pTextItem = &vecText[0];
    for (vector<STextItem>::size_type i = vecText.size(); i--; )
    {
        if (pTextItem->pvText)
        {
//            printf("(%05d) %ws\n", ++argc, pTextItem->pvText);
            mem.Free(pTextItem->pvText);
        }
        ++pTextItem;
    }
}

void __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    exit(0);
}