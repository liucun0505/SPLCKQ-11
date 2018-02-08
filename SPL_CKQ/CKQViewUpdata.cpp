// CKQViewUpdata.cpp : 实现文件
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "CKQViewUpdata.h"
#include "AccessData.h"
#include "MainFrm.h"
#include "SimJzq.h"
#include "MyFunLib.h"
extern CSimJzq  gSimJzq;

IMPLEMENT_DYNCREATE(CCKQViewUpdata, CFormView)

CCKQViewUpdata::CCKQViewUpdata()
	: CFormView(CCKQViewUpdata::IDD)
{

}

CCKQViewUpdata::~CCKQViewUpdata()
{
}

void CCKQViewUpdata::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST_DATA, m_listShowMsg);
	//  DDX_Control(pDX, IDC_LIST1, m_listData1);
	DDX_Control(pDX, IDC_RADIO_TYPE, m_radioUpType);
	DDX_Control(pDX, IDC_EDIT_FILE, m_editFile);
	DDX_Control(pDX, IDC_BTN_BEGINUPDATA, m_btnSend);
	DDX_Control(pDX, IDC_BUTTON1, m_ReadBanBen);
	DDX_Control(pDX, IDC_CHECK1, SelCheck);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_STATIC222, m_mess);
	DDX_Control(pDX, IDC_BTN_REFRESH, m_ref);
}

BEGIN_MESSAGE_MAP(CCKQViewUpdata, CFormView)
	ON_BN_CLICKED(IDC_BTN_CHOOSEFILE, &CCKQViewUpdata::OnBnClickedBtnChoosefile)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CCKQViewUpdata::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_BEGINUPDATA, &CCKQViewUpdata::OnBnClickedBtnBeginupdata)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CCKQViewUpdata::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CCKQViewUpdata::OnBnClickedCheck1)
	ON_COMMAND(ID_ADDMETMSG, &CCKQViewUpdata::OnAddmetmsg)
END_MESSAGE_MAP()


// CCKQViewUpdata 诊断

#ifdef _DEBUG
void CCKQViewUpdata::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCKQViewUpdata::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCKQViewUpdata 消息处理程序
HBRUSH CCKQViewUpdata::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	return hbr;
}

void CCKQViewUpdata::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	SetNewFont();

	CRect rect;
	CRect rect1;
	GetClientRect(rect1);
	GetDlgItem(IDC_BTN_REFRESH)->GetWindowRect(rect);
	ScreenToClient(&rect);
	rect1.left += 10;
	rect1.top = rect.bottom + 10;
	rect1.right -= 5;
	rect1.bottom -= 5;
	m_listData.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_OWNERDRAWFIXED ,rect1,this,IDC_MYLISTUPDATA);//| LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES
	m_listData.InsertColumn(0,_T(""),LVCFMT_LEFT,50);
	m_listData.InsertColumn(1,_T("表地址"),LVCFMT_CENTER,150);
	m_listData.InsertColumn(2,_T("TEI号"),LVCFMT_CENTER,80);
	m_listData.InsertColumn(3,_T("电表状态"),LVCFMT_CENTER,90);
	m_listData.InsertColumn(4,_T("设备类型"),LVCFMT_CENTER,90);
	m_listData.InsertColumn(5,_T("版本号"),LVCFMT_CENTER,150);
	m_listData.InsertColumn(6,_T("读版本结果"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(7,_T("耗时"),LVCFMT_CENTER,130);

	m_listData.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	m_listData.m_nChooseList = 2;

	m_radioUpType.SetCheck(TRUE);
	// TODO: 在此添加专用代码和/或调用基类
}

void CCKQViewUpdata::SetNewFont()
{
	LOGFONT lf;  //逻辑字体结构
	::ZeroMemory(&lf,sizeof(lf));
	lf.lfHeight = 20;
	lf.lfWidth= 0;
	nStop=0;
	nStop_ShengJ=0;
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
	nStop=0;
}

void CCKQViewUpdata::OnBnClickedBtnChoosefile()
{

	CString OpenFilePathName;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_NOCHANGEDIR);
	int nOK=dlg.DoModal();
	if (nOK == IDOK)
	{
		OpenFilePathName = dlg.GetPathName();
		int len =WideCharToMultiByte(CP_ACP,0,OpenFilePathName,OpenFilePathName.GetLength(),NULL,0,NULL,NULL);
		char * pFileName = new char[len + 1];
		WideCharToMultiByte(CP_ACP,0,OpenFilePathName,OpenFilePathName.GetLength(),pFileName,len,NULL,NULL);
		pFileName[len+1] ='\0';
		m_editFile.SetWindowText(OpenFilePathName);
		m_btnSend.EnableWindow(TRUE);
	}
	
}


