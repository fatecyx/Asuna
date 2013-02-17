#ifndef _CORE_H_96ff764a_6d4b_40c4_a535_9cfc43c19026
#define _CORE_H_96ff764a_6d4b_40c4_a535_9cfc43c19026

#include "pragma_once.h"
#include "../Internal/CG_Core.h"
#include "FileIo.H"
#include "Memory.h"
#include "MemoryI.h"
#include "FileIoI.h"

extern HANDLE g_HeapHandle;

inline PVOID CDECL operator new[](size_t Size)
{
    return RtlAllocateHeap(g_HeapHandle, 0, Size);
}

inline PVOID CDECL operator new(size_t Size)
{
    return operator new[](Size);
}

inline Void CDECL operator delete(PVOID pBuffer)
{
    if (pBuffer != NULL)
        RtlFreeHeap(g_HeapHandle, 0, pBuffer);
}

inline Void CDECL operator delete[](PVOID pBuffer)
{
    delete pBuffer;
}

class CCGCore : public CCGUnknownImpl<CCGCore>, public ICGCore
{
protected:
    CCGMemory           m_Memory;
    CCGFileIo           m_IO;
    CCGMemoryI         *m_pMemoryI;
    ICGUIMain          *m_pUI;
    ICGUnknown         *m_pUiInner;

public:
    CCGCore(ICGUnknown *pUnknwonOuter);
    ~CCGCore();

    CGSTATUS Run();

    CGSTATUS QueryInterface0(REFIID iid, PVOID *ppvObject);

    CGSTATUS StringCreate(PUNICODE_STRING DestinationString, LPCWSTR SourceString);
    CGSTATUS StringFree(PUNICODE_STRING UnicodeString);
    LONG     StringCompare(PUNICODE_STRING String1, PUNICODE_STRING String2, BOOL CaseInSensitive);

    CGSTATUS ProfileReadString  (LPCWSTR KeyName, PUNICODE_STRING Buffer, BOOL AllocateBuffer);
    CGSTATUS ProfileReadInt     (LPCWSTR KeyName, PLONG64 Buffer);
    CGSTATUS ProfileSaveString  (LPCWSTR KeyName, LPCWSTR Value);
    CGSTATUS ProfileSaveInt     (LPCWSTR KeyName, LONG64 Value);


    // ICGCore
    CGSTATUS STDCALL GetInterface        (REFIID iid, PVOID *ppvObject);

    CGSTATUS STDCALL CreateString        (PUNICODE_STRING DestinationString, LPCWSTR SourceString);
    CGSTATUS STDCALL FreeString          (PUNICODE_STRING UnicodeString);
    LONG     STDCALL CompareString       (PUNICODE_STRING String1, PUNICODE_STRING String2, BOOL CaseInSensitive);

    CGSTATUS STDCALL ReadProfileString   (LPCWSTR KeyName, PUNICODE_STRING Buffer, BOOL AllocateBuffer);
    CGSTATUS STDCALL ReadProfileInt      (LPCWSTR KeyName, PLONG64 Buffer);
    CGSTATUS STDCALL SaveProfileString   (LPCWSTR KeyName, LPCWSTR Value);
    CGSTATUS STDCALL SaveProfileInt      (LPCWSTR KeyName, LONG64 Value);

    CG_IUNKNOWN_IMPLEMENT(CCGCore);
};

#endif // _CORE_H_96ff764a_6d4b_40c4_a535_9cfc43c19026
