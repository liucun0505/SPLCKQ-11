// CKQTabViewTPshow.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "CKQTabViewTPshow.h"
#include "NetViewTPShow.h"
#include "CKQViewTPShowOldData.h"
// CCKQTabViewTPshow

IMPLEMENT_DYNCREATE(CCKQTabViewTPshow, CTabView)

CCKQTabViewTPshow::CCKQTabViewTPshow()
{

}

CCKQTabViewTPshow::~CCKQTabViewTPshow()
{
}

BEGIN_MESSAGE_MAP(CCKQTabViewTPshow, CTabView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CCKQTabViewTPshow 诊断

#ifdef _DEBUG
void CCKQTabViewTPshow::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CCKQTabViewTPshow::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCKQTabViewTPshow 消息处理程序
int CCKQTabViewTPshow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GetTabControl().SetLocation( CMFCTabCtrl:: LOCATION_TOP); //标签置顶
	GetTabControl().ModifyTabStyle( CMFCTabCtrl:: STYLE_3D_ROUNDED_SCROLL);//3D效果
	GetTabControl().EnableAutoColor( TRUE );//自动着色
	GetTabControl().SetTabBorderSize( 5 ); //边框大小
	GetTabControl().EnableTabSwap( FALSE );    //禁止拖动 

	AddView(RUNTIME_CLASS(CNetViewTPShow),_T("实时拓扑图"),300,NULL);
	AddView(RUNTIME_CLASS(CCKQViewTPShowOldData),_T("历史拓扑图"),300,NULL);
	return 0;
}
