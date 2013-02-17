#pragma comment(linker,"/MERGE:.text=.Kanade /SECTION:.Kanade,ERW")
#pragma comment(linker,"/MERGE:.rdata=.Kanade")
#pragma comment(linker,"/MERGE:.data=.Kanade")

#include "haruuru.h"
#include "my_mem.h"

HKEY hInvalid = (HKEY)-2;
CHAR szConfigFile[] = ".\\haruuru.ini";
CHAR szConfigSection[] = "Kanade";

int WINAPI MyEnumFontFamiliesExA(HDC hdc, LPLOGFONTA lpLogfont, FONTENUMPROCA lpProc, LPARAM lParam, DWORD dwFlags)
{
    lpLogfont->lfCharSet = GB2312_CHARSET;
    return EnumFontFamiliesExA(hdc, lpLogfont, lpProc, lParam, dwFlags);
}

HFONT WINAPI MyCreateFontIndirectA(LPLOGFONTA lplf)
{
    lplf->lfCharSet = GB2312_CHARSET;
//    lstrcpyA(lplf->lfFaceName, "ºÚÌå");
    return CreateFontIndirectA(lplf);
}

LONG WINAPI MyRegOpenKeyExA(HKEY hKey, LPCSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult)
{
    if (!lstrcmpiA(lpSubKey, "Software\\Will\\haruuru"))
    {
        *phkResult = hInvalid;
        return NO_ERROR;
    }

    return RegOpenKeyExA(hKey, lpSubKey, ulOptions, samDesired, phkResult);
}

LONG WINAPI MyRegQueryValueExA(HKEY hKey, LPCSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
    if (hKey != hInvalid)
        return RegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);

    CHAR buffer[0x200];
    DWORD recv;

    if (!lstrcmpiA(lpValueName, "InstallDir") || !lstrcmpiA(lpValueName, "InstallSrc"))
    {
        recv = GetModuleFileNameA(NULL, (LPSTR)lpData, *lpcbData);
        while (lpData[--recv] != '\\');
        lpData[recv] = 0;
        return NO_ERROR;
    }
    else if (!lstrcmpiA(lpValueName, "InstallType"))
    {
        *(LPDWORD)lpData = 2;
        return NO_ERROR;
    }

    memset(buffer, 0, min(sizeof(buffer), *lpcbData * 2));
    recv = GetPrivateProfileStringA(szConfigSection, lpValueName, buffer, buffer, sizeof(buffer), szConfigFile);
    if (recv == 0)
        return NO_ERROR;

    if (!lstrcmpiA(lpValueName, "FontName"))
    {
        memcpy(lpData, buffer, recv + 1);
        return NO_ERROR;
    }

    for (DWORD i = 0, j = *lpcbData * 2; i < j; )
    {
        BYTE v, b = buffer[i++];

        if (b >= '0' && b <= '9') b -= '0';
        else if (b >= 'A' && b <= 'Z') b = b - 'A' + 10;
        else if (b >= 'a' && b <= 'z') b = b - 'a' + 10;

        v = b;

        b = buffer[i++];

        if (b)
        {
            if (b >= '0' && b <= '9') b -= '0';
            else if (b >= 'A' && b <= 'Z') b = b - 'A' + 10;
            else if (b >= 'a' && b <= 'z') b = b - 'a' + 10;
            v = (v << 4) | b;
        }

        *lpData++ = v;
    }

    return NO_ERROR;
}

LONG WINAPI MyRegSetValueExA(HKEY hKey, LPCTSTR lpValueName, DWORD Reserved, DWORD dwType, const BYTE* lpData, DWORD cbData)
{
    if (hKey != hInvalid)
        return RegSetValueExA(hKey, lpValueName, Reserved, dwType, lpData, cbData);

    CHAR *pbuf, buffer[0x200];
/*
    if (!lstrcmpiA(lpValueName, "InstallDir") || !lstrcmpiA(lpValueName, "InstallSrc"))
        return NO_ERROR;
*/
    if (!lstrcmpiA(lpValueName, "FontName"))
    {
        WritePrivateProfileStringA(szConfigSection, lpValueName, (LPSTR)lpData, szConfigFile);
        return NO_ERROR;
    }

    pbuf = buffer;
    for (DWORD i = 0; i != cbData; ++i)
    {
//        pbuf += wsprintfA(pbuf, "%02X", *lpData++);
        BYTE v, b = *lpData++;

        v = (b >> 4) & 0xF;
        if (v >= 0 && v <= 9) v += '0';
        else v = v + 'A' - 10;
        *pbuf++ = v;

        v = b & 0xF;
        if (v >= 0 && v <= 9) v += '0';
        else v = v + 'A' - 10;
        *pbuf++ = v;
    }

    *pbuf = 0;
    for (Int32 i = 2, j = pbuf - buffer - 1; ; ++i)
    {
        if (buffer[i] == buffer[i + 1])
            continue;
        else if (i == j)
        {
            if (buffer[0] == '0')
            {
                buffer[0] = buffer[1];
                buffer[1] = 0;
            }
            else
                buffer[2] = 0;
            break;
        }
        else
            break;
    }

    WritePrivateProfileStringA(szConfigSection, lpValueName, buffer, szConfigFile);

    return NO_ERROR;
}

LONG WINAPI MyRegCloseKey(HKEY hKey)
{
    if (hKey != hInvalid)
        return RegCloseKey(hKey);

    return NO_ERROR;
}
