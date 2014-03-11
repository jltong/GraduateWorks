// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AttendanceRecord.h"
#include "LoginDlg.h"
#include "AdminDlg.h"
#include "afxdialogex.h"
#include "DataBase.h"
#include "ADOConn.h"


// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_UserName(_T(""))
	, m_PassWord(_T(""))
{
	
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Text(pDX, IDC_EDIT_ADMINNAME, m_UserName);
	DDX_Text(pDX, IDC_EDIT_PWD, m_PassWord);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CLoginDlg::OnLogin)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLoginDlg message handlers


void CLoginDlg::OnLogin()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(m_UserName.IsEmpty()||m_PassWord.IsEmpty()){
		AfxMessageBox(_T("密码或用户名不得为空！"));
		return;
	}
	DataBase db;
	CString UserPwd = db.GetLogInPwd(m_UserName);
	if(UserPwd==m_PassWord){
		ShowWindow(SW_HIDE);
		CAdminDlg dlg;
		dlg.DoModal();
		PostMessageW(WM_CLOSE,0,0);
	}
	else{	
		AfxMessageBox(_T("用户名或密码错误，请重新输入"));
		m_UserName.Empty();
		m_PassWord.Empty();
		UpdateData(FALSE);
	}
}





BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CFont *font2 = new CFont;
	font2->CreatePointFont(120,_T("楷体"),NULL);
	this->GetDlgItem(IDC_STATIC_NAME)->SetFont(font2,true);
	this->GetDlgItem(IDC_STATIC_PWD)->SetFont(font2,true);
	this->GetDlgItem(IDC_BUTTON_LOGIN)->SetFont(font2,true);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CLoginDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnSysCommand(nID, lParam);
}


HCURSOR CLoginDlg::OnQueryDragIcon()
{
	// TODO: Add your message handler code here and/or call default

	return CDialogEx::OnQueryDragIcon();
}


void CLoginDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
}
