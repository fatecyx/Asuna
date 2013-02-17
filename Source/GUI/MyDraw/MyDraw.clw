; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChildView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MyDraw.h"
LastPage=0

ClassCount=4
Class1=CMyDrawApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=2
Resource1=IDD_ABOUTBOX
Class2=CChildView
Resource2=IDR_MAINFRAME

[CLS:CMyDrawApp]
Type=0
HeaderFile=MyDraw.h
ImplementationFile=MyDraw.cpp
Filter=N
LastObject=CMyDrawApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N
LastObject=CChildView
BaseClass=CWnd 
VirtualFilter=WC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=MyDraw.cpp
ImplementationFile=MyDraw.cpp
Filter=D

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_LINE_DDA
Command2=ID_LINE_MIDPOINT
Command3=ID_LINE_BH
Command4=ID_LINE_DEFAULT
Command5=ID_CIRCLE_MP
Command6=ID_COLOR_EDIT
Command7=ID_FILL_RECT
Command8=ID_CROP_ENC
Command9=ID_3D_DIMETRIC
Command10=ID_3D_CABINET
Command11=ID_3D_LOOKAT
CommandCount=11

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_LINE_DEFAULT
Command2=ID_LINE_DDA
Command3=ID_LINE_MIDPOINT
Command4=ID_LINE_BH
Command5=ID_CIRCLE_MP
Command6=ID_FILL_RECT
Command7=ID_COLOR_EDIT
Command8=ID_CROP_ENC
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
CommandCount=1

