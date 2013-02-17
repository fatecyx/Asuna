# Microsoft Developer Studio Project File - Name="ef" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ef - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ef.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ef.mak" CFG="ef - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ef - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Gr /MD /W4 /GR- /O2 /Ob1 /I "zlib-1.2.5" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D USE_NT_VER=1 /FD /GS- /GL /MP /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"eden_upk.exe" /DYNAMICBASE:NO /LTCG
# SUBTRACT LINK32 /pdb:none /debug
# Begin Target

# Name "ef - Win32 Release"
# Begin Group "zlib"

# PROP Default_Filter ""
# Begin Source File

SOURCE="E:\Library\zlib\adler32.c"
# End Source File
# Begin Source File

SOURCE="E:\Library\zlib\crc32.c"
# End Source File
# Begin Source File

SOURCE="E:\Library\zlib\inffast.c"
# End Source File
# Begin Source File

SOURCE="E:\Library\zlib\inflate.c"
# End Source File
# Begin Source File

SOURCE="E:\Library\zlib\inftrees.c"
# End Source File
# Begin Source File

SOURCE="E:\Library\zlib\uncompr.c"
# End Source File
# Begin Source File

SOURCE="E:\Library\zlib\zconf.h"
# End Source File
# Begin Source File

SOURCE="E:\Library\zlib\zlib.h"
# End Source File
# Begin Source File

SOURCE="E:\Library\zlib\zutil.c"
# End Source File
# Begin Source File

SOURCE="E:\Library\zlib\zutil.h"
# End Source File
# End Group
# Begin Source File

SOURCE=.\blowfish.cpp
# End Source File
# Begin Source File

SOURCE=.\blowfish.h
# End Source File
# Begin Source File

SOURCE=.\blowfish.h2
# End Source File
# Begin Source File

SOURCE=.\ef.cpp
# End Source File
# Begin Source File

SOURCE=.\ef.h
# End Source File
# Begin Source File

SOURCE=.\GameInfo.cpp
# End Source File
# End Target
# End Project