DWORD WINAPI ThreadSendUPDataList (PVOID pParam) 
{
	//CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	//CCKQViewUpdata * pView = (CCKQViewUpdata *)pParam;
	//INT16U u16BeginNumb = 1;
	//INT8U SendDatabuf[10];
	//INT8U ack = 0 , u8SendAFN = 0 ,AddrBuf[7] , u8ReadCount = 0 , n = 0 , temp8 = 0,strTYPE=0;
	//INT16U SendDatalen = 0 ,temp16 = 0 , u16Numb = 0;
	//CString strAllTPdata = _T("") , strMAC = _T("") , strWhere = _T("");
	//CString strAllTPdata_1 = _T("");
	//CString strNumb , strSTAMsg[1024] , strlist[10];
	//int nlistNumb = 0 , nlistUN = 0 , nInNetNumb = 0 , nUnNetNumb = 0 , nLostNumb = 0 , nUnWhiteNumb = 0;

	//sPartQCSG376_2CreatFrame ptSendQCSG376_2;//南网
	//sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2;

	//sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
	//sPartQGDW376_2CreatFrame ptSendQGDW376;
	//sPartQGDW376_2DeCodeFrame ptRecvQGDW376;

	//pView->m_listData.DeleteAllItems();
	////pView->m_Reflash.EnableWindow(FALSE);
	//pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T(""));
	////pView->m_access.SetCopyTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPShow") , _T("TPMODERR"));
	//pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
	//   	INT16U temp16_Node = 0 , temp16_Node_2=0;
	//	INT16U u16BeginNumb_Node = 1,u16BeginNumb_Node_2=1;
	//	INT8U u8ReadCount_Node = 0 ,u8ReadCount_Node_2 = 0 , n_2 = 0 , temp8_2 = 0;
 //  		if (pMain->m_bCKQ==TRUE){
	//	    ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F1 , SendDatabuf , SendDatalen , ptSendQGDW376 , ptRecvQGDW376 , ptRecvQGDW376_2);
	//	}
	//	else{
	//		ack = gSimJzq.HostSendRcv376_2NoBuf(0x10,F1,ptSendQGDW376,ptRecvQGDW376_2,1);
	//	}
	//	if (ack != 0){// pView->m_Reflash.EnableWindow(TRUE);
	//	return 0;}
	//	temp16 = ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | ptRecvQGDW376_2.s_RcvDataBuf[0];
	//	temp16_Node=temp16+2;

	//	while(temp16_Node){

	//		u16BeginNumb_Node += u8ReadCount_Node;
	//		if (temp16_Node >10)
	//		{
	//			u8ReadCount_Node = 10;
	//		}
	//		else
	//		{
	//			u8ReadCount_Node = temp16_Node;
	//		}
	//		temp16_Node -= u8ReadCount_Node;
	//		SendDatalen = 3;
	//		SendDatabuf[0] = (INT8U)u16BeginNumb_Node;
	//		SendDatabuf[1] = (INT8U)(u16BeginNumb_Node>>8);
	//		SendDatabuf[2] = u8ReadCount_Node;
	//		if (pMain->m_bCKQ==TRUE){
	//		    ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf, 0x10, F21, SendDatabuf, SendDatalen, ptSendQGDW376, ptRecvQGDW376, ptRecvQGDW376_2);
	//		}
	//		else{
	//			ack =gSimJzq.HostSendRcv376_2Buf(0x10,F21,SendDatabuf,SendDatalen,ptSendQGDW376,ptRecvQGDW376_2);
	//		}
 //           if(ack == DACK_SUCESS)
	//		{
	//			strAllTPdata_1 += pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[5] , ptRecvQGDW376_2.s_RcvDataLen -5);
	//			   
	//			if(ptRecvQGDW376_2.s_RcvDataBuf[4]==0x00&&ptRecvQGDW376_2.s_RcvDataBuf[4]==0x00){
	//				temp16_Node=0;
	//			}

	//		}
	//		else{
 //                   temp16_Node=0;
	//				break;
	//		}

	//	}

	//	pView->SetTPdataToAccess(strAllTPdata_1);


	//	while(temp16)
	//	{
	//		u16BeginNumb += u8ReadCount;
	//		if (temp16 >10)
	//		{
	//			u8ReadCount = 10;
	//		}
	//		else
	//		{
	//			u8ReadCount = temp16;
	//		}
	//		temp16 -= u8ReadCount;
	//		SendDatalen = 3;
	//		SendDatabuf[0] = (INT8U)u16BeginNumb;
	//		SendDatabuf[1] = (INT8U)(u16BeginNumb>>8);
	//		SendDatabuf[2] = u8ReadCount;
	//		if (pMain->m_bCKQ==TRUE){
	//		    ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F2 , SendDatabuf , SendDatalen , ptSendQGDW376, ptRecvQGDW376 , ptRecvQGDW376_2);
	//		}
	//		else{
	//			ack =gSimJzq.HostSendRcv376_2Buf(0x10,F2,SendDatabuf,SendDatalen,ptSendQGDW376,ptRecvQGDW376_2);
	//		}
	//		if (ack != 0){ 
	//			//pView->m_Reflash.EnableWindow(TRUE);
	//			return 0;
	//		}

	//		temp8 = ptRecvQGDW376_2.s_RcvDataBuf[2];
	//		for (n = 0; n < temp8; n++)
	//		{
	//			strMAC = pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[3 + 8 * n] , 6 , false , true);
	//			strTYPE=(ptRecvQGDW376_2.s_RcvDataBuf[3 + 8 * n+7]&0x34)>>3;
	//			strWhere = _T("TP_MAC='") + strMAC + _T("'");
	//			//pView->m_access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
	//			pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
	//			if (nlistNumb == 0)
	//			{
	//				nUnNetNumb += 1;
	//				pView->InsertItemToList(strMAC , _T("") , _T("未入网") , strTYPE , _T("0") , _T("0"));
	//			}
	//			else
	//			{
	//				nInNetNumb += 1;
	//				pView->m_tools.Split(strSTAMsg[0] , _T("$") , strlist , nlistNumb);
	//				pView->InsertItemToList(strMAC ,strlist[0] , _T("入网") , strTYPE,   _T("0") , _T("0"));
	//				pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , strWhere);
	//				//pView->m_access.DelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , strWhere);
	//			}
	//		}
	//	}
	////}

	////pView->m_access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , _T("TP_MAC,TP_TEI,TP_ROLE") , _T("") , strSTAMsg , nlistNumb);
	//pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T("TP_MAC,TP_TEI,TP_ROLE") , _T("") , strSTAMsg , nlistNumb);
	//for (n = 0; n < nlistNumb; n++)
	//{
	//	pView->m_tools.Split(strSTAMsg[n] , _T("$") , strlist , nlistUN);
	//	if (pView->m_tools._strDaoxu(strlist[0]) != pMain->m_strMAddress)
	//	{
	//		nUnWhiteNumb += 1;
	//		if (strlist[0].Find(_T("EBEBEBEBEB")) == -1 )
	//		{
	//			pView->InsertItemToList(strlist[0] , strlist[1] , _T("未在白名单") ,0,  _T("0") , _T("0") );
	//		}
	//	}
	//}
	//strNumb.Format(_T("%d") , nInNetNumb);
	////pView->m_staticInNet.SetWindowText(_T("入网（") + strNumb + _T(")"));
	//strNumb.Format(_T("%d") , nUnNetNumb);
	////pView->m_staticUnNet.SetWindowText(_T("未入网（") + strNumb + _T(")"));
	//strNumb.Format(_T("%d") , nUnWhiteNumb);
	////pView->m_staticUnWhite.SetWindowText(_T("未在白名单（") + strNumb + _T(")"));
	////pView->m_Reflash.EnableWindow(TRUE);
	//return 0;



		CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewUpdata  * pView = (CCKQViewUpdata  *)pParam;
	INT16U u16BeginNumb = 1;
	INT8U SendDatabuf[10];
	INT8U ack = 0 , u8SendAFN = 0 ,AddrBuf[7] , u8ReadCount = 0 , n = 0 , temp8 = 0,strTYPE=0;
	INT16U SendDatalen = 0 ,temp16 = 0 , u16Numb = 0;
	CString strAllTPdata = _T("") , strMAC = _T("") , strWhere = _T("");
	CString strAllTPdata_1 = _T("");
	CString strNumb , strSTAMsg[1024] , strlist[10];
	int nlistNumb = 0 , nlistUN = 0 , nInNetNumb = 0 , nUnNetNumb = 0 , nLostNumb = 0 , nUnWhiteNumb = 0;

	sPartQCSG376_2CreatFrame ptSendQCSG376_2;//南网
	sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2;

	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
	sPartQGDW376_2CreatFrame ptSendQGDW376;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376;

	pView->m_listData.DeleteAllItems();
	pView->m_ref.EnableWindow(FALSE);
	pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T(""));
	//pView->m_access.SetCopyTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPShow") , _T("TPMODERR"));
	pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
	   	INT16U temp16_Node = 0 , temp16_Node_2=0;
		INT16U u16BeginNumb_Node = 1,u16BeginNumb_Node_2=1;
		INT8U u8ReadCount_Node = 0 ,u8ReadCount_Node_2 = 0 , n_2 = 0 , temp8_2 = 0;



		
   		if (pMain->m_bCKQ==TRUE){
		    ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F1 , SendDatabuf , SendDatalen , ptSendQGDW376 , ptRecvQGDW376 , ptRecvQGDW376_2);
		}
		else{
			ack = gSimJzq.HostSendRcv376_2NoBuf(0x10,F1,ptSendQGDW376,ptRecvQGDW376_2,1);
		}
		if (ack != 0){ pView->m_ref.EnableWindow(TRUE);
		return 0;}
		temp16 = ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | ptRecvQGDW376_2.s_RcvDataBuf[0];
		temp16_Node=temp16+2;
		while(temp16_Node){

			u16BeginNumb_Node += u8ReadCount_Node;
			if (temp16_Node >30)
			{
				u8ReadCount_Node = 30;
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
		    int j_10F21=10;
			while(j_10F21){
				if (pMain->m_bCKQ==TRUE){
					ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf, 0x10, F21, SendDatabuf, SendDatalen, ptSendQGDW376, ptRecvQGDW376, ptRecvQGDW376_2);
				}
				else{
					ack =gSimJzq.HostSendRcv376_2Buf(0x10,F21,SendDatabuf,SendDatalen,ptSendQGDW376,ptRecvQGDW376_2);
				}
				if(ack == DACK_SUCESS)
				{
					if(ptRecvQGDW376_2.s_RcvDataLen>4){
						  	if(ptRecvQGDW376_2.s_RcvDataBuf[3]==0x00&&ptRecvQGDW376_2.s_RcvDataBuf[4]==0x00){
								temp16_Node=0;
								break;
							}
							strAllTPdata_1 += pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[5] , ptRecvQGDW376_2.s_RcvDataLen -5); 
							break;
					}
					else{
						j_10F21--;
						Sleep(20000);

					}

				}
				else{
						j_10F21--;
						Sleep(20000);
						//continue;
				}
		  }
			if(j_10F21==0){
						//AfxMessageBox(_T("目标*"));
				return 0;
			}

		}
		pView->SetTPdataToAccess(strAllTPdata_1);

		
		while(temp16)
		{
			u16BeginNumb += u8ReadCount;
			if (temp16 >30)
			{
				u8ReadCount = 30;
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
			int j_10F2=10;
			while(j_10F2){
				if (pMain->m_bCKQ==TRUE){
					ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F2 , SendDatabuf , SendDatalen , ptSendQGDW376, ptRecvQGDW376 , ptRecvQGDW376_2);
				}
				else{
					ack =gSimJzq.HostSendRcv376_2Buf(0x10,F2,SendDatabuf,SendDatalen,ptSendQGDW376,ptRecvQGDW376_2);
				}
				if (ack == DACK_SUCESS){ 
                        
						if(ptRecvQGDW376_2.s_RcvDataLen<6){
								j_10F2--;
								Sleep(20000);
								//continue;
						}
						else{
						    break;
						}
				}
				else{
						j_10F2--;
						Sleep(20000);
				}
			}
			if(j_10F2==0){

			  return 0;
		    }
			temp8 = ptRecvQGDW376_2.s_RcvDataBuf[2];
			for (n = 0; n < temp8; n++)
			{
				strMAC = pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[3 + 8 * n] , 6 , false , true);
				strTYPE=(ptRecvQGDW376_2.s_RcvDataBuf[3 + 8 * n+7]&0x34)>>3;
				strWhere = _T("TP_MAC='") + strMAC + _T("'");
				//pView->m_access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
				pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
				if (nlistNumb == 0)
				{
					nUnNetNumb += 1;
					pView->InsertItemToList(strMAC , _T("") , _T("未入网") , strTYPE , _T("0") , _T("0"));
				}
				else
				{
					nInNetNumb += 1;
					pView->m_tools.Split(strSTAMsg[0] , _T("$") , strlist , nlistNumb);
					pView->InsertItemToList(strMAC ,strlist[0] , _T("入网") , strTYPE,   _T("0") , _T("0"));
					pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , strWhere);
					//pView->m_access.DelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , strWhere);
				}
			}
		}
	//}

	//pView->m_access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , _T("TP_MAC,TP_TEI,TP_ROLE") , _T("") , strSTAMsg , nlistNumb);
	pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T("TP_MAC,TP_TEI,TP_ROLE") , _T("") , strSTAMsg , nlistNumb);
	for (n = 0; n < nlistNumb; n++)
	{
		pView->m_tools.Split(strSTAMsg[n] , _T("$") , strlist , nlistUN);
		if (pView->m_tools._strDaoxu(strlist[0]) != pMain->m_strMAddress)
		{
			nUnWhiteNumb += 1;
			if (strlist[0].Find(_T("EBEBEBEBEB")) == -1 )
			{
				pView->InsertItemToList(strlist[0] , strlist[1] , _T("未在白名单") ,0,  _T("0") , _T("0") );
			}
		}
	}
	strNumb.Format(_T("%d") , nInNetNumb);
	//pView->m_staticInNet.SetWindowText(_T("入网（") + strNumb + _T(")"));
	strNumb.Format(_T("%d") , nUnNetNumb);
	//pView->m_staticUnNet.SetWindowText(_T("未入网（") + strNumb + _T(")"));
	strNumb.Format(_T("%d") , nUnWhiteNumb);
	//pView->m_staticUnWhite.SetWindowText(_T("未在白名单（") + strNumb + _T(")"));
	pView->m_ref.EnableWindow(TRUE);
	return 0;
}

