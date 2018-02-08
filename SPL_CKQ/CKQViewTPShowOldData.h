#pragma once


#include "Tools.h"
#include "AccessData.h"
#define  MODUMAXNUMB  1000
#include "TPDlgJDMsg.h"
#include "GW13762.h"
#include "CSG13762.h"
#include "TPDlgShowExplian.h"
#include "TPShowFindList.h"
#include "DlgOldTPMessage.h"
#include "afxcmn.h"
#include "afxwin.h"
// CCKQViewTPShowOldData 窗体视图

class CCKQViewTPShowOldData : public CFormView
{
	DECLARE_DYNCREATE(CCKQViewTPShowOldData)

protected:
	CCKQViewTPShowOldData();           // 动态创建所使用的受保护的构造函数
	virtual ~CCKQViewTPShowOldData();

public:
	enum { IDD = IDD_DIALOG_TUOPUSHOW_OLD };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* pDC);
public:
	bool m_bStop;
	bool m_bOver;
	CString m_strShowlist[1024];
	int m_nShowNumb;
	CDlgOldTPMessage m_DlgOldTPMessage;
	CString m_strChooseMAC;
	CGW13762 m_gw13762;
	bool m_bShow;
	CTPDlgJDMsg m_TPDlgJDMsg;
	CTPDlgShowExplian m_TPDlgShowExplian;

	int m_nLineType;
	int m_nCengNumb , m_nAlldataNumb;
	int m_nPointNumb[MODUMAXNUMB];
	int m_nPointColor[MODUMAXNUMB];
	float m_fPointWeith[MODUMAXNUMB];
	float m_fCoordinate[MODUMAXNUMB][2];
	CString m_strlist[MODUMAXNUMB];
	int m_nPointLine[MODUMAXNUMB][2];
	CBrush m_BrushAll[10];
	CBrush m_RrushFont;
	CPen m_cpenXu;
	int m_nOnlineNumb[10];

	CAccessData m_access;
	CTools m_tools;
	HANDLE m_hThreadsend;
	CRect m_cRect;
	float m_Scale;
	float m_cx;//试图宽度
	float m_cy;//视图高度
	float m_cR;//圆形半径
	float m_cTBWeith;//图像上下边距
	float m_cLRWeith;//图像左右边距
	float m_cRW;//图像右边空余宽度
	float m_fFont;
	void GetPointCoordinate(CString strTableName);
	virtual void OnInitialUpdate();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//afx_msg void OnIdrOldmenuRbtpHeid();
	//afx_msg void OnIdrOldmenuRbtpShow();
	afx_msg void OnIdrOldrbtpMessage();
	afx_msg void OnOldlineZhi();
	afx_msg void OnOldlineZhijiao();
	afx_msg void OnOldrbtpUpdata();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	CProgressCtrl m_ctrlProgress;
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonOver();
	CButton m_btnStop;
	CButton m_btnOver;
};


