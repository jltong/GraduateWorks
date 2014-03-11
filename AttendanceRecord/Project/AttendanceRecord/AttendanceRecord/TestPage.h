#pragma once
#include "afxwin.h"


// CTestPage dialog

class CTestPage : public CDialogEx
{
	DECLARE_DYNAMIC(CTestPage)

public:
	CTestPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestPage();

// Dialog Data
	enum { IDD = IDD_PAGE_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_TestDir;
	CComboBox cbx_TestSph;
	afx_msg void OnButtonTest();
	CString m_TestOut;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnTestsph();
	void freshSphLib();
};
