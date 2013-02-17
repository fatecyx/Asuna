@echo off
setlocal enabledelayedexpansion

del "%~dp1mirai.bin" >NUL 2>NUL

for %%i in (%*) do (
    "%~dp0mirai_text\mirai_text.exe" %%i
)