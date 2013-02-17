@echo off
setlocal enabledelayedexpansion

call "%~dp0set_path.bat"

del "%psbin%\mirai.bin" >NUL 2>NUL

for /f %%i in ('dir/b ^"%psbin%\*.psbin^"') do (
    title %%~nxi
    "%~dp0mirai_text.exe" "%psbin%\%%~nxi"
)

echo compressing...
"%~dp0mirai_text.exe" -compress "%psbin%\mirai.bin"

move /y "%psbin%\mirai.bin" "%gamepath%\mirai.bin" >NUL 2>NUL
