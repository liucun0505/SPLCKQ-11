
// ImitateMeterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "ImitateMeterDlg.h"
#include "afxdialogex.h"
#include "DlgSetMeterData.h"
#include "DlgSetComm.h"
#include "DlgQuxian.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CImitateMeterDlg 对话框




CImitateMeterDlg::CImitateMeterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImitateMeterDlg::IDD, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bConnected = FALSE;
	m_BufRcvLen = 0;
}

void CImitateMeterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SHOWMESSAGE, m_editShowMessage);
	DDX_Control(pDX, IDC_EDIT_PORT, m_editPort);
	DDX_Control(pDX, IDC_EDIT_BAUD, m_editBaud);
	DDX_Control(pDX, IDC_EDIT_PARITY, m_editParity);
	DDX_Control(pDX, IDC_SET_COMM, m_btnOpenComm);
	DDX_Control(pDX, IDC_EDIT_SHOWZHEN, m_editShowZhen);
	DDX_Control(pDX, IDC_CHECK_JO, m_checkJOU);
	//  DDX_Control(pDX, IDC_CHECK_97, m_check97);
	//  DDX_Radio(pDX, IDC_RADIO_TYPE, m_nType);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_combType);
}

BEGIN_MESSAGE_MAP(CImitateMeterDlg, CDialogEx)
	ON_MESSAGE(WM_COMMNOTIFY, OnComm)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_SETMETER_DATA, &CImitateMeterDlg::OnBnClickedSetmeterData)
