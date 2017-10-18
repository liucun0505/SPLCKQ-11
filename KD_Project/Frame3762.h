#pragma once
class CFrame3762 : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CFrame3762)
protected:
	CFrame3762();           // 动态创建所使用的受保护的构造函数
	virtual ~CFrame3762();
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnClose();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


