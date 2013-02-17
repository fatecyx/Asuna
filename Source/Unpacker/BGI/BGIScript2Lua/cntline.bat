@echo off
cd/d "%~dp0"

for %%i in (Chs\*.txt) do @E:\Python27\python.exe test.py "Chs\%%~nxi" "JP\%%~nxi"
pause