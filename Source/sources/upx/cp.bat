@echo off
cd/d "%~dp0"
cls

set file="E:\Desktop\NetPeeker2\NPGUI_crk.exe"

del bak.upx >NUL 2>NUL
copy /y %file% bak.exe
upx.exe bak.exe
del "bak.upx">NUL 2>NUL
rem pause