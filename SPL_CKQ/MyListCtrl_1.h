#pragma once


// MyListCtrl_1

class MyListCtrl_1 : public CListCtrl
{
	DECLARE_DYNAMIC(MyListCtrl_1)

public:
	MyListCtrl_1();
	virtual ~MyListCtrl_1();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


