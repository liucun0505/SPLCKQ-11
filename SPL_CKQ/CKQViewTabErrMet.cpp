// CKQViewTabErrMet.cpp : 实现文件
//
#include "afxmt.h"
#include "stdafx.h"
#include "SPL_CKQ.h"
#include "CKQViewTabErrMet.h"
#include "MainFrm.h"
#include "SimJzq.h"
#include "MyFunLib.h"
#include <afxdb.h>
#include "GW13762.h"
extern CGW13762 Cgw13762;
extern cSerBuf_LoopRcv m_loopRcv13762;
//#include "afxmt.h"
extern CSimJzq  gSimJzq;
CRITICAL_SECTION cs;//锁定一个资源
CRITICAL_SECTION cs2;
static int n_Node= 0;//发送的个数
int SendOk=1;
sAckTimeSta timeclk376[1000];//保存每帧发送前的时间等 按SEQ号保存  对应获取
CString strAllDatalist[1000];//保存选中的地址按顺序
int Hang_Num[1000];//保存选中的行号  按顺序 从0开始 第0行seq为0  下一行的SEQ就为2 4 6
int MET_TYPE[1000];//
sPartQGDW376_2CreatFrame ptSendQGDW376_2[1000];
// CCKQViewTabErrMet
int COUNT;
int Send_COUNT;
int Send_COUNT2;
int Rev_COUNT;
int MAXBF=16;


IMPLEMENT_DYNCREATE(CCKQViewTabErrMet, CFormView)

CCKQViewTabErrMet::CCKQViewTabErrMet()
	: CFormView(CCKQViewTabErrMet::IDD)
	, m_sussnum(0)
	, m_falnum(0)
	, m_Ztime(0)
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
	DDX_Control(pDX, IDC_CHECKSEL, SelCheck);
	DDX_Control(pDX, IDC_STARTREAD, m_StartReadMet);
	DDX_Text(pDX, IDC_SU, m_sussnum);
	DDX_Text(pDX, IDC_FL, m_falnum);
	DDX_Text(pDX, IDC_TI, m_Ztime);
	DDX_Control(pDX, IDC_TI, C_TI);
	DDX_Control(pDX, IDC_FL, C_FL);
	DDX_Control(pDX, IDC_SU, C_SU);
	DDX_Control(pDX, IDC_REFLASH, m_Reflash);
	DDX_Control(pDX, IDC_EDITSS, m_editss);
	DDX_Control(pDX, IDC_STARTREADBINGF, m_BingfReadMet);
}

BEGIN_MESSAGE_MAP(CCKQViewTabErrMet, CFormView)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_METERR_UPDATA, &CCKQViewTabErrMet::OnMeterrUpdata)
	ON_BN_CLICKED(IDC_CHECKSEL, &CCKQViewTabErrMet::OnBnClickedChecksel)
	ON_BN_CLICKED(IDC_REFLASH, &CCKQViewTabErrMet::OnBnClickedReflash)
	ON_BN_CLICKED(IDC_STARTREAD, &CCKQViewTabErrMet::OnBnClickedStartread)
	ON_WM_SIZE()
	ON_COMMAND(ID_ADDMETMSG, &CCKQViewTabErrMet::OnAddmetmsg)
	ON_COMMAND(ID_DELB, &CCKQViewTabErrMet::OnDelb)
	ON_COMMAND(ID_COPYMACMET, &CCKQViewTabErrMet::OnCopymacmet)
	ON_BN_CLICKED(IDC_ADANGA, &CCKQViewTabErrMet::OnBnClickedAdanga)
	ON_BN_CLICKED(IDC_PDANGA, &CCKQViewTabErrMet::OnBnClickedPdanga)
	ON_BN_CLICKED(IDC_STARTSS, &CCKQViewTabErrMet::OnBnClickedStartss)
	ON_BN_CLICKED(IDC_STARTREADBINGF, &CCKQViewTabErrMet::OnBnClickedStartreadbingf)
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
	case	IDC_FL:
		pDC->SetTextColor(RGB(255,0,0));//设置文本颜色为红色
		break;
	case	IDC_SU:
	    pDC->SetTextColor(0x008000);//设置文本颜色
	    break;
	case	IDC_TI:
		pDC->SetTextColor(RGB(255,0,0));//设置文本颜色为红色
		break;
	}
	return hbr;
}
void CCKQViewTabErrMet::SetNewFont()
{
	LOGFONT lf;  //逻辑字体结构
	::ZeroMemory(&lf,sizeof(lf));
	m_sussnum=0;
	m_falnum=0;
	m_Ztime=0;
	nStop=0;
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
	GetDlgItem(IDC_STARTREAD)->GetWindowRect(rect);
	ScreenToClient(&rect);
	rect1.left += 10;
	rect1.top = rect.bottom + 10;
	rect1.right -= 5;
	rect1.bottom -= 5;
	m_listData.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_OWNERDRAWFIXED ,rect1,this,IDC_LISTUPDATAMSG);//|LVS_OWNERDRAWFIXED
	m_listData.InsertColumn(0,_T("序号"),LVCFMT_LEFT,50);//表头每列值不能为空或空格 不然存为xls文件时可能出错
	m_listData.InsertColumn(1,_T("表地址"),LVCFMT_CENTER,140);
	m_listData.InsertColumn(2,_T("TEI号"),LVCFMT_CENTER,50);
	m_listData.InsertColumn(3,_T("电表状态"),LVCFMT_CENTER,80);
	m_listData.InsertColumn(4,_T("设备类型"),LVCFMT_CENTER,80);
	m_listData.InsertColumn(5,_T("正向有功总电能"),LVCFMT_CENTER,120);
	m_listData.InsertColumn(6,_T("抄表结果"),LVCFMT_CENTER,90);
	m_listData.InsertColumn(7,_T("耗时"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(8,_T("表号"),LVCFMT_CENTER,180);
	m_listData.InsertColumn(9,_T("用户名"),LVCFMT_CENTER,130);
	m_listData.InsertColumn(10,_T("测量点"),LVCFMT_CENTER,90);
	m_listData.InsertColumn(11,_T("位置信息"),LVCFMT_CENTER,220);

	m_listData.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);//LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|
	m_listData.m_nChooseList = 3;

	SetNewFont();
	m_staticInNet.SetFont(&m_fontStatic);
	m_staticUnNet.SetFont(&m_fontStatic);
	m_staticUnWhite.SetFont(&m_fontStatic);
}
void CCKQViewTabErrMet::InsertItemToList(CString strAddre , CString strLoca , CString strState , INT8U strType,CString strSendFrames ,CString strRecvFrames)
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
DWORD WINAPI ThreadSendMetERR (PVOID pParam) 
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewTabErrMet * pView = (CCKQViewTabErrMet *)pParam;
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
	pView->m_Reflash.EnableWindow(FALSE);
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
		if (ack != 0){ pView->m_Reflash.EnableWindow(TRUE);
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
	pView->m_staticInNet.SetWindowText(_T("入网（") + strNumb + _T(")"));
	strNumb.Format(_T("%d") , nUnNetNumb);
	pView->m_staticUnNet.SetWindowText(_T("未入网（") + strNumb + _T(")"));
	strNumb.Format(_T("%d") , nUnWhiteNumb);
	pView->m_staticUnWhite.SetWindowText(_T("未在白名单（") + strNumb + _T(")"));
	pView->m_Reflash.EnableWindow(TRUE);
	return 0;
}

