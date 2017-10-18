
// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "KD_Project.h"
#include "ChildFrm.h"
#include "MainFrm.h"
#include "ViewLetTree.h"
#include "RightTabView.h"
#include "KD_ProjectView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_CLOSE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	// TODO: 在此添加成员初始化代码
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
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
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;
	
	return TRUE;
}

// CChildFrame 诊断

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame 消息处理程序


void CChildFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame * pMain = (CMainFrame *)GetParentFrame();
	pMain->m_bNetWork = false;
	CMDIChildWndEx::OnClose();
}


int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//SetMenu(NULL);
	return 0;
}


BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	return TRUE;
}