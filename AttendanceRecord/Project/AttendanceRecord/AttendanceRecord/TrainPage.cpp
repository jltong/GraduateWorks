// TrainPage.cpp : implementation file
//

#include "stdafx.h"
#include "AttendanceRecord.h"
#include "TrainPage.h"
#include "afxdialogex.h"
#include "DataBase.h"
#include "ADOConn.h"



// CTrainPage dialog

IMPLEMENT_DYNAMIC(CTrainPage, CDialogEx)

CTrainPage::CTrainPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTrainPage::IDD, pParent)
	//, m_SpeakerId(_T(""))
	//, m_SpeechId(_T(""))
{

}

CTrainPage::~CTrainPage()
{
}

void CTrainPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TRAINEE, cbx_Trainee);
	DDX_Control(pDX, IDC_COMBO_SPHOFSPK, cbx_sph);
	//DDX_CBString(pDX, IDC_COMBO_TRAINEE, m_SpeakerId);
	//DDX_CBString(pDX, IDC_COMBO_SPHOFSPK, m_SpeechId);
}


BEGIN_MESSAGE_MAP(CTrainPage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TRAIN, &CTrainPage::OnButtonTrain)
	ON_CBN_DROPDOWN(IDC_COMBO_TRAINEE, &CTrainPage::OnDropdownTrainee)
	ON_CBN_DROPDOWN(IDC_COMBO_SPHOFSPK, &CTrainPage::OnDropdownSphofspk)
	ON_CBN_SELCHANGE(IDC_COMBO_TRAINEE, &CTrainPage::OnSelchangeTrainee)
END_MESSAGE_MAP()


// CTrainPage message handlers
BOOL CTrainPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	freshSphLib();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTrainPage::freshSphLib()
{
	DataBase db;
	BOOL bTraining  = TRUE;
	db.ResetTable(_T("SpeechLib"), bTraining);

	CStringArray* idArray = db.GetAllUserInfo(_T("UserId"));

	CString SpeechDir = _T("F:\\SpeechDirectory");
	CString UserId,WavName,SphPath;
	CFileFind finder;
	for(int i=0;i<idArray->GetCount();i++){
		UserId = idArray->GetAt(i);
		SphPath = SpeechDir + _T("\\") + UserId + _T("\\") + _T("*.wav");
		BOOL res = finder.FindFile(SphPath);
		while(res){
			res = finder.FindNextFile();
			if(finder.IsDots()||finder.IsDirectory())  
				continue;
			WavName = finder.GetFileName();
			db.InsertSpeechLib(UserId,WavName);
			
		}
	}//O(m*n)
	finder.Close();
		
	if(idArray!=NULL){
		delete(idArray);
		idArray = NULL;
	}
}

void CTrainPage::OnButtonTrain()
{
	// TODO: Add your control notification handler code here

	// Get the Speaker and his Speach
	CString SpeakerId,SpeechId;
	int index1 = cbx_Trainee.GetCurSel();
	int index2 = cbx_sph.GetCurSel();
	if(index1==-1||index2==-1){
		AfxMessageBox(_T("请先选择说话人以及他（她）的语音，再进行训练！如果没有相应的语音，则回到语音采集页进行语音采集。"));
		return;
	}
	cbx_Trainee.GetLBText(index1,SpeakerId);
	cbx_sph.GetLBText(index2,SpeechId);
	//m_SpeechId = SpeechId;

	CString SpeechDir = _T("F:\\SpeechDirectory");
	CString SphPath = SpeechDir+_T("\\")+SpeakerId+_T("\\")+SpeechId;

	CFileFind finder;
	BOOL res = finder.FindFile(SphPath);
	if(!res){
		AfxMessageBox(_T("找不到指定音频文件。语音库更新中..."));
		//更新语音库
		freshSphLib();
		AfxMessageBox(_T("语音库更新完毕！请重新点击\"训练\"按钮进行训练。"));
		return;
	}
	finder.Close();
	AfxMessageBox(_T("训练成功！"));
}


void CTrainPage::OnDropdownTrainee()
{
	// TODO: Add your control notification handler code here
	DataBase db;
	CStringArray* idArray = db.GetAllUserInfo(_T("UserId"));

	cbx_Trainee.ResetContent();

	for(int i=0;i<idArray->GetCount();i++){
		cbx_Trainee.AddString(idArray->GetAt(i));
	}
	
	UpdateData(FALSE);//or UpdateData(false);
	
	if(idArray!=NULL){
		delete(idArray);
		idArray = NULL;
	}

}


void CTrainPage::OnDropdownSphofspk()
{
	// TODO: Add your control notification handler code here

	
	CString SpeakerId;
	int index = cbx_Trainee.GetCurSel();
	if(index==-1){
		AfxMessageBox(_T("请先选择一个说话人！"));
		return;
	}
	cbx_Trainee.GetLBText(index,SpeakerId);
	//m_SpeakerId = SpeakerId;

	DataBase db;
	CStringArray* idArray = db.GetAllUserSpeech(SpeakerId);

	cbx_sph.ResetContent();

	for(int i=0;i<idArray->GetCount();i++){
		cbx_sph.AddString(idArray->GetAt(i));
	}
	
	UpdateData(FALSE);//or UpdateData(false);
	
	if(idArray!=NULL){
		delete(idArray);
		idArray = NULL;
	}
	
}





void CTrainPage::OnSelchangeTrainee()
{
	// TODO: Add your control notification handler code here
	CString SpeakerId;
	int index = cbx_Trainee.GetCurSel();
	if(index==-1){
		//AfxMessageBox(_T("请先选择一个说话人！"));
		return;
	}
	cbx_Trainee.GetLBText(index,SpeakerId);
	//m_SpeakerId = SpeakerId;

	DataBase db;
	CStringArray* idArray = db.GetAllUserSpeech(SpeakerId);

	cbx_sph.ResetContent();

	for(int i=0;i<idArray->GetCount();i++){
		cbx_sph.AddString(idArray->GetAt(i));
	}
	
	UpdateData(FALSE);//or UpdateData(false);
	
	if(idArray!=NULL){
		delete(idArray);
		idArray = NULL;
	}
}
