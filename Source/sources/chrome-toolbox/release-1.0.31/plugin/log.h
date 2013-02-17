#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>

#include <windows.h>

class Log {
public:
  Log(void);
  ~Log(void);

  bool OpenLog(const char* header);
  bool WriteLog(const char* title, const char* contents);
  bool CloseLog();

private:
  FILE* file_;
  SYSTEMTIME time_;
};

#endif