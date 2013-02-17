#include "stdafx.h"

#define IS_ATOM(_class) ((((ULONG)(_class)) & 0xFFFF0000) == 0)

VOID FreeString(PVOID String)
{
    FreeMemoryP(String);
}

PSTR WCharToMByte(PCWSTR Unicode, ULONG_PTR Length)
{
    PSTR AnsiString;

    if (Length == -1)
        Length = StrLengthW(Unicode);

    ++Length;
    Length *= sizeof(WCHAR);

    AnsiString = (PSTR)AllocateMemoryP(Length);
    if (AnsiString == NULL)
        return NULL;

    RtlUnicodeToMultiByteN(AnsiString, Length, NULL, Unicode, Length);

    return AnsiString;
}

PWSTR MByteToWChar(PCSTR AnsiString, ULONG_PTR Length)
{
    PWSTR Unicode;

    if (Length == -1)
        Length = StrLengthA(AnsiString);

    ++Length;

    Unicode = (PWSTR)AllocateMemoryP(Length * sizeof(WCHAR));
    if (Unicode == NULL)
        return NULL;

    RtlMultiByteToUnicodeN(Unicode, Length * sizeof(WCHAR), NULL, AnsiString, Length);

    return Unicode;
}

PSTR ClassWCharToMByte(PCWSTR Unicode)
{
    return IS_ATOM(Unicode) ? (PSTR)Unicode : WCharToMByte(Unicode);
}

PWSTR ClassMByteToWChar(PCSTR AnsiString)
{
    return IS_ATOM(AnsiString) ? (PWSTR)AnsiString : MByteToWChar(AnsiString);
}

PSTR TitleWCharToMByte(PCWSTR Unicode)
{
    if (Unicode[0] == 0xFFFF)
    {
        PSTR ResourceId = (PSTR)AllocateMemoryP(4);
        if (ResourceId == NULL)
            return NULL;

        ResourceId[0] = -1;
        *(PUSHORT)&ResourceId[1] = Unicode[1];
        ResourceId[3] = 0;

        return ResourceId;
    }

    return WCharToMByte(Unicode);
}

PWSTR TitleMByteToWChar(PCSTR AnsiString)
{
    if (AnsiString[0] == -1)
    {
        PWSTR ResourceId = (PWSTR)AllocateMemoryP(6);
        if (ResourceId == NULL)
            return NULL;

        ResourceId[0] = 0xFFFF;
        ResourceId[1] = *(PUSHORT)&AnsiString[1];
        ResourceId[2] = 0;

        return ResourceId;
    }

    return MByteToWChar(AnsiString);
}

BOOL FreeClass(PVOID ClassName)
{
    return IS_ATOM(ClassName) ? TRUE : FreeMemoryP(ClassName);
}

VOID InitEmptyLargeString(PLARGE_UNICODE_STRING String)
{
    ZeroMemory(String, sizeof(*String));
}

VOID InitStringFromLargeString(PANSI_STRING AnsiString, PLARGE_UNICODE_STRING LargeString)
{
    AnsiString->Length           = LargeString->Length;
    AnsiString->MaximumLength    = LargeString->MaximumLength;
    AnsiString->Buffer           = LargeString->AnsiBuffer;
}

VOID InitStringFromLargeString(PUNICODE_STRING UnicodeString, PLARGE_UNICODE_STRING LargeString)
{
    UnicodeString->Length           = LargeString->Length;
    UnicodeString->MaximumLength    = LargeString->MaximumLength;
    UnicodeString->Buffer           = LargeString->UnicodeBuffer;
}

PLARGE_UNICODE_STRING LargeStringDuplicate(PLARGE_UNICODE_STRING LargeString, PLARGE_UNICODE_STRING Destination)
{
    union
    {
        ANSI_STRING     Ansi;
        UNICODE_STRING  Unicode;
    };

    union
    {
        ANSI_STRING     NewAnsi;
        UNICODE_STRING  NewUnicode;
    };

    if (LargeString->Ansi)
        return NULL;

    InitStringFromLargeString(&Unicode, LargeString);
    if (NT_FAILED(RtlDuplicateUnicodeString(RTL_DUPSTR_ADD_NULL, &Unicode, &NewUnicode)))
        return NULL;

    Destination->Ansi           = FALSE;
    Destination->Length         = NewUnicode.Length;
    Destination->MaximumLength  = NewUnicode.MaximumLength;
    Destination->UnicodeBuffer  = NewUnicode.Buffer;

    return Destination;
}

PLARGE_UNICODE_STRING LargeStringAnsiToUnicode(PLARGE_UNICODE_STRING LargeAnsiString, PLARGE_UNICODE_STRING LargeUnicodeString)
{
    if (LargeAnsiString == NULL)
        return NULL;

    if (!LargeAnsiString->Ansi)
        return LargeStringDuplicate(LargeAnsiString, LargeUnicodeString);

    ANSI_STRING     AnsiString;
    UNICODE_STRING  UnicodeString;

    AnsiString.Buffer          = LargeAnsiString->AnsiBuffer;
    AnsiString.Length          = LargeAnsiString->Length;
    AnsiString.MaximumLength   = LargeAnsiString->MaximumLength;

    if (NT_FAILED(RtlAnsiStringToUnicodeString(&UnicodeString, &AnsiString, TRUE)))
        return NULL;

    LargeUnicodeString->Ansi            = FALSE;
    LargeUnicodeString->Length          = UnicodeString.Length;
    LargeUnicodeString->MaximumLength   = UnicodeString.MaximumLength;
    LargeUnicodeString->Buffer          = (ULONG64)UnicodeString.Buffer;

    return LargeUnicodeString;
}

VOID FreeLargeString(PLARGE_UNICODE_STRING LargeString)
{
    union
    {
        ANSI_STRING     Ansi;
        UNICODE_STRING  Unicode;
    };

    if (LargeString->Buffer == NULL)
        return;

    if (LargeString->Ansi)
    {
        Ansi.Length         = LargeString->Length;
        Ansi.MaximumLength  = LargeString->MaximumLength;
        Ansi.Buffer         = LargeString->AnsiBuffer;

        RtlFreeAnsiString(&Ansi);
    }
    else
    {
        Unicode.Length          = LargeString->Length;
        Unicode.MaximumLength   = LargeString->MaximumLength;
        Unicode.Buffer          = LargeString->UnicodeBuffer;

        RtlFreeUnicodeString(&Unicode);
    }
}

PLARGE_UNICODE_STRING CaptureAnsiWindowName(PLARGE_UNICODE_STRING WindowName, PLARGE_UNICODE_STRING UnicodeWindowName)
{
    InitEmptyLargeString(UnicodeWindowName);

    if (WindowName == NULL || WindowName->Buffer == NULL)
        return NULL;

    if (WindowName->UnicodeBuffer[0] == 0xFFFF)
    {
        WCHAR                   Buffer[0x10];
        ULONG_PTR               Length;
        LARGE_UNICODE_STRING    TitleAsResourceId;

        TitleAsResourceId.Ansi = FALSE;

        Length = WindowName->Ansi ? 3 : 4;

        CopyMemory(Buffer, WindowName->AnsiBuffer + WindowName->Ansi, Length);

        TitleAsResourceId.Length        = Length;
        TitleAsResourceId.MaximumLength = Length;
        TitleAsResourceId.Buffer        = (ULONG64)Buffer;

        return LargeStringDuplicate(&TitleAsResourceId, UnicodeWindowName);
    }

    return LargeStringAnsiToUnicode(WindowName, UnicodeWindowName);
}
