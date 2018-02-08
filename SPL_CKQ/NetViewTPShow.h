#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Tools.h"
#include "AccessData.h"
#define  MODUMAXNUMB  1000
#include "TPDlgJDMsg.h"
#include "GW13762.h"
#include "CSG13762.h"
#include "TPDlgShowExplian.h"
#include "TPShowFindList.h"
// CNetViewTPShow 窗体视图

class CNetViewTPShow : public CFormView
{
	DECLARE_DYNCREATE(CNetViewTPShow)

protected:
	CNetViewTPShow();           // 动态创建所使用的受保护的构造函数
	virtual ~CNetViewTPShow();

public:
	enum { IDD = IDD_DIALOG_TUOPUSHOW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public://发现列表信息
	CTPShowFindList m_TPShowFindList;
	CString m_strPMessage;
public:
	int SUO;
	bool m_bBreak;
	int m_nUpdataTime;
	bool m_bSave;
	bool m_bAutoUpdata;
	CString m_strChooseMAC;
	CGW13762 m_gw13762;
//#ifdef _STD_CSG  //南网标准
	CCSG13762 m_csg13762;
//#endif
	bool m_bShow;
	
	CTPDlgJDMsg m_TPDlgJDMsg;
	CTPDlgShowExplian m_TPDlgShowExplian;

	int m_topo_jzq_port;
	int m_nLineType;
	int m_nMsgType;
	int m_nCengNumb , m_nAlldataNumb;
	int m_nPointNumb[MODUMAXNUMB];//节点TEI
	int m_nPointColor[MODUMAXNUMB];//节点颜色编号
	float m_fPointWeith[MODUMAXNUMB];//节点及节点块宽度
	float m_fCoordinate[MODUMAXNUMB][2];//节点坐标
	CString m_strlist[MODUMAXNUMB];
	int m_nPointLine[MODUMAXNUMB][2];//节点父子关系 ，m_nPointLine[MODUMAXNUMB][0]为自身TEI,  m_nPointLine[MODUMAXNUMB][1]为父TEI
	CBrush m_BrushAll[10];
	CBrush m_RrushFont;
	CPen m_cpenXu;
	int m_nOnlineNumb[10];//统计统一类型节点个数
	
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
	void SetTPdataToAccess(CString strTPdata);
	void GetPointCoordinate(CString strTableName = _T("TPShow"));//获取节点坐标
	sPartQGDW376_2CreatFrame m_ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame m_ptRecvQGDW376_2;
//#ifdef _STD_CSG  //南网标准
	sPartQCSG376_2CreatFrame m_ptSendQCSG376_2;
	sPartQCSG376_2DeCodeFrame m_ptRecvQCSG376_2;
//#endif
	virtual void OnDraw(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual void OnInitialUpdate();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRbtpUpdata();
public:
	//afx_msg void OnCooChange();
	afx_msg void OnLineZhi();
	afx_msg void OnLineZhijiao();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRbtpjdmsgFindlist();
	//afx_msg void OnIdrMenuRbtpShow();
	//afx_msg void OnIdrMenuRbtpHeid();
	//afx_msg void OnRbtpTest();
	afx_msg void OnRbtpjdmsgPtp();
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRbtpAutoupdata();
	afx_msg void OnRbtpSave();

};


DWORD WINAPI ThreadSendTPFindlist(PVOID pParam);