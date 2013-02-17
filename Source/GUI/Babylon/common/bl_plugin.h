#ifndef _BL_PLUGIN_H_
#define _BL_PLUGIN_H_

#include "bl_common.h"

enum EPluginRet
{
    BL_RET_PLG_NOERROR, 
    BL_RET_PLG_UNSUPPORT, 
};

enum EBLPluginCaps
{
    BL_PLUGIN_CAPS_UNKNOWN = 0, 
};

/************************************************************************/
/* 插件类型                                                             */
/************************************************************************/
enum EBLPuginType
{
    BL_PLUGIN_TYPE_INVALID = 0x00000000,   // 无效插件
    BL_PLUGIN_TYPE_IMAGE   = 0x00000001,   // 图片插件
    BL_PLUGIN_TYPE_AUDIO   = 0x00000002,   // 音频插件
    BL_PLUGIN_TYPE_UNPACK  = 0x00000004,   // 解包插件
    BL_PLUGIN_TYPE_PACK    = 0x00000008,   // 封包插件
    BL_PLUGIN_TYPE_MODULE  = 0x00000010,   // 模型插件
    BL_PLUGIN_TYPE_DECODE  = 0x00000020,   // 解码插件
    BL_PLUGIN_TYPE_ENGINE  = 0x00000040,   // 引擎插件
};

typedef struct
{
    PCTChar pCopyright;
    PCTChar pPluginDescription;
    PCTChar pRevision;
    PCTChar pAuthor;
    PCTChar pExtraInfo;
    UInt32  PluginType;
    UInt32  Capability;
} SBLPluginInfo;

interface IBLPlugin
{
    virtual Bool   STDCALL GetFileInfo(IN const SBLFileParam *pFileParam, OUT SBLFileInfo *pFileInfo);
    virtual UInt32 STDCALL GetFileData(IN const SBLFileParam *pFileParam, LPVoid lpBuffer, UInt32 BufferSize);
    virtual Void   STDCALL ReleaseAll();
    virtual Bool   STDCALL GetPluginInfo(OUT SBLPluginInfo *pPluginInfo);
};

class CBLPluginBase : public IBLPlugin
{
    ;
};

#endif /* _BL_PLUGIN_H_ */