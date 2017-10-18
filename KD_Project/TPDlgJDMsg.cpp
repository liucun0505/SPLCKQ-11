// TPDlgJDMsg.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "TPDlgJDMsg.h"
#include "afxdialogex.h"


// CTPDlgJDMsg 对话框

IMPLEMENT_DYNAMIC(CTPDlgJDMsg, CDialogEx)

CTPDlgJDMsg::CTPDlgJDMsg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTPDlgJDMsg::IDD, pParent)
{

}

CTPDlgJDMsg::~CTPDlgJDMsg()
{
}

void CTPDlgJDMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MSG, m_editMsg);
}


BEGIN_MESSAGE_MAP(CTPDlgJDMsg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTPDlgJDMsg 消息处理程序


void CTPDlgJDMsg::KongjianSize(int nID, int cx, int cy, bool bComb)
{
	CWnd *pWnd;  
	pWnd = GetDlgItem(nID);     //获取控件句柄 
	int fcx=0,fcy=0;
	int nBottom = 0;
	if (bComb == true)
	{
		nBottom = 100;
	}
	if(pWnd)    
	{ 
		CRect rect;   //获取控件变化前大小 
		pWnd->GetWindowRect(&rect); 
		ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标 
		rect.left=0;//调整控件大小 
		rect.right=cx; 
		rect.top=0; 
		rect.bottom = cy;
		pWnd->MoveWindow(rect);//设置控件位置 
	}
}

void CTPDlgJDMsg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect); 
	KongjianSize(IDC_EDIT_MSG , rect.right,rect.bottom , false);
}
