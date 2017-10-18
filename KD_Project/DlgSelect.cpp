// DlgSelect.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DlgSelect.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// DlgSelect 对话框

IMPLEMENT_DYNAMIC(DlgSelect, CDialogEx)

DlgSelect::DlgSelect(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgSelect::IDD, pParent)
{

}

DlgSelect::~DlgSelect()
{
}

void DlgSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_NW_GW, m_NW_GW);
}




BEGIN_MESSAGE_MAP(DlgSelect, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgSelect::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgSelect 消息处理程序
BOOL DlgSelect::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	AddData();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void DlgSelect::AddData()
{
	m_NW_GW.AddString(_T("国网"));
	m_NW_GW.AddString(_T("南网"));
	m_NW_GW.SetCurSel(0);
}

void DlgSelect::OnBnClickedOk()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	if(m_NW_GW.GetCurSel()==0)
	{
	pMain->NW_OR_GW=0;
	}
	if(m_NW_GW.GetCurSel()==1)
	{
	pMain->NW_OR_GW=1;
	}
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
