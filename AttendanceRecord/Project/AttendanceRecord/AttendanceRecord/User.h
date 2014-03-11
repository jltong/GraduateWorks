#pragma once
class User
{
	CString UserName;
	CString UserId;
	CString Email;
	CString PhoneNumber;
public:
	User(void);
	User(CString UserName,CString UserId,CString Email,CString PhoneNumber);
	CString getUserName();
	CString getUserId();
	CString getEmail();
	CString getPhoneNumber();
	~User(void);
};