void CCKQViewUpdata::OnBnClickedBtnRefresh()
{
	
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMain->m_bConnected != TRUE)
	{
		AfxMessageBox(_T("请先打开串口！"));
		return;
	}
	//if (pMain->m_strMAddress == "")
	//{
	//	AfxMessageBox(_T("请先连接CCO！"));
	//	return;
	//}

	Refresh_hThreadsend=CreateThread (NULL,0,ThreadSendUPDataList,this,0,NULL);
	CloseHandle(Refresh_hThreadsend);
}

void CCKQViewUpdata::InsertItemToList(CString strAddre , CString strLoca , CString strState , INT8U strType,CString strSendFrames ,CString strRecvFrames)
{
	CString strNumb;
	int n = 0;
	n = m_listData.GetItemCount();
	strNumb.Format(_T("%d") , n + 1);
	m_listData.InsertItem(n , strNumb);
	m_listData.SetItemText(n , 1 , strAddre);//mac
	m_listData.SetItemText(n , 2 , strLoca);//tei
	m_listData.SetItemText(n , 3 , strState);//电表状态
	m_listData.SetItemText(n , 5 , strSendFrames);
	m_listData.SetItemText(n , 6 , strRecvFrames);
	if(strLoca=="1"){
		m_listData.SetItemText(n , 4 , _T("CCO载波模块"));
	}else{
		switch(strType)
		{
		case 0:
			break;
		case 1:
			m_listData.SetItemText(n , 4 , _T("97表"));
			break;
		case 2:
			m_listData.SetItemText(n , 4 , _T("07表"));
			break;
		case 3:
			m_listData.SetItemText(n , 4 , _T("698表"));
			break;
		}
	}
	m_listData.EnsureVisible(n,FALSE);
	m_listData.RedrawItems(n,n);
}

void CCKQViewUpdata::SetTPdataToAccess(CString strTPdata)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	INT8U SucceBuf[3];
	INT16U temp16 = 0;
			CString str=_T("0");
	CString  strMAC ,strTEI ,strPTEI, strRole , strLayer , strSuccess;
	CTools tools;
	CString strlistName[6] = {_T("TP_MAC") ,_T("TP_TEI") ,_T("TP_PTEI") ,_T("TP_ROLE") ,_T("TP_TIER")  ,_T("TP_READSUCCESS")};
	CString strlistData[6];
	CTime timeNow = CTime::GetCurrentTime();
	CString strTime = timeNow.Format("%Y%m%d%H%M%S") , strName , strData;
	
	char szANSIString[5000]; 
	FILE* file_tpmap;
	CString strCSVTime = timeNow.Format("%Y%m%d%H%M%S");  //CSV 保存

	int nNumb = strTPdata.GetLength()/22;
	//m_access.DelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("TPShow"),_T(""));
	m_access.DelectDataFromTable(pMain->m_PeiZhi_db,_T("TPMODERR"),_T(""));
	for(int n = 0 ; n < nNumb ; n++)
	{
		
		strMAC = strTPdata.Mid(0 , 12);
		strlistData[0] = tools._strDaoxu(strMAC);

		strTEI = strTPdata.Mid(12 , 4);
		strlistData[1] = tools._str16tostr10(tools._strDaoxu(strTEI));
		if(strTEI==_T("0100")){
			strlistData[2]=_T("0");
		}
		else{

		strPTEI = strTPdata.Mid(16 , 4);
		strlistData[2] = tools._str16tostr10(tools._strDaoxu(strPTEI));
		}

		strRole = strTPdata.Mid(20 , 2);
		if(tools._str16tostr10(strRole.Mid(0 ,1))=="4"){
			str.Format(_T("%d"),2); 
		}
		else if(tools._str16tostr10(strRole.Mid(0 ,1))=="2"){
			str.Format(_T("%d"),6); 
		}
		else {
		    str.Format(_T("%d"),_ttoi(tools._str16tostr10(strRole.Mid(0 ,1)))+3); 
		}
		strlistData[3] = tools._str16tostr10(str);

		strLayer= tools._str16tostr10(strRole.Mid(1 ,1));
		strLayer.Format(_T("%d"),_ttoi(strLayer)+1); 
		strlistData[4] = tools._str16tostr10(strLayer);//路由层级
		strlistData[5] = "99";


		if (strlistData[0].Mid(0,10) != "EBEBEBEBEB")
		{
			m_access.AddDataToTable(pMain->m_PeiZhi_db,_T("TPMODERR"),strlistName , strlistData ,6);
		}
		strTPdata = strTPdata.Mid(22);
	}

}

CString CCKQViewUpdata::strHEX(CString str,bool bDaoxu)
{
	INT8U * N_data;
	char d[5];
	CString strzong,strtwo;
	N_data=(INT8U*)str.GetBuffer(wcslen(str));
	for(int a=0;a<m_nDataLong;a++)
	{
		sprintf(d, "%X",N_data[a]);
		strtwo.Format(_T("%s"),d);
		if (wcslen(strtwo)==1)
		{
			strtwo = _T("0") + strtwo;
		}
		if (bDaoxu)
		{
			strzong=strtwo+strzong;
		} 
		else
		{
			strzong +=strtwo;
		}

	}
	return strzong;
}

CString CCKQViewUpdata::GetDuanAndLen(int nduan,int nlen)
{
	CString strData;
	CString str;
	CString str16duan,str16len;
	str.Format(_T("%d"),nduan);
	str16duan=m_tools._str10tostr16(str,4);
	str16duan=str16duan.Left(8).Right(2)+str16duan.Left(6).Right(2)+str16duan.Left(4).Right(2)+str16duan.Left(2);
	str.Format(_T("%d"),nlen);
	str16len=m_tools._str10tostr16(str,2);
	str16len=str16len.Left(4).Right(2)+str16len.Left(2);
	strData=str16duan+str16len;
	return strData;
}

void CCKQViewUpdata::SetUpdataListData()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nHang= 0;
	CString strUpDataMessage;
	CString strFile;
	m_editFile.GetWindowText(strFile);
	m_listStrShengjiData.RemoveAll();
	char chBiaoshi[50];
	char chZhiling[50];
	CString strBiaoshi,strZhiling;
	POSITION pos=NULL;
	CString str;
	BYTE buf[2048];
	int tmp = 0, mod = 0;
	int iSectors = 0;
	int len =WideCharToMultiByte(CP_ACP,0,strFile,strFile.GetLength(),NULL,0,NULL,NULL);
	char * pFileName = new char[len + 1];
	WideCharToMultiByte(CP_ACP,0,strFile,strFile.GetLength(),pFileName,len,NULL,NULL);
	pFileName[len+1] ='\0';
	FILE * m_fp = NULL;
	m_fp = fopen(pFileName, "rb");
	fseek(m_fp,0,SEEK_END);
	long nLen = ftell(m_fp);
	CString strlong;
	strlong.Format(_T("%d"),nLen);
	strBiaoshi = _T("00");
	strZhiling = _T("00");
	int changdu=1024;

	if (pMain->NW_OR_GW==1){ //南网标准
		m_nDataLong=changdu;
		if (nLen > 0)
		{
			tmp = nLen / changdu;
			mod = nLen % changdu;
			iSectors = (mod == 0)?tmp:(tmp + 1);
		}
	
		m_FileSize = nLen; 
		m_NrOfSectors = iSectors;

		CString strZongduan;
		strZongduan.Format(_T("%d"),iSectors);
	
		m_nYU=_ttoi(strZongduan)%1024;
		m_nCHU=_ttoi(strZongduan)/1024;
		strZongduan=m_tools._str10tostr16(strZongduan,2);
		strZongduan=strZongduan.Left(4).Right(2)+strZongduan.Left(2);
		fseek(m_fp, 0, SEEK_SET);
		CString strDuanLen;
		int i=0;
		for (i=0; i < (iSectors-1); i++)
		{
			CString strCurSecotor;
			strCurSecotor.Format(_T("%d"), i);
			strCurSecotor=m_tools._str10tostr16(strCurSecotor,2);
			strCurSecotor=strCurSecotor.Left(4).Right(2)+strCurSecotor.Left(2);
	//		CString strSecotorCRC;

			ZeroMemory(buf, changdu * sizeof(BYTE));
	//		strDuanLen=GetDuanAndLen(i,changdu);
			strDuanLen.Format(_T("%d"), changdu);
			strDuanLen=m_tools._str10tostr16(strDuanLen,2);
			strDuanLen=strDuanLen.Left(4).Right(2)+strDuanLen.Left(2);

			fread(buf,changdu,1,m_fp);
			if (strFile.Right(3)=="bin")
			{
				str = m_tools._buf16tostr16((INT8U*)buf,changdu,false,true);
			} 
			else
			{
				str=buf;
				str=strHEX(str,true);
			}
			pos=m_listStrShengjiData.InsertAfter(pos,strCurSecotor + strDuanLen + str + _T("0000")); 
		}
		if (mod!=0)
		{
			CString strCurSecotor;
			strCurSecotor.Format(_T("%d"), i);
			strCurSecotor=m_tools._str10tostr16(strCurSecotor,2);
			strCurSecotor=strCurSecotor.Left(4).Right(2)+strCurSecotor.Left(2);

	//		strDuanLen=GetDuanAndLen(i,mod);
			strDuanLen.Format(_T("%d"), mod);
			strDuanLen=m_tools._str10tostr16(strDuanLen,2);
			strDuanLen=strDuanLen.Left(4).Right(2)+strDuanLen.Left(2);

			fread(buf,mod,1,m_fp);
			m_nDataLong=mod;
			if (strFile.Right(3)=="bin")
			{
				str = m_tools._buf16tostr16((INT8U*)buf,mod,false,true);
			} 
			else
			{
				str=buf;
				str=strHEX(str,true);
			}
			pos=m_listStrShengjiData.InsertAfter(pos, strCurSecotor + strDuanLen + str + _T("0000"));
		}
	}
	else{

		m_nDataLong=changdu;
		if (nLen > 0)
		{
			tmp = nLen / changdu;
			mod = nLen % changdu;
			iSectors = (mod == 0)?tmp:(tmp + 1);
		}
		CString strZongduan;
		strZongduan.Format(_T("%d"),iSectors);

		m_nYU=_ttoi(strZongduan)%1024;
		m_nCHU=_ttoi(strZongduan)/1024;
		strZongduan=m_tools._str10tostr16(strZongduan,2);
		strZongduan=strZongduan.Left(4).Right(2)+strZongduan.Left(2);
		fseek(m_fp, 0, SEEK_SET);
		CString strDuanLen;
		int i=0;
		for (i=0; i < (iSectors-1); i++)
		{
			ZeroMemory(buf, changdu * sizeof(BYTE));
			strDuanLen=GetDuanAndLen(i,changdu);
			fread(buf,changdu,1,m_fp);
			if (strFile.Right(3)=="bin")
			{
				str = m_tools._buf16tostr16((INT8U*)buf,changdu,false,true);
			} 
			else
			{
				str=buf;
				str=strHEX(str,true);
			}
			pos=m_listStrShengjiData.InsertAfter(pos,_T("030000") + strZongduan + strDuanLen+str); 
		}
		if (mod!=0)
		{
			strDuanLen=GetDuanAndLen(i,mod);
			fread(buf,mod,1,m_fp);
			m_nDataLong=mod;
			if (strFile.Right(3)=="bin")
			{
				str = m_tools._buf16tostr16((INT8U*)buf,mod,false,true);
			} 
			else
			{
				str=buf;
				str=strHEX(str,true);
			}
			pos=m_listStrShengjiData.InsertAfter(pos,_T("030100")+strZongduan+strDuanLen+str);
		}
	}

}



