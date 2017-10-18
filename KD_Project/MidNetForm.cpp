// MidNetForm.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "MidNetForm.h"
#include "NetViewTPShow.h"

// CMidNetForm

IMPLEMENT_DYNCREATE(CMidNetForm, CView)

CMidNetForm::CMidNetForm()
{
	m_pdlgNetTP = NULL;
}

CMidNetForm::~CMidNetForm()
{
}

BEGIN_MESSAGE_MAP(CMidNetForm, CView)
END_MESSAGE_MAP()


// CMidNetForm 绘图

void CMidNetForm::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CMidNetForm 诊断

#ifdef _DEBUG
void CMidNetForm::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMidNetForm::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMidNetForm 消息处理程序


void CMidNetForm::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if(lHint != 0)
	{
		CRect rect;
		switch(lHint)
		{
		case 1:
			GetClientRect(rect); 
			m_TPShowFindList.SetWindowPos(NULL,rect.left,rect.top,rect.right,rect.bottom,SWP_SHOWWINDOW);
			m_TPShowFindList.ShowWindow(SW_SHOWMAXIMIZED);
			break;
		case 2:

			break;
		case 3:
			AfxMessageBox(_T("点对点通讯"));
			break;
		}
	}
}


void CMidNetForm::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_TPShowFindList.Create(IDD_DIALOG_FINDLIST,this);
}
