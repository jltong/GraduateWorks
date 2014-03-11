
// AttendanceRecord.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AttendanceRecord.h"
#include "MainDlg.h"
#include <odbcinst.h>
#pragma comment(lib, "odbccp32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAttendanceRecordApp

BEGIN_MESSAGE_MAP(CAttendanceRecordApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAttendanceRecordApp construction

CAttendanceRecordApp::CAttendanceRecordApp()
{
	EnableHtmlHelp();

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CAttendanceRecordApp object

CAttendanceRecordApp theApp;


// CAttendanceRecordApp initialization

/*
bool CAttendanceRecordApp::initMatlabApp(){
	bool res1 = false,
		 res2 = false,
		 res3 = false,
		 res4 = false;

	bool res = mclInitializeApplication(NULL,0);
	if (!res){
		AfxMessageBox(_T("初始化Application错误！"));
		return false;
	}
	res1 = InitializeInitialize();
	res2 = TrainingInitialize();
	res3 = IncTrainInitialize();
	res4 = TestSpeechInitialize();
	if (!res||!res1||!res2||!res3||!res4)
	{
		AfxMessageBox(_T("初始化Lib错误！"));
		return false;
	}
	return true;
}
*/
/*
bool CAttendanceRecordApp::exitMatlabApp(){
	InitializeTerminate();
	TrainingTerminate();
	IncTrainTerminate();
	TestSpeechTerminate();
	bool res = mclTerminateApplication();
	if (!res){
		AfxMessageBox(_T("结束Application错误!"));
		return false;
	}
	return true;
}
*/

bool CAttendanceRecordApp::createDSN(CString szDSN, CString szFile){
	CString szPath;
	
	GetModuleFileName(NULL,szPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);//获得当前程序的运行目录(.exe)所在的目录
	szPath.ReleaseBuffer();
	int nPos=szPath.ReverseFind ('\\');
	szPath=szPath.Left (nPos);
	CString lpszFile = szPath + _T("\\")+szFile;
	
	CString str;
	str.Format(_T("DSN=%s? DBQ=%s? FIL=MicrosoftAccess? DEFAULTDIR=%s?? "),szDSN,lpszFile,szPath);

	int mlen = str.GetLength();
    for (int i=0; i<mlen; i++)
	{
		if (str.GetAt(i) == '?')
			str.SetAt(i,'\0');
	}

  if (FALSE == SQLConfigDataSource(NULL,ODBC_ADD_DSN,_T("Microsoft Access Driver (*.mdb, *.accdb)\0"),str)){
		return false;
  }
  return true;

}

BOOL CAttendanceRecordApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	/*
	if(!initMatlabApp()){
		return FALSE;
	}
	*/
	
	CString szDSN = _T("AR_DSN");
	CString szFile = _T("AR.mdb");
	if(!createDSN(szDSN,szFile)){
		AfxMessageBox(_T("动态创建数据源失败！"));
		return FALSE;
	}
	

	//打开主对话框（模态）
	CMainDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	/*
	if(!exitMatlabApp()){
		return FALSE;
	}
	*/
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CAttendanceRecordApp::ExitInstance()
{
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}
