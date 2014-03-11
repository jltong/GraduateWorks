// TestPage.cpp : implementation file
//

#include "stdafx.h"
#include "AttendanceRecord.h"
#include "TestPage.h"
#include "afxdialogex.h"
#include "DataBase.h"
#include "ADOConn.h"


// CTestPage dialog

IMPLEMENT_DYNAMIC(CTestPage, CDialogEx)

CTestPage::CTestPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestPage::IDD, pParent)
	, m_TestDir(_T(""))
	, m_TestOut(_T(""))
{

}

CTestPage::~CTestPage()
{
}

void CTestPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TESTSPH, m_TestDir);
	DDX_Control(pDX, IDC_COMBO_TESTSPH, cbx_TestSph);
	DDX_Text(pDX, IDC_EDIT_TESTOUT, m_TestOut);
}


BEGIN_MESSAGE_MAP(CTestPage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CTestPage::OnButtonTest)
	ON_CBN_DROPDOWN(IDC_COMBO_TESTSPH, &CTestPage::OnCbnTestsph)
END_MESSAGE_MAP()


// CTestPage message handlers


void CTestPage::OnButtonTest()
{
	// TODO: Add your control notification handler code here
	CString SpeakerId = _T("Test");
	CString SpeechId;
	int index = cbx_TestSph.GetCurSel();
	if(index==-1){
		AfxMessageBox(_T("����ѡ���������ٽ��в��ԣ����û����Ӧ����������ص������ɼ�ҳ���������ɼ���"));
		return;
	}
	
	cbx_TestSph.GetLBText(index,SpeechId);
	//m_SpeechId = SpeechId;

	CString SpeechDir = _T("F:\\SpeechDirectory");
	CString SphPath = SpeechDir+_T("\\")+SpeakerId+_T("\\")+SpeechId;

	CFileFind finder;
	BOOL res = finder.FindFile(SphPath);
	if(!res){
		AfxMessageBox(_T("�Ҳ���ָ����Ƶ�ļ��������������..."));
		//����������
		freshSphLib();
		AfxMessageBox(_T("�����������ϣ������µ��\"����\"��ť����ѵ����"));
		return;
	}
	finder.Close();
	AfxMessageBox(_T("���Գɹ���"));
}


BOOL CTestPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CString SpeechDir = _T("F:\\SpeechDirectory");
	this->m_TestDir = SpeechDir+_T("\\")+_T("Test");
	UpdateData(FALSE);

	// Create Folder
	if(!PathIsDirectory(this->m_TestDir)){
		CreateDirectory(this->m_TestDir,NULL);
	}
	freshSphLib();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTestPage::freshSphLib()
{
	DataBase db;
	BOOL bTraining = FALSE;
	db.ResetTable(_T("SpeechLib"),bTraining);

	//CStringArray* idArray = db.GetAllUserInfo(_T("UserId"));

	CString SpeechDir = _T("F:\\SpeechDirectory");
	CString UserId,WavName,SphPath;
	CFileFind finder;
	
	UserId = _T("Test");
	SphPath = SpeechDir + _T("\\") + UserId + _T("\\") + _T("*.wav");
	BOOL res = finder.FindFile(SphPath);
	while(res){
		res = finder.FindNextFile();
		if(finder.IsDots()||finder.IsDirectory())  
			continue;
		WavName = finder.GetFileName();
		db.InsertSpeechLib(UserId,WavName);		
	}
	
	finder.Close();
	
}
void CTestPage::OnCbnTestsph()
{
	// TODO: Add your control notification handler code here

	CString SpeakerId = _T("Test");
	//m_SpeakerId = SpeakerId;

	DataBase db;
	CStringArray* idArray = db.GetAllUserSpeech(SpeakerId);

	cbx_TestSph.ResetContent();
	for(int i=0;i<idArray->GetCount();i++){
		cbx_TestSph.AddString(idArray->GetAt(i));
	}
	
	UpdateData(FALSE);//or UpdateData(false);
	
	if(idArray!=NULL){
		delete(idArray);
		idArray = NULL;
	}
}