INT8U CCKQViewUpdata::QWzhengchangshengji(CString m_strLujing)//段长1024
{
	//CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	//INT8U AddrBuf[7],AddrMain[6];
	//INT16U temp16_2 = 0,teilen;
	//CString a;   
	//INT8U ack;
	//int DUAN_LEN=1024;
	//CString xiazhuang=_T("00");
	//sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	//sPartQGDW376_2DeCodeFrame sRecv376_2HostFrame,DstDecodeDataFrame;
	//CString strBiaoshi,strZhiling;
	//CString str,str1,strZongduan,strDuanLen;
	//CString str_banben,str_banben_qian;
	//FILE* fp = NULL;
	//POSITION pos=NULL;
	//int tmp = 0, mod = 0;
	//int iSectors = 0;
	//int changdu=DUAN_LEN;//atoi(m_strFenduanlong);
	//char chBiaoshi[50];
	//char chZhiling[50];
	////plog.saveLog_strAll(TIME,"开始获取版本信息",0);
	////ack =gSimJzq.HostSendRcv376_2NoBuf(AFN03,F1,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
	////if(ack==DACK_SUCESS)
	////{
	////	if(DstDecodeDataFrame.s_RcvDataLen==9)
	////	{
	////		//if (DstDecodeDataFrame.s_RcvDataBuf[7]==buf_banben[0]&&DstDecodeDataFrame.s_RcvDataBuf[8]==buf_banben[1])
	////		//{
	////		INT16U cnt= Buf2ToHex16(&DstDecodeDataFrame.s_RcvDataBuf[7]);
	////		str_banben_qian.Format("%u", cnt);
	////		plog.saveLog_strAll(TIME,"当前版本号："+str_banben_qian,0);
	////		//}
	////	}
	////	else
	////	{
	////		ack = DACK_FAILURE;
	////	}
	////}
	////a = m_strLujing.Right(8);
	////str_banben=a.Left(4);
	//////UINT8 buf_banben[2];
	//////UINT16 len_banben;
	//////m_tool._str16tobuf16(str_banben ,buf_banben, len_banben);
	//////str.Format("%d",str_banben);
	////int mm;
	////sscanf(str_banben,"%d",&mm); 
	////str.Format("%d",mm);
	////plog.saveLog_strAll(TIME,"升级文件版本号为："+str,0);
	//
	////m_strLujing=".\\远程升级\\CCO升级文件\\123.bin";
	//BYTE buf[4096];
	//m_listStrShengjiData.RemoveAll();
	//int len =WideCharToMultiByte(CP_ACP,0,m_strLujing,m_strLujing.GetLength(),NULL,0,NULL,NULL);
	//char * pFileName = new char[len + 1];
	//WideCharToMultiByte(CP_ACP,0,m_strLujing,m_strLujing.GetLength(),pFileName,len,NULL,NULL);
	//pFileName[len+1] ='\0';
	//fp = fopen(pFileName, "rb");
	//fseek(fp,0,SEEK_END);
	////plog.saveLog_str(DATA_FILE,TIME,m_strLujing,0);
	////FILE* fp = NULL;
	////fp = fopen(m_strLujing, "rb");
	////BYTE buf[2048];
	////fseek(fp,100L,0);把fp指针移动到离文件开头100字节处；
 //   //fseek(fp,100L,1);把fp指针移动到离文件当前位置100字节处；
	////fseek(fp,100L,2);//把fp指针退回到离文件结尾100字节处。
	////fread(buf,2,3,fp);//每次读一个单元  单元长度changdu
	////str = m_tool._buf16tostr16((INT8U*)buf,changdu,false,0);
	////INT16U cnt= Buf2ToHex16(&DstDecodeDataFrame.s_RcvDataBuf[0]);
	////str.Format("数量：%u", cnt);
	////plog.saveLog_strAll(TIME,"结果：成功。节点数为"+str,0);
	//long nLen;
	//nLen = ftell(fp);
	//strBiaoshi="03";
	//strZhiling.Format(_T("%s"),chZhiling);
	////strNumb.Format(_T("%d") , n + 1);
	//strZhiling=_T("00");
	//m_nDataLong=changdu;
	//if (nLen > 0)
	//{
	//	tmp = nLen / changdu;
	//	mod = nLen % changdu;
	//	iSectors = (mod == 0)?tmp:(tmp + 1);
	//}
	//strZongduan.Format(_T("%d"),iSectors);
	//strZongduan=m_tools._str10tostr16(strZongduan,2);
	//strZongduan=strZongduan.Left(4).Right(2)+strZongduan.Left(2);
	//fseek(fp, 0, SEEK_SET);
	//int i,j;
	//for (i=0; i < (iSectors-1); i++)
	//{
	//	ZeroMemory(buf, changdu * sizeof(BYTE));
	//	strDuanLen=GetDuanAndLen(i,changdu);
	//	fread(buf,changdu,1,fp);//每次读一个单元  单元长度changdu
	//	if (m_strLujing.Right(3)==_T("bin"))
	//	{
	//		str = m_tools._buf16tostr16((INT8U*)buf,changdu,false,0);
	//	} 
	//	else
	//	{
	//		str=buf;
	//		str=strHEX(str,0);
	//	}
	//	if (xiazhuang==_T("00"))
	//	{
	//		pos=m_listStrShengjiData.InsertAfter(pos,_T("0000")+strZhiling+_T("0000000000000000"));
	//		xiazhuang=_T("03");
	//	}
	//	pos=m_listStrShengjiData.InsertAfter(pos,strBiaoshi+_T("00")+strZhiling+strZongduan+strDuanLen+str); 
	//	//AfxMessageBox(strBiaoshi+"00"+strZhiling+strZongduan+strDuanLen+str);
	//}
	//if (mod!=0)
	//{
	//	ZeroMemory(buf, changdu * sizeof(BYTE));
	//	strDuanLen=GetDuanAndLen(i,mod);
	//	fread(buf,mod,1,fp);
	//	m_nDataLong=mod;
	//	if (m_strLujing.Right(3)=="bin")
	//	{
	//		str = m_tools._buf16tostr16((INT8U*)buf,mod,false,0);
	//	} 
	//	else
	//	{
	//		str=buf;
	//		str=strHEX(str,0);
	//	}
	//	pos=m_listStrShengjiData.InsertAfter(pos,strBiaoshi+"01"+strZhiling+strZongduan+strDuanLen+str);
	//	//AfxMessageBox(strBiaoshi+"00"+strZhiling+strZongduan+strDuanLen+str);
	//}
	//i=1;	
	//m_Progress.SetRange(0,iSectors);//设置进度条范围
	//m_Progress.SetPos(1);
 //   m_Progress.SetStep(1);
	//int NUM=1;
	//for(pos = m_listStrShengjiData.GetHeadPosition(); pos != NULL;)
	//{
	//	if(nStop_ShengJ==1){
	//		return 0;
	//	}
	//	CString strShuxingBiaoshiLen;
	//	strShuxingBiaoshiLen=(CString)m_listStrShengjiData.GetNext(pos);
	//	//m_tools._str16tobuf16(strShuxingBiaoshiLen, Sendbufdata , Sendbuflen);
	//	//m_tool._str16tobuf16(m_listStrShengjiData.GetNext(pos),buf,a);
	//	INT16U a;
	//	m_tools._str16tobuf16(strShuxingBiaoshiLen,buf,a);
	//	//memcpy(buf,str,m_listStrShengjiData.GetNext(pos).GetLength());
	//	m_tools._str16tobuf16( pMain->m_strMAddress , AddrMain, temp16_2 , true);
	//    j=10;
	//	while(j){
	//		    //发送的地方
	//			if(nStop_ShengJ==1){
	//				return 0;
	//			}
	//			if (pMain->m_bCKQ==TRUE){
	//				ack = gSimJzq.HostSendRcv376_2F0F8(AddrMain , 0x15 , F1 , buf , a , sQGDW376_2HostFrame ,sRecv376_2HostFrame , DstDecodeDataFrame);
	//		        //ack =gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43 , F8DataHead, AddrMain ,0x13 , F1 , tmpbuf , len16 , sQGDW376_2HostFrame,sRecv376_2HostFrame , DstDecodeDataFrame);
	//			}
	//			else{
	//				//ack=gSimJzq.ReadMeterAndCmpMter(1,AddrBuf,0x00010000,sQGDW376_2HostFrame,DstDecodeDataFrame);
	//				ack =gSimJzq.HostSendRcv376_2Buf(0x15,F1,buf,a,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
	//			}
 //               if(ack==DACK_SUCESS)
	//			{
	//				if(DstDecodeDataFrame.s_head.s_AFN==0x00&&DstDecodeDataFrame.s_head.s_FN==F2)
	//				{
	//					j--;
	//					continue;
	//				}
	//				else
	//				{
	//					str.Format(_T("%d"),i);
	//					str1.Format(_T("%d"),iSectors);
	//					i++;
	//					CString m_str,mz_str;
	//					m_str.Format(_T("%d"),NUM);
	//					mz_str.Format(_T("%d"),iSectors);
	//					m_mess.SetWindowTextW(_T("第")+m_str+_T("段传输完毕    总段数:")+mz_str);
	//					m_Progress.SetPos(NUM);
	//					NUM++;
	//					break;
	//					//}
	//				}
	//			}
	//			else{
	//				j--;
	//				continue;
	//			}
	//	}
	//}
	////plog.saveLog_str(DATA_FILE,TIME,"升级文件传输完毕",0);
	return 0;
}//正常升级
INT8U CCKQViewUpdata::DDzhengchangshengji(CString m_strLujing,INT8U *AddrBuf)//段长1024
{
	//CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	//INT8U AddrMain[6];
	//INT16U temp16 = 0,temp16_2 = 0,teilen;
	//CString a;   
	//INT8U ack;
	//int DUAN_LEN=1024;
	//CString xiazhuang=_T("00");
	//sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	//sPartQGDW376_2DeCodeFrame sRecv376_2HostFrame,DstDecodeDataFrame;
	//CString strBiaoshi,strZhiling;
	//CString str,str1,strZongduan,strDuanLen;
	//CString str_banben,str_banben_qian;
	//CString NodeMAC,NodeTEI,str_F8DataHead,NodeTYPE,NodeSTATE;
	//INT8U F8DataHead[200];
	//FILE* fp = NULL;
	//POSITION pos=NULL;
	//int tmp = 0, mod = 0;
	//int iSectors = 0;
	//int changdu=DUAN_LEN;//atoi(m_strFenduanlong);
	//char chBiaoshi[50];
	//char chZhiling[50];
	//BYTE buf[4096];
	//m_listStrShengjiData.RemoveAll();
	//int len =WideCharToMultiByte(CP_ACP,0,m_strLujing,m_strLujing.GetLength(),NULL,0,NULL,NULL);
	//char * pFileName = new char[len + 1];
	//WideCharToMultiByte(CP_ACP,0,m_strLujing,m_strLujing.GetLength(),pFileName,len,NULL,NULL);
	//pFileName[len+1] ='\0';
	//fp = fopen(pFileName, "rb");
	//fseek(fp,0,SEEK_END);
	//long nLen;
	//nLen = ftell(fp);
	//strBiaoshi="03";
	//strZhiling.Format(_T("%s"),chZhiling);
	////strNumb.Format(_T("%d") , n + 1);
	//strZhiling=_T("00");
	//m_nDataLong=changdu;
	//if (nLen > 0)
	//{
	//	tmp = nLen / changdu;
	//	mod = nLen % changdu;
	//	iSectors = (mod == 0)?tmp:(tmp + 1);
	//}
	//strZongduan.Format(_T("%d"),iSectors);
	//strZongduan=m_tools._str10tostr16(strZongduan,2);
	//strZongduan=strZongduan.Left(4).Right(2)+strZongduan.Left(2);
	//fseek(fp, 0, SEEK_SET);
	//int i,j;
	//for (i=0; i < (iSectors-1); i++)
	//{
	//	ZeroMemory(buf, changdu * sizeof(BYTE));
	//	strDuanLen=GetDuanAndLen(i,changdu);
	//	fread(buf,changdu,1,fp);//每次读一个单元  单元长度changdu
	//	if (m_strLujing.Right(3)==_T("bin"))
	//	{
	//		str = m_tools._buf16tostr16((INT8U*)buf,changdu,false,0);
	//	} 
	//	else
	//	{
	//		str=buf;
	//		str=strHEX(str,0);
	//	}
	//	if (xiazhuang==_T("00"))
	//	{
	//		pos=m_listStrShengjiData.InsertAfter(pos,_T("0000")+strZhiling+_T("0000000000000000"));
	//		xiazhuang=_T("03");
	//	}
	//	pos=m_listStrShengjiData.InsertAfter(pos,strBiaoshi+_T("00")+strZhiling+strZongduan+strDuanLen+str); 
	//	//AfxMessageBox(strBiaoshi+"00"+strZhiling+strZongduan+strDuanLen+str);
	//}
	//if (mod!=0)
	//{
	//	ZeroMemory(buf, changdu * sizeof(BYTE));
	//	strDuanLen=GetDuanAndLen(i,mod);
	//	fread(buf,mod,1,fp);
	//	m_nDataLong=mod;
	//	if (m_strLujing.Right(3)=="bin")
	//	{
	//		str = m_tools._buf16tostr16((INT8U*)buf,mod,false,0);
	//	} 
	//	else
	//	{
	//		str=buf;
	//		str=strHEX(str,0);
	//	}
	//	pos=m_listStrShengjiData.InsertAfter(pos,strBiaoshi+"01"+strZhiling+strZongduan+strDuanLen+str);
	//	//AfxMessageBox(strBiaoshi+"00"+strZhiling+strZongduan+strDuanLen+str);
	//}
	//i=1;
	//m_Progress.SetRange(0,iSectors);//设置进度条范围
	//m_Progress.SetPos(1);
 //   m_Progress.SetStep(1);
	//int NUM=1;
	//for(pos = m_listStrShengjiData.GetHeadPosition(); pos != NULL;)
	//{
	//	CString strShuxingBiaoshiLen;
	//	strShuxingBiaoshiLen=(CString)m_listStrShengjiData.GetNext(pos);
	//	//m_tools._str16tobuf16(strShuxingBiaoshiLen, Sendbufdata , Sendbuflen);
	//	//m_tool._str16tobuf16(m_listStrShengjiData.GetNext(pos),buf,a);
	//	INT16U a;
	//	m_tools._str16tobuf16(strShuxingBiaoshiLen,buf,a);
	//	//memcpy(buf,str,m_listStrShengjiData.GetNext(pos).GetLength());
	//	m_tools._str16tobuf16( pMain->m_strMAddress , AddrMain, temp16_2 , true);

	//	str_F8DataHead=_T("040000B00400");
	//	m_tools._str16tobuf16(str_F8DataHead , F8DataHead , temp16);
	//	for(int n=0;n<6;n++){
	//		F8DataHead[6+n]=AddrMain[n];
	//	}
	//	for(int n=0;n<6;n++){
	//		F8DataHead[12+n]=AddrBuf[n];
	//	}
	//	j=50;
	//	while(j){
	//		    //发送的地方
	//			if (pMain->m_bCKQ==TRUE){
	//				//ack = gSimJzq.HostSendRcv376_2F0F8(AddrMain , 0x15 , F1 , buf , a , sQGDW376_2HostFrame ,sRecv376_2HostFrame , DstDecodeDataFrame);
	//		        ack = gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43, F8DataHead, AddrMain, 0x15, F1, buf, a, sQGDW376_2HostFrame, sRecv376_2HostFrame, DstDecodeDataFrame);
	//			}
	//			else{
	//				ack = gSimJzq.HostSendRcv376_2BufNode(AddrBuf , 0x15 , F1 , buf , a , sQGDW376_2HostFrame , DstDecodeDataFrame);	
	//				//ack =gSimJzq.HostSendRcv376_2Buf(0x15,F1,buf,a,sQGDW376_2HostFrame,sQGDW376_2HostFrame,1);
	//			}
	//			if(ack==DACK_SUCESS)
	//			{
	//				if(DstDecodeDataFrame.s_head.s_AFN==0x00&&DstDecodeDataFrame.s_head.s_FN==F2)
	//				{
	//					j--;
	//					continue;
	//				}
	//				else
	//				{
	//					str.Format(_T("%d"),i);
	//					str1.Format(_T("%d"),iSectors);
	//					i++;
	//					CString m_str,mz_str;
	//					m_str.Format(_T("%d"),NUM);
	//					mz_str.Format(_T("%d"),iSectors);
	//					m_mess.SetWindowTextW(_T("第")+m_str+_T("段传输完毕    总段数:")+mz_str);
	//					m_Progress.SetPos(NUM);
	//					NUM++;
	//					break;
	//					//}
	//				}
	//			}
	//			else{
	//				j--;
	//				continue;
	//			}
	//	}
	//}
	////plog.saveLog_str(DATA_FILE,TIME,"升级文件传输完毕",0);
	return 0;
}//正常升级单点


