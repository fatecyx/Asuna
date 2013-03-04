@echo off
cd/d "%~dp0"

mklink /d "%~dp0%~n1" %1

