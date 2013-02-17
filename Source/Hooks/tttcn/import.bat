@ECHO OFF
CD/D "%~dp0"

MD SDT 2>NUL
For %%i IN (Event\*.sdt) DO (
	ImportText.exe %%i SDT\%%~nxi
)
Pause