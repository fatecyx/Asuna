@ECHO OFF

CD "%~dp0mylib"
For /F "delims=" %%i In ('Dir/s/b *.*') Do (
	For /F "delims=" %%j In ('Dir/s/b E:\MyLib\%%~nxi 2^>NUL') Do Copy /Y "%%~fj" "%%~fi" >NUL 2>NUL
)
rem Copy /Y E:\MyLib\Lib\MyLib ../Babylon >NUL 2>NUL