void CCKQViewTabErrMet::OnMeterrUpdata()
{
	if ( m_listData.GetItemCount()<= 0 )
	{
		AfxMessageBox(_T("列表中没有记录需要保存！"));
		return;
	}
	//打开另存为对话框 ，需要包含 #include <Afxdlgs.h>
	CFileDialog dlg( FALSE, 
		_T(" "), 
		_T("MetData"), 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		_T("(*.xls)|*.xls|(*.xlsx)|*.xlsx||"));
	dlg.m_ofn.lpstrTitle =_T( "文件列表另存为");

	if (dlg.DoModal() != IDOK)
		return;
	CString strFilePath;
	//获得文件路径名
	strFilePath = dlg.GetPathName();
	//判断文件是否已经存在，存在则删除重建
	DWORD dwRe = GetFileAttributes(strFilePath);
	if ( dwRe != (DWORD)-1 )
	{
		DeleteFile(strFilePath);
	}


	CDatabase database;//数据库库需要包含头文件 #include <afxdb.h>
	CString sDriver =_T("MICROSOFT EXCEL DRIVER (*.xls, *.xlsx, *.xlsm, *.xlsb)"); // Excel驱动
	CString sSql,strInsert;
	TRY
	{
		// 创建进行存取的字符串
		sSql.Format(_T("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s"),sDriver, strFilePath, strFilePath);

		// 创建数据库 (既Excel表格文件)
		if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
		{
			//获得列别框总列数
			int iColumnNum,iRowCount;
			LVCOLUMN lvCol;
			CString strColName; //用于保存列标题名称
			int i,j; //列、行循环参数

			iColumnNum = m_listData.GetHeaderCtrl()->GetItemCount();
			iRowCount = m_listData.GetItemCount();
			sSql = _T(" create table Sheet1 ( ");
			strInsert = _T(" insert into Sheet1 ( ") ;
			//获得列标题名称
			lvCol.mask = LVCF_TEXT; //必需设置，说明LVCOLUMN变量中pszText参数有效
			lvCol.cchTextMax = 32; //必设，pszText参数所指向的字符串的大小
			lvCol.pszText = strColName.GetBuffer(32); //必设，pszText 所指向的字符串的实际存储位置。
			//以上三个参数设置后才能通过 GetColumn()函数获得列标题的名称
			for( i=0 ; i< iColumnNum ; i++ )
			{
				if ( !(m_listData.GetColumn(i,&lvCol)) )
					return;
				if ( i<iColumnNum-1 )
				{
					///列表中没列表头
					//AfxMessageBox(lvCol.pszText);
					sSql = sSql + lvCol.pszText + _T(" TEXT , ");
					strInsert = strInsert + lvCol.pszText + _T(" , ");
				}
				else
				{
					sSql = sSql + lvCol.pszText + _T(" TEXT ) ");
					strInsert = strInsert + lvCol.pszText +_T( " )  values ( ");
				}
			}
			//创建Excel表格文件
			database.ExecuteSQL(sSql);
			//循环提取记录并插入到EXCEL中
			sSql = strInsert;
			CString str;
			LPTSTR chTemp = str.GetBufferSetLength(200);//给每个字段分配好长度  不然出错
			for ( j=0 ; j<iRowCount ; j++ )
			{
				//memset(chTemp,0,33);
				for ( i=0 ; i<iColumnNum ; i++ )
				{
					m_listData.GetItemText(j,i,chTemp,33);//.GetItemText(j,i,chTemp,33);
					if(chTemp==_T("")){
						chTemp==_T(" ");//扫描为空时 要加个空格 不然保存失败
					}
					if ( i < (iColumnNum-1) )
					{
						sSql = sSql + _T("'") + chTemp + _T("', ");
					}
					else
					{
						sSql = sSql +_T("'")  + chTemp +_T("' ) ") ;
					}
				}
				//将记录插入到表格中
				database.ExecuteSQL(sSql);
				sSql = strInsert; 
			}
		}     
		 //关闭Excel表格文件
		database.Close();
		AfxMessageBox(_T("Excel文件保存成功！"));
	}
	CATCH_ALL(e)
	{
		//错误类型很多，根据需要进行报错。
		AfxMessageBox(_T("Excel文件保存失败。"));
	}
	END_CATCH_ALL;

	/////////////////////////////////////////////
}

void CCKQViewTabErrMet::SetTPdataToAccess(CString strTPdata)
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

void CCKQViewTabErrMet::OnBnClickedChecksel()
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
		   //m_listData.GetCheck(n);
		   //m_listData.SetCheck(n,!m_listData.GetCheck(n));
        }
	}
	else
	{
		for (int n=0;n<num;n++)
        {
		  m_listData.SetItemState(n, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	      m_listData.m_itemVector.at(n).flag=0;
		  //m_listData.SetItemState(n, 0, LVIS_SELECTED|LVIS_FOCUSED);
		  //m_listData.m_itemVector.at(n).flag=0;
		  //ListView_SetCheckState(m_listData,n,TRUE);
		}
	}

}


void CCKQViewTabErrMet::OnBnClickedReflash()
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

	m_hThreadsend=CreateThread (NULL,0,ThreadSendMetERR,this,0,NULL);
	CloseHandle(m_hThreadsend);
}




