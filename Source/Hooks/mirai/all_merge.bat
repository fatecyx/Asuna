@echo off
setlocal enabledelayedexpansion

call "%~dp0set_path.bat"

md "%psbin%" >NUL 2>NUL

for /f %%i in ('dir/b ^"%sctxt%\*.txt^"') do (
    set bin="%sctxt%\%%~ni.psbin"

    move /y "%bintxt%\%%~ni.bin.txt" "%sctxt%" >NUL 2>NUL
    "%~dp0mergesc.py" "%sctxt%\%%~nxi"
    move /y !bin! "%psbin%" >NUL 2>NUL
    move /y "%sctxt%\%%~ni.bin.txt" "%bintxt%" >NUL 2>NUL
)