DWORD WINAPI ThreadSendbufUpData (PVOID pParam)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewUpdata * pView = (CCKQViewUpdata *)pParam;
	sPartQGDW376_2CreatFrame ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDWF0376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;

	CString NodeMAC,NodeTEI,NodeTYPE;
	INT8U Sendbufdata[2000] ,AddrBuf[6],TEIBuf[2];
	INT16U Sendbuflen = 0,temp16 = 0,teilen;
	INT8U ack = -1;
	CString strFile;
	pView->m_editFile.GetWindowText(strFile);
	if(strFile==_T("")){
		AfxMessageBox(_T("未加载文件"));
		return 0;
	}
	INT8U AddrMain[6];
	INT16U temp16_2 = 0;
	CString a;   
	int DUAN_LEN=1024;
	CString xiazhuang=_T("00");
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame sRecv376_2HostFrame,DstDecodeDataFrame;
	CString strBiaoshi,strZhiling;
	CString str,str1,strZongduan,strDuanLen;
	CString str_banben,str_banben_qian;
	CString str_F8DataHead,NodeSTATE;
	INT8U F8DataHead[200];
	FILE* fp = NULL;
	POSITION pos=NULL;
	int tmp = 0, mod = 0;
	int iSectors = 0;
	int changdu=DUAN_LEN;//atoi(m_strFenduanlong);
	char chBiaoshi[50];
	char chZhiling[50];
	BYTE buf[4096];
	pView->m_listStrShengjiData.RemoveAll();
	int len =WideCharToMultiByte(CP_ACP,0,strFile,strFile.GetLength(),NULL,0,NULL,NULL);
	char * pFileName = new char[len + 1];
	WideCharToMultiByte(CP_ACP,0,strFile,strFile.GetLength(),pFileName,len,NULL,NULL);
	pFileName[len+1] ='\0';
	fp = fopen(pFileName, "rb");
	fseek(fp,0,SEEK_END);
	long nLen;
	nLen = ftell(fp);
	if(pView->m_radioUpType.GetCheck()){//抄控器全网
	   strBiaoshi="03";
	}
	else{
       strBiaoshi="08";
	}
	strZhiling.Format(_T("%s"),chZhiling);
	//strNumb.Format(_T("%d") , n + 1);
	strZhiling=_T("00");
	pView->m_nDataLong=changdu;
	if (nLen > 0)
	{
		tmp = nLen / changdu;
		mod = nLen % changdu;
		iSectors = (mod == 0)?tmp:(tmp + 1);
	}
	strZongduan.Format(_T("%d"),iSectors);
	strZongduan=pView->m_tools._str10tostr16(strZongduan,2);
	strZongduan=strZongduan.Left(4).Right(2)+strZongduan.Left(2);
	fseek(fp, 0, SEEK_SET);
	int i,j;
	for (i=0; i < (iSectors-1); i++)
	{
		ZeroMemory(buf, changdu * sizeof(BYTE));
		strDuanLen=pView->GetDuanAndLen(i,changdu);
		fread(buf,changdu,1,fp);//每次读一个单元  单元长度changdu
		if (strFile.Right(3)==_T("bin"))
		{
			str = pView->m_tools._buf16tostr16((INT8U*)buf,changdu,false,0);
		} 
		else
		{
			str=buf;
			str=pView->strHEX(str,0);
		}
		if (xiazhuang==_T("00"))
		{
			pos=pView->m_listStrShengjiData.InsertAfter(pos,_T("0000")+strZhiling+_T("0000000000000000"));
			xiazhuang=_T("03");
		}
		pos=pView->m_listStrShengjiData.InsertAfter(pos,strBiaoshi+_T("00")+strZhiling+strZongduan+strDuanLen+str); 
		//AfxMessageBox(strBiaoshi+"00"+strZhiling+strZongduan+strDuanLen+str);
	}
	if (mod!=0)
	{
		ZeroMemory(buf, changdu * sizeof(BYTE));
		strDuanLen=pView->GetDuanAndLen(i,mod);
		fread(buf,mod,1,fp);
		pView->m_nDataLong=mod;
		if (strFile.Right(3)=="bin")
		{
			str = pView->m_tools._buf16tostr16((INT8U*)buf,mod,false,0);
		} 
		else
		{
			str=buf;
			str=pView->strHEX(str,0);
		}
		pos=pView->m_listStrShengjiData.InsertAfter(pos,strBiaoshi+"01"+strZhiling+strZongduan+strDuanLen+str);
		//AfxMessageBox(strBiaoshi+"00"+strZhiling+strZongduan+strDuanLen+str);
	}
	i=1;
	pView->m_Progress.SetRange(0,iSectors);//设置进度条范围
	pView->m_Progress.SetPos(1);
	pView->m_Progress.SetStep(1);
	int NUM=0;
	INT32U time1=GetSysTimeClk();
	for(pos = pView->m_listStrShengjiData.GetHeadPosition(); pos != NULL;)
	{
		if(pView->nStop_ShengJ==1){
			return 0;
		}
		CString strShuxingBiaoshiLen;
		strShuxingBiaoshiLen=(CString)pView->m_listStrShengjiData.GetNext(pos);
		//m_tools._str16tobuf16(strShuxingBiaoshiLen, Sendbufdata , Sendbuflen);
		//m_tool._str16tobuf16(m_listStrShengjiData.GetNext(pos),buf,a);
		INT16U a;
		pView->m_tools._str16tobuf16(strShuxingBiaoshiLen,buf,a);
		//memcpy(buf,str,m_listStrShengjiData.GetNext(pos).GetLength());
		pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrMain, temp16_2 , true);

		str_F8DataHead=_T("040000B00400");
		pView->m_tools._str16tobuf16(str_F8DataHead , F8DataHead , temp16);
		for(int n=0;n<6;n++){
			F8DataHead[6+n]=AddrMain[n];
		}
		for(int n=0;n<6;n++){
			F8DataHead[12+n]=AddrBuf[n];
		}
		NodeMAC=pView->m_listData.GetItemText(pView->m_listData.GetSelectionMark(),1);
		NodeTEI=pView->m_listData.GetItemText(pView->m_listData.GetSelectionMark(),2);
		NodeTYPE=pView->m_listData.GetItemText(pView->m_listData.GetSelectionMark(),3);
		j=5;//失败重发次数
		while(j){
				//发送的地方
				if(pView->nStop_ShengJ==1){
					return 0;
				}
				if (pMain->m_bCKQ==TRUE){
			        if(pView->m_radioUpType.GetCheck()){//抄控器全网
						ack = gSimJzq.HostSendRcv376_2F0F8(AddrMain , 0x15 , F1 , buf , a , sQGDW376_2HostFrame ,sRecv376_2HostFrame , DstDecodeDataFrame);
					}
					else{////抄控器单点
						if(NodeMAC==""){
							AfxMessageBox(_T("未选中节点"));
							return 0;
						}
						pView->m_tools._str16tobuf16(NodeMAC , AddrBuf , temp16 , true);//小端模式
						str_F8DataHead=_T("040000B00400");
						pView->m_tools._str16tobuf16(str_F8DataHead , F8DataHead , temp16);
						for(int n=0;n<6;n++){
						    F8DataHead[6+n]=AddrMain[n];
						}
						for(int n=0;n<6;n++){
						    F8DataHead[12+n]=AddrBuf[n];
						}
						ack = gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43, F8DataHead, AddrMain, 0x15, F1, buf, a, sQGDW376_2HostFrame, sRecv376_2HostFrame, DstDecodeDataFrame);
					}
				}
				else{
					if(pView->m_radioUpType.GetCheck()){//集中器全网
						ack =gSimJzq.HostSendRcv376_2Buf(0x15,F1,buf,a,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
					}
					else{//集中器单点
						if(NodeMAC==""){
							AfxMessageBox(_T("未选中节点"));
							return 0;
						}
						pView->m_tools._str16tobuf16(NodeMAC , AddrBuf , temp16 , true);//小端模式
						str_F8DataHead=_T("040000B00400");
						pView->m_tools._str16tobuf16(str_F8DataHead , F8DataHead , temp16);
						for(int n=0;n<6;n++){
						    F8DataHead[6+n]=AddrMain[n];
						}
						for(int n=0;n<6;n++){
						    F8DataHead[12+n]=AddrBuf[n];
						}
						ack = gSimJzq.HostSendRcv376_2BufNode(AddrBuf , 0x15 , F1 , buf , a , sQGDW376_2HostFrame , DstDecodeDataFrame);	
					}
				}
				if(ack==DACK_SUCESS)
				{
					if(DstDecodeDataFrame.s_RcvDataLen<3){

						ack = gSimJzq.Wait3762AckCmpSeq(15000,30,sQGDW376_2HostFrame,DstDecodeDataFrame);
                        j--;
                        continue;
					}
					if((DstDecodeDataFrame.s_head.s_AFN==0x00&&DstDecodeDataFrame.s_head.s_FN==F2)||(sRecv376_2HostFrame.s_head.s_AFN==0x00&&sRecv376_2HostFrame.s_head.s_FN==F2))
					{
						ack = gSimJzq.Wait3762AckCmpSeq(15000,30,sQGDW376_2HostFrame,DstDecodeDataFrame);
                         j--;
							//Sleep(6000);//过滤抄控器慢回的第二帧
						continue;
					}
					else
					{
						if(DstDecodeDataFrame.s_RcvDataBuf[0]==0xff&&DstDecodeDataFrame.s_RcvDataBuf[1]==0xff&&DstDecodeDataFrame.s_RcvDataBuf[2]==0xff&&DstDecodeDataFrame.s_RcvDataBuf[3]==0xff)
						{
							//j--;
							//if(j==0){

							//	str.Format(_T("%d"),i);
							//	str1.Format(_T("%d"),iSectors);
							//	i++;
							//	CString m_str,mz_str;
							//	m_str.Format(_T("%d"),NUM);
							//	mz_str.Format(_T("%d"),iSectors);
							//	pView->m_mess.SetWindowTextW(_T("文件传输失败请检查文件后重新传送！"));
							//	pView->m_Progress.SetPos(NUM);
	
							//	pView->m_btnSend.SetWindowText(_T("开始升级"));
							//	pView->m_ReadBanBen.EnableWindow(true);
							//	pView->m_ref.EnableWindow(true);
							//	NUM++;
							//}
							//Sleep(6000);
							//continue;
						}
						str.Format(_T("%d"),i);
						str1.Format(_T("%d"),iSectors);
						i++;
						CString m_str,mz_str;
						m_str.Format(_T("%d"),NUM);
						mz_str.Format(_T("%d"),iSectors);
						INT32U time2=GetSysTimeInterval(time1);
						CString str_time;
						str_time.Format(_T("%d 分 %d 秒 %d 毫秒"),time2/60000,(time2%60000)/1000,(time2%60000)%1000);
						pView->m_mess.SetWindowTextW(_T("第 ")+m_str+_T(" 段传输完毕  总段数: ")+mz_str+_T("  耗时:")+str_time);
						pView->m_Progress.SetPos(NUM);
						if(NUM==iSectors){
							pView->m_btnSend.SetWindowText(_T("开始升级"));
							pView->m_ReadBanBen.EnableWindow(true);
							pView->m_ref.EnableWindow(true);
						}
						NUM++;
						break;
					}
				}
				else{
					ack = gSimJzq.Wait3762AckCmpSeq(15000,30,sQGDW376_2HostFrame,DstDecodeDataFrame);
					//Sleep(6000);
					j--;
					continue;
				}


		}
		if(j==0){
			pView->m_mess.SetWindowTextW(_T("文件传输失败请检查文件后重新传送！"));
			pView->m_btnSend.SetWindowText(_T("开始升级"));
			pView->m_ReadBanBen.EnableWindow(true);
			pView->m_ref.EnableWindow(true);
		}
	}
	return 0;

}
void CCKQViewUpdata::OnBnClickedBtnBeginupdata()
{
	CString str;
	m_btnSend.GetWindowTextW(str);
	if(str=="开始升级"){
		CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
		CString strMessageAddress;
		pMain->m_bCommunictStop = false;

		if (pMain->m_bConnected == TRUE)
		{

			nStop_ShengJ=0;
			m_btnSend.SetWindowText(_T("停止升级"));
			m_ReadBanBen.EnableWindow(false);
			m_ref.EnableWindow(false);
			m_hThreadsend=CreateThread (NULL,0,ThreadSendbufUpData,this,0,NULL);
			CloseHandle(m_hThreadsend);
		}
		else
		{
			AfxMessageBox(_T("请打开串口！"));
		}
	}
	else{
		nStop_ShengJ=1;
		m_ReadBanBen.EnableWindow(true);
		m_ref.EnableWindow(true);
        m_btnSend.SetWindowText(_T("开始升级"));
	}
}