DWORD WINAPI ThreadSendbufReadMet (PVOID pParam)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewTabErrMet * pView = (CCKQViewTabErrMet *)pParam;
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
	//pView->nSelect = pView->m_listData.GetSelectedCount();
	//if (pView->nSelect == 0) 
	//{ 
	//	pView->m_StartReadMet.SetWindowText(_T("开始抄表"));
	//	AfxMessageBox(_T("未选中节点"));
	//	return 0;
	//} 
	pView->m_sussnum=0;
	pView->m_falnum=0;
	pView->m_Ztime=0;

	pView->C_SU.SetWindowText(_T("0"));
	pView->C_FL.SetWindowText(_T("0"));
	pView->C_TI.SetWindowText(_T("00:00:00"));

	//pView->C_TI.setcol



	INT32U DL;
	//POSITION pos = pView->m_listData.GetFirstSelectedItemPosition(); 
	INT32U z_time1=GetSysTimeClk();

	for(int nItem=0; nItem<pView->m_listData.GetItemCount(); nItem++)
    {
        if( pView->m_listData.m_itemVector.at(nItem).flag==1)
        {

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
			if(NodeTYPE=="97表"){
				AddrBuf[6]=1;
			}
			else if(NodeTYPE==_T("07表")){
				AddrBuf[6]=2;
			}
			else if(NodeTYPE=="698表"){
				AddrBuf[6]=3;
			}
			//AddrBuf[6]=2;
			INT8U tmpbuf[100];
			INT16U len16;

			sDtl2007_Read CmdData645;
			gSimJzq.CodeReadData9707Cmd(AddrBuf[6],00010000,AddrBuf,1,CmdData645);//00010000
			tmpbuf[0]=AddrBuf[6];
			tmpbuf[1]=0;
			tmpbuf[2]=0;
			tmpbuf[3]=CmdData645.s_vDstCmdLen;
			//tmpbuf[2]=CmdData645.s_vDstCmdLen;//F1 F1用
			//tmpbuf[3]=0;
			BufToBuf(&tmpbuf[4],CmdData645.s_pDstCmdBuf,CmdData645.s_vDstCmdLen);
			len16 = CmdData645.s_vDstCmdLen+ 4;
		    INT32U time1=GetSysTimeClk();
			//pView->m_listData.SetFocus();
			pView->m_listData.SetItemText(nItem,6,_T("抄表中..."));
			if (pMain->m_bCKQ==TRUE){
			    ack =gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43 , F8DataHead, AddrMain ,0x13 , F1 , tmpbuf , len16 , ptSendQGDW376_2,ptRecvQGDW376_2 , ptRecvQGDWF0376_2);
				//ack =gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43 , F8DataHead, AddrMain ,0xF1 , F1 , tmpbuf , len16 , ptSendQGDW376_2,ptRecvQGDW376_2 , ptRecvQGDWF0376_2);
			}
			else{
				ack=gSimJzq.ReadMeterAndCmpMter(1,AddrBuf,0x00010000,ptSendQGDW376_2,ptRecvQGDWF0376_2);
			}
			if(pView->nStop==1){
				pView->m_StartReadMet.SetWindowText(_T("开始抄表"));
			return 0;
		    }
			if(ack == DACK_SUCESS)
			{
				//01 00 02 18 FE FE FE FE 68 00 01 00 00 00 00 68 91 08 33 33 34 33 69 33 33 33 39 16   28-6
				//00 00 02 14 68 86 02 11 07 17 00 68 91 08 33 33 34 33 85 36 33 33 0E 16
				if(ptRecvQGDWF0376_2.s_RcvDataLen>20){
					INT8U DL[4];
					DL[0]=ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-6]-0x33;
					DL[1]=ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-5]-0x33;
					DL[2]=ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-4]-0x33;
					DL[3]=ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-3]-0x33;
					CString cs=pMain->m_tools._buf16tostr16(DL,4,false,true);
					//DL = (ptRecvQGDWF0376_2.s_RcvDataBuf[25]-0x33)<<24;//| (ptRecvQGDWF0376_2.s_RcvDataBuf[24]-0x33)<<16 | (ptRecvQGDWF0376_2.s_RcvDataBuf[23]-0x33)<<8 | (ptRecvQGDWF0376_2.s_RcvDataBuf[22]-0X33); 
					//float f_DL=DL*(0.01);
					//CString cs;
			//            cs.Format(_T("%g"),f_DL);
					cs=cs.Mid(0,6)+_T(".")+cs.Mid(6,2);
					pView->m_listData.SetItemText(nItem,5,cs);
					pView->m_listData.SetItemText(nItem,6,_T("成功"));
					pView->m_listData.EnsureVisible(nItem,FALSE);
					pView->m_listData.RedrawItems(nItem,nItem);

					INT32U time2=GetSysTimeInterval(time1);
					CString str_time;
					str_time.Format(_T("%d"),time2);
					pView->m_listData.SetItemText(nItem,7,str_time+"ms");
					pView->m_sussnum++;
				}
				else{
					pView->m_listData.SetItemText(nItem,6,_T("失败"));
					pView->m_listData.EnsureVisible(nItem,FALSE);
					pView->m_listData.RedrawItems(nItem,nItem);
					pView->m_listData.SetItemText(nItem,7,_T("回复错误"));
					INT32U time2=GetSysTimeInterval(time1);
					CString str_time;
					str_time.Format(_T("%d"),time2);
					pView->m_listData.SetItemText(nItem,7,str_time+"ms");
					pView->m_falnum++;

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
				pView->m_falnum++;
			}
			//pView->nSelect=pView->nSelect-1;
			if(pView->nStop==1){
				pView->m_StartReadMet.SetWindowText(_T("开始抄表"));
			return 0;
		    }
		} 

        }
    }





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
//			if(NodeTYPE=="97表"){
//				AddrBuf[6]=1;
//			}
//			else if(NodeTYPE==_T("07表")){
//				AddrBuf[6]=2;
//			}
//			else if(NodeTYPE=="698表"){
//				AddrBuf[6]=3;
//			}
//			//AddrBuf[6]=2;
//			INT8U tmpbuf[100];
//			INT16U len16;
//
//			sDtl2007_Read CmdData645;
//			gSimJzq.CodeReadData9707Cmd(AddrBuf[6],00010000,AddrBuf,1,CmdData645);//00010000
//			tmpbuf[0]=AddrBuf[6];
//			tmpbuf[1]=0;
//			tmpbuf[2]=0;
//			tmpbuf[3]=CmdData645.s_vDstCmdLen;
//			//tmpbuf[2]=CmdData645.s_vDstCmdLen;//F1 F1用
//			//tmpbuf[3]=0;
//			BufToBuf(&tmpbuf[4],CmdData645.s_pDstCmdBuf,CmdData645.s_vDstCmdLen);
//			len16 = CmdData645.s_vDstCmdLen+ 4;
//		    INT32U time1=GetSysTimeClk();
//			//pView->m_listData.SetFocus();
//			pView->m_listData.SetItemText(nItem,6,_T("抄表中..."));
//			if (pMain->m_bCKQ==TRUE){
//			    ack =gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43 , F8DataHead, AddrMain ,0x13 , F1 , tmpbuf , len16 , ptSendQGDW376_2,ptRecvQGDW376_2 , ptRecvQGDWF0376_2);
//				//ack =gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43 , F8DataHead, AddrMain ,0xF1 , F1 , tmpbuf , len16 , ptSendQGDW376_2,ptRecvQGDW376_2 , ptRecvQGDWF0376_2);
//			}
//			else{
//				ack=gSimJzq.ReadMeterAndCmpMter(1,AddrBuf,0x00010000,ptSendQGDW376_2,ptRecvQGDWF0376_2);
//			}
//			if(pView->nStop==1){
//				pView->m_StartReadMet.SetWindowText(_T("开始抄表"));
//			return 0;
//		    }
//			if(ack == DACK_SUCESS)
//			{
//				//01 00 02 18 FE FE FE FE 68 00 01 00 00 00 00 68 91 08 33 33 34 33 69 33 33 33 39 16   28-6
//				//00 00 02 14 68 86 02 11 07 17 00 68 91 08 33 33 34 33 85 36 33 33 0E 16
//				if(ptRecvQGDWF0376_2.s_RcvDataLen>20){
//					INT8U DL[4];
//					DL[0]=ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-6]-0x33;
//					DL[1]=ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-5]-0x33;
//					DL[2]=ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-4]-0x33;
//					DL[3]=ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-3]-0x33;
//					CString cs=pMain->m_tools._buf16tostr16(DL,4,false,true);
//					//DL = (ptRecvQGDWF0376_2.s_RcvDataBuf[25]-0x33)<<24;//| (ptRecvQGDWF0376_2.s_RcvDataBuf[24]-0x33)<<16 | (ptRecvQGDWF0376_2.s_RcvDataBuf[23]-0x33)<<8 | (ptRecvQGDWF0376_2.s_RcvDataBuf[22]-0X33); 
//					//float f_DL=DL*(0.01);
//					//CString cs;
//			//            cs.Format(_T("%g"),f_DL);
//					cs=cs.Mid(0,6)+_T(".")+cs.Mid(6,2);
//					pView->m_listData.SetItemText(nItem,5,cs);
//					pView->m_listData.SetItemText(nItem,6,_T("成功"));
//					pView->m_listData.EnsureVisible(nItem,FALSE);
//					pView->m_listData.RedrawItems(nItem,nItem);
//
//					INT32U time2=GetSysTimeInterval(time1);
//					CString str_time;
//					str_time.Format(_T("%d"),time2);
//					pView->m_listData.SetItemText(nItem,7,str_time+"ms");
//					pView->m_sussnum++;
//				}
//				else{
//					pView->m_listData.SetItemText(nItem,6,_T("失败"));
//					pView->m_listData.EnsureVisible(nItem,FALSE);
//					pView->m_listData.RedrawItems(nItem,nItem);
//					pView->m_listData.SetItemText(nItem,7,_T("回复错误"));
//					INT32U time2=GetSysTimeInterval(time1);
//					CString str_time;
//					str_time.Format(_T("%d"),time2);
//					pView->m_listData.SetItemText(nItem,7,str_time+"ms");
//					pView->m_falnum++;
//
//				}
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
//				pView->m_falnum++;
//			}
//			pView->nSelect=pView->nSelect-1;
//			if(pView->nStop==1){
//				pView->m_StartReadMet.SetWindowText(_T("开始抄表"));
//			return 0;
//		    }
//		} 
//	}



	if(pView->nStop==1){
		pView->m_StartReadMet.SetWindowText(_T("开始抄表"));
			return 0;
	}
	INT32U z_time2=GetSysTimeInterval(z_time1);
	INT32U z_time2_ms;
	CString strTest,strTest1,strTest2,strTest3;
	strTest.Format(_T("%d"),pView->m_sussnum);
	pView->C_SU.SetWindowText(strTest);
	strTest1.Format(_T("%d"),pView->m_falnum);
	pView->C_FL.SetWindowText(strTest1);

	strTest2.Format(_T("%d 分 %d 秒 %d 毫秒"),z_time2/60000,(z_time2%60000)/1000,(z_time2%60000)%1000);
	pView->C_TI.SetWindowText(strTest2);
	pView->m_StartReadMet.SetWindowText(_T("开始抄表"));

	return 0;
}









