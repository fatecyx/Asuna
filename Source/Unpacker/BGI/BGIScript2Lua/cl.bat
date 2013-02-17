@echo off

for %%i in (%*) do "%~dp0luajit.exe" "%%~fi"