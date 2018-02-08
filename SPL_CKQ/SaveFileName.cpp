// SaveFileName.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "SaveFileName.h"
#include "afxdialogex.h"
#include "afxdialogex.h"
#include "AccessData.h"
#include "Tools.h"
#include "MainFrm.h

// SaveFileName 对话框

IMPLEMENT_DYNAMIC(SaveFileName, CDialogEx)

SaveFileName::SaveFileName(CWnd* pParent /*=NULL*/)
	: CDialogEx(SaveFileName::IDD, pParent)
{

}

SaveFileName::~SaveFileName()
{
}

void SaveFileName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_savefilename);
}


BEGIN_MESSAGE_MAP(SaveFileName, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &SaveFileName::OnEnChangeEdit1)
END_MESSAGE_MAP()


// SaveFileName 消息处理程序
BOOL SaveFileName::OnInitDialog()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();

	CDialogEx::OnInitDialog();
	CAccessData access;
	CTools tools;
	int nHang= 0;
	CString stWhere = _T("ConfigName='调试信息'");
	CString strData;
	CString strlist[10];
	int nNumb = 0;
	
	//if(access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
	if(access.SelectDataFromTable(pMain->m_PeiZhi_db,_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
	{
		m_savefilename.SetWindowTextW(strlist[0]);
	}
	else
	{
		AfxMessageBox(_T("获取数据失败!"));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void SaveFileName::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
