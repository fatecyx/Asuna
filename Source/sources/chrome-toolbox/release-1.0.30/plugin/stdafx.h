#ifndef STDAFX_H_
#define STDAFX_H_

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <map>
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>

inline void* __cdecl operator new[](size_t size)
{
    return size ? malloc(size) : NULL;
}

inline void* __cdecl operator new(size_t size)
{
    return (void *)(new char[size]);
}

inline void __cdecl operator delete(void *p)
{
    if (p != NULL)
        free(p);
}

inline void __cdecl operator delete[](void *p)
{
    delete(p);
}

#define MAX_KEY_NUM 0xFF
#define MAX_FUNCTION_LEN  64
#define MAX_KEY_LEN 32
#define MAX_BUFFER_LEN  1024

#define WM_TRAYICON_NOTIFY            WM_USER+400

#define WM_CHROMEHWND                 WM_USER+100
#define WM_CHROMECLOSE                WM_USER+101
#define WM_TRIGGER_CHROME_SHORTCUTS   WM_USER+102
#define WM_TABCLOSE                   WM_USER+103
#define WM_CLOSE_CURRENT_TAB          WM_USER+104
#define WM_UPDATE_CLOSECHROME_PROMPT  WM_USER+105
#define WM_CHROMEMOUSEWHEEL           WM_USER+106
#define WM_FLASH_FULLSCREEN_STATUS    WM_USER+107
#define WM_PRESS_ENTER_OPEN_NEW_TAB   WM_USER+108

#define EVENTID_FRESH   3456

#define OFFSET_LEN    97
#define VISTA_OFFSET_LEN    110
#define TIP_BUTTON_WIDTH  26
#define TIP_BUTTON_HEIGHT 18
#define CONST_FRAME_BORDER  4
#define CONST_FRAME_CAPTION_HEIGHT  40
#define MINIMUM_VERSION_SUPPORT_POPUP 10

#define MSG_BASE                      1000
#define MSG_ALWAYS_ON_TOP             MSG_BASE+1
#define MSG_CLOSECHROME_TITLE         MSG_BASE+2
#define MSG_CLOSECHROME_MESSAGE       MSG_BASE+3
#define MSG_CLOSECHROME_OK            MSG_BASE+4
#define MSG_CLOSECHROME_CANCEL        MSG_BASE+5
#define MSG_CLOSECHROME_NOALERT       MSG_BASE+6

struct KeyStokeItem {
  WORD virual_key;
  BOOL is_pressed;
};

struct LocalMessageItem {
  TCHAR msg_always_on_top[256]; 
  TCHAR msg_closechrome_title[256]; 
  TCHAR msg_closechrome_message[256]; 
  TCHAR msg_closechrome_ok[256]; 
  TCHAR msg_closechrome_cancel[256]; 
  TCHAR msg_closechrome_noalert[256];
};

struct ShortCutItem {
  char shortcuts_key[MAX_KEY_LEN];
  char function[MAX_FUNCTION_LEN];
  BOOL ishotkey;
  UINT index;
  void* object;
};

enum CmdMsgType {
  kCmdUpdateShortcuts = 0,
  kCmdRequestUpdate,
  kCmdResponseUpdate,
  kCmdUpdateDBClickCloseTab,
  kCmdUpdateIsListening,
  kCmdUpdateTabCount,
  kCmdUpdateLocalMessage,
  kCmdUpdateCloseChromePrompt,
  kCmdUpdateCloseLastTab,
  kCmdUpdateSwitchTab,
  kCmdUpdatePressEnterOpenNewTab,
  kCmdKeyDown,
  kCmdKeyUp,
  kCmdEvent,
  kCmdMouseRotated,
  kCmdChromeClose,
  kCmdTabClose,
  kCmdDBClickCloseTab,
  kCmdServerShutDown,
  kCmdClientShutDown,
  kCmdChromeWindowCreated,
  kCmdChromeWindowRemoved,
  kCmdExistsPinnedTabs,
  kCmdPressEnterOpenNewTab,
};

struct CmdMsgItem {
  CmdMsgType cmd;
  union CmdMsgValue{
    UINT shortcuts_Id;
    bool double_click_closetab;
    bool is_listening;
    bool is_closechrome_prompt;
    bool close_last_tab;
    bool enable_switch_tab;
    bool press_enter_open_new_tab;
    int rotatedcount;
    struct KeyDown {
      WPARAM wparam;
      LPARAM lparam;
    }key_down;
    struct ChromeWindow {
      HWND chrome_handle;
      int windowid;
    }chrome_window;
    struct TabCount {
      int windowid;
      int tabcount;
      bool pinnedtab;
    }tabcount;
  }value;
};

typedef std::map<HWND, CmdMsgItem::CmdMsgValue::TabCount> ChromeWindowIdMap;

#endif