void CCKQViewTabErrMet::OnBnClickedStartread()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	CString NodeMAC;
	m_StartReadMet.GetWindowTextW(str);
		m_sussnum=0;
	m_falnum=0;
	if(str=="开始抄表"){
		nStop=0;

		CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	    CString strMessageAddress;
	    pMain->m_bCommunictStop = false;
		if (pMain->m_bConnected == TRUE)
		{
			m_hThreadsend_READ=CreateThread (NULL,0,ThreadSendbufReadMet,this,0,NULL);
			CloseHandle(m_hThreadsend_READ);
		}
		else
		{
			AfxMessageBox(_T("请打开串口！"));
			return;
		}
		m_StartReadMet.SetWindowText(_T("停止抄表"));
	}
	else{
		nStop=1;
        m_StartReadMet.SetWindowText(_T("开始抄表"));
	}

}

void CCKQViewTabErrMet::KongjianSize(int nID, int cx, int cy, bool bComb)
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
void CCKQViewTabErrMet::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(rect); 
	if (rect.right == 0 || rect.bottom == 0 )
	{
		return;
	}
	//KongjianSize(IDC_STARTREAD,rect.right,rect.bottom);
	KongjianSize(IDC_LISTUPDATAMSG,rect.right,rect.bottom,TRUE);
	GetClientRect(m_cRect);
}




void CCKQViewTabErrMet::OnAddmetmsg()
{
	// TODO: 在此添加命令处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   
    CString str;
    addmactest tipDlg;           // 构造对话框类CTipDlg的实例  
	tipDlg.n_ChooseDlg=1;
    nRes = tipDlg.DoModal();  // 弹出对话框      
    return;    
    // 根据各变量的值更新相应的控件   
}
void CCKQViewTabErrMet::InsertMetMsg(CString str1,CString str2,CString str3)
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

void CCKQViewTabErrMet::OnDelb()
{
	// TODO: 在此添加命令处理程序代码
	int nSelect = m_listData.GetSelectedCount();
	if (nSelect == 0) 
	{ 

		AfxMessageBox(_T("未选中节点"));
		return ;

	} 
	POSITION pos = m_listData.GetFirstSelectedItemPosition(); 
    while (pos) 
    { 
		int nItem = m_listData.GetNextSelectedItem(pos); 
		m_listData.DeleteItem(nItem);
		pos = m_listData.GetFirstSelectedItemPosition();
	}
}


