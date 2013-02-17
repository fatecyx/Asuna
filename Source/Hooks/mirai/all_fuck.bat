@echo off
setlocal enabledelayedexpansion

call "%~dp0set_path.bat"

md "%bintxt%" >NUL 2>NUL

set list=
for /f %%i in ('dir/b ^"%ps2p%\*.ps2^"') do (
    set list=!list! "%ps2p%\%%~nxi"
)

"%~dp0fuckall.py" !list!

move/y "%ps2p%\*.bin.txt" "%bintxt%" >NUL 2>NUL
