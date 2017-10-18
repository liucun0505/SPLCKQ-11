#pragma once


// CChildWnd13762

class CChildWnd13762 : public CMDIChildWndEx
{
	DECLARE_DYNAMIC(CChildWnd13762)

public:
	CChildWnd13762();
	virtual ~CChildWnd13762();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


