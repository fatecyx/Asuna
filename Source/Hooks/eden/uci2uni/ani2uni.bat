@echo off
IF "%~f1"=="" Start notepad "%~f0"&GOTO:EOF
cd/d "%~f1"

rem goto:ProcANI

for %%i in (*.ani) do (
	"%~dp0ani2bmp.exe" "%%~fi"
)

:EncToUCI
"G:\x\UCI\batuci.bat" %CD%
ping /n 3 0.0 >nul 2>nul

:ProcANI
for %%i in (*.ani) do (
	"%~dp0uci2uni.exe" "%%~fi"
)