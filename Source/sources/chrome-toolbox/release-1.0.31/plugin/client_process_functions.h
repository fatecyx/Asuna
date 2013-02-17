#ifndef CLIENT_PROCESS_FUNCTIONS_H_
#define CLIENT_PROCESS_FUNCTIONS_H_

namespace client_process_unit {

// Client pipe thread, communication with the plugin process.
DWORD WINAPI Client_Thread(void* param);

// Some hook function.

// Hook keyboard function.
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

// Hook getmessage function.
LRESULT CALLBACK GetMsgProc(int code, WPARAM wParam, LPARAM lParam);

// Hook window procedure.
LRESULT CALLBACK CallWndProcHook(int code, WPARAM wParam, LPARAM lParam);

// Send command to server.
void WriteToServer(const CmdMsgItem& item);

// Read some infomation from config file.
int ReadBaseInfomation(const TCHAR* appname, const TCHAR* cfgname);
void ReadBaseInfomation(const TCHAR* appname, const TCHAR* cfgname, 
                        TCHAR* buffer, unsigned int len);

// When dll terminate, terminate the client thread.
void ExitClientThread();

}

#endif