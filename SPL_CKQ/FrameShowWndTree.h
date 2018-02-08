#pragma once
#include "MyTreeCtrl.h"
#include "Tools.h"
#include "AccessData.h"

// CFrameShowWndTree

class CFrameShowWndTree : public CDockablePane
{
	DECLARE_DYNAMIC(CFrameShowWndTree)

public:
	CFrameShowWndTree();
	virtual ~CFrameShowWndTree();

	CFont m_Font;
	CAccessData m_access;
	CTools m_tools;
	CString m_strlist[1000];
	CImageList m_imageList1;
	void InsertItemToTreeList(CString strTableName);
	void MyExpandTree(HTREEITEM hTreeItem);

protected:
	MyTreeCtrl m_treeData;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


