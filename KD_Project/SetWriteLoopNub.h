#if !defined(AFX_SETWRITELOOPNUB_H__0F424A25_88F9_4C8C_A0EF_F0D9C4669841__INCLUDED_)
#define AFX_SETWRITELOOPNUB_H__0F424A25_88F9_4C8C_A0EF_F0D9C4669841__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetWriteLoopNub.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetWriteLoopNub dialog

class CSetWriteLoopNub : public CDialog
{
// Construction
public:
	CString m_strName;
	CSetWriteLoopNub(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetWriteLoopNub)
	enum { IDD = IDD_DIALOG_LOOP };
	CString	m_strNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetWriteLoopNub)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetWriteLoopNub)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETWRITELOOPNUB_H__0F424A25_88F9_4C8C_A0EF_F0D9C4669841__INCLUDED_)
