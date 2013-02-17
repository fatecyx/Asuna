# Microsoft Developer Studio Project File - Name="pinonono" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=pinonono - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pinonono.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pinonono.mak" CFG="pinonono - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pinonono - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "pinonono - Win32 Release_fin" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pinonono - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "pinonono___Win32_Release"
# PROP BASE Intermediate_Dir "pinonono___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PINONONO_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PINONONO_EXPORTS" /D "MY_DEBUG" /FD /GL /GS- /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"K:\galgame\盛开的钢琴之森下\piano.dll" /ltcg /noentry
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "pinonono - Win32 Release_fin"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "pinonono___Win32_Release_fin"
# PROP BASE Intermediate_Dir "pinonono___Win32_Release_fin"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PINONONO_EXPORTS" /FD /GL /GS- /c
# ADD CPP /nologo /MD /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PINONONO_EXPORTS" /FD /GL /GS- /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"K:\galgame\盛开的钢琴之森下\piano.dll" /ltcg /noentry
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"K:\galgame\盛开的钢琴之森下\piano.dll" /ltcg /noentry
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "pinonono - Win32 Release"
# Name "pinonono - Win32 Release_fin"
# Begin Group "libvorbis"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\libvorbis\codec.h
# End Source File
# Begin Source File

SOURCE=.\libvorbis\ogg.h
# End Source File
# Begin Source File

SOURCE=.\libvorbis\os_types.h
# End Source File
# Begin Source File

SOURCE=.\libvorbis\vorbisfile.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AudioPlayback.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioPlayback.h
# End Source File
# Begin Source File

SOURCE=.\piano.cpp
# End Source File
# Begin Source File

SOURCE=.\piano.def

!IF  "$(CFG)" == "pinonono - Win32 Release"

!ELSEIF  "$(CFG)" == "pinonono - Win32 Release_fin"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\piano.h
# End Source File
# Begin Source File

SOURCE=.\piano_fin.def

!IF  "$(CFG)" == "pinonono - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "pinonono - Win32 Release_fin"

!ENDIF 

# End Source File
# End Target
# End Project
