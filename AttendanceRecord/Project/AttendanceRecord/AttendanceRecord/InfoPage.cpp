// InfoPage.cpp : implementation file
//

#include "stdafx.h"
#include "AttendanceRecord.h"
#include "InfoPage.h"
#include "afxdialogex.h"
#include "DataBase.h"
#include "ADOConn.h"


// CInfoPage dialog

IMPLEMENT_DYNAMIC(CInfoPage, CDialogEx)

CInfoPage::CInfoPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInfoPage::IDD, pParent)
	, m_Name(_T(""))
	, m_Id(_T(""))
	, m_Email(_T(""))
	, m_PhoneNumber(_T(""))
{

}

CInfoPage::~CInfoPage()
{
}
void CInfoPage::reSetItems(){
	this->m_Name = _T("");
	this->m_Id = _T("");
	this->m_Email = _T("");
	this->m_PhoneNumber = _T("");
}
void CInfoPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_ID, m_Id);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_Email);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_PhoneNumber);
}


BEGIN_MESSAGE_MAP(CInfoPage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REGINFO, &CInfoPage::OnButtonRegInfo)
END_MESSAGE_MAP()


// CInfoPage message handlers


void CInfoPage::OnButtonRegInfo()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_Name.IsEmpty()||m_Id.IsEmpty()||m_Email.IsEmpty()||m_PhoneNumber.IsEmpty()){
		AfxMessageBox(_T("���Ƚ��û���Ϣ��д������"));
		return;
	}
	DataBase db;

	if(db.isExistId(m_Id,_T("UserInfo"))){
		db.UpdateInfo(m_Name,m_Id,m_Email,m_PhoneNumber);
		AfxMessageBox(_T("�û���Ϣ���³ɹ���"));
	}
	else{
		if(!db.InsertUserInfo(m_Name,m_Id,m_Email,m_PhoneNumber)){
			AfxMessageBox(_T("�û���Ϣע��ʧ�ܣ�"));
			return;
		}
		else{
			AfxMessageBox(_T("�û���Ϣע��ɹ���"));
		}
	}
	reSetItems();
	UpdateData(FALSE);
}
