#include "Babylon.h"
#include "ID.h"

#define ____________________MENU_SEPARATOR____________________ { { 0 }, NULL, MF_SEPARATOR },

/************************************************************************/
/* 主程序菜单                                                           */
/************************************************************************/
SMenuItem Menu_File[] = 
{
    { { FCONTROL|FVIRTKEY, 'I', IDM_FILE_SCRLIST }, _T("脚本列表(&I)...") },
    { { FCONTROL|FVIRTKEY, 'O', IDM_FILE_OPENSCR }, _T("打开脚本(&O)...") },
    { { FALT|FVIRTKEY,     'C', IDM_FILE_CLOSE   }, _T("关闭文件(&C)...") },

    ____________________MENU_SEPARATOR____________________

    { { FVIRTKEY, VK_ESCAPE, ID_EXIT }, _T("退出(&X)") },
};

SMenuItem Menu_Main[] =
{
    { { FROOTMENU,          0,     ID_POPUP }, _T("文件(&F)"), MF_POPUP, Menu_File, countof(Menu_File) },
    { { FROOTMENU|FVIRTKEY, VK_F1, ID_ABOUT }, _T("关于(&H)") },
};

DWORD dwMenuCount = countof(Menu_Main);

#undef ____________________MENU_SEPARATOR____________________