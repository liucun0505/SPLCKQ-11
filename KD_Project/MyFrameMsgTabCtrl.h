#pragma once


// CMyFrameMsgTabCtrl
#include "MyListCtrl.h"
class CMyFrameMsgTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyFrameMsgTabCtrl)

public:
	CMyFrameMsgTabCtrl();
	virtual ~CMyFrameMsgTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl m_ctrlMssage;
	CMyListCtrl m_ctrlFrame;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


