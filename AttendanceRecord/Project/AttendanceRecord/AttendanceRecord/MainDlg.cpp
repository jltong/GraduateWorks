
// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AttendanceRecord.h"
#include "MainDlg.h"
#include "LoginDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg dialog




CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
	, m_CurrentTime(_T(""))
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TIME, m_CurrentTime);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CMainDlg::OnOpenRegisterPanel)
	ON_BN_CLICKED(IDC_BUTTON_ATTEND, &CMainDlg::OnAttend)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// TODO: Add extra initialization here



	// Set the Font
	
	CFont *font1 = new CFont;
	font1->CreatePointFont(180,_T("楷体"),NULL);
	CFont *font2 = new CFont;
	font2->CreatePointFont(120,_T("楷体"),NULL);
	this->GetDlgItem(IDC_STATIC_MAINTITLE)->SetFont(font1,true);
	this->GetDlgItem(IDC_EDIT_TIME)->SetFont(font2,true);
	this->GetDlgItem(IDC_STATIC_LOGSCREEN)->SetFont(font2,true);
	this->GetDlgItem(IDC_BUTTON_ATTEND)->SetFont(font2,true);
	this->GetDlgItem(IDC_BUTTON_REGISTER)->SetFont(font2,true);
	
	// Start the first Timer to trace the current time.
	UINT_PTR nTimerId = 1;
	UINT nElapse = 1000;//1000 ms
	SetTimer(nTimerId,nElapse,NULL);
	
	// Set the Current Time
	CTime ct = CTime::GetCurrentTime();
	m_CurrentTime = this->GetCStringTime(ct);
	UpdateData(false);
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}

	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainDlg::OnOpenRegisterPanel()
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
	CLoginDlg dlg;
	dlg.DoModal();
	ShowWindow(SW_SHOW);
}


void CMainDlg::OnAttend()
{
	// TODO: Add your control notification handler code here
	//UpdateData(TRUE);
	AfxMessageBox(_T("我来了！"+m_CurrentTime));
}


CString CMainDlg::GetCStringTime(CTime ct){
	CString szTime;
	int hour = ct.GetHour();
	int minute = ct.GetMinute();
	int second = ct.GetSecond();
	szTime.Format(_T("%02d:%02d:%02d"),hour,minute,second);
	//AfxMessageBox(szTime);
	return szTime;

}

void CMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnTimer(nIDEvent);
	switch(nIDEvent){
		case 1:
			CTime ct = CTime::GetCurrentTime();
			m_CurrentTime = this->GetCStringTime(ct);
			UpdateData(FALSE);
			break;
	}
	
}

void CMainDlg::OnDestroy()
{
	
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


HBRUSH CMainDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_MAINTITLE)
    {
        pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,0));
		
		
    }
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
