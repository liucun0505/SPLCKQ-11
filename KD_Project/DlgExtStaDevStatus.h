#pragma once


// DlgExtStaDevStatus dialog

class DlgExtStaDevStatus : public CDialogEx
{
	DECLARE_DYNAMIC(DlgExtStaDevStatus)

public:
	DlgExtStaDevStatus(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgExtStaDevStatus();

// Dialog Data
	enum { IDD = IDD_DIALOG_EXT_STA_DEV_STATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CEdit FileName;
	afx_msg void OnEnChangeEditFile();
	afx_msg void OnBnClickedButtonOpen();
	BOOL OnInitDialog(void);
	afx_msg void OnBnClickedCancel();
	CEdit FileName1;
	afx_msg void OnBnClickedOk();
};
