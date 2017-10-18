#pragma once

#include "DlgNetTP.h"
#include "TPShowFindList.h"
// CMidNetForm 视图

class CMidNetForm : public CView
{
	DECLARE_DYNCREATE(CMidNetForm)

protected:
	CMidNetForm();           // 动态创建所使用的受保护的构造函数
	virtual ~CMidNetForm();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	CTPShowFindList m_TPShowFindList;
	CDlgNetTP * m_pdlgNetTP;
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
public:
	virtual void OnInitialUpdate();
};


