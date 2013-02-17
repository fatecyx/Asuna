# Microsoft Developer Studio Project File - Name="UndocApiLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=UndocApiLib - Win32 ntdll
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UndocApiLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UndocApiLib.mak" CFG="UndocApiLib - Win32 ntdll"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UndocApiLib - Win32 ntdll" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UndocApiLib - Win32 apphelp" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UndocApiLib - Win32 ws2_32" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UndocApiLib - Win32 zlib" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UndocApiLib - Win32 ucidec" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "UndocApiLib - Win32 user32" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UndocApiLib - Win32 ntdll"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UNDOCAPILIB_EXPORTS" /YX /FD /c
# ADD CPP /nologo /Gr /MD /w /W0 /GR- /O2 /Ob1 /D "UNDOC_LIB_NTDLL" /D "WIN32" /D "NDEBUG" /FD /GS- /GL /MP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/ntdll.dll" /implib:"E:\MyLib\MyLibrary\Library\undoc_ntdll.lib" /ltcg /NOENTRY
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 apphelp"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "UndocApiLib___Win32_apphelp"
# PROP BASE Intermediate_Dir "UndocApiLib___Win32_apphelp"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gr /MD /w /W0 /GR- /O2 /Ob1 /D "UNDOC_LIB_NTDLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UNDOCAPILIB_EXPORTS" /FD /GS- /GL /MP /c
# ADD CPP /nologo /Gr /MD /w /W0 /GR- /O2 /Ob1 /D "UNDOC_LIB_NTDLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UNDOCAPILIB_EXPORTS" /FD /GS- /GL /MP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/ntdll.dll" /implib:"E:\MyLib\MyLibrary\Library\undoc_ntdll.lib" /ltcg /NOENTRY
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/apphelp.dll" /implib:"E:\MyLib\MyLibrary\Library\undoc_apphelp.lib" /ltcg /NOENTRY
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ws2_32"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "UndocApiLib___Win32_ws2_32"
# PROP BASE Intermediate_Dir "UndocApiLib___Win32_ws2_32"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gr /MD /w /W0 /GR- /O2 /Ob1 /D "UNDOC_LIB_NTDLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UNDOCAPILIB_EXPORTS" /FD /GS- /GL /MP /c
# ADD CPP /nologo /Gr /MD /w /W0 /GR- /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FD /GS- /GL /MP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/ntdll.dll" /implib:"E:\MyLib\MyLibrary\Library\undoc_ntdll.lib" /ltcg /NOENTRY
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/WS2_32.dll" /implib:"E:\MyLib\MyLibrary\Library\ws2_32.lib" /ltcg /NOENTRY
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 zlib"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "UndocApiLib___Win32_zlib"
# PROP BASE Intermediate_Dir "UndocApiLib___Win32_zlib"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gr /MD /w /W0 /GR- /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FD /GS- /GL /MP /c
# ADD CPP /nologo /Gr /MD /w /W0 /GR- /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FD /GS- /GL /MP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/WS2_32.dll" /implib:"E:\MyLib\MyLibrary\Library\ws2_32.lib" /ltcg /NOENTRY
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/zlib1.dll" /implib:"E:\MyLib\MyLibrary\Library\zlib1.lib" /ltcg /NOENTRY
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ucidec"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "UndocApiLib___Win32_ucidec"
# PROP BASE Intermediate_Dir "UndocApiLib___Win32_ucidec"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gr /MD /w /W0 /GR- /O2 /Ob1 /D "UNDOC_LIB_NTDLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UNDOCAPILIB_EXPORTS" /FD /GS- /GL /MP /c
# ADD CPP /nologo /Gr /MD /w /W0 /GR- /O2 /Ob1 /D "UNDOC_LIB_NTDLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FD /GS- /GL /MP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/ntdll.dll" /implib:"E:\MyLib\MyLibrary\Library\undoc_ntdll.lib" /ltcg /NOENTRY
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/ucidec.dll" /implib:"E:/MyLib/MyLibrary/Library/ucidec.lib" /ltcg /NOENTRY
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 user32"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "UndocApiLib___Win32_user32"
# PROP BASE Intermediate_Dir "UndocApiLib___Win32_user32"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gr /MD /w /W0 /GR- /O2 /Ob1 /D "UNDOC_LIB_NTDLL" /D "WIN32" /D "NDEBUG" /FD /GS- /GL /MP /c
# ADD CPP /nologo /Gr /MD /w /W0 /GR- /O2 /Ob1 /D "UNDOC_LIB_NTDLL" /D "WIN32" /D "NDEBUG" /FD /GS- /GL /MP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/ntdll.dll" /implib:"E:\MyLib\MyLibrary\Library\undoc_ntdll.lib" /ltcg /NOENTRY
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"Release/USER32.dll" /implib:"E:\MyLib\MyLibrary\Library\undoc_user32.lib" /ltcg /NOENTRY
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "UndocApiLib - Win32 ntdll"
# Name "UndocApiLib - Win32 apphelp"
# Name "UndocApiLib - Win32 ws2_32"
# Name "UndocApiLib - Win32 zlib"
# Name "UndocApiLib - Win32 ucidec"
# Name "UndocApiLib - Win32 user32"
# Begin Group "apphelp"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\undoc_apphelp.cpp

!IF  "$(CFG)" == "UndocApiLib - Win32 ntdll"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 apphelp"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ws2_32"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 zlib"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ucidec"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 user32"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\undoc_apphelp.def

!IF  "$(CFG)" == "UndocApiLib - Win32 ntdll"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 apphelp"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ws2_32"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 zlib"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ucidec"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 user32"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "ntdll"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\undoc_ntdll.cpp

!IF  "$(CFG)" == "UndocApiLib - Win32 ntdll"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 apphelp"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ws2_32"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 zlib"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ucidec"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 user32"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\undoc_ntdll.def

!IF  "$(CFG)" == "UndocApiLib - Win32 ntdll"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 apphelp"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ws2_32"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 zlib"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ucidec"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 user32"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "ws2_32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\undoc_ws2_32.cpp

!IF  "$(CFG)" == "UndocApiLib - Win32 ntdll"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 apphelp"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ws2_32"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 zlib"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ucidec"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 user32"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\undoc_ws2_32.def

!IF  "$(CFG)" == "UndocApiLib - Win32 ntdll"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 apphelp"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ws2_32"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 zlib"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ucidec"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 user32"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "zlib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\zlib1.cpp

!IF  "$(CFG)" == "UndocApiLib - Win32 ntdll"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 apphelp"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ws2_32"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 zlib"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ucidec"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 user32"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\zlib1.def

!IF  "$(CFG)" == "UndocApiLib - Win32 ntdll"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 apphelp"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ws2_32"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 zlib"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ucidec"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 user32"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "ucidec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ucidec.cpp

!IF  "$(CFG)" == "UndocApiLib - Win32 ntdll"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 apphelp"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ws2_32"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 zlib"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ucidec"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 user32"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ucidec.def

!IF  "$(CFG)" == "UndocApiLib - Win32 ntdll"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 apphelp"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ws2_32"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 zlib"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ucidec"

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 user32"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "user32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\undoc_user32.cpp
# End Source File
# Begin Source File

SOURCE=.\undoc_user32.def

!IF  "$(CFG)" == "UndocApiLib - Win32 ntdll"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 apphelp"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ws2_32"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 zlib"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 ucidec"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "UndocApiLib - Win32 user32"

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
