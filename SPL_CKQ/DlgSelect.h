#pragma once
#include "afxwin.h"
#include "AccessData.h"
#include "Tools.h"

// DlgSelect 对话框

class DlgSelect : public CDialogEx
{
	DECLARE_DYNAMIC(DlgSelect)

public:
	DlgSelect(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgSelect();

// 对话框数据
	enum { IDD = IDD_DIALOG_NW };
protected:
	void AddData();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_NW_GW;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
