#pragma once
#include "afxwin.h"


// SaveFileName 对话框

class SaveFileName : public CDialogEx
{
	DECLARE_DYNAMIC(SaveFileName)

public:
	SaveFileName(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SaveFileName();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CEdit m_savefilename;
};
