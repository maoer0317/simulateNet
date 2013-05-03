; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPetriDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "petri.h"

ClassCount=4
Class1=CPetriApp
Class2=CPetriDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_DIALOGBAR (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_PETRI_DIALOG
Class4=recordDlg
Resource5=IDD_DIALOG1

[CLS:CPetriApp]
Type=0
HeaderFile=petri.h
ImplementationFile=petri.cpp
Filter=N

[CLS:CPetriDlg]
Type=0
HeaderFile=petriDlg.h
ImplementationFile=petriDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_STATIC_LIST

[CLS:CAboutDlg]
Type=0
HeaderFile=petriDlg.h
ImplementationFile=petriDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PETRI_DIALOG]
Type=1
Class=CPetriDlg
ControlCount=29
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC_TIME,static,1342308352
Control4=IDC_STATIC_SEL,static,1342308352
Control5=IDC_STATIC_QUEUE,static,1342308352
Control6=IDC_STATIC_BAR,static,1342308352
Control7=IDC_STATIC_LEV,static,1342308352
Control8=IDC_STATIC_REST,static,1342308352
Control9=IDC_STATIC_DIS,static,1342308352
Control10=IDC_EDIT_TIMEACC,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_ARRIVE,edit,1350631552
Control16=IDC_EDIT_SEARCH,edit,1350631552
Control17=IDC_EDIT_SERVICE,edit,1350631552
Control18=IDC_SPIN1,msctls_updown32,1342177330
Control19=IDC_BUTTON_RESTART,button,1342242816
Control20=IDC_STATIC_OUT,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC_ARRIVE_INT,static,1342308352
Control25=IDC_STATIC_SEL_INT,static,1342308352
Control26=IDC_STATIC_SER_INT,static,1342308352
Control27=IDC_STATIC,static,1342177294
Control28=IDC_BUTTON_RECORD,button,1342242816
Control29=IDC_STATIC_LIST,static,1342308352

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG1]
Type=1
Class=recordDlg
ControlCount=1
Control1=IDC_LIST2,listbox,1353777409

[CLS:recordDlg]
Type=0
HeaderFile=recordDlg.h
ImplementationFile=recordDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

