#pragma comment(linker, "/ENTRY:main")
#pragma comment(linker, "/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker, "/SECTION:.Amano,ERW /MERGE:.text=.Amano")

#include "SafePacker.h"
#include "MyLibraryUser.cpp"

class SafePacker : public SafePackerImpl<SafePacker>
{
    ;
};

ForceInline Void main2(Int argc, WChar **argv)
{
    PRTL_USER_PROCESS_PARAMETERS UserProcessParameter;

    UserProcessParameter = (PRTL_USER_PROCESS_PARAMETERS)AllocateMemory(Nt_CurrentPeb()->ProcessParameters->MaximumLength + 4);
    CopyMemory(UserProcessParameter, Nt_CurrentPeb()->ProcessParameters, Nt_CurrentPeb()->ProcessParameters->Length);
    *(PULONG_PTR)PtrAdd(UserProcessParameter, UserProcessParameter->MaximumLength - 4) = -1;
    Nt_CurrentPeb()->ProcessParameters = UserProcessParameter;

    if (--argc == 0)
        return;

    SafePacker sp;

    do
    {
        sp.Auto(*++argv);
    } while (--argc);
}

int __cdecl main(Int argc, WChar **argv)
{
    getargsW(&argc, &argv);
    main2(argc, argv);
    ReleaseArgv(argv);
    return Nt_ExitProcess(0);
}
