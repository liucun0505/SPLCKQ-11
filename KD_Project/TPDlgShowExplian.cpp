// TPDlgShowExplian.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "TPDlgShowExplian.h"
#include "afxdialogex.h"


// CTPDlgShowExplian 对话框

IMPLEMENT_DYNAMIC(CTPDlgShowExplian, CDialogEx)

CTPDlgShowExplian::CTPDlgShowExplian(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTPDlgShowExplian::IDD, pParent)
{

}

CTPDlgShowExplian::~CTPDlgShowExplian()
{
}

void CTPDlgShowExplian::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CCO, m_staticCCO);
	DDX_Control(pDX, IDC_STATIC_UCCO, m_staticUCCO);
	DDX_Control(pDX, IDC_STATIC_STA, m_staticSTA);
	DDX_Control(pDX, IDC_STATIC_USTA, m_staticUSTA);
	DDX_Control(pDX, IDC_STATIC_PCO, m_staticPCO);
	DDX_Control(pDX, IDC_STATIC_OUT, m_staticOUT);
}


BEGIN_MESSAGE_MAP(CTPDlgShowExplian, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTPDlgShowExplian 消息处理程序


BOOL CTPDlgShowExplian::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	m_BrushAll[2].CreateSolidBrush(RGB(255,0,0));//CC0
	m_BrushAll[3].CreateSolidBrush(RGB(255,128,128));//U_CCO
	m_BrushAll[4].CreateSolidBrush(RGB(0,255,0));//STA
	m_BrushAll[5].CreateSolidBrush(RGB(128,255,128));//U_STA
	m_BrushAll[6].CreateSolidBrush(RGB(255,128,64));//PCO
	m_BrushAll[7].CreateSolidBrush(RGB(192,192,192));//掉线
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CTPDlgShowExplian::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CString str = _T("");
	CDC *pDc;
	pDc = GetDC();
	pDc->BeginPath();
	pDc->SelectObject(&m_BrushAll[2]); //CCO
	pDc->EndPath();
	pDc->Ellipse(30,30,60,60); 
	str.Format(_T("%d") , m_nList[0]);
	m_staticCCO.SetWindowTextW(_T("CCO (") + str +  _T(")"));
	//

	pDc->BeginPath();
	pDc->SelectObject(&m_BrushAll[3]); //U_CCO
	pDc->EndPath();
	pDc->Ellipse(30,70,60,100); 
	str.Format(_T("%d") , m_nList[1]);
	m_staticUCCO.SetWindowTextW(_T("UCCO (") + str +  _T(")"));

	pDc->BeginPath();
	pDc->SelectObject(&m_BrushAll[4]); //STA
	pDc->EndPath();
	pDc->Ellipse(30,110,60,140); 
	str.Format(_T("%d") , m_nList[2]);
	m_staticSTA.SetWindowTextW(_T("STA (") + str +  _T(")"));

	pDc->BeginPath();
	pDc->SelectObject(&m_BrushAll[5]); //U_STA
	pDc->EndPath();
	pDc->Ellipse(30,150,60,180); 
	str.Format(_T("%d") , m_nList[3]);
	m_staticUSTA.SetWindowTextW(_T("USTA (") + str +  _T(")"));

	pDc->BeginPath();
	pDc->SelectObject(&m_BrushAll[6]); //PCO
	pDc->EndPath();
	pDc->Ellipse(30,190,60,220); 
	str.Format(_T("%d") , m_nList[4]);
	m_staticPCO.SetWindowTextW(_T("PCO (") + str +  _T(")"));

	pDc->BeginPath();
	pDc->SelectObject(&m_BrushAll[7]); //掉线
	pDc->EndPath();
	pDc->Ellipse(30,230,60,260); 
	str.Format(_T("%d") , m_nList[5]);
	m_staticOUT.SetWindowTextW(_T("掉线 (") + str +  _T(")"));

	pDc->FillPath();
}
void CTPDlgShowExplian::GetNumb(int * nNumb)
{
	for(int n = 0 ; n < 10 ; n ++)
	{
		m_nList[n] = nNumb[n];
	}
}