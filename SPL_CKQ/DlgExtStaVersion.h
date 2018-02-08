#pragma once
#include "afxwin.h"


// DlgExtStaVersion 对话框

class DlgExtStaVersion : public CDialogEx
{
	DECLARE_DYNAMIC(DlgExtStaVersion)

public:
	DlgExtStaVersion(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgExtStaVersion();

// 对话框数据
	enum { IDD = IDD_DIALOG_EXT_STAVERSION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