void CCKQViewTabErrMet::OnCopymacmet()
{
	// TODO: 在此添加命令处理程序代码

	int nSelect = m_listData.GetSelectedCount();
	if (nSelect == 0) 
	{ 
		AfxMessageBox(_T("未选中节点"));
		return ;

	} 
	CString strCopy=_T("");
	POSITION pos = m_listData.GetFirstSelectedItemPosition(); 
    while (nSelect) 
    { 
		int nItem = m_listData.GetNextSelectedItem(pos); 
		strCopy+= m_listData.GetItemText (nItem , 1)+_T("\r\n");
		nSelect--;
	}

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


void CCKQViewTabErrMet::OnBnClickedAdanga()
{
	// TODO: 在此添加控件通知处理程序代码

	CFileDialog dlg( TRUE,//TRUE或FALSE。TRUE为打开文件；FALSE为保存文件
				_T(" "), //为缺省的扩展名
			_T( "data"), //为显示在文件名组合框的编辑框的文件名，一般可选NULL 
				OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,//为对话框风格，一般为OFN_HIDEREADONLY   |   OFN_OVERWRITEPROMPT,即隐藏只读选项和覆盖已有文件前提示。 
				_T("EXCEL文件(*.xls)|*.xls|EXCEL文件(*.xlsx)|*.xlsx|所有文件(*.*)|*.*||")//_T("Excel 文件(*.*)|*.xlsx|*.xls|Excel 文件(*.*)|*.xlsx|*.xls|")//为下拉列表枢中显示文件类型
				);
	 dlg.m_ofn.lpstrTitle = _T("导入数据");
 
	 if (dlg.DoModal() != IDOK)
	  return;
	 CString strFilePath;
	 //获得文件路径名
	 strFilePath = dlg.GetPathName();
	 //判断文件是否已经存在，存在则打开文件
	 DWORD dwRe = GetFileAttributes(strFilePath);
	 if ( dwRe != (DWORD)-1 )
	 {
	  //ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	 }
	 else return;
	 TRY
	 {
		 CDatabase db;//数据库库需要包含头文件 #include <afxdb.h>
		 CString sDriver =_T("MICROSOFT EXCEL DRIVER (*.xls, *.xlsx, *.xlsm, *.xlsb)") ; // Excel驱动
		 CString sSql,arr[12];
		 sSql.Format(_T("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s"),sDriver, strFilePath, strFilePath);
		 if(!db.OpenEx(sSql,CDatabase::noOdbcDialog))//连接数据源DJB．xls
		 {
		  MessageBox(_T("打开EXCEL文件失败!","错误"));
		  return;
		 }
		 //打开EXCEL表
		 CRecordset pset(&db);
		 m_listData.DeleteAllItems();
		 //AfxMessageBox(_T("OK"));
		/* sSql = "SELECT 学号,姓名,成绩 "       
					   "FROM EXCELDEMO";      */          
					  // "ORDER BY 姓名";
		 sSql.Format(_T("SELECT * FROM [Sheet1$]"));
		 pset.Open(CRecordset::forwardOnly,sSql,CRecordset::readOnly);
		 while(!pset.IsEOF())
		 {
		 pset.GetFieldValue(_T("序号"),arr[0]);//前面字段必须与表中的相同，否则出错。
		 pset.GetFieldValue(_T("表地址"),arr[1]);
		 pset.GetFieldValue(_T("TEI号"),arr[2]);
		 pset.GetFieldValue(_T("电表状态"),arr[3]);
		 pset.GetFieldValue(_T("设备类型"),arr[4]);
		 pset.GetFieldValue(_T("正向有功总电能"),arr[5]);
		 pset.GetFieldValue(_T("抄表结果"),arr[6]);
		 pset.GetFieldValue(_T("耗时"),arr[7]);
		 pset.GetFieldValue(_T("表号"),arr[8]);
		 pset.GetFieldValue(_T("用户名"),arr[9]);
		 pset.GetFieldValue(_T("测量点"),arr[10]);
		 pset.GetFieldValue(_T("位置信息"),arr[11]);
		 //pset.get
 
		 int count = m_listData.GetItemCount();//插入到ListCtrl中
		 m_listData.InsertItem(count,arr[0]);
		 m_listData.SetItemText(count,1,arr[1]);
		 m_listData.SetItemText(count,2,arr[2]);
		 m_listData.SetItemText(count,3,arr[3]);
		 m_listData.SetItemText(count,4,arr[4]);
		 m_listData.SetItemText(count,5,arr[5]);
		 m_listData.SetItemText(count,6,arr[6]);
		 m_listData.SetItemText(count,7,arr[7]);
		 m_listData.SetItemText(count,8,arr[8]);
		 m_listData.SetItemText(count,9,arr[9]);
		 m_listData.SetItemText(count,10,arr[10]);
		 m_listData.SetItemText(count,11,arr[11]);
		 pset.MoveNext();
		 }
		 db.Close();
	}
	CATCH_ALL(e)
	{
		//错误类型很多，根据需要进行报错。
		AfxMessageBox(_T("Excel格式不对，导入失败"));
		return;
	}
	END_CATCH_ALL;
	 //MessageBox(_T("Excel数据成功导入系统!","导入成功"));
}


void CCKQViewTabErrMet::OnBnClickedPdanga()
{
	// TODO: 在此添加控件通知处理程序代码

	//CString str1=_T("447555");

	//CString str2=_T("99444445557777");

	//int m =str2.Find(str1);
	//int n =str1.Find(str2);
	// CString xh;
	// xh.Format(_T("%d"),m);
	// MessageBox(_T("m==")+xh);
	// xh.Format(_T("%d"),n);
	// MessageBox(_T("n==")+xh);
		TRY
	{
		CFileDialog dlg( TRUE,//TRUE或FALSE。TRUE为打开文件；FALSE为保存文件
				_T(" "), //为缺省的扩展名
			_T( "data"), //为显示在文件名组合框的编辑框的文件名，一般可选NULL 
				OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,//为对话框风格，一般为OFN_HIDEREADONLY   |   OFN_OVERWRITEPROMPT,即隐藏只读选项和覆盖已有文件前提示。 
				_T("EXCEL文件(*.xls)|*.xls|EXCEL文件(*.xlsx)|*.xlsx|所有文件(*.*)|*.*||")//_T("Excel 文件(*.*)|*.xlsx|*.xls|Excel 文件(*.*)|*.xlsx|*.xls|")//为下拉列表枢中显示文件类型
				);
	 dlg.m_ofn.lpstrTitle = _T("导入数据");
 
	 if (dlg.DoModal() != IDOK)
	  return;
	 CString strFilePath;
	 //获得文件路径名
	 strFilePath = dlg.GetPathName();
	 //判断文件是否已经存在，存在则打开文件
	 DWORD dwRe = GetFileAttributes(strFilePath);
	 if ( dwRe != (DWORD)-1 )
	 {
	  //ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	 }
	 else return;
	 CDatabase db;//数据库库需要包含头文件 #include <afxdb.h>
	 CString sDriver =_T("MICROSOFT EXCEL DRIVER (*.xls, *.xlsx, *.xlsm, *.xlsb)") ; // Excel驱动
	 CString sSql,arr[4];
	// Driver={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=path to xls/xlsx/xlsm/xlsb file
		 sSql.Format(_T("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s"),sDriver, strFilePath, strFilePath);
		 if(!db.OpenEx(sSql,CDatabase::noOdbcDialog))//连接数据源DJB．xls
		 {
		  MessageBox(_T("打开EXCEL文件失败!","错误"));
		  return;
		 }
		 //打开EXCEL表
		 CRecordset pset(&db);
		 sSql.Format(_T("SELECT * FROM [Sheet1$]"));
		 pset.Open(CRecordset::forwardOnly,sSql,CRecordset::readOnly);
		 int COUNT = m_listData.GetItemCount();//插入到ListCtrl中
		 while(!pset.IsEOF())
		 {
			 pset.GetFieldValue(_T("表号"),arr[0]);//前面字段必须与表中的相同，否则出错。
			 pset.GetFieldValue(_T("用户名"),arr[1]);
			 pset.GetFieldValue(_T("测量点"),arr[2]);
			 pset.GetFieldValue(_T("位置信息"),arr[3]);
			 //pset.get
 
			 int count = m_listData.GetItemCount();//插入到ListCtrl中
			 CString xh=_T(" ");
			 xh.Format(_T("%d"),count+1);
			 int biaozhi=0;
			 for(int num=0;num<COUNT;num++){
				 CString ss=m_listData.GetItemText(num,1);
				 biaozhi=arr[0].Find(ss);
				 if(biaozhi!=-1){
					m_listData.SetItemText(num,8,arr[0]);
					m_listData.SetItemText(num,9,arr[1]);
					m_listData.SetItemText(num,10,arr[2]);
					m_listData.SetItemText(num,11,arr[3]);
					break;
				 }
			 }
			 if(biaozhi==-1||COUNT==0){
				m_listData.InsertItem(count,xh);
				m_listData.SetItemText(count,8,arr[0]);
				m_listData.SetItemText(count,9,arr[1]);
				m_listData.SetItemText(count,10,arr[2]);
				m_listData.SetItemText(count,11,arr[3]);

			 }
			 pset.MoveNext();
		 }
		 db.Close();
	}
	CATCH_ALL(e)
	{
		//错误类型很多，根据需要进行报错。
		AfxMessageBox(_T("Excel格式不对，匹配失败"));
		return;
	}
	END_CATCH_ALL;
	// MessageBox(_T("Excel数据成功导入系统!","导入成功"));
}


void CCKQViewTabErrMet::OnBnClickedStartss()
{
	// TODO: 在此添加控件通知处理程序代码

	int COUNT = m_listData.GetItemCount();
	int biaozhi=0;
	int NUM=0;
	CString s_editss=_T(" ");
	m_editss.GetWindowText(s_editss);
	for (int n=0;n<COUNT;n++)
    {
		m_listData.SetItemState(n, 0, LVIS_SELECTED|LVIS_FOCUSED);
	}
	for(int num=0;num<COUNT;num++){
		CString ss=m_listData.GetItemText(num,1);
		biaozhi=ss.Find(s_editss);
		m_listData.SetFocus();
		if(biaozhi!=-1){
			NUM++;
            m_listData.SetItemState(num, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
		}
	}
    if(NUM==0){
        MessageBox(_T("没有匹配的表地址"));
	}

}

DWORD WINAPI ThreadRevbufBingF (PVOID pParam)
{
	CSimJzq   gSimJzqRev;
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewTabErrMet * pView = (CCKQViewTabErrMet *)pParam;
	sPartQGDW376_2CreatFrame ptSendQGDW376_2;
	
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
	//INT8U ack = -1;


	while(1){

		//EnterCriticalSection(&cs);
	    if(pView->nStop==1){
			pView->m_BingfReadMet.SetWindowText(_T("并发抄表"));
			//LeaveCriticalSection(&cs);
			return 0;
			
	    }
	 //   LeaveCriticalSection(&cs);
		//EnterCriticalSection(&cs);
		INT8U ack = -1;
		INT8U recvbuf[2048];
	    INT16U recvbuflen=0;
		sPartQGDW376_2DeCodeFrame ptRecvQGDWF0376_2;
        //ack = gSimJzqRev.Wait3762AckCmpSeq(15000,20,ptSendQGDW376_2,ptRecvQGDWF0376_2);
		//LeaveCriticalSection(&cs);
	    ///ack = gSimJzq.Wait3762Ack(15000,50,ptRecvQGDWF0376_2);

	//		INT8U recvbuf[D376_MAXRCVBUFLEN];
	//INT16U recvbuflen=0;
	//int nItem = 0;
	
	//SYSTEMTIME st;
	//GetLocalTime(&st);
	//pMainDlg->m_strSysDateTime_rx.Format(_T("%d年%d月%d日 %.2d:%.2d:%.2d.%.3d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	//
		//EnterCriticalSection(&cs);
	    gSimJzqRev.GetCOMMLENToBuf(2048 , 15000 , 20 , recvbuf , recvbuflen);
		//LeaveCriticalSection(&cs);
	    if(recvbuflen >0){
        //EnterCriticalSection(&cs);
		ack = Cgw13762.Decode376_2Frame(recvbuf,recvbuflen,ptRecvQGDWF0376_2);
		//plog.saveLog_HexBuf(DATA_FILE,INPUT_DATA,recvbuf,recvbuflen);//打印接收帧数据
		//EnterCriticalSection(&cs);
		int nItemL = pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemCount();
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.InsertItem( nItemL,pMain-> m_strSysDateTime_rx);
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItemL , 1, _T("接收<<"));
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItemL , 2 , pMain->m_tools._buf16tostr16(recvbuf , recvbuflen , true));
		//LeaveCriticalSection(&cs);
		//pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.EnsureVisible(nItemL,FALSE);
		//pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.RedrawItems(nItemL,nItem);


		  int nItem=ptRecvQGDWF0376_2.s_head.s_Msg_Seq;
		   if(ptRecvQGDWF0376_2.s_head.s_AFN==0x00&&ptRecvQGDWF0376_2.s_head.s_FN==0x02)//否认
		   {
			   		pView->m_listData.SetItemText(Hang_Num[nItem],6,_T("失败"));
					pView->m_listData.EnsureVisible(Hang_Num[nItem],FALSE);
					pView->m_listData.RedrawItems(Hang_Num[nItem],Hang_Num[nItem]);
					//pView->m_listData.SetItemText(nItem,7,_T("回复否认"));
					INT32U time2=GetSysTimeInterval(timeclk376[nItem].timeclk);
					CString str_time;
					str_time.Format(_T("%d"),time2);
					pView->m_listData.SetItemText(Hang_Num[nItem],7,str_time+"ms/否认");
					pView->m_falnum++;

		   }
		  else{
			   if(ptRecvQGDWF0376_2.s_RcvDataLen>3){
				   //EnterCriticalSection(&cs);
				   //MAXBF=MAXBF+1;
				   //LeaveCriticalSection(&cs);
				    SendOk=1;
				    INT8U DL[4];
					DL[0]=ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-6]-0x33;
					DL[1]=ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-5]-0x33;
					DL[2]=ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-4]-0x33;
					DL[3]=ptRecvQGDWF0376_2.s_RcvDataBuf[ptRecvQGDWF0376_2.s_RcvDataLen-3]-0x33;
					CString strcs=pMain->m_tools._buf16tostr16(DL,4,false,true);

					strcs=strcs.Mid(0,6)+_T(".")+strcs.Mid(6,2);
					pView->m_listData.SetItemText(Hang_Num[nItem],5,strcs);
					pView->m_listData.SetItemText(Hang_Num[nItem],6,_T("成功"));
					pView->m_listData.EnsureVisible(Hang_Num[nItem],FALSE);
					pView->m_listData.RedrawItems(Hang_Num[nItem],Hang_Num[nItem]);

					INT32U time2=GetSysTimeInterval(timeclk376[nItem].timeclk);
					CString str_time;
					str_time.Format(_T("%d"),time2);
					pView->m_listData.SetItemText(Hang_Num[nItem],7,str_time+"ms");
					pView->m_sussnum=pView->m_sussnum+1;
					CString strTest;
	                strTest.Format(_T("%d"),pView->m_sussnum);
	                pView->C_SU.SetWindowText(strTest);
					Hang_Num[nItem]=999;
					
					 //EnterCriticalSection(&cs);
				    //MAXBF=MAXBF+1;
				    //LeaveCriticalSection(&cs);
					//EnterCriticalSection(&cs);
					if(pView->m_falnum+pView->m_sussnum==Rev_COUNT){
						LeaveCriticalSection(&cs);
						pView->m_BingfReadMet.SetWindowText(_T("并发抄表"));
						INT32U z_time2=GetSysTimeInterval(timeclk376[0].timeclk);
						INT32U z_time2_ms;
						CString strTest2;
						strTest2.Format(_T("%d 分 %d 秒 %d 毫秒"),z_time2/60000,(z_time2%60000)/1000,(z_time2%60000)%1000);
						pView->C_TI.SetWindowText(strTest2);
						CString strTest;
	                    strTest.Format(_T("%d"),pView->m_falnum);
	                    pView->C_FL.SetWindowText(strTest);
						return 0;
					}
					//EnterCriticalSection(&cs);
				    
					//LeaveCriticalSection(&cs);
			   }
			   else{
				   	pView->m_listData.SetItemText(Hang_Num[nItem],6,_T("失败"));
					pView->m_listData.EnsureVisible(Hang_Num[nItem],FALSE);
					pView->m_listData.RedrawItems(Hang_Num[nItem],Hang_Num[nItem]);
					pView->m_listData.SetItemText(nItem,7,_T("回复错误"));
					INT32U time2=GetSysTimeInterval(timeclk376[nItem].timeclk);
					CString str_time;
					str_time.Format(_T("%d"),time2);
					pView->m_listData.SetItemText(Hang_Num[nItem],7,str_time+"ms");
					pView->m_falnum++;
					    //EnterCriticalSection(&cs);

			   }
		   }
	   }
	   else{
						for(int mm=0;mm<Rev_COUNT;mm++){
							if(Hang_Num[mm]!=999){
								pView->m_falnum=pView->m_falnum+1;
								pView->m_listData.SetItemText(Hang_Num[mm],6,_T("失败"));
								pView->m_listData.SetItemText(Hang_Num[mm],7,_T("15000ms/超时"));
								pView->m_listData.EnsureVisible(Hang_Num[mm],FALSE);
					            pView->m_listData.RedrawItems(Hang_Num[mm],Hang_Num[mm]);
							}
						}

						INT32U z_time2=GetSysTimeInterval(timeclk376[0].timeclk);
						INT32U z_time2_ms;
						CString strTest2;
						strTest2.Format(_T("%d 分 %d 秒 %d 毫秒"),z_time2/60000,(z_time2%60000)/1000,(z_time2%60000)%1000);
						pView->C_TI.SetWindowText(strTest2);
						CString strTest;
	                    strTest.Format(_T("%d"),pView->m_falnum);
	                    pView->C_FL.SetWindowText(strTest);
		                pView->m_BingfReadMet.SetWindowText(_T("并发抄表"));
		                return 0;
	   }
	   //LeaveCriticalSection(&cs);


	//INT32U z_time2=GetSysTimeInterval(timeclk376[0].timeclk);
	//INT32U z_time2_ms;
	//CString strTest2;
	//strTest2.Format(_T("%d 分 %d 秒 %d 毫秒"),z_time2/60000,(z_time2%60000)/1000,(z_time2%60000)%1000);
	//pView->C_TI.SetWindowText(strTest2);
	//if(pView->m_falnum+pView->m_sussnum==COUNT){
	//	   pView->m_BingfReadMet.SetWindowText(_T("并发抄表"));
	//	   return 0;
	// }

	   Sleep(5);
	}
	return 0;
}


