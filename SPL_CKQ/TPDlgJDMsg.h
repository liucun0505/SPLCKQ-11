#pragma once
#include "afxwin.h"


// CTPDlgJDMsg 对话框

class CTPDlgJDMsg : public CDialogEx
{
	DECLARE_DYNAMIC(CTPDlgJDMsg)

public:
	CTPDlgJDMsg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTPDlgJDMsg();

// 对话框数据
	enum { IDD = IDD_DIALOG_TPSHOW_JDMSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CRect m_cRect;
	void KongjianSize(int nID, int cx, int cy, bool bComb);
	CEdit m_editMsg;
//	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
