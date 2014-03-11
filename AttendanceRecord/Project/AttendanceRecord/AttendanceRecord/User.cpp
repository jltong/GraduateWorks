#include "StdAfx.h"
#include "User.h"


User::User(void)
{
	this->UserName = _T("");
	this->UserId = _T("");
	this->Email = _T("");
	this->PhoneNumber = _T("");
}


User::~User(void)
{
}

User::User(CString UserName,CString UserId,CString Email,CString PhoneNumber)
{
	this->UserName = UserName;
	this->UserId = UserId;
	this->Email = Email;
	this->PhoneNumber = PhoneNumber;
}
CString User::getUserName(){
	return this->UserName;
}

CString User::getUserId(){
	return this->UserId;
}
CString User::getEmail(){
	return this->Email;
}
CString User::getPhoneNumber(){
	return this->PhoneNumber;
}