//#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "UIMain.h"
#include "my_commsrc.h"
#include "../Internal/CG_GUID.c"

OVERLOAD_CPP_NEW_WITH_HEAP(CMem::GetGlobalHeap())

CG_API
CGSTATUS
CG_METHOD_CALLTYPE
CreateInterface(
    interface ICGCoreBase   *pCore,
    ICGUnknown              *pUnknownOuter,
    REFIID                   InterfaceId,
    PVOID                   *ppvObject
)
{
    CGSTATUS    Status;
    CCGUICtrl  *pUiCtrl;

    if (ppvObject == NULL)
        return STATUS_INVALID_PARAMETER_3;

    *ppvObject = NULL;
    if (pUnknownOuter != NULL && InterfaceId != IID_IUnknown)
        return STATUS_INVALID_PARAMETER_2;

    pUiCtrl = new CCGUICtrl(pCore, pUnknownOuter);
    if (pUiCtrl == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    Status = pUiCtrl->NonDelegatingQueryInterface(InterfaceId, ppvObject);
    if (!CG_SUCCESS(Status))
        delete pUiCtrl;

    pUiCtrl->NonDelegatingRelease();

    return Status;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, ULONG Reason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(lpReserved);

    switch (Reason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hInstance);
            MyLib_Initialize();
            break;

        case DLL_PROCESS_DETACH:
            MyLib_UnInitialize();
            break;
    }

    return TRUE;
}
