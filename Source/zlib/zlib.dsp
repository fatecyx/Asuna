# Microsoft Developer Studio Project File - Name="zlib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=zlib - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "zlib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "zlib.mak" CFG="zlib - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "zlib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ZLIB_EXPORTS" /YX /FD /c
# ADD CPP /nologo /Gr /MD /W4 /GR- /O2 /Ob1 /I "E:\Library\zlib\contrib\minizip" /I "E:\Library\zlib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D USE_CRT_VER=1 /FD /GS- /GL /MP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 mylib_nt.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"E:\MyLib\rt\minizip1.dll" /implib:"E:\MyLib\MyLibrary\Library\minizip1.lib" /ltcg /NOENTRY
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "zlib - Win32 Release"
# Begin Group "zlib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Library\zlib\adler32.c
# ADD CPP /w /W0
# End Source File
# Begin Source File

SOURCE=..\..\..\Library\zlib\crc32.c
# ADD CPP /w /W0
# End Source File
# Begin Source File

SOURCE=..\..\..\Library\zlib\inffast.c
# ADD CPP /w /W0
# End Source File
# Begin Source File

SOURCE=..\..\..\Library\zlib\inflate.c
# ADD CPP /w /W0
# End Source File
# Begin Source File

SOURCE=..\..\..\Library\zlib\inftrees.c
# ADD CPP /w /W0
# End Source File
# Begin Source File

SOURCE=..\..\..\Library\zlib\contrib\minizip\ioapi.c
# ADD CPP /w /W0
# End Source File
# Begin Source File

SOURCE=..\..\..\Library\zlib\contrib\minizip\unzip.c
# ADD CPP /w /W0
# End Source File
# Begin Source File

SOURCE=..\..\..\Library\zlib\zutil.c
# ADD CPP /w /W0
# End Source File
# End Group
# Begin Source File

SOURCE=.\zlibdll.cpp
# End Source File
# Begin Source File

SOURCE=.\zlibdll.def
# End Source File
# End Target
# End Project
