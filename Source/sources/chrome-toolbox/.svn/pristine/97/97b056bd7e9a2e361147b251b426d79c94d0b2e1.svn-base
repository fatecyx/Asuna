#include "log.h"

Log::Log(void) {
  file_ = NULL;
}

Log::~Log(void) {
  if (file_ != NULL)
    CloseLog();
}

bool Log::OpenLog(const char* header) {
  if (file_ != NULL)
    return false;

  char filename[MAX_PATH];
  GetLocalTime(&time_);
  sprintf_s(filename, "C:\\Log\\%s_%d%02d%02d_%d.log",
            header, time_.wYear, time_.wMonth, time_.wDay,
            GetCurrentProcessId());
  file_ = fopen(filename, "a");
  if (file_ == NULL)
    return false;
  else
    return true;
}

bool Log::WriteLog(const char* title, const char* contents) {
  if (file_ == NULL) {
    return false;
  }

  GetLocalTime(&time_);
  if (fprintf(file_, "[%02d:%02d:%02d %03d] [%s] %s\n",
              time_.wHour, time_.wMinute, time_.wSecond, time_.wMilliseconds,
              title, contents) > 0) {
    fflush(file_);
    return true;
  } else
    return false;
}

bool Log::CloseLog() {
  if (file_ != NULL) {
    fclose(file_);
    file_ = NULL;
  }
  return true;
}
