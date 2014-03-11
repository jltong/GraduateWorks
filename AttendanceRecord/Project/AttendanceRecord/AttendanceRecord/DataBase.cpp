#include "StdAfx.h"
#include "DataBase.h"
#include "ADOConn.h"


DataBase::DataBase(void)
{
}


DataBase::~DataBase(void)
{
}

BOOL DataBase::isExistName(CString UserName,CString TableName){
		//�������ݿ�
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//����SELECT���
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM "+TableName+" WHERE UserName='" + UserName + "'");
	
	//ִ��SELECT���
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);
	if (m_pRecordset->adoEOF){
		m_AdoConn.ExitConnect();
		return FALSE;
	}
	else{
		m_AdoConn.ExitConnect();
		return TRUE;
	}
}
BOOL DataBase::isExistId(CString UserId, CString TableName){
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//����SELECT���
	_bstr_t vSQL;
	_RecordsetPtr m_pRecordset;
	
	vSQL = _T("SELECT * FROM "+TableName+" WHERE UserId='" + UserId + "'");
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);
	if (m_pRecordset->adoEOF){
		m_AdoConn.ExitConnect();
		return FALSE;//���û������ڣ����أ�
	}
	else{
		m_AdoConn.ExitConnect();
		return TRUE;
	}
}
BOOL DataBase::InsertUserInfo(CString UserName, CString UserId, CString Email, CString PhoneNumber)
{
	//�������ݿ�
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//����INSERT���
	
	_bstr_t vSQL;
	_RecordsetPtr m_pRecordset;
	

	vSQL = _T("INSERT INTO UserInfo(UserName,UserId,Email,PhoneNumber) VALUES('" + UserName + "','" + UserId + "','" + Email + "','" + PhoneNumber + "')");	
	//ִ��INSERT���
	BOOL res=m_AdoConn.ExecuteSQL(vSQL);	
	//�Ͽ������ݿ������
	m_AdoConn.ExitConnect();
	return res;
}
BOOL DataBase::InsertSpeechLib(CString UserId, CString WavName)
{
	//�������ݿ�
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//����INSERT���
	
	_bstr_t vSQL;
	_RecordsetPtr m_pRecordset;
	

	vSQL = _T("INSERT INTO SpeechLib(UserId,WavName) VALUES('" + UserId + "','" + WavName + "')");	
	//ִ��INSERT���
	BOOL res=m_AdoConn.ExecuteSQL(vSQL);	
	//�Ͽ������ݿ������
	m_AdoConn.ExitConnect();
	return res;
}
BOOL DataBase::InsertAttendRecord(CString UserId, CString Date, CString Time)
{
	//�������ݿ�
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//����INSERT���
	

	_bstr_t vSQL;
	//vSQL =_T("SELECT * FROM signin");
	//_RecordsetPtr m_pRecordset;
	//m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	vSQL = _T("INSERT INTO AttendRecord(UserId,Date,Time) VALUES('" + UserId + "','"+ Date + "','"+ Time+"')");	
	//ִ��INSERT���
	BOOL res=m_AdoConn.ExecuteSQL(vSQL);

	//m_pRecordset->Update();
	//when the consequence of the SELECT is empty,
	//the Update() may have memory access error.

	//�Ͽ������ݿ������
	m_AdoConn.ExitConnect();
	return res;
}

void DataBase::UpdateInfo(CString UserName, CString UserId, CString Email, CString PhoneNumber)
{
	//�������ݿ�
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//����UPDATE���
	//User nUser = GetUserInfo(UserId);

	_bstr_t vSQL;
	/*
	vSQL =_T("SELECT * FROM userinfo");
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);
	*/
	vSQL = _T("UPDATE UserInfo SET UserName='" + UserName + "',Email='"+ Email +"',PhoneNumber='"+ PhoneNumber +"' WHERE UserId='" + UserId + "'");
	//ִ��UPDATE���
	m_AdoConn.ExecuteSQL(vSQL);
	//m_pRecordset->Update();
	m_AdoConn.ExitConnect();

}
	
void DataBase::DeleteUser(CString UserId)
{
	// This method may be unsafe!
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//����DELETE���
	_bstr_t vSQL;
	vSQL = _T("DELETE FROM UserInfo WHERE UserId='" + UserId+ "'");
	//ִ��DELETE���
	m_AdoConn.ExecuteSQL(vSQL);	
	//�Ͽ������ݿ������
	m_AdoConn.ExitConnect();

}
void DataBase::ResetTable(CString TableName, BOOL bTraining)
{
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//����DELETE���
	_bstr_t vSQL;
	CString UserId = _T("Test");

	if(bTraining)
		vSQL = _T("DELETE FROM "+TableName+" WHERE UserId<>'" + UserId+ "'");
	else
		vSQL = _T("DELETE FROM "+TableName+" WHERE UserId='" + UserId+ "'");
	//ִ��DELETE���
	m_AdoConn.ExecuteSQL(vSQL);	
	//�Ͽ������ݿ������
	m_AdoConn.ExitConnect();
}

CString DataBase::GetLogInPwd(CString UserName)
{
	//�������ݿ�
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//����SELECT���
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM LogIn WHERE UserName='" + UserName + "'");
	//ִ��SELETE���
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	CString UserPwd;
	//���ظ��е�ֵ
	if (!m_pRecordset->adoEOF)
	{
		UserPwd = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("UserPwd");
	}
	//�Ͽ������ݿ������
	m_AdoConn.ExitConnect();
	return UserPwd;
}

User DataBase::GetUserInfo(CString UserId)
{
	//�������ݿ�
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();

	//����SELECT���
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM UserInfo WHERE UserId ='" + UserId + "'");
	//ִ��SELETE���
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	CString UserName,Email,PhoneNumber;
	//���ظ��е�ֵ
	if (!m_pRecordset->adoEOF)
	{
		UserName = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("UserName");
		Email = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("Email");
		PhoneNumber =(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("PhoneNumber");
	
	}
	User nUser(UserName,UserId,Email,PhoneNumber);
	//�Ͽ������ݿ������
	m_AdoConn.ExitConnect();
	return nUser;
}

CStringArray* DataBase::GetAllUserInfo(CString Attribute)
{
	//�������ݿ�
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();

	//����SELECT���
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM UserInfo");
	//ִ��SELETE���
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	CStringArray* itemArray = new CStringArray;

	CString item;
	//���ظ��е�ֵ
	while (!m_pRecordset->adoEOF)
	{
		item = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect((const _variant_t)Attribute);// wait to check the correctness!
		
		itemArray->Add(item);

		m_pRecordset->MoveNext();
	}
	
	//�Ͽ������ݿ������
	m_AdoConn.ExitConnect();
	return itemArray;
}

CStringArray* DataBase::GetAllUserSpeech(CString UserId)
{
	//�������ݿ�
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();

	//����SELECT���
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM SpeechLib WHERE UserId ='" + UserId + "'");
	//ִ��SELETE���
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	CStringArray* wavArray = new CStringArray;

	CString wavname;
	//���ظ��е�ֵ
	while (!m_pRecordset->adoEOF)
	{
		wavname = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("WavName");// wait to check the correctness!
		
		wavArray->Add(wavname);

		m_pRecordset->MoveNext();
	}
	
	//�Ͽ������ݿ������
	m_AdoConn.ExitConnect();
	return wavArray;

}