// NetViewRepeat.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "NetViewRepeat.h"


// CNetViewRepeat

IMPLEMENT_DYNCREATE(CNetViewRepeat, CFormView)

CNetViewRepeat::CNetViewRepeat()
	: CFormView(CNetViewRepeat::IDD)
{

}

CNetViewRepeat::~CNetViewRepeat()
{
}

void CNetViewRepeat::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNetViewRepeat, CFormView)
END_MESSAGE_MAP()


// CNetViewRepeat 诊断

#ifdef _DEBUG
void CNetViewRepeat::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CNetViewRepeat::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CNetViewRepeat 消息处理程序
