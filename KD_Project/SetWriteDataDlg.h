#if !defined(AFX_SETWRITEDATADLG_H__1D82F39C_A5A3_4EAC_A8D9_101BC871C86A__INCLUDED_)
#define AFX_SETWRITEDATADLG_H__1D82F39C_A5A3_4EAC_A8D9_101BC871C86A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetWriteDataDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetWriteDataDlg dialog
#include "CDTL2007.h"
#include "Tools.h"
class CSetWriteDataDlg : public CDialog
{
// Construction
public:
	CSetWriteDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetWriteDataDlg)
	enum { IDD = IDD_SETWRITEDATA_DLG };
	CEdit	m_editData;
	CListCtrl	m_listData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetWriteDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	CString m_strWriteData;
	CString m_strWriteDataMessage;
	bool m_bWrite;
	int m_hitRow , m_hitCol;
	CTools m_tools;
	CString m_strWriteName;
	bool m_bYesOrNo;
	bool m_bTwo;
	CString m_strFN;
	CString m_strINIname;
	CString m_strBeizhu;
	CString m_strGeshi;
	CRect m_rect;
	int m_nFenhao;
	int m_nBaifenhao[100];
	int m_nData;
	int m_nx;
	int m_ny;
	int m_nwidth;
	int m_nheight;
	int m_ntiaoguo;
	CString m_strStatic;
	CString m_strEdit;
	CString GetZijie(CString strBeizhu,CString strEdit);
	CString GetData(int n,CString str);
	CString GetStatic(int n);
	CString GetEdit(int n);
	void setEdit();
	void setData();
	CString GetBits(CString strBeizhu,int nZhi);
	CString GetBin(CString strBeizhu,CString strEdit);
	CString GetBit(CString strBeizhu,int n);
	CString GetChar(CString strBeizhu,CString strEdit);
	CString GetAscll(CString strBeizhu,CString strEdit);

	CString GetDADT(CString strEdit);
	CString GetTIME(CString strEdit);
	CString GetChina(CString strEdit);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetWriteDataDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonChakan();
	afx_msg void OnClickListData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETWRITEDATADLG_H__1D82F39C_A5A3_4EAC_A8D9_101BC871C86A__INCLUDED_)
