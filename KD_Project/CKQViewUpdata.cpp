// CKQViewUpdata.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "CKQViewUpdata.h"
#include "AccessData.h"
#include "MainFrm.h"
#include "SimJzq.h"
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
}

BEGIN_MESSAGE_MAP(CCKQViewUpdata, CFormView)
	ON_BN_CLICKED(IDC_BTN_CHOOSEFILE, &CCKQViewUpdata::OnBnClickedBtnChoosefile)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CCKQViewUpdata::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_BEGINUPDATA, &CCKQViewUpdata::OnBnClickedBtnBeginupdata)
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
	switch(pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_SUCCESS:
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT); 
		hbr =  CreateSolidBrush(RGB(0,255,0));
		break;
	case IDC_STATIC_SENDING:
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT); 
		hbr =  CreateSolidBrush(RGB(0,255,255));
		break;
	case IDC_STATIC_UNSEND:
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT); 
		hbr =  CreateSolidBrush(RGB(255,0,0));
		break;
	}
	return hbr;
}

void CCKQViewUpdata::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	SetNewFont();
	GetDlgItem(IDC_STATIC_SUCCESS)->SetFont(&m_fontStatic);
	GetDlgItem(IDC_STATIC_SENDING)->SetFont(&m_fontStatic);
	GetDlgItem(IDC_STATIC_UNSEND)->SetFont(&m_fontStatic);

	CRect rect;
	CRect rect1;
	GetClientRect(rect1);
	GetDlgItem(IDC_BTN_BEGINUPDATA)->GetWindowRect(rect);
	ScreenToClient(&rect);
	rect1.left += 10;
	rect1.top = rect.bottom + 10;
	rect1.right -= 10;
	rect1.bottom -= 10;
	m_listData.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT | LVS_ALIGNLEFT | WS_TABSTOP ,rect1,this,IDC_LISTUPDATAMSG);//| LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES
	m_listData.InsertColumn(0,_T(""),LVCFMT_LEFT,20);
	m_listData.InsertColumn(1,_T(""),LVCFMT_LEFT,30);
	m_listData.InsertColumn(2,_T("MAC地址"),LVCFMT_CENTER,200);
	m_listData.InsertColumn(3,_T("状态"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(4,_T("进度"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(5,_T("耗时"),LVCFMT_CENTER,100);
	m_listData.InsertColumn(6,_T("版本号"),LVCFMT_CENTER,200);
	m_listData.InsertColumn(7,_T("备注"),LVCFMT_CENTER,200);
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
		delete[] pFileName;
	}
	
}
void CCKQViewUpdata::OnBnClickedBtnRefresh()
{
	
    CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CAccessData access;
	CString strAllDatalist[6];
	CString strlist[1000];
	CString str;
	int nNumb = 0 , nAlldataNumb , nCount;
	m_listData.DeleteAllItems();
	access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPShow") , _T("TP_MAC,TP_ROLE") ,_T("") ,strlist ,nAlldataNumb);
	//access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPShow") , _T("TP_MAC,TP_ROLE") ,_T("") ,strlist ,nAlldataNumb);
	for (int n = 0 ; n < nAlldataNumb ; n++)
	{
		str.Format(_T("%d") , n + 1);
		m_tools.Split(strlist[n] , _T("$") ,strAllDatalist , nNumb);
		if (strAllDatalist[0].Mid(0 , 10) != "BEBEBEBEBE")
		{
			nCount = m_listData.GetItemCount();
			m_listData.InsertItem(nCount , _T(""));
			m_listData.SetItemText(nCount , 1 ,str);
			m_listData.SetItemText(nCount , 2 ,strAllDatalist[0]);
			switch(_ttoi(strAllDatalist[1]))
			{
			case 2:
				m_listData.SetItemText(nCount , 7 ,_T("CCO"));
				break;
			case 4:
				m_listData.SetItemText(nCount , 7 ,_T("STA"));
				break;
			}
		}
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

DWORD WINAPI ThreadSendbufUpData (PVOID pParam)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewUpdata * pView = (CCKQViewUpdata *)pParam;
	sPartQGDW376_2CreatFrame ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDWF0376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;

	//南网标准
	sPartQCSG376_2CreatFrame ptSendQCSG376_2;
	sPartQCSG376_2DeCodeFrame ptRecvQCSGF0376_2;
	sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2;

	CString strShuxingBiaoshiLen;
	INT8U Sendbufdata[JZQ_MAX_BUFF_LEN] ,AddrBuf[7] ;
	INT16U Sendbuflen = 0,temp16 = 0;
	INT8U ack = -1;
	pView->SetUpdataListData();
	pView->m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
	CString strDatalen = _T("") , str = _T("");

	if (pMain->NW_OR_GW==1){ //南网标准
		CString strNrOfSectors;
		strNrOfSectors.Format(_T("%d"), pView->m_NrOfSectors);
		strNrOfSectors=pView->m_tools._str10tostr16(strNrOfSectors,2);
		strNrOfSectors=strNrOfSectors.Left(4).Right(2)+strNrOfSectors.Left(2);

		CString strFileSize;
		strFileSize.Format(_T("%d"), pView->m_FileSize);
		strFileSize=pView->m_tools._str10tostr16(strFileSize,4);
		strFileSize=strFileSize.Left(8).Right(2)+strFileSize.Left(6).Right(2)+strFileSize.Left(4).Right(2) + strFileSize.Left(2);
	
		pView->m_tools._str16tobuf16(_T("0200000000000000") +  strNrOfSectors + strFileSize + _T("0000"), Sendbufdata , Sendbuflen);
		ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x07 , FN_07_F1 , Sendbufdata , Sendbuflen , ptSendQCSG376_2 ,ptRecvQCSGF0376_2 , ptRecvQCSG376_2);
		if (ack == 0 && ptRecvQCSG376_2.s_head.s_AFN == 0x00 && ptRecvQCSG376_2.s_head.s_FN == FN_00_F1)
		{
			for(POSITION pos = pView->m_listStrShengjiData.GetHeadPosition(); pos != NULL;)
			{
				if (pMain->m_bCommunictStop)
				{
					return false;
				}
				strShuxingBiaoshiLen=(CString)pView->m_listStrShengjiData.GetNext(pos);
			
				CString strCurSector;
				strCurSector=strShuxingBiaoshiLen.Left(4);
				strCurSector=strCurSector.Left(4).Right(2)+strCurSector.Left(2);

				pView->m_tools._str16tobuf16(strShuxingBiaoshiLen  , Sendbufdata , Sendbuflen);
				ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x07 , FN_07_F2 , Sendbufdata , Sendbuflen , ptSendQCSG376_2 ,ptRecvQCSGF0376_2 , ptRecvQCSG376_2);
				switch(ack)
				{
				case 0:
					if (ptRecvQCSG376_2.s_head.s_AFN == 0x00 && ptRecvQCSG376_2.s_head.s_FN == FN_00_F2)
					{
						switch(ptRecvQCSG376_2.s_RcvDataBuf[0])
						{
						case 0:
							str = _T(">>>>失败:通信超时");
							break;
						case 1:
							str = _T(">>>>失败:无效数据单元");
							break;
						case 2:
							str = _T(">>>>失败:长度错");
							break;
						case 3:
							str = _T(">>>>失败:校验错误");
							break;
						case 4:
							str = _T(">>>>失败:信息类不存在");
							break;
						case 5:
							str = _T(">>>>失败:格式错误");
							break;
						case 6:
							str = _T(">>>>失败:表号重复");
							break;
						case 7:
							str = _T(">>>>失败:表号不存在");
							break;
						case 8:
							str = _T(">>>>失败:电表应用层无应答");
							break;
						case 9:
							str = _T(">>>>失败:主节点忙");
							break;
						case 10:
							str = _T(">>>>失败:主节点不支持此命令");
							break;
						case 11:
							str = _T(">>>>失败:从节点不应答");
							break;
						case 12:
							str = _T(">>>>失败:从节点不在网内");
							break;
						}
						str += _T("\r\n");
					}
					else if (ptRecvQCSG376_2.s_head.s_AFN == 0x00 && ptRecvQCSG376_2.s_head.s_FN == FN_00_F1)
					{
						pView->SetDlgItemTextW(IDC_STATIC_SENDING, _T("升级传输中（")+strCurSector+_T("）"));
						::PostMessage((HWND)(AfxGetApp()->m_pMainWnd), WM_PAINT, NULL, NULL); 
					}
					else
					{

					}
					break;
				case 0x13://失败
					break;
				case 0x30://SEQ不一致
					break;
				case 0x0A://主节点不支持此命令
					break;
				default:
					break;
				}
			}

			pView->SetDlgItemTextW(IDC_STATIC_SENDING, _T("升级传输结束"));
			::PostMessage((HWND)(AfxGetApp()->m_pMainWnd), WM_PAINT, NULL, NULL); 
		}
	}
	else{

		pView->m_tools._str16tobuf16(_T("0000000000000000000000")  , Sendbufdata , Sendbuflen);
		ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x15 , F1 , Sendbufdata , Sendbuflen , ptSendQGDW376_2 ,ptRecvQGDWF0376_2 , ptRecvQGDW376_2);
		if (ack == 0 && ptRecvQGDW376_2.s_head.s_AFN == 0x15)
		{
			for(POSITION pos = pView->m_listStrShengjiData.GetHeadPosition(); pos != NULL;)
			{
				if (pMain->m_bCommunictStop)
				{
					return false;
				}
				strShuxingBiaoshiLen=(CString)pView->m_listStrShengjiData.GetNext(pos);
				pView->m_tools._str16tobuf16(strShuxingBiaoshiLen  , Sendbufdata , Sendbuflen);
				ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x15 , F1 , Sendbufdata , Sendbuflen , ptSendQGDW376_2 ,ptRecvQGDWF0376_2 , ptRecvQGDW376_2);
				switch(ack)
				{
				case 0:
					if (ptRecvQGDW376_2.s_head.s_AFN == 0x00 && ptRecvQGDW376_2.s_head.s_FN == F2)
					{
						switch(ptRecvQGDW376_2.s_RcvDataBuf[0])
						{
						case 0:
							str = _T(">>>>失败:通信超时");
							break;
						case 1:
							str = _T(">>>>失败:无效数据单元");
							break;
						case 2:
							str = _T(">>>>失败:长度错");
							break;
						case 3:
							str = _T(">>>>失败:校验错误");
							break;
						case 4:
							str = _T(">>>>失败:信息类不存在");
							break;
						case 5:
							str = _T(">>>>失败:格式错误");
							break;
						case 6:
							str = _T(">>>>失败:表号重复");
							break;
						case 7:
							str = _T(">>>>失败:表号不存在");
							break;
						case 8:
							str = _T(">>>>失败:电表应用层无应答");
							break;
						case 9:
							str = _T(">>>>失败:主节点忙");
							break;
						case 10:
							str = _T(">>>>失败:主节点不支持此命令");
							break;
						case 11:
							str = _T(">>>>失败:从节点不应答");
							break;
						case 12:
							str = _T(">>>>失败:从节点不在网内");
							break;
						}
						str += _T("\r\n");
					}
					else
					{

					}
					break;
				case 0x13://失败
					break;
				case 0x30://SEQ不一致
					break;
				case 0x0A://主节点不支持此命令
					break;
				default:
					break;
				}
			}
		}
	}
	
	return 0;
}
void CCKQViewUpdata::OnBnClickedBtnBeginupdata()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strMessageAddress;
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{
		m_hThreadsend=CreateThread (NULL,0,ThreadSendbufUpData,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("请打开串口！"));
	}
}
