// petriDlg.cpp : implementation file
//

#include "stdafx.h"
#include "petri.h"
#include "petriDlg.h"

#include "recordDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#define SIM_TIME 14400  //总仿真时间14400s  即8：00-12：00

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPetriDlg dialog

CPetriDlg::CPetriDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPetriDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPetriDlg)
	m_arrive_mean = 0.4f;
	m_search_mean = 1.5f;
	m_service_mean = 0.5f;
	m_timeacc = 5;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	rand_flag=true;
//	z1=11;
	i=0;
	z0=(unsigned)time( NULL )%2987;
	m_linkQueue.InitQueue();
}

void CPetriDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPetriDlg)
	DDX_Control(pDX, IDC_STATIC_SER_INT, m_ser_int);
	DDX_Control(pDX, IDC_STATIC_SEL_INT, m_sel_int);
	DDX_Control(pDX, IDC_STATIC_ARRIVE_INT, m_arrive_int);
	DDX_Control(pDX, IDC_STATIC_OUT, m_out);
	DDX_Control(pDX, IDC_SPIN1, m_spin);
	DDX_Control(pDX, IDC_STATIC_DIS, m_dis);
	DDX_Control(pDX, IDC_STATIC_REST, m_rest);
	DDX_Control(pDX, IDC_STATIC_LEV, m_leave);
	DDX_Control(pDX, IDC_STATIC_SEL, m_sel);
	DDX_Control(pDX, IDC_STATIC_QUEUE, m_queue);
	DDX_Control(pDX, IDC_STATIC_BAR, m_bar);
	DDX_Control(pDX, IDC_STATIC_TIME, m_ctr_time);
	DDX_Text(pDX, IDC_EDIT_ARRIVE, m_arrive_mean);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_search_mean);
	DDX_Text(pDX, IDC_EDIT_SERVICE, m_service_mean);
	DDX_Text(pDX, IDC_EDIT_TIMEACC, m_timeacc);
	DDV_MinMaxInt(pDX, m_timeacc, 1, 100);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPetriDlg, CDialog)
	//{{AFX_MSG_MAP(CPetriDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_EN_CHANGE(IDC_EDIT_TIMEACC, OnChangeEditTimeacc)
	ON_BN_CLICKED(IDC_BUTTON_RESTART, OnButtonRestart)
	ON_EN_CHANGE(IDC_EDIT_ARRIVE, OnChangeEditArrive)
	ON_EN_CHANGE(IDC_EDIT_SEARCH, OnChangeEditSearch)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnButtonRecord)
	ON_MESSAGE(WM_CHILDCLOSE,OnChildClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPetriDlg message handlers

BOOL CPetriDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_brush.CreateSolidBrush(RGB(255,251,240));
	// TODO: Add extra initialization here
	SetTimer(1,1000/m_timeacc,NULL);
	//SetTimer(1,1000,NULL);
	for(int j=0;j<50;j++)
	{
		select_finish[j].time=14400;
		select_finish[j].num=0;
	}
	now_time=0;
	index=0;

	mean_long=0;
	mean_stay_time=0;
	mean_work_time=0;

	place.bargin_zone=0;
	place.leave=0;
	place.queue=0;
	place.rest=1;
	place.select=0;
	event.arrive_time=getArriveTime();
	CString str;
	str.Format("%d",event.arrive_time);
	m_arrive_int.SetWindowText(str);
	client[0].sn=0;
	client[0].arrive_time=event.arrive_time;
	//select_finish[0]=event.arrive_time+getSelectTime();
	//event.finish_time=getServiceTime();
	event.finish_time=20;
	event.select_time=getSelectTime();
	client[0].select_time=event.select_time;
	client[0].select_finish=client[0].arrive_time+client[0].select_time;
	select_finish[0].time=client[0].select_finish;
	//m_linkQueue.QInsert(client[0]);
	str.Format("%d",event.select_time);
	m_sel_int.SetWindowText(str);
	m_ctr_time.SetWindowText("8:00");
	
	m_spin.SetBuddy(GetDlgItem(IDC_EDIT_TIMEACC));
	m_spin.SetRange(1,100);
	m_spin.SetPos(m_timeacc);

	//queue init

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPetriDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPetriDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPetriDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPetriDlg::manage()           //总控程序 4个变迁处理子程序
{
	if(now_time<=SIM_TIME)
	{
		if(now_time>=event.finish_time)
		{
			finish();
		}
		if(place.rest==1 && place.queue>=1)
		{
			bargin(); 
		}
		if(now_time>=event.arrive_time)
		{
			arrive();
		}
		if(place.select>=1)
		{
			select();
		}	
	}
	else
		KillTimer(1);
}

void CPetriDlg::bargin()
{
	place.rest=0;
	int next_time=getServiceTime();
	CString str;
	str.Format("%d",next_time);
	m_ser_int.SetWindowText(str);
	place.queue-=1;
	place.bargin_zone+=1;
	event.finish_time=now_time+next_time;
	
	int index;
	index=m_linkQueue.QDelete();
	client[index].bargin_begin=now_time;
	client[index].service_time=next_time;

	info.Format("顾客ID:%d,",client[index].sn+1);
	info+="到达:";
	info+=TimeConver(client[index].arrive_time);
	str.Format(",选购:%ds",client[index].select_time);
	info+=str;
	str.Format(",排队:%ds,",client[index].bargin_begin-client[index].select_finish-1);
	info+=str;
	info+="结算开始:";
	info+=TimeConver(client[index].bargin_begin);
	str.Format(",结算时间:%ds,",client[index].service_time);
	info+=str;
	info+="离开:";
	info+=TimeConver(client[index].bargin_begin+client[index].service_time);
//	str_record+=info;
//	str_record+="\n";
	//m_outlist.Format("%d",5);
	mean_stay_time+=client[index].service_time+
		             client[index].bargin_begin-client[index].select_finish-1;
	mean_work_time+=client[index].service_time;
	//m_dis.SetWindowText(str);
	
}

void CPetriDlg::arrive()
{
	i+=1;
	int next_time=getArriveTime();
	int next_sel_time=getSelectTime();
	CString str;
	str.Format("%d",next_time);
	m_arrive_int.SetWindowText(str);
	str.Format("%d",next_sel_time);
	m_sel_int.SetWindowText(str);
	event.arrive_time=now_time+next_time;
	place.select+=1;
	client[i].sn=i;
	client[i].arrive_time=event.arrive_time;
	client[i].select_time=next_sel_time;
	client[i].select_finish=client[i].arrive_time+client[i].select_time;
	for(int j=0;j<50;j++)
	{
		if(select_finish[j].time==14400)
		{
			select_finish[j].time=client[i].select_finish;
			select_finish[j].num=client[i].sn;
			break;
		}
		else
		{
			select_finish[49].time=14400;
		}
	}
}

//判断选购是否结束 若结束送入队列区
void CPetriDlg::select()
{

	int temp;
	temp=select_finish[0].time;
	int min;
	int index;
	for(int j=0;j<50;j++)
	{
		if(select_finish[j].time<=temp)
		{
			temp=select_finish[j].time;
			min=j;
			index=select_finish[j].num;
		}
	}
	if(now_time>=temp)
	{
		place.select-=1;
		place.queue+=1;
		mean_long=(mean_long+place.queue)/2;
		select_finish[min].time=14400;
		m_linkQueue.QInsert(client[index]);
	}
}

void CPetriDlg::finish()
{
	recordDlg* child;
	child=(recordDlg*)FindWindow(NULL,"Record");

	place.rest=1;
	if(place.bargin_zone>=1)
	{
		place.bargin_zone-=1;
		place.leave+=1;
		m_dis.SetWindowText(info);
		CString str;
		str.Format("平均队伍长度:%d,滞留时间:%d,工作时间%d",
			        mean_long,mean_stay_time/place.leave,mean_work_time/place.leave);
		m_out.SetWindowText(str);
		str.Format("%4d%16d%16d%20d%16d%16d",
			       client[index].sn+1,client[index].arrive_time,
				   client[index].select_time,
				   client[index].bargin_begin,client[index].service_time,
				   client[index].bargin_begin+client[index].service_time);
		if(NULL!=child)
		{
			child->m_list.AddString(info);
			child->m_list.SetCurSel(place.leave);
		//	MessageBox("have child");
		}
	}
}

int CPetriDlg::getServiceTime()
{
		/*服务耗时服从gamma分布，期望a*b，平均耗时为m_service_mean,
	  选取参数(形状参数)a=2，b=m_service_mean/a;
	  若x~gamma(a,1), 则当y=b*x(b>0)时，y~gamma(a,b);
	  算法：gamma(a,1)的舍选法步骤：
	  1，独立产生u1~U(0,1),u2~U(0,1);
	  2, 令V=(2*a-1)^(1/2)*log( u2/(1-u2) );
	  3, 若log(u1*u2^2)< a-log(4)+( sqrt(2*a-1) )*V-a*exp(V);
	     则选取，令x=a*exp(V),否则，舍弃，返回第一步。*/
	int a=2;
	int b=(int)(m_service_mean*60/a);
	float u1;
	float u2;
	double v;
	double y;
	double left,right;

	do{
		u1=random();
		u2=random();
		//v=sqrt(2*a-1)*log( u2/(1-u2) );
		v=1.732*log( u2/(1-u2) );
		left=log(u1*u2*u2);
		//right=a-log(4)+(sqrt(2*a-1))*v-a*exp(v);
		right=0.6137+1.73*v-2*exp(v);
	}
	while(left>right);
	y=b*a*exp(v);
    service_ran=(int)y;
	//CString str;
	//str.Format("u1:%f,,u2:%f,,v:%f,,left:%f,\n,right:%f,,y:%f,,",
	//	         u1,u2,v,left,right,y);
	//MessageBox(str);
	//m_out.SetWindowText(str);
	return (int)y;
//	return 40;

/*	float y;
	float r,v,c;
	float right;
	r=sqrt(2*a-1);
	v=pow(a,r);
	c=16*exp(-a)/r;
	float u_temp;
	float temp1,temp2;
	temp1=pow(u2,r-1);
	temp2=pow(u2,r);

	do{
		u1=random();
		u_temp=random();
		u2=pow( (v*u_temp/(1-u_temp)),(1/r) );
		right=u2*exp(-u2)*( (v+temp2)*(v+temp2) )/	( 16*exp(-2)*v*temp1 );
		//	( 16*exp(-2)*v*temp1 )/( (v+temp2)*(v+temp2) );
	}
	while(u1<=right);
    y=b*u2;*/
  
}

int CPetriDlg::getSelectTime()
{	
	//服从维布尔分布
	/*
	f(y)= (b/a)*((y-v)/a)^(b-1)*exp( -( (y-v)/a )^b ),  y>=v;
	      0                                          ,  y<v;

	参数设置：v=60*m_select_time-a;
	          a=5;
			  b=1;
	*/
	float a=15;
	float b=1;
	float v=60*m_search_mean-a;

	float u1;
	int y;
	u1=random();
	y=int(v+a*(-log(u1)));  //y=y=v+a*(-log(u1))^(1/b);
	return y;               // seconds test
}

int CPetriDlg::getArriveTime()
{
	//服从指数分布
	float x=random();
	int y;
	y=int( (-m_arrive_mean*60)*log(fabs(x)) );
	if(y==0)
		y=1;
    return y;
//	return 1;
}

void CPetriDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	now_time+=1;
	manage();
	CString str;
	int hour;
	int minite;
	int second;
	hour=(int)now_time/3600;
	minite=((int)now_time%3600)/60;
	second=(int)now_time%3600%60;
	str.Format("%d:%d:%d",8+hour,minite,second);
	m_ctr_time.SetWindowText(str);
	update();
	CDialog::OnTimer(nIDEvent);
	
	random();
}

