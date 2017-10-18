#pragma once
#include "afxwin.h"


// CDlg13762UpdataConfig 对话框

class CDlg13762UpdataConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg13762UpdataConfig)

public:
	CDlg13762UpdataConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg13762UpdataConfig();

// 对话框数据
	enum { IDD = IDD_DIALOG_3762UPDA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CStatic m_editFile;
	afx_msg void OnBnClickedOk();
	CComboBox m_combBS;
//	CComboBox m_combSX;
	CComboBox m_combZL;
	CEdit m_editFile;
	CEdit m_editFrameSize;
	CStatic m_staticSize;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOpen();
	CButton m_checkDX;
	afx_msg void OnEnChangeEditFile();
};
