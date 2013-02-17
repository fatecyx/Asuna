# Microsoft Developer Studio Project File - Name="BinarySplitter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BinarySplitter - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BinarySplitter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BinarySplitter.mak" CFG="BinarySplitter - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BinarySplitter - Win32 Release" (based on "Win32 (x86) Application")
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
# ADD CPP /nologo /Gr /MD /W4 /GR- /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_7ZIP_ST" /D "UNICODE" /D "_UNICODE" /FD /GL /GS- /MP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"BinarySplitter.exe" /LTCG /FIXED
# SUBTRACT LINK32 /pdb:none /debug
# Begin Target

# Name "BinarySplitter - Win32 Release"
# Begin Group "LZMA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\Library\LZMA\C\Bra86.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Library\LZMA\C\LzFind.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Library\LZMA\C\LzFind.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Library\LZMA\C\Lzma86.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Library\LZMA\C\Lzma86Dec.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Library\LZMA\C\Lzma86Enc.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Library\LZMA\C\LzmaDec.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Library\LZMA\C\LzmaDec.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Library\LZMA\C\LzmaEnc.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\..\..\Library\LZMA\C\LzmaEnc.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "aes128"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\MyLib\cls\aes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\MyLib\cls\aes_x86_v2.asm
# Begin Custom Build
InputDir=\MyLib\cls
IntDir=.\Release
InputPath=..\..\..\..\MyLib\cls\aes_x86_v2.asm
InputName=aes_x86_v2

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	yasm -I$(InputDir) -f win32 -O2 -DPREFIX -DNON_MOD16_STACK -DBIT_DEPTH=8 -o "$(IntDir)\$(InputName)".obj "$(InputPath)"

# End Custom Build
# End Source File
# End Group
# Begin Group "sha256"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\MyLib\include\sha256.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\MyLib\include\sha256.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\BinarySplitter.rc
# End Source File
# Begin Source File

SOURCE=.\BinarySplitterMsg.h
# End Source File
# Begin Source File

SOURCE=.\ControllerSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\ControllerSplitter.h
# End Source File
# Begin Source File

SOURCE=.\DialogSplit.h
# End Source File
# Begin Source File

SOURCE=.\memcpy.asm
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1
# End Source File
# Begin Source File

SOURCE=.\ModelSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelSplitter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\MyLib\src\my_api.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\MyLib\src\my_crtadd.cpp
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ViewSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewSplitter.h
# End Source File
# Begin Source File

SOURCE=.\WinMain.cpp
# End Source File
# Begin Source File

SOURCE=.\XPStyle.manifest
# End Source File
# End Target
# End Project
