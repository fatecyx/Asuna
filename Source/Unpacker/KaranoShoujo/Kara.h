#ifndef _KARA_H_
#define _KARA_H_

#pragma comment(lib, "ntdll.lib")

#include "my_headers.h"
#include "gal_common.h"

#pragma pack(1)

typedef struct
{
    UInt64 Magic;
    UInt32 FileNum;
    UInt32 unk;
} SKaraPackHeader;

typedef struct
{
    Char   FileName[0x20];
    UInt32 Offset;
    UInt32 EncryptFlags;
    UInt32 Size;
    UInt32 EncryptSize;
} SKaraPackEntry;

typedef struct
{
    UInt32 FileNum;
    SKaraPackEntry *pEntry;
} SMyKaraPackIndex;

#pragma pack()

class CKaranoShoujo : public CUnpackerBase
{
protected:
    enum
    {
        KARA_NO_SHOUJO_ENCRYPT_FLAG_16 = 1 << 16,
        KARA_NO_SHOUJO_FILE_TYPE_IMAGE = 0x30000000,
        KARA_NO_SHOUJO_FILE_TYPE_OTHER = 0x20000000,
    };

    SMyKaraPackIndex m_index;
    CFileDisk m_file;

public:
    CKaranoShoujo()
    {
        m_index.pEntry = NULL;
    }

    ~CKaranoShoujo()
    {
        Release();
    }

    Bool Open(PCWChar pszFileName)
    {
        SKaraPackHeader header;

        if (!m_file.Open(pszFileName))
            return False;

        if (!m_file.Read(&header, sizeof(header)))
            return False;

        if (header.Magic != TAG8('PACK', 'DAT.'))
            return False;

        return InitIndex(&header);
    }

    UInt32 ExtractFile(SKaraPackEntry *pEntry, PCWChar pszOutPath = NULL)
    {
        UInt32 ExtractedFileSize;
        SFileInfo info;
        WChar szFile[MAX_PATH];

        if (GetFileData(&info, pEntry) == False)
            return 0;

        if (pszOutPath)
        {
            lstrcpyW(szFile, pszOutPath);
            rmextw(szFile);
            lstrcatW(szFile, L"\\");
            ExtractedFileSize = StrLenW(szFile);
        }
        else
        {
            szFile[0] = 0;
            ExtractedFileSize = 0;
        }

        MultiByteToWideChar(CP_ACP, 0, pEntry->FileName, -1, szFile + ExtractedFileSize, countof(szFile) - ExtractedFileSize);

        ExtractedFileSize = findnamew(szFile) - szFile;
        if (ExtractedFileSize)
        {
            szFile[--ExtractedFileSize] = 0;
            MyCreateDirectoryW(szFile);
            szFile[ExtractedFileSize] = L'\\';
        }

        CFileDisk File;

        ExtractedFileSize = 0;
        if (File.Open(szFile, File.FILE_ACCESS_WRITE, File.FILE_SHAREMODE_READ, File.FILE_CREATE_ALWAYS))
        {
            File.Write(info.ImgData.pbBuffer, info.ImgData.BufferSize);
            ExtractedFileSize = info.ImgData.BufferSize;
        }

        FreeFileData(&info);

        return ExtractedFileSize;
    }

    Bool GetFileData(SFileInfo *pFileInfo, const SKaraPackEntry *pEntry)
    {
        PByte pbBuffer;
        PChar pExtension;
/*
        if (lstrcmpA(pEntry->FileName, "window.bmp"))
            return False;
*/
        if (!m_file.Seek(m_file.FILE_SEEK_BEGIN, pEntry->Offset))
            return False;

        pbBuffer = (PByte)Alloc(pEntry->Size);
        if (pbBuffer == NULL)
            return False;

        do
        {
            if (!m_file.Read(pbBuffer, pEntry->Size))
                break;

            if (pEntry->EncryptFlags & 0x00FFFFFF)
            {
                if (TEST_BITS(pEntry->EncryptFlags, 16) && !DecryptFlagBits16(pEntry, pbBuffer, pEntry->Size))
                    break;

                if (
                    TEST_BITS(pEntry->EncryptFlags, 1) ||
                    TEST_BITS(pEntry->EncryptFlags, 2) ||
                    TEST_BITS(pEntry->EncryptFlags, 4) ||
                    TEST_BITS(pEntry->EncryptFlags, 8)
                    )
                {
                    printf("%s: Unimplemented decryption\n", pEntry->FileName);
                    getch();
                }
            }

            pExtension = findexta(pEntry->FileName);
            if (!lstrcmpA(pExtension, ".s"))
            {
                DecryptScript(pbBuffer, pEntry->Size);
            }

            pFileInfo->FileType = UNPACKER_FILE_TYPE_BIN;
            pFileInfo->BinData.pbBuffer = pbBuffer;
            pFileInfo->BinData.BufferSize = pEntry->Size;

            return True;

        } while (0);

        Free(pbBuffer);
        return False;
    }

