@echo off
setlocal enabledelayedexpansion

for %%i in (%*) do (
    set psbin="%%~dpi..\psbin\"
    set bintxt=%%~dpi..\bintxt\
    set bin="%%~dpni.psbin"
    md !psbin! >NUL 2>NUL

    move /y "!bintxt!%%~ni.bin.txt" "%%~dpi" >NUL 2>NUL
    "%~dp0mergesc.py" %%i
    move /y !bin! !psbin! >NUL 2>NUL
    move /y "%%~dpni.bin.txt" "!bintxt!" >NUL 2>NUL
)
