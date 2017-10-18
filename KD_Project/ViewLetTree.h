#pragma once

#include "KD_ProjectDoc.h"
// CViewLetTree 视图

class CViewLetTree : public CTreeView
{
	DECLARE_DYNCREATE(CViewLetTree)

protected:
	CViewLetTree();           // 动态创建所使用的受保护的构造函数
	virtual ~CViewLetTree();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	CImageList m_ilDrives;//图片列表
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


