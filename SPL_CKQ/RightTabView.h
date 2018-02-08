#pragma once


// CRightTabView 视图

class CRightTabView : public CTabView
{
	DECLARE_DYNCREATE(CRightTabView)

protected:
	CRightTabView();           // 动态创建所使用的受保护的构造函数
	virtual ~CRightTabView();

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
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
public:
	CCreateContext m_context;
	int m_nOpenNumb;
	int m_nFindNet;
	int m_nTPShow;
	int m_nPointToPoint;
//	afx_msg void OnClose();
	virtual void OnInitialUpdate();
//	virtual void OnDraw(CDC* /*pDC*/);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