void CCKQViewUpdata::KongjianSize(int nID, int cx, int cy, bool bComb)
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
		//rect.left=(int)(rect.left*((float)cx/(float)fcx));//调整控件大小 
		rect.right=(int)(rect.right*((float)cx/(float)fcx)); 
		//rect.top=(int)(rect.top*((float)cy/(float)fcy)); 
		rect.bottom = (int)(rect.bottom*((float)cy/(float)fcy));// + nBottom;
		pWnd->MoveWindow(rect);//设置控件位置 
	}
}
void CCKQViewUpdata::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(rect); 
	if (rect.right == 0 || rect.bottom == 0 )
	{
		return;
	}
	//KongjianSize(IDC_BTN_BEGINUPDATA,rect.right,rect.bottom);
	KongjianSize(IDC_MYLISTUPDATA,rect.right,rect.bottom,TRUE);
	GetClientRect(m_cRect);
}

DWORD WINAPI ThreadSendbufReadBAN (PVOID pParam)
{
	//AfxMessageBox(_T("升级"));
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewUpdata * pView = (CCKQViewUpdata *)pParam;
	CString str_banben_qian;
	sPartQGDW376_2CreatFrame ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDWF0376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
	INT8U vSrcBuf[200];
	INT16U vSrcLen=0;
	CString NodeMAC,NodeTEI,str_F8DataHead,NodeTYPE,NodeSTATE;
	INT8U Sendbufdata[2000] ,AddrBuf[7],TEIBuf[2],AddrMain[6];
	INT16U Sendbuflen = 0,temp16 = 0,temp16_2 = 0,teilen;
	INT8U ack = -1;
	INT8U F8DataHead[200];

	pView->nSelect = pView->m_listData.GetSelectedCount();
	if (pView->nSelect == 0) 
	{ 
		pView->m_ReadBanBen.SetWindowText(_T("获取版本号"));
		AfxMessageBox(_T("未选中节点"));
		return 0;

	} 

	INT32U DL;
	//POSITION pos = pView->m_listData.GetFirstSelectedItemPosition(); 
	INT32U z_time1=GetSysTimeClk();
	for(int nItem=0; nItem<pView->m_listData.GetItemCount(); nItem++)
    {
        if( pView->m_listData.m_itemVector.at(nItem).flag==1)
        {
			if(pView->nStop==1){
				return 0;
			}
			NodeMAC=pView->m_listData.GetItemText(nItem,1);
			NodeTEI=pView->m_listData.GetItemText(nItem,2);
			NodeSTATE=pView->m_listData.GetItemText(nItem,3);
			NodeTYPE=pView->m_listData.GetItemText(nItem,4);
			pMain->m_tools._str16tobuf16(NodeMAC , AddrBuf , temp16 , true);//小端模式
			//pMain->m_tools._str16tobuf16(NodeTEI , TEIBuf , teilen , true);
			pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrMain, temp16_2 , true);
		//-----------------------测试抄表-------------------------------------
			if(NodeTEI==_T("1")||NodeSTATE==_T("未入网")){	
				continue;
			}
			else{
				//“040000B00400111111111111000000000000”
				str_F8DataHead=_T("040000B00400");
				pView->m_tools._str16tobuf16(str_F8DataHead , F8DataHead , temp16);
				for(int n=0;n<6;n++){
					F8DataHead[6+n]=AddrMain[n];
				}
				for(int n=0;n<6;n++){
					F8DataHead[12+n]=AddrBuf[n];
				}

				//AddrBuf[6]=2;
				INT8U tmpbuf[100];
				INT16U len16;
				len16 = 0;
				INT32U time1=GetSysTimeClk();
				//pView->m_listData.SetFocus();
				pView->m_listData.SetItemText(nItem,6,_T("读版本号中..."));
				if (pMain->m_bCKQ==TRUE){
					ack =gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43 , F8DataHead, AddrMain ,0x03 , F1 , tmpbuf , len16 , ptSendQGDW376_2,ptRecvQGDW376_2 , ptRecvQGDWF0376_2);
				}
				else{
					ack = gSimJzq.HostSendRcv376_2BufNode(AddrBuf , 0x03 , F1 , tmpbuf , len16 , ptSendQGDW376_2 , ptRecvQGDWF0376_2);		
				}
				if(pView->nStop==1){
					pView->m_ReadBanBen.SetWindowText(_T("获取版本号"));
					return 0;
				}
				if(ack == DACK_SUCESS)
				{
					//01 00 02 18 FE FE FE FE 68 00 01 00 00 00 00 68 91 08 33 33 34 33 69 33 33 33 39 16   28-6
					//00 00 02 14 68 86 02 11 07 17 00 68 91 08 33 33 34 33 85 36 33 33 0E 16

							if(ptRecvQGDWF0376_2.s_RcvDataLen==9)
							{
							
								str_banben_qian=pView->m_tools._buf16tostr16(&ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-2] , 2);
								pView->m_listData.SetItemText(nItem,5,str_banben_qian);
								pView->m_listData.SetItemText(nItem,6,_T("成功"));
								pView->m_listData.EnsureVisible(nItem,FALSE);
								pView->m_listData.RedrawItems(nItem,nItem);

								INT32U time2=GetSysTimeInterval(time1);
								CString str_time;
								str_time.Format(_T("%d"),time2);
								pView->m_listData.SetItemText(nItem,7,str_time+"ms");
							}
							else
							{
								ack = DACK_FAILURE;
								pView->m_listData.SetItemText(nItem,6,_T("失败"));
								pView->m_listData.EnsureVisible(nItem,FALSE);
								pView->m_listData.RedrawItems(nItem,nItem);
								pView->m_listData.SetItemText(nItem,7,_T("回复错误"));
								INT32U time2=GetSysTimeInterval(time1);
								CString str_time;
								str_time.Format(_T("%d"),time2);
								pView->m_listData.SetItemText(nItem,7,str_time+"ms");
							}
				}
				else{
					pView->m_listData.SetItemText(nItem,6,_T("失败"));
					pView->m_listData.EnsureVisible(nItem,FALSE);
					pView->m_listData.RedrawItems(nItem,nItem);
					pView->m_listData.SetItemText(nItem,7,_T("超时"));
					INT32U time2=GetSysTimeInterval(time1);
					CString str_time;
					str_time.Format(_T("%d"),time2);
					pView->m_listData.SetItemText(nItem,7,str_time+"ms");
					//pView->m_falnum++;
				}
				if(pView->nStop==1){
					pView->m_ReadBanBen.SetWindowText(_T("获取版本号"));
				return 0;
				}
			} 
        }
    }








