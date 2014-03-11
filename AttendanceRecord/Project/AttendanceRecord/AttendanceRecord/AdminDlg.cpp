// AdminDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AttendanceRecord.h"
#include "AdminDlg.h"
#include "afxdialogex.h"


// CAdminDlg dialog

IMPLEMENT_DYNAMIC(CAdminDlg, CDialogEx)

CAdminDlg::CAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdminDlg::IDD, pParent)
{

}

CAdminDlg::~CAdminDlg()
{
}

void CAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADMIN_TAB, m_tab);

}


BEGIN_MESSAGE_MAP(CAdminDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, IDC_ADMIN_TAB, &CAdminDlg::OnTcnSelchangeAdminTab)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAdminDlg message handlers


void CAdminDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
}


void CAdminDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnSysCommand(nID, lParam);
}


BOOL CAdminDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	// Add 2 pages for the Tab Control
	m_tab.InsertItem(0,_T("个人信息"));
	m_tab.InsertItem(1,_T("语音采集"));
	m_tab.InsertItem(2,_T("模型建立"));
	m_tab.InsertItem(3,_T("说话人测试"));
	
	// Associate the Tab with the Pages
	m_infopage.Create(IDD_PAGE_INFO,&m_tab);
	m_recorderpage.Create(IDD_PAGE_RECORDER,&m_tab);
	m_trainpage.Create(IDD_PAGE_TRAIN,&m_tab);
	m_testpage.Create(IDD_PAGE_TEST,&m_tab);

	// Set the scope that pages display in the client area
	CRect rc;
	m_tab.GetClientRect(&rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;

	m_infopage.MoveWindow(&rc);
	m_recorderpage.MoveWindow(&rc);
	m_trainpage.MoveWindow(&rc);
	m_testpage.MoveWindow(&rc);
	
	//Save the pointer of dlg
	pDialog[0] = &m_infopage;
	pDialog[1] = &m_recorderpage;
	pDialog[2] = &m_trainpage;
	pDialog[3] = &m_testpage;

	//Display initial page
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	pDialog[3]->ShowWindow(SW_HIDE);
	
	// Set the Timer
	//SetTimer(1,1000,NULL);//#1, every 1000ms;
	//SetTimer(2,8000,NULL);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


HCURSOR CAdminDlg::OnQueryDragIcon()
{
	// TODO: Add your message handler code here and/or call default

	return CDialogEx::OnQueryDragIcon();
}


void CAdminDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CAdminDlg::OnTcnSelchangeAdminTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int m_CurSel = m_tab.GetCurSel();
	pDialog[m_CurSel]->ShowWindow(true);
	for(int i=0;i<PAGE_NUM;i++){
		if(i==m_CurSel)
			continue;
		pDialog[i]->ShowWindow(false);
	}
	
	*pResult = 0;
}


void CAdminDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnTimer(nIDEvent);
	// Timer test succeed! wait to use it!!
	/*
	switch(nIDEvent){
		case 1:
			// test case !!
			m_infopage.UpdateData(true);
			if(!m_infopage.m_Name.IsEmpty()&&!m_infopage.m_Id.IsEmpty()){
				m_recorderpage.m_Speechdir = m_infopage.m_Name+_T("+")+m_infopage.m_Id;
				//if(m_infopage.m_Name==_T("ben"))
					//m_recorderpage.cbx_SpeechSrc.AddString(_T("BEN"));
			}

			
			m_recorderpage.UpdateData(false);
			break;
		case 2:
			m_recorderpage.cbx_SpeechSrc.ResetContent();
			m_recorderpage.cbx_SpeechSrc.AddString(_T("CHINA"));
			KillTimer(2);
			break;

		
	}
	*/
}
