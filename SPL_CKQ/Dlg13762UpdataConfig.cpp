// Dlg13762UpdataConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "Dlg13762UpdataConfig.h"
#include "afxdialogex.h"
#include "AccessData.h"
#include "Tools.h"
#include "MainFrm.h"

// CDlg13762UpdataConfig 对话框

IMPLEMENT_DYNAMIC(CDlg13762UpdataConfig, CDialogEx)

CDlg13762UpdataConfig::CDlg13762UpdataConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg13762UpdataConfig::IDD, pParent)
{

}

CDlg13762UpdataConfig::~CDlg13762UpdataConfig()
{
}

void CDlg13762UpdataConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_STATIC_SIZE, m_editFile);
	DDX_Control(pDX, IDC_COMBO_BS, m_combBS);
	//  DDX_Control(pDX, IDC_COMBO_SX, m_combSX);
	DDX_Control(pDX, IDC_COMBO_ZL, m_combZL);
	DDX_Control(pDX, IDC_EDIT_FILE, m_editFile);
	DDX_Control(pDX, IDC_EDIT_FRAMESIZE, m_editFrameSize);
	DDX_Control(pDX, IDC_STATIC_SIZE, m_staticSize);
	DDX_Control(pDX, IDC_CHECK_DX, m_checkDX);
}


BEGIN_MESSAGE_MAP(CDlg13762UpdataConfig, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlg13762UpdataConfig::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CDlg13762UpdataConfig::OnBnClickedButtonOpen)
	ON_EN_CHANGE(IDC_EDIT_FILE, &CDlg13762UpdataConfig::OnEnChangeEditFile)
END_MESSAGE_MAP()


// CDlg13762UpdataConfig 消息处理程序


void CDlg13762UpdataConfig::OnBnClickedOk()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (m_editFile.GetWindowTextLengthW() == 0)
	{
		AfxMessageBox(_T("请选择升级文件"));
		return;
	}
	CString strlistName[2] = {_T("ConfigName") ,_T("MessageData")};
	CString strFile , strFrameSize , strBS , strZL , strDX;
	CAccessData access;
	m_editFile.GetWindowTextW(strFile);
	m_editFrameSize.GetWindowTextW(strFrameSize);
	m_combBS.GetWindowTextW(strBS);
	strBS.Mid(0,2);
	m_combZL.GetWindowTextW(strZL);
	strZL.Mid(0,2);
	if(m_checkDX.GetCheck())
	{
		strDX = _T("1");
	}
	else
	{
		strDX = _T("0");
	}
	CString strlistData = strFile + _T("☆") + strFrameSize + _T("☆") + strBS + _T("☆") + strZL + _T("☆") + strDX + _T("☆");
	CString strSet = _T("MessageData='") + strlistData + _T("'");
	CString stWhere = _T("ConfigName='升级信息'");
	//if(!access.UpdataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("Config"),strSet , stWhere))
	if(!access.UpdataFromTable(pMain->m_PeiZhi_db,_T("Config"),strSet , stWhere))
	{
		AfxMessageBox(_T("数据保存失败!"));
		return;
	}
	CDialogEx::OnOK();
}


BOOL CDlg13762UpdataConfig::OnInitDialog()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();

	CDialogEx::OnInitDialog();
	CAccessData access;
	CTools tools;
	int nHang= 0;
	CString stWhere = _T("ConfigName='升级信息'");
	CString strData;
	CString strlist[10];
	int nNumb = 0;
	m_combBS.AddString(_T("00H:清除下装文件"));
	m_combBS.AddString(_T("03H:本地通讯模块升级文件"));
	m_combBS.AddString(_T("07H:主节点和子节点模块升级"));
	m_combBS.AddString(_T("08H:子节点模块升级"));

	m_combZL.AddString(_T("00H:报文方式下装"));
	//m_combZL.AddString(_T("01H：FTP方式传输"));
	//m_combZL.AddString(_T("02：启动组地址升级"));

	//if(access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
	if(access.SelectDataFromTable(pMain->m_PeiZhi_db,_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
	{
		tools.Split(strData , _T("☆") , strlist , nNumb);
		m_editFile.SetWindowTextW(strlist[0]);
		m_editFrameSize.SetWindowTextW(strlist[1]);
		m_combBS.SetWindowTextW(strlist[2]);
		m_combZL.SetWindowTextW(strlist[3]);
		m_checkDX.SetCheck(_ttoi(strlist[4]));
	}
	else
	{
		AfxMessageBox(_T("获取数据失败!"));
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlg13762UpdataConfig::OnBnClickedButtonOpen()
{
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
		m_editFile.SetWindowText(OpenFilePathName);
		FILE* fp = NULL;
		fp = fopen(pFileName, "rb");
		fseek(fp,0,SEEK_END);
		long nLen = ftell(fp);
		CString strlong;
		strlong.Format(_T("%d"),nLen);
		m_staticSize.SetWindowText(strlong);
		delete[] pFileName;
	}
	
}


void CDlg13762UpdataConfig::OnEnChangeEditFile()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