    static Int32 STDCALL EnumFilesCallback(LPVoid lpBuffer, PWIN32_FIND_DATAW pFindData, LPVoid lpParam)
    {
        Bool bUsedDefaultChar;
        Int  CharRecv;
        SKaraPackEntry *pEntry = (SKaraPackEntry *)lpBuffer;

        pEntry->Size = pFindData->nFileSizeLow;
        pEntry->EncryptSize = pFindData->nFileSizeLow;
        CharRecv = WideCharToMultiByte(
                       CP_ACP,
                       0,
                       pFindData->cFileName + (ULong)lpParam,
                       -1,
                       pEntry->FileName,
                       countof(pEntry->FileName),
                       NULL,
                       &bUsedDefaultChar);

        return bUsedDefaultChar ? 0 : CharRecv ? 1 : 0;
    }

    UInt32 Pack(PCWChar pszPath)
    {
        Bool  Result;
        PByte pbBuffer;
        ULong Length, Offset, PackedFiles, BufferSize, FileSize, BytesWritten, Extension;
        WChar szPackName[MAX_PATH];
        Char  szFileName[MAX_PATH], *pszFileName;
        Large_Integer FileNum;
        SKaraPackHeader PackHeader;
        SKaraPackEntry *pEntry;

        Length = StrLenW(pszPath);
        if (szPackName[Length - 1] != '\\')
            ++Length;

        Result = EnumDirectoryFiles(
                     (LPVoid *)&pEntry,
                     L"*.*",
                     sizeof(*pEntry),
                     pszPath,
                     &FileNum,
                     EnumFilesCallback,
                     (LPVoid)Length,
                     ENUM_DIRECTORY_FILES_FLAG_ENUMSUBDIR);
        if (!Result)
            return 0;

        lstrcpyW(szPackName, pszPath);
        Length = StrLenW(szPackName);
        if (szPackName[Length - 1] == '\\')
            szPackName[--Length] = 0;

        lstrcpyW(szPackName + Length, L".dat");

        CFileDisk filePack, file;

        do
        {
            PackedFiles = 0;
            Result = filePack.Open(
                         szPackName,
                         filePack.FILE_ACCESS_WRITE,
                         filePack.FILE_SHAREMODE_READ,
                         filePack.FILE_CREATE_NEW);
            if (!Result)
                break;

            if (!filePack.Seek(filePack.FILE_SEEK_BEGIN, FileNum.LowPart * sizeof(*pEntry) + sizeof(PackHeader)))
                break;

            Length = WideCharToMultiByte(CP_ACP, 0, pszPath, -1, szFileName, countof(szFileName), NULL, NULL);
            pszFileName = szFileName + Length - 1;
            if (*(pszFileName - 1) != '\\')
                *pszFileName++ = '\\';

            Offset = filePack.GetCurrentPos();
            BufferSize = 0x2000;
            pbBuffer = (PByte)Alloc(BufferSize);
            for (UInt32 i = 0; i != FileNum.LowPart; ++i)
            {
                PChar pszExtension;

                lstrcpyA(pszFileName, pEntry[i].FileName);
                if (!file.Open(szFileName))
                {
                    pEntry[i].Size = 0;
                    continue;
                }

                FileSize = pEntry[i].Size;
                if (FileSize > BufferSize)
                {
                    BufferSize = FileSize;
                    pbBuffer = (PByte)ReAlloc(BufferSize, pbBuffer);
                }

                file.Read(pbBuffer);

                pszExtension = findexta(pEntry[i].FileName);
                if (*pszExtension == '.')
                    ++pszExtension;
                Extension = *(PUInt32)pszExtension;
                if ((Extension & 0xFFDF) == 'S')
                {
                    DecryptScript(pbBuffer, FileSize);
                    pEntry[i].EncryptFlags = KARA_NO_SHOUJO_ENCRYPT_FLAG_16|KARA_NO_SHOUJO_FILE_TYPE_OTHER;
                    EncryptFlagBits16(pEntry + i, pbBuffer, FileSize);
                }
                else
                {
                    switch (Extension & 0xFFDFDFDF)
                    {
                        case TAG3('OGG'):
                        case TAG3('UCA'):
                        case TAG3('M4A') & 0xFFDFDFDF:
                            pEntry[i].EncryptFlags = KARA_NO_SHOUJO_FILE_TYPE_OTHER;
                            break;

                        case TAG3('UCI'):
                        case TAG3('BMP'):
                            pEntry[i].EncryptFlags = KARA_NO_SHOUJO_FILE_TYPE_IMAGE;
                            NO_BREAK;

                        default:
                            pEntry[i].EncryptFlags |= KARA_NO_SHOUJO_ENCRYPT_FLAG_16;
                            EncryptFlagBits16(pEntry + i, pbBuffer, FileSize);
                    }
                }

                filePack.Write(pbBuffer, FileSize, (PUInt32)&BytesWritten);
                pEntry[i].Offset = Offset;
                Offset += BytesWritten;
            }

            PackHeader.Magic = TAG8('PACK', 'DAT.');
            PackHeader.FileNum = FileNum.LowPart;
            PackHeader.unk = FileNum.LowPart;

            filePack.Rewind();
            filePack.Write(&PackHeader, sizeof(PackHeader));
            filePack.Write(pEntry, PackHeader.FileNum * sizeof(*pEntry));

        } while (0);

        EnumDirectoryFilesFree(pEntry);

        return PackedFiles;
    }

