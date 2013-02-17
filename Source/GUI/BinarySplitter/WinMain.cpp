#pragma comment(linker,"/ENTRY:tWinMain")
#pragma comment(linker,"/SECTION:.text,ERW /MERGE:.rdata=.text /MERGE:.data=.text")
#pragma comment(linker,"/SECTION:.Amano,ERW /MERGE:.text=.Amano")
#pragma comment(lib, "comctl32.lib")

#include <Windows.h>
#include "ViewSplitter.h"
#include "ControllerSplitter.h"
#include "ModelSplitter.h"
#include "Mem.cpp"
#include "sha256.h"

class Encoder : public CModelSplitter
{
public:
    using CModelSplitter::Encrypt;
    using CModelSplitter::Decrypt;
};

ForceInline UInt WinMain2(HINSTANCE hInstance, HINSTANCE hPrevInstance, PTChar lpCmdLine, Int nCmdShow)
{
/*
    CViewSplitter bs;
    CModelSplitter model;
    CControllerSplitter ctrl;
*/
    ULONG Key[8];
    sha256_ctx s_ctx;
    aes_encrypt_ctx aes_context;
    UCHAR szID[] =
    {
		0xa5, 0xb0, 0x01, 0x4a, 0x3a, 0xde, 0xc0, 0x24, 0x2f, 0x29, 0x66, 0x0a, 0x42, 0xe9, 0xc9, 0xda,
        0xf7, 0x9f, 0xf9, 0x1e
    };
    CHAR szKey[] = "Key";

    sha256_init(&s_ctx);
    sha256((PBYTE)szKey, sizeof(szKey) - 1, (PBYTE)Key);

    Key[0] ^= Key[4];
    Key[1] ^= Key[5];
    Key[2] ^= Key[6];
    Key[3] ^= Key[7];

    aes_encrypt_key128(Key, &aes_context);

    Encoder enc;
    enc.Decrypt(&aes_context, szID, sizeof(szID), Key);

    UNUSED_VARIABLE(hPrevInstance);
    UNUSED_VARIABLE(lpCmdLine);
    UNUSED_VARIABLE(nCmdShow);

    return 0;
/*
    ctrl.AttachModel(&model);
    ctrl.AttachView(&bs);
    return ctrl.Execute(hInstance);
*/
}

Int WINAPI tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PTChar lpCmdLine, Int nCmdShow)
{
    TChar end;

    UNUSED_VARIABLE(hInstance);
    UNUSED_VARIABLE(hPrevInstance);
    UNUSED_VARIABLE(lpCmdLine);
    UNUSED_VARIABLE(nCmdShow);

    lpCmdLine = GetCommandLine();
    end = *lpCmdLine++ == '\"' ? '\"' : ' ';
    while (*lpCmdLine && *lpCmdLine != end) ++lpCmdLine;
    if (*++lpCmdLine)
    {
      while (*lpCmdLine == ' ' || *lpCmdLine == '\t') ++lpCmdLine;
    }
    ExitProcess(WinMain2(GetModuleHandle(NULL), 0, lpCmdLine, SW_SHOWDEFAULT));
}