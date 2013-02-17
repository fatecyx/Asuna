#ifndef UTIL_H_
#define UTIL_H_

#include "npfunctions.h"

namespace utils {

class IdentifierToString {
public:
  explicit IdentifierToString(NPIdentifier identifier)
    : identifier_name_(NULL) {
      identifier_name_ = NPN_UTF8FromIdentifier(identifier);
  }
  const char* identifier_name() const { return identifier_name_; }
  operator const char*() const { return identifier_name_; }
  ~IdentifierToString() { if (identifier_name_) NPN_MemFree(identifier_name_); }

private:
  // Disable evil constructors.
  IdentifierToString();
  IdentifierToString(const IdentifierToString&);

  char* identifier_name_;
};

class Utf8ToUnicode {
public:
  explicit Utf8ToUnicode(const char* utf8data, unsigned int datalen = -1)
    : buffer_(NULL) {
    int size = MultiByteToWideChar(CP_UTF8, 0, utf8data, datalen, 0, 0);
    if (size > 0)
      buffer_ = new WCHAR[size + 1];
    if (buffer_) {
      MultiByteToWideChar(CP_UTF8, 0, utf8data, datalen, buffer_, size);
      buffer_[size] = 0;
    }
  }
  operator WCHAR*() const { return buffer_; }
  WCHAR** operator &() { return &buffer_; }
  ~Utf8ToUnicode() { if (buffer_) delete[] buffer_; }

private:
  Utf8ToUnicode();
  Utf8ToUnicode(const Utf8ToUnicode&);
  WCHAR* buffer_;
};

enum WinVersion {
  WINVERSION_PRE_2000 = 0,  // Not supported
  WINVERSION_2000 = 1,      // Not supported
  WINVERSION_XP = 2,
  WINVERSION_SERVER_2003 = 3,
  WINVERSION_VISTA = 4,
  WINVERSION_2008 = 5,
  WINVERSION_WIN7 = 6,
};

WinVersion GetWinVersion();
void GetNonClientMetrics(NONCLIENTMETRICS* metrics);

}

#endif