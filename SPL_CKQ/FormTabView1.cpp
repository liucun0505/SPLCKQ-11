// FormTabView1.cpp : 实现文件
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "FormTabView1.h"
#include "MainFrm.h"
#include "SimJzq.h"
extern CSimJzq  gSimJzq;
// CFormTabView1

IMPLEMENT_DYNCREATE(CFormTabView1, CFormView)

CFormTabView1::CFormTabView1()
	: CFormView(CFormTabView1::IDD)
	, m_nChooseType(0)
{
	//  m_nFindType = 0;
}

CFormTabView1::~CFormTabView1()
{
}

void CFormTabView1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BUTTON2, m_btnTest1);
	DDX_Radio(pDX, IDC_RADIO_TYPE, m_nChooseType);
	DDX_Control(pDX, IDC_LIST_CKQ, m_listCKQ);
	DDX_Control(pDX, IDC_EDIT_CCOADDR, m_editCCOAddress);
	DDX_Control(pDX, IDC_BUTTON_LINK, m_btnLink);
	DDX_Control(pDX, IDC_RADIO_TYPE, m_radioType);
}

BEGIN_MESSAGE_MAP(CFormTabView1, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CFormTabView1::OnBnClickedButtonFind)
	ON_WM_CREATE()
	ON_NOTIFY(NM_CLICK, IDC_LIST_CKQ, &CFormTabView1::OnNMClickListCkq)
	ON_BN_CLICKED(IDC_BUTTON_LINK, &CFormTabView1::OnBnClickedButtonLink)
END_MESSAGE_MAP()


// CFormTabView1 诊断

#ifdef _DEBUG
void CFormTabView1::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormTabView1::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormTabView1 消息处理程序








