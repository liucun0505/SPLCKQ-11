#pragma once
#include "afxwin.h"
#include "Tools.h"
#include "afxcmn.h"


// CFormTabView1 窗体视图

class CFormTabView1 : public CFormView
{
	DECLARE_DYNCREATE(CFormTabView1)

protected:
	CFormTabView1();           // 动态创建所使用的受保护的构造函数
	virtual ~CFormTabView1();

public:
	enum { IDD = IDD_DIALOG_TEST };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	
	HANDLE m_hThreadsend;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	INT8U m_uSNID;
	CTools m_tools;
	afx_msg void OnBnClickedButtonFind();
	virtual void OnInitialUpdate();
	int m_nChooseType;
	int m_nChooselist;
	CListCtrl m_listCKQ;
	afx_msg void OnNMClickListCkq(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_editCCOAddress;
	afx_msg void OnBnClickedButtonLink();
	CButton m_btnLink;
	CButton m_radioType;
};


