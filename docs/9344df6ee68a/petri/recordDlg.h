#if !defined(AFX_RECORDDLG_H__81A93E48_38ED_45CD_97B6_2FC784D18D85__INCLUDED_)
#define AFX_RECORDDLG_H__81A93E48_38ED_45CD_97B6_2FC784D18D85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// recordDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// recordDlg dialog

class recordDlg : public CDialog
{
// Construction
public:
	recordDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(recordDlg)
	enum { IDD = IDD_DIALOG1 };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(recordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(recordDlg)
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDDLG_H__81A93E48_38ED_45CD_97B6_2FC784D18D85__INCLUDED_)
