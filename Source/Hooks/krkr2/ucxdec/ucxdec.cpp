#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "MyLibraryUser.h"
#include "MyLibraryUser.cpp"
#include "../compbin2h/ucidec.h"
#include "../compbin2h/ucadec.h"

#pragma comment(linker, "/EXPORT:UCIDecode=ucidec.UCIDecode")
#pragma comment(linker, "/EXPORT:UCIFree=ucidec.UCIFree")
#pragma comment(linker, "/EXPORT:UCIFree=ucidec.UCIFree")
#pragma comment(linker, "/EXPORT:GetPicture=ucidec.GetPicture")
#pragma comment(linker, "/EXPORT:GetPictureInfo=ucidec.GetPictureInfo")
#pragma comment(linker, "/EXPORT:GetPluginInfo=ucidec.GetPluginInfo")
#pragma comment(linker, "/EXPORT:IsSupported=ucidec.IsSupported")

#pragma comment(linker, "/EXPORT:UCADecode=ucadec.UCADecode")
#pragma comment(linker, "/EXPORT:UCADecode2=ucadec.UCADecode2")
#pragma comment(linker, "/EXPORT:UCAFree=ucadec.UCAFree")

typedef struct
{
    ULONG OriginalSize;
    BYTE  Buffer[1];

} *PCOMPRESS_DATA;

BOOL UnInitialize(PVOID BaseAddress)
{
    UNREFERENCED_PARAMETER(BaseAddress);

    MemoryAllocator::DestroyGlobalHeap();

    return FALSE;
}

NTSTATUS
LoadCompressedDll(
    PCOMPRESS_DATA  CompressData,
    ULONG           DataSize,
    PUNICODE_STRING DllName,
    PVOID          *ModuleBase
)
{
    PVOID       Buffer;
    ULONG       Size;
    NTSTATUS    Status;

    Size = CompressData->OriginalSize;
    Buffer = MemoryAllocator::AllocateMemory(Size);
    if (Buffer == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    Status = UCL_NRV2E_Decompress(
                CompressData->Buffer,
                DataSize,
                Buffer,
                &Size
             );

    if (!Status)
    {
        MemoryAllocator::FreeMemory(Buffer);
        return STATUS_UNSUCCESSFUL;
    }

    Status = LoadDllFromMemory(Buffer, Size, DllName, ModuleBase);

    MemoryAllocator::FreeMemory(Buffer);

    return Status;
}

BOOL Initialize(PVOID BaseAddress)
{
    PVOID           ModuleBase;
    NTSTATUS        Status;
    UNICODE_STRING  DllName;
    ULONG           Length;
    PLDR_MODULE     LdrModule;
    WCHAR           DllNameBuffer[MAX_NTPATH];

    UNREFERENCED_PARAMETER(BaseAddress);

    if (MemoryAllocator::CreateGlobalHeap() == NULL)
        return FALSE;

    LdrModule = Nt_FindLdrModuleByHandle(&__ImageBase);

    Length = LdrModule->FullDllName.Length - LdrModule->BaseDllName.Length;
    CopyMemory(DllNameBuffer, LdrModule->FullDllName.Buffer, Length);
    Length /= sizeof(WCHAR);

    DllName.Buffer = DllNameBuffer;

    *(PULONG64)&DllNameBuffer[Length + 0] = TAG4W('ucid');
    *(PULONG64)&DllNameBuffer[Length + 4] = TAG4W('ec.d');
    *(PULONG64)&DllNameBuffer[Length + 8] = TAG2W('ll');

    DllName.Length          = (USHORT)(Length + CONST_STRLEN(L"ucidec.dll"));
    DllName.Length          = DllName.Length * sizeof(WCHAR);
    DllName.MaximumLength   = DllName.Length;

    if (Nt_IsPathExists(DllNameBuffer))
        Status = LdrLoadDll(NULL, 0, &DllName, &ModuleBase);
    else
        Status = LoadCompressedDll((PCOMPRESS_DATA)ucidec, sizeof(ucidec) - 4, &DllName, NULL);

    if (!NT_SUCCESS(Status))
        return FALSE;

    *(PULONG64)&DllNameBuffer[Length + 0] = TAG4W('ucad');
    
    if (Nt_IsPathExists(DllNameBuffer))
        Status = LdrLoadDll(NULL, 0, &DllName, &ModuleBase);
    else
        Status = LoadCompressedDll((PCOMPRESS_DATA)ucadec, sizeof(ucadec) - 4, &DllName, NULL);

    if (!NT_SUCCESS(Status))
        return FALSE;

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, PVOID Reserved)
{
    UNREFERENCED_PARAMETER(Reserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            return Initialize(hInstance) || UnInitialize(hInstance);

        case DLL_PROCESS_DETACH:
            UnInitialize(hInstance);
            break;
    }

    return TRUE;
}
