// DlgAddress.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DlgAddress.h"
#include "afxdialogex.h"
#include "MainFrm.h"

CString gstrMSGZONE = _T("");


// CDlgAddress 对话框

IMPLEMENT_DYNAMIC(CDlgAddress, CDialogEx)

CDlgAddress::CDlgAddress(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAddress::IDD, pParent)
{

}

CDlgAddress::~CDlgAddress()
{
}

void CDlgAddress::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ADDR1, m_editAddr1);
	DDX_Control(pDX, IDC_EDIT_ADDR2, m_editAddr2);
	DDX_Control(pDX, IDC_EDIT_ADDR3, m_editAddr3);
	DDX_Control(pDX, IDC_LIST_ADDR2, m_listAddr2);
	DDX_Control(pDX, IDC_COMBO1, m_comb1);
	DDX_Control(pDX, IDC_COMBO2, m_comb2);
	DDX_Control(pDX, IDC_COMBO3, m_comb3);
	DDX_Control(pDX, IDC_COMBO4, m_comb4);
	DDX_Control(pDX, IDC_COMBO5, m_comb5);
	DDX_Control(pDX, IDC_COMBO6, m_comb6);
	DDX_Control(pDX, IDC_COMBO7, m_comb7);
	DDX_Control(pDX, IDC_COMBO8, m_comb8);
	DDX_Control(pDX, IDC_COMBO9, m_comb9);
	DDX_Control(pDX, IDC_EDIT_NUMB, m_editNumb);
	DDX_Control(pDX, IDC_EDIT_XNUMB, m_editXNumb);
}


BEGIN_MESSAGE_MAP(CDlgAddress, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgAddress::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DLE, &CDlgAddress::OnBnClickedButtonDle)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CDlgAddress::OnCbnSelchangeCombo5)
//	ON_LBN_SELCANCEL(IDC_LIST_ADDR2, &CDlgAddress::OnLbnSelcancelListAddr2)
//	ON_LBN_KILLFOCUS(IDC_LIST_ADDR2, &CDlgAddress::OnLbnKillfocusListAddr2)
ON_BN_CLICKED(IDOK, &CDlgAddress::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgAddress 消息处理程序



BOOL CDlgAddress::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdataDlg();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CDlgAddress::UpdataDlg()
{
	/////////////////南网隐藏控件
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strtmp;
	if(pMain->NW_OR_GW==1)
	{
	GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC11)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC12)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC14)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC16)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_COMBO1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_COMBO9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_NUMB)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_XNUMB)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_ADDR2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_ADD)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_DLE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LIST_ADDR2)->ShowWindow(SW_HIDE);

	CRect rect , frect;   //获取控件变化前大小 
	GetClientRect(frect); 
	GetDlgItem(IDC_EDIT_ADDR3)->GetWindowRect(&rect); 
	ScreenToClient(&rect);
	rect.MoveToY(150);
	rect.MoveToX(590);
	GetDlgItem(IDC_EDIT_ADDR3)->MoveWindow(rect);//设置控件位置 
	GetDlgItem(IDC_STATIC15)->GetWindowRect(&rect); 
	ScreenToClient(&rect);
	rect.MoveToY(150);
	rect.MoveToX(500);
	GetDlgItem(IDC_STATIC15)->MoveWindow(rect);//设置控件位置

	}
	////////////////////////////


	m_editAddr1.SetLimitText(12);
	m_editAddr2.SetLimitText(12);
	m_editAddr3.SetLimitText(12);

	m_comb1.AddString(_T("0:带路由或路由模式"));
	m_comb1.AddString(_T("1:不带路由或旁路模式"));
	m_comb1.SetCurSel(0);

	m_comb2.AddString(_T("0:无附加节点"));
	m_comb2.AddString(_T("1:有附加节点"));
	m_comb2.SetCurSel(0);

	m_comb3.AddString(_T("0:对主节点操作"));
	m_comb3.AddString(_T("1:对从节点操作"));
	m_comb3.SetCurSel(0);

	m_comb4.AddString(_T("0:不进行冲突检测"));
	m_comb4.AddString(_T("1:进行冲突检测"));
	m_comb4.SetCurSel(0);

	m_comb5.AddString(_T("0:无中继"));
	m_comb5.AddString(_T("1"));
	m_comb5.AddString(_T("2"));
	m_comb5.AddString(_T("3"));
	m_comb5.AddString(_T("4"));
	m_comb5.AddString(_T("5"));
	m_comb5.AddString(_T("6"));
	m_comb5.AddString(_T("7"));
	m_comb5.AddString(_T("8"));
	m_comb5.AddString(_T("9"));
	m_comb5.AddString(_T("10"));
	m_comb5.AddString(_T("11"));
	m_comb5.AddString(_T("12"));
	m_comb5.AddString(_T("13"));
	m_comb5.AddString(_T("14"));
	m_comb5.AddString(_T("15"));
	m_comb5.SetCurSel(0);

	m_comb6.AddString(_T("0:不分信道"));
	m_comb6.AddString(_T("1信道"));
	m_comb6.AddString(_T("2信道"));
	m_comb6.AddString(_T("3信道"));
	m_comb6.AddString(_T("4信道"));
	m_comb6.AddString(_T("5信道"));
	m_comb6.AddString(_T("6信道"));
	m_comb6.AddString(_T("7信道"));
	m_comb6.AddString(_T("8信道"));
	m_comb6.AddString(_T("9信道"));
	m_comb6.AddString(_T("10信道"));
	m_comb6.AddString(_T("11信道"));
	m_comb6.AddString(_T("12信道"));
	m_comb6.AddString(_T("13信道"));
	m_comb6.AddString(_T("14信道"));
	m_comb6.AddString(_T("15信道"));
	m_comb6.SetCurSel(0);

	m_comb7.AddString(_T("0:未编码"));
	m_comb7.AddString(_T("1:RS编码"));
	m_comb7.SetCurSel(0);

	m_comb8.AddString(_T("1200"));
	m_comb8.AddString(_T("2400"));
	m_comb8.AddString(_T("4800"));
	m_comb8.AddString(_T("7200"));
	m_comb8.AddString(_T("9600"));
	m_comb8.SetCurSel(0);

	m_comb9.AddString(_T("0:bit/s"));
	m_comb9.AddString(_T("1:kbit/s"));
	m_comb9.SetCurSel(0);

	if (gstrMSGZONE.GetLength() <= 12){
		m_editAddr1.SetWindowText(_T("111111111111"));
		m_editAddr3.SetWindowText(_T("000000000000"));
	}
	else
	{
		strtmp = m_tool._strDaoxu(gstrMSGZONE.Mid(12, 12));
		m_editAddr1.SetWindowText(strtmp);

		strtmp = m_tool._strDaoxu(gstrMSGZONE.Right(12));
		m_editAddr3.SetWindowText(strtmp);
	}
	m_editNumb.SetWindowText(_T("0"));
	m_editXNumb.SetWindowText(_T("0"));
}
void CDlgAddress::OnBnClickedButtonAdd()
{
	if (m_listAddr2.GetCount()<m_comb5.GetCurSel())
	{
		CString strAddr2;
		m_editAddr2.GetWindowText(strAddr2);
		m_listAddr2.AddString(m_tool.BeforeAddO(strAddr2,12));
	}
	
}


