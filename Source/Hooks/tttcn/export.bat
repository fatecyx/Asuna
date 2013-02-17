@ECHO OFF
CD/D "%~dp0"
Set OutDir=Event_Text
MD %OutDir%>NUL 2>NUL
For %%i IN (Event\*.SDT) DO (
	ExportText.exe "%%~fi"
	Move "%%~dpni.txt" "%OutDir%\%%~ni.txt"
)