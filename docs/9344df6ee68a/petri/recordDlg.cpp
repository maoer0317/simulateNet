// recordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "petri.h"
#include "recordDlg.h"

#define WM_CHILDCLOSE  WM_USER+2

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// recordDlg dialog


recordDlg::recordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(recordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(recordDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void recordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(recordDlg)
	DDX_Control(pDX, IDC_LIST2, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(recordDlg, CDialog)
	//{{AFX_MSG_MAP(recordDlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// recordDlg message handlers

void recordDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CWnd* pMain;
	pMain=GetParent();
	if(NULL!=pMain)
	{
		pMain->SendMessage(WM_CHILDCLOSE);
	}
//		MessageBox("have main");
//	MessageBox("haha");

	CDialog::OnClose();
}
