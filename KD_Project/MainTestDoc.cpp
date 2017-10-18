// MainTestDoc.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "MainTestDoc.h"


// CMainTestDoc

IMPLEMENT_DYNCREATE(CMainTestDoc, CDocument)

CMainTestDoc::CMainTestDoc()
{
}

BOOL CMainTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CMainTestDoc::~CMainTestDoc()
{
}


BEGIN_MESSAGE_MAP(CMainTestDoc, CDocument)
END_MESSAGE_MAP()


// CMainTestDoc 诊断

#ifdef _DEBUG
void CMainTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CMainTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CMainTestDoc 序列化

void CMainTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}
#endif


// CMainTestDoc 命令
