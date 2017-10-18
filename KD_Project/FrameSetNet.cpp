// FrameSetNet.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "FrameSetNet.h"
#include "ViewLetTree.h"
#include "RightTabView.h"
#include "MidNetForm.h"
#include "MainFrm.h"
// CFrameSetNet

IMPLEMENT_DYNCREATE(CFrameSetNet, CMDIChildWnd)

CFrameSetNet::CFrameSetNet()
{

}

CFrameSetNet::~CFrameSetNet()
{
}
//
//BOOL CFrameSetNet::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
//{
//	CRect rc;
//	GetClientRect(&rc);
//	if(!m_wndSplitter.CreateStatic(this,1,2))
//		return FALSE;
//	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CViewLetTree), CSize(rc.Width()/5, rc.Height()), pContext))   
//		return FALSE; 
//	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMidNetForm), CSize(0,0), pContext))   
//		return FALSE; 
//
//	return TRUE;
//}

BEGIN_MESSAGE_MAP(CFrameSetNet, CMDIChildWnd)
	ON_WM_CLOSE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CFrameSetNet 消息处理程序


void CFrameSetNet::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame * pMain = (CMainFrame *)GetParentFrame();
	pMain->m_bNetWork = false;
	pMain->m_bNetWorkOpen = TRUE;
	CMDIChildWnd::OnClose();
}


int CFrameSetNet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetMenu(NULL);
	return 0;
}


BOOL CFrameSetNet::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style   =   WS_CHILD|

		WS_VISIBLE|

		WS_OVERLAPPED|

		WS_CAPTION|

		WS_SYSMENU|

		// FWS_ADDTOTITLE|

		WS_THICKFRAME|

		WS_MINIMIZEBOX|

		WS_MAXIMIZEBOX|

		WS_MAXIMIZE;
	cs.lpszName = _T("网络管理");
	return CMDIChildWnd::PreCreateWindow(cs);
}

BOOL CFrameSetNet::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	CRect rc;
	GetClientRect(&rc);
	if(!m_wndSplitter.CreateStatic(this,1,2))
		return FALSE;
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CViewLetTree), CSize(rc.Width()/5, rc.Height()), pContext))   
		return FALSE; 
	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CRightTabView), CSize(0,0), pContext))   
		return FALSE; 

	return TRUE;
	//return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}


//void CFrameSetNet::OnIdrRbmenuMeterr()
//{
//	// TODO: 在此添加命令处理程序代码
//}
