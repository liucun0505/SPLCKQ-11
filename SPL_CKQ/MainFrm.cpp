
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "DlgConnection.h"
#include "MainFrm.h"
#include "Tools.h"
#include "cSerBuf_LoopRcv.h"
#include "DlgSelect.h"
//extern cSerBuf_LoopRcv  m_loopRcv64507;
extern cSerBuf_LoopRcv m_loopRcv13762;

#define BIT_SET(x, bitn)    (x |=   (1 << bitn))
#define BIT_CLR(x, bitn)    (x &=  ~(1 << bitn))
#define IS_BIT_SET(x, bitn) ((x & (1 << bitn)) != 0)
#define IS_BIT_CLR(x, bitn) ((x & (1 << bitn)) == 0)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

//BEGIN_MESSAGE_MAP
BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_MESSAGE(WM_COMMNOTIFY, OnComm)
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_CONNECT_OPEN, &CMainFrame::OnConnectOpen)
	ON_COMMAND(ID_CONNECT_CLOSE, &CMainFrame::OnConnectClose)
	ON_COMMAND(ID_NETWORT_OPEN, &CMainFrame::OnNetwortOpen)
	ON_UPDATE_COMMAND_UI(ID_CONNECT_OPEN, &CMainFrame::OnUpdateConnectOpen)
	ON_UPDATE_COMMAND_UI(ID_CONNECT_CLOSE, &CMainFrame::OnUpdateConnectClose)
	ON_WM_TIMER()
	ON_COMMAND(ID_3762_OPEN, &CMainFrame::On3762Open)
	ON_COMMAND(ID_FRAMESHOW, &CMainFrame::OnFrameshow)
	ON_COMMAND(ID_COPYFRAME, &CMainFrame::OnCopyframe)
	ON_WM_CLOSE()
	ON_COMMAND(ID_JZQ, &CMainFrame::OnJzq)
	ON_UPDATE_COMMAND_UI(ID_JZQ, &CMainFrame::OnUpdateJzq)
	ON_COMMAND(ID_CKQ20, &CMainFrame::OnCkq20)
	ON_UPDATE_COMMAND_UI(ID_CKQ20, &CMainFrame::OnUpdateCkq20)
END_MESSAGE_MAP()


//static UINT indicators[] =
//{
//	ID_SEPARATOR,           // 状态行指示器
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
//};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
	m_bNetWork = FALSE;
	m_bNetWorkOpen = FALSE;
	m_bConnected = FALSE;
	m_bsetopen=TRUE;
	m_bsetclos=FALSE;
	m_bFrame3762 = FALSE;
	m_bFrame698 = FALSE;
	m_bCommunictStop = FALSE;
	m_strMAddress = _T("");
	m_376seq = 0;
	m_nConnectType = 0;
	m_PeiZhi_db=".\\配置文件\\13762Data.accdb";
	m_bCKQ=TRUE;
	m_bJZQ=!m_bCKQ;
}

