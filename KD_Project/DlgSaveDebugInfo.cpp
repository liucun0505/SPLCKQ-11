// DlgSaveDebugInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DlgSaveDebugInfo.h"
#include "afxdialogex.h"
#include "AccessData.h"
#include "Tools.h"
#include "MainFrm.h"

// DlgSaveDebugInfo 对话框

IMPLEMENT_DYNAMIC(DlgSaveDebugInfo, CDialogEx)

DlgSaveDebugInfo::DlgSaveDebugInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgSaveDebugInfo::IDD, pParent)
{

}

DlgSaveDebugInfo::~DlgSaveDebugInfo()
{
}

void DlgSaveDebugInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE, FileName);
}


BEGIN_MESSAGE_MAP(DlgSaveDebugInfo, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_FILE, &DlgSaveDebugInfo::OnEnChangeEditFile)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &DlgSaveDebugInfo::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDOK, &DlgSaveDebugInfo::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgSaveDebugInfo 消息处理程序


void DlgSaveDebugInfo::OnEnChangeEditFile()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void DlgSaveDebugInfo::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString OpenFilePathName;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_NOCHANGEDIR);
	int nOK=dlg.DoModal();
	if (nOK == IDOK)
	{
		OpenFilePathName = dlg.GetPathName();
		int len =WideCharToMultiByte(CP_ACP,0,OpenFilePathName,OpenFilePathName.GetLength(),NULL,0,NULL,NULL);
		char * pFileName = new char[len + 1];
		WideCharToMultiByte(CP_ACP,0,OpenFilePathName,OpenFilePathName.GetLength(),pFileName,len,NULL,NULL);
		pFileName[len] ='\0';
		FileName.SetWindowText(OpenFilePathName);
/*		FILE* fp = NULL;
		fp = fopen(pFileName, "rb");
		fseek(fp,0,SEEK_END);
		long nLen = ftell(fp);
		CString strlong;
		strlong.Format(_T("%d"),nLen);*/
		delete[] pFileName;
	}
	
}


void DlgSaveDebugInfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (FileName.GetWindowTextLengthW() == 0)
	{
		AfxMessageBox(_T("请选择升级文件"));
		return;
	}
	CString strlistName[2] = {_T("ConfigName") ,_T("MessageData")};
	CString strFile;
	CAccessData access;
	FileName.GetWindowTextW(strFile);
	
	CString strlistData = strFile + _T("☆");
	CString strSet = _T("MessageData='") + strlistData + _T("'");
	CString stWhere = _T("ConfigName='调试信息'");
	//if(!access.UpdataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("Config"),strSet , stWhere))
	if(!access.UpdataFromTable(pMain->m_PeiZhi_db,_T("Config"),strSet , stWhere))
	{
		AfxMessageBox(_T("数据保存失败!"));
		return;
	}

	CDialogEx::OnOK();
}


BOOL DlgSaveDebugInfo::OnInitDialog(void)
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
		tools.Split(strData , _T("☆") , strlist , nNumb);
		FileName.SetWindowTextW(strlist[0]);
	}
	else
	{
		AfxMessageBox(_T("获取数据失败!"));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}
