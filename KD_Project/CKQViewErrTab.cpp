// CKQViewErrTab.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "CKQViewErrTab.h"
#include "CKQViewTabErrMet.h"
#include "CKQViewTabErrMod.h"

// CCKQViewErrTab

IMPLEMENT_DYNCREATE(CCKQViewErrTab, CTabView)

CCKQViewErrTab::CCKQViewErrTab()
{

}

CCKQViewErrTab::~CCKQViewErrTab()
{
}

BEGIN_MESSAGE_MAP(CCKQViewErrTab, CTabView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CCKQViewErrTab 诊断

#ifdef _DEBUG
void CCKQViewErrTab::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CCKQViewErrTab::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCKQViewErrTab 消息处理程序


int CCKQViewErrTab::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GetTabControl().SetLocation( CMFCTabCtrl:: LOCATION_TOP); //标签置顶
	GetTabControl().ModifyTabStyle( CMFCTabCtrl:: STYLE_3D_ROUNDED_SCROLL);//3D效果
	GetTabControl().EnableAutoColor( TRUE );//自动着色
	GetTabControl().SetTabBorderSize( 5 ); //边框大小
	GetTabControl().EnableTabSwap( FALSE );    //禁止拖动 

	AddView(RUNTIME_CLASS(CCKQViewTabErrMod),_T("模块故障信息"),300,NULL);
	AddView(RUNTIME_CLASS(CCKQViewTabErrMet),_T("电表故障信息"),300,NULL);
	return 0;
}


//void CCKQViewErrTab::OnIdrRbmenuMeterr()
//{
//	// TODO: 在此添加命令处理程序代码
//}
