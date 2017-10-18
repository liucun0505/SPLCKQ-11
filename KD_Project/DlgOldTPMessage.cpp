// DlgOldTPMessage.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DlgOldTPMessage.h"
#include "afxdialogex.h"

#include "CKQViewTPShowOldData.h"

// CDlgOldTPMessage 对话框

IMPLEMENT_DYNAMIC(CDlgOldTPMessage, CDialogEx)

CDlgOldTPMessage::CDlgOldTPMessage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOldTPMessage::IDD, pParent)
{

}

CDlgOldTPMessage::~CDlgOldTPMessage()
{
}

void CDlgOldTPMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datetimeBegin);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_datetimeEnd);
	DDX_Control(pDX, IDC_LIST1, m_listShow);
	DDX_Control(pDX, IDC_CHECK_SHOW, m_checkShow);
}


BEGIN_MESSAGE_MAP(CDlgOldTPMessage, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SELECT, &CDlgOldTPMessage::OnBnClickedBtnSelect)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CDlgOldTPMessage::OnBnClickedBtnDelete)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CDlgOldTPMessage::OnBnClickedBtnClear)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgOldTPMessage 消息处理程序




BOOL CDlgOldTPMessage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CCKQViewTPShowOldData * pView = (CCKQViewTPShowOldData *)GetParentFrame();
	CTime   tm;
	tm=CTime::GetCurrentTime();
	m_datetimeBegin.SetTime(&tm);
	m_datetimeBegin.SetFormat(_T("yyyy-MM-dd   HH:mm:ss"));

	m_datetimeEnd.SetTime(&tm);
	m_datetimeEnd.SetFormat(_T("yyyy-MM-dd   HH:mm:ss"));
	m_listShow.InsertColumn(0 , _T("TP_TABNAME") , LVCFMT_CENTER , 200);
	m_listShow.InsertColumn(1 , _T("TP_MAC") , LVCFMT_CENTER , 200);
	m_listShow.InsertColumn(2 , _T("TP_TEI") , LVCFMT_CENTER , 100);
	m_listShow.InsertColumn(3 , _T("TP_PTEI") , LVCFMT_CENTER , 100);
	m_listShow.InsertColumn(4 , _T("TP_ROLE") , LVCFMT_CENTER , 100);
	m_listShow.InsertColumn(5 , _T("TP_TIER") , LVCFMT_CENTER , 100);
	m_listShow.InsertColumn(6 , _T("TP_QOS") , LVCFMT_CENTER , 100);
	m_listShow.InsertColumn(7 , _T("TP_STATUS") , LVCFMT_CENTER , 100);
	m_listShow.InsertColumn(8 , _T("TP_BY") , LVCFMT_CENTER , 100);
	m_listShow.InsertColumn(9 , _T("TP_SUCCESS") , LVCFMT_CENTER , 100);
	m_listShow.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CDlgOldTPMessage::KongjianSize(int nID, int cx, int cy, bool bComb)
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
		//rect.top=(int)(rect.top*((float)cy/(float)fcy)); 
		rect.bottom = (int)(rect.bottom*((float)cy/(float)fcy)) + nBottom;
		pWnd->MoveWindow(rect);//设置控件位置 
	}
}

void CDlgOldTPMessage::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(rect); 
	if (rect.right == 0 || rect.bottom == 0 )
	{
		return;
	}
	KongjianSize(IDC_BTN_CLEAR,rect.right,rect.bottom);
	KongjianSize(IDC_LIST1,rect.right,rect.bottom);
	GetClientRect(m_cRect);
}

