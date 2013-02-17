@ECHO OFF
CD/D "%~dp0"

Set FileName=CG_Headers.h
DEL /Q %FileName% >NUL 2>NUL

Call:Generate >> %FileName%
GOTO:EOF

:Generate

ECHO #ifndef _CG_HEADERS_H_0355b122_99ca_4757_8ec8_0533958b5085
ECHO #define _CG_HEADERS_H_0355b122_99ca_4757_8ec8_0533958b5085
ECHO.
ECHO #include "pragma_once.h"

FOR %%i in (*.h) DO IF NOT [%%i]==[%FileName%] ECHO #include "%%~nxi"

ECHO.
ECHO #endif // _CG_HEADERS_H_0355b122_99ca_4757_8ec8_0533958b5085
