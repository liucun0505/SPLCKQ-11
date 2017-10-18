
// KD_Project.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "KD_Project.h"
#include "MainFrm.h"


#include "KD_ProjectDoc.h"

#include "ChildFrm.h"
#include "FrameSetNet.h"
#include "KD_ProjectView.h"

#include "Frame3762.h"
#include "FView3762.h"

#include "Form698.h"
#include "View698.h"

#include "MainTestFrame.h"
#include "MainTestDoc.h"

#include "NetTabView.h"
#include "RightTabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKD_ProjectApp

BEGIN_MESSAGE_MAP(CKD_ProjectApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CKD_ProjectApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CKD_ProjectApp 构造

CKD_ProjectApp::CKD_ProjectApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("KD_Project.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CKD_ProjectApp 对象

CKD_ProjectApp theApp;


// CKD_ProjectApp 初始化

BOOL CKD_ProjectApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	
	m_pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CKD_ProjectDoc),
		RUNTIME_CLASS(CFrameSetNet), 
		RUNTIME_CLASS(CRightTabView));
	if (!m_pDocTemplate)
		return FALSE;
	//AddDocTemplate(m_pDocTemplate);

	m_pDocTemp3762 = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CKD_ProjectDoc),
		RUNTIME_CLASS(CFrame3762), // 自定义 MDI 子框架
		RUNTIME_CLASS(CFView3762));
	if (!m_pDocTemp3762)
		return FALSE;
	//AddDocTemplate(m_pDocTemp3762);

	m_pDocTemp698 = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CKD_ProjectDoc),
		RUNTIME_CLASS(CForm698), // 自定义 MDI 子框架
		RUNTIME_CLASS(CView698));
	if (!m_pDocTemp698)
		return FALSE;
	//AddDocTemplate(m_pDocTemp698);

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 MDI 应用程序中，这应在设置 m_pMainWnd 之后立即发生

	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand=CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);



	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CKD_ProjectApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CKD_ProjectApp 消息处理程序


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
public:
//	virtual BOOL OnInitDialog();
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
//	afx_msg void OnClose();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_CLOSE()
	ON_WM_CLOSE()
//	ON_WM_CREATE()
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CKD_ProjectApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CKD_ProjectApp 自定义加载/保存方法

void CKD_ProjectApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CKD_ProjectApp::LoadCustomState()
{
}

void CKD_ProjectApp::SaveCustomState()
{
}

// CKD_ProjectApp 消息处理程序






//BOOL CAboutDlg::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// TODO:  在此添加额外的初始化
//	
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// 异常: OCX 属性页应返回 FALSE
//}


//BOOL CAboutDlg::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: 在此添加专用代码和/或调用基类
//
//	return CDialogEx::PreCreateWindow(cs);
//}


//void CAboutDlg::OnClose()
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnClose();
//}


//int CAboutDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码
//
//	return 0;
//}
