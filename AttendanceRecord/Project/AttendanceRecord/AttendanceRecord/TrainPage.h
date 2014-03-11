#pragma once
#include "afxwin.h"


// CTrainPage dialog

class CTrainPage : public CDialogEx
{
	DECLARE_DYNAMIC(CTrainPage)

public:
	CTrainPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTrainPage();

// Dialog Data
	enum { IDD = IDD_PAGE_TRAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonTrain();
	afx_msg void OnDropdownTrainee();
	afx_msg void OnDropdownSphofspk();
	CComboBox cbx_Trainee;
	CComboBox cbx_sph;
	virtual BOOL OnInitDialog();
	void freshSphLib();
	//CString m_SpeakerId;
	//CString m_SpeechId;
	afx_msg void OnSelchangeTrainee();
};
