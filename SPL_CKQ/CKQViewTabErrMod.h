#pragma once
#include "MyListCtrl.h"
#include "AccessData.h"
#include "Tools.h"
#include "afxwin.h"

// CCKQViewTabErrMod 窗体视图

class CCKQViewTabErrMod : public CFormView
{
	DECLARE_DYNCREATE(CCKQViewTabErrMod)

protected:
	CCKQViewTabErrMod();           // 动态创建所使用的受保护的构造函数
	virtual ~CCKQViewTabErrMod();

public:
	enum { IDD = IDD_DIALOG_CKQ_ERR_MOD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	void SetNewFont();
	CFont m_fontStatic;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void InsertItemToList(CString strMAC , CString strTEI , CString strState , CString strLoca , CString strAddress , CString strType);
	CAccessData m_access;
	CTools m_tools;
	HANDLE m_hThreadsend;
	CMyListCtrl m_listData;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnModerrUpdata();
	CButton m_checkWhite;
	CButton m_checkMet;
	CStatic m_staticInNet;
	CStatic m_staticUnNet;
	//CStatic m_staticLostNet;
	CStatic m_staticUnWhite;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


