#include "utils.h"

#include <stddef.h>

#define SIZEOF_STRUCT_WITH_SPECIFIED_LAST_MEMBER(struct_name, member) \
  offsetof(struct_name, member) + \
  (sizeof static_cast<struct_name*>(NULL)->member)
#define NONCLIENTMETRICS_SIZE_PRE_VISTA \
  SIZEOF_STRUCT_WITH_SPECIFIED_LAST_MEMBER(NONCLIENTMETRICS, lfMessageFont)

namespace utils {
  WinVersion GetWinVersion() {
    static bool checked_version = false;
    static WinVersion win_version = WINVERSION_PRE_2000;
    if (!checked_version) {
      OSVERSIONINFOEX version_info;
      version_info.dwOSVersionInfoSize = sizeof version_info;
      GetVersionEx(reinterpret_cast<OSVERSIONINFO*>(&version_info));
      if (version_info.dwMajorVersion == 5) {
        switch (version_info.dwMinorVersion) {
        case 0:
          win_version = WINVERSION_2000;
          break;
        case 1:
          win_version = WINVERSION_XP;
          break;
        case 2:
        default:
          win_version = WINVERSION_SERVER_2003;
          break;
        }
      } else if (version_info.dwMajorVersion == 6) {
        if (version_info.wProductType != VER_NT_WORKSTATION) {
          // 2008 is 6.0, and 2008 R2 is 6.1.
          win_version = WINVERSION_2008;
        } else {
          if (version_info.dwMinorVersion == 0) {
            win_version = WINVERSION_VISTA;
          } else {
            win_version = WINVERSION_WIN7;
          }
        }
      } else if (version_info.dwMajorVersion > 6) {
        win_version = WINVERSION_WIN7;
      }
      checked_version = true;
    }
    return win_version;
  }

  void GetNonClientMetrics(NONCLIENTMETRICS* metrics) {
    static const UINT SIZEOF_NONCLIENTMETRICS =
        (GetWinVersion() >= WINVERSION_VISTA) ?
        sizeof(NONCLIENTMETRICS) : NONCLIENTMETRICS_SIZE_PRE_VISTA;
    metrics->cbSize = SIZEOF_NONCLIENTMETRICS;
    const bool success = !!SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
        SIZEOF_NONCLIENTMETRICS, metrics, 0);
  }
}