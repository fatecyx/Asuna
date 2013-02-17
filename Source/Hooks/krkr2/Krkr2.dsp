# Microsoft Developer Studio Project File - Name="krkr2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=KRKR2 - WIN32 MAHOYO
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "krkr2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "krkr2.mak" CFG="KRKR2 - WIN32 MAHOYO"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "krkr2 - Win32 Mahoyo" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "krkr2 - Win32 Tenshin" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "krkr2 - Win32 Mahoyo"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "krkr2___Win32_Mahoyo"
# PROP BASE Intermediate_Dir "krkr2___Win32_Mahoyo"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gr /MD /W4 /O2 /Ob1 /D USE_NT_VER=1 /D "WIN32" /D "NDEBUG" /D MAHOYO=1 /FD /GL /GS- /MP /c
# ADD CPP /nologo /Gr /MD /W4 /GR- /O2 /Ob1 /D MAHOYO=1 /D USE_NT_VER=1 /D "WIN32" /D "NDEBUG" /D "SUPPORT_AAC_DECODE" /FD /GL /GS- /MP /arch:SSE /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mylib_nt.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"krkr2.dll" /ltcg
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 mylib_nt.lib msvcrt.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"mahoyo.dll" /ltcg /DELAYLOAD:ucxdec.dll
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "krkr2 - Win32 Tenshin"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "krkr2___Win32_Tenshin"
# PROP BASE Intermediate_Dir "krkr2___Win32_Tenshin"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gr /MD /W4 /GR- /O2 /Ob1 /D MAHOYO=1 /D USE_NT_VER=1 /D "WIN32" /D "NDEBUG" /D "SUPPORT_AAC_DECODE" /FD /GL /GS- /MP /arch:SSE /c
# ADD CPP /nologo /Gr /MD /W4 /GR- /O2 /Ob1 /D TENSHIN=1 /D USE_NT_VER=1 /D "WIN32" /D "NDEBUG" /D SUPPORT_AAC_DECODE=0 /FD /GL /GS- /MP /arch:SSE /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 mylib_nt.lib msvcrt.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"mahoyo.dll" /ltcg /DELAYLOAD:ucxdec.dll
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 mylib_nt.lib msvcrt.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"tenshin.dll" /ltcg /DELAYLOAD:ucxdec.dll
# SUBTRACT LINK32 /pdb:none /debug

!ENDIF 

# Begin Target

# Name "krkr2 - Win32 Mahoyo"
# Name "krkr2 - Win32 Tenshin"
# Begin Source File

SOURCE=.\AudioDecoder.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioDecoder.h
# End Source File
# Begin Source File

SOURCE=.\Cxdex_DecryptBlock.h
# End Source File
# Begin Source File

SOURCE=.\Extension.cpp
# End Source File
# Begin Source File

SOURCE=.\HookStub.cpp
# End Source File
# Begin Source File

SOURCE=.\krkr2.cpp
# End Source File
# Begin Source File

SOURCE=.\krkr2.def
# End Source File
# Begin Source File

SOURCE=.\krkr2.h
# End Source File
# Begin Source File

SOURCE=.\Krkr2AudioDecoder.cpp
# End Source File
# Begin Source File

SOURCE=.\Krkr2AudioDecoder.h
# End Source File
# End Target
# End Project
