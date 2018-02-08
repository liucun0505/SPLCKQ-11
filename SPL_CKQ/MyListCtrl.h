#if !defined(AFX_MYLISTCTRL_H__42C98E83_FEBD_41E5_BA71_CE83E47AF1C1__INCLUDED_)
#define AFX_MYLISTCTRL_H__42C98E83_FEBD_41E5_BA71_CE83E47AF1C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//
#include <vector>
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window
struct ITEM_CHECK
{
 int item;                 //第几行
 int flag;                 //falg 0是空，1是被选中，-1是变灰
};


class CMyListCtrl : public CListCtrl
{
// Construction
public:
	CMyListCtrl();
	vector<ITEM_CHECK>      m_itemVector;
// Attributes
public:
	void DrawItem(LPDRAWITEMSTRUCT   lpdis);
	//int InsertItem(int nItem,LPCTSTR lpszItem);

// Operations
public:
	int m_itemYes;
	int m_nChooseList;

	//int sort_column; // 记录点击的列
 //
 //    bool method; // 记录比较方法
	 //int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl)

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
//	afx_msg void OnCopyframe();
//	afx_msg void OnUpdateCopyframe(CCmdUI *pCmdUI);
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__42C98E83_FEBD_41E5_BA71_CE83E47AF1C1__INCLUDED_)
