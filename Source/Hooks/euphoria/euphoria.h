#ifndef _EUPHORIA_H_038f598b_2b11_4635_bc9d_36862fa94178
#define _EUPHORIA_H_038f598b_2b11_4635_bc9d_36862fa94178

#include "pragma_once.h"
#include "my_headers.h"
#include "../../Unpacker/SafePack/SafePackReader/SafePackReader.h"

#define YURIS_GLOBAL_INFO_MAGIC   TAG4('YGIM')
#define COMPARE_CONST(v1, v2)     (_rotl((v1), 12) == _rotl((v2), 12))

#define EXE_ENTRY_POINT  0x458469
//#define EXE_EP  0x403858

typedef PVOID (CDECL *malloc_routine)(ULONG Size);
typedef PVOID (CDECL *free_routine)(ULONG Size);

#pragma pack(1)

enum YU_RIS_STORAGE_TYPE
{
    STORAGE_DISK    = 1,
    STORAGE_YPF,
};

typedef struct
{
    ULONG   Size;
    PVOID   Buffer;
    BYTE    StorageType;
    BYTE    FileType;
    DUMMY_STRUCT(2);
    ULONG   FileIndex;
    ULONG   PacIndex;
    ULONG   FileInfoOffsetOfYpf;
    ULONG   Unknown[3];
} YU_RIS_LOAD_FILE_INFO;

struct YU_RIS_GLOBAL_INFO : public RTL_THREAD_FRAME
{
    malloc_routine      malloc;
    free_routine        free;
    CSafePackReader    *PackReader;
    ULONG_PTR           LoadFileHookOffset;

    NTSTATUS
    (CDECL *LoadFileFunc)(
        YU_RIS_LOAD_FILE_INFO  *Info,
        PCSTR                   FileName,
        BOOL                    Unknown,
        bool FileInfoInitialized
    );  // 0044E648
};

typedef struct
{
    ULONG               Flags;
    YU_RIS_GLOBAL_INFO *GlobalInfo;
} FAKE_GLOBAL_INFO;

#pragma pack()

#define RVA_MALLOC  (0x55A6C)
#define RVA_FREE    (0x5664D)

#endif // _EUPHORIA_H_038f598b_2b11_4635_bc9d_36862fa94178