    Void Auto(PCWChar pszFileName)
    {
        SKaraPackEntry *pEntry;
        DWORD Attributes;
        WChar szPath[MAX_PATH], szConsoleTitle[0x30];
        extern Bool bCtrlC;

        Attributes = GetFileAttributesW(pszFileName);
        if (Attributes == -1)
            return;

        if (Attributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            Pack(pszFileName);
            return;
        }

        if (!Open(pszFileName))
            return;

        lstrcpyW(szPath, pszFileName);
        rmextw(szPath);
        pEntry = m_index.pEntry;
        for (UInt32 i = 0; i != m_index.FileNum && !bCtrlC; ++i, ++pEntry)
        {
            UInt32 Size;
            printf("Extracting \"%s\" ... ", pEntry->FileName);
            swprintf(szConsoleTitle, L"%u / %u", i + 1, m_index.FileNum);
            SetConsoleTitleW(szConsoleTitle);
            Size = ExtractFile(pEntry, szPath);
            printf("%s\n", Size ? "OK" : "failed");
        }
    }

protected:
    Bool InitIndex(SKaraPackHeader *pHeader)
    {
        UInt32 EntrySize;

        m_index.FileNum = pHeader->FileNum;
        EntrySize = pHeader->FileNum * sizeof(*m_index.pEntry);
        m_index.pEntry = (SKaraPackEntry *)Alloc(EntrySize);
        if (m_index.pEntry == NULL)
            return False;

        return m_file.Read(m_index.pEntry, EntrySize);
    }

    Void Release()
    {
        SafeFree(&m_index.pEntry);
    }

    // decrypt functions

    Void DecryptScript(PByte pbBuffer, UInt32 BufferSize)
    {
        while (BufferSize--)
            pbBuffer[BufferSize] = ~pbBuffer[BufferSize];
    }

    Bool DecryptFlagBits1 (const SKaraPackEntry *pEntry, PByte pbBuffer, UInt32 BufferSize)
    {
    }

    Bool DecryptFlagBits2 (const SKaraPackEntry *pEntry, PByte pbBuffer, UInt32 BufferSize)
    {
    }

    Bool DecryptFlagBits4 (const SKaraPackEntry *pEntry, PByte pbBuffer, UInt32 BufferSize)
    {
    }

    Bool DecryptFlagBits8 (const SKaraPackEntry *pEntry, PByte pbBuffer, UInt32 BufferSize)
    {
    }

    Bool DecryptFlagBits16(const SKaraPackEntry *pEntry, PByte pbBuffer, UInt32 BufferSize)
    {
        UInt32 EncryptSize, Key;

        if (pEntry->Size > BufferSize)
            return False;

        EncryptSize = pEntry->EncryptSize / 4;
        if (EncryptSize == 0)
            return False;

        Key = EncryptSize << ((EncryptSize & 7) + 8);
        Key ^= EncryptSize;

        do
        {
            UInt32 Temp;

            Temp = *(PInt32)pbBuffer ^ Key;
            *(PInt32)pbBuffer = Temp;
            pbBuffer += 4;
            Key = _rotl(Key, Temp % 24);
        } while (--EncryptSize);

        return True;
    }

    Bool EncryptFlagBits16(const SKaraPackEntry *pEntry, PByte pbBuffer, UInt32 BufferSize)
    {
        UInt32 EncryptSize, Key;

        if (pEntry->Size > BufferSize)
            return False;

        EncryptSize = pEntry->EncryptSize / 4;
        if (EncryptSize == 0)
            return False;

        Key = EncryptSize << ((EncryptSize & 7) + 8);
        Key ^= EncryptSize;

        do
        {
            UInt32 Temp;

            Temp = *(PInt32)pbBuffer;
            *(PInt32)pbBuffer = Temp ^ Key;
            pbBuffer += 4;
            Key = _rotl(Key, Temp % 24);
        } while (--EncryptSize);

        return True;
    }
};

#endif /* _KARA_H_ */