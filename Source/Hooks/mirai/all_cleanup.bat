@echo off
setlocal enabledelayedexpansion

call "%~dp0set_path.bat"

rd/s/q "%bintxt%" >NUL 2>NUL
rd/s/q "%sctxt%" >NUL 2>NUL
rd/s/q "%psbin%" >NUL 2>NUL