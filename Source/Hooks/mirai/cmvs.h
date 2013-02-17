#ifndef _CMVS_H_c23b18b9_ac3f_4d75_87cd_9a58397c439b_
#define _CMVS_H_c23b18b9_ac3f_4d75_87cd_9a58397c439b_

#include "MyLibrary.h"
#include "UnpackerBase.h"

#pragma pack(push, 1)

typedef struct
{
    ULONG           EntrySize;
    LARGE_INTEGER   Offset;
    ULONG           Size;
    ULONG           Hash1;
    ULONG           Hash2;
    CHAR            Name[1];

} CPZ_FILE_ENTRY, *PCPZ_FILE_ENTRY;

typedef struct CPZ_DIRECTORY_ENTRY
{
    ULONG EntrySize;
    ULONG FileCount;
    ULONG FileEntryOffset;
    ULONG Hash;
    CHAR  Name[1];

} CPZ_DIRECTORY_ENTRY, *PCPZ_DIRECTORY_ENTRY;

typedef struct CMVS_PS2_HEADER
{
    ULONG Magic;
    ULONG HeaderSize;
    ULONG Unknown1;
    ULONG Crc;
    ULONG ThunkCount;
    ULONG OpCodeSize;
    ULONG DataSize;
    ULONG TextSize;

} CMVS_PS2_HEADER, *PCMVS_PS2_HEADER;

class CpzStream
{
public:
    PCPZ_DIRECTORY_ENTRY    DirectoryEntry;
    PCSTR                   CpzFileName;
    ULONG                   DirectoryCount;
    ULONG                   DirectoryEntrySize;

public:
    virtual VOID THISCALL DeleteDestruction(BOOLEAN Destroy);
    virtual PCPZ_DIRECTORY_ENTRY THISCALL InitIndex(PCSTR CpzFileName, ULONG_PTR Zero = 0);
    virtual PVOID THISCALL LoadFileX(PCSTR CpzFileName, PCSTR PathName, PCSTR FileName, PULONG FileSize);
    virtual PVOID THISCALL LoadFile(PCSTR CpzFileName, PCSTR FileName, PULONG FileSize, ULONG Zero1 = 0, ULONG Zero2 = 0);
};

#if ML_X86

#define MIRAI_LOAD_CPZ_RVA  0x4A650
#define MIRAI_LOAD_PS2_RVA  0x4A820
#define MIRAI_LOAD_PB3_RVA  0x25E50

#elif ML_AMD64

#endif

class CpzObject
{
public:
    CHAR        CpzFileName[0x800];
    CpzStream*  Stream;

public:
    CpzObject()
    {
        Stream = NULL;
        CpzFileName[0] = 0;
    }

    ~CpzObject()
    {
        if (Stream != NULL)
            Stream->DeleteDestruction(TRUE);
    }

    BOOL THISCALL LoadCpz(ULONG_PTR Index, PCSTR CpzFileName, ULONG_PTR Unknown1 = 1, ULONG_PTR Unknown2 = 1)
    {
        TYPE_OF(&CpzObject::LoadCpz) LoadCpzF;

        *(PVOID *)&LoadCpzF = (PVOID)PtrAdd(0x400000, MIRAI_LOAD_CPZ_RVA);

        return (this->*LoadCpzF)(Index, CpzFileName, Unknown1, Unknown2);
    }

    PVOID THISCALL LoadPs2(PCSTR Ps2File, PULONG FileSize)
    {
        TYPE_OF(&CpzObject::LoadPs2) LoadPs2F;

        *(PVOID *)&LoadPs2F = (PVOID)PtrAdd(0x400000, MIRAI_LOAD_PS2_RVA);

        return (this->*LoadPs2F)(Ps2File, FileSize);
    }
};

typedef struct
{
    PVOID Buffer;
    ULONG Size;
    ULONG Width;
    ULONG Height;
    ULONG BitsPerPixel;
    BOOL  NativeAlpha;

} CMVS_IMAGE_OBJECT, *PCMVS_IMAGE_OBJECT;

