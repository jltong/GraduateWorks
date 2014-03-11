
// AttendanceRecord.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAttendanceRecordApp:
// See AttendanceRecord.cpp for the implementation of this class
//

class CAttendanceRecordApp : public CWinApp
{
public:
	CAttendanceRecordApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	bool initMatlabApp();
	bool exitMatlabApp();
	bool createDSN(CString szDSN, CString szFile);

	DECLARE_MESSAGE_MAP()
};

extern CAttendanceRecordApp theApp;