void CPetriDlg::update()
{
	CString str;
	str.Format("%d",place.select);
	m_sel.SetWindowText(str);
	str.Format("%d",place.queue);
	m_queue.SetWindowText(str);
	str.Format("%d",place.bargin_zone);
	m_bar.SetWindowText(str);
	str.Format("%d",place.leave);
	m_leave.SetWindowText(str);
	str.Format("%d",place.rest);
	m_rest.SetWindowText(str);
}

void CPetriDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	/*CString str;
	str.Format("%d",m_timeacc);
	MessageBox(str);*/
	UpdateData(TRUE);
	*pResult = 0;
}


void CPetriDlg::OnChangeEditTimeacc() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	KillTimer(1);
	SetTimer(1,1000/m_timeacc,NULL);
//	CString str;
//	str.Format("%d",m_timeacc);
//	MessageBox(str);
}

float CPetriDlg::random()
{
	int z1;
	int m=32771;
	int a=13;
	z1=(a*z0)%m;
	z0=z1;

	/*CString str;
	str.Format("%d, %d",a*z0,z1);
	MessageBox(str);*/

		return (float)fabs(float(z1)/m);
/*	int z;
	srand( (unsigned)time( NULL ) );
	z=rand();
	return z;*/
	
}

void CPetriDlg::OnButtonRestart() 
{
	// TODO: Add your control notification handler code here
	now_time=0;
	UpdateData(TRUE);
	index=0;
	i=0;
	place.bargin_zone=0;
	place.leave=0;
	place.queue=0;
	place.rest=1;
	place.select=0;
	event.arrive_time=getArriveTime();
	client[0].sn=1;
	client[0].arrive_time=event.arrive_time;
	//select_finish[0]=event.arrive_time+getSelectTime();
	event.finish_time=(int)m_service_mean;
	event.select_time=getSelectTime();
}

