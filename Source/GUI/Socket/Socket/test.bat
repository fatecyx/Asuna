@ECHO OFF&CD/D "%~dp0"
Start Socket.exe
Ping /n 3 0.0>NUL
FOR /L %%i IN (1 1 5) DO Start "" telnet 127.0.0.1