// CKQViewTabErrMod.cpp : 实现文件
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "CKQViewTabErrMod.h"
#include "MainFrm.h"
#include "SimJzq.h"
extern CSimJzq  gSimJzq;
// CCKQViewTabErrMod

IMPLEMENT_DYNCREATE(CCKQViewTabErrMod, CFormView)

CCKQViewTabErrMod::CCKQViewTabErrMod()
	: CFormView(CCKQViewTabErrMod::IDD)
{

}

CCKQViewTabErrMod::~CCKQViewTabErrMod()
{
}

void CCKQViewTabErrMod::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_WHITELIST, m_checkWhite);
	DDX_Control(pDX, IDC_CHECK_METLIST, m_checkMet);
	DDX_Control(pDX, IDC_STATIC_SUCCESS, m_staticInNet);
	DDX_Control(pDX, IDC_STATIC_UNSEND, m_staticUnNet);
	//DDX_Control(pDX, IDC_STATIC_SENDING, m_staticLostNet);
	DDX_Control(pDX, IDC_STATIC_UNSEND2, m_staticUnWhite);
}

BEGIN_MESSAGE_MAP(CCKQViewTabErrMod, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCKQViewTabErrMod::OnBnClickedButtonClear)
	ON_COMMAND(ID_MODERR_UPDATA, &CCKQViewTabErrMod::OnModerrUpdata)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CCKQViewTabErrMod 诊断

#ifdef _DEBUG
void CCKQViewTabErrMod::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCKQViewTabErrMod::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCKQViewTabErrMod 消息处理程序

HBRUSH CCKQViewTabErrMod::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_SUCCESS:
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT); 
		hbr =  CreateSolidBrush(RGB(0,128,0));//
		break;
	//case IDC_STATIC_SENDING:
	//	pDC->SetTextColor(RGB(255, 255, 255));
	//	pDC->SetBkMode(TRANSPARENT); 
	//	hbr =  CreateSolidBrush(RGB(195,195,195));
	//	break;
	case IDC_STATIC_UNSEND:
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT); 
		hbr =  CreateSolidBrush(RGB(255,0,0));
		break;
	case IDC_STATIC_UNSEND2:
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT); 
		hbr =  CreateSolidBrush(RGB(0,128,128));
		break;
	}
	return hbr;
}

void CCKQViewTabErrMod::SetNewFont()
{
	LOGFONT lf;  //逻辑字体结构
	::ZeroMemory(&lf,sizeof(lf));
	lf.lfHeight = 20;
	lf.lfWidth= 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = FW_BOLD;
	lf.lfItalic = FALSE;
	lf.lfUnderline = FALSE;
	lf.lfStrikeOut= FALSE;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
	m_fontStatic.CreateFontIndirect(&lf);
}

