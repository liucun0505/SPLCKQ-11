#pragma once
#include "afxwin.h"


// CDlgCCOTPchange 对话框

class CDlgCCOTPchange : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCCOTPchange)

public:
	CDlgCCOTPchange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCCOTPchange();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editData;
	afx_msg void OnBnClickedOk();
};
