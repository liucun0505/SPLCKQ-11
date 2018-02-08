#pragma once


// CForm698 框架

class CForm698 : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CForm698)
protected:
	CForm698();           // 动态创建所使用的受保护的构造函数
	virtual ~CForm698();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


