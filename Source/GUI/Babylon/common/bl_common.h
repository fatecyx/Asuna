#ifndef _BL_COMMON_H_
#define _BL_COMMON_H_

#include <Windows.h>
#include "my_headers.h"

#ifdef _DLL
    #define BL_API EXTC __declspec(dllexport)
#else
    #define BL_API EXTC __declspec(dllimport)
#endif

#define BL_STRING_ABOUT_MESSAGE    _T("Amano")
#define BL_STRING_CONFIG_FILE_NAME _T("Babylon.xml")
#define BL_STRING_SCRIPT_PATH      _T("script\\")
#define BL_STRING_PLUGIN_PATH      _T("plugin\\")

#define BL_FAILED(Result) (((Long)(Result)) < 0)
#define BL_SUCCEEDED(Result) (!BL_FAILED(Result))

enum // BLErrorCode
{
    BL_ERROR_SUCCEES = 0,

    BL_ERROR_BASE    = 0x80000000,

    BL_ERROR_UNKNOWN = BL_ERROR_BASE,
    BL_ERROR_INVALID_PARAMETER,
    BL_ERROR_INVALID_FORMAT,
    BL_ERROR_NOT_ENOUGH_BUFFER,
    BL_ERROR_IO_FAILED,
    BL_ERROR_OUT_OF_MEMORY,
};

inline PTChar BLNewString(PTChar pszString, ULong Length = -1)
{
    if (Length == -1)
        Length = StrLength(pszString);
    else
        ++Length;

    PTChar pStringBuffer = (PTChar)HeapAlloc(GetProcessHeap(), 0, (Length + 1) * sizeof(TChar));
    if (pStringBuffer != NULL)
    {
        memcpy(pStringBuffer, pszString, Length * sizeof(TChar));
        pStringBuffer[Length] = 0;
    }
    
    return pStringBuffer;
}

inline Void BLFreeString(PTChar &pszString)
{
    if (pszString != NULL)
    {
        HeapFree(GetProcessHeap(), 0, pszString);
        pszString = NULL;
    }
}

/*****************************************************************************
 *  导出类型
 *****************************************************************************/
enum EExportType
{
    BL_EXPORT_TYPE_UNKNOWN, // 未知文件
    BL_EXPORT_TYPE_IMAGE,   // 图片文件
    BL_EXPORT_TYPE_AUDIO,   // 音频文件
    BL_EXPORT_TYPE_PACK,    // 打包文件
    BL_EXPORT_TYPE_MODULE,  // 模型文件
    BL_EXPORT_TYPE_TEXT,    // 文本文件
    BL_EXPORT_TYPE_BINARY,  // 普通文件
};

/************************************************************************/
/* 文件信息结构, 插件填写                                               */
/************************************************************************/
typedef struct
{
    // 图片
    UInt32   Width;       // 图片宽
    UInt32   Height;      // 图片高

    // 公用
    UInt32   Count;       // 子文件个数
                          // 图片文件: 帧数
                          // 打包文件: 子文件个数
                          // 模型文件: 部件个数

    UInt32   Size;        // 文件大小
    UInt32   Type;        // 导出文件类型
    PWChar*  ppInfo;      // 文件信息
                          // 打包文件: 子文件名列表
                          // 普通文件: 第一个为说明串
                          //           第二个为扩展名
} SBLFileInfo;

/************************************************************************/
/* 文件读取参数结构, 主程序填写                                         */
/************************************************************************/
typedef struct
{
    LPCVoid data;       // 文件数据
    UInt32  size;       // =0 表示 data 为文件名(WChar)
                        // 导入时这里是导入文件的大小
    PVoid   pExtra;     // 辅助数据
    UInt32  pakIndex;   // 包文件索引号(在TreeView里的顺序, 可选)
    UInt32  fileIndex;  // 子文件索引号
    UInt32  head;       // 文件起始偏移
    UInt32  tail;       // 文件结束偏移
    PWChar  path;       // 磁盘文件的全路径文件名
                        // 包/包内文件为 NULL
    PWChar  node;       // TreeView 的节点名
                        // 包文件时为选中文件的节点名
                        // 可以用于在读文件时修改显示的文件名
    HWND    hWnd;       // 主窗口的句柄
} SBLFileParam;

#endif /* _BL_COMMON_H_ */
