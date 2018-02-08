#pragma once
#include "afxwin.h"


// DlgSaveDebugInfo 对话框

class DlgSaveDebugInfo : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSaveDebugInfo)

public:
	DlgSaveDebugInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgSaveDebugInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_DEBUGINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit FileName;
	afx_msg void OnEnChangeEditFile();
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedOk();
	BOOL OnInitDialog(void);
};
