# Microsoft Developer Studio Project File - Name="Babylon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Babylon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Babylon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Babylon.mak" CFG="Babylon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Babylon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Babylon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Babylon - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Gr /MD /W3 /GR- /O1 /I "../mylib" /I "../" /I "../common" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "UNICODE" /D "_UNICODE" /FD /GL /GS- /MP4 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"../Babylon.exe" /ltcg /DYNAMICBASE:NO
# SUBTRACT LINK32 /pdb:none /debug

!ELSEIF  "$(CFG)" == "Babylon - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Babylon - Win32 Release"
# Name "Babylon - Win32 Debug"
# Begin Group "common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\bl_common.h
# End Source File
# Begin Source File

SOURCE=..\common\bl_plugin.h
# End Source File
# Begin Source File

SOURCE=..\common\my_xml.h
# End Source File
# End Group
# Begin Group "mylib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\mylib\FileDisk.h
# End Source File
# Begin Source File

SOURCE=..\mylib\ImageCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\mylib\ImageCtrl.h
# End Source File
# Begin Source File

SOURCE=..\mylib\RichEditCtl.cpp
# End Source File
# Begin Source File

SOURCE=..\mylib\RichEditCtl.h
# End Source File
# Begin Source File

SOURCE=..\mylib\WindowBase.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Babylon.cpp
# End Source File
# Begin Source File

SOURCE=.\Babylon.h
# End Source File
# Begin Source File

SOURCE=.\Babylon.rc
# End Source File
# Begin Source File

SOURCE=.\CtrlText.cpp
# End Source File
# Begin Source File

SOURCE=.\CtrlText.h
# End Source File
# Begin Source File

SOURCE=.\ID.h
# End Source File
# Begin Source File

SOURCE=.\Kanade.ico
# End Source File
# Begin Source File

SOURCE=.\MenuInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ScriptDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptDialog.h
# End Source File
# Begin Source File

SOURCE=.\ScriptParser.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptParser.h
# End Source File
# Begin Source File

SOURCE=.\TreeViewCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeViewCtrl.h
# End Source File
# Begin Source File

SOURCE=.\WinMain.cpp
# End Source File
# Begin Source File

SOURCE=.\XPStyle.manifest
# End Source File
# End Target
# End Project
