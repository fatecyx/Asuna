@ECHO OFF
CD/D "%~dp0"

For /F "delims=" %%i In (Info.txt) Do (
	ECHO ==================================================%%i
	ECHO.
	ECHO --------------------------------------
	ECHO.
)