void CDlgAddress::OnBnClickedButtonDle()
{
	m_listAddr2.DeleteString(m_listAddr2.GetCaretIndex());
}


void CDlgAddress::OnCbnSelchangeCombo5()
{
	int nNumb = m_listAddr2.GetCount();
	for(int n = 0 ; n < nNumb ; n++)
	{
		m_listAddr2.DeleteString(0);
	}
}
void CDlgAddress::OnBnClickedOk()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();

	if (m_listAddr2.GetCount() != m_comb5.GetCurSel())
	{
		AfxMessageBox(_T("中继级别与中继地址输入不匹配,请重新输入"));
		return;
	}
	INT8U bufMessageR[6];
	INT8U temp1 = 0, temp2 = 0 , temp3 = 0 , temp4 = 0 , temp5 = 0 , temp6 = 0 , temp7 = 0 ,  temp9 = 0;
	INT16U tempBaud = 0;
	CString strBaud , strRecvBitNumb , strXNumb;
	temp1 = m_comb1.GetCurSel();
	temp2 = m_comb2.GetCurSel();
	temp3 = m_comb3.GetCurSel();
	temp4 = m_comb4.GetCurSel();
	temp5 = m_comb5.GetCurSel();
	temp6 = m_comb6.GetCurSel();
	temp7 = m_comb7.GetCurSel();
	m_comb8.GetWindowText(strBaud);
	tempBaud = _ttoi(strBaud);
	temp9 = m_comb9.GetCurSel();
	tempBaud = (temp9<<15) | tempBaud ;
	m_editNumb.GetWindowText(strRecvBitNumb);
	m_editXNumb.GetWindowText(strXNumb);

	bufMessageR[0] = (temp5<<4) | (temp4<<3) | (temp3<<2) | (temp2<<1) | temp1; 
	bufMessageR[1] = (temp7<<4) | temp6;
	bufMessageR[2] = _ttoi(strRecvBitNumb);
	bufMessageR[3] = (INT8U)tempBaud;
	bufMessageR[4] = (INT8U)(tempBaud >> 8);
	bufMessageR[5] = _ttoi(strXNumb);

	CString strAddrAll , strAddr;
	strAddrAll = m_tool._buf16tostr16(bufMessageR,6);
	if(pMain->NW_OR_GW==0)
	{
		if(temp3 == 1)
		{
			m_editAddr1.GetWindowText(strAddr);
			strAddrAll += m_tool._strDaoxu(m_tool.BeforeAddO(strAddr,12));
			for (int n = 0 ; n < m_listAddr2.GetCount() ; n++)
			{
				m_listAddr2.GetText(n,strAddr);
				strAddrAll += m_tool._strDaoxu(m_tool.BeforeAddO(strAddr,12));
			}
			m_editAddr3.GetWindowText(strAddr);
			strAddrAll += m_tool._strDaoxu(m_tool.BeforeAddO(strAddr,12));
		}
			
	}
	if(pMain->NW_OR_GW==1)
	{
			m_editAddr1.GetWindowText(strAddr);
			strAddrAll = m_tool._strDaoxu(m_tool.BeforeAddO(strAddr,12));
			for (int n = 0 ; n < m_listAddr2.GetCount() ; n++)
			{
				m_listAddr2.GetText(n,strAddr);
				strAddrAll += m_tool._strDaoxu(m_tool.BeforeAddO(strAddr,12));
			}
			m_editAddr3.GetWindowText(strAddr);
			strAddrAll += m_tool._strDaoxu(m_tool.BeforeAddO(strAddr,12));			
	}
	m_strMsgAndAddr = strAddrAll;
	gstrMSGZONE=m_strMsgAndAddr;
	CDialogEx::OnOK();
}