void CDlgOldTPMessage::OnBnClickedBtnSelect()
{

	CCKQViewTPShowOldData * pView = (CCKQViewTPShowOldData *)GetParentFrame()->GetActiveView();
	pView->m_nShowNumb = 0;
	CTime tBeginTime , tEndTime;
	CString strBeginTime , strEndTime;
	m_datetimeBegin.GetTime(tBeginTime);
	m_datetimeEnd.GetTime(tEndTime); 
	strBeginTime = tBeginTime.Format(_T("%Y%m%d%H%M%S"));
	strBeginTime = strBeginTime.Mid(2);
	strEndTime = tEndTime.Format(_T("%Y%m%d%H%M%S"));
	strEndTime = strEndTime.Mid(2);

	m_listShow.DeleteAllItems();
	CString strlistData[1024];
	CString strlistValue[10];
	int nlistTable = 0 , nlistData = 0 , nlistValue = 0;
	int m = 0, n = 0, nlistNumb = 0;
	CString strTabName, strWhere = _T("HISTTPNAME>='") + strBeginTime + _T("' and HISTTPNAME<='") + strEndTime + _T("'");
	if (strBeginTime == strEndTime)
	{
		strWhere = _T("");
	}
	m_access.SelectDataFromTable(_T(".\\配置文件\\HistTPShow.accdb") , _T("HISTTPNAME") ,  _T("HISTTPNAME") , strWhere ,pView->m_strShowlist, pView->m_nShowNumb);
	for (n = 0; n < pView->m_nShowNumb; n++)
	{
		strTabName = pView->m_strShowlist[n].Mid(0 , pView->m_strShowlist[n].GetLength() - 1);
		pView->m_strShowlist[n] = strTabName;
		if (!m_checkShow.GetCheck())
		{
			m_listShow.InsertItem(n, strTabName);
		} 
		else
		{
			m_access.SelectDataFromTable(_T(".\\配置文件\\HistTPShow.accdb") , strTabName ,  _T("TP_MAC,TP_TEI,TP_PTEI,TP_ROLE,TP_TIER,TP_QOS,TP_STATUS,TP_BY,TP_READSUCCESS") , _T("") ,strlistData, nlistData);
			for (m = 0; m < nlistData; m++)
			{
				m_tools.Split(strlistData[m], _T("$"), strlistValue, nlistValue);
				nlistNumb = m_listShow.GetItemCount();
				m_listShow.InsertItem(nlistNumb, strTabName);
				m_listShow.SetItemText(nlistNumb, 1, strlistValue[0]);
				m_listShow.SetItemText(nlistNumb, 2, strlistValue[1]);
				m_listShow.SetItemText(nlistNumb, 3, strlistValue[2]);
				m_listShow.SetItemText(nlistNumb, 4, strlistValue[3]);
				m_listShow.SetItemText(nlistNumb, 5, strlistValue[4]);
				m_listShow.SetItemText(nlistNumb, 6, strlistValue[5]);
				m_listShow.SetItemText(nlistNumb, 7, strlistValue[6]);
				m_listShow.SetItemText(nlistNumb, 8, strlistValue[7]);
				m_listShow.SetItemText(nlistNumb, 9, strlistValue[8]);
			}
		}
	}
}

void CDlgOldTPMessage::OnBnClickedBtnDelete()
{
	if(6 == MessageBox(_T("注意：历史数据删除后将无法找回，是否继续删除？") , _T("删除列表历史数据") ,MB_YESNO))
	{
		CCKQViewTPShowOldData * pView = (CCKQViewTPShowOldData *)GetParentFrame()->GetActiveView();
		CString strWhere = _T("");
		for (int n = 0; n < pView->m_nShowNumb; n++)
		{
			strWhere = _T("HISTTPNAME='") + pView->m_strShowlist[n] + _T("'");
			m_access.DelectDataFromTable(_T(".\\配置文件\\HistTPShow.accdb") , _T("HISTTPNAME"), strWhere);
			m_access.DelectTable(_T(".\\配置文件\\HistTPShow.accdb") , pView->m_strShowlist[n]);
		}
		pView->m_nShowNumb = 0;
		m_listShow.DeleteAllItems();
	}
}
void CDlgOldTPMessage::OnBnClickedBtnClear()
{
	if(6 == MessageBox(_T("注意：历史数据删除后将无法找回，是否继续删除？") , _T("删除所有历史数据") ,MB_YESNO))
	{
		CString strTabName;
		CString strlistTable[1024];
		CString strlistData[1024];
		CString strlistValue[10];
		int nlistTable = 0 , nlistData = 0 , nlistValue = 0;
		int m = 0, n = 0, nlistNumb = 0;
		m_access.SelectDataFromTable(_T(".\\配置文件\\HistTPShow.accdb") , _T("HISTTPNAME") ,  _T("HISTTPNAME") , _T("") ,strlistTable, nlistTable);
		for (n = 0; n < nlistTable; n++)
		{
			strTabName = strlistTable[n].Mid(0 , strlistTable[n].GetLength() - 1);
			m_access.DelectTable(_T(".\\配置文件\\HistTPShow.accdb") , strTabName);
		}
		m_access.DelectDataFromTable(_T(".\\配置文件\\HistTPShow.accdb") , _T("HISTTPNAME") ,_T(""));
		m_listShow.DeleteAllItems();
	}
}