//	INT32U DL;
//	POSITION pos = pView->m_listData.GetFirstSelectedItemPosition(); 
//	INT32U z_time1=GetSysTimeClk();
//	while (pView->nSelect) 
//	{ 
//		if(pView->nStop==1){
//			return 0;
//		}
//		int nItem = pView->m_listData.GetNextSelectedItem(pos); 
//		NodeMAC=pView->m_listData.GetItemText(nItem,1);
//		NodeTEI=pView->m_listData.GetItemText(nItem,2);
//		NodeSTATE=pView->m_listData.GetItemText(nItem,3);
//		NodeTYPE=pView->m_listData.GetItemText(nItem,4);
//		pMain->m_tools._str16tobuf16(NodeMAC , AddrBuf , temp16 , true);//小端模式
//		//pMain->m_tools._str16tobuf16(NodeTEI , TEIBuf , teilen , true);
//		pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrMain, temp16_2 , true);
////-----------------------测试抄表-------------------------------------
//		if(NodeTEI==_T("1")||NodeSTATE==_T("未入网")){	
//		   pView->nSelect=pView->nSelect-1;
//           continue;
//		}
//		else{
//			//“040000B00400111111111111000000000000”
//			str_F8DataHead=_T("040000B00400");
//			pView->m_tools._str16tobuf16(str_F8DataHead , F8DataHead , temp16);
//			for(int n=0;n<6;n++){
//				F8DataHead[6+n]=AddrMain[n];
//			}
//			for(int n=0;n<6;n++){
//				F8DataHead[12+n]=AddrBuf[n];
//			}
//
//			//AddrBuf[6]=2;
//			INT8U tmpbuf[100];
//			INT16U len16;
//			len16 = 0;
//		    INT32U time1=GetSysTimeClk();
//			//pView->m_listData.SetFocus();
//			pView->m_listData.SetItemText(nItem,6,_T("读版本号中..."));
//			if (pMain->m_bCKQ==TRUE){
//			    ack =gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43 , F8DataHead, AddrMain ,0x03 , F1 , tmpbuf , len16 , ptSendQGDW376_2,ptRecvQGDW376_2 , ptRecvQGDWF0376_2);
//			}
//			else{
//				ack = gSimJzq.HostSendRcv376_2BufNode(AddrBuf , 0x03 , F1 , tmpbuf , len16 , ptSendQGDW376_2 , ptRecvQGDWF0376_2);		
//			}
//			if(pView->nStop==1){
//				pView->m_ReadBanBen.SetWindowText(_T("获取版本号"));
//			    return 0;
//		    }
//			if(ack == DACK_SUCESS)
//			{
//				//01 00 02 18 FE FE FE FE 68 00 01 00 00 00 00 68 91 08 33 33 34 33 69 33 33 33 39 16   28-6
//				//00 00 02 14 68 86 02 11 07 17 00 68 91 08 33 33 34 33 85 36 33 33 0E 16
//
//						if(ptRecvQGDWF0376_2.s_RcvDataLen==9)
//						{
//							
//							str_banben_qian=pView->m_tools._buf16tostr16(&ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-2] , 2);
//							pView->m_listData.SetItemText(nItem,5,str_banben_qian);
//							pView->m_listData.SetItemText(nItem,6,_T("成功"));
//							pView->m_listData.EnsureVisible(nItem,FALSE);
//							pView->m_listData.RedrawItems(nItem,nItem);
//
//							INT32U time2=GetSysTimeInterval(time1);
//							CString str_time;
//							str_time.Format(_T("%d"),time2);
//							pView->m_listData.SetItemText(nItem,7,str_time+"ms");
//						}
//						else
//						{
//							ack = DACK_FAILURE;
//							pView->m_listData.SetItemText(nItem,6,_T("失败"));
//							pView->m_listData.EnsureVisible(nItem,FALSE);
//							pView->m_listData.RedrawItems(nItem,nItem);
//							pView->m_listData.SetItemText(nItem,7,_T("回复错误"));
//							INT32U time2=GetSysTimeInterval(time1);
//							CString str_time;
//							str_time.Format(_T("%d"),time2);
//							pView->m_listData.SetItemText(nItem,7,str_time+"ms");
//						}
//			}
//			else{
//				pView->m_listData.SetItemText(nItem,6,_T("失败"));
//				pView->m_listData.EnsureVisible(nItem,FALSE);
//				pView->m_listData.RedrawItems(nItem,nItem);
//				pView->m_listData.SetItemText(nItem,7,_T("超时"));
//				INT32U time2=GetSysTimeInterval(time1);
//				CString str_time;
//				str_time.Format(_T("%d"),time2);
//				pView->m_listData.SetItemText(nItem,7,str_time+"ms");
//				//pView->m_falnum++;
//			}
//			pView->nSelect=pView->nSelect-1;
//			if(pView->nStop==1){
//				pView->m_ReadBanBen.SetWindowText(_T("获取版本号"));
//			return 0;
//		    }
//		} 
//	}
	if(pView->nStop==1){
		pView->m_ReadBanBen.SetWindowText(_T("获取版本号"));
			return 0;
	}
	//INT32U z_time2=GetSysTimeInterval(z_time1);
	//INT32U z_time2_ms;
	//CString strTest,strTest1,strTest2,strTest3;
	//strTest.Format(_T("%d"),pView->m_sussnum);
	//pView->C_SU.SetWindowText(strTest);
	//strTest1.Format(_T("%d"),pView->m_falnum);
	//pView->C_FL.SetWindowText(strTest1);

	//strTest2.Format(_T("%d 分 %d 秒 %d 毫秒"),z_time2/60000,(z_time2%60000)/1000,(z_time2%60000)%1000);
	//pView->C_TI.SetWindowText(strTest2);
	pView->m_ReadBanBen.SetWindowText(_T("获取版本号"));

	return 0;
}
void CCKQViewUpdata::OnBnClickedButton1()//获取版本号
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	CString NodeMAC;
	m_ReadBanBen.GetWindowTextW(str);
	if(str=="获取版本号"){
		nStop=0;
	    m_ReadBanBen.SetWindowText(_T("停止获取"));

		CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	    CString strMessageAddress;
	    pMain->m_bCommunictStop = false;
		if (pMain->m_bConnected == TRUE)
		{
			m_hThreadsend_READ=CreateThread (NULL,0,ThreadSendbufReadBAN,this,0,NULL);
			CloseHandle(m_hThreadsend_READ);
		}
		else
		{
			AfxMessageBox(_T("请打开串口！"));
		}
	}
	else{
		nStop=1;
        m_ReadBanBen.SetWindowText(_T("获取版本号"));
	}
}


