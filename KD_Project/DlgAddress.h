#pragma once
#include "afxwin.h"
#include "Tools.h"
// CDlgAddress 对话框

class CDlgAddress : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddress)

public:
	CDlgAddress(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAddress();

// 对话框数据
	enum { IDD = IDD_DLG_ADDRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strMsgAndAddr;
	void UpdataDlg();
	CTools m_tool;
	CEdit m_editAddr1;
	CEdit m_editAddr2;
	CEdit m_editAddr3;
	CListBox m_listAddr2;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDle();
	virtual BOOL OnInitDialog();
	CComboBox m_comb1;
	CComboBox m_comb2;
	CComboBox m_comb3;
	CComboBox m_comb4;
	CComboBox m_comb5;
	CComboBox m_comb6;
	CComboBox m_comb7;
	CComboBox m_comb8;
	CComboBox m_comb9;
	CEdit m_editNumb;
	afx_msg void OnCbnSelchangeCombo5();
	afx_msg void OnBnClickedOk();
	CEdit m_editXNumb;
};
