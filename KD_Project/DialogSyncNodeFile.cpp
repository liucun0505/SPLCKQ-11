// DlgExtStaStatus.cpp : implementation file
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DialogSyncNodeFile.h"
#include "afxdialogex.h"
#include "AccessData.h"
#include "Tools.h"
#include "MainFrm.h"




using namespace std;
// DlgExtStaStatus dialog

IMPLEMENT_DYNAMIC(DialogSyncNodeFile, CDialogEx)

DialogSyncNodeFile::DialogSyncNodeFile(CString stWhere, CWnd* pParent /*=NULL*/)
: CDialogEx(DialogSyncNodeFile::IDD, pParent)
, m_ClearFirst(0)
{
	m_stWhere = stWhere;
}

DialogSyncNodeFile::~DialogSyncNodeFile()
{
}

void DialogSyncNodeFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE_1_1, FileName1);
	DDX_Control(pDX, IDC_EDIT1_1, m_editNodeNum);
	DDX_Control(pDX, IDC_EDIT1, editStartMAC);
	DDX_Control(pDX, IDC_EDIT2, editTotalNodeNum);
}


BEGIN_MESSAGE_MAP(DialogSyncNodeFile, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_1_1, &DialogSyncNodeFile::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDCANCEL_1_1, &DialogSyncNodeFile::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK_1_1, &DialogSyncNodeFile::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO2, &DialogSyncNodeFile::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &DialogSyncNodeFile::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO1, &DialogSyncNodeFile::OnBnClickedRadio1)
END_MESSAGE_MAP()


// DlgExtStaStatus message handlers


void DialogSyncNodeFile::OnBnClickedButtonOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString OpenFilePathName;
	CFileDialog dlg(TRUE, NULL, NULL, OFN_NOCHANGEDIR);
	int nOK = dlg.DoModal();
	if (nOK == IDOK)
	{
		OpenFilePathName = dlg.GetPathName();
		int len = WideCharToMultiByte(CP_ACP, 0, OpenFilePathName, OpenFilePathName.GetLength(), NULL, 0, NULL, NULL);
		char * pFileName = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, OpenFilePathName, OpenFilePathName.GetLength(), pFileName, len, NULL, NULL);
		pFileName[len + 1] = '\0';
		FileName1.SetWindowText(OpenFilePathName);
		/*		FILE* fp = NULL;
		fp = fopen(pFileName, "rb");
		fseek(fp,0,SEEK_END);
		long nLen = ftell(fp);
		CString strlong;
		strlong.Format(_T("%d"),nLen);*/
	}
}
BOOL DialogSyncNodeFile::OnInitDialog()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();

	CDialogEx::OnInitDialog();
	CAccessData access;
	CTools tools;
	int nHang = 0;
	CString strData;
	CString strlist[10];
	int nNumb = 0;

	if (access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("Config"), _T("MessageData"), m_stWhere, &strData, nHang))
	{
		tools.Split(strData, _T("☆"), strlist, nNumb);
		FileName1.SetWindowTextW(strlist[0]);
		m_sfilename = strlist[0];
	}
	else
	{
		AfxMessageBox(_T("获取数据失败!"));
	}

	m_editNodeNum.SetLimitText(3);
	editStartMAC.SetLimitText(12);
	editTotalNodeNum.SetLimitText(4);
	m_editNodeNum.SetWindowTextW(_T("32"));
    editStartMAC.SetWindowTextW(_T("1"));
    editTotalNodeNum.SetWindowTextW(_T("1016"));
	

	return TRUE;  // return TRUE unless you set the focus to a control
}


