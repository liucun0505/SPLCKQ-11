#pragma once

#include "MyFrameMsgTabCtrl.h"
// CFrameShowWnd

class CFrameShowWnd : public CDockablePane
{
	DECLARE_DYNAMIC(CFrameShowWnd)

public:
	CFrameShowWnd();
	virtual ~CFrameShowWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CMyFrameMsgTabCtrl m_myTabCtrl;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnCopyframe();
};


