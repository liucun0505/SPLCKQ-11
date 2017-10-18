// RightTabView.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "KD_ProjectDoc.h"
#include "RightTabView.h"
#include "FormTabView1.h"
#include "NetViewTPShow.h"
#include "NetViewPToP.h"
#include "NetViewRepeat.h"
#include "CKQViewConfig.h"
#include "FView3762.h"
#include "CKQViewUpdata.h"
#include "CKQViewErrTab.h"
#include "CKQTabViewTPshow.h"
#include "DlgExtReadMeter.h"


// CRightTabView

IMPLEMENT_DYNCREATE(CRightTabView, CTabView)

CRightTabView::CRightTabView()
{
	m_nFindNet = -1;
	m_nTPShow = -1;
	m_nPointToPoint = -1;
	m_nOpenNumb = -1;
}

CRightTabView::~CRightTabView()
{
}

BEGIN_MESSAGE_MAP(CRightTabView, CTabView)
	ON_WM_CREATE()
//	ON_WM_CLOSE()
//ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRightTabView 诊断

#ifdef _DEBUG
void CRightTabView::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightTabView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightTabView 消息处理程序

int CRightTabView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GetTabControl().SetLocation( CMFCTabCtrl:: LOCATION_TOP); //标签置顶
	GetTabControl().ModifyTabStyle( CMFCTabCtrl:: STYLE_3D_ROUNDED_SCROLL);//3D效果
	GetTabControl().EnableAutoColor( TRUE );//自动着色
	GetTabControl().SetTabBorderSize( 10 ); //边框大小
	GetTabControl().EnableTabSwap( FALSE );    //禁止拖动 

	//GetTabControl().HideSingleTab( TRUE );   //单个Tab时候不显示Tab标签
	/*CCreateContext context;
	context.m_pCurrentDoc = GetDocument();
	context.m_pNewViewClass = RUNTIME_CLASS(CFormTabView1);*/
	AddView(RUNTIME_CLASS(CFormTabView1),_T("网络搜索"),200,NULL);
	AddView(RUNTIME_CLASS(CCKQTabViewTPshow),_T("拓扑显示"),200,NULL);
	AddView(RUNTIME_CLASS(CNetViewPToP),_T("点对点通讯"),300,NULL);
	AddView(RUNTIME_CLASS(CCKQViewConfig),_T("常用查询与设定"),300,NULL);
	AddView(RUNTIME_CLASS(CCKQViewUpdata),_T("模块升级"),300,NULL);
	AddView(RUNTIME_CLASS(CCKQViewErrTab),_T("故障信息"),300,NULL);
	AddView(RUNTIME_CLASS(CFView3762),_T("抄控器转发"),300,NULL);

	
	
	return 0;
}


BOOL CRightTabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CTabView::PreCreateWindow(cs);
}

void CRightTabView::OnInitialUpdate()
{
	CTabView::OnInitialUpdate();
	//
}
void CRightTabView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	SetActiveView(lHint);

}
