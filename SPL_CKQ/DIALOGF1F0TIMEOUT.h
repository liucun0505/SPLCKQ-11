#pragma once
#include "afxwin.h"


// CDIALOGF1F0TIMEOUT dialog

class CDIALOGF1F0TIMEOUT : public CDialogEx
{
	DECLARE_DYNAMIC(CDIALOGF1F0TIMEOUT)

public:
	CDIALOGF1F0TIMEOUT(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDIALOGF1F0TIMEOUT();

// Dialog Data
	enum { IDD = IDD_DIALOG_F0F1_TIMEOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_timeout;
	int itimeout;
	BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
