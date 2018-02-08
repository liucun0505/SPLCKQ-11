#pragma once
#include "afxwin.h"
#include "CKQViewTabErrMet.h"
#include "CKQViewUpdata.h"
// addmactest 对话框

class addmactest : public CDialogEx
{
	DECLARE_DYNAMIC(addmactest)

public:
	addmactest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~addmactest();

// 对话框数据
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int n_ChooseDlg;
	CString m_MAC;
	CString m_TYPE;
	CString m_TEI;
	afx_msg void OnBnClickedOk();
	CButton m_ch;
};
