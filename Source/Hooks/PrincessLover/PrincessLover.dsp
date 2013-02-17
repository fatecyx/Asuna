# Microsoft Developer Studio Project File - Name="PrincessLover" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PrincessLover - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PrincessLover.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PrincessLover.mak" CFG="PrincessLover - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PrincessLover - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PrincessLover - Win32 LocalEmulator" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PrincessLover - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PRINCESSLOVER_EXPORTS" /YX /FD /c
# ADD CPP /nologo /Gr /MD /W4 /GR- /O2 /Ob1 /D "MY_DEBUG" /D USE_NT_VER=1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SUPPORT_AAC_DECODE" /D "UNICODE" /D "_UNICODE" /FD /GS- /GL /MP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 MyLib_NT.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"K:\galgame\¥×¥ê¥ó¥»¥¹¥é¥Ð©`\Sharu.dll" /ltcg /DELAYLOAD:ucadec.dll /DELAYLOAD:bass.dll /DELAYLOAD:bass_aac.dll /DELAYLOAD:ucidec.dll /DELAYLOAD:GDI32.dll
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "PrincessLover - Win32 LocalEmulator"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "PrincessLover___Win32_LocalEmulator"
# PROP BASE Intermediate_Dir "PrincessLover___Win32_LocalEmulator"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gr /MD /W3 /O2 /Ob1 /D USE_NT_VER=1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MY_DEBUG" /D "SUPPORT_AAC_DECODE" /FD /D /GL /GS- /QIfist /MP /c
# ADD CPP /nologo /Gr /MD /W3 /O2 /Ob1 /D "MY_DEBUG" /D LOCALE_EMULATOR_ONLY=1 /D USE_NT_VER=1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FD /GL /GS- /QIfist /MP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 MyLib_NT.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"F:\galgame\¥×¥ê¥ó¥»¥¹¥é¥Ð©`\Sharu.dll" /ltcg /DELAYLOAD:ucadec.dll /DELAYLOAD:bass.dll /DELAYLOAD:bass_aac.dll /DELAYLOAD:ucidec.dll /DELAYLOAD:USER32.dll /DELAYLOAD:GDI32.dll /DELAYLOAD:COMCTL32.dll
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 MyLib_NT.lib ntdll.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"F:\galgame\¥×¥ê¥ó¥»¥¹¥é¥Ð©`\LocaleEmulator.dll" /ltcg
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "PrincessLover - Win32 Release"
# Name "PrincessLover - Win32 LocalEmulator"
# Begin Source File

SOURCE=.\LocaleEmulator.cpp

!IF  "$(CFG)" == "PrincessLover - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "PrincessLover - Win32 LocalEmulator"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PrincessLover.cpp
# End Source File
# Begin Source File

SOURCE=.\PrincessLover.def

!IF  "$(CFG)" == "PrincessLover - Win32 Release"

!ELSEIF  "$(CFG)" == "PrincessLover - Win32 LocalEmulator"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PrincessLover.h
# End Source File
# End Target
# End Project
