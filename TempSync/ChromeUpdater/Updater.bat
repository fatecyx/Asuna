@ECHO OFF

cd/d "%~dp0"

set URL=http://commondatastorage.googleapis.com/chromium-browser-snapshots/Win
set FILE=mini_installer.exe
for /F "delims=" %%i in (LATEST_CHANGE) do set LATEST_CHANGE=%%i

del CHECK
wget.exe %URL%/LAST_CHANGE >NUL 2>NUL
ren LAST_CHANGE CHECK
for /F "delims=" %%j in (CHECK) do set CHECK=%%j
if not "%LATEST_CHANGE%"=="%CHECK%" goto Download
echo You have the latest Chromium version - Build %LATEST_CHANGE%

ping -n 5 localhost > NUL
goto eof

:Download

echo Downloading latest version of Chromium Build %Check%
wget.exe -N %URL%/%CHECK%/%FILE%

echo Updating Chromium from Build %LATEST_CHANGE% to version %Check% ...
rem mini_installer.exe
copy /y CHECK LATEST_CHANGE