// NetViewPToP.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "NetViewPToP.h"
#include "CDTL2007.h"
#include "MainFrm.h"
#include "SimJzq.h"
extern CSimJzq  gSimJzq;

// CNetViewPToP

IMPLEMENT_DYNCREATE(CNetViewPToP, CFormView)

CNetViewPToP::CNetViewPToP()
	: CFormView(CNetViewPToP::IDD)
{

}

CNetViewPToP::~CNetViewPToP()
{
}

void CNetViewPToP::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MAC1, m_editMAC1);
	DDX_Control(pDX, IDC_COMBO_645, m_comb645);
	DDX_Control(pDX, IDC_EDIT_SEND645, m_editSend645);
	DDX_Control(pDX, IDC_EDIT_RECV645, m_editRecv645);
	DDX_Control(pDX, IDC_EDIT4, m_editAddr);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSend);
}

BEGIN_MESSAGE_MAP(CNetViewPToP, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO_645, &CNetViewPToP::OnCbnSelchangeCombo645)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CNetViewPToP::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CNetViewPToP 诊断

#ifdef _DEBUG
void CNetViewPToP::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CNetViewPToP::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CNetViewPToP 消息处理程序


void CNetViewPToP::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_editAddr.SetLimitText(12);
	m_editAddr.SetWindowTextW(_T("AAAAAAAAAAAA"));
	m_comb645.AddString(_T("读地址"));
	m_comb645.AddString(_T("读电量"));
}


void CNetViewPToP::OnCbnSelchangeCombo645()
{
	cDTL2007 dtl645;
	Stu_Dtl2007 stu645;
	sDtl2007_Read stuCmdData;
	INT8U Addrebuf[6];
	INT8U Databuf[255];
	INT16U Datalen = 0;
	CString strAddr;
	m_editAddr.GetWindowTextW(strAddr);
	strAddr=strAddr.Left(12).Right(2)+strAddr.Left(10).Right(2)+strAddr.Left(8).Right(2)
		+strAddr.Left(6).Right(2)+strAddr.Left(4).Right(2)+strAddr.Left(2).Right(2) + strAddr.Left(2);
	m_tools._str16tobuf16(strAddr ,stu645.s_AmtBuf , Datalen );
	switch(m_comb645.GetCurSel())
	{
	case 0:
		dtl645.CodeReadAmtAdd(0 , Databuf , Datalen);
		m_editSend645.SetWindowTextW(m_tools._buf16tostr16(Databuf , Datalen ));
		break;
	case 1:
		dtl645.CodeReadDataCmd(0x00010000, stu645.s_AmtBuf, 0, stuCmdData);
		m_editSend645.SetWindowTextW(m_tools._buf16tostr16(stuCmdData.s_pDstCmdBuf, stuCmdData.s_vDstCmdLen ));
		break;
	}
}
DWORD WINAPI ThreadSendPTP (PVOID pParam) 
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CNetViewPToP *pView=(CNetViewPToP*)pParam;
	INT8U ack = 0 , u8SendAFN = 0 ,AddrBuf[7] , temp8 = 0;
	INT8U SendDatabuf[255];
	INT16U SendDatalen = 0;
	INT16U temp16 = 0;
	CString strAddr ,strData;
	sPartQGDW376_2CreatFrame ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;

	sPartQCSG376_2CreatFrame ptSendQCSG376_2;//南网
	sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2;


	pView->m_editMAC1.GetWindowTextW(strAddr);
	pView->m_editSend645.GetWindowTextW(strData);
	temp8 = wcslen(strData)/2;
	strData = _T("02") + pView->m_tools._buf16tostr16(&temp8 , 1) + strData;
	pView->m_tools._str16tobuf16(strData ,SendDatabuf , SendDatalen );
	pView->m_tools._str16tobuf16(strAddr ,AddrBuf , temp16 ,TRUE);



	if (pMain->NW_OR_GW==1){ //南网标准
		ack = gSimJzq.HostSendRcv376_2BufNode(AddrBuf , 0xF0 , FN_F0_F140 , SendDatabuf , SendDatalen , ptSendQCSG376_2 ,ptRecvQCSG376_2);

		switch(ack)
		{
		case 0:
			strData = pMain->m_strSysTime + _T("==>") + pView->m_tools._buf16tostr16(&ptRecvQCSG376_2.s_RcvDataBuf[2] , ptRecvQCSG376_2.s_RcvDataLen - 2)+ _T("\r\n");
			pView->m_editRecv645.ReplaceSel(strData);
			break;
   		case 0x30:
			break;
		default:
			break;
		}
	}
	else{
		ack = gSimJzq.HostSendRcv376_2BufNode(AddrBuf , 0x02 , F1 , SendDatabuf , SendDatalen , ptSendQGDW376_2 ,ptRecvQGDW376_2);

		switch(ack)
		{
		case 0:
			strData = pMain->m_strSysTime + _T("==>") + pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[2] , ptRecvQGDW376_2.s_RcvDataLen - 2)+ _T("\r\n");
			pView->m_editRecv645.ReplaceSel(strData);
			break;
		case 0x30:
			break;
		default:
			break;
		}
	}

	pView->m_btnSend.EnableWindow(TRUE);
	return 0;
}

void CNetViewPToP::OnBnClickedButtonSend()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();

	if (pMain->m_bConnected == TRUE)
	{
		m_btnSend.EnableWindow(FALSE);
		m_hThreadsend=CreateThread (NULL,0,ThreadSendPTP,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("请打开串口！"));
	}
}
