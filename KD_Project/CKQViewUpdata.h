#pragma once

#include "MyListCtrl.h"
#include "afxcmn.h"
#include "Tools.h"
#include "afxwin.h"
#include "AccessData.h"
#include "Tools.h"
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
	int m_nDataLong , m_nYU , m_nCHU;
	CAccessData m_accessData;
	HANDLE m_hThreadsend;
	CStringList m_listStrShengjiData;//升级发送列表
	void SetUpdataListData();
	CString GetDuanAndLen(int nduan,int nlen);
	CString strHEX(CString str,bool bDaoxu = TRUE);
//#ifdef _STD_CSG  //南网标准
	int m_FileSize, m_NrOfSectors;
//#endif
public:
	CTools m_tools;
	CMyListCtrl m_listData;
	afx_msg void OnBnClickedBtnChoosefile();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedBtnRefresh();
	CButton m_radioUpType;
	CEdit m_editFile;
	afx_msg void OnBnClickedBtnBeginupdata();
	CButton m_btnSend;
};


