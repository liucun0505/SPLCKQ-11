
// MainFrm.h : CMainFrame 类的接口
//
#include "ChildFrm.h"
#include "FrameSetNet.h"
#include "Frame3762.h"
#include "Form698.h"
#include "MainTestFrame.h"
#include "cSerBuf_LoopRcv.h"
#include "GW13762.h"
#include "CSG13762.h"
#include "SimMeter.h"
#include "Tools.h"
#include "cSerBuf_LoopRcv.h"
#include "FrameShowWnd.h"
#include "FrameShowWndTree.h"
#include "gPublicObjct.h"
#include "resource.h"
#include "LogFile.h"
#include "Tools.h"
#include "AccessData.h"
#include "CKQViewTabErrMet.h"
#pragma once
#define MAXBLOCK 4096

#define CONNECTCKQ  1
#define CONNECTCCO  2
#define CONNECTSTA  3

#define OPENNET 1
#define OPEN13762 2
#define OPEN698 3

#define START_CODE	0X68
#define END_CODE	0X16

#define DOWN 0//下行方向
#define UP	 1//上行方向

#define LAUNCH 1
#define ANSWER 0

#define MASTER_NOD	0
#define SLAVE_NOD	1

#define BPLC 3 //宽带载波

#define R_INFOR_SIZE 6

#define AFN_FN_LENGTH 3

#define  DATA_FILE	 0
#define  DataIfo	1
#define  PARS_FILE	2
#define  OUTPUT 0
#define  TIME 1
#define  NOTIME 0
#define  INPUT_DATA	 1

#define MAX_BUF_LENGTH 4096

#define AUTO_TEST 1
#define AUTO_TEST_START_NOD_ADDR 1
#define READ_SLAVE_NOD_NUM_MAX 0XFF
#define COM_ACK_TIMEOUT_SECONDS 5//15//5//串口等待单片机回应时间

#define FLASH_READ_LENGTH 1024
#define NOD_NUM_OF_1KFLASH 64//1KFLASH上的节点信息数量
#define AFN_MAX_NUM 23

#define SAVE_LOG 1//是否保存LOG文件

#define MAX_NOD_ADDR 999999999999//节点地址最大值
#define FLASH_DELED_DATA 0XFFFFFFFFFFFF//删除后的节点地址


enum AFN
{
	AFN00=0,AFN01,AFN02,AFN03,AFN04,AFN05,AFN06,AFN10=0X10,AFN11,AFN12,AFN13,AFNF0=0XF0
};

enum ProtocolType
{
	TRANSPARENT_TRANS=0,DLT645_1997,DLT645_2007
};

enum enum_AUTO_TEST_SATE{AUTO_TEST_WRITE_READ=0,	AUTO_TEST_ADD_DEL,	AUTO_TEST_ELECTRICAL_METER,	AUTO_TEST_3762PROTOCAL,	 AUTO_TEST_FLOW_METER ,AUTO_TEST_CHAOBIAO, TEST_STAT_RESET_READ};//LCJ3

typedef union
{
	BYTE bitByte;
	struct 
	{
		BYTE comunate_mod:6;
		BYTE prm:1;
		BYTE dir:1;
	}bits;
}UN_C_DATA;//control data

typedef union
{
	BYTE bitByte[6];
	struct 
	{
		BYTE route			:1;//路由标识
		BYTE subNode		:1;
		BYTE module			:1;
		BYTE collisDetect	:1;
		BYTE routeLevel		:4;//byte1

		BYTE channel		:4;
		BYTE errCorrect		:4;//byte 2

		BYTE prediAnserBn	;//byte 3 predictAnswerbyteNum

		WORD rate			:15;
		WORD rateUnit		:1;//速率单位 byte4-5

		BYTE serialNum		;//byte 6
	}bits;
}UN_DOWN_R_DATA;//control data

