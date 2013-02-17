# Microsoft Developer Studio Project File - Name="nitroplus" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=nitroplus - Win32 GUILTY_CROWN_LOST_XMAS
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nitroplus.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nitroplus.mak" CFG="nitroplus - Win32 GUILTY_CROWN_LOST_XMAS"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nitroplus - Win32 GUILTY_CROWN_LOST_XMAS" (based on "Win32 (x86) Console Application")
!MESSAGE "nitroplus - Win32 axanael" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "nitroplus - Win32 GUILTY_CROWN_LOST_XMAS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "nitroplus___Win32_GUILTY_CROWN_LOST_XMAS"
# PROP BASE Intermediate_Dir "nitroplus___Win32_GUILTY_CROWN_LOST_XMAS"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gr /MD /W4 /O2 /Ob1 /D USE_NT_VER=1 /D "WIN32" /D GUILTY_CROWN_LOST_XMAS_TRAILER=1 /FD /GS- /GL /MP /c
# ADD CPP /nologo /Gr /MD /W4 /O2 /Ob1 /D USE_NT_VER=1 /D "WIN32" /D GUILTY_CROWN_LOST_XMAS_TRAILER=1 /FD /GS- /GL /MP /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mylib_nt.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"nitroplus.exe" /ltcg /fixed
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 mylib_nt.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"gclx_upk.exe" /ltcg /fixed
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "nitroplus - Win32 axanael"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "nitroplus___Win32_axanael"
# PROP BASE Intermediate_Dir "nitroplus___Win32_axanael"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gr /MD /W4 /O2 /Ob1 /D USE_NT_VER=1 /D "WIN32" /D GUILTY_CROWN_LOST_XMAS_TRAILER=1 /FD /GS- /GL /MP /c
# ADD CPP /nologo /Gr /MD /W4 /O2 /Ob1 /D USE_NT_VER=1 /D "WIN32" /D AXANAEL=1 /FD /GS- /GL /MP /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mylib_nt.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"nitroplus.exe" /ltcg /fixed
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 mylib_nt.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"axanael_upk.exe" /ltcg /fixed
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "nitroplus - Win32 GUILTY_CROWN_LOST_XMAS"
# Name "nitroplus - Win32 axanael"
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\nitroplus.cpp
# End Source File
# Begin Source File

SOURCE=.\nitroplus.h
# End Source File
# End Target
# End Project
