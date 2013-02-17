@ECHO OFF
MD Event_Conv>NUL 2>NUL
For %%i IN (Patch\*.SDT) DO (
	ExportText.exe "%%~fi"
)
move patch\*.txt Event_Conv