DWORD WINAPI ThreadSendbufBingF (PVOID pParam)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewTabErrMet * pView = (CCKQViewTabErrMet *)pParam;
	CSimJzq   gSimJzqSend;
	CGW13762 Cgw13762Send;
	INT8U Sendbufdata[2000] ,AddrBuf[7],TEIBuf[2],AddrMain[6];
	//int COUNT=pView->nSelect;
	INT8U ack = -1;
	INT16U Sendbuflen = 0,temp16 = 0;
	DWORD  nsize = 0;
	//int n=0;
	while(1){
		Sleep(10);//线程扫描时间
		//EnterCriticalSection(&cs);
		//if(SendOk==1){//如果允许发送 进入发送
		//	LeaveCriticalSection(&cs);
			
			//if(pView->nStop==1){
			//	
			//	pView->m_BingfReadMet.SetWindowText(_T("并发抄表"));
			//    return 0;
		 //   }
			
			//EnterCriticalSection(&cs);
			//LeaveCriticalSection(&cs);
			while(Send_COUNT){
				
				//EnterCriticalSection(&cs);
				if(pView->nStop==1){
                    //LeaveCriticalSection(&cs);
					pView->m_BingfReadMet.SetWindowText(_T("并发抄表"));
					return 0;
				}
				//else{
				//	LeaveCriticalSection(&cs);
				//}
				if(n_Node<Send_COUNT2){
					Sleep(100);
					//int cp_n_Node=n_Node;
					//pMain->m_tools._str16tobuf16(strAllDatalist[cp_n_Node] , AddrBuf , temp16 , true);//小端模式
					//AddrBuf[6]=2;
					//INT8U tmpbuf[100];
			
					//INT16U len16;
					//tmpbuf[0]=AddrBuf[6];
					//tmpbuf[1] = 0x00;
					//sDtl2007_Read CmdData645;
					//gSimJzqSend.CodeReadData9707Cmd(AddrBuf[6],0x00010000,AddrBuf,1,CmdData645);
					//tmpbuf[2] = CmdData645.s_vDstCmdLen;
					//tmpbuf[3] = 0x00;
					//BufToBuf(&tmpbuf[4],CmdData645.s_pDstCmdBuf,CmdData645.s_vDstCmdLen);
					//len16 = CmdData645.s_vDstCmdLen+ 4;
					//ack = Cgw13762Send.Code376_2_HostBufNodeFrame(AddrBuf,0xF1,F1,tmpbuf,len16,ptSendQGDW376_2);
					//if(ack == DACK_SUCESS)
					//{
					//	
						gSimJzqSend.BF_SendBufToCom(ptSendQGDW376_2[n_Node].s_SendDataBuf ,ptSendQGDW376_2[n_Node].s_SendDataLen);
						timeclk376[ptSendQGDW376_2[n_Node].s_head.s_Msg_Seq].timeclk=GetSysTimeClk();
						Send_COUNT--;
						n_Node=n_Node+1;
						//MAXBF_cp=MAXBF_cp-1;
						//EnterCriticalSection(&cs);
						//MAXBF=MAXBF_cp;
						//LeaveCriticalSection(&cs);
					//}


				}
				else{
					pView->m_BingfReadMet.SetWindowText(_T("并发抄表"));
					return 0;
				}
				//LeaveCriticalSection(&cs);
			}
			//for(;n_Node<COUNT;n_Node++){
			//	LeaveCriticalSection(&cs);
			//	Sleep(10);
			//	
			//	if(pView->nStop==1){
			//		pView->m_BingfReadMet.SetWindowText(_T("并发抄表"));
			//		return 0;
			//	}
			//	int cp_n_Node=n_Node;
			//	EnterCriticalSection(&cs);
			//	if(SendOk==1){
			//		LeaveCriticalSection(&cs);
			//	    //发送代码写到这里
			//	   		pMain->m_tools._str16tobuf16(strAllDatalist[cp_n_Node] , AddrBuf , temp16 , true);//小端模式
		 //               //pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrMain, temp16_2 , true);

			//			AddrBuf[6]=2;
			//			INT8U tmpbuf[100];
			//
			//			INT16U len16;
			//			tmpbuf[0]=AddrBuf[6];
			//			tmpbuf[1] = 0x00;
			//			sDtl2007_Read CmdData645;
			//			gSimJzq.CodeReadData9707Cmd(AddrBuf[6],0x00010000,AddrBuf,1,CmdData645);
			//			tmpbuf[2] = CmdData645.s_vDstCmdLen;
			//			tmpbuf[3] = 0x00;
			//			BufToBuf(&tmpbuf[4],CmdData645.s_pDstCmdBuf,CmdData645.s_vDstCmdLen);
			//			len16 = CmdData645.s_vDstCmdLen+ 4;
			//			ack = Cgw13762.Code376_2_HostBufNodeFrame(AddrBuf,0xF1,F1,tmpbuf,len16,ptSendQGDW376_2);
			//			if(ack == DACK_SUCESS)
			//			{
			//				gSimJzq.SendBufToCom(ptSendQGDW376_2.s_SendDataBuf ,ptSendQGDW376_2.s_SendDataLen);
			//				timeclk376[ptSendQGDW376_2.s_head.s_Msg_Seq].timeclk=GetSysTimeClk();
			//				//timeclk376[cp_n_Node].s_Seq = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
			//			}


			//		//根据n_Node的值进行发送下一个 代表已发送的序号（从0开始）  又代表第几个表 
			//	}
			//	else{
			//		LeaveCriticalSection(&cs);
			//		break;
			//	}
			//	if(n_Node==COUNT-1){
			//		SendOk=0;
			//		LeaveCriticalSection(&cs);
			//	}
			//				
			//}
		//}
		//else{
		//	LeaveCriticalSection(&cs);
		//}
			//if(pView->nStop==1){
			//	pView->m_BingfReadMet.SetWindowText(_T("并发抄表"));
			//    return 0;
		 //   }
		//if(n_Node==COUNT){//如果发送序号完了 并且等待5秒都没接到发送信号 就停止所有发送
		//	for(int n=0;n<50;n++){
		//		Sleep(100);
		//	}
		//	if(SendOk==0){
		//		pView->m_BingfReadMet.SetWindowText(_T("并发抄表"));
  //             return 0;
		//	}
		//}
          		if(Send_COUNT==0){
					//pView->m_BingfReadMet.SetWindowText(_T("并发抄表"));
					//pView->m_hThreadsend_RevBingF=CreateThread (NULL,0,ThreadRevbufBingF,pView,0,NULL);
			        //CloseHandle(pView->m_hThreadsend_RevBingF);
					return 0;
				}
		//Sleep(5);//线程扫描时间
	}
	return 0;
}


