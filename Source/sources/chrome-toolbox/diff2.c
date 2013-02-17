diff --git a/apihook/dll_entry.cc b/apihook/dll_entry.cc
index 71c9c4c..aff83be 100644
--- a/apihook/dll_entry.cc
+++ b/apihook/dll_entry.cc
@@ -105,6 +105,7 @@ BOOL WINAPI DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
   switch(reason) {
     case DLL_PROCESS_ATTACH:
       //g_Log.OpenLog("APIHOOK");
+      DisableThreadLibraryCalls(hModule);
       Init();
       g_log.WriteLog("Msg", "DLL_PROCESS_ATTACH");
       break;
diff --git a/apihook/stdafx.h b/apihook/stdafx.h
index 5852e0c..22b2c70 100644
--- a/apihook/stdafx.h
+++ b/apihook/stdafx.h
@@ -6,4 +6,25 @@
 #include <windows.h>
 #include <windowsx.h>
 
+inline void* __cdecl operator new[](size_t size)
+{
+    return size ? malloc(size) : NULL;
+}
+
+inline void* __cdecl operator new(size_t size)
+{
+    return (void *)(new char[size]);
+}
+
+inline void __cdecl operator delete(void *p)
+{
+    if (p != NULL)
+        free(p);
+}
+
+inline void __cdecl operator delete[](void *p)
+{
+    delete(p);
+}
+
 #endif
\ No newline at end of file
diff --git a/browser_mute_script_object.cc b/browser_mute_script_object.cc
index 638d2ed..36d0d8a 100644
--- a/browser_mute_script_object.cc
+++ b/browser_mute_script_object.cc
@@ -35,7 +35,7 @@ void BrowserMuteScriptObject::InitHandler() {
 
 void BrowserMuteScriptObject::Deallocate() {
   char logs[256];
-  sprintf_s(logs, "BrowserMuteScriptObject this=%ld", this);
+  sprintf(logs, "BrowserMuteScriptObject this=%ld", this);
   g_log.WriteLog("Deallocate", logs);
   delete this;
 }
diff --git a/client_process_functions.cc b/client_process_functions.cc
index 6c09246..2226d07 100644
--- a/client_process_functions.cc
+++ b/client_process_functions.cc
@@ -81,7 +81,7 @@ void UpdateShortcutsFromMemory() {
       }
 
       for (int i = 0; i < count; i++) {
-        key_map_new->insert(std::make_pair(list[i].shortcuts_key, list[i]));
+        key_map_new->insert(std::make_pair(std::string(list[i].shortcuts_key), list[i]));
       }
       map_current_used_flag = map_current_used_flag == 1 ? 2 : 1;
       key_map_old->clear();
@@ -344,14 +344,25 @@ LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
 
     HWND hwnd = GetForegroundWindow();
     ChromeWindowIdMap::iterator tabcount_iter = chrome_window_map.find(hwnd);
-    if ((wParam == VK_F4 || wParam == 'W') && 
-        ((GetKeyState(VK_CONTROL) & 0x80)) && close_last_tab &&
-        tabcount_iter != chrome_window_map.end() && 
-        tabcount_iter->second.tabcount == 1) {
-      CmdMsgItem item;
-      item.cmd = kCmdTabClose;
-      WriteToServer(item);
-      return TRUE;
+    switch (wParam)
+    {
+        case 'W':
+            if (GetKeyState(VK_CONTROL) >= 0)
+                break;
+            // fall through
+        case VK_F4:
+            if (GetKeyState(VK_SHIFT) < 0 || GetKeyState(VK_MENU) < 0)
+                break;
+
+            if (close_last_tab &&
+                tabcount_iter != chrome_window_map.end() &&
+                tabcount_iter->second.tabcount == 1)
+            {
+                CmdMsgItem item;
+                item.cmd = kCmdTabClose;
+                WriteToServer(item);
+                return TRUE;
+            }
     }
 
     ConvenienceScriptObject::ShortCutKeyMap* shortcut_map;
diff --git a/convenience_plugin.cc b/convenience_plugin.cc
index 4d30701..138bab9 100644
--- a/convenience_plugin.cc
+++ b/convenience_plugin.cc
@@ -560,8 +560,35 @@ LRESULT ConveniencePlugin::WndProc(HWND hWnd, UINT Msg,
       pObject->UpdateCloseChromePromptFlag(wParam);
       break;
     case WM_CHROMEMOUSEWHEEL: {
-      bool forward = lParam > 0 ? true : false;
-      pObject->TriggerSwitchTab(forward);
+        bool forward = lParam > 0 ? true : false;
+#if 1
+        INPUT inputs[2], input;
+
+        inputs[0].type = INPUT_KEYBOARD;
+        inputs[0].ki.wVk = VK_CONTROL;
+        inputs[0].ki.wScan = 0;
+        inputs[0].ki.time = 0;
+        inputs[0].ki.dwFlags = 0;
+        inputs[0].ki.dwExtraInfo = 0;
+        inputs[1].type = INPUT_KEYBOARD;
+        inputs[1].ki.wVk = forward ? VK_PRIOR : VK_NEXT;
+        inputs[1].ki.wScan = 0; 
+        inputs[1].ki.time = 0;
+        inputs[1].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
+        inputs[1].ki.dwExtraInfo = 0;
+
+        SendInput(2, inputs, sizeof(*inputs));
+        inputs[0].ki.dwFlags |= KEYEVENTF_KEYUP;
+        inputs[1].ki.dwFlags |= KEYEVENTF_KEYUP;
+        input = inputs[1];
+        inputs[1] = inputs[0];
+        inputs[0] = input;
+        SendInput(2, inputs, sizeof(*inputs));
+#elif 0
+        pObject->TriggerShortcuts(MOD_CONTROL, forward ? VK_PRIOR : VK_NEXT); 
+#else
+        pObject->TriggerSwitchTab(forward);
+#endif
       break;
     }
     case WM_KEYDOWN: {
diff --git a/convenience_script_object.cc b/convenience_script_object.cc
index 5774edf..42348b5 100644
--- a/convenience_script_object.cc
+++ b/convenience_script_object.cc
@@ -183,7 +183,7 @@ bool ConvenienceScriptObject::UpdateShortCutList(const NPVariant *args,
           item.ishotkey = NPVARIANT_TO_BOOLEAN(property_value);
       }
       item.object = array_object;
-      key_map_new->insert(ShortCutPair(item.shortcuts_key, item));
+      key_map_new->insert(ShortCutPair(std::string(item.shortcuts_key), item));
       shortcuts_list_[i] = item;
     }
 
diff --git a/dll_entry.cc b/dll_entry.cc
index 5dc5fcb..f73926a 100644
--- a/dll_entry.cc
+++ b/dll_entry.cc
@@ -13,6 +13,7 @@ BOOL OSCALL DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved) {
   g_module = hModule;
   switch(reason) {
     case DLL_PROCESS_ATTACH:
+      DisableThreadLibraryCalls(hModule);
       g_log.OpenLog("NPAPI");
       g_log.WriteLog("Msg","DLL_PROCESS_ATTACH");
       break;
diff --git a/log.cc b/log.cc
index caf21c3..72d16cd 100644
--- a/log.cc
+++ b/log.cc
@@ -15,7 +15,7 @@ bool Log::OpenLog(const char* header) {
 
   char filename[MAX_PATH];
   GetLocalTime(&time_);
-  sprintf_s(filename, "C:\\Log\\%s_%d%02d%02d_%d.log",
+  sprintf(filename, "C:\\Log\\%s_%d%02d%02d_%d.log",
             header, time_.wYear, time_.wMonth, time_.wDay,
             GetCurrentProcessId());
   file_ = fopen(filename, "a");
diff --git a/ncbutton.cc b/ncbutton.cc
index 59b9648..6d0855f 100644
--- a/ncbutton.cc
+++ b/ncbutton.cc
@@ -36,10 +36,10 @@ void NCButton::Init(HWND parenthwnd) {
 
   grph_ = Graphics::FromHDC(GetWindowDC(parent_hwnd_));
 
-  SetWindowPos(parent_hwnd_, HWND_TOPMOST, 0, 0, 0, 0,
+  SetWindowPos(parent_hwnd_, HWND_NOTOPMOST, 0, 0, 0, 0,
                SWP_NOSIZE | SWP_NOMOVE);
 
-  is_topmost_ = true;
+  is_topmost_ = false;
 }
 
 void NCButton::OnPaint(HDC paintdc /* = NULL */) {
diff --git a/stdafx.h b/stdafx.h
index 3d8cfa5..816efb8 100644
--- a/stdafx.h
+++ b/stdafx.h
@@ -9,6 +9,27 @@
 #include <windows.h>
 #include <windowsx.h>
 
+inline void* __cdecl operator new[](size_t size)
+{
+    return size ? malloc(size) : NULL;
+}
+
+inline void* __cdecl operator new(size_t size)
+{
+    return (void *)(new char[size]);
+}
+
+inline void __cdecl operator delete(void *p)
+{
+    if (p != NULL)
+        free(p);
+}
+
+inline void __cdecl operator delete[](void *p)
+{
+    delete(p);
+}
+
 #define MAX_KEY_NUM 0xFF
 #define MAX_FUNCTION_LEN  64
 #define MAX_KEY_LEN 32
