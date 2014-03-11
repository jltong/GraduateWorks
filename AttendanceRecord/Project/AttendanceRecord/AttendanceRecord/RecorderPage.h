#pragma once
#include "afxwin.h"


// CRecorderPage dialog

class CRecorderPage : public CDialogEx
{
	DECLARE_DYNAMIC(CRecorderPage)

public:
	CRecorderPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRecorderPage();

// Dialog Data
	enum { IDD = IDD_PAGE_RECORDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Speechdir;
	afx_msg void OnSaveSpeech();
	virtual BOOL OnInitDialog();
	CComboBox cbx_SpeechSrc;
	afx_msg void OnCbnDropdown();
};
