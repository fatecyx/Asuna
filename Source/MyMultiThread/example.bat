@ECHO OFF
Set/A Threads=%Random% %% 5
ECHO %Threads%
ED6Compress.exe "CH00488 ._CH" -o output._ch -t %Threads%
Pause