@echo off
cd/d "%~dp0"

rd/q VAXAutoText
rd/q VCUserProps

mklink /d VAXAutoText "%appdata%\VisualAssist\Autotext"
mklink /d VCUserProps "%LOCALAPPDATA%\Microsoft\MSBuild\v4.0"
mklink /d ImmPyCommands "F:\Crack\Immunity Debugger\PyCommands"
mklink /d ImmPyLibs "F:\Crack\Immunity Debugger\Libs"
mklink /d PyLibs "E:\Python\Lib\site-packages"