ON_BN_CLICKED(IDC_SET_COMM, &CImitateMeterDlg::OnBnClickedSetComm)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON_BEGIN, &CImitateMeterDlg::OnBnClickedButtonBegin)
ON_BN_CLICKED(IDC_BUTTON_END, &CImitateMeterDlg::OnBnClickedButtonEnd)
ON_BN_CLICKED(IDC_BTN_SETQUXIAN, &CImitateMeterDlg::OnBnClickedBtnSetquxian)
ON_WM_SIZE()
ON_BN_CLICKED(IDC_BUTTON1, &CImitateMeterDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CImitateMeterDlg 消息处理程序

BOOL CImitateMeterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if (!CreatEvent())
	{
		return -1;
	}
	ShowWindow(SW_SHOWMAXIMIZED);
	SetErrorMode(SEM_FAILCRITICALERRORS|SEM_NOGPFAULTERRORBOX);

	m_checkJOU.SetCheck(TRUE);
	char buf[20];
	CString strPort,strBaud,strParity,strDatasize,strStopByte;
	GetPrivateProfileString("COM","Port","",buf,sizeof(buf),".\\模拟表数据\\Config.ini");
	strPort.Format("%s",buf);
	GetPrivateProfileString("COM","Baud","",buf,sizeof(buf),".\\模拟表数据\\Config.ini");
	strBaud.Format("%s",buf);
	GetPrivateProfileString("COM","Parity","",buf,sizeof(buf),".\\模拟表数据\\Config.ini");
	strParity.Format("%s",buf);
	GetPrivateProfileString("COM","DataSize","",buf,sizeof(buf),".\\模拟表数据\\Config.ini");
	strDatasize.Format("%s",buf);
	GetPrivateProfileString("COM","StopByte","",buf,sizeof(buf),".\\模拟表数据\\Config.ini");
	strStopByte.Format("%s",buf);

	m_combType.AddString("645_1997");
	m_combType.AddString("645_2007");
	m_combType.AddString("645_188");
	m_combType.SetCurSel(2);
	if (OpenCOM(strPort,_ttoi(strBaud),_ttoi(strParity),_ttoi(strDatasize),_ttoi(strStopByte)))
	{
		switch(_ttoi(strParity))
		{
		case 0:
			strParity = "无校验";
			break;
		case 1:
			strParity = "奇校验";
			break;
		case 2:
			strParity = "偶校验";
			break;
		}
		m_editPort.SetWindowTextA(strPort);
		m_editBaud.SetWindowTextA(strBaud);
		m_editParity.SetWindowTextA(strParity);
		m_btnOpenComm.SetWindowTextA("关闭串口");
	}
	else
	{
		MessageBox("");
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImitateMeterDlg::KongjianSize(int nID, int cx, int cy , bool bComb)
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

BOOL CImitateMeterDlg::CreatEvent()
{
	if((m_hPostMsgEvent=CreateEvent(NULL, TRUE, TRUE, NULL))==NULL)
		return FALSE;

	memset(&m_osRead, 0, sizeof(OVERLAPPED));
	memset(&m_osWrite, 0, sizeof(OVERLAPPED));

	// 为重叠读创建事件对象，手工重置，初始化为无信号的
	if((m_osRead.hEvent=CreateEvent(NULL, TRUE, FALSE, NULL))==NULL)
		return FALSE;

	// 为重叠写创建事件对象，手工重置，初始化为无信号的
	if((m_osWrite.hEvent=CreateEvent(NULL, TRUE, FALSE, NULL))==NULL)
		return FALSE;
	return TRUE;
}
void CImitateMeterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImitateMeterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CImitateMeterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CImitateMeterDlg::OnBnClickedSetmeterData()
{
	CDlgSetMeterData setMeterdlg;
	setMeterdlg.DoModal();
}


void CImitateMeterDlg::OnBnClickedSetComm()
{
	CString strBtnName;
	m_btnOpenComm.GetWindowTextA(strBtnName);
	if (strBtnName == "打开串口")
	{
		CDlgSetComm setCommdlg;
		if(setCommdlg.DoModal()==IDOK)
		{
			if (OpenCOM(setCommdlg.m_strPort,setCommdlg.m_nBaud,setCommdlg.m_nParity,setCommdlg.m_nDataSize,setCommdlg.m_nStopByte))
			{
				m_editPort.SetWindowTextA(setCommdlg.m_strPort);
				m_editBaud.SetWindowTextA(setCommdlg.m_strBaud);
				m_editParity.SetWindowTextA(setCommdlg.m_strParity);
				m_btnOpenComm.SetWindowTextA("关闭串口");
			}
		}
		
	} 
	else
	{
		if(!m_bConnected)
			return;

		m_bConnected=FALSE;
		SetEvent(m_hPostMsgEvent); 
		SetCommMask(hCom, 0); 
		WaitForSingleObject(m_pThread->m_hThread, INFINITE);
		m_pThread=NULL;
		CloseHandle(hCom);
		m_editPort.SetWindowTextA("");
		m_editBaud.SetWindowTextA("");
		m_editParity.SetWindowTextA("");
		m_btnOpenComm.SetWindowTextA("打开串口");
		for(int n = 0; n < m_BufRcvLen ; n++ )
		{
			m_BufRcv[n] = 0x00;
		}
		m_BufRcvLen = 0;
	}

}

UINT CommProc(LPVOID pParam)
{
	OVERLAPPED os;
	DWORD dwMask, dwTrans;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	CImitateMeterDlg* pDlag= (CImitateMeterDlg*)pParam;

	memset(&os, 0, sizeof(OVERLAPPED));
	os.hEvent=CreateEvent(NULL, TRUE, FALSE, NULL);

	if(os.hEvent==NULL)
	{
		AfxMessageBox(_T("无法创建事件对象!"));
		return (UINT)-1;
	}

	while(pDlag->m_bConnected)
	{
		ClearCommError(pDlag->hCom,&dwErrorFlags,&ComStat);

		if(ComStat.cbInQue)
		{
			// 无限等待WM_COMMNOTIFY消息被处理完
			WaitForSingleObject(pDlag->m_hPostMsgEvent, INFINITE);
			ResetEvent(pDlag->m_hPostMsgEvent);

			// 通知视图
			PostMessage(pDlag->m_hTermWnd, WM_COMMNOTIFY, EV_RXCHAR, 0);

			continue;
		}

		dwMask=0;

		if(!WaitCommEvent(pDlag->hCom, &dwMask, &os)) // 重叠操作
		{

			if(GetLastError()==ERROR_IO_PENDING)
				// 无限等待重叠操作结果
				GetOverlappedResult(pDlag->hCom, &os, &dwTrans, TRUE);
			else
			{
				CloseHandle(os.hEvent);
				return (UINT)-1;
			}
		}
	}
	CloseHandle(os.hEvent);
	return 0;
}
bool CImitateMeterDlg::OpenCOM(CString strPort , int nBaud , int nParity , int nByteSize, int nStopBit)
{
	DCB dcb;
	COMMTIMEOUTS TimeOuts;
	m_hTermWnd=this->GetSafeHwnd();
	if(m_bConnected)
	{
		return false;
	}
	if (strPort.GetLength()>4)
	{
		strPort = _T("\\\\.\\")+strPort;
	}

	hCom=CreateFile(strPort,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,NULL);
	SetupComm(hCom,MAXBLOCK,MAXBLOCK);
	SetCommMask(hCom, EV_RXCHAR);

	PurgeComm( hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR ); 

	//// 把间隔超时设为最大，把总超时设为0将导致ReadFile立即返回并完成操作
	TimeOuts.ReadIntervalTimeout=MAXDWORD; 
	TimeOuts.ReadTotalTimeoutMultiplier=0; 
	TimeOuts.ReadTotalTimeoutConstant=0; 

	///* 设置写超时以指定WriteComm成员函数中的GetOverlappedResult函数的等待时间*/
	TimeOuts.WriteTotalTimeoutMultiplier=50;
	TimeOuts.WriteTotalTimeoutConstant=2000;

	SetCommTimeouts(hCom, &TimeOuts);


	GetCommState(hCom,&dcb);
	dcb.BaudRate=nBaud;  //传输速率
	dcb.ByteSize=nByteSize;    //起始位
	dcb.Parity=nParity;  //奇偶性
	dcb.StopBits=nStopBit; //停止位
	CString strcom;
	if(SetCommState(hCom,&dcb))
	{
		m_pThread=AfxBeginThread(CommProc, this, THREAD_PRIORITY_NORMAL, 
			0, CREATE_SUSPENDED, NULL); // 创建并挂起线程

		if(m_pThread==NULL)
		{
			CloseHandle(hCom);
			return false;
		}
		else

		{
			m_bConnected=TRUE;
			m_pThread->ResumeThread(); // 恢复线程运行
		}
		return true;
	}
	return false;
}

void CImitateMeterDlg::ShowZhen(CString strData,CString strSF)
{
	CTime systime;
	CString strSysTime,strSysDate;
	systime = CTime::GetCurrentTime();
	strSysDate = systime.Format("%Y-%m-%d");
	strSysTime = systime.Format("%H:%M:%S")+"  "+strSF+":";
	strData = strSysTime+strData+"\r\n";
	int l=m_editShowZhen.GetWindowTextLength();
	m_editShowZhen.SetSel(l,l,FALSE);
	m_editShowZhen.SetFocus();
	m_editShowZhen.ReplaceSel(strData);
	if (l == m_editShowZhen.GetWindowTextLength())
	{
		m_editShowZhen.SetWindowText("");
		m_editShowZhen.ReplaceSel(strData);
	}
	CString szPath = ".\\模拟表数据\\数据帧\\"+strSysDate+".txt";
	FILE * file;
	file=fopen(szPath,_T("r"));
	if  ( file == NULL )
	{
		file=fopen(szPath,_T("a+"));
		fwrite(strData,strlen(strData),1,file);
		fclose(file);
	}
	else
	{
		fclose(file); 
		file=fopen(szPath,_T("a+"));
		fwrite(strData,strlen(strData),1,file);
		fclose(file);
	} 
}
void CImitateMeterDlg::ShowMessage(CString strData)
{

}
#include "CDTL645.h"
CDTL645   m_645;
LRESULT CImitateMeterDlg::OnComm(WPARAM wParam, LPARAM lParam)
{
	INT8U buf[1];
	CString str;
	int nLength;//, nTextLength;

	//	CEdit& edit=GetEditCtrl();

	if(!m_bConnected || (wParam & EV_RXCHAR)!=EV_RXCHAR) // 是否是EV_RXCHAR事件?
	{
		SetEvent(m_hPostMsgEvent); // 允许发送下一个WM_COMMNOTIFY消息
		return 0L;
	}

	nLength=ReadComm(buf,1);

	if(nLength)
	{      
		
		INT8U RcvDataLen = 0;
		INT8U RcvDataZLen = 0;
		INT8U RcvData[300];
		m_BufRcv[ m_BufRcvLen++] = buf[0];  //数据入队  

		if (m_BufRcvLen>200)
		{
			for(int n = 0; n < m_BufRcvLen ; n++ )
			{
				m_BufRcv[n] = 0x00;
			}
			m_BufRcvLen = 0;
		}

		if (m_combType.GetCurSel() == 0)//m_check97.GetCheck())
		{
			if (m_dtl2007.Decode1997(m_BufRcv,m_BufRcvLen,255,&RecvDtl1997,RcvData,RcvDataLen))
			{
				INT8U DIbuf[3];
				INT16U Di97;
				DIbuf[0] = (INT8U)RecvDtl1997.s_Di;
				DIbuf[1] = (INT8U)(RecvDtl1997.s_Di>>8);
				CString strDi = m_dtl2007._buf16tostr16(DIbuf,2);
				CString strSenddata,strPAddress;
				m_strYaddress = m_dtl2007._buf16tostr16(RecvDtl1997.s_AmtBuf,6,false,true);

				switch(RecvDtl1997.s_Con)
				{
				case 0x01:
					ShowZhen(m_dtl2007._buf16tostr16(m_BufRcv,m_BufRcvLen,true),"接收-读："+m_strYaddress+"  【【"+strDi+"】】");
					break;
				case 0x04:
					ShowZhen(m_dtl2007._buf16tostr16(m_BufRcv,m_BufRcvLen,true),"接收-写："+m_strYaddress+"  【【"+strDi+"】】");
					break;
				default:
					ShowZhen(m_dtl2007._buf16tostr16(m_BufRcv,m_BufRcvLen,true),"接收："+m_strYaddress+"  【【"+strDi+"】】");
					break;

				}
				RecvDtl1997.s_Di =  RecvDtl1997.s_Di>>8|RecvDtl1997.s_Di<<8;
				m_dtl2007.TranDi2007(RecvDtl1997.s_Di,RecvDtl2007.s_Di,RcvDataZLen);
				for (int n = 0 ; n <6;n++)
				{
					RecvDtl2007.s_AmtBuf[n] = RecvDtl1997.s_AmtBuf[n];
				}
				RecvDtl2007.s_Con = RecvDtl1997.s_Con+0x10;
				RecvDtl2007.s_97Con = RecvDtl1997.s_Con;
				RecvDtl2007.s_97Di = RecvDtl1997.s_Di;
				//if(RcvDataZLen!=RcvDataLen) return 0L;
				for(int n = 0; n < m_BufRcvLen ; n++ )
				{
					m_BufRcv[n] = 0x00;
				}
				m_BufRcvLen = 0;
				
				SendMeterData(RecvDtl2007,RcvData,RcvDataLen);


				/*switch(RecvDtl1997.s_Di)
				{
				case 0xB611:
				case 0xB612:
				case 0xB613:
				strSenddata = "010203";
				RecvDtl1997.s_Con+=0x80;
				break;
				case 0x901F:
				strSenddata = "01020304";
				RecvDtl1997.s_Con+=0x80;
				break;
				default:
				strSenddata = "";
				RecvDtl1997.s_Con+=0xC0;
				break;
				}
				INT8U BufRecv[100];
				INT8U BufRecvlen=0;
				INT8U BufDataRecv[100];
				INT8U BufDataRecvlen=0;
				m_dtl2007._str16tobuf16(strSenddata,BufDataRecv,BufDataRecvlen);
				m_dtl2007.CodeToWatchZuzhen1997(RecvDtl1997,BufDataRecv,BufDataRecvlen,255,BufRecv,BufRecvlen);
				DWORD nsize;
				WriteFile(hCom,BufRecv,BufRecvlen,&nsize,&m_osWrite);
				ShowZhen(m_dtl2007._buf16tostr16(BufRecv,BufRecvlen,true),"发送："+m_strYaddress+"  【【"+strDi+"】】");
				for(int n = 0; n < m_BufRcvLen ; n++ )
				{
				m_BufRcv[n] = 0x00;
				}
				m_BufRcvLen = 0;*/
			}
		} 
		else if (m_combType.GetCurSel() == 1)
		{
			if(m_dtl2007.Decode2007(m_BufRcv,m_BufRcvLen,255,&RecvDtl2007,RcvData,RcvDataLen))
			{
				INT8U DIbuf[5];
				DIbuf[3] = (INT8U)RecvDtl2007.s_Di;
				DIbuf[2] = (INT8U)(RecvDtl2007.s_Di>>8);
				DIbuf[1] = (INT8U)(RecvDtl2007.s_Di>>16);
				DIbuf[0] = (INT8U)(RecvDtl2007.s_Di>>24);
				CString strDi = m_dtl2007._buf16tostr16(DIbuf,4);
				m_strYaddress = m_dtl2007._buf16tostr16(RecvDtl2007.s_AmtBuf,6,false,true);
				switch(RecvDtl2007.s_Con)
				{
				case 0x11:
					ShowZhen(m_dtl2007._buf16tostr16(m_BufRcv,m_BufRcvLen,true),"接收-读："+m_strYaddress+"  【【"+strDi+"】】");
					break;
				case 0x08:
				case 0x14:
					ShowZhen(m_dtl2007._buf16tostr16(m_BufRcv,m_BufRcvLen,true),"接收-写："+m_strYaddress+"  【【"+strDi+"】】");
					break;
				default:
					ShowZhen(m_dtl2007._buf16tostr16(m_BufRcv,m_BufRcvLen,true),"接收："+m_strYaddress+"  【【"+strDi+"】】");
					break;

				}
				
				for(int n = 0; n < m_BufRcvLen ; n++ )
				{
					m_BufRcv[n] = 0x00;
				}
				m_BufRcvLen = 0;
				SendMeterData(RecvDtl2007,RcvData,RcvDataLen);
			}
		}
		else if(m_combType.GetCurSel() == 2)
		{
			if(m_dtl188.Decode188Data(m_BufRcv,m_BufRcvLen,255,&RecvDtl188,RcvData,RcvDataLen))
			{
				INT8U DIbuf[3];
				INT16U Di97;
				DIbuf[0] = (INT8U)RecvDtl188.s_Di;
				DIbuf[1] = (INT8U)(RecvDtl188.s_Di>>8);
				CString strDi = m_dtl2007._buf16tostr16(DIbuf,2);
				CString strSenddata,strPAddress;
				m_strYaddress = m_dtl2007._buf16tostr16(RecvDtl188.s_AmtBuf,7,false,true);
				switch(RecvDtl188.s_Con)
				{
				case 0x01:
					ShowZhen(m_dtl2007._buf16tostr16(m_BufRcv,m_BufRcvLen,true),"接收-读："+m_strYaddress+"  【【"+strDi+"】】");
					break;
				case 0x04:
					ShowZhen(m_dtl2007._buf16tostr16(m_BufRcv,m_BufRcvLen,true),"接收-写："+m_strYaddress+"  【【"+strDi+"】】");
					break;
				default:
					ShowZhen(m_dtl2007._buf16tostr16(m_BufRcv,m_BufRcvLen,true),"接收："+m_strYaddress+"  【【"+strDi+"】】");
					break;

				}
				//RecvDtl188.s_Di =  RecvDtl188.s_Di>>8|RecvDtl188.s_Di<<8;
				m_dtl2007.Tran188to2007(RecvDtl188.s_Di,RecvDtl2007.s_Di,RcvDataZLen);
				for (int n = 0 ; n <6;n++)
				{
					RecvDtl2007.s_AmtBuf[n] = RecvDtl188.s_AmtBuf[n];
				}
				RecvDtl2007.s_Con = RecvDtl188.s_Con+0x10;
				RecvDtl2007.s_97Con = RecvDtl188.s_Con;
				RecvDtl2007.s_97Di = RecvDtl188.s_Di;
				RecvDtl2007.s_188Sec = RecvDtl188.s_SER;
				RecvDtl2007.s_188Type = RecvDtl188.s_Type;
				//if(RcvDataZLen!=RcvDataLen) return 0L;
				for(int n = 0; n < m_BufRcvLen ; n++ )
				{
					m_BufRcv[n] = 0x00;
				}
				m_BufRcvLen = 0;
				SendMeterData(RecvDtl2007,RcvData,RcvDataLen);
			}
		}
	}
	SetEvent(m_hPostMsgEvent);//允许发送下一个WM_COMMNOTIFY消息
	return 0L;
}


DWORD CImitateMeterDlg::ReadComm(INT8U *buf, DWORD dwLength)
{
	DWORD length=0;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	length=min(dwLength, ComStat.cbInQue);
	ReadFile(hCom,buf,length,&length,&m_osRead);	
	return length;
}

void CImitateMeterDlg::SendMeterData(Stu_Dtl2007 stDtl2007,INT8U * databuf,INT8U datalen)
{
	CString strSendType;
	INT8U BufRecv[300];
	INT8U BufRecvlen = 0;
	char  buff[500000];
	char xieyiname[500];
	CString strAddress,str;
	bool ack = false;
	GetPrivateProfileSection("表地址",buff,sizeof(buff),".\\模拟表数据\\模拟表地址.ini"); 
	for(char*   Namee=buff;   *Namee!= '\0';   Namee+=strlen(Namee)+1)
	{
		strAddress.Format("%s", Namee);
		strAddress = strAddress.Left(12);
		str = strAddress.Mid(10,2)+strAddress.Mid(8,2)+strAddress.Mid(6,2)+strAddress.Mid(4,2)+strAddress.Mid(2,2)+strAddress.Mid(0,2);
		if (m_checkJOU.GetCheck())
		{
			if(_ttoi(m_strYaddress.Right(4))%2 == 0)
			{
				stDtl2007.s_AmtBuf[0] = 0x02;
				stDtl2007.s_AmtBuf[1] = 0x00;
				stDtl2007.s_AmtBuf[2] = 0x00;
				stDtl2007.s_AmtBuf[3] = 0x00;
				stDtl2007.s_AmtBuf[4] = 0x00;
				stDtl2007.s_AmtBuf[5] = 0x00;
			}
			else
			{
				stDtl2007.s_AmtBuf[0] = 0x01;
				stDtl2007.s_AmtBuf[1] = 0x00;
				stDtl2007.s_AmtBuf[2] = 0x00;
				stDtl2007.s_AmtBuf[3] = 0x00;
				stDtl2007.s_AmtBuf[4] = 0x00;
				stDtl2007.s_AmtBuf[5] = 0x00;
			}
		}
		
		if(m_dtl2007._buf16tostr16(stDtl2007.s_AmtBuf,6)==str)
		{
			switch(stDtl2007.s_Con)
			{
			case  0x08:
				ack = SendWriteTime(stDtl2007,databuf,datalen,BufRecv,BufRecvlen);
				strSendType = "发送-写：";
				break;
			case 0x11:
				if ((stDtl2007.s_Di>>24)==0x06)
				{
					if ((stDtl2007.s_Di>>16)==0x06A1)
					{
						ack = SendReadData(stDtl2007,BufRecv,BufRecvlen);
					} 
					else
					{
						ack = SendReadQuxianData(stDtl2007,databuf,datalen,BufRecv,BufRecvlen);
					}
				}
				else
				{
					ack = SendReadData(stDtl2007,BufRecv,BufRecvlen);
				}
				strSendType = "发送-读：";
				break;
			case 0x14:
				ack = SendWriteData(stDtl2007,databuf,datalen,BufRecv,BufRecvlen);
				strSendType = "发送-写：";
				break;
			}
			if (ack)
			{
				DWORD nsize;
				INT8U DIbuf[5];
				CString strDi;
				if (m_combType.GetCurSel() == 0)//m_check97.GetCheck())
				{
					DIbuf[1] = (INT8U)(stDtl2007.s_97Di);
					DIbuf[0] = (INT8U)(stDtl2007.s_97Di>>8);
					strDi = m_dtl2007._buf16tostr16(DIbuf,2);
				}
				else if(m_combType.GetCurSel() == 1)
				{
					DIbuf[3] = (INT8U)stDtl2007.s_Di;
					DIbuf[2] = (INT8U)(stDtl2007.s_Di>>8);
					DIbuf[1] = (INT8U)(stDtl2007.s_Di>>16);
					DIbuf[0] = (INT8U)(stDtl2007.s_Di>>24);
					strDi = m_dtl2007._buf16tostr16(DIbuf,4);
				}
				else if(m_combType.GetCurSel() ==2)
				{
					DIbuf[0] = (INT8U)(stDtl2007.s_97Di);
					DIbuf[1] = (INT8U)(stDtl2007.s_97Di>>8);
					strDi = m_dtl2007._buf16tostr16(DIbuf,2);
				}
				
				if (stDtl2007.s_Con!=0x08)
				{
					WriteFile(hCom,BufRecv,BufRecvlen,&nsize,&m_osWrite);
					ShowZhen(m_dtl2007._buf16tostr16(BufRecv,BufRecvlen,true),strSendType+m_strYaddress+"  【【"+strDi+"】】");
				}
				
			}
			break;
		}
		
	}
}
bool CImitateMeterDlg::SendReadQuxianData(Stu_Dtl2007 stDtl2007,INT8U * databuf,INT8U datalen,INT8U * Recvbuf,INT8U &Recvlen)
{
	switch(stDtl2007.s_Di)
	{
	case 0x06000001:
		ReadTimeQuxianData(stDtl2007,databuf,datalen,Recvbuf,Recvlen);
		break;
	}
	return true;
}
void CImitateMeterDlg::ReadTimeQuxianData(Stu_Dtl2007 stDtl2007,INT8U * databuf,INT8U datalen,INT8U * Recvbuf,INT8U &Recvlen)
{
	CAccessData accessData;
	INT8U bufDi[4];
	CString strAddress,strDI,strTime;
	strAddress = m_dtl2007._buf16tostr16(stDtl2007.s_AmtBuf,6);
	strAddress = strAddress.Mid(10,2)+strAddress.Mid(8,2)+strAddress.Mid(6,2)+strAddress.Mid(4,2)+strAddress.Mid(2,2)+strAddress.Mid(0,2);
	bufDi[0] = stDtl2007.s_Di>>24;
	bufDi[1] = stDtl2007.s_Di>>16;
	bufDi[2] = stDtl2007.s_Di>>8;
	bufDi[3] = stDtl2007.s_Di;
	strDI = m_dtl2007._buf16tostr16(bufDi,4);
	CString strStype = "数据";
	CString strWhere = "DI='04000901'";
	CString strData[300];
	int nHang = 0;
	int n;
	CString strMoshizi,str;
	if(accessData.SelectDataFromTable(".\\模拟表数据\\"+strAddress+".mdb","参变量数据",strStype,strWhere,strData,nHang))
	{
		strMoshizi = strData[0].Mid(0,strData[0].GetLength()-1);
		str = m_dtl2007._buf16tostr16(&databuf[1],datalen-1);
		for(n = 0;n<datalen-1;n++)
		{
			strTime += str.Mid((datalen-2-n)*2,2);
		}
		nHang = 0;
		strStype = "NAME";
		CString strTimeFW,strBTime,strETime;
		INT8U bufAlllei[225];
		INT8U RecvDatabuf[255];
		INT8U RecvDatabuflen = 0;;
		if(accessData.SelectDataFromTable(".\\模拟表数据\\CurveData.mdb","TableName",strStype,"",strData,nHang))
		{
			for(n = 0;n<nHang;n++)
			{
				strTimeFW = strData[n].Mid(0,strData[n].GetLength()-1);
				strBTime = strTimeFW.Left(10);
				strETime = strTimeFW.Right(10);
				if ((_ttoi(strTime)>=_ttoi(strBTime))&&(_ttoi(strTime)<=_ttoi(strETime)))
				{
					nHang = 0;
					CString strHHMM = strTime.Right(4);
					int nNumb = 1+(_ttoi(strHHMM.Left(2))*60+_ttoi(strHHMM.Right(2)))/15;
					CString strNumb;
					strNumb.Format("%d",nNumb);
					if (strNumb.GetLength()==1)
					{
						strNumb = "0"+strNumb;
					}
					CString strWhere = "时间='"+strNumb+":"+strHHMM+"'";
					strStype = "A电压,B电压,C电压,A电流,B电流,C电流,频率,总有功功率,A有功功率,B有功功率,C有功功率,总无功功率,A无功功率,B无功功率,C无功功率,总功率因数,A功率因数,B功率因数,C功率因数,正向有功总电能,反向有功总电能,组合无功1总电能,组合无功2总电能,一象限无功总电能,二象限无功总电能,三象限无功总电能,四象限无功总电能,当前有功需量,当前无功需量";
					if(accessData.SelectDataFromTable(".\\模拟表数据\\CurveData.mdb",strTimeFW,strStype,strWhere,strData,nHang))
					{
						int m = 0;
						INT8U nlen = 0;
						int nzonglen= 0;
						for(int x = 0;x<strlen(strData[0]);x++)
						{
							if (strData[0].Mid(x,1) == "$")
							{
								m_dtl2007._str16tobuf16(strData[0].Left(x),&bufAlllei[nzonglen],nlen,true);
								nzonglen += nlen;
								strData[0] = strData[0].Mid(x+1);
								x = -1;
								continue;
							}
						}
						GetQuxianData(strTime,strMoshizi,bufAlllei,RecvDatabuf,RecvDatabuflen);
						stDtl2007.s_Con = stDtl2007.s_Con+0x80;

						stDtl2007.s_AmtBuf[5] = m_AddressBuf[0];
						stDtl2007.s_AmtBuf[4] = m_AddressBuf[1];
						stDtl2007.s_AmtBuf[3] = m_AddressBuf[2];
						stDtl2007.s_AmtBuf[2] = m_AddressBuf[3];
						stDtl2007.s_AmtBuf[1] = m_AddressBuf[4];
						stDtl2007.s_AmtBuf[0] = m_AddressBuf[5];
						m_dtl2007.CodeToWatchZuzhen(stDtl2007,RecvDatabuf,RecvDatabuflen,255,Recvbuf,Recvlen);
					}
				}
			}
		}
	}
}
void CImitateMeterDlg::GetQuxianData(CString strTime,CString strMoshizi,INT8U * bufdata,INT8U * bufQuxianData,INT8U &Quxianlen)
{
	CString strtwo = m_dtl2007._str16tostr2(strMoshizi);
	INT8U timeBuf[5];
	INT8U timeLen = 0;
	m_dtl2007._str16tobuf16(strTime,timeBuf,timeLen,true);
	int nlen = 0;
	int i = 0;
	int nLeiNumb = 0;
	INT8U nDataLen = 5;
	int nDataBegin = 0;
	INT8U cs= 0;
	bufQuxianData[i++] = 0xA0;
	bufQuxianData[i++] = 0xA0;
	i++;
	bufQuxianData[i++] = timeBuf[0];
	bufQuxianData[i++] = timeBuf[1];
	bufQuxianData[i++] = timeBuf[2];
	bufQuxianData[i++] = timeBuf[3];
	bufQuxianData[i++] = timeBuf[4];
	for(int n = 0 ;n < 6 ;n++)
	{
		switch(n)
		{
		case 0:
			nDataBegin = 0;
			nLeiNumb = 17;
			break;
		case 1:
			nDataBegin = 17;
			nLeiNumb = 24;
			break;
		case 2:
			nDataBegin = 41;
			nLeiNumb = 8;
			break;
		case 3:
			nDataBegin = 49;
			nLeiNumb = 16;
			break;
		case 4:
			nDataBegin = 65;
			nLeiNumb = 16;
			break;
		case 5:
			nDataBegin = 81;
			nLeiNumb = 6;
			break;
		}
		if (strtwo.Mid(7-n,1) == "1")
		{
			for(int m = 0;m<nLeiNumb;m++)
			{
				bufQuxianData[i++] = bufdata[nDataBegin+m];
			}
			nDataLen += nLeiNumb+1;
		} 
		else
		{
			nDataLen+=1;
		}
		bufQuxianData[i++] = 0xAA;
	}
	bufQuxianData[2] = nDataLen;

	for(int m = 0 ;m<3+nDataLen;m++)
	{
		cs += bufQuxianData[m];
	}
	bufQuxianData[i++] = cs;
	bufQuxianData[i++] = 0xE5;
	Quxianlen = i;
}
bool CImitateMeterDlg::Get97Data(INT16U Di97)
{
	switch(Di97)
	{
	case 0xB611:
	case 0xB612:
	case 0xB613:
	case 0xB621:
	case 0xB622:
	case 0xB623:
	case 0xA41F:
	case 0xA42F:
	case 0xA51F:
	case 0xA52F:
	case 0xB41F:
	case 0xB42F:
	case 0xB51F:
	case 0xB52F:
	case 0xB212:
		return true;
	}
	return false;
}
bool CImitateMeterDlg::GetKuaiData(Stu_Dtl2007 stDtl2007,INT8U * Recvbuf,INT8U &Recvlen)
{
	CAccessData accessData;
	CString strFenLei,strAddress,strDI;
	INT8U bufLen= 0;
	INT8U bufDi[4];
	switch(stDtl2007.s_Di>>24)
	{
	case 0x00:
		strFenLei = "电能量数据";
		break;
	case 0x01:
		strFenLei = "最大需量及发生时间数据";
		break;
	case 0x02:
		strFenLei = "变量数据标";
		break;
	case 0x03:
		strFenLei = "事件记录数据";
		break;
	case 0x04:
		strFenLei = "参变量数据";
		break;
	case 0x05:
		strFenLei = "冻结数据";
		break;
	case 0x06:
		strFenLei = "负荷记录数据";
		break;
	case 0xff:
		strFenLei = "188数据";
		break;
	default:
		strFenLei = "其他数据";
		break;
	}
	strAddress = m_dtl2007._buf16tostr16(stDtl2007.s_AmtBuf,6);
	strAddress = strAddress.Mid(10,2)+strAddress.Mid(8,2)+strAddress.Mid(6,2)+strAddress.Mid(4,2)+strAddress.Mid(2,2)+strAddress.Mid(0,2);
	
	if (Get97Data(stDtl2007.s_97Di))
	{
		bufDi[0] = stDtl2007.s_97Di>>8;
		bufDi[1] = stDtl2007.s_97Di;
		strDI = m_dtl2007._buf16tostr16(bufDi,2);
	} 
	else
	{
		bufDi[0] = stDtl2007.s_Di>>24;
		bufDi[1] = stDtl2007.s_Di>>16;
		bufDi[2] = stDtl2007.s_Di>>8;
		bufDi[3] = stDtl2007.s_Di;
		strDI = m_dtl2007._buf16tostr16(bufDi,4);
	}
	
	
	CString strData[300];
	CString strStype = "数据";
	CString strWhere = "DI='"+strDI+"'";
	CString strRecvData,strRecvDatalen;
	int nHang= 0;
	if(accessData.SelectDataFromTable(".\\模拟表数据\\"+strAddress+".mdb",strFenLei,strStype,strWhere,strData,nHang))
	{
		if (nHang == 0)
		{
			return false;
		}
		CString strAlldata;
		for(int nRow = 0;nRow<nHang;nRow++)
		{
			strAlldata = strData[nRow];
			int m = 0;
			for(int n = 0;n<strlen(strAlldata);n++)
			{
				if (strAlldata.Mid(n,1) == "$")
				{
					if (m==0)
					{
						strRecvData = strAlldata.Left(n);
					} 
					else
					{
						strRecvDatalen = strAlldata.Left(n);
					}
					strAlldata = strAlldata.Mid(n+1);
					n=-1;
					m+=1;
					continue;
				}
			}
		}
		if ((strDI.Mid(4,2) == "FF"||strDI.Mid(6,2) == "FF")&&strRecvData.Mid(8,1) == ";")
		{
			CString strDi;
			INT32U tmp32Di;
			strRecvData = strRecvData +_T(";");
			for(int b = 0;b<strRecvData.GetLength();b++)
			{
				if (strRecvData.Mid(b,1)==";")
				{
					strDi = strRecvData.Left(b).Right(8);
					stDtl2007.s_Di=((INT8U)strtol((CStringA)strDi.Mid(0,2),NULL,16)<<24)|((INT8U)strtol((CStringA)strDi.Mid(2,2),NULL,16)<<16)|
						((INT8U)strtol((CStringA)strDi.Mid(4,2),NULL,16)<<8)|((INT8U)strtol((CStringA)strDi.Mid(6,2),NULL,16));
					if(!GetKuaiData(stDtl2007,&Recvbuf[Recvlen],bufLen))
					{
						return false;
					}
					Recvlen+=bufLen;
				}
			}
		}
		else
		{
			m_dtl2007._str16tobuf16(strRecvData,Recvbuf,Recvlen,true);
		}
		return true;
	}
	return false;
}

bool CImitateMeterDlg::SendReadData(Stu_Dtl2007 stDtl2007,INT8U * Recvbuf,INT8U &Recvlen)
{
	INT8U Recvdata[200];
	INT8U Recvdatalen = 0;
	if(GetKuaiData(stDtl2007,Recvdata,Recvdatalen))
	{
		stDtl2007.s_Con += 0x80; 
		stDtl2007.s_97Con += 0x80;
	}
	else
	{
		stDtl2007.s_Con += 0xC0; 
	}
	INT8U nlen = 0;
	if (m_combType.GetCurSel() == 0)//m_check97.GetCheck())
	{
		Stu_Dtl1997 RecvDtl1997;
		m_dtl2007._str16tobuf16(m_strYaddress,RecvDtl1997.s_AmtBuf,nlen,true);
		RecvDtl1997.s_Con=stDtl2007.s_97Con;
		RecvDtl1997.s_Di =stDtl2007.s_97Di;
		m_dtl2007.CodeToWatchZuzhen1997(RecvDtl1997,Recvdata,Recvdatalen,255,Recvbuf,Recvlen);
	}
	else if(m_combType.GetCurSel() == 1)
	{
		m_dtl2007._str16tobuf16(m_strYaddress,stDtl2007.s_AmtBuf,nlen,true);
		m_dtl2007.CodeToWatchZuzhen(stDtl2007,Recvdata,Recvdatalen,255,Recvbuf,Recvlen);
	}
	else if(m_combType.GetCurSel() == 2)
	{
		Stu_Dtl188 RecvDtl188;
		m_dtl2007._str16tobuf16(m_strYaddress,RecvDtl188.s_AmtBuf,nlen,true);
		RecvDtl188.s_AmtBuf[6] = 0x00;
		RecvDtl188.s_Con=stDtl2007.s_97Con;
		RecvDtl188.s_Di =stDtl2007.s_97Di;
		RecvDtl188.s_Type = stDtl2007.s_188Type;
		RecvDtl188.s_SER = stDtl2007.s_188Sec;
		m_dtl188.Code188Data(RecvDtl188,Recvdata,Recvdatalen,Recvbuf,Recvlen);
	}

	
	return true;
}

bool CImitateMeterDlg::SendWriteTime(Stu_Dtl2007 stDtl2007,INT8U * databuf,INT8U datalen,INT8U * Recvbuf,INT8U &Recvlen)
{
	CAccessData accessData;
	INT8U bufDi[4];
	INT8U Recvdata[200];
	int Recvdatalen = 0;
	CString strSet,strDate,strTime,strWhere,strDI,strAddress,str;
	CString strFenLei = "参变量数据";
	strAddress = m_dtl2007._buf16tostr16(stDtl2007.s_AmtBuf,6);
	strAddress = strAddress.Mid(10,2)+strAddress.Mid(8,2)+strAddress.Mid(6,2)+strAddress.Mid(4,2)+strAddress.Mid(2,2)+strAddress.Mid(0,2);
	strDI = "04000101";
	str = m_dtl2007._buf16tostr16(databuf,datalen);
	for(int n = 0 ;n<datalen;n++)
	{
		strDate += str.Mid((datalen-n-1)*2,2);
	}
	strTime = strDate.Mid(6);
	strDate = strDate.Mid(0,6)+"00";
	strSet = "数据='"+strDate+"'";
	strWhere = "DI='04000101'";
	if(accessData.UpdataFromTable(".\\模拟表数据\\"+strAddress+".mdb",strFenLei,strSet,strWhere))
	{
		strSet = "数据='"+strTime+"'";
		strWhere = "DI='04000102'";
		if(accessData.UpdataFromTable(".\\模拟表数据\\"+strAddress+".mdb",strFenLei,strSet,strWhere))
		{
			stDtl2007.s_Con += 0x80;
		}
		else
		{
			stDtl2007.s_Con += 0xC0;
		}
	}
	else
	{
		stDtl2007.s_Con += 0xC0;
	}

	

	m_dtl2007.CodeToWatchZuzhen(stDtl2007,Recvdata,Recvdatalen,255,Recvbuf,Recvlen);
	return true;
}

bool CImitateMeterDlg::SendWriteData(Stu_Dtl2007 stDtl2007,INT8U * databuf,INT8U datalen,INT8U * Recvbuf,INT8U &Recvlen)
{
	CAccessData accessData;
	CString strFenLei,strAddress,strDI;
	INT8U bufDi[4];
	switch(stDtl2007.s_Di>>24)
	{
	case 0x00:
		strFenLei = "电能量数据";
		break;
	case 0x01:
		strFenLei = "最大需量及发生时间数据";
		break;
	case 0x02:
		strFenLei = "变量数据标";
		break;
	case 0x03:
		strFenLei = "事件记录数据";
		break;
	case 0x04:
		strFenLei = "参变量数据";
		break;
	case 0x05:
		strFenLei = "冻结数据";
		break;
	default:
		strFenLei = "其他数据";
		break;
	}
	strAddress = m_dtl2007._buf16tostr16(stDtl2007.s_AmtBuf,6);
	strAddress = strAddress.Mid(10,2)+strAddress.Mid(8,2)+strAddress.Mid(6,2)+strAddress.Mid(4,2)+strAddress.Mid(2,2)+strAddress.Mid(0,2);
	bufDi[0] = stDtl2007.s_Di>>24;
	bufDi[1] = stDtl2007.s_Di>>16;
	bufDi[2] = stDtl2007.s_Di>>8;
	bufDi[3] = stDtl2007.s_Di;
	strDI = m_dtl2007._buf16tostr16(bufDi,4);
	
	CString strSet,strWhere,strData,str;
	str = m_dtl2007._buf16tostr16(databuf,datalen);
	for(int n = 0 ;n<datalen;n++)
	{
		strData += str.Mid((datalen-n-1)*2,2);
	}
	INT8U Recvdata[200];
	int Recvdatalen = 0;
	if (strDI == "04001503" && strData == "000000000000000000000000") 
	{
		strDI = "04001501";
		strData = "AAAA000000000000000000000000";
		strSet = "数据='"+strData+"'";
		strWhere = "DI='"+strDI+"'";
		if(accessData.UpdataFromTable(".\\模拟表数据\\"+strAddress+".mdb",strFenLei,strSet,strWhere))
		{
			stDtl2007.s_Con += 0x80;
		}
		else
		{
			stDtl2007.s_Con += 0xC0;
		}
	}
	else
	{
		strSet = "数据='"+strData+"'";
		strWhere = "DI='"+strDI+"'";
		if(accessData.UpdataFromTable(".\\模拟表数据\\"+strAddress+".mdb",strFenLei,strSet,strWhere))
		{
			stDtl2007.s_Con += 0x80;
		}
		else
		{
			stDtl2007.s_Con += 0xC0;
		}
		//stDtl2007.s_Con += 0xC0;
	}
	
	//stDtl2007.s_AmtBuf[0] = m_AddressBuf[5];
	//stDtl2007.s_AmtBuf[1] = m_AddressBuf[4];
	//stDtl2007.s_AmtBuf[2] = m_AddressBuf[3];
	//stDtl2007.s_AmtBuf[3] = m_AddressBuf[2];
	//stDtl2007.s_AmtBuf[4] = m_AddressBuf[1];
	//stDtl2007.s_AmtBuf[5] = m_AddressBuf[0];

	if (m_combType.GetCurSel() == 0)//m_check97.GetCheck())
	{
		Stu_Dtl1997 RecvDtl1997;
		RecvDtl1997.s_Con=stDtl2007.s_Con - 0x10;
		RecvDtl1997.s_Di =stDtl2007.s_97Di;
		m_dtl2007.CodeToWatchZuzhen1997(RecvDtl1997,Recvdata,Recvdatalen,255,Recvbuf,Recvlen);
	}
	else if(m_combType.GetCurSel() == 1)
	{
		m_dtl2007.CodeToWatchZuzhen(stDtl2007,Recvdata,Recvdatalen,255,Recvbuf,Recvlen);
	}
	else if(m_combType.GetCurSel() == 2)
	{
		Stu_Dtl188 RecvDtl188;
		RecvDtl188.s_Con=stDtl2007.s_Con - 0x10;
		RecvDtl188.s_Di =stDtl2007.s_97Di;
		RecvDtl188.s_SER =stDtl2007.s_188Sec;
		RecvDtl188.s_Type =stDtl2007.s_188Type;
		m_dtl188.Code188Data(RecvDtl188,Recvdata,Recvdatalen,Recvbuf,Recvlen);
	}
	return true;
}

void CImitateMeterDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}


void CImitateMeterDlg::OnBnClickedButtonBegin()
{
	SetTimer(1,1000,NULL);
}


void CImitateMeterDlg::OnBnClickedButtonEnd()
{
	KillTimer(1);
}


void CImitateMeterDlg::OnBnClickedBtnSetquxian()
{
	CDlgQuxian quxianDlg;
	quxianDlg.DoModal();
}


void CImitateMeterDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect); 
	if (rect.right == 0 || rect.bottom == 0 )
	{
		return;
	}
	KongjianSize(IDC_SET_COMM,rect.right,rect.bottom);
	KongjianSize(IDC_SETMETER_DATA,rect.right,rect.bottom);
	KongjianSize(IDC_BTN_SETQUXIAN,rect.right,rect.bottom);
	KongjianSize(IDC_EDIT_SHOWMESSAGE,rect.right,rect.bottom);
	KongjianSize(IDC_EDIT_SHOWZHEN,rect.right,rect.bottom);
	KongjianSize(IDC_CHECK_JO,rect.right,rect.bottom);
	KongjianSize(IDC_CHECK_97,rect.right,rect.bottom);
	KongjianSize(IDC_EDIT_PORT,rect.right,rect.bottom);
	KongjianSize(IDC_EDIT_BAUD,rect.right,rect.bottom);
	KongjianSize(IDC_EDIT_PARITY,rect.right,rect.bottom);
	KongjianSize(IDC_STATIC1,rect.right,rect.bottom);
	KongjianSize(IDC_STATIC2,rect.right,rect.bottom);
	KongjianSize(IDC_STATIC3,rect.right,rect.bottom);
	KongjianSize(IDC_STATIC4,rect.right,rect.bottom);
	KongjianSize(IDC_BUTTON1,rect.right,rect.bottom);
	KongjianSize(IDC_COMBO_TYPE,rect.right,rect.bottom,1);
	GetClientRect(m_cRect);
}


void CImitateMeterDlg::OnBnClickedButton1()
{
	m_editShowZhen.SetWindowText("");
}