typedef union
{
	BYTE bitByte[6];
	struct 
	{
		BYTE route			:1;//路由标识
		BYTE resved1		:1;
		BYTE module			:1;
		BYTE resved2		:1;
		BYTE routeLevel		:4;//byte1

		BYTE channel		:4;
		BYTE resved3		:4;//byte 2

		BYTE RealPhaseLine	:4;//byte 3 predictAnswerbyteNum
		BYTE meterChStyle	:4;

		BYTE finalCmdQual	:4;
		BYTE finalAnsQual	:4;//速率单位 byte4

		BYTE events			:1;//byte 5
		BYTE resved4		:7;

		BYTE serialNum;			//byte6
	}bits;
}UN_UP_R_DATA;//上行信息数据

typedef union
{
	UN_DOWN_R_DATA	R_down;
	UN_UP_R_DATA	R_up;
}UN_R_DATA;

typedef union
{
	BYTE data[3];
	struct 
	{
		BYTE test;
		WORD route			:15;//路由标识
		WORD K				:1;
	}bits;
}UN_ST_TEST;


typedef struct
{
	BYTE DT1;
	BYTE DT2;
}ST_Fn;

typedef struct tpd_ST_1376_2_FRAME{
	WORD L;
	UN_C_DATA C;

	UN_R_DATA R;//上下行R可选

	BYTE A1[6];
	BYTE A2[6];
	BYTE A3[6];

	BYTE AFN;

	ST_Fn Fn;

	BYTE CS;
}ST_1376_2_FRAME;


typedef struct tpd_SAVE_376_2_APNFN{

	unsigned char apn;
	unsigned char fn;
	unsigned char SEQ;

}SAVE_376_2_APNFN;

#define MAX_NOD_NUM 1024 //最大节点数
#define MAX_READ_NUM 10//单片机一次允许读取的最大节点数，超过次数会返回否认
typedef struct TYPE_ST_RECV_NOD_INFOR//接收节点信息
{
	WORD wTotlaNodNum;//总结点数，正常情况下也是当前写入的节点总数
	WORD wSumCurrentNodNum;//当前结点数量累加
	BYTE byCurrentNodNum;//当前应答节点数目

	UINT64 L64NodAddrs[MAX_NOD_NUM];//所有节点的地址,作为数字存储更方便比较
	WORD wAddrPos;//地址缓存区的写入指针

	WORD wSlaveNodRdSN;//读取的从节点序号
	WORD wNeedReadNodTotalNum;//需要读取的节点数量
	BYTE byRdNodNumNow;//现在需要读取的节点数量
}ST_RECV_NOD_INFOR;

typedef struct TYPE_ST_FLASH_INFOR//接收节点信息
{
	UINT64 U64FlashAddrs[MAX_NOD_NUM];//所有节点的地址,作为数字存储更方便比较
	WORD wAddrPos;//地址缓存区的写入指针
}ST_FLASH_INFOR;


typedef struct TYPDEF_ST_COM_BUF_INFOR
{
	INT16U ReadPos;//读指针
	INT16U WritePos;//写指针，一旦在解析的时候获取了正确的一帧数据之后，解析到写指针的话，则读写指针同时回零
	INT16U wFrameLength;//一帧长度
}ST_COM_BUF_INFOR;

typedef struct TYPDEF_ST_COM_BUF
{
	ST_COM_BUF_INFOR stInfor;
	INT8U m_BufRcv[MAX_BUF_LENGTH];
}ST_COM_BUF;

#define ADD_SALVE_NODE_NUM_IN_ADT 200
#define DEL_SALVE_NODE_NUM_IN_ADT 100//删除数量不能超过写入的数量
#define FINAL_ADD_SAVLE_NUM_1TIME_IN_ADT   (ADD_SALVE_NODE_NUM_IN_ADT - DEL_SALVE_NODE_NUM_IN_ADT)
typedef struct TYPDEF_ST_ADD_DEL_NOD_TEST
{
	BYTE del_node_num;//删除从节点数量

	BYTE before_del_pos;//在写入的节点，开始删除节点的前一个节点位置，即剩下的前段节点的最后一个节点       这两个参数都是以1-200的区间来说的，其他区间按间隔类推
	BYTE after_del_pos;//在写入的节点，删除节点的最后一个节点的后一个节点位置，即剩下的后段节点的开始节点

	WORD nodCounter;//ADT 测试时，地址与节点数不一致
}ST_ADD_DEL_NOD_TEST;

