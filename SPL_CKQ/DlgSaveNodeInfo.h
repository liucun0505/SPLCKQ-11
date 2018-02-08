#pragma once
#include "afxwin.h"


// DlgSaveNodeInfo 对话框

class DlgSaveNodeInfo : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSaveNodeInfo)

public:
	DlgSaveNodeInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgSaveNodeInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_NODEINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnEnChangeEditFile();
	afx_msg void OnBnClickedOk();
	CEdit FileName;
	virtual BOOL OnInitDialog();
};
