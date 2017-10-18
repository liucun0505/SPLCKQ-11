#pragma once


// CCKQViewErrTab 视图

class CCKQViewErrTab : public CTabView
{
	DECLARE_DYNCREATE(CCKQViewErrTab)

protected:
	CCKQViewErrTab();           // 动态创建所使用的受保护的构造函数
	virtual ~CCKQViewErrTab();

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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnIdrRbmenuMeterr();
};


