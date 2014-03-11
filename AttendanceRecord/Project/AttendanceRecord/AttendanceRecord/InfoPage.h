#pragma once


// CInfoPage dialog

class CInfoPage : public CDialogEx
{
	DECLARE_DYNAMIC(CInfoPage)

public:
	CInfoPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInfoPage();

// Dialog Data
	enum { IDD = IDD_PAGE_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Name;
	CString m_Id;
	CString m_Email;
	CString m_PhoneNumber;
	afx_msg void OnButtonRegInfo();
	void reSetItems();
};
