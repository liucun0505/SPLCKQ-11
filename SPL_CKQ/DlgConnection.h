#pragma once
#include "afxwin.h"
#include "AccessData.h"
#include "Tools.h"
// CDlgConnection 对话框

class CDlgConnection : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConnection)

public:
	CDlgConnection(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgConnection();

// 对话框数据
	enum { IDD = IDD_DIALOG_CONNECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
	void AddPort();
public:
	CTools m_tools;
	CAccessData m_access;
	CString m_strMainMAC;
	CString m_strCommPort;
	CString m_strCommBaud;
	CString m_strCommParity;
	CString m_strCommDatabit;
	CString m_strCommStopbit;
	CComboBox m_combCommPort;
	int m_nRadioType;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
//	afx_msg void OnCbnSelchangeComboCommport();
	CComboBox m_combBaud;
	CComboBox m_combDataBit;
	CComboBox m_combParity;
	CComboBox m_combStopBit;
	CComboBox m_combMAC;
	CComboBox m_NWGW;
};
