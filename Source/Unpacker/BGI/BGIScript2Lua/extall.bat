@echo off
cd/d "%~dp0"

md Chs >NUL 2>NUL
md JP >NUL 2>NUL
for %%i in (D:\galgame\∑x“Ì§Œ•Ê©`•π•∆•£•¢\data01000\*.lua) do @call "%~dp0ext.bat" "%%~fi"
move /y D:\galgame\∑x“Ì§Œ•Ê©`•π•∆•£•¢\data01000\*.txt "%~dp0Chs"

for %%i in (D:\galgame\∑x“Ì§Œ•Ê©`•π•∆•£•¢\data01000_sc\*.lua) do @call "%~dp0ext.bat" "%%~fi"
move /y D:\galgame\∑x“Ì§Œ•Ê©`•π•∆•£•¢\data01000_sc\*.txt "%~dp0JP"