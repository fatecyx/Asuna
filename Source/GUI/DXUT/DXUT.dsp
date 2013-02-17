# Microsoft Developer Studio Project File - Name="DXUT" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DXUT - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DXUT.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DXUT.mak" CFG="DXUT - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DXUT - Win32 Release" (based on "Win32 (x86) Application")
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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Gr /MD /W4 /GR- /Z7 /O2 /Ob1 /I "../../Hooks/D3DHook/DXUT" /D USE_NT_VER=1 /D "WIN32" /D "NDEBUG" /D "UNICODE" /D "_UNICODE" /FD /GL /GS- /MP /arch:SSE /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 mylib_nt.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"DXUT.exe" /ltcg /fixed /ignore:4197
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "DXUT - Win32 Release"
# Begin Group "DXUT"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\..\Library\DXSDK\Samples\C++\DXUT\Core\DXUT.cpp"
# End Source File
# Begin Source File

SOURCE=../../Hooks/D3DHook/DXUT/DXUT.h
# End Source File
# Begin Source File

SOURCE=..\..\Hooks\D3DHook\DXUT\DXUTConfig.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\Library\DXSDK\Samples\C++\DXUT\Core\DXUTenum.cpp"
# End Source File
# Begin Source File

SOURCE=../../Hooks/D3DHook/DXUT/DXUTgui.cpp
# End Source File
# Begin Source File

SOURCE=../../Hooks/D3DHook/DXUT/DXUTgui.h
# End Source File
# Begin Source File

SOURCE=../../Hooks/D3DHook/DXUT/DXUTmisc.cpp
# End Source File
# Begin Source File

SOURCE=../../Hooks/D3DHook/DXUT/DXUTmisc.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DXUT.def
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DXUTDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\TextDef.h
# End Source File
# End Target
# End Project