class CMainTestFrame;
class CFrameSetNet;
class CFrame3762;
//class CChildWnd13762;
class CForm698;
class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();
public://公共参数
	CString m_data;
	CString m_dataMessage;
	INT8U m_376seq;
	CFont m_Font70;
	CFont m_Font100;
	CFont m_Font120;
	CString m_strSysDateTime;
	CString	m_strSysDateTime_rx;
	CString	m_strSysDateTime_tx;
	CString m_strSysTime;
	CStringList m_FenzuFnList;
	INT8U m_HostNodeAddress[6];
	CString m_strMAddress;
	CString GetRecvErrName(INT8U nChoose);
	CString GetAckErrName(INT8U nChoose);
public://菜单参数
	bool m_bCKQ;
	bool m_bJZQ;
	bool m_bsetopen;
	bool m_bsetclos;
	INT8U m_nChooseView;
public://南网判断参数
	CString m_PeiZhi;
	CString m_PeiZhi_db;
	int NW_OR_GW;
public://状态栏参数
	CMFCStatusBar     m_wndStatusBar;
	BOOL LoadStatusBar();
	void SetStatusBat(CString strPort);
public://串口参数
	bool m_bCommunictStop;
	CWinThread* m_pThread;  // 代表辅助线程
	volatile BOOL m_bConnected;  //串口是否联接
	volatile HWND m_hTermWnd;    //保存视图的窗口句柄
	volatile HANDLE m_hPostMsgEvent; // 用于WM_COMMNOTIFY消息的事件对象
	OVERLAPPED m_osRead, m_osWrite; // 用于重叠读/写	
	volatile HANDLE hCom;  //COM口句柄
	void SendBufToCOMM(INT8U * sendbuf,INT16U sendLen , INT8U nType = 0);
	void BF_SendBufToCOMM(INT8U * sendbuf,INT16U sendLen , INT8U nType = 0);
	//cSerBuf_LoopRcv  m_loopRcv64507;
	//cSerBuf_LoopRcv  m_loopRcv13762;
	DWORD ReadComm(INT8U *buf, DWORD dwLength);//从串口中接收数据，每次一个字节
	CString GetCommMessage(CString strPort, CString strBaud , CString strParity , CString strDatabit, CString strStopbit);//通过串口信息编写成信息串
// 窗口参数
public:
	CMainTestFrame * m_pMainTestFrame;
	CFrameSetNet * m_pFrameNetWork;//子窗口对象指针
	bool m_bNetWork;//判断子窗口是否打开
	bool m_bNetWorkOpen;//判断子窗口是否打开
	CFrame3762 * m_pFrame3762;
	bool  m_bFrame3762;
	CAccessData m_access;
	CForm698 * m_pFrame698;
	bool  m_bFrame698;
public://网络子窗口内公共参数
	int m_nConnectType;
// 特性
public://日志
	bool bAutoTestRunCmd;//线程运行或者停止的标识
	unsigned char getFn(ST_Fn stFn);
	void Creat_File();
	void Close_File();
public:
	CSplitterWnd m_litterWnd;
// 操作
public:
	CTools m_tools;
	int m_nCopyFrame;
	CFrameShowWnd m_FrameShowWnd;
	CFrameShowWndTree mm_FrameShowWndTree;
	void InsertItemToOnlineList(CString strTableName );
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	
	CMFCToolBarImages m_UserImages;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg LRESULT OnComm(WPARAM wParam, LPARAM lParam);
	afx_msg void OnConnectOpen();
	afx_msg void OnConnectClose();
	afx_msg void OnNetwortOpen();
	afx_msg void OnUpdateConnectOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConnectClose(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void On3762Open();
	afx_msg void OnFrameshow();
	afx_msg void OnCopyframe();
	afx_msg void OnClose();
//	afx_msg void OnIdrRbmenuMeterr();
	afx_msg void OnJzq();
	afx_msg void OnUpdateJzq(CCmdUI *pCmdUI);
	afx_msg void OnCkq20();
	afx_msg void OnUpdateCkq20(CCmdUI *pCmdUI);
};


