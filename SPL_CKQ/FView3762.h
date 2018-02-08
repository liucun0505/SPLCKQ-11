#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "AccessData.h"
#include "Tools.h"
#include "SetWriteDataDlg.h"
#include "GW13762.h"
#include "CSG13762.h"
#include "DisplayData.h"
#include "Dlg13762Frame.h"
#include "SetWriteLoopNub.h"
// CFView3762 窗体视图

class CFView3762 : public CFormView
{
	DECLARE_DYNCREATE(CFView3762)

protected:
	CFView3762();           // 动态创建所使用的受保护的构造函数
	virtual ~CFView3762();

public:
	enum { IDD = IDD_DIALOG_3762 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:

	bool m_bFEF001;
	HTREEITEM m_hTree;
	CString m_strPWData;
	INT16U FileCalculateCRC(INT8U CRCHi,INT8U CRCLo,INT8U* InputData, long DataLen);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nLoopData;
	CString SetBeizhu(int nCishu,CString strBeizhu);
	CString SetGershi(int nCishu,CString strGeshi);
	CSetWriteLoopNub m_setWriteLoop;
	bool m_bZuZhen;
	CDlg13762Frame m_dlg13762Zuzhen;
	void GetZuzhenFrame();
	void ShowZuzhenData(INT8U nType = 0);
public:
	FILE* m_fp;
	CDisplayData m_display;
	CGW13762 m_gw13762;
	CCSG13762 m_nw13762;//NW
	sPartQGDW376_2CreatFrame m_ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame m_ptRecvQGDW376_2;
	sPartQCSG376_2CreatFrame m_ptSendQCSG376_2;//NW
	sPartQCSG376_2DeCodeFrame m_ptRecvQCSG376_2;//NW
	CTools m_tools;
	HANDLE m_hThreadsend;
	CRect m_cRect;
	long m_lShowLeft;
	CSetWriteDataDlg m_setWriteDatadlg;
	void KongjianSize(int nID, int cx, int cy, bool bComb = FALSE);
	void SetStruct3762(CString strMessage, CString strAFN_FN , CString strData , CString strDatalen, PartQGDW376_2 & pt3762);
	void UpdataTreeData();
	CPoint m_point; 
	void SetItemCheckState(HTREEITEM item, BOOL bCheck);
public://AFN=15 F001相关数据
	int m_nYU;
	int m_nCHU;
	int m_nDataLong;
	CString m_strMessageData;//信息域地址域
	CStringList m_listStrShengjiData;//升级发送列表
	BOOL SetUpdataListData();//将升级文件保存到发送列表中
	CString GetDuanAndLen(int nduan,int nlen);
	CString strHEX(CString str,bool bDaoxu);
	INT8U SendUpdataData(CString strName, INT8U *F8DataHead, int nChoose = 0);//升级函数
	INT8U SendSecretData(CString strName , int nChoose = 0);
	void SaveDebugData(INT32U pos, INT8U *recvBuf, INT16U recvLen);//保存运行日志到文件
	INT8U RecvDebugData(CString strName, INT8U *F8DataHead , int nChoose = 0);//读运行日志
	void SaveExtendStaVersion(INT32U sn, INT8U *recvBuf, INT16U recvLen);  // 保存STA扩展版本号
	INT8U RecvExtendStaDevStatus(CString strName , INT8U *F8DataHead, int nChoose = 0); //读STA扩展版本号
	void SaveExtendStaDevStatus(INT32U sn, INT8U *recvBuf, INT16U recvLen);  // 保存STA的设备状态
	INT8U RecvExtendStaVersion(CString strName, INT8U *F8DataHead, int nChoose = 0); //读STA的设备状态
	void SaveNodeInfo(INT32U sn, INT8U *recvBuf, INT16U recvLen);  // 保存STA节点信息
	INT8U RecvNodeInfo(CString strName , INT8U *F8DataHead, int nChoose = 0); //读STA节点信息

	INT32U m_F1F0_TimeOut;//并发抄表超时时间
	
public:
	void SetWindowText(CString strData);
	void GetF8Data(INT8U * SrcDatabuf , INT16U SrcDatalen , INT8U * DstDatabuf , INT16U & DstDatalen);
public:
	int m_nDClick;
	bool m_bDCEditAddr;
	CAccessData m_accessData;
	void StorageListData();
	void DisplayData(CString strName ,CString strCode , CString strShowMsg , INT8U * databuf , INT16U datalen , int nType = 0);
public:
	CTreeCtrl m_treeData;
	CEdit m_editShow;
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickTreeData(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkTreeData(NMHDR *pNMHDR, LRESULT *pResult);
	CComboBox m_combType;
	CEdit m_editAddress;
	afx_msg void OnEnSetfocusEditMessage();
	afx_msg void OnEnKillfocusEditMessage();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEnSetfocusEditAddress();
	afx_msg void OnEnKillfocusEditAddress();
	afx_msg void OnBnClickedButtonAddress();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonXy();
	afx_msg void OnBnClickedButtonStop();
	CButton m_btnSend;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonClear();
//	CButton m_editZuzhen;
	CButton m_btnZuZhen;
	afx_msg void OnBnClickedButtonZuzhen();

public://南网相关
	INT32U getNWfn(INT8U GW_AFN , CString GW_Fn);
	CButton button_address;
	afx_msg void OnBnClickedButton1();

	CString m_strFilePath_f0f1;
	void Save_log_File(INT8U* F8DataHead);//保存flash 中的log数据 
};


