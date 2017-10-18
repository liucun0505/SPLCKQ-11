// DlgCCOTPchange.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DlgCCOTPchange.h"
#include "afxdialogex.h"
#include "Tools.h"
#include "AccessData.h"
#include "MainFrm.h"

// CDlgCCOTPchange 对话框

IMPLEMENT_DYNAMIC(CDlgCCOTPchange, CDialogEx)

CDlgCCOTPchange::CDlgCCOTPchange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCCOTPchange::IDD, pParent)
{

}

CDlgCCOTPchange::~CDlgCCOTPchange()
{
}

void CDlgCCOTPchange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DATA, m_editData);
}


BEGIN_MESSAGE_MAP(CDlgCCOTPchange, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgCCOTPchange::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCCOTPchange 消息处理程序


void CDlgCCOTPchange::OnBnClickedOk()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strData;
	CAccessData accessdata;
	CString strTEI , strMAC ,strPTEI , strLayer , strQos , strRole , strStatus , strBY;
	CTools tools;
	CString strlistName[8] = {_T("TP_MAC") ,_T("TP_TEI") ,_T("TP_PTEI") ,_T("TP_ROLE") ,_T("TP_TIER") ,_T("TP_QOS") ,_T("TP_STATUS") ,_T("TP_BY") };
	CString strlistData[8];
	CString strAllTPdata = _T("01000F0E0D0C0B0A000001000000020000000000");
	//accessdata.DelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("CCOTPShow"),_T(""));
	accessdata.DelectDataFromTable(pMain->m_PeiZhi_db,_T("CCOTPShow"),_T(""));
	m_editData.GetWindowTextW(strData);
	strData = strAllTPdata + strData;
	int nNumb = strData.GetLength()/40;
	for(int n = 0 ; n < nNumb ; n++)
	{
		if (wcslen(strData) < 40)
		{
			break;
		}
		if (strData.Mid(0 , 20) == "00000000000000000000")
		{
			break;
		}
		strTEI = strData.Mid(0 , 4);
		strlistData[1] = tools._str16tostr10(tools._strDaoxu(strTEI));
		strMAC = strData.Mid(4 , 12);
		strlistData[0] = tools._strDaoxu(strMAC);
		strPTEI = strData.Mid(16 , 4);
		strlistData[2] = tools._str16tostr10(tools._strDaoxu(strPTEI));
		strLayer = strData.Mid(20 , 4);
		strlistData[4] = tools._str16tostr10(tools._strDaoxu(strLayer));
		strQos = strData.Mid(24 , 4);
		strlistData[5] = tools._str16tostr10(tools._strDaoxu(strQos));
		strRole = strData.Mid(28 , 4);
		strlistData[3] = tools._str16tostr10(tools._strDaoxu(strRole));
		strStatus = strData.Mid(32 , 2);
		strlistData[6] = tools._str16tostr10(strStatus);
		strBY = strData.Mid(34 , 6);
		strlistData[7] = tools._strDaoxu(strBY);
		//accessdata.AddDataToTable(_T(".\\配置文件\\13762Data.accdb"),_T("CCOTPShow"),strlistName , strlistData ,8);
		accessdata.AddDataToTable(pMain->m_PeiZhi_db,_T("CCOTPShow"),strlistName , strlistData ,8);
		strData = strData.Mid(40);
	}
	AfxMessageBox(_T("完成！右键点击“测试导入拓扑图”"));
	CDialogEx::OnOK();
}
