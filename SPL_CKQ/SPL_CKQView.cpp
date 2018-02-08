
// SPL_CKQView.cpp : CSPL_CKQView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SPL_CKQ.h"
#endif

#include "SPL_CKQDoc.h"
#include "SPL_CKQView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSPL_CKQView

IMPLEMENT_DYNCREATE(CSPL_CKQView, CView)

BEGIN_MESSAGE_MAP(CSPL_CKQView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSPL_CKQView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSPL_CKQView 构造/析构

CSPL_CKQView::CSPL_CKQView()
{
	// TODO: 在此处添加构造代码

}

CSPL_CKQView::~CSPL_CKQView()
{
}

BOOL CSPL_CKQView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSPL_CKQView 绘制

void CSPL_CKQView::OnDraw(CDC* /*pDC*/)
{
	CSPL_CKQDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CSPL_CKQView 打印


void CSPL_CKQView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSPL_CKQView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSPL_CKQView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSPL_CKQView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CSPL_CKQView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSPL_CKQView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSPL_CKQView 诊断

#ifdef _DEBUG
void CSPL_CKQView::AssertValid() const
{
	CView::AssertValid();
}

void CSPL_CKQView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSPL_CKQDoc* CSPL_CKQView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSPL_CKQDoc)));
	return (CSPL_CKQDoc*)m_pDocument;
}
#endif //_DEBUG


// CSPL_CKQView 消息处理程序
