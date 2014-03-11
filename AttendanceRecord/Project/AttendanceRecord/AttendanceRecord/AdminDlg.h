#pragma once
#include "afxcmn.h"
#include "InfoPage.h"
#include "RecorderPage.h"
#include "TrainPage.h"
#include "TestPage.h"

#define PAGE_NUM 4
// CAdminDlg dialog

class CAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminDlg)

public:
	CAdminDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdminDlg();

// Dialog Data
	enum { IDD = IDD_ADMIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();

	CTabCtrl m_tab;
	CInfoPage m_infopage;
	CRecorderPage m_recorderpage;
	CTrainPage m_trainpage;
	CTestPage m_testpage;


	CDialog* pDialog[PAGE_NUM];
	afx_msg void OnTcnSelchangeAdminTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
