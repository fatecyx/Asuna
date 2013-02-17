#ifndef _BINARYSPLITTERMSG_H_
#define _BINARYSPLITTERMSG_H_

#include "pragma_once.h"
#include <Windows.h>

#define MAX_PASSWORD_LENGTH 1024

enum
{
    WM_APP_MSG_FIRST = WM_APP,

    WM_APP_SPLIT,
    WM_APP_VERIFY,
    WM_APP_MERGE,

    WM_APP_FORCE_STOP,

    WM_APP_MSG_LAST,
};

#define DLG_SPLIT_STRING_BTN_SPLIT                  _T("分割(&S)")
#define DLG_SPLIT_STRING_BTN_STOP                   _T("停止(&S)")

#define DLG_MERGE_STRING_BTN_OPEN                   _T("打开(&M)")
#define DLG_MERGE_STRING_BTN_MERGE                  _T("合并(&M)")
#define DLG_MERGE_STRING_BTN_STOP                   DLG_SPLIT_STRING_BTN_STOP

#define CTRL_ERR_STRING_NO_ERROR                    _T("操作成功完成")

#define CTRL_ERR_STRING_UNKNOWN_ERROR               _T("未知错误")
#define CTRL_ERR_STRING_INVALID_SLICE_SIZE          _T("无效的分卷大小")
#define CTRL_ERR_STRING_INVALID_INPUT_NAME          _T("无效的源文件")
#define CTRL_ERR_STRING_INVALID_OUPUT_NAME          _T("无效的目标文件")
#define CTRL_ERR_STRING_OUTPUT_ALREADY_EXIST_ASK    _T("目标文件已存在, 确定要覆盖吗?")

#define CTRL_ERR_STRING_FAILED_FILE_NOT_FOUND       _T("找不到文件")
#define CTRL_ERR_STRING_FAILED_OPEN_FILE            _T("打开文件失败")
#define CTRL_ERR_STRING_FAILED_CREATE_FILE          _T("创建文件失败")
#define CTRL_ERR_STRING_FAILED_GET_SIZE             _T("获取文件大小失败")
#define CTRL_ERR_STRING_FAILED_READ_FILE            _T("读取文件失败")
#define CTRL_ERR_STRING_FAILED_WRITE_FILE           _T("写入文件失败")
#define CTRL_ERR_STRING_FAILED_CLOSE_FILE           _T("关闭文件失败")
#define CTRL_ERR_STRING_FAILED_IOCP_CREATE          _T("创建IO完成端口失败")
#define CTRL_ERR_STRING_FAILED_IOCP_BIND_DEVICE     _T("关联设备到IO完成端口失败")
#define CTRL_ERR_STRING_FAILED_IOCP_GET_STATUS      _T("GetQueuedCompletionStatus() 失败")
#define CTRL_ERR_STRING_FAILED_QUEUE_ITEM           _T("QueueUserWorkItem() 失败")
#define CTRL_ERR_STRING_FAILED_OUT_OF_MEMORY        _T("没有足够的内存进行此操作")
#define CTRL_ERR_STRING_FAILED_INVALID_PARAM        _T("无效的参数")
#define CTRL_ERR_STRING_FAILED_FILE_SIZE_ZERO       _T("指定文件大小为0")
#define CTRL_ERR_STRING_FAILED_INVALID_SLICE_SIZE   _T("无效的分卷大小")
#define CTRL_ERR_STRING_FAILED_INVALID_FILE_SIZE    _T("无效的文件大小")
#define CTRL_ERR_STRING_FAILED_INVALID_FORMAT       _T("无效的分割文件")
#define CTRL_ERR_STRING_FAILED_NOT_FIRST            _T("不是第一个分卷")
#define CTRL_ERR_STRING_FAILED_INVALID_PASSWORD     _T("密码错误")
#define CTRL_ERR_STRING_FAILED_PART_FILE_CORRUPT    _T("文件已损坏")

#define BS_ERR_STRING_FAILED_OPEN_FILE              CTRL_ERR_STRING_FAILED_OPEN_FILE
#define BS_ERR_STRING_FAILED_READ_FILE              CTRL_ERR_STRING_FAILED_READ_FILE
#define BS_ERR_STRING_FAILED_INVALID_FORMAT         CTRL_ERR_STRING_FAILED_INVALID_FORMAT
#define BS_ERR_STRING_FAILED_NOT_FIRST              CTRL_ERR_STRING_FAILED_NOT_FIRST
#define BS_ERR_STRING_FAILED_INVALID_PASSWORD       CTRL_ERR_STRING_FAILED_INVALID_PASSWORD
#define BS_ERR_STRING_CONFIRM_TO_OVERWRITE          CTRL_ERR_STRING_OUTPUT_ALREADY_EXIST_ASK

#endif // _BINARYSPLITTERMSG_H_