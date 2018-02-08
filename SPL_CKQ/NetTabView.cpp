// NetTabView.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "NetTabView.h"
#include "FormTabView1.h"
#include "NetViewTPShow.h"
#include "NetViewRepeat.h"

// CNetTabView

IMPLEMENT_DYNCREATE(CNetTabView, CTabView)

CNetTabView::CNetTabView()
{

}

CNetTabView::~CNetTabView()
{
}

BEGIN_MESSAGE_MAP(CNetTabView, CTabView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CNetTabView 诊断

#ifdef _DEBUG
void CNetTabView::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CNetTabView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CNetTabView 消息处理程序


void CNetTabView::OnInitialUpdate()
{
	CTabView::OnInitialUpdate();
}


int CNetTabView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GetTabControl().SetLocation( CMFCTabCtrl:: LOCATION_TOP); //标签置顶
	GetTabControl().ModifyTabStyle( CMFCTabCtrl:: STYLE_3D_ROUNDED_SCROLL);//3D效果
	GetTabControl().EnableAutoColor( TRUE );//自动着色
	GetTabControl().SetTabBorderSize( 5 ); //边框大小
	GetTabControl().EnableTabSwap( FALSE );    //禁止拖动 
	CCreateContext context;
	//AddView(RUNTIME_CLASS(CFormTabView1),_T("网络搜索"),200,&m_context);
	context.m_pNewViewClass = RUNTIME_CLASS(CFormTabView1);
	context.m_pCurrentDoc = GetDocument();
	AddView(RUNTIME_CLASS(CFormTabView1),_T("网络搜索"),200,&context);

	context.m_pNewViewClass = RUNTIME_CLASS(CNetViewTPShow);
	AddView(RUNTIME_CLASS(CNetViewTPShow),_T("拓扑显示"),200,&context);

	context.m_pNewViewClass = RUNTIME_CLASS(CNetViewTPShow);
	AddView(RUNTIME_CLASS(CNetViewTPShow),_T("拓扑显示"),200,&context);

	
	return 0;
}