void CPetriDlg::OnChangeEditArrive() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CPetriDlg::OnChangeEditSearch() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

HBRUSH CPetriDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_STATIC_SEL)
		return m_brush;
	if(pWnd->GetDlgCtrlID()==IDC_STATIC_QUEUE)
		return m_brush;
	if(pWnd->GetDlgCtrlID()==IDC_STATIC_BAR)
		return m_brush;
	if(pWnd->GetDlgCtrlID()==IDC_STATIC_LEV)
		return m_brush;
	if(pWnd->GetDlgCtrlID()==IDC_STATIC_REST)
		return m_brush;
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

CString CPetriDlg::TimeConver(int now_time)
{
	CString str;
	int hour;
	int minite;
	int second;
	hour=(int)now_time/3600;
	minite=((int)now_time%3600)/60;
	second=(int)now_time%3600%60;
	str.Format("%d:%d:%d",8+hour,minite,second);
    return str;
}

void CPetriDlg::OnButtonRecord() 
{
	// TODO: Add your control notification handler code here
//	m_recordDlg.DoModal();
	//CFont font;
	//font.CreateFont(
	recordDlg* dlg1;
	dlg1=new recordDlg();
	dlg1->Create(IDD_DIALOG1,FromHandle(m_hWnd));
	dlg1->ShowWindow(SW_SHOW);
	CString str;
	str="顾客ID   到达时间   选购时间   结算开始时间   结算时间   离开时间";
	dlg1->m_list.AddString(str);
	//dlg1->m_list.Create(LBS_SORT,CRect(0,0,300,300),FromHandle(m_hWnd),IDC_LIST1);
	//CString str2;
	for(int j=0;j<place.leave;j++)
	{
		str.Format("%4d%16d%16d%20d%16d%16d",
			       client[j].sn+1,client[j].arrive_time,client[j].select_time,
				   client[j].bargin_begin,client[j].service_time,
				   client[j].bargin_begin+client[j].service_time);
		//str2+=str;
		dlg1->m_list.AddString(str);
	}
	//MessageBox(str2);
	//dlg1.DoModal();

}
void CPetriDlg::OnChildClose() 
{
//	MessageBox("child close");
/*	recordDlg* dlg;
	dlg=(recordDlg*)FindWindow(NULL,"Record");
	if(NULL!=dlg)
	{
		delete dlg;
	}
	//	MessageBox("get dlg");*/
}
/*info.Format("顾客ID:%d,",client[index].sn+1);
	info+="到达时间:";
	info+=TimeConver(client[index].arrive_time);
	str.Format(",选购时间:%ds",client[index].select_time);
	info+=str;
	str.Format(",排队时间:%ds,",client[index].bargin_begin-client[index].select_finish-1);
	info+=str;
	info+="结算开始时间:";
	info+=TimeConver(client[index].bargin_begin);
	str.Format(",结算时间:%ds,",client[index].service_time);
	info+=str;
	info+="离开时间:";
	info+=TimeConver(client[index].bargin_begin+client[index].service_time);
	mean_stay_time+=client[index].service_time+
		             client[index].bargin_begin-client[index].select_finish-1;
	mean_work_time+=client[index].service_time;*/
