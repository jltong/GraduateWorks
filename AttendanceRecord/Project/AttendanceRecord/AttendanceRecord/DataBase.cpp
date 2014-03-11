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
		//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置SELECT语句
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM "+TableName+" WHERE UserName='" + UserName + "'");
	
	//执行SELECT语句
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
	//设置SELECT语句
	_bstr_t vSQL;
	_RecordsetPtr m_pRecordset;
	
	vSQL = _T("SELECT * FROM "+TableName+" WHERE UserId='" + UserId + "'");
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);
	if (m_pRecordset->adoEOF){
		m_AdoConn.ExitConnect();
		return FALSE;//该用户不存在，返回！
	}
	else{
		m_AdoConn.ExitConnect();
		return TRUE;
	}
}
BOOL DataBase::InsertUserInfo(CString UserName, CString UserId, CString Email, CString PhoneNumber)
{
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置INSERT语句
	
	_bstr_t vSQL;
	_RecordsetPtr m_pRecordset;
	

	vSQL = _T("INSERT INTO UserInfo(UserName,UserId,Email,PhoneNumber) VALUES('" + UserName + "','" + UserId + "','" + Email + "','" + PhoneNumber + "')");	
	//执行INSERT语句
	BOOL res=m_AdoConn.ExecuteSQL(vSQL);	
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
	return res;
}
BOOL DataBase::InsertSpeechLib(CString UserId, CString WavName)
{
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置INSERT语句
	
	_bstr_t vSQL;
	_RecordsetPtr m_pRecordset;
	

	vSQL = _T("INSERT INTO SpeechLib(UserId,WavName) VALUES('" + UserId + "','" + WavName + "')");	
	//执行INSERT语句
	BOOL res=m_AdoConn.ExecuteSQL(vSQL);	
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
	return res;
}
BOOL DataBase::InsertAttendRecord(CString UserId, CString Date, CString Time)
{
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置INSERT语句
	

	_bstr_t vSQL;
	//vSQL =_T("SELECT * FROM signin");
	//_RecordsetPtr m_pRecordset;
	//m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	vSQL = _T("INSERT INTO AttendRecord(UserId,Date,Time) VALUES('" + UserId + "','"+ Date + "','"+ Time+"')");	
	//执行INSERT语句
	BOOL res=m_AdoConn.ExecuteSQL(vSQL);

	//m_pRecordset->Update();
	//when the consequence of the SELECT is empty,
	//the Update() may have memory access error.

	//断开与数据库的连接
	m_AdoConn.ExitConnect();
	return res;
}

void DataBase::UpdateInfo(CString UserName, CString UserId, CString Email, CString PhoneNumber)
{
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置UPDATE语句
	//User nUser = GetUserInfo(UserId);

	_bstr_t vSQL;
	/*
	vSQL =_T("SELECT * FROM userinfo");
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);
	*/
	vSQL = _T("UPDATE UserInfo SET UserName='" + UserName + "',Email='"+ Email +"',PhoneNumber='"+ PhoneNumber +"' WHERE UserId='" + UserId + "'");
	//执行UPDATE语句
	m_AdoConn.ExecuteSQL(vSQL);
	//m_pRecordset->Update();
	m_AdoConn.ExitConnect();

}
	
void DataBase::DeleteUser(CString UserId)
{
	// This method may be unsafe!
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置DELETE语句
	_bstr_t vSQL;
	vSQL = _T("DELETE FROM UserInfo WHERE UserId='" + UserId+ "'");
	//执行DELETE语句
	m_AdoConn.ExecuteSQL(vSQL);	
	//断开与数据库的连接
	m_AdoConn.ExitConnect();

}
void DataBase::ResetTable(CString TableName, BOOL bTraining)
{
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置DELETE语句
	_bstr_t vSQL;
	CString UserId = _T("Test");

	if(bTraining)
		vSQL = _T("DELETE FROM "+TableName+" WHERE UserId<>'" + UserId+ "'");
	else
		vSQL = _T("DELETE FROM "+TableName+" WHERE UserId='" + UserId+ "'");
	//执行DELETE语句
	m_AdoConn.ExecuteSQL(vSQL);	
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
}

CString DataBase::GetLogInPwd(CString UserName)
{
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();
	//设置SELECT语句
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM LogIn WHERE UserName='" + UserName + "'");
	//执行SELETE语句
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	CString UserPwd;
	//返回各列的值
	if (!m_pRecordset->adoEOF)
	{
		UserPwd = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("UserPwd");
	}
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
	return UserPwd;
}

User DataBase::GetUserInfo(CString UserId)
{
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();

	//设置SELECT语句
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM UserInfo WHERE UserId ='" + UserId + "'");
	//执行SELETE语句
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	CString UserName,Email,PhoneNumber;
	//返回各列的值
	if (!m_pRecordset->adoEOF)
	{
		UserName = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("UserName");
		Email = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("Email");
		PhoneNumber =(LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("PhoneNumber");
	
	}
	User nUser(UserName,UserId,Email,PhoneNumber);
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
	return nUser;
}

CStringArray* DataBase::GetAllUserInfo(CString Attribute)
{
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();

	//设置SELECT语句
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM UserInfo");
	//执行SELETE语句
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	CStringArray* itemArray = new CStringArray;

	CString item;
	//返回各列的值
	while (!m_pRecordset->adoEOF)
	{
		item = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect((const _variant_t)Attribute);// wait to check the correctness!
		
		itemArray->Add(item);

		m_pRecordset->MoveNext();
	}
	
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
	return itemArray;
}

CStringArray* DataBase::GetAllUserSpeech(CString UserId)
{
	//连接数据库
	ADOConn m_AdoConn;
	m_AdoConn.OnInitADOConn();

	//设置SELECT语句
	_bstr_t vSQL;
	vSQL = _T("SELECT * FROM SpeechLib WHERE UserId ='" + UserId + "'");
	//执行SELETE语句
	_RecordsetPtr m_pRecordset;
	m_pRecordset = m_AdoConn.GetRecordSet(vSQL);

	CStringArray* wavArray = new CStringArray;

	CString wavname;
	//返回各列的值
	while (!m_pRecordset->adoEOF)
	{
		wavname = (LPCTSTR)(_bstr_t)m_pRecordset->GetCollect("WavName");// wait to check the correctness!
		
		wavArray->Add(wavname);

		m_pRecordset->MoveNext();
	}
	
	//断开与数据库的连接
	m_AdoConn.ExitConnect();
	return wavArray;

}