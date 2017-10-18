#pragma once


// CNetTabView 视图

class CNetTabView : public CTabView
{
	DECLARE_DYNCREATE(CNetTabView)

protected:
	CNetTabView();           // 动态创建所使用的受保护的构造函数
	virtual ~CNetTabView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


