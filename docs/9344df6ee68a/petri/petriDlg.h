// petriDlg.h : header file
//

#if !defined(AFX_PETRIDLG_H__1122602F_AC35_4E67_8D6E_172A7EE0356C__INCLUDED_)
#define AFX_PETRIDLG_H__1122602F_AC35_4E67_8D6E_172A7EE0356C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPetriDlg dialog
//#include "recordDlg.h"
#include "LinkQueue.h"
#define WM_CHILDCLOSE WM_USER+2
class CPetriDlg : public CDialog
{
// Construction
public:
	void manage();
	CPetriDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPetriDlg)
	enum { IDD = IDD_PETRI_DIALOG };
	CStatic	m_ser_int;
	CStatic	m_sel_int;
	CStatic	m_arrive_int;
	CStatic	m_out;
	CSpinButtonCtrl	m_spin;
	CStatic	m_dis;
	CStatic	m_rest;
	CStatic	m_leave;
	CStatic	m_sel;
	CStatic	m_queue;
	CStatic	m_bar;
	CStatic	m_ctr_time;
	float	m_arrive_mean;
	float	m_search_mean;
	float	m_service_mean;
	int		m_timeacc;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPetriDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	public:
		CString TimeConver(int second);
		float random();
		void update();
		int getArriveTime();
		int getSelectTime();
		int getServiceTime();
		void finish();
		void select();
		void arrive();
		void bargin();
		int now_time;
		tag_select_finish select_finish[50];
		int index;
		int i;
//		int z1;
		int z0;
//		bool rand_flag;
		tag_event event;
		tag_place place;
		tag_client client[1000];
		//TEST
		int service_ran;
		CBrush m_brush;
		CLinkQueue m_linkQueue;
		CString info;
		//CString outlist1;
		int mean_long;
		int mean_stay_time;
		int mean_work_time;
	//	recordDlg m_dlg1;
	//	recordDlg m_recordDlg;
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPetriDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditTimeacc();
	afx_msg void OnButtonRestart();
	afx_msg void OnChangeEditArrive();
	afx_msg void OnChangeEditSearch();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButtonRecord();
	afx_msg void OnChildClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PETRIDLG_H__1122602F_AC35_4E67_8D6E_172A7EE0356C__INCLUDED_)