class CmvsImageManager
{
public:
    BOOL THISCALL LoadPb3(PCMVS_IMAGE_OBJECT Image, PCSTR Path, PCSTR ImageFile, ULONG Zero = 0)
    {
        TYPE_OF(&CmvsImageManager::LoadPb3) LoadPb3F;

        *(PVOID *)&LoadPb3F = (PVOID)PtrAdd(0x400000, MIRAI_LOAD_PB3_RVA);

        return (this->*LoadPb3F)(Image, Path, ImageFile, Zero);
    }
};

class CmvsObject
{
public:

    DUMMY_STRUCT(0xC7C);

    CmvsImageManager *ImageManager;

    DUMMY_STRUCT(0x265C);

    ULONG PsIndex;                  // 0x32DC
    ULONG Ip;                       // 0x32E0

    DUMMY_STRUCT(0x734);

    PCMVS_PS2_HEADER Ps2Buffer[4];  // 0x3A18
    PBYTE Ps2OpBuffer[4];           // 0x3A28
    PBYTE Ps2DataBuffer[4];         // 0x3A38
    PBYTE Ps2StringBuffer[4];       // 0x3A48
};

#pragma pack(pop)

typedef struct UNPACKER_CPZ_ENTRY : public UNPACKER_FILE_ENTRY_BASE
{
    PCPZ_DIRECTORY_ENTRY    CpzDirectory;
    PCPZ_FILE_ENTRY         CpzFile;

} UNPACKER_CPZ_ENTRY, *PUNPACKER_CPZ_ENTRY;

class CmvsUnpackerX : public UnpackerImpl<CmvsUnpackerX>
{
protected:
    CpzObject   cpz;
    CmvsImageManager *imgmgr;

public:
    CmvsUnpackerX(CmvsImageManager *imgmgr)
    {
        this->imgmgr = imgmgr;
    }

    UPK_STATUS Open(PCWSTR FileName)
    {
        CpzStream*              Stream;
        PCPZ_DIRECTORY_ENTRY    Directory, DirectoryBase;
        PCPZ_FILE_ENTRY         FileEntry, FileEntryBase;
        PUNPACKER_CPZ_ENTRY     Entry;

        union
        {
            CHAR  CpzPathA[MAX_NTPATH];
            WCHAR CpzPathW[MAX_NTPATH];
        };

        Nt_UnicodeToAnsi(CpzPathA, countof(CpzPathA), FileName);
        if (!cpz.LoadCpz(0, CpzPathA))
            return STATUS_UNSUCCESSFUL;

        Stream = cpz.Stream;
        DirectoryBase = Stream->InitIndex(CpzPathA);
        if (DirectoryBase == NULL)
            return STATUS_UNSUCCESSFUL;

        m_Index.EntrySize = sizeof(*Entry);
        m_Index.FileCount.QuadPart = 0;

        Directory = DirectoryBase;
        for (ULONG_PTR Count = Stream->DirectoryCount; Count; --Count)
        {
            m_Index.FileCount.QuadPart += Directory->FileCount;
            Directory = PtrAdd(Directory, Directory->EntrySize);
        }

        m_Index.Entry = AllocateEntry(m_Index.FileCount.QuadPart);
        if (m_Index.Entry == NULL)
            return STATUS_NO_MEMORY;

        Entry = (PUNPACKER_CPZ_ENTRY)m_Index.Entry;
        Directory = DirectoryBase;
        FileEntryBase = (PCPZ_FILE_ENTRY)PtrAdd(DirectoryBase, Stream->DirectoryEntrySize);

        for (ULONG_PTR Count = Stream->DirectoryCount; Count; --Count)
        {
            FileEntry = PtrAdd(FileEntryBase, Directory->FileEntryOffset);
            for (ULONG_PTR FileCount = Directory->FileCount; FileCount; --FileCount)
            {
                ULONG_PTR Length;

                Entry->CpzFile = FileEntry;
                Entry->CpzDirectory = Directory;

                Length = MultiByteToWideChar(CP_SHIFTJIS, 0, Directory->Name, -1, CpzPathW, countof(CpzPathW));
                CpzPathW[Length - 1] = '\\';
                Length = MultiByteToWideChar(CP_SHIFTJIS, 0, FileEntry->Name, -1, CpzPathW + Length, countof(CpzPathW) - Length);
                Entry->SetFileName(CpzPathW);

                FileEntry = PtrAdd(FileEntry, FileEntry->EntrySize);
                ++Entry;
            }

            Directory = PtrAdd(Directory, Directory->EntrySize);
        }

        return STATUS_SUCCESS;
    }

