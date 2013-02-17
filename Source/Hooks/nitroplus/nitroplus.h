#ifndef _NITROPLUS_H_b48726f8_7f7d_4b9a_bc62_77a0f4daaed5_
#define _NITROPLUS_H_b48726f8_7f7d_4b9a_bc62_77a0f4daaed5_

#include "MyLibraryUser.h"
#include "npack.h"
#include "AntiDebug.h"

#define CODE_PAGE_NLS_KEY   L"SYSTEM\\ControlSet001\\Control\\Nls\\CodePage"
#define SYSTEM_PATH_KEY     L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Installer"
#define SYSTEM_PATH_VALUE   L"InstallerLocation"


enum
{
    ExceptionQueryPackPath  = EXCEPTION_CODE(EXCEPTION_CODE_USER + 1),
    ExceptionReadFileData   = EXCEPTION_CODE(EXCEPTION_CODE_USER + 2),
    ExceptionWriteMemory    = EXCEPTION_CODE(EXCEPTION_CODE_USER + 3),
};

class NitruPlusHelper : public AntiDebugImpl<NitruPlusHelper>
{
protected:
    NPackReader np;

public:
    NTSTATUS InitializeDebugger()
    {
        WCHAR FileName[0x20];

        *(PULONG64)&FileName[0x0] = TAG4W('axan');
        *(PULONG64)&FileName[0x4] = TAG4W('ael_');
        *(PULONG64)&FileName[0x8] = TAG4W('cn.n');
        *(PULONG64)&FileName[0xC] = TAG4W('pack');

        FileName[0x10] = 0;

        return np.Open(FileName);
    }

    NTSTATUS QueryPackPath(PIO_CONTROL_PARAMETER IoControl)
    {
        ULONG Length;
        PWSTR FileName;
        
        if (IoControl->OutputBufferLength < MAX_NTPATH * sizeof(WCHAR))
            return STATUS_BUFFER_TOO_SMALL;

        Length = Nt_GetModulePath(&__ImageBase, (PWSTR)IoControl->OutputBuffer, MAX_NTPATH);
        FileName = (PWSTR)IoControl->OutputBuffer + Length;

        *(PULONG64)&FileName[0x0] = TAG4W('axan');
        *(PULONG64)&FileName[0x4] = TAG4W('ael_');
        *(PULONG64)&FileName[0x8] = TAG4W('cn.n');
        *(PULONG64)&FileName[0xC] = TAG4W('pack');

        FileName[0x10] = 0;

        Length += CONST_STRLEN(L"axanael_cn.npack") + 1;

        IoControl->OutputBufferLength = Length * sizeof(WCHAR);

        return STATUS_SUCCESS;
    }

    NTSTATUS ReadFileData(PIO_CONTROL_PARAMETER IoControl)
    {
        NTSTATUS            Status;
        NP_FIND_FILE_INFO  *FindInfo;

        if (sizeof(*FindInfo) != IoControl->InputBufferLength)
            return STATUS_INFO_LENGTH_MISMATCH;

        FindInfo = (NP_FIND_FILE_INFO *)IoControl->InputBuffer;
        if (FindInfo->FileSize > IoControl->OutputBufferLength)
            return STATUS_BUFFER_TOO_SMALL;

        Status = np.GetFileData(IoControl->OutputBuffer, FindInfo);
        if (NT_SUCCESS(Status))
            IoControl->OutputBufferLength = FindInfo->FileSize;

        return Status;
    }

    NTSTATUS WriteMemory(PIO_CONTROL_PARAMETER IoControl)
    {
        CopyMemory(IoControl->OutputBuffer, IoControl->InputBuffer, IoControl->InputBufferLength);
        return STATUS_SUCCESS;
    }

    BEGIN_EXCEPTION_MAP
        HANDLE_EXCEPTION(ExceptionQueryPackPath,    QueryPackPath)
        HANDLE_EXCEPTION(ExceptionReadFileData,     ReadFileData)
        HANDLE_EXCEPTION(ExceptionWriteMemory,      WriteMemory)
    END_EXCEPTION_MAP
};

typedef struct
{
    UNICODE_STRING  SystemDirectory;
    CPTABLEINFO     CpTable936;
    CPTABLEINFO     CpTable932;
    PVOID           CP936;
    PVOID           CP932;

    ULONG_PTR        ParentPid;
    NPackReader     *npack;
    NitruPlusHelper *Helper;

} NITRO_PLUS_INFO, *PNITRO_PLUS_INFO;

#pragma pack(1)

typedef struct NITRO_PLUS_FILE_STREAM // 0x158
{
    CHAR    FileName[0x104];    // 0x000
    ULONG   Unknown1;           // 0x104
    ULONG   FileSize;           // 0x108
    ULONG   FileNameHash;       // 0x10C
    HANDLE  FileHandle;         // 0x110
    ULONG   Unknown2;           // 0x114
    PVOID   FileContext;        // 0x118    FILE*
    PVOID   Buffer;             // 0x11C

    BOOL
    (CDECL
    *Initialize)(
        NITRO_PLUS_FILE_STREAM *Stream
    );    // 0x120

    BOOL
    (CDECL
    *Read)(
        NITRO_PLUS_FILE_STREAM *Stream
    );          // 0x124

    ULONG
    (CDECL
    *ReadRaw)(
        NITRO_PLUS_FILE_STREAM *Stream,
        PVOID                   Buffer,
        ULONG                   BlockCount,
        ULONG                   BlockSize
    );       // 0x128

    ULONG64
    (CDECL
    *Write)(
        NITRO_PLUS_FILE_STREAM *Stream
    );         // 0x12C

    LONG
    (CDECL
    *Seek)(
        NITRO_PLUS_FILE_STREAM *Stream,
        ULONG                   Position,
        LONG                    MoveMethod
    );          // 0x130

    ULONG
    (CDECL
    *GetPosision)(
        NITRO_PLUS_FILE_STREAM *Stream
    );        // 0x134

    LONG
    (CDECL
    *Close)(
        NITRO_PLUS_FILE_STREAM *Stream
    );         // 0x138

    PVOID   NullStub[4];                                            // 0x13C

    BOOL
    (CDECL
    *CleanUp)(
        NITRO_PLUS_FILE_STREAM *Stream
    );       // 0x14C

    ULONG   MetaSize;                                               // 0x150
    PVOID   FileInfo;                                               // 0x154

//    PVOID MetaInfo;
} *PNITRO_PLUS_FILE_STREAM;

typedef struct
{
    PVOID   Unknown;
    ULONG   Version;
    ULONG   Hash[2];
    BYTE    IsCompressed;
    BYTE    IsEncrypted;
    USHORT  PadFor4;
    ULONG   EntryCount;
    ULONG   DirectoryCount;
    ULONG   FileCount;
    ULONG   Reserve[2];
    ULONG   EntrySize;

} *PNPA_HEADER_INFO;

typedef struct
{
    PSTR    FileName;           // 0x00
    ULONG   FileType;           // 0x04

    DUMMY_STRUCT(0x1C);

    ULONG   FileSize;           // 0x24

    DUMMY_STRUCT(0x58);

    ULONG   ShiftJisHash;       // 0x84

} *PNITRO_PLUS_FILE_ENTRY;

#pragma pack()

#endif // _NITROPLUS_H_b48726f8_7f7d_4b9a_bc62_77a0f4daaed5_
