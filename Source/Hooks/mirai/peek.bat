@echo off
setlocal enabledelayedexpansion

for %%i in (%*) do (
    "%~dp0peekjp.py" %%i
    set sctxt="%%~dpi..\sctxt"
    set sc=%%~dpni
    set sc="!sc:~0,-4!.txt"
    md !sctxt! >NUL 2>NUL
    move /y !sc! !sctxt! >NUL 2>NUL
)