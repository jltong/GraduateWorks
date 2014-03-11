// RecorderPage.cpp : implementation file
//

#include "stdafx.h"
#include "AttendanceRecord.h"
#include "RecorderPage.h"

#include "afxdialogex.h"
#include "DataBase.h"
#include "ADOConn.h"

// CRecorderPage dialog

IMPLEMENT_DYNAMIC(CRecorderPage, CDialogEx)

CRecorderPage::CRecorderPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRecorderPage::IDD, pParent)
	, m_Speechdir(_T(""))
{

}

CRecorderPage::~CRecorderPage()
{
}

void CRecorderPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SPHDIR, m_Speechdir);
	DDX_Control(pDX, IDC_COMBO_SPHSRC, cbx_SpeechSrc);
}


BEGIN_MESSAGE_MAP(CRecorderPage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVESPH, &CRecorderPage::OnSaveSpeech)
	ON_CBN_DROPDOWN(IDC_COMBO_SPHSRC, &CRecorderPage::OnCbnDropdown)
END_MESSAGE_MAP()


// CRecorderPage message handlers

BOOL CRecorderPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	

	this->m_Speechdir = _T("F:\\SpeechDirectory");
	UpdateData(FALSE);

	// Create Folder
	if(!PathIsDirectory(this->m_Speechdir)){
		CreateDirectory(this->m_Speechdir,NULL);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CRecorderPage::OnSaveSpeech()
{
	// TODO: Add your control notification handler code here
	CString Speaker(_T(""));
	int index = cbx_SpeechSrc.GetCurSel();
	if(index==-1){
		AfxMessageBox(_T("请先选择一个语音源！"));
		return;
	}
	cbx_SpeechSrc.GetLBText(index,Speaker);

	CString abspath = this->m_Speechdir + _T("\\") + Speaker;
	AfxMessageBox(abspath);
	
}
void CRecorderPage::OnCbnDropdown()
{
	// TODO: Add your control notification handler code here
	DataBase db;
	CStringArray* idArray = db.GetAllUserInfo(_T("UserId"));

	cbx_SpeechSrc.ResetContent();

	for(int i=0;i<idArray->GetCount();i++){
		cbx_SpeechSrc.AddString(idArray->GetAt(i));
	}
	
	UpdateData(FALSE);//or UpdateData(false);
	
	if(idArray!=NULL){
		delete(idArray);
		idArray = NULL;
	}
}
