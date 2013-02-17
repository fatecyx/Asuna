call:do >nul 2>nul
goto:eof

:do
rd/s/q out
md out
move t\*.txt out\