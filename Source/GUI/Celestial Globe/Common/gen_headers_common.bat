@ECHO OFF
CD/D "%~dp0"

Set FileName=CG_Headers.h
DEL /Q %FileName% >NUL 2>NUL

Call:Generate >> %FileName%
GOTO:EOF

:Generate

ECHO #ifndef _CG_HEADERS_H_97b6cc58_d04e_4a0a_8c3f_f666a277afae
ECHO #define _CG_HEADERS_H_97b6cc58_d04e_4a0a_8c3f_f666a277afae
ECHO.
ECHO #include "pragma_once.h"

FOR %%i in (*.h) DO IF NOT [%%i]==[%FileName%] ECHO #include "%%~nxi"

ECHO.
ECHO #endif // _CG_HEADERS_H_97b6cc58_d04e_4a0a_8c3f_f666a277afae
