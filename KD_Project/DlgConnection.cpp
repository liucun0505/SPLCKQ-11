// DlgConnection.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DlgConnection.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CDlgConnection 对话框

IMPLEMENT_DYNAMIC(CDlgConnection, CDialogEx)

CDlgConnection::CDlgConnection(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgConnection::IDD, pParent)
	, m_nRadioType(0)
{
	m_nRadioType = 0;
}

CDlgConnection::~CDlgConnection()
{
}

void CDlgConnection::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMMPORT, m_combCommPort);
	DDX_Radio(pDX, IDC_RADIO1, m_nRadioType);
	DDX_Control(pDX, IDC_COMBO_COMMBAUD, m_combBaud);
	DDX_Control(pDX, IDC_COMBO_COMMDABABIE, m_combDataBit);
	DDX_Control(pDX, IDC_COMBO_COMMPARITY, m_combParity);
	DDX_Control(pDX, IDC_COMBO_COMMSTOPBIT, m_combStopBit);
	DDX_Control(pDX, IDC_COMBO_MAC, m_combMAC);
	DDX_Control(pDX, IDC_COMBO_NWGW, m_NWGW);
}


BEGIN_MESSAGE_MAP(CDlgConnection, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgConnection::OnBnClickedOk)
//	ON_CBN_SELCHANGE(IDC_COMBO_COMMPORT, &CDlgConnection::OnCbnSelchangeComboCommport)
END_MESSAGE_MAP()


// CDlgConnection 消息处理程序



void CDlgConnection::OnBnClickedOk()
{
	
    CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	if(m_NWGW.GetCurSel()==0)
	{
	    pMain->NW_OR_GW=0;
		pMain->m_PeiZhi=".\\配置文件\\13762树控件.ini";
		pMain->m_PeiZhi_db=".\\配置文件\\13762Data.accdb";
	}
	if(m_NWGW.GetCurSel()==1)
	{
		pMain->NW_OR_GW=1;
		pMain->m_PeiZhi=".\\配置文件\\13762树控件NW.ini";
		pMain->m_PeiZhi_db=".\\配置文件\\13762DataNW.accdb";
	}

	m_combMAC.GetWindowText(m_strMainMAC);
	if (m_strMainMAC == "")
	{
		AfxMessageBox(_T("请选择抄控器MAC地址"));
		return ;
	}
	CString strBaud , strDatabit;
	m_combCommPort.GetWindowText(m_strCommPort);
	m_combBaud.GetWindowText(m_strCommBaud);
	strBaud.Format(_T("%d"),m_combBaud.GetCurSel());
	m_strCommParity.Format(_T("%d"),m_combParity.GetCurSel());
	m_combDataBit.GetWindowText(m_strCommDatabit);
	strDatabit.Format(_T("%d"),m_combDataBit.GetCurSel());
	m_strCommStopbit.Format(_T("%d"),m_combStopBit.GetCurSel());

	CString strlistData = m_strCommPort + _T("☆") + strBaud + _T("☆") + m_strCommParity + _T("☆")+ m_strCommStopbit + _T("☆") +strDatabit+ _T("☆") + m_strMainMAC + _T("☆");
	CString strSet = _T("MessageData='") + strlistData + _T("'");
	CString stWhere = _T("ConfigName='串口信息'");
	try
	{
		//if(!m_access.UpdataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("Config"),strSet , stWhere))
		if(!m_access.UpdataFromTable(pMain->m_PeiZhi_db,_T("Config"),strSet , stWhere))
		{
			AfxMessageBox(_T("数据保存失败!"));
			return;
		}
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("错误描述：%s\n错误消息%s"), 
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		AfxMessageBox(strMsg);
	}

	CDialogEx::OnOK();
}


