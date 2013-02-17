#include "Test_Lib.h"

typedef struct
{
    DWORD           grAttrs;        // attributes
    LPCSTR          szDllName;      // pointer to dll name
    HMODULE *       phModule;       // address of module handle
    PImgThunkData   pIAT;           // address of the IAT
    PCImgThunkData  pINT;           // address of the INT
    PCImgThunkData  pBoundIAT;      // address of the optional bound IAT
    PCImgThunkData  pUnloadIAT;     // address of optional copy of original IAT
    DWORD           dwTimeStamp;    // 0 if not bound,
    // O.W. date/time stamp of DLL bound to (Old BIND)
} ImgDelayDescrInternal2;

template<class Type>
Type RVAToPointer(RVA Value, ULONG_PTR ImageBase)
{
    return (Type)((ULONG_PTR)Value + ImageBase);
}

EXTC FARPROC WINAPI __delayLoadHelper2(PCImgDelayDescr pidd, FARPROC *ppfnIATEntry)
{
    LPCSTR    lpDllName, lpProcName;
    HMODULE   hModule;
    register ULONG_PTR ImageBase;
    PIMAGE_THUNK_DATA pThunkData;
    WCHAR szDllName[MAX_PATH];

    *ppfnIATEntry = NULL;

    if (!TEST_BITS(pidd->grAttrs, dlattrRva))
        return NULL;

    ImageBase = (ULONG_PTR)&__ImageBase;
    lpDllName = (LPCSTR)(ImageBase + pidd->rvaDLLName);

    if (MultiByteToWideChar(CP_ACP, 0, lpDllName, -1, szDllName, countof(szDllName)) == 0)
        return NULL;

    hModule = LoadLibraryExW(szDllName, NULL, 0);
    if (hModule == NULL)
        return NULL;

    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_PIN|GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)hModule, &hModule);

    pThunkData = (PIMAGE_THUNK_DATA)(ImageBase + pidd->rvaINT);
    pThunkData += ppfnIATEntry - ((FARPROC *)(ImageBase + pidd->rvaIAT));
    if ((LONG_PTR)pThunkData->u1.AddressOfData < 0)
        lpProcName = (LPCSTR)(WORD)pThunkData->u1.AddressOfData;
    else
        lpProcName = (LPCSTR)((ULONG_PTR)pThunkData->u1.AddressOfData + ImageBase + 2);

    *ppfnIATEntry = GetProcAddress(hModule, lpProcName);

    return *ppfnIATEntry;
}