void DialogSyncNodeFile::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void DialogSyncNodeFile::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (FileName1.GetWindowTextLengthW() == 0)
	{
		AfxMessageBox(_T("请选择档案文件"));
		return;
	}
	CString strlistName[2] = { _T("ConfigName"), _T("MessageData") };
	CString strFile;
	CAccessData access;
	FileName1.GetWindowTextW(strFile);
	m_sfilename = strFile;
	CString strlistData = strFile + _T("☆");
	CString strSet = _T("MessageData='") + strlistData + _T("'");

	if (!access.UpdataFromTable(pMain->m_PeiZhi_db, _T("Config"), strSet, m_stWhere))
	{
		AfxMessageBox(_T("数据保存失败!"));
		return;
	}

	CString strNodenum = _T("");
	CString strtmp = _T("");

	m_NodeNum = 100;//per frame;
	
	m_editNodeNum.GetWindowText(strNodenum);
	m_NodeNum = _ttol(strNodenum);

	editTotalNodeNum.GetWindowText(strtmp);
	m_TotalNum = _ttol(strtmp);

	if (m_SyncMdoe == e_SyncAuto)
	{
		editStartMAC.GetWindowText(strtmp);
		m_StartMAC = _ttoi64 (strtmp);
	}

	CDialogEx::OnOK();
}


void DialogSyncNodeFile::FileNameIndexChange()
{
	SYSTEMTIME st;
	CString date = _T("");

	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CAccessData access;
	CTools tools;
	int nHang = 0;
	CString strData;
	CString strlist[10];
	int nNumb = 0;

	if (access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("Config"), _T("MessageData"), m_stWhere, &strData, nHang))
	{
		tools.Split(strData, _T("☆"), strlist, nNumb);
		m_sfilename = strlist[0];
	}
	else
	{
		AfxMessageBox(_T("获取数据失败!"));
		return;
	}

	GetLocalTime(&st);
	date.Format(_T("_%.2d%.2d_%.2d%.2d%.2d"), st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	m_sfilename.Insert(m_sfilename.GetLength() - 4, date);
}

void DialogSyncNodeFile::SaveInfo(CString strTopLine)
{

	char szANSIString[5000];
	CTools m_tools;
	char * pFileName = new char[256];

	USES_CONVERSION;
	pFileName = T2A(m_sfilename.GetBuffer(0));

	m_tools.AutoMakedir(pFileName);


	m_fp = fopen(pFileName, "a+");

	if (m_fp != NULL)
	{
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, strTopLine, -1, szANSIString, sizeof(szANSIString), NULL, NULL);
		fwrite(szANSIString, wcslen(strTopLine), 1, m_fp);
		fclose(m_fp);
	}

}

void DialogSyncNodeFile::SetFileName(CString str)
{
	m_sfilename = str;
}

void DialogSyncNodeFile::ReadFileLine()
{
	char str[256];
	CString cstr;


	int len = WideCharToMultiByte(CP_ACP, 0, m_sfilename, m_sfilename.GetLength(), NULL, 0, NULL, NULL);
	char * pFileName = new char[256];
	WideCharToMultiByte(CP_ACP, 0, m_sfilename, m_sfilename.GetLength(), pFileName, len, NULL, NULL);

	pFileName[len] = '\0';



	m_fp = fopen(pFileName, "r");

	if (m_fp != NULL)
	{

		while (!feof(m_fp))
		{
			fgets(str, 256, m_fp);
			if (str[0] != '\r'){
				cstr = str;
				m_fileline.push_back(cstr);
				//AfxMessageBox(cstr);
			}
		}

		fclose(m_fp);
	}
	else
	{

		AfxMessageBox(_T("文件不存在！"));
	}
	/*for (auto i : m_fileline)
	TRACE("\n%s",i);*/
}


void DialogSyncNodeFile::SplitLine(CString cmdline, CString token)
{

	int cmdargnum = 0;
	CString cstr;
	int index = 0;

	cstr = cmdline + token;
	while (TRUE)
	{
		index = cstr.Find(token);
		if (index == -1)
		{
			break;
		}
		m_linearg[cmdargnum++] = cstr.Left(index);
		cstr = cstr.Right(cstr.GetLength() - index - 1);
	}

}


void DialogSyncNodeFile::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
	m_SyncMdoe = e_SyncFile;

}


void DialogSyncNodeFile::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
	m_SyncMdoe= e_SyncAuto;
}


void DialogSyncNodeFile::OnBnClickedRadio1()
{
	m_ClearFirst = 1;
	// TODO: Add your control notification handler code here
}
