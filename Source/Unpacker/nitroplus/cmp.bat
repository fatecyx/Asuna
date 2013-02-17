@echo off
setlocal ENABLEDELAYEDEXPANSION

for %%i in (nss\*.*) do (
    fc/b "%%~fi" "nss1\%%~nxi" >NUL 2>NUL
    if !ERRORLEVEL!==1 ECHO %%i
)

pause