CMainFrame::~CMainFrame()
{
	m_FrameShowWnd.ShowWindow(SW_HIDE);
	
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // 其他可用样式...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // 设置为 FALSE 会将关闭按钮放置在选项卡区域的右侧
	mdiTabParams.m_bTabIcons = FALSE;    // 设置为 TRUE 将在 MDI 选项卡上启用文档图标
	mdiTabParams.m_bAutoColor = TRUE;    // 设置为 FALSE 将禁用 MDI 选项卡的自动着色
	mdiTabParams.m_bDocumentMenu = TRUE; // 在选项卡区域的右边缘启用文档菜单
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 允许用户定义的工具栏操作:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	LoadStatusBar();
	

	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 启用增强的窗口管理对话框
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// 启用工具栏和停靠窗口菜单替换
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// 加载用户定义的工具栏图像
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}
	if((m_hPostMsgEvent=CreateEvent(NULL, FALSE, TRUE, NULL))==NULL)
		return FALSE;

	memset(&m_osRead, 0, sizeof(OVERLAPPED));
	memset(&m_osWrite, 0, sizeof(OVERLAPPED));

	// 为重叠读创建事件对象，手工重置，初始化为无信号的
	if((m_osRead.hEvent=CreateEvent(NULL, FALSE, FALSE, NULL))==NULL)
		return FALSE;

	// 为重叠写创建事件对象，手工重置，初始化为无信号的
	if((m_osWrite.hEvent=CreateEvent(NULL, FALSE, FALSE, NULL))==NULL)
		return FALSE;
	// 启用菜单个性化(最近使用的命令)
	// TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	/*CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);*/

	// 将文档名和应用程序名称在窗口标题栏上的顺序进行交换。这
	// 将改进任务栏的可用性，因为显示的文档名带有缩略图。
	ModifyStyle(0, FWS_PREFIXTITLE);

	m_Font70.CreatePointFont(90,_T("黑体"));
	m_Font100.CreatePointFont(100,_T("黑体"));
	m_Font120.CreatePointFont(125,_T("黑体"));


	CString strObjectView("信息窗口");  
	if (!m_FrameShowWnd.Create(strObjectView, this, CRect(0, 0, 200, 200), TRUE, 1001, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))  
	{  
		TRACE0("未能创建“信息窗口”窗口\n");  
		return 0; // 未能创建  
	}
	m_FrameShowWnd.EnableDocking(CBRS_ALIGN_ANY); //使可停靠与浮动  
	DockPane(&m_FrameShowWnd);
	m_FrameShowWnd.ShowWindow(SW_HIDE);

	CString strObjectView2("树形拓扑");  
	if (!mm_FrameShowWndTree.Create(strObjectView2, this, CRect(0, 0, 600, 400), TRUE, 1002, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))  
	{  
		TRACE0("未能创建“树形拓扑”窗口\n");  
		return 0; // 未能创建  
	}
	mm_FrameShowWndTree.EnableDocking(CBRS_ALIGN_ANY); //使可停靠与浮动  
	DockPane(&mm_FrameShowWndTree);
	mm_FrameShowWndTree.ShowWindow(SW_SHOW);


	return 0;
}

void CMainFrame::OnFrameshow()
{
	m_FrameShowWnd.ShowWindow(SW_SHOW);
}
void CMainFrame::Creat_File()
{

//#if 0
//	//初始化隐藏调试信息
//	displayComData = false;
//	GetDlgItem(IDC_BUTTON10)->SetWindowText("显示调试信息");
//#endif

	///////////打开本轮测试的LOG文件
	CString str,strTemp;
	SYSTEMTIME st;
	GetLocalTime(&st);
	CFileException fileException;

	str = _T(".\\日志\\DataFile-");
	strTemp.Format(_T("%.4d年%.2d月%.2d日"),st.wYear,st.wMonth,st.wDay);
	//strTemp.Format(_T("%.4d年%.2d月%.2d日%.2d点%.2d分%.2d秒"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	if(!cfileData.Open(str+ strTemp +_T(".txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite 
		| CFile::shareDenyNone, &fileException))
	{
		//TRACE( "Can't open file, error = %u\n",fileException.m_cause );
		AfxMessageBox(_T("Can't open file,自动测试数据LOG无法保存"));
		bAutoTestRunCmd = false;
	}else TRACE("open data file ok \r\n");

	//str = _T(".\\log_3762\\ParsFile-");		
	//if(!cfileParse.Open(str+ strTemp +_T(".txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite 
	//	| CFile::shareDenyNone, &fileException))
	//{
	//	//TRACE( "Can't open file, error = %u\n",fileException.m_cause );
	//	AfxMessageBox(_T("Can't open PARSE file，自动测试解析LOG无法保存"));
	//	bAutoTestRunCmd = false;
	//}else TRACE("open parse file ok \r\n");

	cfileData.Write(str,str.GetLength());
}
void CMainFrame::Close_File()
{
	cfileData.Close();
	cfileParse.Close();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 为所有用户工具栏启用自定义按钮
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}
BOOL CMainFrame::LoadStatusBar()
{
	UINT indicators[] =
	{
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR
	};
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return FALSE;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_POPOUT,0);
	m_wndStatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_POPOUT,30);
	m_wndStatusBar.SetPaneText(1,_T("串口:"));
	m_wndStatusBar.SetPaneInfo(2,ID_SEPARATOR,SBPS_POPOUT,150);
	m_wndStatusBar.SetPaneText(2,_T("关闭"));
	m_wndStatusBar.SetPaneInfo(3,ID_SEPARATOR,SBPS_STRETCH,0);
	SetTimer(IDS_STATUSBARSYSTIME,500,NULL);
	return TRUE;
}






