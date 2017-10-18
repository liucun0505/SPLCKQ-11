#pragma once
#include "afxwin.h"
#include "GW13762.h"
#include "CSG13762.h"
#include "Tools.h"
#include "DisplayData.h"
// CCKQViewConfig 窗体视图

class CCKQViewConfig : public CFormView
{
	DECLARE_DYNCREATE(CCKQViewConfig)

protected:
	CCKQViewConfig();           // 动态创建所使用的受保护的构造函数
	virtual ~CCKQViewConfig();

public:
	enum { IDD = IDD_DIALOG_CKQ_CONFIG };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CDisplayData m_display;
	int m_nRorW;
//#ifdef _STD_CSG  //南网标准
	void DisplayDataToView(sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2);
//#endif

//#ifdef _STD_CSG  //南网标准
	bool GetDataToSturt(INT8U &DstAFN , INT32U &DstFN , INT8U * DstBuf , INT16U & DstBuflen);
//#endif
	void DisplayDataToView(sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2);
	bool GetDataToSturt(INT8U &DstAFN , INT16U &DstFN , INT8U * DstBuf , INT16U & DstBuflen);
	CTools m_tools;
	sPartQGDW376_2CreatFrame m_ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame m_ptRecvQGDW376_2;
	HANDLE m_hThreadsend;
	void SetItemEnableF();
	void Updata();
	void MoveMap(int nID);
	CFont m_Font;
	CBrush m_Back;
	CListBox m_listType;
	virtual void OnInitialUpdate();
	afx_msg void OnSelchangeListType();
	CEdit m_edit101;
	CEdit m_edit11;
	CEdit m_edit12;
	CEdit m_edit21;
	CEdit m_edit22;
	CEdit m_edit31;
	CEdit m_edit32;
	CEdit m_edit33;
	CEdit m_edit51;
	CComboBox m_comb11;
	CComboBox m_comb31;
	CComboBox m_comb41;
	CComboBox m_comb42;
	CComboBox m_comb61;
	CComboBox m_comb71;
	CComboBox m_comb81;
	CComboBox m_comb91;
	CEdit m_editMMAC;
	CEdit m_editTime;
	CButton m_btnClear;
	CButton m_btnRead;
	CButton m_btnWrite;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonClian();
	afx_msg void OnBnClickedButtonRead();
	afx_msg void OnBnClickedButtonWrite();
	CStatic m_pictureMap;
};


