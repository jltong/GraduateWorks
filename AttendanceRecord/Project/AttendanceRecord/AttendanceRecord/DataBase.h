#pragma once
#include "User.h"
class DataBase
{
public:
	DataBase(void);
	~DataBase(void);

	//database operation in sql
	BOOL isExistName(CString UserName,CString TableName);//�ж��û����Ƿ����
	BOOL isExistId(CString UserId,CString TableName);//�ж��û�ID�Ƿ����

	
	BOOL InsertUserInfo(CString UserName, CString UserId, CString Email, CString PhoneNumber); 
	
	BOOL InsertAttendRecord(CString UserId, CString Date, CString Time);

	BOOL InsertSpeechLib(CString UserId, CString WavName);

	void UpdateInfo(CString UserName, CString UserId, CString Email, CString PhoneNumber);
	
	void DeleteUser(CString UserId);

	void ResetTable(CString TableName, BOOL bTraining);
	
	CString GetLogInPwd(CString UserName);

	User GetUserInfo(CString UserId);
	
	CStringArray* GetAllUserInfo(CString Attribute);
	
	CStringArray* GetAllUserSpeech(CString UserId);
};