UINT CommProcc(LPVOID pParam)
{
	OVERLAPPED os;
	DWORD dwMask, dwTrans;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	CMainFrame* pMain= (CMainFrame*)pParam;

	memset(&os, 0, sizeof(OVERLAPPED));
	os.hEvent=CreateEvent(NULL, FALSE, FALSE, NULL);

	if(os.hEvent==NULL)
	{
		AfxMessageBox(_T("无法创建事件对象!"));
		return (UINT)-1;
	}

	while(pMain->m_bConnected)
	{
		ClearCommError(pMain->hCom,&dwErrorFlags,&ComStat);

		if(ComStat.cbInQue)
		{
			// 无限等待WM_COMMNOTIFY消息被处理完
			WaitForSingleObject(pMain->m_hPostMsgEvent, INFINITE);
			ResetEvent(pMain->m_hPostMsgEvent);

			// 通知视图
			PostMessage(pMain->m_hTermWnd, WM_COMMNOTIFY, EV_RXCHAR, 0);

			continue;
		}

		dwMask=0;

		if(!WaitCommEvent(pMain->hCom, &dwMask, &os)) // 重叠操作
		{

			if(GetLastError()==ERROR_IO_PENDING)
				// 无限等待重叠操作结果
				GetOverlappedResult(pMain->hCom, &os, &dwTrans, TRUE);
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
void CMainFrame::OnConnectOpen()
{
	CDlgConnection dlgConnection;
	CTools tools;
	INT16U temp16 = 0;
	while(1)
	{
		int nBTN = dlgConnection.DoModal();
		if (nBTN == IDOK)
		{
			COMMTIMEOUTS TimeOuts;

			tools._str16tobuf16(dlgConnection.m_strMainMAC , m_HostNodeAddress ,temp16,true);

			m_hTermWnd=this->GetSafeHwnd();
			int xunhuan=0;
			if(m_bConnected)
				return;
			hCom=CreateFile(_T("\\\\.\\")+dlgConnection.m_strCommPort,
				GENERIC_READ|GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
				NULL);
			SetupComm(hCom,MAXBLOCK,MAXBLOCK);
			SetCommMask(hCom, EV_RXCHAR);
			PurgeComm( hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR );  //清干净输入、输出缓冲区 

			// 把间隔超时设为最大，把总超时设为0将导致ReadFile立即返回并完成操作
			TimeOuts.ReadIntervalTimeout=MAXDWORD; 
			TimeOuts.ReadTotalTimeoutMultiplier=0; 
			TimeOuts.ReadTotalTimeoutConstant=0; 

			//设置写超时以指定WriteComm成员函数中的GetOverlappedResult函数的等待时间
			TimeOuts.WriteTotalTimeoutMultiplier=50;
			TimeOuts.WriteTotalTimeoutConstant=2000;

			SetCommTimeouts(hCom, &TimeOuts);

			DCB dcb;
			GetCommState(hCom,&dcb);
			dcb.BaudRate=_ttol(dlgConnection.m_strCommBaud);  //传输速率
			dcb.Parity=_ttol(dlgConnection.m_strCommParity);  //奇偶性
			dcb.ByteSize=_ttol(dlgConnection.m_strCommDatabit);    //起始位
			dcb.StopBits=_ttol(dlgConnection.m_strCommStopbit); //停止位
			if(SetCommState(hCom,&dcb))
			{
				m_pThread=AfxBeginThread(CommProcc, this, THREAD_PRIORITY_NORMAL, 
					0, CREATE_SUSPENDED, NULL); // 创建并挂起线程

				if(m_pThread==NULL)
				{
					CloseHandle(hCom);
					return;
				}
				else	
				{
					SetStatusBat(GetCommMessage(dlgConnection.m_strCommPort,dlgConnection.m_strCommBaud,dlgConnection.m_strCommParity,dlgConnection.m_strCommDatabit,dlgConnection.m_strCommStopbit));
					m_bsetopen = false;
					m_bsetclos = true;
					m_bConnected=TRUE;
					m_nConnectType = CONNECTCKQ;
					m_pThread->ResumeThread(); // 恢复线程运行
				}
				return;
			}
			else
			{
				AfxMessageBox(dlgConnection.m_strCommPort + _T(" 被占用或未找到!请检查串口"));
			}
		}
		else
		{
			break;
		}
	}
	
}
void CMainFrame::OnConnectClose()
{
	
	if(!m_bConnected)
		return;
	m_bsetclos=FALSE;
	m_bsetopen=TRUE;
	m_bConnected=FALSE;

	//结束CommProc线程中WaitSingleObject函数的等待
	SetEvent(m_hPostMsgEvent); 

	//结束CommProc线程中WaitCommEvent的等待
	SetCommMask(hCom, 0); 

	//等待辅助线程终止
	WaitForSingleObject(m_pThread->m_hThread, INFINITE);
	m_pThread=NULL;
	SetStatusBat(_T("关闭"));
	m_nConnectType = 0;
	CloseHandle(hCom);
}

LRESULT CMainFrame::OnComm(WPARAM wParam, LPARAM lParam)
{
	INT8U buf[1];
	CString str;
	int nLength;
	if(!m_bConnected || (wParam & EV_RXCHAR)!=EV_RXCHAR) // 是否是EV_RXCHAR事件?
	{
		SetEvent(m_hPostMsgEvent); // 允许发送下一个WM_COMMNOTIFY消息
		return 0L;
	}

	nLength=ReadComm(buf,1);
	if(nLength)
	{
		m_loopRcv13762.InPutRcvByte(buf[0]);
	}
	SetEvent(m_hPostMsgEvent);//允许发送下一个WM_COMMNOTIFY消息
	return 0L;
}
DWORD CMainFrame::ReadComm(INT8U *buf, DWORD dwLength)
{
	DWORD length=0;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	length=min(dwLength, ComStat.cbInQue);
	ReadFile(hCom,buf,length,&length,&m_osRead);	
	return length;
}
void CMainFrame::OnUpdateConnectOpen(CCmdUI *pCmdUI)
{
	if (m_bsetopen)
	{
		pCmdUI-> Enable(TRUE); 
	}
	else
	{
		pCmdUI-> Enable(FALSE); 
	}
}
void CMainFrame::OnUpdateConnectClose(CCmdUI *pCmdUI)
{
	if (m_bsetclos)
	{
		pCmdUI-> Enable(TRUE); 
	}
	else
	{
		pCmdUI-> Enable(FALSE); 
	}
}
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
#if 0//no ms
	CTime t = CTime::GetCurrentTime();//获取当前系统时间   
	m_strSysTime = t.Format("%H:%M:%S");
	m_strSysDateTime = t.Format("%Y年%m月%d日 %H:%M:%S");
#else
	SYSTEMTIME st;
	GetLocalTime(&st);
	m_strSysTime.Format(_T("%.2d:%.2d.%.2d"), st.wHour, st.wMinute, st.wSecond);
	//m_strSysDateTime.Format(_T("%d年%d月%d日 %.2d:%.2d:%.2d:%.3d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#endif 




	if (nIDEvent == IDS_STATUSBARSYSTIME)
	{
		CClientDC dc(this);  
		CSize cs = dc.GetTextExtent(m_strSysTime);//获取字符串长度   
		m_wndStatusBar.SetPaneInfo(4,ID_SEPARATOR,SBPS_POPOUT,cs.cx);//根据字符串长度设置窗格长度   
		m_wndStatusBar.SetPaneText(4,m_strSysTime,TRUE);
	}
	else
	{
		switch(nIDEvent)
		{
		case 0:
			break;
		}
	}
	
	CMDIFrameWndEx::OnTimer(nIDEvent);
}
void CMainFrame::SetStatusBat(CString strPort)
{
	m_wndStatusBar.SetPaneText(2,strPort,TRUE);
}
CString CMainFrame::GetCommMessage(CString strPort, CString strBaud , CString strParity , CString strDatabit, CString strStopbit)
{
	CString strData = strPort + _T("（") + strBaud + _T("，");
	switch(_ttoi(strParity))
	{
	case 0:
		strParity = "N";
		break;
	case 1:
		strParity = "E";
		break;
	case 2:
		strParity = "O";
		break;
	}
	switch(_ttoi(strStopbit))
	{
	case 0:
		strStopbit = "1";
		break;
	case 1:
		strStopbit = "1.5";
		break;
	case 2:
		strStopbit = "2";
		break;
	}
	strData += strParity + _T("，") + strDatabit + _T("，") + strStopbit + _T("）");
	return strData;
}
void CMainFrame::OnNetwortOpen()
{
	/*if(!m_bConnected)
	{
		AfxMessageBox(_T("请先打开串口连接抄控器!"));
		return;
	}*/
		
	m_nChooseView = OPENNET;
	CSPL_CKQApp* pApp=(CSPL_CKQApp*)AfxGetApp();
	if (m_bNetWork==FALSE)
	{
		pApp->m_pDocTemplate->OpenDocumentFile(NULL);
		m_pFrameNetWork=(CFrameSetNet *)GetActiveFrame();
		m_bNetWork=TRUE;
		return;
	}
	m_pFrameNetWork->MDIActivate();
}
void CMainFrame::On3762Open()
{
	if(!m_bConnected)
	{
		AfxMessageBox(_T("请先打开串口连接抄控器!"));
		return;
	}
	m_nChooseView = OPEN13762;
	///////////////////////////////////////////////////////////
	//DlgSelect dlgsetnw;
	//int nBTN = dlgsetnw.DoModal();
	//if(NW_OR_GW==0)
	//{
	//	m_PeiZhi=".\\配置文件\\13762树控件.ini";
	//	m_PeiZhi_db=".\\配置文件\\13762Data.accdb";
	//}
	//else if(NW_OR_GW==1)
	//{
	//	m_PeiZhi=".\\配置文件\\13762树控件NW.ini";
	//	m_PeiZhi_db=".\\配置文件\\13762DataNW.accdb";
	//}
	////////////////////////////////////////////////////////////
	CSPL_CKQApp* pApp=(CSPL_CKQApp*)AfxGetApp();
	pApp->m_pDocTemp3762->OpenDocumentFile(NULL);
	m_pFrame3762=(CFrame3762 *)GetActiveFrame();
	m_bFrame3762=TRUE;
	return;
	//if (m_bFrame3762==FALSE)
	//{
	//pApp->m_pDocTemp3762->OpenDocumentFile(NULL);
	//m_pFrame3762=(CFrame3762 *)GetActiveFrame();
	//m_bFrame3762=TRUE;
	//return;
	//}
	//m_pFrame3762->MDIActivate();
}

void CMainFrame::SendBufToCOMM(INT8U * sendbuf,INT16U sendLen , INT8U nType)
{
	DWORD  nsize = 0;
	m_loopRcv13762.ClrRcvBuf();


	SYSTEMTIME st;
	GetLocalTime(&st);
	m_strSysDateTime_tx.Format(_T("%d年%d月%d日 %.2d:%.2d:%.2d.%.3d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);


	switch(nType)
	{
	case 0:
		WriteFile(hCom,sendbuf,sendLen,&nsize,&m_osWrite);
		break;
	case 1:
		//WriteFile(m_hCom645,sendbuf,sendLen,&nsize,&m_osWrite2);
		break;
	}
	///////保存日志
	int nItem = m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemCount();
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.InsertItem(nItem , m_strSysDateTime_tx);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 1, _T("发送>>"));
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 2 , m_tools._buf16tostr16(sendbuf , sendLen , true));
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.EnsureVisible(nItem,FALSE);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.RedrawItems(nItem,nItem);

}

void CMainFrame::BF_SendBufToCOMM(INT8U * sendbuf,INT16U sendLen , INT8U nType)
{
	DWORD  nsize = 0;
	//m_loopRcv13762.ClrRcvBuf();


	SYSTEMTIME st;
	GetLocalTime(&st);
	m_strSysDateTime_tx.Format(_T("%d年%d月%d日 %.2d:%.2d:%.2d.%.3d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);


	switch(nType)
	{
	case 0:
		WriteFile(hCom,sendbuf,sendLen,&nsize,&m_osWrite);
		break;
	case 1:
		//WriteFile(m_hCom645,sendbuf,sendLen,&nsize,&m_osWrite2);
		break;
	}
	///////保存日志
	int nItem = m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemCount();
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.InsertItem(nItem , m_strSysDateTime_tx);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 1, _T("发送>>"));
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 2 , m_tools._buf16tostr16(sendbuf , sendLen , true));
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.EnsureVisible(nItem,FALSE);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.RedrawItems(nItem,nItem);

}
unsigned char CMainFrame::getFn(ST_Fn stFn)
{
	unsigned char fn = 0;
	char i = 0;
	
	for (;i<8;i++)
	{
		if (IS_BIT_SET(stFn.DT1,i))
		{
			fn = i+1;
			break;
		}
	}
	fn += (stFn.DT2 << 3); 

	return fn;
}

void CMainFrame::OnCopyframe()
{
	CString strCopy = m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemText (m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.m_itemYes , 2);
	if (strCopy == "")
	{
		return;
	}
	CStringA strA;
	strA = strCopy;
	if(OpenClipboard())   
	{   
		HGLOBAL   clipbuffer;   
		char   *   buffer;   
		EmptyClipboard();   
		clipbuffer   =   GlobalAlloc(GMEM_DDESHARE,   strA.GetLength()+1);   
		buffer   =   (char*)GlobalLock(clipbuffer);   
		strcpy(buffer, (LPSTR)(LPCSTR)strA);
		GlobalUnlock(clipbuffer);   
		SetClipboardData(CF_TEXT,clipbuffer);   
		CloseClipboard();   
	}
}


void CMainFrame::OnClose()
{
	
    CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	if(6 == MessageBox(_T("该软件正在运行，是否退出？") , _T("系统提示") ,MB_YESNO))
	{
		//m_access.DelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("TPShow"),_T(""));
		m_access.DelectDataFromTable(pMain->m_PeiZhi_db,_T("TPShow"),_T(""));
		CMDIFrameWndEx::OnClose();
	}
}

CString CMainFrame::GetRecvErrName(INT8U nChoose)
{
	CString str;
	switch(nChoose)
	{
	case 0:
		str = _T(">>>>失败:通信超时");
		break;
	case 1:
		str = _T(">>>>失败:无效数据单元");
		break;
	case 2:
		str = _T(">>>>失败:长度错");
		break;
	case 3:
		str = _T(">>>>失败:校验错误");
		break;
	case 4:
		str = _T(">>>>失败:信息类不存在");
		break;
	case 5:
		str = _T(">>>>失败:格式错误");
		break;
	case 6:
		str = _T(">>>>失败:表号重复");
		break;
	case 7:
		str = _T(">>>>失败:表号不存在");
		break;
	case 8:
		str = _T(">>>>失败:电表应用层无应答");
		break;
	case 9:
		str = _T(">>>>失败:主节点忙");
		break;
	case 10:
		str = _T(">>>>失败:主节点不支持此命令");
		break;
	case 11:
		str = _T(">>>>失败:从节点不应答");
		break;
	case 12:
		str = _T(">>>>失败:从节点不在网内");
		break;
	}
	return str;
}
CString CMainFrame::GetAckErrName(INT8U nChoose)
{
	CString str;
	switch(nChoose)
	{
	case 0x13://失败
		str = _T("失败");
		break;
	case 0x30://SEQ不一致
		str = _T("SEQ不一致");
		break;
	case 0x0A://主节点不支持此命令
		str = _T("主节点不支持此命令");
		break;
	case 0xA0://通讯超时
		str = _T("通讯超时");
		break;
	default:
		str = _T("其他错误");
		break;
	}
	return str;
}

void CMainFrame::InsertItemToOnlineList(CString strTableName)
{
	//ShowNetListView *pViewOnlineList=(ShowNetListView*)m_cSplitter.GetPane(0,1);//放在OnCreate函数里
	m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.DeleteAllItems();
	CString strNumb;
	CString m_strlist[1000];
	CString str;
	CString str_nodeNum = _T("");
	CString strAllDatalist[500][6];
	CString f_strDatalist[6][500];
	int nNumb = 0 , nAlldataNumb;
	int n = 0 , m = 0 , i = 0;
	m_access.SelectDataFromTable(m_PeiZhi_db/*_T(".\\配置文件\\HistTPShow.accdb")*/, strTableName , _T("TP_MAC,TP_TEI,TP_PTEI,TP_ROLE") ,_T("") ,m_strlist ,nAlldataNumb);
	if(nAlldataNumb>0){
		for(n = 0 ; n < nAlldataNumb ; n++)
		{
			m_tools.Split(m_strlist[n] , _T("$") ,strAllDatalist[n] , nNumb);
	        str.Format(_T("%d") , n + 1);
	        m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.InsertItem(n,str);
	        m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,1,strAllDatalist[n][0]);
	        m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,2,strAllDatalist[n][1]); 
			m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,3,strAllDatalist[n][2]);
			if(strAllDatalist[n][3]==_T("2")){
				m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,4,_T("CCO"));
			}
			else if(strAllDatalist[n][3]==_T("4")){
				m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,4,_T("STA"));
			}
			else if(strAllDatalist[n][3]==_T("6")){
				m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,4,_T("PCO"));
			}
			else{
				m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,4,_T("未知角色"));
			}
		}
	}


	//pViewOnlineList->GetListCtrl().InsertItem(n , strNumb);
	//pViewOnlineList->GetListCtrl().SetItemText(n , 1 , strAddress);
	////pViewOnlineList->GetListCtrl().SetItemText(n , 1 , strMAC.Mid(0 , 2) + _T(":") + strMAC.Mid(2 , 2) + _T(":") + strMAC.Mid(4 , 2) + _T(":") + strMAC.Mid(6 , 2) + _T(":") + strMAC.Mid(8 , 2) + _T(":") + strMAC.Mid(10 , 2));
	//pViewOnlineList->GetListCtrl().SetItemText(n , 2 , strTEI);
	//pViewOnlineList->GetListCtrl().EnsureVisible(n,FALSE);
	//pViewOnlineList->GetListCtrl().RedrawItems(n,n);
}

void CMainFrame::OnJzq()
{
	// TODO: 在此添加命令处理程序代码
	m_bJZQ=!m_bJZQ;
	m_bCKQ=!m_bJZQ;
}


void CMainFrame::OnUpdateJzq(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_bJZQ);   
}


void CMainFrame::OnCkq20()
{
	// TODO: 在此添加命令处理程序代码
	m_bCKQ=!m_bCKQ;
	m_bJZQ=!m_bCKQ;
}


void CMainFrame::OnUpdateCkq20(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_bCKQ); 
}