BOOL CDlgConnection::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	// TODO:  在此添加额外的初始化
	AddPort();

	int nHang= 0;
	CString stWhere = _T("ConfigName='串口信息'");
	CString strData ,strPort;
	CString strlist[7];
	int nNumb = 0 ,n = 0;
	try
	{
		//if(m_access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
		if(m_access.SelectDataFromTable(pMain->m_PeiZhi_db,_T("Config"),_T("MessageData"),stWhere,&strData,nHang))
		{
			m_tools.Split(strData , _T("☆") , strlist , nNumb);
			m_combCommPort.SetWindowTextW(strlist[0]);
			m_combBaud.SetCurSel(_ttoi(strlist[1]));
			m_combParity.SetCurSel(_ttoi(strlist[2]));
			m_combStopBit.SetCurSel(_ttoi(strlist[3]));
			m_combDataBit.SetCurSel(_ttoi(strlist[4]));
			m_combMAC.SetWindowTextW(strlist[5]);
		}
	}
	catch (_com_error& e)
	{
		CString strMsg;
		strMsg.Format(_T("错误描述：%s\n错误消息%s"), 
			(LPCTSTR)e.Description(),
			(LPCTSTR)e.ErrorMessage());
		AfxMessageBox(strMsg);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CDlgConnection::AddPort()
{
	m_combMAC.AddString(_T("000000000001"));
	m_combMAC.AddString(_T("000000000002"));
	m_combMAC.AddString(_T("BEBEBEBEBE01"));
	m_combMAC.SetCurSel(2);

	m_combBaud.AddString(_T("1200"));
	m_combBaud.AddString(_T("2400"));
	m_combBaud.AddString(_T("4800"));
	m_combBaud.AddString(_T("9600"));
	m_combBaud.AddString(_T("14400"));
	m_combBaud.AddString(_T("19200"));
	m_combBaud.AddString(_T("38500"));
	m_combBaud.AddString(_T("56000"));
	m_combBaud.AddString(_T("57600"));
	m_combBaud.AddString(_T("115200"));
	m_combBaud.SetCurSel(3);
	m_combParity.AddString(_T("无校验"));
	m_combParity.AddString(_T("奇校验"));
	m_combParity.AddString(_T("偶校验"));
	m_combParity.SetCurSel(2);

	m_combDataBit.AddString(_T("5"));
	m_combDataBit.AddString(_T("6"));
	m_combDataBit.AddString(_T("7"));
	m_combDataBit.AddString(_T("8"));
	m_combDataBit.SetCurSel(3);

	m_combStopBit.AddString(_T("1"));
	m_combStopBit.AddString(_T("1.5"));
	m_combStopBit.AddString(_T("2"));
	m_combStopBit.SetCurSel(0);

	m_NWGW.AddString(_T("国网"));
	m_NWGW.AddString(_T("南网"));
	m_NWGW.SetCurSel(0);


	CString str = _T("");
	int n1 = 0,n2 = 0,n3 = 100;
	HKEY hKey;
	if( ::RegOpenKeyEx( HKEY_LOCAL_MACHINE,
		_T("Hardware\\DeviceMap\\SerialComm"),
		NULL,
		KEY_READ,
		&hKey) == ERROR_SUCCESS) // 打开串口注册表
	{
		int i=0,j = 0;;
		TCHAR portName[256],commName[256];
		DWORD dwLong,dwSize;
		while(1)
		{
			dwLong = dwSize = sizeof(portName);
			if( ::RegEnumValue( hKey,
				i,
				portName,
				&dwLong,
				NULL,
				NULL,
				(PUCHAR)commName,
				&dwSize ) == ERROR_NO_MORE_ITEMS ) // 枚举串口
				break;
			n1=0;
			n2=0;
			n3=100;
			if (i == 0)
			{
				m_combCommPort.AddString( commName ); 
			}
			else
			{
				str = commName;
				n1= _ttoi(str.Mid(3));
				for(j=0;j<m_combCommPort.GetCount();j++)
				{
					m_combCommPort.GetLBText(j,str);
					n2= _ttoi(str.Mid(3));
					if (j+1 < m_combCommPort.GetCount())
					{
						m_combCommPort.GetLBText(j+1,str);
						n3= _ttoi(str.Mid(3));
						if (n1<n2)
						{
							m_combCommPort.InsertString(j,commName);
							break;
						}
						if (n1>n2&&n1<n3)
						{
							m_combCommPort.InsertString(j+1,commName);
							break;
						}
					}
					else
					{
						m_combCommPort.AddString( commName ); 
						break;
					}

				}
			}
			i++;
		}
		if( m_combCommPort.GetCount() == 0 )
		{
			::AfxMessageBox(_T("在HKEY_LOCAL_MACHINE:Hardware\\DeviceMap\\SerialComm里找不到串口!!!" ));
		}
		else
		{
			m_combCommPort.SetCurSel(0);
		}
		RegCloseKey(hKey);
	}

}