void CFormTabView1::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_listCKQ.InsertColumn(0,_T("状态"),LVCFMT_LEFT,100);
	m_listCKQ.InsertColumn(1,_T("CCO地址"),LVCFMT_LEFT,150);
	m_listCKQ.InsertColumn(2,_T("STA地址"),LVCFMT_LEFT,150);
	m_listCKQ.InsertColumn(3,_T("SNID"),LVCFMT_LEFT,50);
	m_listCKQ.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
}
//执行线程
DWORD WINAPI ThreadSendFindlist (PVOID pParam) 
{
	//王会元标记
	//此处为点击“搜网”执行  
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CFormTabView1 * pView = (CFormTabView1 *)pParam;
	INT16U u16temp = 0 , u16BeginNumb = 0;
	INT8U SendDatabuf[10];
	INT8U ack = 0 , u8SendAFN = 0 ,u8ReadCount = 0 , u8temp = 0 , u8tempAll = 0 , n = 0;
	INT16U SendDatalen = 0 ,temp16 = 0;
	CString strdata = _T("000014");
    if (pMain->NW_OR_GW==1){ //南网标准
		sPartQCSG376_2CreatFrame ptSendQCSG376_2;
		sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2;

		if (pView->m_radioType.GetCheck())
		{
			ack = gSimJzq.HostSendRcv376_2Buf(0xF0 , FN_F0_F30 , SendDatabuf , SendDatalen ,ptSendQCSG376_2 , ptRecvQCSG376_2);
		}
		else
		{
			ack = gSimJzq.HostSendRcv376_2Buf(0xF0 ,  FN_F0_F31 , SendDatabuf , SendDatalen ,ptSendQCSG376_2 , ptRecvQCSG376_2);
		}
		switch(ack)
		{
		case 0x00://成功
			u8temp = ptRecvQCSG376_2.s_RcvDataBuf[0];
			if (pView->m_radioType.GetCheck())
			{
				for (n = 0; n < u8temp; n++)
				{
					strdata = pView->m_tools._buf16tostr16(&ptRecvQCSG376_2.s_RcvDataBuf[1 + 7*n] , 6 , false , true);
					pView->m_listCKQ.InsertItem(pView->m_listCKQ.GetItemCount() , _T("未连接"));
					pView->m_listCKQ.SetItemText(pView->m_listCKQ.GetItemCount() -1 ,1 , strdata);
					pView->m_listCKQ.SetItemText(pView->m_listCKQ.GetItemCount() -1 ,3 , pView->m_tools._buf16tostr16(&ptRecvQCSG376_2.s_RcvDataBuf[7 + 7*n] , 1));
				}
			}
			else
			{
				for (n = 0; n < u8temp; n++)
				{
					strdata = pView->m_tools._buf16tostr16(&ptRecvQCSG376_2.s_RcvDataBuf[7 + 13*n] , 6 , false , true);
					pView->m_listCKQ.InsertItem(pView->m_listCKQ.GetItemCount() , _T("未连接"));
					pView->m_listCKQ.SetItemText(pView->m_listCKQ.GetItemCount() -1 ,2 , strdata);
					pView->m_listCKQ.SetItemText(pView->m_listCKQ.GetItemCount() -1 ,1 , pView->m_tools._buf16tostr16(&ptRecvQCSG376_2.s_RcvDataBuf[1 + 13*n] , 6 , false , true));
					pView->m_listCKQ.SetItemText(pView->m_listCKQ.GetItemCount() -1 ,3 , pView->m_tools._buf16tostr16(&ptRecvQCSG376_2.s_RcvDataBuf[13 + 13*n] , 1));
				}
			}
			break;
		}
	}
	else{
		sPartQGDW376_2CreatFrame ptSendQGDW376_2;
		sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;

		if (pView->m_radioType.GetCheck())
		{
			ack = gSimJzq.HostSendRcv376_2Buf(0xF0 , F30 , SendDatabuf , SendDatalen ,ptSendQGDW376_2 , ptRecvQGDW376_2);
		}
		else
		{
			ack = gSimJzq.HostSendRcv376_2Buf(0xF0 , F31 , SendDatabuf , SendDatalen ,ptSendQGDW376_2 , ptRecvQGDW376_2);
		}

		switch(ack)
		{
		case 0x00://成功
			u8temp = ptRecvQGDW376_2.s_RcvDataBuf[0];
			if (pView->m_radioType.GetCheck())
			{
				for (n = 0; n < u8temp; n++)
				{
					strdata = pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[1 + 7*n] , 6 , false , true);
					pView->m_listCKQ.InsertItem(pView->m_listCKQ.GetItemCount() , _T("未连接"));
					pView->m_listCKQ.SetItemText(pView->m_listCKQ.GetItemCount() -1 ,1 , strdata);
					pView->m_listCKQ.SetItemText(pView->m_listCKQ.GetItemCount() -1 ,3 , pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[7 + 7*n] , 1));
				}
			}
			else
			{
				for (n = 0; n < u8temp; n++)
				{
					strdata = pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[7 + 13*n] , 6 , false , true);
					pView->m_listCKQ.InsertItem(pView->m_listCKQ.GetItemCount() , _T("未连接"));
					pView->m_listCKQ.SetItemText(pView->m_listCKQ.GetItemCount() -1 ,2 , strdata);
					pView->m_listCKQ.SetItemText(pView->m_listCKQ.GetItemCount() -1 ,1 , pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[1 + 13*n] , 6 , false , true));
					pView->m_listCKQ.SetItemText(pView->m_listCKQ.GetItemCount() -1 ,3 , pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[13 + 13*n] , 1));
				}
			}
			break;
		}
	}
	return 0;
}

void CFormTabView1::OnBnClickedButtonFind()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMain->m_bConnected == TRUE)
	{
		m_listCKQ.DeleteAllItems();
		m_btnLink.SetWindowTextW(_T("连接"));
		m_editCCOAddress.SetWindowText(_T(""));
		pMain->m_strMAddress = _T("");
		m_hThreadsend=CreateThread (NULL,0,ThreadSendFindlist,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("请先打开串口！"));
	}
}

void CFormTabView1::OnNMClickListCkq(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CString strType = _T("");
	for(int m_n=0; m_n<m_listCKQ.GetItemCount(); m_n++)
	{
		if( m_listCKQ.GetItemState(m_n,LVIS_SELECTED) == LVIS_SELECTED )
		{
			strType = m_listCKQ.GetItemText(m_n , 0);
			if (strType == "未连接")
			{
				m_btnLink.SetWindowTextW(_T("连接"));
			}
			else
			{
				m_btnLink.SetWindowTextW(_T("断开"));
			}
			if (m_radioType.GetCheck())
			{
				m_editCCOAddress.SetWindowText(m_listCKQ.GetItemText(m_n,1));
			}
			else
			{
				m_editCCOAddress.SetWindowText(m_listCKQ.GetItemText(m_n,2));
			}
			m_nChooselist = m_n;
			break;
		}
	}
	*pResult = 0;
}

