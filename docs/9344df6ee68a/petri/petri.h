// petri.h : main header file for the PETRI application
//

#if !defined(AFX_PETRI_H__CF2DAFF4_15F6_41FE_831C_ADA8AAD8D2D3__INCLUDED_)
#define AFX_PETRI_H__CF2DAFF4_15F6_41FE_831C_ADA8AAD8D2D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPetriApp:
// See petri.cpp for the implementation of this class
//

class CPetriApp : public CWinApp
{
public:
	CPetriApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPetriApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPetriApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PETRI_H__CF2DAFF4_15F6_41FE_831C_ADA8AAD8D2D3__INCLUDED_)
