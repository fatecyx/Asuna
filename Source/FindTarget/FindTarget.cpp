#pragma comment(linker,"/ENTRY:WinMain")
#pragma comment(linker, "/MERGE:.text=.Yumemi /SECTION:.Yumemi,ERW")
#pragma comment(linker, "/MERGE:.rdata=.Yumemi")
#pragma comment(linker, "/MERGE:.data=.Yumemi")

//#define _UNICODE
//#define UNICODE

#include <windows.h>
#include <tchar.h>
#include <shlobj.h>
#include "my_mem.h"

const static LPSTR MBTitle = (LPSTR)0x400179;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HRESULT	hResult;
	LPWSTR	lpszPathLink;
	TCHAR	szPathtoFile[MAX_PATH];
	IShellLink*		pShellLink   = NULL;
	IPersistFile*	pPersistFile = NULL;
	WIN32_FIND_DATA	findData;

	int argc;
	LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(),&argc);
	if (argc == 1)
	{
		LPSTR szMsgText = "Do you want to add \"Open File &Location\" to right-click menu(link file only)?";
		if (MessageBox(NULL,szMsgText,LPCSTR(MBTitle),
			MB_OKCANCEL|MB_ICONINFORMATION) == IDOK)
		{
			HKEY hkey;
			TCHAR lpSubKey[] = _T("lnkfile\\Shell\\Open File Location\\command");
			if (RegCreateKey(HKEY_CLASSES_ROOT,lpSubKey,&hkey) == ERROR_SUCCESS)
			{
				int iLength;

                GetModuleFileName(NULL, szPathtoFile, sizeof(szPathtoFile));
				iLength = wsprintf(szPathtoFile, "%s%s", szPathtoFile, " \"%1\"");
				RegSetValueEx(hkey,NULL,0,REG_SZ, (PBYTE)szPathtoFile, iLength * sizeof(TCHAR));
				lpSubKey[33] = 0;
				RegCreateKey(HKEY_CLASSES_ROOT, lpSubKey, &hkey);
				if (RegSetValueEx(hkey,NULL,0,REG_SZ,
					(BYTE *)(szMsgText + 20),19) == ERROR_SUCCESS)
				{
					MessageBox(NULL,"Add successfully.", MBTitle,MB_ICONINFORMATION);
				}
				else
				{
					MessageBox(NULL,"Add failed.", MBTitle, MB_ICONINFORMATION);
				}
			}
		}
	}
	else while (--argc)
	{
		lpszPathLink = argv[argc];

		CoInitialize(NULL);
		hResult = CoCreateInstance(CLSID_ShellLink, NULL,
			CLSCTX_INPROC_SERVER, IID_IShellLink, (void **) &pShellLink);
		if (hResult == S_OK)
		{
			hResult = pShellLink->QueryInterface(IID_IPersistFile,(void **)&pPersistFile);
			if (hResult == S_OK)
			{
				hResult = pPersistFile->Load(lpszPathLink,0);
				pShellLink->GetPath(szPathtoFile, MAX_PATH, &findData, SLGP_UNCPRIORITY);

				pPersistFile->Release();

				STARTUPINFO si;
				PROCESS_INFORMATION pi;
				TCHAR szCmdLine[MAX_PATH + 32];

                si.cb = sizeof(si);
                ZeroMemory((PBYTE)&si.cb + sizeof(&si.cb), sizeof(si) - sizeof(si.cb));
				wsprintf(szCmdLine, "%s%s", "explorer /select,", szPathtoFile);
				if (szPathtoFile[0] != 0)
				{
					CreateProcess(NULL,
						szCmdLine,
						NULL,		// Process handle not inheritable.
						NULL,		// Thread handle not inheritable.
						FALSE,		// Set handle inheritance to FALSE.
						0,			// No creation flags.
						NULL,		// Use parent's environment block.
						NULL,		// Use parent's starting directory.
						&si,		// Pointer to STARTUPINFO structure.
						&pi);		// Pointer to PROCESS_INFORMATION structure.
				}
			}
			pShellLink->Release();
		}
        CoUninitialize();
	}

	ExitProcess(0);
}