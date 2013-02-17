@echo off

for %%i in (%*) do (
    E:\Python27\python.exe "%~dp0extxt.py" -e "%%~fi" "%%~dpni.txt"
)