void CCKQViewUpdata::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	int num = 0;
	num = m_listData.GetItemCount();
	if(SelCheck.GetCheck()==1){
		m_listData.SetFocus();
        for (int n=0;n<num;n++)
        {
		   m_listData.m_itemVector.at(n).flag=1;
		   //ListView_SetCheckState(m_listData,n,FALSE);
           m_listData.SetItemState(n, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
        }
	}
	else
	{
		for (int n=0;n<num;n++)
        {
		   m_listData.m_itemVector.at(n).flag=0;
		   //ListView_SetCheckState(m_listData,n,FALSE);
           m_listData.SetItemState(n, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		}
	}
}


void CCKQViewUpdata::OnAddmetmsg()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   
    CString str;
    addmactest tipDlg;           // 构造对话框类CTipDlg的实例  
	tipDlg.n_ChooseDlg=2;
    nRes = tipDlg.DoModal();  // 弹出对话框      
    return;  
}
void CCKQViewUpdata::InsertMetMsg(CString str1,CString str2,CString str3)
{
	CString str;
	int m=m_listData.GetItemCount();
	str.Format(_T("%d") , m + 1);
	m_listData.InsertItem(m,str);
	str1=m_tools.BeforeAddO(str1,12);
	m_listData.SetItemText(m ,1,str1);
	m_listData.SetItemText(m ,2,str3);
	if(str2=="1"){
		m_listData.SetItemText(m ,4,_T("97表")); 
	}
	else if(str2=="2"){
		m_listData.SetItemText(m ,4,_T("07表"));
	}
	else if(str2=="3"){
		m_listData.SetItemText(m ,4,_T("698表"));
	}
}
