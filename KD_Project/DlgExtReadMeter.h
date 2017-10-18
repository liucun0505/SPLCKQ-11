#pragma once
#include "afxcmn.h"
#include <vector>
#include "Tools.h"
#include "afxwin.h"
#include "DlgFile.h"
#include "DialogSyncNodeFile.h"

#define TIMER_ID_CYCLE (200)
#define TIMER_ID_LAST (300)
#define RM_SUCCESS (0)
#define RM_NO06F2 (1)
#define RM_06F2SEQERR (2)
#define RM_00F1SEQERR (3)
#define RM_NOACK (4)
#define RM_UNKNOWNERR (255)
// DlgExtReadMeter dialog

struct s_NodeList
{
	
	CString node;
	INT8U prot_type;//协议类型
	INT8U is_met;//是否有上报,有： 1，没有 ： 0
	INT8U status;//状态，成功:1，失败：0
};




class DlgExtReadMeter : public CDialogEx
{
	DECLARE_DYNAMIC(DlgExtReadMeter)

public:
	DlgExtReadMeter(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgExtReadMeter();

// Dialog Data
	enum { IDD = IDD_DIALOG_READMT };



public:
	
	bool m_bTerminateButtun;//结束路由查表按钮

	CEdit m_editReadCycle;//抄表周期间隔
	double m_fcycle;
	CEdit m_editReadLast;//抄表持续时间
	double m_flast;
	bool m_bSettimer;//设置时钟标志
	CEdit m_ReadType;//抄表读取内容
	CEdit m_str645Frame;//要发送的645帧报文
	CEdit m_editShow;//打印内容
	CButton m_btnStartReadMT;
	CButton m_btnStopReadMT;
	CComboBox m_cbtnDi;

	CTools m_tools;


	sPartQGDW376_2CreatFrame m_ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame m_ptRecvQGDW376_2;

	INT32U m_Di;
	INT32U m_dotnum;//数据的小数个数
	CWinThread* MyThread;
	
	CEdit m_RmStatus;
	BOOL m_bReadMeterStatus;//路由工作状态
	CEdit m_RmTotal;
	INT32U m_nTotal;
	CEdit m_RmSuccess;
	INT32U m_nReadSuccess;
	CEdit m_RmFail;
	INT32U m_nReadFail;
	INT32U m_iRound;

	Dlgfile *dlgfile;
	Dlgfile *dlgsavenodefile;
	//Dlgfile *dlgsyncnodefile;
	DialogSyncNodeFile *dlgsyncnodefile;

	

	INT32U m_EventID;
	

	std::vector<s_NodeList> v_snodelist;
	std::vector<s_NodeList>::iterator iter_node,iter_end;
	std::vector <s_NodeList> v_nodejzq;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


	

public:
	int ReadMeter();
	void SetWindowText(CString strData);
	void SetWindowText(INT32U idata);
	void Update();
	BOOL OnInitDialog();
	void router_start();
	void router_suspend();
	void router_resume();
	BOOL router_status();
	INT32U ReadNodeNumber();
	bool ReadMasterMAC(INT8U MAC[6]);

	void PrintNodeTable();
	INT8U GetNodeTable(INT32U nTotal);
	UINT SyncNodeFile(INT16U nodenumperframe);
	UINT SaveNodeFile();

	INT8U MatchNode_CheckRepeat(CString SearchStaMac,INT16U &StaIndex);
	void SaveFailureNode();

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedButton1Rm();//重启路由
	afx_msg void OnBnClickedButton2Rm();//暂停路由
	afx_msg void OnBnClickedButton3Rm();//恢复路由
	afx_msg void OnBnClickedButton4Rm();//开始路由抄表
	afx_msg void OnBnClickedButton6Rm();//设置保存文件
	afx_msg void OnBnClickedButton5Rm();//结束路由抄表
	


	
	CEdit m_editRound;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton7();
};

static UINT ThreadReadMeter(LPVOID pParam);
static UINT ThreadSwitch(LPVOID pParam);
