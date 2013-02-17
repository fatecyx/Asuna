@echo off & setlocal enabledelayedexpansion
cd/d "%~dp0"

call:proc >nul 2>nul
goto:eof

:proc
rd/s/q cn
rd/s/q jp
rd/s/q fin
md cn
md jp
md fin
set exe=mscpeek.exe
for %%i in (K:\galgame\きっと、確みわたる劾弼よりも\scenario_sc\*.msc) do (
	title %%i
	%exe% "%%i"
)
move K:\galgame\きっと、確みわたる劾弼よりも\scenario_sc\*.txt cn\ 

for %%i in (K:\galgame\きっと、確みわたる劾弼よりも\backup\scenario\*.msc) do (
	title %%i
	%exe% "%%i"
)
move K:\galgame\きっと、確みわたる劾弼よりも\backup\scenario\*.txt jp\

for %%i in (cn\*.txt) do (
	combine.exe "%%i" "%~dp0jp\%%~nxi" "fin\%%~nxi"
)