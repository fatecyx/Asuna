del "%~dp0log.txt"
for %%i in (%*) do "%~dp0BConv.exe" %%i>>"%~dp0log.txt"