// Form698.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "Form698.h"
#include "MainFrm.h"

// CForm698

IMPLEMENT_DYNCREATE(CForm698, CMDIChildWnd)

CForm698::CForm698()
{

}

CForm698::~CForm698()
{
}


BEGIN_MESSAGE_MAP(CForm698, CMDIChildWnd)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CForm698 消息处理程序


void CForm698::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame * pMain = (CMainFrame *)GetParentFrame();
	pMain->m_bFrame698 = false;
	CMDIChildWnd::OnClose();
}


BOOL CForm698::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	//cs.style   =   WS_CHILD|

	//	WS_VISIBLE|

	//	WS_OVERLAPPED|

	//	WS_CAPTION|

	//	WS_SYSMENU|

	//	// FWS_ADDTOTITLE|

	//	WS_THICKFRAME|

	//	WS_MINIMIZEBOX|

	//	WS_MAXIMIZEBOX|

	//	WS_MAXIMIZE;
	//cs.lpszName = _T("698测试");
	return CMDIChildWnd::PreCreateWindow(cs);
}
