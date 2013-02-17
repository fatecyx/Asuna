#include "video_window_manager.h"

#include "log.h"

extern Log g_log;

VideoWindowManager::~VideoWindowManager(void) {
  VideoMap::iterator iter;
  for(iter = video_map_.begin(); iter != video_map_.end(); iter++) {
    iter->second->Unsubclass();
  }
}

bool VideoWindowManager::AddNewVideoWindow(HWND chromeHwnd, HWND videoHwnd) {
  bool flag = false;

  VideoMap::iterator pair = video_map_.find(chromeHwnd);
  if (pair == video_map_.end()) {
    char logs[256];
    sprintf(logs, "AddNewVideoWindow,chromeHwnd=0x%X,videohwnd=0x%X",
            chromeHwnd, videoHwnd);
    g_log.WriteLog("AddNewVideoWindow", logs);
    VideoWindow* pVideo = new VideoWindow();
    pVideo->InitWindow(chromeHwnd, videoHwnd);
    video_map_.insert(VideoWinPair(chromeHwnd, pVideo));
    flag = true;
  }

  return flag;
}

void VideoWindowManager::RemoveVideoWindow(HWND chromeHwnd) {
  VideoMap::iterator pair = video_map_.find(chromeHwnd);
  if (pair == video_map_.end()) {
    video_map_.erase(pair);
  }
}

BOOL VideoWindowManager::WndProc(HWND hwnd, UINT& msg, 
                                 WPARAM& wParam, LPARAM& lParam) {
  BOOL ret = FALSE;
  VideoMap::iterator pair = video_map_.find(hwnd);
  if (pair != video_map_.end()) {
    ret = pair->second->WndProc(hwnd, msg, wParam, lParam);
  }
  return ret;
}