void CCKQViewTabErrMet::OnBnClickedStartreadbingf()
{
	// TODO: 在此添加控件通知处理程序代码 并发抄表
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	nSelect = m_listData.GetSelectedCount();
	if (nSelect == 0) 
	{ 
		m_StartReadMet.SetWindowText(_T("开始抄表"));
		AfxMessageBox(_T("未选中节点"));
		return;

	} 
	for(int n=0;n<1000;n++){
		timeclk376->timeclk=0;;//保存每帧发送前的时间等 按SEQ号保存  对应获取
        strAllDatalist[n]=_T("");//保存选中的地址按顺序
		ptSendQGDW376_2[n].s_SendDataLen=0;
        Hang_Num[n]=0;
	}
	COUNT=0;
	Send_COUNT=0;
	Rev_COUNT=0;
	Send_COUNT2=0;
	n_Node=0;
	m_sussnum=0;
	m_falnum=0;
	m_Ztime=0;
	MAXBF=16;
	pMain->m_376seq=0;
	C_SU.SetWindowText(_T("0"));
	C_FL.SetWindowText(_T("0"));
	C_TI.SetWindowText(_T("00:00:00"));
	CString str;
	CString NodeMAC,NodeTEI,NodeSTATE;

	CSimJzq   gSimJzqSend;
	CGW13762 Cgw13762Send;
	INT8U Sendbufdata[2000] ,AddrBuf[7],TEIBuf[2],AddrMain[6];
	//int COUNT=pView->nSelect;
	INT8U ack = -1;
	INT16U Sendbuflen = 0,temp16 = 0;
	DWORD  nsize = 0;
	

	POSITION pos = m_listData.GetFirstSelectedItemPosition(); 
	int num_strAllDatalist=0;
	while (nSelect) 
	{ 




		Hang_Num[num_strAllDatalist] = m_listData.GetNextSelectedItem(pos); 
		NodeTEI=m_listData.GetItemText(Hang_Num[num_strAllDatalist],2);
		NodeSTATE=m_listData.GetItemText(Hang_Num[num_strAllDatalist],3);
//-----------------------测试抄表-------------------------------------
		if(NodeTEI==_T("1")||NodeSTATE==_T("未入网")){	
		   nSelect=nSelect-1;
           continue;
		}
		
		strAllDatalist[num_strAllDatalist]=m_listData.GetItemText(Hang_Num[num_strAllDatalist],1);
		              

					pMain->m_tools._str16tobuf16(strAllDatalist[num_strAllDatalist] , AddrBuf , temp16 , true);//小端模式
					AddrBuf[6]=2;
					INT8U tmpbuf[100];
			
					INT16U len16;
					tmpbuf[0]=AddrBuf[6];
					tmpbuf[1] = 0x00;
					sDtl2007_Read CmdData645;
					sDtl2007_Read CmdData645_2;
					//gSimJzqSend.CodeReadData9707Cmd(AddrBuf[6],0x0400010C,AddrBuf,1,CmdData645_2);
					gSimJzqSend.CodeReadData9707Cmd(AddrBuf[6],0x00010000,AddrBuf,1,CmdData645);
					tmpbuf[2] = CmdData645.s_vDstCmdLen;//+CmdData645_2.s_vDstCmdLen;
					tmpbuf[3] = 0x00;
					//BufToBuf(&tmpbuf[4],CmdData645_2.s_pDstCmdBuf,CmdData645_2.s_vDstCmdLen);
					BufToBuf(&tmpbuf[4],CmdData645.s_pDstCmdBuf,CmdData645.s_vDstCmdLen);
					len16 = CmdData645.s_vDstCmdLen+ 4;
					ack = Cgw13762Send.Code376_2_HostBufNodeFrame(AddrBuf,0xF1,F1,tmpbuf,len16,ptSendQGDW376_2[num_strAllDatalist]);
					if(ack == DACK_SUCESS)
					{
					}
					num_strAllDatalist++;
		//NodeTEI=pView->m_listData.GetItemText(nItem,2);
		//NodeSTATE=pView->m_listData.GetItemText(nItem,3);
		//NodeTYPE=pView->m_listData.GetItemText(nItem,4);
		//pMain->m_tools._str16tobuf16(NodeMAC , AddrBuf , temp16 , true);//小端模式
		//pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrMain, temp16_2 , true);
		//pMain->m_tools._str16tobuf16(NodeTEI , TEIBuf , teilen , true);
//-----------------------测试抄表-------------------------------------
		nSelect=nSelect-1;
	}
	m_loopRcv13762.ClrRcvBuf();
	COUNT=num_strAllDatalist;
	Send_COUNT=COUNT;
	Send_COUNT2=COUNT;
	Rev_COUNT=COUNT;
	
	//InitializeCriticalSection(&cs);
	//InitializeCriticalSection(&cs2);
	m_BingfReadMet.GetWindowTextW(str);
	if(str=="并发抄表"){
		nStop=0;

		CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	    CString strMessageAddress;
	    pMain->m_bCommunictStop = false;
		if (pMain->m_bConnected == TRUE)
		{
			m_hThreadsend_RevBingF=CreateThread (NULL,0,ThreadRevbufBingF,this,0,NULL);
			CloseHandle(m_hThreadsend_RevBingF);
			//Sleep(2000);
			m_hThreadsend_SendBingF=CreateThread (NULL,0,ThreadSendbufBingF,this,0,NULL);
			CloseHandle(m_hThreadsend_SendBingF);
		}
		else
		{
			AfxMessageBox(_T("请打开串口！"));
			return;
		}
		m_BingfReadMet.SetWindowText(_T("停止并发"));
	}
	else{
		nStop=1;
        m_BingfReadMet.SetWindowText(_T("并发抄表"));
	}
}
