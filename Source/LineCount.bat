@echo off & setlocal enabledelayedexpansion
cd/d "%~dp0"

set excludedir=sources,gui,Unpacker/yosuga,CSharp,DS
cloc-1.53.exe --ignore-case --exclude-dir=%excludedir% --report-file=report.txt --counted=filenames.txt "C:\New folder"
goto:eof

set wc=F:\Git\bin\wc.exe
del line_log.txt >nul 2>nul

set/a line=0
for /f "delims=" %%f in (folderlist.txt) do (
	call:dir %%f
)
echo !line!>>line_log.txt
goto:eof

:dir
for /r %1 %%a in (.\*.cpp .\*.h .\*.c) do (
	echo %%a>>line_log.txt
	for /f "tokens=1,2,3* delims= " %%l in ('%wc% -l "%%a"') do (
		title %%a
echo %%l>>line_log.txt
		set/a line+=%%l
echo !line!>>line_log.txt
	)
)
goto:eof