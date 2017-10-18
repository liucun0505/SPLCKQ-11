#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"
#include "AccessData.h"
#include "Tools.h"
#include "afxwin.h"
// CDlgOldTPMessage 对话框

class CDlgOldTPMessage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOldTPMessage)

public:
	CDlgOldTPMessage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgOldTPMessage();

// 对话框数据
	enum { IDD = IDD_DIALOG_OLDTPMSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CAccessData m_access;
	CTools m_tools;
	CRect m_cRect;
	void KongjianSize(int nID, int cx, int cy, bool bComb = false);
	CDateTimeCtrl m_datetimeBegin;
	CDateTimeCtrl m_datetimeEnd;
	afx_msg void OnBnClickedBtnSelect();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnClear();
	CListCtrl m_listShow;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_checkShow;
};
