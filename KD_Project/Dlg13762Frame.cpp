// Dlg13762Frame.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "Dlg13762Frame.h"
#include "afxdialogex.h"


// CDlg13762Frame 对话框

IMPLEMENT_DYNAMIC(CDlg13762Frame, CDialogEx)

CDlg13762Frame::CDlg13762Frame(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg13762Frame::IDD, pParent)
{

}

CDlg13762Frame::~CDlg13762Frame()
{
}

void CDlg13762Frame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_C1, m_combC1);
	DDX_Control(pDX, IDC_COMBO_C2, m_combC2);
	DDX_Control(pDX, IDC_COMBO_C3, m_combC3);
	DDX_Control(pDX, IDC_COMBO_M1, m_combM1);
	DDX_Control(pDX, IDC_COMBO_M2, m_combM2);
	DDX_Control(pDX, IDC_COMBO_M3, m_combM3);
	DDX_Control(pDX, IDC_COMBO_M4, m_combM4);
	DDX_Control(pDX, IDC_COMBO_M5, m_combM5);
	DDX_Control(pDX, IDC_COMBO_M6, m_combM6);
	DDX_Control(pDX, IDC_COMBO_M9, m_combM9);
	DDX_Control(pDX, IDC_COMBOM_7, m_combM7);
	DDX_Control(pDX, IDC_COMBOM_8, m_combM8);
	DDX_Control(pDX, IDC_EDIT_A1, m_editA1);
	DDX_Control(pDX, IDC_EDIT_A2, m_editA2);
	DDX_Control(pDX, IDC_EDIT_A3, m_editA3);
	DDX_Control(pDX, IDC_EDIT_FN, m_editFN);
	DDX_Control(pDX, IDC_EDIT_M1, m_editM1);
	DDX_Control(pDX, IDC_EDIT_M2, m_editM2);
	DDX_Control(pDX, IDC_EDITDATA, m_editData);
	DDX_Control(pDX, IDC_COMBO_AFN, m_combAFN);
}


