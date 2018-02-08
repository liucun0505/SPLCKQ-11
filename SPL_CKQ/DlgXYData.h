#pragma once
#include "afxcmn.h"
#include "AccessData.h"
#include "Tools.h"
#include "afxwin.h"
// CDlgXYData 对话框

class CDlgXYData : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgXYData)

public:
	CDlgXYData(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgXYData();

// 对话框数据
	enum { IDD = IDD_DIALOG_XY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTools m_tool;
	CAccessData m_access;
	int m_nSelNumb;
	CListCtrl m_listData;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickListData(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_editAFNFN;
	CEdit m_editData;
	CEdit m_editDatalen;
	CEdit m_editDownBM;
	CEdit m_editDownMsg;
	CEdit m_editUpBM;
	CEdit m_editUpMsg;
	int m_datacharlen;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonInset();
	afx_msg void OnBnClickedButtonDel();
	CComboBox m_combANF;
	afx_msg void OnCbnSelchangeCombAfn();
	CEdit m_editName;
	afx_msg void OnEnChangeEditData();
	afx_msg void OnBnClickedButton1();
};
