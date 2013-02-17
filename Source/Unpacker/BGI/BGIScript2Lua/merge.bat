@echo off

cd/d "%~dp0"

md merge2 >NUL 2>NUL
for %%i in (jp\*.txt) do (
    call py.bat merge.py "jp\%%~nxi" "chs\%%~nxi" "merge2\%%~nxi"
)
