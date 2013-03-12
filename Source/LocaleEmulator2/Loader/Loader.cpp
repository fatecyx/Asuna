#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Asuna,ERW /MERGE:.text=.Asuna")

#include "MyLibrary.cpp"
#include "../LocaleEmulator/LocaleEmulator.h"
#include "mlns.h"

ForceInline Void main2(Long_Ptr argc, WChar **argv)
{
    if (argc < 2)
        return;

    ULONG_PTR               Length;
    PWSTR                   DllFullPath, CurrentDirectory, CommandLine;
    PLDR_MODULE             Module;
    NTSTATUS                Status;
    UNICODE_STRING          CurrentDirectoryString;
    ML_PROCESS_INFORMATION  ProcessInfo;

    static WCHAR Dll[] = L"LocaleEmulator.dll";

    Module = FindLdrModuleByHandle(NULL);

    Length = Module->FullDllName.Length - Module->BaseDllName.Length;
    DllFullPath = (PWSTR)AllocStack(Length + sizeof(Dll));
    CopyMemory(DllFullPath, Module->FullDllName.Buffer, Length);
    CopyStruct(PtrAdd(DllFullPath, Length), Dll, sizeof(Dll));

    RtlCreateUnicodeString(&CurrentDirectoryString, argv[1]);

    *findnamew(CurrentDirectoryString.Buffer) = 0;
    CurrentDirectory = CurrentDirectoryString.Buffer[0] == 0 ? NULL : CurrentDirectoryString.Buffer;

    CommandLine = CurrentPeb()->ProcessParameters->CommandLine.Buffer;
    for (WCHAR end = CommandLine[0] == '"' ? '"' : ' '; *++CommandLine != end && CommandLine[0] != 0; );

    if (CommandLine[0] == 0)
    {
        CommandLine = NULL;
    }
    else
    {
        ++CommandLine;
        while (CommandLine[0] == ' ' || CommandLine[0] == '\t')
            ++CommandLine;
    }

    Status = CreateProcessWithDll(
                CPWD_BEFORE_KERNEL32,
                DllFullPath,
                argv[1],
                CommandLine,
                CurrentDirectory,
                CREATE_SUSPENDED,
                NULL,
                &ProcessInfo
            );

    RtlFreeUnicodeString(&CurrentDirectoryString);

    PrintConsoleW(L"%p\n", Status);
    if (NT_FAILED(Status))
    {
        Nt_Sleep(1000);
        return;
    }

    PLEPEB LePeb;

    LePeb = NULL;

    if (NT_SUCCESS(Status)) LOOP_ONCE
    {
        LePeb = OpenOrCreateLePeb(ProcessInfo.dwProcessId, TRUE);
        if (LePeb == NULL)
        {
            Status = STATUS_UNSUCCESSFUL;
            break;
        }

        static WCHAR FaceName[]     = L"MS Gothic";
        static WCHAR StandardName[] = L"@tzres.dll,-572";
        static WCHAR DaylightName[] = L"@tzres.dll,-572";

        LePeb->Leb.AnsiCodePage    = CP_SHIFTJIS;
        LePeb->Leb.OemCodePage     = CP_SHIFTJIS;
        LePeb->Leb.LocaleID        = 0x411;
        LePeb->Leb.DefaultCharset  = SHIFTJIS_CHARSET;

        CopyStruct(LePeb->Leb.DefaultFaceName, FaceName, sizeof(FaceName));

        LePeb->Leb.Timezone.Bias = -480;
        LePeb->Leb.Timezone.DaylightBias = 0;
        CopyStruct(LePeb->Leb.Timezone.StandardName, StandardName, sizeof(StandardName));
        CopyStruct(LePeb->Leb.Timezone.DaylightName, DaylightName, sizeof(DaylightName));

        LePeb->ooxxAddress = ProcessInfo.FirstCallLdrLoadDll;

        StrCopyW(LePeb->LeDllFullPath, DllFullPath);

        Status = ReadMemory(ProcessInfo.hProcess, PtrAdd(LePeb->ooxxAddress, 1), &LePeb->ooxxValue, 4);
        FAIL_BREAK(Status);

        Status = ZwResumeProcess(ProcessInfo.hProcess);
    }

    CloseLePeb(LePeb);

    if (NT_FAILED(Status))
    {
        ZwTerminateProcess(ProcessInfo.hProcess, Status);
    }

    ZwClose(ProcessInfo.hProcess);
    ZwClose(ProcessInfo.hThread);

    Ps::Sleep(1000);

    return;
}

int __cdecl main(Long_Ptr argc, wchar_t **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    ReleaseArgv(argv);
    Ps::ExitProcess(0);
}
