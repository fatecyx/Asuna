# Microsoft Developer Studio Project File - Name="j6win" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=j6win - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "j6win.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "j6win.mak" CFG="j6win - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "j6win - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "J6WIN_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "J6WIN_EXPORTS" /FD /GS- /GL /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"E:\Desktop\§Ø•Œ“ªΩ€π£\j6_sc.dll" /ltcg
# SUBTRACT LINK32 /pdb:none
# Begin Target

# Name "j6win - Win32 Release"
# Begin Source File

SOURCE=.\EncryptText\aes.h
# End Source File
# Begin Source File

SOURCE=.\EncryptText\aes_x86_v2.asm
# Begin Custom Build
InputDir=.\EncryptText
IntDir=.\Release
InputPath=.\EncryptText\aes_x86_v2.asm
InputName=aes_x86_v2

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	yasm -I$(InputDir) -f win32 -O2 -DPREFIX -DNON_MOD16_STACK -DBIT_DEPTH=8 -o "$(IntDir)\$(InputName)".obj "$(InputPath)"

# End Custom Build
# End Source File
# Begin Source File

SOURCE=.\j6_sc.def
# End Source File
# Begin Source File

SOURCE=.\j6win.cpp
# End Source File
# Begin Source File

SOURCE=.\EncryptText\sha2.c
# End Source File
# Begin Source File

SOURCE=.\EncryptText\sha2.h
# End Source File
# Begin Source File

SOURCE=.\TextHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\TextHandler.h
# End Source File
# End Target
# End Project
