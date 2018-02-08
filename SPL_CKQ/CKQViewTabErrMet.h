#pragma once


#include "MyListCtrl.h"
#include "AccessData.h"
#include "Tools.h"
#include "afxwin.h"
#include "addmactest.h"
// CCKQViewTabErrMet 窗体视图

class CCKQViewTabErrMet : public CFormView
{
	DECLARE_DYNCREATE(CCKQViewTabErrMet)

protected:
	CCKQViewTabErrMet();           // 动态创建所使用的受保护的构造函数
	virtual ~CCKQViewTabErrMet();

public:
	enum { IDD = IDD_DIALOG_CKQ_ERR_MET };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	CFont m_fontStatic;
	void SetNewFont();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void InsertItemToList(CString strAddre , CString strLoca , CString strState , INT8U strType,CString strSendFrames ,CString strRecvFrames);
	void SetTPdataToAccess(CString strTPdata);
	void InsertMetMsg(CString str1,CString str2,CString str3);
	CAccessData m_access;
	CTools m_tools;
	HANDLE m_hThreadsend;
	HANDLE m_hThreadsend_READ;
	HANDLE m_hThreadsend_SendBingF;
	HANDLE m_hThreadsend_RevBingF;

	int nStop;
	CMyListCtrl m_listData;
	FILE* m_fp;
	int nSelect;
	virtual void OnInitialUpdate();
//	afx_msg void OnIdrRbmenuMeterr();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMeterrUpdata();
	CStatic m_staticInNet;
	CStatic m_staticUnNet;
	CStatic m_staticUnWhite;
	afx_msg void OnBnClickedChecksel();
	CButton SelCheck;
	afx_msg void OnBnClickedReflash();
	afx_msg void OnBnClickedStartread();
	CButton m_StartReadMet;
	int m_sussnum;
	int m_falnum;
	long m_Ztime;
	CStatic C_TI;
	CStatic C_FL;
	CStatic C_SU;
	CButton m_Reflash;
	CRect m_cRect;
	void KongjianSize(int nID, int cx, int cy, bool bComb = false);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnAddmetmsg();
	afx_msg void OnDelb();
	afx_msg void OnCopymacmet();
	afx_msg void OnBnClickedAdanga();
	afx_msg void OnBnClickedPdanga();
	afx_msg void OnBnClickedStartss();
	CEdit m_editss;
	afx_msg void OnBnClickedStartreadbingf();
	CButton m_BingfReadMet;
};