    UPK_STATUS GetFileData(PUNPACKER_FILE_INFO FileInfo, UNPACKER_FILE_ENTRY_BASE *BaseEntry, ULONG Flags /* = 0 */)
    {
        BOOL                Success;
        PVOID               Buffer;
        PBYTE               Source, Destination;
        ULONG               FileSize;
        LONG_PTR            Stride;
        UPK_STATUS          Status;
        PUNPACKER_CPZ_ENTRY Entry;
        PWSTR               Extension;
        CMVS_IMAGE_OBJECT   Image;
        IMAGE_BITMAP_HEADER BmpHeader;

        Entry = (PUNPACKER_CPZ_ENTRY)BaseEntry;

        Extension = findextw(Entry->GetFileName());
        if (!StrICompareW(Extension, L".ps2"))
        {
            Buffer = cpz.LoadPs2(Entry->CpzFile->Name, &FileSize);
        }
        else if (!StrICompareW(Extension, L".pb3"))
        {
            Buffer = NULL;
            Success = imgmgr->LoadPb3(&Image, "", Entry->CpzFile->Name);
            if (!Success)
                return STATUS_UNSUCCESSFUL;

            InitBitmapHeader(&BmpHeader, Image.Width, Image.Height, Image.BitsPerPixel, &Stride);

            Status = AllocateFileData(FileInfo, BmpHeader.FileSize, UnpackerFileBitmap);
            FAIL_RETURN(Status);

            *(PIMAGE_BITMAP_HEADER)FileInfo->SingleFrame.Buffer = BmpHeader;

            Source = (PBYTE)Image.Buffer;
            Destination = (PBYTE)PtrAdd(FileInfo->SingleFrame.Buffer, BmpHeader.RawOffset);
            Destination += (Image.Height - 1) * Stride;

            for (ULONG_PTR Height = Image.Height; Height; --Height)
            {
                CopyMemory(Destination, Source, Stride);
                Destination -= Stride;
                Source += Stride;
            }

            LocalFree(Image.Buffer);

            return STATUS_SUCCESS;
        }
        else
        {
            Buffer = cpz.Stream->LoadFile(cpz.Stream->CpzFileName, Entry->CpzFile->Name, &FileSize);
        }

        if (Buffer == NULL)
            return STATUS_UNSUCCESSFUL;

        Status = AllocateFileData(FileInfo, FileSize, UnpackerFileBinary);
        FAIL_RETURN(Status);

        CopyMemory(FileInfo->BinaryData.Buffer, Buffer, FileSize);
        LocalFree(Buffer);

        return STATUS_SUCCESS;
    }
};

typedef struct TEXTBIN_ENTRY
{
    ULONG Offset    : 31;
    ULONG Decrypted : 1;
    ULONG Length;
    CHAR  Text[1];

    TEXTBIN_ENTRY* Next()
    {
        return PtrAdd(this, ROUND_UP(Length, 4) + sizeof(ULONG) + sizeof(Length));
    }

} *PTEXTBIN_ENTRY;

typedef struct
{
    ULONG           Count;
    ULONG           Crc;
    TEXTBIN_ENTRY   Entry[1];

} *PTEXTBIN_HEADER;

#endif // _CMVS_H_c23b18b9_ac3f_4d75_87cd_9a58397c439b_
