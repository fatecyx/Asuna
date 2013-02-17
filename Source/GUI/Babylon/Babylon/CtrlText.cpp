#include "CtrlText.h"
#include "ID.h"

SCtrlInfo g_ciCheckBox[] = 
{
    { _T("禁用音频播放功能(&9)"),           IDB_AUDIO_PLAY }, 
    { _T("标准图片格式也通过插件转换输出"), IDB_IMAGE_CONVERT },
};

const DWORD g_dwCheckBox = countof(g_ciCheckBox);

SCtrlInfo g_ciRButton[] = 
{
    { _T("上一帧(&1)"),   IDB_PREV_FRAME  }, 
    { _T("下一帧(&2)"),   IDB_NEXT_FRAME  }, 
    { _T("RGB(&3)"),      IDB_VIEW_RGB    }, 
    { _T("Alpha(&4)"),    IDB_VIEW_ALPHA  }, 
    { _T("导出文件(&E)"), IDB_EXPORT      }, 
    { _T("全部导出(&A)"), IDB_EXPORT_ALL  }, 
    { _T("插件列表"),     IDB_PLUGIN_LIST }, 
};

const DWORD g_dwRButton = countof(g_ciRButton);

SCtrlInfo g_ciLButton[] = 
{
    { _T("播放(&6)"), IDB_PLAY  }, 
    { _T("停止(&7)"), IDB_STOP  }, 
    { _T("暂停(&8)"), IDB_PAUSE }, 
};

const DWORD g_dwLButton = countof(g_ciLButton);