#pragma once
#include "afxwin.h"
#include "Tools.h"


// CNetViewPToP 窗体视图

class CNetViewPToP : public CFormView
{
	DECLARE_DYNCREATE(CNetViewPToP)

protected:
	CNetViewPToP();           // 动态创建所使用的受保护的构造函数
	virtual ~CNetViewPToP();

public:
	enum { IDD = IDD_DIALOG_POINTTOPOINT };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HANDLE m_hThreadsend;
	CTools m_tools;
	CEdit m_editMAC1;
	CComboBox m_comb645;
	CEdit m_editSend645;
	CEdit m_editRecv645;
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo645();
	CEdit m_editAddr;
	afx_msg void OnBnClickedButtonSend();
	CButton m_btnSend;
};