BEGIN_MESSAGE_MAP(CDlg13762Frame, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlg13762Frame 消息处理程序


BOOL CDlg13762Frame::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpDataData();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlg13762Frame::UpDataData()
{
	m_combC1.AddString(_T("0:下行"));
	m_combC1.AddString(_T("1:上行"));
	m_combC1.SetCurSel(0);

	m_combC2.AddString(_T("0:从动"));
	m_combC2.AddString(_T("1:启动"));
	m_combC2.SetCurSel(1);

	m_combC3.AddString(_T("1:集中式路由载波"));
	m_combC3.AddString(_T("2:分布式路由载波"));
	m_combC3.AddString(_T("3:宽带载波"));
	m_combC3.AddString(_T("10:微功率无线"));
	m_combC3.AddString(_T("20:以太网"));
	m_combC3.SetCurSel(2);

	m_combM1.AddString(_T("0:有"));
	m_combM1.AddString(_T("1:无"));
	m_combM1.SetCurSel(0);

	m_combM2.AddString(_T("0:有"));
	m_combM2.AddString(_T("1:无"));
	m_combM2.SetCurSel(0);

	m_combM3.AddString(_T("0:主"));
	m_combM3.AddString(_T("1:从"));
	m_combM3.SetCurSel(0);

	m_combM4.AddString(_T("0:无"));
	m_combM4.AddString(_T("1:有"));
	m_combM4.SetCurSel(0);

	m_combM5.AddString(_T("0:无"));
	m_combM5.AddString(_T("1:"));
	m_combM5.AddString(_T("2:"));
	m_combM5.AddString(_T("3:"));
	m_combM5.AddString(_T("4:"));
	m_combM5.AddString(_T("5:"));
	m_combM5.AddString(_T("6:"));
	m_combM5.AddString(_T("7:"));
	m_combM5.AddString(_T("8:"));
	m_combM5.AddString(_T("9:"));
	m_combM5.AddString(_T("10:"));
	m_combM5.AddString(_T("11:"));
	m_combM5.AddString(_T("12:"));
	m_combM5.AddString(_T("13:"));
	m_combM5.AddString(_T("14:"));
	m_combM5.AddString(_T("15:"));
	m_combM5.SetCurSel(0);

	m_combM6.AddString(_T("0:无"));
	m_combM6.AddString(_T("1:"));
	m_combM6.AddString(_T("2:"));
	m_combM6.AddString(_T("3:"));
	m_combM6.AddString(_T("4:"));
	m_combM6.AddString(_T("5:"));
	m_combM6.AddString(_T("6:"));
	m_combM6.AddString(_T("7:"));
	m_combM6.AddString(_T("8:"));
	m_combM6.AddString(_T("9:"));
	m_combM6.AddString(_T("10:"));
	m_combM6.AddString(_T("11:"));
	m_combM6.AddString(_T("12:"));
	m_combM6.AddString(_T("13:"));
	m_combM6.AddString(_T("14:"));
	m_combM6.AddString(_T("15:"));
	m_combM6.SetCurSel(0);

	m_combM7.AddString(_T("0:无"));
	m_combM7.AddString(_T("1:RS"));
	m_combM7.SetCurSel(0);

	m_editM1.SetWindowTextW(_T("0"));
	
	m_combM8.AddString(_T("0:默认"));
	m_combM8.SetCurSel(0);

	m_combM9.AddString(_T("0:bit/s"));
	m_combM9.AddString(_T("1:kbit/s"));
	m_combM9.SetCurSel(0);

	m_editM2.SetWindowTextW(_T("0"));

	m_editA1.SetWindowTextW(_T("BEBEBEBEBE01"));
	m_editA1.SetLimitText(12);
	m_editA3.SetWindowTextW(_T("0F0E0D0C0B0A "));
	m_editA3.SetLimitText(12);
	m_editData.SetWindowTextW(_T(""));

	m_combAFN.AddString(_T("00:确认否认"));
	m_combAFN.AddString(_T("01:初始化"));
	m_combAFN.AddString(_T("02:数据转发"));
	m_combAFN.AddString(_T("03:查询数据"));
	m_combAFN.AddString(_T("04:链路接口检测"));
	m_combAFN.AddString(_T("05:控制命令"));
	m_combAFN.AddString(_T("06:主动上报"));
	m_combAFN.AddString(_T("10:路由查询"));
	m_combAFN.AddString(_T("11:路由设置"));
	m_combAFN.AddString(_T("12:路由控制"));
	m_combAFN.AddString(_T("13:路由数据转发"));
	m_combAFN.AddString(_T("14:路由数据抄读"));
	m_combAFN.AddString(_T("15:文件传输"));
	m_combAFN.AddString(_T("F0:扩展命令"));
	m_combAFN.SetCurSel(3);

	m_editFN.SetWindowTextW(_T("F4"));
}


void CDlg13762Frame::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect); 
	if (rect.right == 0 || rect.bottom == 0 )
	{
		return;
	}
	KongjianSize(IDC_STATIC1,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC2,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC3,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC4,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC5,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC6,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC7,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC8,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC9,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC10,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC11,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC12,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC13,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC14,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC15,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC16,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC17,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC18,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC19,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC20,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC21,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC22,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC23,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC24,rect.right,rect.bottom); 

	KongjianSize(IDC_COMBO_C1,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_C2,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_C3,rect.right,rect.bottom); 

	KongjianSize(IDC_COMBO_M1,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_M2,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_M3,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_M4,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_M5,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_M6,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBOM_7,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBOM_8,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_M9,rect.right,rect.bottom); 
	KongjianSize(IDC_EDIT_M1,rect.right,rect.bottom); 
	KongjianSize(IDC_EDIT_M2,rect.right,rect.bottom); 

	KongjianSize(IDC_EDIT_A1,rect.right,rect.bottom); 
	KongjianSize(IDC_EDIT_A2,rect.right,rect.bottom); 
	KongjianSize(IDC_EDIT_A3,rect.right,rect.bottom); 

	KongjianSize(IDC_COMBO_AFN,rect.right,rect.bottom); 
	KongjianSize(IDC_EDIT_FN,rect.right,rect.bottom); 
	KongjianSize(IDC_EDITDATA,rect.right,rect.bottom); 

	GetClientRect(m_cRect);
	// TODO: 在此处添加消息处理程序代码
}
void CDlg13762Frame::KongjianSize(int nID, int cx, int cy, bool bComb)
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
		fcx=m_cRect.right;
		fcy=m_cRect.bottom;
		rect.left=(int)(rect.left*((float)cx/(float)fcx));//调整控件大小 
		rect.right=(int)(rect.right*((float)cx/(float)fcx)); 
		rect.top=(int)(rect.top*((float)cy/(float)fcy)); 
		rect.bottom = (int)(rect.bottom*((float)cy/(float)fcy)) + nBottom;
		pWnd->MoveWindow(rect);//设置控件位置 
	}
}