#pragma comment(linker, "/ENTRY:DllEntryPoint")
#pragma comment(linker,"/MERGE:.text=.Sharu /SECTION:.Sharu,EWR")
#pragma comment(linker,"/MERGE:.rdata=.Sharu")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "msvcrt6.lib")

#define _CHAR_UNSIGNED

#include <Windows.h>
#include <Shlwapi.h>
#include "Plugin.h"

HWND	hwndOD;
TCHAR	szUddPath[MAX_PATH];

int WINAPI DllEntryPoint(HINSTANCE hInstance, unsigned long reason, void* lpReserved)
{
	return TRUE;
}

extc int _export cdecl ODBG_Pluginmenu(int origin, char data[4096], void *item)
{
	if (origin!=PM_MAIN)
	{
		return 0;                          // No pop-up menus in OllyDbg's windows
	}

	lstrcpyA(data, "0 &Clear|1 &Explore, 2 &About");
	return 1;
};


extc void _export cdecl ODBG_Pluginaction(int origin, int action, void *item)
{
	if (origin != PM_MAIN)
	{
		return;
	}
	enum ACTION {CLEAR, OPEN, ABOUT};

	HANDLE hFind;
	WIN32_FIND_DATA wfd;

	switch (action)
	{
    case CLEAR:
		if (szUddPath[0] == 0) break;

		{
			TCHAR *szExt[] = {"*.bak", "*.udd"}, szFile[MAX_PATH];

			for (int i = 0; i != sizeof(szExt) / sizeof(*szExt); ++i)
			{
				wsprintf(szFile, "%s\\%s", szUddPath, szExt[i]);
				hFind = FindFirstFile(szFile, &wfd);
				if (hFind == INVALID_HANDLE_VALUE)
				{
					continue;
				}
				do
				{
					wsprintf(szFile, "%s\\%s", szUddPath, wfd.cFileName);
					DeleteFile(szFile);
				} while(FindNextFile(hFind, &wfd));
			}
		}
		break;

    case OPEN:		
		if (szUddPath[0] == 0) break;
		ShellExecute(hwndOD, NULL, szUddPath, NULL, NULL, SW_SHOW);
		break;

    case ABOUT:
		MessageBox(hwndOD, "Clear UDD by Sharu", "About", 0x40);
		break;
	};
};

extc int _export cdecl ODBG_Plugindata(char shortname[32])
{
	lstrcpyA(shortname, "Clear UDD");
	return PLUGIN_VERSION;
};

extc int _export cdecl ODBG_Plugininit(int ollydbgversion, HWND hw, ulong *features)
{
	hwndOD = hw;
	GetModuleFileName(NULL, szUddPath, sizeof(szUddPath));
	PathRemoveFileSpec(szUddPath);
	lstrcat(szUddPath, "\\ollydbg.ini");
	if (0 == GetPrivateProfileString("History", 
					"UDD path", szUddPath, szUddPath, sizeof(szUddPath), szUddPath))
	{
		szUddPath[0] = 0;
	}
	return 0;
};