DWORD WINAPI ThreadSendConnect (PVOID pParam) 
{
	//王会元标记
	//此处为点击“搜网”执行  
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CFormTabView1 * pView = (CFormTabView1 *)pParam;
	CString strAddre , strBtnName;
	INT16U u16temp = 0 , u16BeginNumb = 0;
	INT8U SendDatabuf[10];
	INT8U ack = 0 , u8SendAFN = 0 ,u8ReadCount = 0 , u8temp = 0 , u8tempAll = 0 , n = 0;
	INT16U SendDatalen = 1 ,temp16 = 0;
    if (pMain->NW_OR_GW==1){ //南网标准
		sPartQCSG376_2CreatFrame ptSendQCSG376_2;
		sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2;

		pView->m_btnLink.GetWindowTextW(strBtnName);
		pView->m_editCCOAddress.GetWindowTextW(strAddre);
		if (strAddre == "")
		{
			AfxMessageBox(_T("请选择集中器"));
			return 0;
		}
		if (strBtnName == "连接")
		{
			SendDatabuf[0] = _ttoi(pView->m_listCKQ.GetItemText(pView->m_nChooselist , 3));
		}
		else
		{
			SendDatabuf[0] = 0;
		}
		ack = gSimJzq.HostSendRcv376_2Buf(0xF0 , FN_F0_F32 , SendDatabuf , SendDatalen ,ptSendQCSG376_2 , ptRecvQCSG376_2);
		if (ack == 0)
		{
			if (strBtnName == "连接")
			{
				pMain->m_strMAddress = strAddre;
				pView->m_listCKQ.SetItemText(pView->m_nChooselist , 0 , _T("已连接"));
				pView->m_btnLink.SetWindowTextW(_T("断开"));
				pMain->m_nConnectType = CONNECTCCO;
				
			}
			else
			{
				pMain->m_strMAddress = _T("");
				pView->m_listCKQ.SetItemText(pView->m_nChooselist , 0 , _T("未连接"));
				pView->m_btnLink.SetWindowTextW(_T("连接"));
				pMain->m_nConnectType = CONNECTCKQ;
				
			}
		}

	}
	else{
		sPartQGDW376_2CreatFrame ptSendQGDW376_2;
		sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;

		pView->m_btnLink.GetWindowTextW(strBtnName);
		pView->m_editCCOAddress.GetWindowTextW(strAddre);
		if (strAddre == "")
		{
			AfxMessageBox(_T("请选择集中器"));
			return 0;
		}
		if (strBtnName == "连接")
		{
			SendDatabuf[0] = _ttoi(pView->m_listCKQ.GetItemText(pView->m_nChooselist , 3));
		}
		else
		{
			SendDatabuf[0] = 0;
		}
		ack = gSimJzq.HostSendRcv376_2Buf(0xF0 , F32 , SendDatabuf , SendDatalen ,ptSendQGDW376_2 , ptRecvQGDW376_2);
		if (ack == 0)
		{
			if (strBtnName == "连接")
			{
				pMain->m_strMAddress = strAddre;
				pView->m_listCKQ.SetItemText(pView->m_nChooselist , 0 , _T("已连接"));
				pView->m_btnLink.SetWindowTextW(_T("断开"));
				pMain->m_nConnectType = CONNECTCCO;
				g_ConnectCCO = 1;
			}
			else
			{
				pMain->m_strMAddress = _T("");
				pView->m_listCKQ.SetItemText(pView->m_nChooselist , 0 , _T("未连接"));
				pView->m_btnLink.SetWindowTextW(_T("连接"));
				pMain->m_nConnectType = CONNECTCKQ;
				g_ConnectCCO = 0;
			}
		}
	}
	return 0;
}

void CFormTabView1::OnBnClickedButtonLink()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMain->m_bConnected == TRUE)
	{
		m_hThreadsend=CreateThread (NULL,0,ThreadSendConnect,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("请先打开串口！"));
	}
}
