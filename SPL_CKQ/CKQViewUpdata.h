#pragma once

#include "MyListCtrl.h"
#include "afxcmn.h"
#include "Tools.h"
#include "afxwin.h"
#include "AccessData.h"
#include "Tools.h"
#include "addmactest.h"
// CCKQViewUpdata 窗体视图

class CCKQViewUpdata : public CFormView
{
	DECLARE_DYNCREATE(CCKQViewUpdata)

protected:
	CCKQViewUpdata();           // 动态创建所使用的受保护的构造函数
	virtual ~CCKQViewUpdata();

public:
	enum { IDD = IDD_DIALOG_CKQ_UPDATA };
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
	int nStop_ShengJ;
	int m_nDataLong , m_nYU , m_nCHU;
	CAccessData m_accessData;
	HANDLE m_hThreadsend;
	HANDLE Refresh_hThreadsend;
	HANDLE m_hThreadsend_READ;
	int nStop;
	int nSelect;
	CStringList m_listStrShengjiData;//升级发送列表
	void SetUpdataListData();
	void InsertMetMsg(CString str1,CString str2,CString str3);
	CString GetDuanAndLen(int nduan,int nlen);
	CString strHEX(CString str,bool bDaoxu = TRUE);
//#ifdef _STD_CSG  //南网标准
	int m_FileSize, m_NrOfSectors;
//#endif
public:
	CTools m_tools;
	CMyListCtrl m_listData;

	CAccessData m_access;
	INT8U QWzhengchangshengji(CString m_strLujing);//段长1024
	INT8U DDzhengchangshengji(CString m_strLujing,INT8U *AddrBuf);
	void InsertItemToList(CString strAddre , CString strLoca , CString strState , INT8U strType,CString strSendFrames ,CString strRecvFrames);
	void SetTPdataToAccess(CString strTPdata);

	afx_msg void OnBnClickedBtnChoosefile();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedBtnRefresh();
	CButton m_radioUpType;
	CEdit m_editFile;
	afx_msg void OnBnClickedBtnBeginupdata();
	CButton m_btnSend;
	CRect m_cRect;
	void KongjianSize(int nID, int cx, int cy, bool bComb = false);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton1();
	CButton m_ReadBanBen;
	afx_msg void OnBnClickedCheck1();
	CButton SelCheck;
	afx_msg void OnAddmetmsg();
	CProgressCtrl m_Progress;
	CStatic m_mess;
	CButton m_ref;
};


