// CKQViewTabErrMet.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "CKQViewTabErrMet.h"
#include "MainFrm.h"
#include "SimJzq.h"
extern CSimJzq  gSimJzq;

// CCKQViewTabErrMet

IMPLEMENT_DYNCREATE(CCKQViewTabErrMet, CFormView)

CCKQViewTabErrMet::CCKQViewTabErrMet()
	: CFormView(CCKQViewTabErrMet::IDD)
{

}

CCKQViewTabErrMet::~CCKQViewTabErrMet()
{
}

void CCKQViewTabErrMet::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_INNET, m_staticInNet);
	DDX_Control(pDX, IDC_STATIC_UNNET, m_staticUnNet);
	DDX_Control(pDX, IDC_STATIC_UNMETLIST, m_staticUnWhite);
}

BEGIN_MESSAGE_MAP(CCKQViewTabErrMet, CFormView)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_METERR_UPDATA, &CCKQViewTabErrMet::OnMeterrUpdata)
END_MESSAGE_MAP()


// CCKQViewTabErrMet 诊断

#ifdef _DEBUG
void CCKQViewTabErrMet::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCKQViewTabErrMet::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCKQViewTabErrMet 消息处理程序
HBRUSH CCKQViewTabErrMet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_INNET:
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT); 
		hbr =  CreateSolidBrush(RGB(0,128,0));//
		break;
	case IDC_STATIC_UNNET:
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT); 
		hbr =  CreateSolidBrush(RGB(255,0,0));
		break;
	case IDC_STATIC_UNMETLIST:
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT); 
		hbr =  CreateSolidBrush(RGB(0,128,128));
		break;
	}
	return hbr;
}
void CCKQViewTabErrMet::SetNewFont()
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
void CCKQViewTabErrMet::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CRect rect;
	CRect rect1;
	GetClientRect(rect1);
	GetDlgItem(IDC_STATIC_INNET)->GetWindowRect(rect);
	ScreenToClient(&rect);
	rect1.left += 10;
	rect1.top = rect.bottom + 10;
	rect1.right -= 10;
	rect1.bottom -= 10;
	m_listData.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_OWNERDRAWFIXED ,rect1,this,IDC_LISTUPDATAMSG);
	m_listData.InsertColumn(0,_T(""),LVCFMT_LEFT,50);
	m_listData.InsertColumn(1,_T("表地址"),LVCFMT_CENTER,150);
	m_listData.InsertColumn(2,_T("地理位置"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(3,_T("电表状态"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(4,_T("MAC地址"),LVCFMT_CENTER,150);
	m_listData.InsertColumn(5,_T("已发帧数"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(6,_T("已收帧数"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(7,_T("设备类型"),LVCFMT_CENTER,200);
	m_listData.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listData.m_nChooseList = 3;

	SetNewFont();
	m_staticInNet.SetFont(&m_fontStatic);
	m_staticUnNet.SetFont(&m_fontStatic);
	m_staticUnWhite.SetFont(&m_fontStatic);
}
void CCKQViewTabErrMet::InsertItemToList(CString strAddre , CString strLoca , CString strState , CString strMAC , CString strSendFrames ,CString strRecvFrames , CString strType)
{
	CString strNumb;
	int n = 0;
	n = m_listData.GetItemCount();
	strNumb.Format(_T("%d") , n + 1);
	m_listData.InsertItem(n , strNumb);
	m_listData.SetItemText(n , 1 , strAddre);
	m_listData.SetItemText(n , 2 , strLoca);
	m_listData.SetItemText(n , 3 , strState);
	m_listData.SetItemText(n , 4 , strMAC.Mid(0 , 2) + _T(":") + strMAC.Mid(2 , 2) + _T(":") + strMAC.Mid(4 , 2) + _T(":") + strMAC.Mid(6 , 2) + _T(":") + strMAC.Mid(8 , 2) + _T(":") + strMAC.Mid(10 , 2));
	m_listData.SetItemText(n , 5 , strSendFrames);
	m_listData.SetItemText(n , 6 , strRecvFrames);
	switch(_ttoi(strType))
	{
	case 1:
		break;
	case 2:
		m_listData.SetItemText(n , 7 , _T("集中器载波模块"));
		break;
	case 3:
		break;
	case 4:
		if (strMAC.Find(_T("BEBEBEBEBE")) != -1 )
		{
			m_listData.SetItemText(n , 7 , _T("抄控器载波模块"));
		} 
		else
		{
			m_listData.SetItemText(n , 7 , _T("单相表载波模块"));
		}
		break;
	}
	m_listData.EnsureVisible(n,FALSE);
	m_listData.RedrawItems(n,n);
}
DWORD WINAPI ThreadSendMetERR (PVOID pParam) 
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewTabErrMet * pView = (CCKQViewTabErrMet *)pParam;
	INT16U u16temp = 0 , u16BeginNumb = 0;
	INT8U SendDatabuf[10];
	INT8U ack = 0 , u8SendAFN = 0 ,AddrBuf[7] , u8ReadCount = 0 , n = 0 , temp8 = 0;
	INT16U SendDatalen = 0 ,temp16 = 0 , u16Numb = 0;
	CString strAllTPdata = _T("") , strMAC = _T("") , strWhere = _T("");
	CString strNumb , strSTAMsg[1024] , strlist[10];
	int nlistNumb = 0 , nlistUN = 0 , nInNetNumb = 0 , nUnNetNumb = 0 , nLostNumb = 0 , nUnWhiteNumb = 0;

	sPartQCSG376_2CreatFrame ptSendQCSG376_2;//南网
	sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2;

	sPartQGDW376_2CreatFrame ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;



	pView->m_listData.DeleteAllItems();
	pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T(""));
	pView->m_access.SetCopyTable(pMain->m_PeiZhi_db, _T("TPShow") , _T("TPMODERR"));
	//pView->m_access.SetCopyTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPShow") , _T("TPMODERR"));
	pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);

	if (pMain->NW_OR_GW==1){ //南网标准
		ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F1 , SendDatabuf , SendDatalen , ptSendQCSG376_2 , ptRecvQCSG376_2 , ptRecvQCSG376_2);
		if (ack != 0) return 0;
		temp16 = ptRecvQCSG376_2.s_RcvDataBuf[1] << 8 | ptRecvQCSG376_2.s_RcvDataBuf[0];
		while(temp16)
		{
			u16BeginNumb += u8ReadCount;
			if (temp16 >10)
			{
				u8ReadCount = 10;
			}
			else
			{
				u8ReadCount = temp16;
			}
			temp16 -= u8ReadCount;
			SendDatalen = 3;
			SendDatabuf[0] = (INT8U)u16BeginNumb;
			SendDatabuf[1] = (INT8U)(u16BeginNumb>>8);
			SendDatabuf[2] = u8ReadCount;
			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F2 , SendDatabuf , SendDatalen , ptSendQCSG376_2, ptRecvQCSG376_2 , ptRecvQCSG376_2);
			if (ack != 0) return 0;

			temp8 = ptRecvQCSG376_2.s_RcvDataBuf[2];
			for (n = 0; n < temp8; n++)
			{
				strMAC = pView->m_tools._buf16tostr16(&ptRecvQCSG376_2.s_RcvDataBuf[3 + 8 * n] , 6 , false , true);
				strWhere = _T("TP_MAC='") + strMAC + _T("'");
				//pView->m_access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
				pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
				if (nlistNumb == 0)
				{
					nUnNetNumb += 1;
					pView->InsertItemToList(strMAC , _T("") , _T("未入网") , strMAC , _T("0") , _T("0") ,_T("4"));
				}
				else
				{
					nInNetNumb += 1;
					pView->m_tools.Split(strSTAMsg[0] , _T("$") , strlist , nlistNumb);
					pView->InsertItemToList(strMAC , _T("") , _T("入网") , strMAC ,   _T("0") , _T("0"), strlist[1]);
					pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , strWhere);
					//pView->m_access.DelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , strWhere);
				}
			}
		}
	}
	else{
		ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F1 , SendDatabuf , SendDatalen , ptSendQGDW376_2 , ptRecvQGDW376_2 , ptRecvQGDW376_2);
		if (ack != 0) return 0;
		temp16 = ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | ptRecvQGDW376_2.s_RcvDataBuf[0];
		while(temp16)
		{
			u16BeginNumb += u8ReadCount;
			if (temp16 >10)
			{
				u8ReadCount = 10;
			}
			else
			{
				u8ReadCount = temp16;
			}
			temp16 -= u8ReadCount;
			SendDatalen = 3;
			SendDatabuf[0] = (INT8U)u16BeginNumb;
			SendDatabuf[1] = (INT8U)(u16BeginNumb>>8);
			SendDatabuf[2] = u8ReadCount;
			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F2 , SendDatabuf , SendDatalen , ptSendQGDW376_2, ptRecvQGDW376_2 , ptRecvQGDW376_2);
			if (ack != 0) return 0;

			temp8 = ptRecvQGDW376_2.s_RcvDataBuf[2];
			for (n = 0; n < temp8; n++)
			{
				strMAC = pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[3 + 8 * n] , 6 , false , true);
				strWhere = _T("TP_MAC='") + strMAC + _T("'");
				//pView->m_access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
				pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
				if (nlistNumb == 0)
				{
					nUnNetNumb += 1;
					pView->InsertItemToList(strMAC , _T("") , _T("未入网") , strMAC , _T("0") , _T("0") ,_T("4"));
				}
				else
				{
					nInNetNumb += 1;
					pView->m_tools.Split(strSTAMsg[0] , _T("$") , strlist , nlistNumb);
					pView->InsertItemToList(strMAC , _T("") , _T("入网") , strMAC ,   _T("0") , _T("0"), strlist[1]);
					pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , strWhere);
					//pView->m_access.DelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , strWhere);
				}
			}
		}
	}

	//pView->m_access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , _T("TP_MAC,TP_TEI,TP_ROLE") , _T("") , strSTAMsg , nlistNumb);
	pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T("TP_MAC,TP_TEI,TP_ROLE") , _T("") , strSTAMsg , nlistNumb);
	for (n = 0; n < nlistNumb; n++)
	{
		pView->m_tools.Split(strSTAMsg[n] , _T("$") , strlist , nlistUN);
		if (pView->m_tools._strDaoxu(strlist[0]) != pMain->m_strMAddress)
		{
			nUnWhiteNumb += 1;
			if (strlist[0].Find(_T("BEBEBEBEBE")) == -1 )
			{
				pView->InsertItemToList(strlist[0] , _T("") , _T("未在白名单") , strlist[0] , _T("0") , _T("0") , strlist[2]);
			}
		}
	}
	strNumb.Format(_T("%d") , nInNetNumb);
	pView->m_staticInNet.SetWindowText(_T("入网（") + strNumb + _T(")"));
	strNumb.Format(_T("%d") , nUnNetNumb);
	pView->m_staticUnNet.SetWindowText(_T("未入网（") + strNumb + _T(")"));
	strNumb.Format(_T("%d") , nUnWhiteNumb);
	pView->m_staticUnWhite.SetWindowText(_T("未在白名单（") + strNumb + _T(")"));
	return 0;
}

void CCKQViewTabErrMet::OnMeterrUpdata()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMain->m_bConnected != TRUE)
	{
		AfxMessageBox(_T("请先打开串口！"));
		return;
	}
	if (pMain->m_strMAddress == "")
	{
		AfxMessageBox(_T("请先连接CCO！"));
		#if (0==LOOPTEST)
			 return;
			#endif
	}

	m_hThreadsend=CreateThread (NULL,0,ThreadSendMetERR,this,0,NULL);
	CloseHandle(m_hThreadsend);
}
