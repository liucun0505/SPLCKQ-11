
// KD_ProjectView.cpp : CKD_ProjectView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "KD_Project.h"
#endif

#include "KD_ProjectDoc.h"
#include "KD_ProjectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKD_ProjectView

IMPLEMENT_DYNCREATE(CKD_ProjectView, CView)

BEGIN_MESSAGE_MAP(CKD_ProjectView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKD_ProjectView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CKD_ProjectView 构造/析构

CKD_ProjectView::CKD_ProjectView()
{
	// TODO: 在此处添加构造代码

}

CKD_ProjectView::~CKD_ProjectView()
{
}

BOOL CKD_ProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CKD_ProjectView 绘制

void CKD_ProjectView::OnDraw(CDC* /*pDC*/)
{
	CKD_ProjectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CKD_ProjectView 打印


void CKD_ProjectView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKD_ProjectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CKD_ProjectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CKD_ProjectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CKD_ProjectView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKD_ProjectView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKD_ProjectView 诊断

#ifdef _DEBUG
void CKD_ProjectView::AssertValid() const
{
	CView::AssertValid();
}

void CKD_ProjectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKD_ProjectDoc* CKD_ProjectView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKD_ProjectDoc)));
	return (CKD_ProjectDoc*)m_pDocument;
}
#endif //_DEBUG


// CKD_ProjectView 消息处理程序
