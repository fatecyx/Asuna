@echo off

for %%i in (k:\galgame\∑x“Ì§Œ•Ê©`•π•∆•£•¢\data01000\*.lua) do (
    title %%i
    "%~dp0luajit.exe" "%%~fi"
)