void CCKQViewTabErrMod::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CRect rect;
	CRect rect1;
	GetClientRect(rect1);
	GetDlgItem(IDC_BUTTON_CLEAR)->GetWindowRect(rect);
	ScreenToClient(&rect);
	rect1.left += 10;
	rect1.top = rect.bottom + 10;
	rect1.right -= 10;
	rect1.bottom -= 10;
	m_listData.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_OWNERDRAWFIXED ,rect1,this,IDC_LISTUPDATAMSG);
	m_listData.InsertColumn(0,_T(""),LVCFMT_LEFT,50);
	m_listData.InsertColumn(1,_T("MAC地址"),LVCFMT_CENTER,150);
	m_listData.InsertColumn(2,_T("TEI"),LVCFMT_CENTER,50);
	m_listData.InsertColumn(3,_T("模块状态"),LVCFMT_CENTER,150);
	m_listData.InsertColumn(4,_T("地理位置"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(5,_T("电表地址"),LVCFMT_CENTER,150);
	m_listData.InsertColumn(6,_T("模块类型"),LVCFMT_CENTER,200);
	m_listData.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listData.m_nChooseList = 4;

	SetNewFont();
	m_staticInNet.SetFont(&m_fontStatic);
	m_staticUnNet.SetFont(&m_fontStatic);
	//m_staticLostNet.SetFont(&m_fontStatic);
	m_staticUnWhite.SetFont(&m_fontStatic);
}


void CCKQViewTabErrMod::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CCKQViewTabErrMod::InsertItemToList(CString strMAC , CString strTEI , CString strState , CString strLoca , CString strAddress , CString strType)
{
	CString strNumb;
	int n = 0;
	n = m_listData.GetItemCount();
	strNumb.Format(_T("%d") , n + 1);
	m_listData.InsertItem(n , strNumb);
	m_listData.SetItemText(n , 1 , strMAC.Mid(0 , 2) + _T(":") + strMAC.Mid(2 , 2) + _T(":") + strMAC.Mid(4 , 2) + _T(":") + strMAC.Mid(6 , 2) + _T(":") + strMAC.Mid(8 , 2) + _T(":") + strMAC.Mid(10 , 2));
	m_listData.SetItemText(n , 2 , strTEI);
	m_listData.SetItemText(n , 3 , strState);
	m_listData.SetItemText(n , 4 , strLoca);
	m_listData.SetItemText(n , 5 , strAddress);
	switch(_ttoi(strType))
	{
	case 1:
		break;
	case 2:
		m_listData.SetItemText(n , 6 , _T("集中器载波模块"));
		break;
	case 3:
		break;
	case 4:
		if (strMAC.Find(_T("EBEBEBEBEB")) != -1 )
		{
			m_listData.SetItemText(n , 6 , _T("抄控器载波模块"));
		} 
		else
		{
			m_listData.SetItemText(n , 6 , _T("单相表载波模块"));
		}
		break;
	}
	m_listData.EnsureVisible(n,FALSE);
	m_listData.RedrawItems(n,n);
}

DWORD WINAPI ThreadSendModERR (PVOID pParam) 
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewTabErrMod * pView = (CCKQViewTabErrMod *)pParam;
	INT16U u16BeginNumb_Node = 1;
	INT8U SendDatabuf[10];
	INT8U ack = 0 , u8SendAFN = 0 ,AddrBuf[7] , u8ReadCount_Node = 0 , n = 0 , temp8 = 0;
	INT16U SendDatalen = 0 ,temp16_Node = 0 , u16Numb = 0;
	CString strAllTPdata = _T("") , strMAC = _T("") , strWhere = _T("");
	CString strNumb , strSTAMsg[1024] , strlist[10];
	int nlistNumb = 0 , nlistUN = 0 , nInNetNumb = 0 , nUnNetNumb = 0 , nLostNumb = 0 , nUnWhiteNumb = 0;
	sPartQGDW376_2CreatFrame ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;

	sPartQCSG376_2CreatFrame ptSendQCSG376_2;//南网
	sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2;

	pView->m_listData.DeleteAllItems();
	//pView->m_access.DelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , _T(""));
	//pView->m_access.SetCopyTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPShow") , _T("TPMODERR"));
	pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , _T(""));
	pView->m_access.SetCopyTable(pMain->m_PeiZhi_db, _T("TPShow") , _T("TPMODERR"));
	pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16_Node , true);
	//查询白名单状态


	//if (pMain->NW_OR_GW==1){ //南网标准
	//	ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0xF0 , FN_F0_F17 , SendDatabuf , SendDatalen , ptSendQCSG376_2 , ptRecvQCSG376_2 , ptRecvQCSG376_2);
	//	if (ack != 0) return 0;
	//	if (ptRecvQCSG376_2.s_RcvDataBuf[0] == 0x55)
	//	{
	//		pView->m_checkWhite.SetCheck(TRUE);
	//		pView->m_checkMet.SetCheck(TRUE);
	//	}
	//	else
	//	{
	//		pView->m_checkWhite.SetCheck(FALSE);
	//		pView->m_checkMet.SetCheck(FALSE);
	//	}
	//	//查询白名单信息
	//	pView->InsertItemToList(pMain->m_strMAddress , _T("1") , _T("入网") , _T("") , _T("无") , _T("2"));
	//	ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F1 , SendDatabuf , SendDatalen , ptSendQCSG376_2 , ptRecvQCSG376_2 , ptRecvQCSG376_2);
	//	if (ack != 0) return 0;
	//	temp16_Node = ptRecvQCSG376_2.s_RcvDataBuf[1] << 8 | ptRecvQCSG376_2.s_RcvDataBuf[0];
	//	while(temp16_Node)
	//	{
	//		u16BeginNumb_Node += u8ReadCount;
	//		if (temp16_Node >10)
	//		{
	//			u8ReadCount = 10;
	//		}
	//		else
	//		{
	//			u8ReadCount = temp16_Node;
	//		}
	//		temp16_Node -= u8ReadCount;
	//		SendDatalen = 3;
	//		SendDatabuf[0] = (INT8U)u16BeginNumb_Node;
	//		SendDatabuf[1] = (INT8U)(u16BeginNumb_Node>>8);
	//		SendDatabuf[2] = u8ReadCount;
	//		ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F2 , SendDatabuf , SendDatalen , ptSendQCSG376_2, ptRecvQCSG376_2 , ptRecvQCSG376_2);
	//		if (ack != 0) return 0;

	//		temp8 = ptRecvQCSG376_2.s_RcvDataBuf[2];
	//		for (n = 0; n < temp8; n++)
	//		{
	//			strMAC = pView->m_tools._buf16tostr16(&ptRecvQCSG376_2.s_RcvDataBuf[3 + 8 * n] , 6 , false , true);
	//			strWhere = _T("TP_MAC='") + strMAC + _T("'");
	//			pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
	//			//pView->m_access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
	//			if (nlistNumb == 0)
	//			{
	//				nUnNetNumb += 1;
	//				pView->InsertItemToList(strMAC , _T("无") , _T("未入网") , _T("") , _T("未知") , _T(""));
	//			}
	//			else
	//			{
	//				nInNetNumb += 1;
	//				pView->m_tools.Split(strSTAMsg[0] , _T("$") , strlist , nlistNumb);
	//				pView->InsertItemToList(strMAC , strlist[0] , _T("入网") , _T("") , strMAC , strlist[1]);
	//				pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , strWhere);
	//				//pView->m_access.DelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , strWhere);
	//			}
	//		}
	//	}
	//}

	//else{
		ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0xF0 , F17 , SendDatabuf , SendDatalen , ptSendQGDW376_2 , ptRecvQGDW376_2 , ptRecvQGDW376_2);
		if (ack != 0) return 0;
		if (ptRecvQGDW376_2.s_RcvDataBuf[0] == 0x55)
		{
			pView->m_checkWhite.SetCheck(TRUE);
			pView->m_checkMet.SetCheck(TRUE);
		}
		else
		{
			pView->m_checkWhite.SetCheck(FALSE);
			pView->m_checkMet.SetCheck(FALSE);
		}
		//查询白名单信息
		pView->InsertItemToList(pMain->m_strMAddress , _T("1") , _T("入网") , _T("") , _T("无") , _T("2"));
		ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F1 , SendDatabuf , SendDatalen , ptSendQGDW376_2 , ptRecvQGDW376_2 , ptRecvQGDW376_2);
		if (ack != 0) return 0;
		temp16_Node = ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | ptRecvQGDW376_2.s_RcvDataBuf[0];
		while(temp16_Node)
		{
			u16BeginNumb_Node += u8ReadCount_Node;
			if (temp16_Node >10)
			{
				u8ReadCount_Node = 10;
			}
			else
			{
				u8ReadCount_Node = temp16_Node;
			}
			temp16_Node -= u8ReadCount_Node;
			SendDatalen = 3;
			SendDatabuf[0] = (INT8U)u16BeginNumb_Node;
			SendDatabuf[1] = (INT8U)(u16BeginNumb_Node>>8);
			SendDatabuf[2] = u8ReadCount_Node;
			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F2 , SendDatabuf , SendDatalen , ptSendQGDW376_2, ptRecvQGDW376_2 , ptRecvQGDW376_2);
			if (ack != 0) return 0;

			temp8 = ptRecvQGDW376_2.s_RcvDataBuf[2];
			for (n = 0; n < temp8; n++)
			{
				strMAC = pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[3 + 8 * n] , 6 , false , true);
				strWhere = _T("TP_MAC='") + strMAC + _T("'");
				pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
				//pView->m_access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
				if (nlistNumb == 0)
				{
					nUnNetNumb += 1;
					pView->InsertItemToList(strMAC , _T("无") , _T("未入网") , _T("") , _T("未知") , _T(""));
				}
				else
				{
					nInNetNumb += 1;
					pView->m_tools.Split(strSTAMsg[0] , _T("$") , strlist , nlistNumb);
					pView->InsertItemToList(strMAC , strlist[0] , _T("入网") , _T("") , strMAC , strlist[1]);
					pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , strWhere);
					//pView->m_access.DelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , strWhere);
				}
			}
		}
	//}////这里标记


	pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T("TP_MAC,TP_TEI,TP_ROLE") , _T("") , strSTAMsg , nlistNumb);
	//pView->m_access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , _T("TP_MAC,TP_TEI,TP_ROLE") , _T("") , strSTAMsg , nlistNumb);
	for (n = 0; n < nlistNumb; n++)
	{
		pView->m_tools.Split(strSTAMsg[n] , _T("$") , strlist , nlistUN);
		if (pView->m_tools._strDaoxu(strlist[0]) != pMain->m_strMAddress)
		{
			nUnWhiteNumb += 1;
			if (strlist[0].Find(_T("EBEBEBEBEB")) == -1 )
			{
				pView->InsertItemToList(strlist[0] , strlist[1] , _T("未在白名单") , _T("") , strlist[0] , strlist[2]);
			}
		}
	}
	//查询掉线信息


	//统计数量 = 0 , nUnNetNumb , nLostNumb , nUnWhiteNumb = 0
	strNumb.Format(_T("%d") , nInNetNumb + 1);
	pView->m_staticInNet.SetWindowText(_T("入网（") + strNumb + _T(")"));
	strNumb.Format(_T("%d") , nUnNetNumb);
	pView->m_staticUnNet.SetWindowText(_T("未入网（") + strNumb + _T(")"));
	strNumb.Format(_T("%d") , nLostNumb);
	//pView->m_staticLostNet.SetWindowText(_T("离线（") + strNumb + _T(")"));
	//strNumb.Format(_T("%d") , nUnWhiteNumb);
	pView->m_staticUnWhite.SetWindowText(_T("未在白名单（") + strNumb + _T(")"));
	return 0;
}

void CCKQViewTabErrMod::OnModerrUpdata()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMain->m_bConnected != TRUE)
	{
		AfxMessageBox(_T("请先打开串口！"));
		return;
	}
	//if (pMain->m_strMAddress == "")
	//{
	//	AfxMessageBox(_T("请先连接CCO！"));
	//#if (0==LOOPTEST)
	//		 return;
	//		#endif
	//}

	m_hThreadsend=CreateThread (NULL,0,ThreadSendModERR,this,0,NULL);
	CloseHandle(m_hThreadsend);
}

