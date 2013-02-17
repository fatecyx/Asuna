@echo off
setlocal enabledelayedexpansion

call "%~dp0set_path.bat"

md "%sctxt%" >NUL 2>NUL

for /f %%i in ('dir/b ^"%bintxt%\*.bin.txt^"') do (
    "%~dp0peekjp.py" "%bintxt%\%%~nxi"

    set sc=%bintxt%\%%~nxi
    set sc="!sc:~0,-8!.txt"
    move /y !sc! "%sctxt%" >NUL 2>NUL
)
