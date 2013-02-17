#ifndef CONVENIENCE_PLUGIN_H_
#define CONVENIENCE_PLUGIN_H_

#include <queue>

#include "plugin_base.h"
#include "script_object_base.h"

// This plugin is used for communication with the client process.
// It disposes command received from client, and communicates with
// chrome render process with ConvenienceScriptObject.
class ConveniencePlugin : public PluginBase {
private:
  ConveniencePlugin(void);
  virtual ~ConveniencePlugin(void);

public:
  NPError Init(NPP instance, uint16_t mode, int16_t argc, char* argn[],
               char* argv[], NPSavedData* saved);
  NPError UnInit(NPSavedData** save);
  NPError GetValue(NPPVariable variable, void *value);
  NPError SetWindow(NPWindow* window);

  // Create convenience plugin object.
  static PluginBase* CreateObject() { return new ConveniencePlugin; }

  // Write shortcuts list to memory file.(server side)
  void SetShortcutsToMemory(ShortCutItem* list, int count);

  // Send double click close tab to client.
  void UpdateDBClick_CloseTab(bool double_click_closetab);

  // Send current state of set shortcuts to client.
  void UpdateIsListening(bool is_listening);

  // Notify client process the specified window's tab count.
  void UpdateTabCount(int windowid, int tabcount);

  // Notify client process the flag that closing last tab.
  void UpdateCloseLastTab(bool close_last_tab);

  // Notify client process the flag that when user is closing 
  // the current chrome window that has multi-tab, whether prompt or not.
  void UpdateCloseChromePromptFlag(bool flag);

  // Get local information.
  void GetLocalMessage();

  // When chrome window is created, notify client process.
  void ChromeWindowCreated(int windowid);

  // When chrome window is destroyed, notify client process.
  void ChromeWindowRemoved(int windowid);

  // Notify client process, whether enable mouse wheel to 
  // switch tab feature or not.
  void EnableMouseSwitchTab(bool flag);

  // Notify client process, the specified chrome window has pinned tab or not.
  void ExistsPinnedTab(int windowid, bool pinned);

  // Notify plugin to enable press enter to open new tab or not.
  void PressEnterOpenNewTab(bool flag);

private:
  // The plugin's new window process.
  static LRESULT WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

  // Server thread, communicate with client use named pipe.
  static DWORD WINAPI Server_Thread(void* param);

  // Send command to client process
  void WriteToClient(const CmdMsgItem& item);

  // Get message from front-end, the index is a code correspond to the message.
  bool GetNPMessage(int index, TCHAR* msg, int msglen);

private:
  // Script object interface.
  ScriptObjectBase* scriptobject_;

  // The plugin's old window process.
  static WNDPROC old_proc_;

  // Memory file handle, memory file used for update shortcuts data.
  HANDLE memory_file_handle_;
  HANDLE server_thread_handle_;
  HANDLE server_pipe_handle_;

  // Hook handle.
  HHOOK keyboard_hook_;
  HHOOK get_msg_hook_;
  HHOOK call_wnd_hook_;

  // The queue for save triggered shortcuts list index.
  std::queue<int> shortcuts_queue_;

  // Using for multi-thread access shortcuts_queue_ variable.
  CRITICAL_SECTION cs_;

  bool get_local_message_flag_;

  // Some flag.
  static bool close_last_tab_;
  static bool close_chrome_prompt_;
  static bool db_click_close_tab_;
  static bool enable_switch_tab_;
  static bool press_enter_open_new_tab_;

  static ChromeWindowIdMap chrome_window_map_;

};

#endif