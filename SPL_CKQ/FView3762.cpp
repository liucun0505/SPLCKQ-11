// FView3762.cpp : 实现文件
//



#include "stdafx.h"
#include "SPL_CKQ.h"
#include "FView3762.h"
#include "DlgAddress.h"
#include "DlgXYData.h"
#include "MainFrm.h"
#include "Dlg13762UpdataConfig.h"
#include "DlgSaveDebugInfo.h"
#include "DlgExtStaVersion.h"
#include "DlgExtStaDevStatus.h"
#include "DIALOGF1F0TIMEOUT.h"
#include "DlgSaveNodeInfo.h"
#include "SimJzq.h"
#include "DlgExtReadMeter.h"
extern CSimJzq  gSimJzq;
#include "GW13762.h"
extern CGW13762 Cgw13762;
#include "CSG13762.h"
extern CCSG13762 Ccsg13762;



// CFView3762

IMPLEMENT_DYNCREATE(CFView3762, CFormView)



CFView3762::CFView3762()
	: CFormView(CFView3762::IDD)
{

	m_strPWData = _T("");
	m_bDCEditAddr = false;
	m_bZuZhen = false;
	m_nDClick = 0;
	m_bFEF001 = false;
	m_fp = NULL;
	m_F1F0_TimeOut = 10;

}

CFView3762::~CFView3762()
{
}

void CFView3762::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_DATA, m_treeData);
	DDX_Control(pDX, IDC_EDIT_SHOW, m_editShow);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_combType);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_editAddress);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSend);
	DDX_Control(pDX, IDC_BUTTON_ZUZHEN, m_btnZuZhen);
	DDX_Control(pDX, IDC_BUTTON_ADDRESS, button_address);
}

BEGIN_MESSAGE_MAP(CFView3762, CFormView)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_TREE_DATA, &CFView3762::OnClickTreeData)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_DATA, &CFView3762::OnDblclkTreeData)
//	ON_WM_MBUTTONDBLCLK()
ON_WM_LBUTTONDBLCLK()
ON_EN_SETFOCUS(IDC_EDIT_ADDRESS, &CFView3762::OnEnSetfocusEditAddress)
ON_EN_KILLFOCUS(IDC_EDIT_ADDRESS, &CFView3762::OnEnKillfocusEditAddress)
ON_BN_CLICKED(IDC_BUTTON_ADDRESS, &CFView3762::OnBnClickedButtonAddress)
ON_BN_CLICKED(IDC_BUTTON_SEND, &CFView3762::OnBnClickedButtonSend)
ON_BN_CLICKED(IDC_BUTTON_XY, &CFView3762::OnBnClickedButtonXy)
ON_BN_CLICKED(IDC_BUTTON_STOP, &CFView3762::OnBnClickedButtonStop)
ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CFView3762::OnBnClickedButtonClear)
ON_BN_CLICKED(IDC_BUTTON_ZUZHEN, &CFView3762::OnBnClickedButtonZuzhen)
ON_BN_CLICKED(IDC_BUTTON1, &CFView3762::OnBnClickedButton1)
END_MESSAGE_MAP()


// CFView3762 诊断

#ifdef _DEBUG
void CFView3762::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCEk
void CFView3762::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG
const  INT8U CRCHTalbe[] =
{
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40
};

const  INT8U CRCLTalbe[] = 
{
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
	0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
	0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
	0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
	0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
	0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
	0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
	0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
	0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
	0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
	0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
	0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
	0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
	0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
	0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
	0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
	0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
	0x41, 0x81, 0x80, 0x40
};


// CFView3762 消息处理程序
void CFView3762::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	m_gw13762.SetMainAdd(pMain->m_HostNodeAddress);
	gSimJzq.SetMainAdd(pMain->m_HostNodeAddress);

	
	m_editAddress.SetWindowTextW(_T("000000B00400"));

	////南网控制
	if(pMain->NW_OR_GW==1)
	{
		m_editAddress.SetWindowTextW(_T("222222222222010000000000"));
		button_address.SetWindowText(_T("地址域设置"));
		GetDlgItem(IDC_BUTTON_ZUZHEN)->ShowWindow(SW_HIDE);
	}

	if (pMain->m_nChooseView == OPENNET)
	{
		m_btnZuZhen.ShowWindow(SW_HIDE);
	}
	
	CRect rect;
	GetDlgItem(IDC_TREE_DATA)->GetWindowRect(&rect); 
	ScreenToClient(&rect);
	m_dlg13762Zuzhen.Create(IDD_DIALOG_13862,this);
	m_dlg13762Zuzhen.SetWindowPos(NULL,rect.left,rect.top,rect.right,rect.bottom,SWP_HIDEWINDOW);
	
	UpdataTreeData();
}

void CFView3762::UpdataTreeData()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	m_combType.AddString(_T("0:保留"));
	m_combType.AddString(_T("1:集中式路由载波通信"));
	m_combType.AddString(_T("2:分布式路由载波通信"));
	m_combType.AddString(_T("3:宽带载波"));
	m_combType.AddString(_T("10:微功率无线通讯"));
	m_combType.AddString(_T("20:以太网通讯"));
	m_combType.SetCurSel(3);
	m_treeData.DeleteAllItems();
	wchar_t   buf[10000]; 
	wchar_t   buff[10000];
	m_hTree = m_treeData.InsertItem(_T("载波协议"));
	HTREEITEM hPrieant = NULL;
	GetPrivateProfileSectionNames(buf,sizeof(buf), pMain->m_PeiZhi);//".\\配置文件\\13762树控件.ini")); 
	CString str;	
	for(wchar_t*   Name=buf;   *Name!= '\0';   Name+=wcslen(Name)+1) 
	{
		str.Format(_T("%s"), Name);
		hPrieant=m_treeData.InsertItem(str,m_hTree);
		GetPrivateProfileSection(str,buff,sizeof(buff), pMain->m_PeiZhi);//_T(".\\配置文件\\13762树控件.ini")); 
		CString  strr;
		CString  sub;
		for(wchar_t*   Namee=buff;   *Namee!= '\0';   Namee+=wcslen(Namee)+1)
		{
			sub.Format(_T("%s"), Namee);
			m_treeData.InsertItem(sub.Mid(7),hPrieant);
		}
		m_treeData.Expand(hPrieant,TVE_EXPAND);
		m_treeData.SortChildren(hPrieant);
	}

	m_treeData.Expand(m_hTree,TVE_EXPAND);
}
// CView13762 消息处理程序
void CFView3762::KongjianSize(int nID, int cx, int cy, bool bComb)
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
		rect.top=(int)(rect.top*((float)cy/(float)fcy)); 
		rect.bottom = (int)(rect.bottom*((float)cy/(float)fcy)) + nBottom;
		pWnd->MoveWindow(rect);//设置控件位置 
	}
}

void CFView3762::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(rect); 
	if (rect.right == 0 || rect.bottom == 0 )
	{
		return;
	}

	KongjianSize(IDD_DIALOG_13862,rect.right,rect.bottom);
	KongjianSize(IDC_BUTTON_ZUZHEN,rect.right,rect.bottom);
	KongjianSize(IDC_BUTTON_SEND,rect.right,rect.bottom); 
	KongjianSize(IDC_BUTTON_STOP,rect.right,rect.bottom); 
	KongjianSize(IDC_BUTTON_CLEAR,rect.right,rect.bottom); 
	KongjianSize(IDC_TREE_DATA,rect.right,rect.bottom); 
	KongjianSize(IDC_EDIT_SHOW,rect.right,rect.bottom); 
	KongjianSize(IDC_EDIT_ADDRESS,rect.right,rect.bottom); 
	KongjianSize(IDC_STATIC1,rect.right,rect.bottom); 
	KongjianSize(IDC_BUTTON_ADDRESS,rect.right,rect.bottom); 
	KongjianSize(IDC_BUTTON_XY,rect.right,rect.bottom); 
	KongjianSize(IDC_COMBO_TYPE,rect.right,rect.bottom,TRUE); 
	GetClientRect(m_cRect);
}

void CFView3762::OnClickTreeData(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_TREEVIEW* pHdr = (NM_TREEVIEW*)pNMHDR;
	UINT uFlag = 0 ;
	GetCursorPos(&m_point);
	m_treeData.ScreenToClient(&m_point);
	HTREEITEM item = m_treeData.HitTest(m_point, &uFlag);
	if(item) 
	{
		if (uFlag & TVHT_ONITEMSTATEICON)  //检测是否点击了CHECK框
		{
			BOOL bCheck = m_treeData.GetCheck(item);
			SetItemCheckState(item, !bCheck); //递归查找子节点的邻节点
		} 
	}
	*pResult = 0;
}

void CFView3762::SetItemCheckState(HTREEITEM item, BOOL bCheck)
{  
	HTREEITEM child = m_treeData.GetChildItem(item);
	while(child)
	{
		m_treeData.SetCheck(child, bCheck);
		SetItemCheckState(child, bCheck);
		child = m_treeData.GetNextItem(child, TVGN_NEXT);
	}
}

CString CFView3762::SetBeizhu(int nCishu,CString strBeizhu)
{
	CString strData;
	int b=0;
	bool bloop=false;
	int a=1;
	for(a=1;a<(wcslen(strBeizhu)+1);a++)
	{
		if (strBeizhu.Left(a).Right(1)==";")
		{
			if (bloop==true) break;
			if (strBeizhu.Left(a+4).Right(4)=="loop")
			{
				b=a;
				bloop=true;
			}
		}
	}
	m_nLoopData = 0;
	CString strZuo=strBeizhu.Left(b);
	CString strYou=strBeizhu.Right(wcslen(strBeizhu)-a);
	CString strYoubeizhu = strYou;
	for (a=0;a<wcslen(strYoubeizhu);a++)
	{
		if (strYoubeizhu.Mid(a,1)==";")
		{
			if (strYoubeizhu.Left(4) == "DADT"||strYoubeizhu.Left(3) == "bin"||strYoubeizhu.Left(1) == "A"||strYoubeizhu.Left(4) == "char")
			{
				m_nLoopData+=1;
			}
			if (strYoubeizhu.Left(4) == "bits")
			{
				m_nLoopData+=_ttoi(strYoubeizhu.Mid(9,1));
			}
			if (strYoubeizhu.Left(a+4) == "bit,")
			{
				m_nLoopData+=_ttoi(strYoubeizhu.Mid(8,1));
			}
			strYoubeizhu = strYoubeizhu.Mid(a+1);
			a=0;
		}
	}
	CString strYouzong=_T("");
	for(a=0;a<nCishu;a++)
	{
		strYouzong+=strYou;
	}
	strData=strZuo+strYouzong;
	return strData;
}
CString CFView3762::SetGershi(int nCishu,CString strGeshi)
{
	CString strData;
	int nFenhao=1;
	int a=0;
	for(a=2;a<(wcslen(strGeshi)+1);a++)
	{
		if (strGeshi.Right(a).Left(1)==";")
		{
			if (nFenhao==m_nLoopData)
			{
				break;
			}
			nFenhao++;
		}
	}
	CString strZuo=strGeshi.Left(wcslen(strGeshi)-a+1);
	CString strYou=strGeshi.Right(a-1);

	CString strYouzong=_T("");
	CString strB;
	CString strYouN;
	bool bS=false;

	CString strGuodu;
	for(a=0;a<nCishu;a++)
	{
		strGuodu=strYou;
		for(int b=1;b<(int)wcslen(strGuodu);b++)
		{
			if (strGuodu.Left(b).Right(1)=="S")
			{
				strB.Format(_T("%d"),a+1);
				strGuodu=strGuodu.Left(b-1)+strB+strGuodu.Right(wcslen(strGuodu)-b);
				bS=true;
			}
		}
		if (bS==false)
		{
			strGuodu=strYou;
		}
		strYouzong+=strGuodu;
	}
	strData=strZuo+strYouzong;
	return strData;
}

#define READ_LOG_LEN 1024

void CFView3762::Save_log_File(INT8U* F8DataHead)
{
	CFile mFile(m_strFilePath_f0f1, CFile::modeWrite | CFile::modeCreate);
	INT32U sendpara[2];
	INT8U ack = -1;
	INT16U i;
	INT8U bitmap[6];
	INT8U retrycnt = 0;
	CString tmpstr;

	sendpara[1] = READ_LOG_LEN;
	sendpara[0] = 0;

	SetWindowText(_T("------------------------------读取日志-----------------------\n"));

	for (i = 0; i < 41; i++)
	{
	retry:
		TRACE("\nseg %d\n",i);
		sendpara[0] = i* READ_LOG_LEN;
		ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43, F8DataHead, 0xF0, F1, (INT8U *)sendpara, 6, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);

		if (0 == ack)
		{
			if (m_ptRecvQGDW376_2.s_head.s_AFN == 0xF0 && m_ptRecvQGDW376_2.s_head.s_FN == F1)
			{
				mFile.Write((INT8U *)m_ptRecvQGDW376_2.s_RcvDataBuf+6, READ_LOG_LEN);
				bitmap[i / 8] |= i % 8;
				tmpstr.Format(_T(">>>>接收成功段: %d\n"), i);
				SetWindowText(tmpstr);
			}
			else
			{
				if (retrycnt++ < 3)
				{
					goto retry;
				}
				else
				{
					retrycnt = 0;
					tmpstr.Format(_T(">>>>数据包有误: %d\n"), i);
					SetWindowText(tmpstr);
				}
			}
		}
		else
		{
			
			if (retrycnt++ < 3)
			{
				goto retry;
			}
			else
			{
				retrycnt = 0;
				tmpstr.Format(_T(">>>>接收超时: %d\n"), i);
				SetWindowText(tmpstr);
			}
		}
	}

	mFile.Close();
	SetWindowText(_T("--------------------------------------------------------------------------------\n"));
	return;
}

void CFView3762::OnDblclkTreeData(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nGeFen=0;
	UINT uFlag = 0 ;
	HTREEITEM htree=m_treeData.HitTest(m_point, &uFlag);
	CString str=m_treeData.GetItemText(htree);
	HTREEITEM hpartree=m_treeData.GetParentItem(htree);
	CString strZuming=m_treeData.GetItemText(hpartree);
	CString strWhere = str.Mid(1,4);
	CString strData;
	CString strlistData[10];
	CString strDatalen;
	CString strSetData;
	int nHang = 0;
	if (strZuming == "15H文件传输" && strWhere == "F001")
	{
		CDlg13762UpdataConfig dlgUpdataConfig;
		dlgUpdataConfig.DoModal();
		return;
	}
	else if(strZuming == "F0H扩展命令" && strWhere == "F021")
	{
		DlgSaveDebugInfo dlgSaveDebugInfo;

		dlgSaveDebugInfo.DoModal();
		return;	
	}
	else if(strZuming == "F0H扩展命令" && strWhere == "F153")
	{
		DlgExtStaVersion dlgExtStaVersion;

		dlgExtStaVersion.DoModal();
		return;	
	}
	
	else if (strZuming == "14H路由数据抄读" && strWhere == "F001")
	{
		DlgExtReadMeter dlgExtReadMeter;

		dlgExtReadMeter.DoModal();
		return;
	}

	else if (strZuming == "F0H扩展命令" && strWhere == "F158")
	{
		DlgExtStaDevStatus dlgExtStaDevStatus;

		dlgExtStaDevStatus.DoModal();
		return;
	}
	
	else if(strZuming == "10H路由查询" && strWhere == "F002")
	{
		DlgSaveNodeInfo dlgSaveNodeInfo;

		dlgSaveNodeInfo.DoModal();
		return;	
	}
	
	else if (strZuming == "F1H并发抄表" && strWhere == "F001")
	{
		CDIALOGF1F0TIMEOUT dlgtimeout;

		if (dlgtimeout.DoModal() == IDOK)
		{
			m_F1F0_TimeOut = dlgtimeout.itimeout;
		}
		return;
	}

	else if (strZuming == "F0H扩展命令" && strWhere == "F001")
	{
		TCHAR szFilter[] = _T("bin文件(*.bin)|*.bin|文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
		CFileDialog fileDlg(FALSE, _T("bin"), _T("cco_log"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);

		if (IDOK == fileDlg.DoModal())
		{
			m_strFilePath_f0f1 = fileDlg.GetPathName();
		}

	}


	strWhere = _T("AFN_FN='") + strZuming.Mid(0,2) + strWhere + _T("'");
	//m_accessData.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("DataMessage"),_T("DownBM,DownXS"),strWhere,&strData,nHang);
	m_accessData.SelectDataFromTable(pMain->m_PeiZhi_db,_T("DataMessage"),_T("DownBM,DownXS"),strWhere,&strData,nHang);
	m_tools.strlistData(strData,_T("$"),strlistData);
	if (strlistData[0] == "" && strlistData[1] == "")
	{
		return;
	}
	int nLoop , a = 0;
	if (strlistData[0].Find(_T("loop")) != -1)
	{
		if (strlistData[0].Left(4)=="loop")
		{
			m_setWriteLoop.DoModal();
			nLoop=_ttoi(m_setWriteLoop.m_strNum);
			strlistData[0]=SetBeizhu(nLoop,strlistData[0]);
			strlistData[1]=SetGershi(nLoop,strlistData[1]);
		}
		else
		{
			for(a=1;a<(wcslen(strlistData[0])+1);a++)
			{
				if (strlistData[0].Left(a).Right(1)==";")
				{
					if (strlistData[0].Left(a+4).Right(4)=="loop")
					{
						m_setWriteLoop.DoModal();
						nLoop=_ttoi(m_setWriteLoop.m_strNum);
						strlistData[0]=SetBeizhu(nLoop,strlistData[0]);
						strlistData[1]=SetGershi(nLoop,strlistData[1]);
						break;
					}
				}
			}
		}

	}

	for(int a=1;a<(int)(wcslen(strlistData[1])+1);a++)
	{
		if (strlistData[1].Left(a).Right(1)==";")
		{
			nGeFen++;
		}
	}

	m_setWriteDatadlg.m_bWrite = true;
	m_setWriteDatadlg.m_strBeizhu=strlistData[0];
	m_setWriteDatadlg.m_strGeshi=strlistData[1];
	m_setWriteDatadlg.m_nData=nGeFen;
	//m_accessData.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("DataMessage"),_T("DataMessage") , strWhere ,&strData,nHang );
	m_accessData.SelectDataFromTable(pMain->m_PeiZhi_db,_T("DataMessage"),_T("DataMessage") , strWhere ,&strData,nHang );
	m_setWriteDatadlg.m_strWriteDataMessage = strData.Mid(0,wcslen(strData) - 1);
	if (m_setWriteDatadlg.DoModal() == IDOK)
	{
		strDatalen.Format(_T("%d"),wcslen(m_setWriteDatadlg.m_strWriteData)/2);
		strSetData = _T("Databuf='") + m_setWriteDatadlg.m_strWriteData + _T("',Datalen='") + strDatalen + _T("',DataMessage='") + m_setWriteDatadlg.m_strWriteDataMessage + _T("'");
		//m_accessData.UpdataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("DataMessage"),strSetData,strWhere);
		m_accessData.UpdataFromTable(pMain->m_PeiZhi_db,_T("DataMessage"),strSetData,strWhere);
	}
	*pResult = 0;
}

void CFView3762::OnEnSetfocusEditMessage()
{
	m_nDClick = 1;
	m_bDCEditAddr = true;
}

void CFView3762::OnEnKillfocusEditMessage()
{
	m_nDClick = 0;
	m_bDCEditAddr = false;
}

void CFView3762::OnEnSetfocusEditAddress()
{
	m_nDClick = 2;
}

void CFView3762::OnEnKillfocusEditAddress()
{
	m_nDClick = 0;
}

void CFView3762::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(m_nDClick)
	{
	case 1:
		AfxMessageBox(_T("地址"));
		break;
	case 2:
		AfxMessageBox(_T("信息"));
		break;
	}
	CFormView::OnLButtonDblClk(nFlags, point);
}

void CFView3762::OnBnClickedButtonAddress()
{
	CDlgAddress dlgAddress;
	if(dlgAddress.DoModal()==IDOK)
	{
           m_editAddress.SetWindowText(dlgAddress.m_strMsgAndAddr);
	}
}

void CFView3762::StorageListData()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strdata;
	CString strfenzu;
	pMain->m_FenzuFnList.RemoveAll();
	HTREEITEM hFirstItem=m_treeData.GetRootItem();
	if(!hFirstItem)
		return;
	m_treeData.Expand(hFirstItem,TVE_EXPAND);
	POSITION pos=NULL;
	HTREEITEM hNextItem=m_treeData.GetNextItem(hFirstItem,TVGN_NEXTVISIBLE);
	while(hNextItem)
	{
		if (!m_treeData.GetChildItem(hNextItem))
		{
			if (m_treeData.GetCheck(hNextItem))
			{
				CString strF;
				strdata=m_treeData.GetItemText(hNextItem);
				HTREEITEM hFatherItem=m_treeData.GetParentItem(hNextItem);
				strfenzu=m_treeData.GetItemText(hFatherItem);
				CString strfenzuAndF=strfenzu.Mid(0,2)+strdata.Mid(1,4) + strdata.Mid(6);
				pos=pMain->m_FenzuFnList.InsertAfter(pos,strfenzuAndF);
			}
		}	
		else
		{
			m_treeData.Expand(hNextItem,TVE_EXPAND);
		}
		hNextItem=m_treeData.GetNextItem(hNextItem,TVGN_NEXTVISIBLE);
	}
}

void CFView3762::SetStruct3762(CString strMessage, CString strAFN_FN , CString strData , CString strDatalen, PartQGDW376_2 & pt3762)
{
	CString strC , strMessageData , strAddress, strAddr1 , strAddr2 , strAddr3;
	CStringA str;
	INT16U templen = 0;

	m_combType.GetWindowText(strC);
	pt3762.s_Con = (0x01<<6) | ((INT8U)_ttoi(strC.Mid(0,strC.Find(_T(":")))));
	strMessageData = strMessage.Mid(0,12);
	m_tools._str16tobuf16(strMessageData,pt3762.s_MsgBuf , templen);//信息域R

	strAddress = strMessage.Mid(12);
	if(strAddress != _T(""))
	{
		strAddr1 = strAddress.Mid(0,12);
		m_tools._str16tobuf16(strAddr1,pt3762.s_MainAddBuf , templen);//信息域R
		strAddr2 = strAddress.Mid(12,wcslen(strAddress) - 24);
		m_tools._str16tobuf16(strAddr2,pt3762.s_RelayAddBuf , templen);//信息域R
		strAddr3 = strAddress.Right(12);
		m_tools._str16tobuf16(strAddr3,pt3762.s_DestAddBuf , templen);//信息域R
	}
	str = strAFN_FN.Mid(0,2);
	pt3762.s_AFN = (INT8U)strtol(str,NULL,16);//AFN
	m_tools._strFto16(strAFN_FN.Mid(3),pt3762.s_FN);//数据单元标识
	m_tools._str16tobuf16(strData,pt3762.s_DataBuf , templen);//数据
	pt3762.s_DataLen = _ttoi(strDatalen);//数据长度

}

CString CFView3762::strHEX(CString str,bool bDaoxu)
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

CString CFView3762::GetDuanAndLen(int nduan,int nlen)
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

BOOL CFView3762::SetUpdataListData()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nHang= 0;
	CString strlist[10];
	CString strUpDataMessage;
	CString stWhere = _T("ConfigName='升级信息'");
	
	//m_accessData.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("Config"),_T("MessageData"),stWhere,&strUpDataMessage,nHang);
	if (m_accessData.SelectDataFromTable(pMain->m_PeiZhi_db, _T("Config"), _T("MessageData"), stWhere, &strUpDataMessage, nHang) == NULL)
	{
	
		AfxMessageBox(_T("获取数据失败!"));
		return FALSE;
	}
	
	
	m_tools.Split(strUpDataMessage , _T("☆") , strlist , nHang);
	m_listStrShengjiData.RemoveAll();
	char chBiaoshi[50];
	char chZhiling[50];
	CString strBiaoshi,strZhiling;
	POSITION pos=NULL;
	CString str;
	BYTE buf[2048];
	int tmp = 0, mod = 0;
	int iSectors = 0;
	int len =WideCharToMultiByte(CP_ACP,0,strlist[0],strlist[0].GetLength(),NULL,0,NULL,NULL);
	char * pFileName = new char[len + 1];
	WideCharToMultiByte(CP_ACP,0,strlist[0],strlist[0].GetLength(),pFileName,len,NULL,NULL);
	pFileName[len] ='\0';

	//m_tools.AutoMakedir(pFileName);

    m_fp = fopen(pFileName, "rb");
    if(m_fp==NULL)
        return FALSE;
    
    
	fseek(m_fp,0,SEEK_END);
	long nLen = ftell(m_fp);
	CString strlong;
	strlong.Format(_T("%d"),nLen);
	strBiaoshi=strlist[2].Left(2);
	strZhiling=strlist[3].Left(2);
	int changdu=_ttoi(strlist[1]);
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
		if (strlist[0].Right(3)=="bin")
		{
			str = m_tools._buf16tostr16((INT8U*)buf,changdu,false,_ttoi(strlist[4]));
		} 
		else
		{
			str=buf;
			str=strHEX(str,_ttoi(strlist[4]));
		}

		if (strBiaoshi=="00")
		{
			pos=m_listStrShengjiData.InsertAfter(pos,strBiaoshi+"00"+strZhiling+"0000000000000000"); 
			return TRUE;
		}
		pos=m_listStrShengjiData.InsertAfter(pos,strBiaoshi+"00"+strZhiling+strZongduan+strDuanLen+str); 
	}
	if (mod!=0)
	{
		strDuanLen=GetDuanAndLen(i,mod);
		fread(buf,mod,1,m_fp);
		m_nDataLong=mod;
		if (strlist[0].Right(3)=="bin")
		{
			str = m_tools._buf16tostr16((INT8U*)buf,mod,false,_ttoi(strlist[4]));
		} 
		else
		{
			str=buf;
			str=strHEX(str,_ttoi(strlist[4]));
		}
		pos=m_listStrShengjiData.InsertAfter(pos,strBiaoshi+"01"+strZhiling+strZongduan+strDuanLen+str);
	}
	delete[] pFileName;

	return TRUE;
}

INT8U CFView3762::SendUpdataData(CString strName, INT8U* F8DataHead,int nChoose)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str = _T("======================================================\r\n");
	if (pMain->m_nChooseView == OPEN13762)
	{
		str += _T("★") + strName + _T("★\r\n");
	}
	else if (pMain->m_nChooseView == OPENNET)
	{
		str += _T("★F0F008转发13762报文（") + strName + _T("）★\r\n");
	}
	SetWindowText(str);
	CString strShuxingBiaoshiLen;
	INT8U Sendbufdata[JZQ_MAX_BUFF_LEN] , AddrBuf[7];
	INT16U Sendbuflen = 0 ,temp16 = 0;
	INT8U ack = -1;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
	
	CString strDatalen = _T("");
	int iUpdateTarget = ((*F8DataHead) >> 2) & 0x01;
	

	if (SetUpdataListData() == FALSE)
		return FALSE;


	for(POSITION pos = m_listStrShengjiData.GetHeadPosition(); pos != NULL;)
	{
		if (pMain->m_bCommunictStop)
		{
			SetWindowText(_T("--------------------------------------------------------------------------------\r\n"));
			return false;
		}
		strShuxingBiaoshiLen=(CString)m_listStrShengjiData.GetNext(pos);
		m_tools._str16tobuf16(strShuxingBiaoshiLen  , Sendbufdata , Sendbuflen);
SENDCONTINUE:
		switch (nChoose)
		{
		case  0:
			switch (iUpdateTarget)
			{
			case 0:
				ack = gSimJzq.HostSendRcv376_2Buf(0x15, F1, Sendbufdata, Sendbuflen, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);
				break;
			case 1:
				ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43, F8DataHead,0x15, F1, Sendbufdata, Sendbuflen, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);
				break;
			default:
				break;
			}
			break;
		case  1:
			m_tools._str16tobuf16(pMain->m_strMAddress, AddrBuf, temp16, true);
			//ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf, 0x15, F1, Sendbufdata, Sendbuflen, m_ptSendQGDW376_2, ptRecvQGDW376_2, m_ptRecvQGDW376_2);
			ack = gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43, F8DataHead, AddrBuf, 0x15, F1, Sendbufdata, Sendbuflen, m_ptSendQGDW376_2, ptRecvQGDW376_2, m_ptRecvQGDW376_2);
			
			break;
		}
		switch(ack)
		{
		case 0:
			if (m_ptRecvQGDW376_2.s_head.s_AFN == 0x00 && m_ptRecvQGDW376_2.s_head.s_FN == F2)
			{
				str = pMain->GetRecvErrName(m_ptRecvQGDW376_2.s_RcvDataBuf[0]);
				str += _T("\r\n");
				SetWindowText(str);
				switch (MessageBox(_T("错误码:") + str + _T(" ，是否重发") ,_T("返回否认帧") ,MB_ABORTRETRYIGNORE ))
				{
				case 3://终止
					return 0;
				case 4://重试
					goto SENDCONTINUE;
					break;
				}
			}
			else
			{
				SetWindowText(_T(">>>>升级成功段:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf , m_ptRecvQGDW376_2.s_RcvDataLen , false , true)) + _T("\r\n"));
			}
			break;
		default:
			str = pMain->GetRecvErrName(ack);
			switch (MessageBox(_T("错误码:") + str + _T(" ，是否重发") ,_T("失败") ,MB_ABORTRETRYIGNORE ))
			{
			case 3://终止
				return 0;
			case 4://重试
				goto SENDCONTINUE;
				break;
			}
			break;
		}
	}
	SetWindowText(_T("--------------------------------------------------------------------------------\r\n"));
	return 0;
}

INT16U CFView3762::FileCalculateCRC(INT8U CRCHi,INT8U CRCLo,INT8U* InputData, long DataLen)
{
	INT8U Index;        
	while (DataLen--)
	{
		Index = CRCLo ^ (*InputData);
		InputData++;
		CRCLo = CRCHi ^ CRCHTalbe[Index]; 
		CRCHi = CRCLTalbe[Index];
	} 
	return (((INT8U)CRCHi << 8) | CRCLo);
}
INT8U CFView3762::SendSecretData(CString strName , int nChoose)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strAFN_FN = _T("") , strWhere = _T("") , strData = _T("");
	CString strCRC , strLen;
	int nHang= 0;
	CStringA str;
	INT8U u8SendAFN = 0 , buf[255] , F8DataHead[20] , AddrBuf[7];
	INT16U u16SendFN = 0 , buflen = 0 ,temp16 = 0;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
	str = strName.Mid(0,2);
	u8SendAFN = (INT8U)strtol(str,NULL,16);//AFN
	m_tools._strFto16(strName.Mid(3,3),u16SendFN);//数据单元标识
	strAFN_FN = strName.Mid(0,6);
	strWhere = _T("AFN_FN='") + strAFN_FN + _T("'");

	m_editAddress.GetWindowText(m_strMessageData);
	m_tools._str16tobuf16(m_strMessageData , F8DataHead , temp16);
	//if(m_accessData.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("DataMessage"),_T("Databuf"),strWhere,&strData,nHang))
	if(m_accessData.SelectDataFromTable(pMain->m_PeiZhi_db,_T("DataMessage"),_T("Databuf"),strWhere,&strData,nHang))
	{
		strData = strData.Mid(0 , strData.GetLength() - 1);
		m_tools._str16tobuf16(strData , buf , buflen);
		INT16U crc = FileCalculateCRC(0xff,0xff,buf,buflen);
		INT8U bufcrc[2] ,ack = 0;
		bufcrc[1] = crc>>8;
		bufcrc[0] = (INT8U)crc;
		strCRC = m_tools._buf16tostr16(bufcrc,2,0,0);
		strLen.Format(_T("%d") , wcslen(strData)/2);
		strLen = m_tools._strDaoxu(m_tools._str10tostr16(strLen ,4));
		strData = _T("AAAAAAAA")+ strLen + _T("DCCCBCAC0C0C0C0C") + strCRC + _T("0000000000000000000000000000") + strData + _T("AAAAAAAA");
		strLen.Format(_T("%d") , wcslen(strData)/2);
		strLen = m_tools._strDaoxu(m_tools._str10tostr16(strLen ,2));
		strData = _T("030100010000000000") + strLen + strData;
		m_tools._str16tobuf16(strData  , buf , buflen);

		switch (nChoose)
		{
		case 0:
			ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43 ,F8DataHead ,0x15 , F1 , buf , buflen , m_ptSendQGDW376_2 , m_ptRecvQGDW376_2);
			break;
		case 1:
			m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x15 , F1 , buf , buflen , m_ptSendQGDW376_2,ptRecvQGDW376_2 , m_ptRecvQGDW376_2);
			break;
		}
		if (ack != 0) return false;
		if (m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf ,m_ptRecvQGDW376_2.s_RcvDataLen) == "00000000")
		{
			SetWindowText(_T("设置成功\r\n"));
		}
		else
		{
			SetWindowText(_T("设置失败\r\n"));
		}
	}

	return true;
}
void CFView3762::SaveDebugData(INT32U pos, INT8U *recvBuf, INT16U recvLen)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nHang= 0;
	CString strlist[10];
	CString strUpDataMessage;
	CString stWhere = _T("ConfigName='调试信息'");
	m_accessData.SelectDataFromTable(pMain->m_PeiZhi_db,_T("Config"),_T("MessageData"),stWhere,&strUpDataMessage,nHang);
	//m_accessData.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("Config"),_T("MessageData"),stWhere,&strUpDataMessage,nHang);
	m_tools.Split(strUpDataMessage , _T("☆") , strlist , nHang);
	
	int len =WideCharToMultiByte(CP_ACP,0,strlist[0],strlist[0].GetLength(),NULL,0,NULL,NULL);
	char * pFileName = new char[len + 1];
	WideCharToMultiByte(CP_ACP,0,strlist[0],strlist[0].GetLength(),pFileName,len,NULL,NULL);
	pFileName[len] ='\0';

	m_tools.AutoMakedir(pFileName);
	//CString ss=m_tools._buf16tostr16(recvBuf,recvLen);
	m_fp = fopen(pFileName, "r+b");
	if(m_fp == NULL)
	{
		m_fp = fopen(pFileName, "w+b");
	}
	fseek(m_fp, pos, SEEK_SET);
	if(m_fp!=NULL)
		fwrite(recvBuf,recvLen,1,m_fp);
	fclose(m_fp);
}
INT8U CFView3762::RecvDebugData(CString strName , INT8U *F8DataHead, int nChoose)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str = _T("======================================================\r\n");
	if (pMain->m_nChooseView == OPEN13762)
	{
		str += _T("★") + strName + _T("★\r\n");
	}
	else if (pMain->m_nChooseView == OPENNET)
	{
		str += _T("★F0F008转发13762报文（") + strName + _T("）★\r\n");
	}
	SetWindowText(str);

	CString strShuxingBiaoshiLen;
	INT8U Recvbufdata[JZQ_MAX_BUFF_LEN] , AddrBuf[7];
	INT16U Recvbuflen = 0 ,temp16 = 0;
	INT8U Sendbufdata[20] ;
	INT16U Sendbuflen = 6;
	INT8U ack = -1;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
//	SetUpdataListData();
	CString strDatalen = _T("");

	INT32U nTotalInfoLen = 40*1024;
	INT32U nReadPos = 0;
	INT16U nReadLen = 1024;

	INT32U nRetTotalInfoLen = 0;
	INT32U nRetPos = 0;
	INT16U nSaveLen = 0;

	int resendcnt = 0;


	while(nReadPos + nReadLen < nTotalInfoLen)
	{
		if (pMain->m_bCommunictStop)
		{
			SetWindowText(_T("--------------------------------------------------------------------------------\r\n"));
			return false;
		}
SENDCONTINUE:
		Sendbufdata[0] = nReadPos&0xff;
		Sendbufdata[1] = (nReadPos>>8)&0xff;
		Sendbufdata[2] = (nReadPos>>16)&0xff;
		Sendbufdata[3] = (nReadPos>>24)&0xff;
	
		Sendbufdata[4] = nReadLen&0xff;
		Sendbufdata[5] = (nReadLen>>8)&0xff;

		switch (nChoose)
		{
		case  0:
			ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43 ,F8DataHead ,0xF0 , F21 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2 , m_ptRecvQGDW376_2);
//			ack = gSimJzq.HostSendRcv376_2Buf(0xF0 , F21 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2 , m_ptRecvQGDW376_2);
			break;
		case  1:
			m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
			ack = gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43 , F8DataHead, AddrBuf ,0xF0 , F21 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2,ptRecvQGDW376_2 , m_ptRecvQGDW376_2);
//			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf ,0xF0 , F21 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2,ptRecvQGDW376_2 , m_ptRecvQGDW376_2);
			break;
		}
		switch(ack)
		{
		case 0:
			if (m_ptRecvQGDW376_2.s_head.s_AFN == 0x00 && m_ptRecvQGDW376_2.s_head.s_FN == F2)
			{
				str = pMain->GetRecvErrName(m_ptRecvQGDW376_2.s_RcvDataBuf[0]);
				str += _T("\r\n");
				SetWindowText(str);
				if(resendcnt > 5)
				{
					break;
				}
				switch (MessageBox(_T("错误码:") + str + _T(" ，是否重发") ,_T("返回否认帧") ,MB_ABORTRETRYIGNORE ))
				{
				case 3://终止
					return 0;
				case 4://重试
					resendcnt++;
					goto SENDCONTINUE;
					break;
				}
			}
			else
			{
				if (m_ptRecvQGDW376_2.s_head.s_AFN == 0xF0 && m_ptRecvQGDW376_2.s_head.s_FN == F21)
				{
					if(m_ptRecvQGDW376_2.s_RcvDataLen > 10)
					{
						nRetTotalInfoLen = m_ptRecvQGDW376_2.s_RcvDataBuf[3];
						nRetTotalInfoLen <<= 8;
						nRetTotalInfoLen += m_ptRecvQGDW376_2.s_RcvDataBuf[2];
						nRetTotalInfoLen <<= 8;
						nRetTotalInfoLen += m_ptRecvQGDW376_2.s_RcvDataBuf[1];
						nRetTotalInfoLen <<= 8;
						nRetTotalInfoLen += m_ptRecvQGDW376_2.s_RcvDataBuf[0];

						nRetPos = m_ptRecvQGDW376_2.s_RcvDataBuf[7];
						nRetPos <<= 8;
						nRetPos += m_ptRecvQGDW376_2.s_RcvDataBuf[6];
						nRetPos <<= 8;
						nRetPos += m_ptRecvQGDW376_2.s_RcvDataBuf[5];
						nRetPos <<= 8;
						nRetPos += m_ptRecvQGDW376_2.s_RcvDataBuf[4];

						nSaveLen = m_ptRecvQGDW376_2.s_RcvDataBuf[9];
						nSaveLen <<= 8;
						nSaveLen += m_ptRecvQGDW376_2.s_RcvDataBuf[8];
						if(nSaveLen > m_ptRecvQGDW376_2.s_RcvDataLen-10)
						{
							nSaveLen = m_ptRecvQGDW376_2.s_RcvDataLen-10;
						}
					
						SaveDebugData(nRetPos, &m_ptRecvQGDW376_2.s_RcvDataBuf[10], nSaveLen);

						SetWindowText(_T(">>>>接收成功:") + m_tools._str16tostr10(m_tools._buf16tostr16(&m_ptRecvQGDW376_2.s_RcvDataBuf[4] , 4 , false , true)) + _T("\r\n"));
						if(nRetPos + nSaveLen >= nRetTotalInfoLen)
						{
							return 0;
						}
						else
						{
							nReadPos = nRetPos + nSaveLen;
							nReadLen = nSaveLen;
							nTotalInfoLen = nRetTotalInfoLen;
						}
						resendcnt = 0;
					}
					else
					{
						SetWindowText(_T(">>>>数据包有误:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf , m_ptRecvQGDW376_2.s_RcvDataLen , false , true)) + _T("\r\n"));
					}
				}
				
			}
			break;
		default:
			if(resendcnt > 5)
			{
				break;
			}

			str = pMain->GetRecvErrName(ack);
			switch (MessageBox(_T("错误码:") + str + _T(" ，是否重发") ,_T("失败") ,MB_ABORTRETRYIGNORE ))
			{
			case 3://终止
				return 0;
			case 4://重试
				resendcnt++;
				goto SENDCONTINUE;
				break;
			}
			break;
		}
	}
	SetWindowText(_T("--------------------------------------------------------------------------------\r\n"));
	return 0;
}
void CFView3762::SaveExtendStaVersion(INT32U sn, INT8U *recvBuf, INT16U recvLen)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nHang= 0;
	char szANSIString[5000];
	CString strlist[10];
	CString strUpDataMessage;

	CString stWhere = _T("ConfigName='扩展版本信息'");
	m_accessData.SelectDataFromTable(pMain->m_PeiZhi_db,_T("Config"),_T("MessageData"),stWhere,&strUpDataMessage,nHang);
	//m_accessData.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("Config"),_T("MessageData"),stWhere,&strUpDataMessage,nHang);
	m_tools.Split(strUpDataMessage , _T("☆") , strlist , nHang);
	
	int len =WideCharToMultiByte(CP_ACP,0,strlist[0],strlist[0].GetLength(),NULL,0,NULL,NULL);
	char * pFileName = new char[len + 1];
	WideCharToMultiByte(CP_ACP,0,strlist[0],strlist[0].GetLength(),pFileName,len,NULL,NULL);
	pFileName[len] ='\0';

	m_tools.AutoMakedir(pFileName);

/*	m_fp = fopen(pFileName, "r+b");
	if(m_fp == NULL)
	{
		m_fp = fopen(pFileName, "w+b");
		
		char szANSIString[1000]; 
		CString strTopLine = _T("       STA_MAC,STA_ROLE,BT_DATE,BT_VER,CPU0_DATE,CPU0_VER,CPU1_DATE,CPU1_VER,PZ_DATE,PZ_VER,LIB_DATE,LIB_VER,HW_DATE,HW_VER\n");
		WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
		fwrite(szANSIString,wcslen(strTopLine),1,m_fp);
	}*/
	

	m_fp=fopen(pFileName,"r");
	if  ( m_fp == NULL )
	{
		m_fp=fopen(pFileName,"a+");

		if(m_fp != NULL) 
		{
			CString strTopLine = _T("    SN,       STA_MAC, STA_ROLE, BT_DATE,  BT_VER,CPU0_DATE,CPU0_VER,CPU1_DATE,CPU1_VER, PZ_DATE,  PZ_VER,LIB_DATE,LIB_VER, HW_DATE,  HW_VER\n");
			WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
			fwrite(szANSIString,wcslen(strTopLine),1,m_fp);
		}
	}
	else
	{
		fclose(m_fp); 
		m_fp=fopen(pFileName,"a+");
	} 
	if(m_fp != NULL) 
	{
		CString strAllTPdata = _T("");
		strAllTPdata = m_tools._buf16tostr16(recvBuf , recvLen);
	
		CString strlistData[20];

		CString strSn;
		strSn.Format(_T("%d"),sn+1);
		strlistData[0] = strSn;

		CString  strMAC = strAllTPdata.Mid(6 , 12);
		strlistData[1] = m_tools._strDaoxu(strMAC);
		strlistData[2] = strAllTPdata.Mid(18 , 2);

		strlistData[3] = m_tools._strDaoxu(strAllTPdata.Mid(20 , 8));
		strlistData[4] = m_tools._strDaoxu(strAllTPdata.Mid(28 , 8));

		strlistData[5] = m_tools._strDaoxu(strAllTPdata.Mid(36 , 8));
		strlistData[6] = m_tools._strDaoxu(strAllTPdata.Mid(44 , 8));

		strlistData[7] = m_tools._strDaoxu(strAllTPdata.Mid(52 , 8));
		strlistData[8] = m_tools._strDaoxu(strAllTPdata.Mid(60 , 8));

		strlistData[9] = m_tools._strDaoxu(strAllTPdata.Mid(68 , 8));
		strlistData[10] = m_tools._strDaoxu(strAllTPdata.Mid(76 , 8));

		strlistData[11] = m_tools._strDaoxu(strAllTPdata.Mid(84 , 8));
		strlistData[12] = m_tools._strDaoxu(strAllTPdata.Mid(92 , 8));

		strlistData[13] = m_tools._strDaoxu(strAllTPdata.Mid(100 , 8));
		strlistData[14] = m_tools._strDaoxu(strAllTPdata.Mid(108 , 8));

		CString strTopLine = strlistData[0] + _T(",") + strlistData[1] + _T(",") + strlistData[2] + _T(",") + strlistData[3] + _T(",") + strlistData[4] 
			+ _T(",") + strlistData[5]+ _T(",") + strlistData[6]+ _T(",") + strlistData[7]+ _T(",") + strlistData[8] 
			+ _T(",") + strlistData[9]+ _T(",") + strlistData[10]+ _T(",") + strlistData[11]+ _T(",") + strlistData[12]
			+ _T(",") + strlistData[13]+ _T(",") + strlistData[14]+ _T("\n");
		WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
		fwrite(szANSIString,wcslen(strTopLine),1,m_fp);

		fclose(m_fp);
	}
	delete[] pFileName;
}
INT8U CFView3762::RecvExtendStaVersion(CString strName , INT8U *F8DataHead, int nChoose)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str = _T("======================================================\r\n");
	if (pMain->m_nChooseView == OPEN13762)
	{
		str += _T("★") + strName + _T("★\r\n");
	}
	else if (pMain->m_nChooseView == OPENNET)
	{
		str += _T("★F0F008转发13762报文（") + strName + _T("）★\r\n");
	}
	SetWindowText(str);

	CString strShuxingBiaoshiLen;
	INT8U Recvbufdata[JZQ_MAX_BUFF_LEN] , AddrBuf[7];
	INT16U Recvbuflen = 0 ,temp16 = 0;
	INT8U Sendbufdata[20] ;
	INT16U Sendbuflen = 3;
	INT8U ack = -1;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
//	SetUpdataListData();
	CString strDatalen = _T("");

	INT32U nTotalNum = 1;
	INT32U nReadStart = 0;

	int resendcnt = 0;

	switch (nChoose)
	{
	case  0:
		ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43 ,F8DataHead ,0x10 , F1 , Sendbufdata , 0 , m_ptSendQGDW376_2 , m_ptRecvQGDW376_2);
		break;
	case  1:
		m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
		ack = gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43 , F8DataHead, AddrBuf ,0x10 , F1 , Sendbufdata , 0 , m_ptSendQGDW376_2,ptRecvQGDW376_2 , m_ptRecvQGDW376_2);
		break;
	}
	if(0 == ack)
	{
		if (m_ptRecvQGDW376_2.s_head.s_AFN == 0x10 && m_ptRecvQGDW376_2.s_head.s_FN == F1)
		{
			nTotalNum = m_ptRecvQGDW376_2.s_RcvDataBuf[1];
			nTotalNum <<= 8;
			nTotalNum += m_ptRecvQGDW376_2.s_RcvDataBuf[0];
			SetWindowText(_T(">>>>节点数量:") + m_tools._str16tostr10(m_tools._buf16tostr16(&m_ptRecvQGDW376_2.s_RcvDataBuf[0] , 2 , false , true)) + _T("\r\n"));
		}
		else
		{
			SetWindowText(_T(">>>>数据包有误:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf , m_ptRecvQGDW376_2.s_RcvDataLen , false , true)) + _T("\r\n"));
			return 0;
		}
	}
	else
	{
		SetWindowText(_T(">>>>数据包有误:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf , m_ptRecvQGDW376_2.s_RcvDataLen , false , true)) + _T("\r\n"));
		return 0;
	}
	
	while(nReadStart < nTotalNum)
	{
		if (pMain->m_bCommunictStop)
		{
			SetWindowText(_T("--------------------------------------------------------------------------------\r\n"));
			return false;
		}

		
SENDCONTINUE:
		Sendbufdata[0] = (nReadStart + 1)&0xff;
		Sendbufdata[1] = ((nReadStart + 1)>>8)&0xff;
		Sendbufdata[2] = 0x01;
	
		//Sendbufdata[0] = Sendbufdata[1] = Sendbufdata[2]=0;

	    Sendbuflen = 3;
		switch (nChoose)
		{
		case  0:
			ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43 ,F8DataHead ,0xF0 , F153 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2 , m_ptRecvQGDW376_2);
//			ack = gSimJzq.HostSendRcv376_2Buf(0xF0 , F21 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2 , m_ptRecvQGDW376_2);
			break;
		case  1:
			m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
			ack = gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43 , F8DataHead, AddrBuf ,0xF0 , F153 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2,ptRecvQGDW376_2 , m_ptRecvQGDW376_2);
//			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf ,0xF0 , F21 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2,ptRecvQGDW376_2 , m_ptRecvQGDW376_2);
			break;
		}
		switch(ack)
		{
		case 0:
			if (m_ptRecvQGDW376_2.s_head.s_AFN == 0x00 && m_ptRecvQGDW376_2.s_head.s_FN == F2)
			{
				str = pMain->GetRecvErrName(m_ptRecvQGDW376_2.s_RcvDataBuf[0]);
				
				CString strSn;
				strSn.Format(_T(", sn %d"),nReadStart+1);

				str = str + strSn + _T("\r\n");
				SetWindowText(str);
				
				nReadStart++;
				resendcnt = 0;
				break;
/*				if(resendcnt > 5)
				{
					break;
				}
				switch (MessageBox(_T("错误码:") + str + _T(" ，是否重发") ,_T("返回否认帧") ,MB_ABORTRETRYIGNORE ))
				{
				case 3://终止
					return 0;
				case 4://重试
					resendcnt++;
					goto SENDCONTINUE;
					break;
				}*/
			}
			else
			{
				if (m_ptRecvQGDW376_2.s_head.s_AFN == 0xF0 && m_ptRecvQGDW376_2.s_head.s_FN == F153)
				{
					if(m_ptRecvQGDW376_2.s_RcvDataLen > 10)
					{
						
						SaveExtendStaVersion(nReadStart, &m_ptRecvQGDW376_2.s_RcvDataBuf[0], m_ptRecvQGDW376_2.s_RcvDataLen);

						SetWindowText(_T(">>>>接收成功:") + m_tools._buf16tostr16(&m_ptRecvQGDW376_2.s_RcvDataBuf[3] , 6 , false , true) + _T("\r\n"));
						nReadStart++;
						resendcnt = 0;
					}
					else
					{
						SetWindowText(_T(">>>>数据包有误:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf , m_ptRecvQGDW376_2.s_RcvDataLen , false , true)) + _T("\r\n"));
					}
				}
				
			}
			break;
		default:
			str = pMain->GetRecvErrName(ack);

			CString strSn;
			strSn.Format(_T(", sn %d"),nReadStart+1);
			str = str + strSn + _T("\r\n");
			SetWindowText(str);
			nReadStart++;
			resendcnt = 0;
			break;

			if(resendcnt > 5)
			{
				break;
			}
/*			switch (MessageBox(_T("错误码:") + str + _T(" ，是否重发") ,_T("失败") ,MB_ABORTRETRYIGNORE ))
			{
			case 3://终止
				return 0;
			case 4://重试
				resendcnt++;
				goto SENDCONTINUE;
				break;
			}
			break;*/
		}
	}
	SetWindowText(_T("--------------------------------------------------------------------------------\r\n"));
	return 0;
}

void CFView3762::SaveExtendStaDevStatus(INT32U sn, INT8U *recvBuf, INT16U recvLen)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nHang = 0;
	char szANSIString[5000];
	CString strlist[10];
	CString strUpDataMessage;

	CString stWhere = _T("ConfigName='STA的设备状态信息'");
	m_accessData.SelectDataFromTable(pMain->m_PeiZhi_db, _T("Config"), _T("MessageData"), stWhere, &strUpDataMessage, nHang);
	//m_accessData.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("Config"),_T("MessageData"),stWhere,&strUpDataMessage,nHang);
	m_tools.Split(strUpDataMessage, _T("☆"), strlist, nHang);

	int len = WideCharToMultiByte(CP_ACP, 0, strlist[0], strlist[0].GetLength(), NULL, 0, NULL, NULL);
	char * pFileName = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, strlist[0], strlist[0].GetLength(), pFileName, len, NULL, NULL);
	pFileName[len] = '\0';

	m_tools.AutoMakedir(pFileName);

	/*	m_fp = fopen(pFileName, "r+b");
	if(m_fp == NULL)
	{
	m_fp = fopen(pFileName, "w+b");

	char szANSIString[1000];
	CString strTopLine = _T("       STA_MAC,STA_ROLE,BT_DATE,BT_VER,CPU0_DATE,CPU0_VER,CPU1_DATE,CPU1_VER,PZ_DATE,PZ_VER,LIB_DATE,LIB_VER,HW_DATE,HW_VER\n");
	WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
	fwrite(szANSIString,wcslen(strTopLine),1,m_fp);
	}*/
	m_fp = fopen(pFileName, "r");
	if (m_fp == NULL)
	{
		m_fp = fopen(pFileName, "a+");

		if (m_fp != NULL)
		{
			//CString strTopLine = _T("    SN,       STA_MAC, SND_PKG_CNT, RCV_PKG_CNT, SND_PKG_LOSS_CNT,RCV_PKG_LOSS_CNT, FREQ_OFFSET , PLL_LOSS_OF_LOCK, FC_RCV_CNT_TOTAL,  FC_RCV_CNT_SUCCESS, FC_PKG_LOSS_CNT,FC_FILTER_CNT\n");
			CString strTopLine = _T("SN, STA_MAC, TX, RX, TX_LOSS, RX_LOSS, FREQ_OFFSET, PLL_RESET, FC_TOTAL, FC_SUCCESS, FC_LOSS, FC_FILTER\n");
			WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, strTopLine, -1, szANSIString, sizeof(szANSIString), NULL, NULL);
			fwrite(szANSIString, wcslen(strTopLine), 1, m_fp);
		}
	}
	else
	{
		fclose(m_fp);
		m_fp = fopen(pFileName, "a+");
	}
	if (m_fp != NULL)
	{
		CString strAllTPdata = _T("");
		strAllTPdata = m_tools._buf16tostr16(recvBuf, recvLen);

		CString strlistData[20];

		CString strSn;
		strSn.Format(_T("%d"), sn + 1);
		strlistData[0] = strSn;

		CString  strMAC = strAllTPdata.Mid(6, 12);
		strlistData[1] = m_tools._strDaoxu(strMAC);//MAC

		strlistData[2] = m_tools._strDaoxu(strAllTPdata.Mid(18, 8));//SND_PKG_CNT

		strlistData[3] = m_tools._strDaoxu(strAllTPdata.Mid(26, 8));//RCV_PKG_CNT

		strlistData[4] = m_tools._strDaoxu(strAllTPdata.Mid(34, 8));//SND_PKG_LOSS_CNT

		strlistData[5] = m_tools._strDaoxu(strAllTPdata.Mid(42, 8));//RCV_PKG_LOSS_CNT
		
		strlistData[6] = m_tools._strDaoxu(strAllTPdata.Mid(50, 8));//FREQ_OFFSET

		strlistData[7] = m_tools._strDaoxu(strAllTPdata.Mid(58, 8));//PLL_LOSS_OF_LOCK
		
		strlistData[8] = m_tools._strDaoxu(strAllTPdata.Mid(66, 8));//FC_RCV_CNT_TOTAL

		strlistData[9] = m_tools._strDaoxu(strAllTPdata.Mid(74, 8));//FC_RCV_CNT_SUCCESS
		
		strlistData[10] = m_tools._strDaoxu(strAllTPdata.Mid(82, 8));//FC_PKG_LOSS_CNT

		strlistData[11] = m_tools._strDaoxu(strAllTPdata.Mid(90, 8));//FC_FILTER_CNT
		
		

		CString strTopLine = strlistData[0] + _T(",") + strlistData[1] + _T(",") + strlistData[2] + _T(",") + strlistData[3] + _T(",") + strlistData[4]
			+ _T(",") + strlistData[5] + _T(",") + strlistData[6] + _T(",") + strlistData[7] + _T(",") + strlistData[8]
			+ _T(",") + strlistData[9] + _T(",") + strlistData[10] + _T(",") + strlistData[11]  +_T("\n");
		WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, strTopLine, -1, szANSIString, sizeof(szANSIString), NULL, NULL);
		fwrite(szANSIString, wcslen(strTopLine), 1, m_fp);

		fclose(m_fp);
		
	}
	delete[] pFileName;
}
INT8U CFView3762::RecvExtendStaDevStatus(CString strName, INT8U *F8DataHead, int nChoose)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str = _T("======================================================\r\n");
	if (pMain->m_nChooseView == OPEN13762)
	{
		str += _T("★") + strName + _T("★\r\n");
	}
	else if (pMain->m_nChooseView == OPENNET)
	{
		str += _T("★F0F008转发13762报文（") + strName + _T("）★\r\n");
	}
	SetWindowText(str);

	CString strShuxingBiaoshiLen;
	INT8U Recvbufdata[JZQ_MAX_BUFF_LEN], AddrBuf[7];
	INT16U Recvbuflen = 0, temp16 = 0;
	INT8U Sendbufdata[20];
	INT16U Sendbuflen = 3;
	INT8U ack = -1;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
	//	SetUpdataListData();
	CString strDatalen = _T("");

	INT32U nTotalNum = 1;
	INT32U nReadStart = 0;

	int resendcnt = 0;

	switch (nChoose)
	{
	case  0:
		ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43, F8DataHead, 0x10, F1, Sendbufdata, 0, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);
		break;
	case  1:
		m_tools._str16tobuf16(pMain->m_strMAddress, AddrBuf, temp16, true);
		ack = gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43, F8DataHead, AddrBuf, 0x10, F1, Sendbufdata, 0, m_ptSendQGDW376_2, ptRecvQGDW376_2, m_ptRecvQGDW376_2);
		break;
	}
	if (0 == ack)
	{
		if (m_ptRecvQGDW376_2.s_head.s_AFN == 0x10 && m_ptRecvQGDW376_2.s_head.s_FN == F1)
		{
			nTotalNum = m_ptRecvQGDW376_2.s_RcvDataBuf[1];
			nTotalNum <<= 8;
			nTotalNum += m_ptRecvQGDW376_2.s_RcvDataBuf[0];
			SetWindowText(_T(">>>>节点数量:") + m_tools._str16tostr10(m_tools._buf16tostr16(&m_ptRecvQGDW376_2.s_RcvDataBuf[0], 2, false, true)) + _T("\r\n"));
		}
		else
		{
			SetWindowText(_T(">>>>数据包有误:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf, m_ptRecvQGDW376_2.s_RcvDataLen, false, true)) + _T("\r\n"));
			return 0;
		}
	}
	else
	{
		SetWindowText(_T(">>>>数据包有误:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf, m_ptRecvQGDW376_2.s_RcvDataLen, false, true)) + _T("\r\n"));
		return 0;
	}

	while (nReadStart < nTotalNum)
	{
		if (pMain->m_bCommunictStop)
		{
			SetWindowText(_T("--------------------------------------------------------------------------------\r\n"));
			return false;
		}

	SENDCONTINUE:
		Sendbufdata[0] = (nReadStart + 1) & 0xff;
		Sendbufdata[1] = ((nReadStart + 1) >> 8) & 0xff;
		Sendbufdata[2] = 0x01;

	//Sendbufdata[0] = Sendbufdata[1] = Sendbufdata[2] = 0;

		Sendbuflen = 3;
		switch (nChoose)
		{
		case  0:
			ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43, F8DataHead, 0xF0, F158, Sendbufdata, Sendbuflen, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);
			//			ack = gSimJzq.HostSendRcv376_2Buf(0xF0 , F21 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2 , m_ptRecvQGDW376_2);
			break;
		case  1:
			m_tools._str16tobuf16(pMain->m_strMAddress, AddrBuf, temp16, true);
			ack = gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43, F8DataHead, AddrBuf, 0xF0, F158, Sendbufdata, Sendbuflen, m_ptSendQGDW376_2, ptRecvQGDW376_2, m_ptRecvQGDW376_2);
			//			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf ,0xF0 , F21 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2,ptRecvQGDW376_2 , m_ptRecvQGDW376_2);
			break;
		}
		switch (ack)
		{
		case 0:
			if (m_ptRecvQGDW376_2.s_head.s_AFN == 0x00 && m_ptRecvQGDW376_2.s_head.s_FN == F2)
			{
				str = pMain->GetRecvErrName(m_ptRecvQGDW376_2.s_RcvDataBuf[0]);

				CString strSn;
				strSn.Format(_T(", sn %d"), nReadStart + 1);

				str = str + strSn + _T("\r\n");
				SetWindowText(str);

				nReadStart++;
				resendcnt = 0;
				break;
				/*
				if(resendcnt > 5)
				{
				break;
				}
				switch (MessageBox(_T("错误码:") + str + _T(" ，是否重发") ,_T("返回否认帧") ,MB_ABORTRETRYIGNORE ))
				{
				case 3://终止
				return 0;
				case 4://重试
				resendcnt++;
				goto SENDCONTINUE;
				break;
				}
				*/
			}
			else
			{
				if (m_ptRecvQGDW376_2.s_head.s_AFN == 0xF0 && m_ptRecvQGDW376_2.s_head.s_FN == F158)
				{
					if (m_ptRecvQGDW376_2.s_RcvDataLen > 10)
					{

						SaveExtendStaDevStatus(nReadStart, &m_ptRecvQGDW376_2.s_RcvDataBuf[0], m_ptRecvQGDW376_2.s_RcvDataLen);

						SetWindowText(_T(">>>>接收成功:") + m_tools._buf16tostr16(&m_ptRecvQGDW376_2.s_RcvDataBuf[3], 6, false, true) + _T("\r\n"));
						nReadStart++;
						resendcnt = 0;
					}
					else
					{
						SetWindowText(_T(">>>>数据包有误:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf, m_ptRecvQGDW376_2.s_RcvDataLen, false, true)) + _T("\r\n"));
					}
				}

			}
			break;
		default:
			str = pMain->GetRecvErrName(ack);

			CString strSn;
			strSn.Format(_T(", sn %d"), nReadStart + 1);
			str = str + strSn + _T("\r\n");
			SetWindowText(str);
			nReadStart++;
			resendcnt = 0;
			break;

			if (resendcnt > 5)
			{
				break;
			}
			/*			switch (MessageBox(_T("错误码:") + str + _T(" ，是否重发") ,_T("失败") ,MB_ABORTRETRYIGNORE ))
			{
			case 3://终止
			return 0;
			case 4://重试
			resendcnt++;
			goto SENDCONTINUE;
			break;
			}
			break;*/
		}
	}
	SetWindowText(_T("--------------------------------------------------------------------------------\r\n"));
	return 0;
}

void CFView3762::SaveNodeInfo(INT32U sn, INT8U *recvBuf, INT16U recvLen)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nHang= 0;
	char szANSIString[5000];
	CString strlist[10];
	CString strUpDataMessage;
	
	CString stWhere = _T("ConfigName='节点信息'");
	m_accessData.SelectDataFromTable(pMain->m_PeiZhi_db,_T("Config"),_T("MessageData"),stWhere,&strUpDataMessage,nHang);
	//m_accessData.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("Config"),_T("MessageData"),stWhere,&strUpDataMessage,nHang);
	m_tools.Split(strUpDataMessage , _T("☆") , strlist , nHang);
	
	int len =WideCharToMultiByte(CP_ACP,0,strlist[0],strlist[0].GetLength(),NULL,0,NULL,NULL);
	char * pFileName = new char[len + 1];
	WideCharToMultiByte(CP_ACP,0,strlist[0],strlist[0].GetLength(),pFileName,len,NULL,NULL);
	pFileName[len] ='\0';

	m_tools.AutoMakedir(pFileName);

/*	m_fp = fopen(pFileName, "r+b");
	if(m_fp == NULL)
	{
		m_fp = fopen(pFileName, "w+b");
		
		char szANSIString[1000]; 
		CString strTopLine = _T("       STA_MAC,STA_ROLE,BT_DATE,BT_VER,CPU0_DATE,CPU0_VER,CPU1_DATE,CPU1_VER,PZ_DATE,PZ_VER,LIB_DATE,LIB_VER,HW_DATE,HW_VER\n");
		WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
		fwrite(szANSIString,wcslen(strTopLine),1,m_fp);
	}*/
	m_fp=fopen(pFileName,"r");
	if  ( m_fp == NULL )
	{
		m_fp=fopen(pFileName,"a+");

		if(m_fp != NULL) 
		{
			CString strTopLine = _T("    SN,       STA_MAC, STA_INFO\n");
			WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
			fwrite(szANSIString,wcslen(strTopLine),1,m_fp);
		}
	}
	else
	{
		fclose(m_fp); 
		m_fp=fopen(pFileName,"a+");
	} 
	if(m_fp != NULL) 
	{
		CString strAllTPdata = _T("");
		strAllTPdata = m_tools._buf16tostr16(recvBuf , recvLen);
	
		CString strlistData[20];
		INT8U n = recvBuf[2];
		INT8U i;
		for(i = 0; i < n; i++)
		{
			CString strSn;
		
			strSn.Format(_T("%d"),sn + i +1);
			strlistData[0] = strSn;

			CString  strMAC = strAllTPdata.Mid(i*16 + 6  , 12);
			strlistData[1] = m_tools._strDaoxu(strMAC);
			strlistData[2] = m_tools._strDaoxu(strAllTPdata.Mid(i*16 + 18 , 4));

			CString strTopLine = strlistData[0] + _T(",") + strlistData[1] + _T(",") + strlistData[2] + _T("\n");
			WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
			fwrite(szANSIString,wcslen(strTopLine),1,m_fp);
		}

		fclose(m_fp);
	}
	delete[] pFileName;
}
INT8U CFView3762::RecvNodeInfo(CString strName , INT8U *F8DataHead, int nChoose)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str = _T("======================================================\r\n");
	if (pMain->m_nChooseView == OPEN13762)
	{
		str += _T("★") + strName + _T("★\r\n");
	}
	else if (pMain->m_nChooseView == OPENNET)
	{
		str += _T("★F0F008转发13762报文（") + strName + _T("）★\r\n");
	}
	SetWindowText(str);

	CString strShuxingBiaoshiLen;
	INT8U Recvbufdata[JZQ_MAX_BUFF_LEN] , AddrBuf[7];
	INT16U Recvbuflen = 0 ,temp16 = 0;
	INT8U Sendbufdata[20] ;
	INT16U Sendbuflen = 3;
	INT8U ack = -1;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
//	SetUpdataListData();
	CString strDatalen = _T("");

	INT32U nTotalNum = 1;
	INT32U nReadStart = 0;

	int resendcnt = 0;

	switch (nChoose)
	{
	case  0:
		ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43 ,F8DataHead ,0x10 , F1 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2 , m_ptRecvQGDW376_2);
		break;
	case  1:
		m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
		ack = gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43 , F8DataHead, AddrBuf ,0x10 , F1 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2,ptRecvQGDW376_2 , m_ptRecvQGDW376_2);
		break;
	}
	if(0 == ack)
	{
		if (m_ptRecvQGDW376_2.s_head.s_AFN == 0x10 && m_ptRecvQGDW376_2.s_head.s_FN == F1)
		{
			nTotalNum = m_ptRecvQGDW376_2.s_RcvDataBuf[1];
			nTotalNum <<= 8;
			nTotalNum += m_ptRecvQGDW376_2.s_RcvDataBuf[0];
			SetWindowText(_T(">>>>节点数量:") + m_tools._str16tostr10(m_tools._buf16tostr16(&m_ptRecvQGDW376_2.s_RcvDataBuf[0] , 2 , false , true)) + _T("\r\n"));
		}
		else
		{
			SetWindowText(_T(">>>>数据包有误:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf , m_ptRecvQGDW376_2.s_RcvDataLen , false , true)) + _T("\r\n"));
			return 0;
		}
	}
	else
	{
		SetWindowText(_T(">>>>数据包有误:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf , m_ptRecvQGDW376_2.s_RcvDataLen , false , true)) + _T("\r\n"));
		return 0;
	}
	
	while(nReadStart < nTotalNum)
	{
		if (pMain->m_bCommunictStop)
		{
			SetWindowText(_T("--------------------------------------------------------------------------------\r\n"));
			return false;
		}
SENDCONTINUE:
		Sendbufdata[0] = (nReadStart + 1)&0xff;
		Sendbufdata[1] = ((nReadStart + 1)>>8)&0xff;
		Sendbufdata[2] = 10;
	    Sendbuflen = 3;
		switch (nChoose)
		{
		case  0:
			ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43 ,F8DataHead ,0x10 , F2 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2 , m_ptRecvQGDW376_2);
//			ack = gSimJzq.HostSendRcv376_2Buf(0xF0 , F21 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2 , m_ptRecvQGDW376_2);
			break;
		case  1:
			m_tools._str16tobuf16( pMain->m_strMAddress , AddrBuf , temp16 , true);
			ack = gSimJzq.HostSendRcv376_2F0F8MsgAddrBuf(0x43 , F8DataHead, AddrBuf ,0x10 , F2 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2,ptRecvQGDW376_2 , m_ptRecvQGDW376_2);
//			ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf ,0xF0 , F21 , Sendbufdata , Sendbuflen , m_ptSendQGDW376_2,ptRecvQGDW376_2 , m_ptRecvQGDW376_2);
			break;
		}
		switch(ack)
		{
		case 0:
			if (m_ptRecvQGDW376_2.s_head.s_AFN == 0x00 && m_ptRecvQGDW376_2.s_head.s_FN == F2)
			{
				str = pMain->GetRecvErrName(m_ptRecvQGDW376_2.s_RcvDataBuf[0]);
				
				CString strSn;
				strSn.Format(_T(", sn %d"),nReadStart+1);

				str = str + strSn + _T("\r\n");
				SetWindowText(str);
			
				if(resendcnt > 5)
				{
					break;
				}
				switch (MessageBox(_T("错误码:") + str + _T(" ，是否重发") ,_T("返回否认帧") ,MB_ABORTRETRYIGNORE ))
				{
				case 3://终止
					return 0;
				case 4://重试
					resendcnt++;
					goto SENDCONTINUE;
					break;
				}
			}
			else
			{
				if (m_ptRecvQGDW376_2.s_head.s_AFN == 0x10 && m_ptRecvQGDW376_2.s_head.s_FN == F2)
				{
					if(m_ptRecvQGDW376_2.s_RcvDataLen > 3)
					{
						SaveNodeInfo(nReadStart, &m_ptRecvQGDW376_2.s_RcvDataBuf[0], m_ptRecvQGDW376_2.s_RcvDataLen);

						SetWindowText(_T(">>>>接收成功:") + m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf , m_ptRecvQGDW376_2.s_RcvDataLen , false , true) + _T("\r\n"));
						nReadStart += m_ptRecvQGDW376_2.s_RcvDataBuf[2];
						resendcnt = 0;
						if(m_ptRecvQGDW376_2.s_RcvDataBuf[2] == 0)
						{
							break;
						}
					}
					else
					{
						SetWindowText(_T(">>>>数据包有误:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf , m_ptRecvQGDW376_2.s_RcvDataLen , false , true)) + _T("\r\n"));
					}
				}
				
			}
			break;
		default:
			str = pMain->GetRecvErrName(ack);

			CString strSn;
			strSn.Format(_T(", sn %d"),nReadStart+1);
			str = str + strSn + _T("\r\n");
			SetWindowText(str);

			if(resendcnt > 5)
			{
				break;
			}
			switch (MessageBox(_T("错误码:") + str + _T(" ，是否重发") ,_T("失败") ,MB_ABORTRETRYIGNORE ))
			{
			case 3://终止
				return 0;
			case 4://重试
				resendcnt++;
				goto SENDCONTINUE;
				break;
			}
			break;
		}
	}
	SetWindowText(_T("--------------------------------------------------------------------------------\r\n"));
	return 0;
}

void CFView3762::DisplayData(CString strName , CString strCode , CString strShowMsg , INT8U * databuf , INT16U datalen ,int nType)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str = _T("======================================================\r\n");
	if (pMain->m_nChooseView == OPEN13762)
	{
		str += _T("★") + strName + _T("★\r\n");
	}
	else if (pMain->m_nChooseView == OPENNET)
	{
		str += _T("★F0F008转发13762报文（") + strName + _T("）★\r\n");
	}
	if (datalen == 0)
	{
		str += _T(">>>>无数据\r\n");
		str += _T("--------------------------------------------------------------------------------\r\n");
	}
	else
	{
		switch (nType)
		{
		case 0:
			if (strCode == "")
			{
				str += _T(">>>>数据：") + m_tools._buf16tostr16(databuf, datalen) + _T("\r\n");
				str += _T("--------------------------------------------------------------------------------\r\n");
			}
			else
			{
				str += m_display.DisplayShowMessage(strCode, strShowMsg, databuf, datalen);
			}
			break;
		case 1:
			str += _T(">>>>成功：") + m_tools._buf16tostr16(databuf, datalen) + _T("\r\n");
			str += _T("--------------------------------------------------------------------------------\r\n");
			break;
		case 2:
			switch (databuf[0])
			{
			case 0:
				str += _T(">>>>失败:通信超时");
				break;
			case 1:
				str += _T(">>>>失败:无效数据单元");
				break;
			case 2:
				str += _T(">>>>失败:长度错");
				break;
			case 3:
				str += _T(">>>>失败:校验错误");
				break;
			case 4:
				str += _T(">>>>失败:信息类不存在");
				break;
			case 5:
				str += _T(">>>>失败:格式错误");
				break;
			case 6:
				str += _T(">>>>失败:表号重复");
				break;
			case 7:
				str += _T(">>>>失败:表号不存在");
				break;
			case 8:
				str += _T(">>>>失败:电表应用层无应答");
				break;
			case 9:
				str += _T(">>>>失败:主节点忙");
				break;
			case 10:
				str += _T(">>>>失败:主节点不支持此命令");
				break;
			case 11:
				str += _T(">>>>失败:从节点不应答");
				break;
			case 12:
				str += _T(">>>>失败:从节点不在网内");
				break;
			}
			str += _T("\r\n--------------------------------------------------------------------------------\r\n");
			break;
		}
	}
	SetWindowText(str);
}
void CFView3762::GetZuzhenFrame()
{
	CString str = _T("") , str1 = _T("");
	INT16U nlen = 0;
	int nBegin = 0;
	m_dlg13762Zuzhen.m_combC1.GetWindowTextW(str);
	m_ptSendQGDW376_2.s_head.u_con.s_conBit.s_Con_DIR = (INT8U)_ttoi(str.Mid(0,str.Find(_T(":"))));
	m_dlg13762Zuzhen.m_combC2.GetWindowTextW(str);
	m_ptSendQGDW376_2.s_head.u_con.s_conBit.s_Con_PRM = (INT8U)_ttoi(str.Mid(0,str.Find(_T(":"))));
	m_dlg13762Zuzhen.m_combC3.GetWindowTextW(str);
	m_ptSendQGDW376_2.s_head.u_con.s_conBit.s_Con_ComMode = (INT8U)_ttoi(str.Mid(0,str.Find(_T(":"))));

	m_dlg13762Zuzhen.m_combM1.GetWindowTextW(str);
	m_ptSendQGDW376_2.s_head.u_msg.s_DownMsgBit.s_Msg_RouterFlag = (INT8U)_ttoi(str.Mid(0,str.Find(_T(":"))));
	m_dlg13762Zuzhen.m_combM2.GetWindowTextW(str);
	m_ptSendQGDW376_2.s_head.u_msg.s_DownMsgBit.s_reserved_1 = (INT8U)_ttoi(str.Mid(0,str.Find(_T(":"))));
	m_dlg13762Zuzhen.m_combM3.GetWindowTextW(str);
	m_ptSendQGDW376_2.s_head.u_msg.s_DownMsgBit.s_Msg_ComFlag = (INT8U)_ttoi(str.Mid(0,str.Find(_T(":"))));
	m_dlg13762Zuzhen.m_combM4.GetWindowTextW(str);
	m_dlg13762Zuzhen.m_combM5.GetWindowTextW(str1);
	m_ptSendQGDW376_2.s_head.u_msg.s_DownMsgBit.s_reserved_2 = ((INT8U)_ttoi(str1.Mid(0,str1.Find(_T(":"))))) |((INT8U)_ttoi(str.Mid(0,str.Find(_T(":")))));

	m_dlg13762Zuzhen.m_combM6.GetWindowTextW(str);
	m_ptSendQGDW376_2.s_head.u_msg.s_DownMsgBit.s_chanle_num = (INT8U)_ttoi(str.Mid(0,str.Find(_T(":"))));
	m_dlg13762Zuzhen.m_combM7.GetWindowTextW(str);
	m_ptSendQGDW376_2.s_head.u_msg.s_DownMsgBit.s_errcode = (INT8U)_ttoi(str.Mid(0,str.Find(_T(":"))));

	m_dlg13762Zuzhen.m_editM1.GetWindowTextW(str);
	m_ptSendQGDW376_2.s_head.u_msg.s_DownMsgBit.s_ackbyte = (INT8U)_ttoi(str);

	m_dlg13762Zuzhen.m_combM8.GetWindowTextW(str);
	if (str.Find(_T(":")) == -1)
	{
		str = _T("0");
	}
	m_dlg13762Zuzhen.m_combM9.GetWindowTextW(str1);
	m_ptSendQGDW376_2.s_head.u_msg.s_DownMsgBit.s_errcode = ((INT8U)_ttoi(str1.Mid(0,str1.Find(_T(":")))))<<15 | ((INT8U)_ttoi(str));
	m_dlg13762Zuzhen.m_editM2.GetWindowTextW(str);
	m_ptSendQGDW376_2.s_head.s_Msg_Seq = (INT8U)_ttoi(str);

	m_dlg13762Zuzhen.m_editA1.GetWindowTextW(str);
	m_tools._str16tobuf16(str , m_ptSendQGDW376_2.s_head.s_MainAddBuf , nlen , true);
	/*m_dlg13762Zuzhen.m_editA3.GetWindowTextW(str);
	m_tools._str16tobuf16(str , m_ptSendQGDW376_2.s_head.s_DestAddBuf , nlen , true);*/

	
}
void CFView3762::ShowZuzhenData(INT8U nType)
{
	CString strMessage = _T("==================================================\r\n") , str = _T("");
	strMessage += _T("--------------------控制码--------------------\r\n");
	if (m_ptRecvQGDW376_2.s_head.u_con.s_conBit.s_Con_DIR)
	{
		strMessage += _T("传输方向：上行");
	}
	else
	{
		strMessage += _T("传输方向：下行");
	}
	strMessage += _T("\r\n");
	if (m_ptRecvQGDW376_2.s_head.u_con.s_conBit.s_Con_PRM)
	{
		strMessage += _T("启动标志：启动站");
	}
	else
	{
		strMessage += _T("启动标志：从动站");
	}
	strMessage += _T("\r\n");
	switch (m_ptRecvQGDW376_2.s_head.u_con.s_conBit.s_Con_ComMode)
	{
	case 1:
		strMessage += _T("通讯方式：集中式路由载波");
		break;
	case 2:
		strMessage += _T("通讯方式：分布式路由载波");
		break;
	case 3:
		strMessage += _T("通讯方式：宽带载波");
		break;
	case 10:
		strMessage += _T("通讯方式：微功率无线");
		break;
	case 20:
		strMessage += _T("通讯方式：以太网");
		break;
	}
	strMessage += _T("\r\n");
	strMessage += _T("--------------------信息域--------------------\r\n");

	if (m_ptRecvQGDW376_2.s_head.u_msg.s_UpMsgBit.s_Msg_RouterFlag)
	{
		strMessage += _T("路由标识：不带路由或工作在旁路模式\r\n");
	}
	else
	{
		strMessage += _T("路由标识：带路由或工作在路由模式\r\n");
	}
	if (m_ptRecvQGDW376_2.s_head.u_msg.s_UpMsgBit.s_Msg_ComFlag)
	{
		strMessage += _T("通讯模块标识：从节点操作\r\n");
	}
	else
	{
		strMessage += _T("通讯模块标识：主节点操作\r\n");
	}
	str.Format(_T("%d") , m_ptRecvQGDW376_2.s_head.u_msg.s_UpMsgBit.s_reserved_2>1);
	if(str == "0")
	{
		strMessage += _T("中继级别：无中继\r\n");
	}
	else
	{
		strMessage += _T("中继级别：" + str + _T("\r\n"));
	}

	str.Format(_T("%d") , m_ptRecvQGDW376_2.s_head.u_msg.s_UpMsgBit.s_chanle_num);
	if(str == "0")
	{
		strMessage += _T("信道标识：部分信道\r\n");
	}
	else
	{
		strMessage += _T("信道标识：第") + str + _T("信道\r\n");
	}

	str.Format(_T("%d") , m_ptRecvQGDW376_2.s_head.u_msg.s_UpMsgBit.s_Msg_phase);
	if(str == "0")
	{
		strMessage += _T("相线标识：不确定\r\n");
	}
	else
	{
		strMessage += _T("相线标识：第") + str + _T("相线\r\n");
	}

	switch(m_ptRecvQGDW376_2.s_head.u_msg.s_UpMsgBit.s_Meter_flag)
	{
	case 1:
		strMessage += _T("通道特征：物理信道为单相供电，逻辑信道为单信道\r\n");
		break;
	case 2:
		strMessage += _T("通道特征：物理信道为单相供电，逻辑信道为两信道\r\n");
		break;
	case 3:
		strMessage += _T("通道特征：物理信道为单相供电，逻辑信道为三信道\r\n");
		break;
	case 4:
		strMessage += _T("通道特征：物理信道为三相供电，逻辑信道为三信道\r\n");
		break;
	default:
		strMessage += _T("通道特征：保留\r\n");
		break;
	}

	str.Format(_T("%d") , m_ptRecvQGDW376_2.s_head.u_msg.s_UpMsgBit.s_CmdCsq);
	strMessage += _T("信号品质：") + str + _T("\r\n");

	if(m_ptRecvQGDW376_2.s_head.u_msg.s_UpMsgBit.s_Msg_Event)
	{
		strMessage += _T("事件标志：有上报事件\r\n");
	}
	else
	{
		strMessage += _T("事件标志：无上报事件\r\n");
	}
	
	str.Format(_T("%d") , m_ptRecvQGDW376_2.s_head.s_Msg_Seq);
	if(nType == 0x30)
	{
		strMessage += _T("序列号：") + str + _T("（接收与发送不一致）\r\n");
	}
	else
	{
		strMessage += _T("序列号：") + str + _T("\r\n");
	}
	

	strMessage += _T("--------------------地址域--------------------\r\n");

	if(m_ptRecvQGDW376_2.s_head.u_msg.s_UpMsgBit.s_Msg_ComFlag)
	{
		strMessage += _T("源地址：") + m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_head.s_MainAddBuf , 6 , false , true) + _T("\r\n");
		strMessage += _T("目的地址：") + m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_head.s_DestAddBuf , 6 , false , true) + _T("\r\n");
	}
	else
	{
		strMessage += _T("源地址：无\r\n");
		strMessage += _T("目的地址：无\r\n");
	}
	strMessage += _T("--------------------数据域--------------------\r\n");
	
	strMessage += _T("AFN=") + m_tools._buf16tostr16(&m_ptRecvQGDW376_2.s_head.s_AFN , 1) + _T("H    ");
	strMessage += _T("FN=") + m_tools._str16toF(m_ptRecvQGDW376_2.s_head.s_FN) + _T("\r\n");
	strMessage += _T("数据：") + m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf,m_ptRecvQGDW376_2.s_RcvDataLen) + _T("\r\n");
	strMessage +=_T("==================================================\r\n");
	SetWindowText(strMessage);
}
void CFView3762::SetWindowText(CString strData)
{
	CString strEditXianshi;
	m_editShow.GetWindowText(strEditXianshi);
	m_editShow.SetSel(strEditXianshi.GetLength(),strEditXianshi.GetLength());
	m_editShow.ReplaceSel(strData);
}
DWORD WINAPI ThreadSendbufZuzhen (PVOID pParam) 
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CFView3762 *pView=(CFView3762*)pParam;
	CString str = _T("");
	CStringA strA;
	INT8U u8AFN = 0,ack = FALSE;
	INT16U u16FN = 0 , SendDatalen = 0 , temp16 = 0;
	INT8U SendDatabuf[JZQ_MAX_BUFF_LEN] , AddrBuf[6] , MainAddrBuf[7];
	pView->GetZuzhenFrame();

	pView->m_dlg13762Zuzhen.m_editA1.GetWindowTextW(str);
	pView->m_tools._str16tobuf16(str , AddrBuf , temp16 , true);

	Cgw13762.QueMainAdd(MainAddrBuf);
	Cgw13762.SetMainAdd(AddrBuf);

	pView->m_dlg13762Zuzhen.m_editA3.GetWindowTextW(str);
	pView->m_tools._str16tobuf16(str , AddrBuf , temp16 , true);

	pView->m_dlg13762Zuzhen.m_combAFN.GetWindowTextW(str);
	strA = str;
	u8AFN = (INT8U)strtol(strA,NULL,16);
	pView->m_dlg13762Zuzhen.m_editFN.GetWindowTextW(str);
	pView->m_tools._strFto16(str ,u16FN);
	pView->m_dlg13762Zuzhen.m_editData.GetWindowTextW(str);
	pView->m_tools._str16tobuf16(str , SendDatabuf , SendDatalen);

	if (pView->m_ptSendQGDW376_2.s_head.u_msg.s_DownMsgBit.s_Msg_ComFlag == 0x01)
	{
		ack = gSimJzq.HostSendRcv376_2BufNode(AddrBuf ,u8AFN , u16FN , SendDatabuf , SendDatalen , pView->m_ptSendQGDW376_2 , pView->m_ptRecvQGDW376_2);
	}
	else
	{
		ack = gSimJzq.HostSendRcv376_2Buf(u8AFN , u16FN , SendDatabuf , SendDatalen , pView->m_ptSendQGDW376_2 , pView->m_ptRecvQGDW376_2);
	}
	switch(ack)
	{
	case 0:
		pView->ShowZuzhenData();
		break;
	case 0x13://失败
		pView->SetWindowText(_T("通讯失败！！！\r\n"));
		break;
	case 0x30://SEQ不一致
		pView->ShowZuzhenData(ack);
		break;
	case 0x0A://主节点不支持此命令
		pView->SetWindowText(_T("主节点不支持此命令！！！\r\n"));
		break;
	default:
		pView->SetWindowText(_T("其他错误！！！\r\n"));
		break;
	}
	pView->m_btnSend.EnableWindow(TRUE);
	Cgw13762.SetMainAdd(MainAddrBuf);
	return 0;
}
static UINT ThreadSendbuf (LPVOID pParam) 
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CFView3762 *pView=(CFView3762*)pParam;
	INT8U ack = 0 , u8SendAFN = 0 ,AddrBuf[7] ,F8DataHead[20];
	INT8U SendDatabuf[JZQ_MAX_BUFF_LEN];
	INT8U SendFramebuf[JZQ_MAX_BUFF_LEN];
	INT16U SendDatalen = 0 ,SendFramelen = 0 ,u16SendFN = 0 , temp16 = 0;
	CString strAFN_FN , strData , strWhere , strDataName , strDatalist[5] , strMAddress = _T("");
	CStringA str;
	int nHang= 0;

	

	INT32U u32SendFN =0;//南网fn
	CString str_32;//NW用


	pView->m_editAddress.GetWindowText(pView->m_strMessageData);
	pView->m_tools._str16tobuf16(pView->m_strMessageData , F8DataHead , temp16);

	
	//pMain->m_strMAddress = pView->m_strMessageData;

	 memset((INT8U*)&pView->m_ptSendQGDW376_2, 0, sizeof(sPartQCSG376_2CreatFrame));
	memset((INT8U*)&pView->m_ptRecvQGDW376_2, 0, sizeof(sPartQCSG376_2DeCodeFrame));
	pView->m_ptSendQGDW376_2.s_SendDataLen = 0;
	pView->m_ptSendQGDW376_2.s_RcvDataLen = 0;
	pView->m_ptRecvQGDW376_2.s_RcvDataLen = 0;

	if (pMain->NW_OR_GW == 1)
	{
		memset((INT8U*)&pView->m_ptSendQCSG376_2, 0, sizeof(sPartQCSG376_2CreatFrame));
		memset((INT8U*)&pView->m_ptRecvQCSG376_2, 0, sizeof(sPartQCSG376_2DeCodeFrame));
		pView->m_ptSendQCSG376_2.s_SendDataLen = 0;
		pView->m_ptSendQCSG376_2.s_RcvDataLen = 0;
		pView->m_ptRecvQCSG376_2.s_RcvDataLen = 0;
	}


	for(POSITION pos = pMain->m_FenzuFnList.GetHeadPosition(); pos != NULL;)
	{
		if (pMain->m_bCommunictStop)
		{
			pView->m_btnSend.EnableWindow(TRUE);
			pMain->m_bCommunictStop = false;
			return 0;
		}
		strAFN_FN=(CString)pMain->m_FenzuFnList.GetNext(pos);
		strDataName = strAFN_FN;
		str = strAFN_FN.Mid(0,2);//02F001  02
		u8SendAFN = (INT8U)strtol(str,NULL,16);//AFN
		pView->m_tools._strFto16(strAFN_FN.Mid(3,3),u16SendFN);//数据单元标识
		strAFN_FN = strAFN_FN.Mid(0,6);


		str_32=strAFN_FN.Mid(3,3);//NW
		u32SendFN=pView->getNWfn(u8SendAFN,str_32);//NW

		switch (u8SendAFN)
		{
		case 0x15:
			pView->SendUpdataData(strDataName, F8DataHead);
			break;
		case 0xFE:
			pView->SendSecretData(strDataName);
			break;
		default:
			strWhere = _T("AFN_FN='") + strAFN_FN + _T("'");
			if(pView->m_accessData.SelectDataFromTable(pMain->m_PeiZhi_db,_T("DataMessage"),_T("Databuf,Datalen,UpBM,UpXS"),strWhere,&strData,nHang))
			{
				if(pMain->NW_OR_GW==0)
				{
					pView->m_tools.strlistData(strData,_T("$"),strDatalist);
					pView->m_tools._str16tobuf16(strDatalist[0]  , SendDatabuf , SendDatalen);
//---------读运行日志 读STA版本号 特殊处理------------------------------------------------------------------------------------
					if(u8SendAFN == 0xF0 && u16SendFN == F21)  // AFN=F0, F21 读运行日志
					{
						if(SendDatabuf[0] == 0x00 && SendDatabuf[1] == 0x00 && SendDatabuf[2] == 0x00
							&& SendDatabuf[3] == 0x00 && SendDatabuf[4] == 0x00 && SendDatabuf[5] == 0x00)
						{
							pView->RecvDebugData(strDataName, F8DataHead);
							break;
						}
					}
					if(u8SendAFN == 0xF0 && u16SendFN == F153)  // AFN=F0, F153 读STA版本号
					{
						if(SendDatabuf[0] == 0x00 && SendDatabuf[1] == 0x00 && SendDatabuf[2] == 0x00)
						{
							pView->RecvExtendStaVersion(strDataName, F8DataHead);
							break;
						}
					}
					if (u8SendAFN == 0xF0 && u16SendFN == F158)  // AFN=F0, F153 读STA的设备状态号
					{
						if (SendDatabuf[0] == 0x00 && SendDatabuf[1] == 0x00 && SendDatabuf[2] == 0x00)
						{
							pView->RecvExtendStaDevStatus(strDataName, F8DataHead);
							break;
						}
					}
					if(u8SendAFN == 0x10 && u16SendFN == F2)  // AFN=10, 2 读节点信息
					{
						if(SendDatabuf[0] == 0x00 && SendDatabuf[1] == 0x00 && SendDatabuf[2] == 0x00)
						{
							pView->RecvNodeInfo(strDataName, F8DataHead);
							break;
						}
					}

					if (u8SendAFN == 0xF0 && u16SendFN == F1)  
					{
						if (SendDatabuf[4] == 0x00&&SendDatabuf[5] == 0x00)
						{
							pView->Save_log_File(F8DataHead);
							break;
						}
					}


//------------------------------------------------------------------------------------------------------------------

                    if(u8SendAFN == 0xF1 && u16SendFN == F1)  // 并发抄表修改超时
						ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43, F8DataHead, u8SendAFN, u16SendFN, SendDatabuf, SendDatalen, pView->m_ptSendQGDW376_2, pView->m_ptRecvQGDW376_2, pView->m_F1F0_TimeOut*1000);
                    else
					    ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43 ,F8DataHead ,u8SendAFN , u16SendFN , SendDatabuf , SendDatalen , pView->m_ptSendQGDW376_2 , pView->m_ptRecvQGDW376_2);
					switch (ack)
					{
					case 0x00://成功
						if (pView->m_ptRecvQGDW376_2.s_head.s_AFN == 0x00)
						{
							if (pView->m_ptRecvQGDW376_2.s_head.s_FN == F2)
							{
								pView->DisplayData(strDataName, strDatalist[2] , strDatalist[3] ,  pView->m_ptRecvQGDW376_2.s_RcvDataBuf ,  pView->m_ptRecvQGDW376_2.s_RcvDataLen , 2);
							}
							else
							{
								pView->DisplayData(strDataName, strDatalist[2] , strDatalist[3] ,  pView->m_ptRecvQGDW376_2.s_RcvDataBuf ,  pView->m_ptRecvQGDW376_2.s_RcvDataLen , 1);
							}
						}
						else
						{
							pView->DisplayData(strDataName, strDatalist[2] , strDatalist[3] ,  pView->m_ptRecvQGDW376_2.s_RcvDataBuf ,  pView->m_ptRecvQGDW376_2.s_RcvDataLen);
						}
						break;
					case 0x30://SEQ不相同
						pView->DisplayData(strDataName,strDatalist[2] , strDatalist[3] ,  pView->m_ptRecvQGDW376_2.s_RcvDataBuf ,  pView->m_ptRecvQGDW376_2.s_RcvDataLen);
						break;
					}
				}

				/////NW
				else if(pMain->NW_OR_GW==1)
				{

					INT8U CSG_Srccn;//控制位
					sPartQCSG376_2_Head  tmpfame;
					tmpfame.u_con.s_conBit.s_Con_reserved = 0;
					tmpfame.u_con.s_conBit.s_Con_VER = 0;
					tmpfame.u_con.s_conBit.s_Con_ADD = Ccsg13762.GetADDFlag(u32SendFN);
					tmpfame.u_con.s_conBit.s_Con_DIR = DBIT_376_2Con_DIR ;
					tmpfame.u_con.s_conBit.s_Con_PRM = DV376_2CON_PRM_MASTER;
					CSG_Srccn=tmpfame.u_con.s_conByte;
					pView->m_tools.strlistData(strData,_T("$"),strDatalist);
					pView->m_tools._str16tobuf16(strDatalist[0]  , SendDatabuf , SendDatalen);
					ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(CSG_Srccn,F8DataHead ,u8SendAFN , u32SendFN , SendDatabuf , SendDatalen , pView->m_ptSendQCSG376_2 , pView->m_ptRecvQCSG376_2);
					switch (ack)
					{
					case 0x00://成功
						if (pView->m_ptRecvQCSG376_2.s_head.s_AFN == 0x00)
						{
							if (pView->m_ptRecvQCSG376_2.s_head.s_FN == FN_00_F2)
							{
								pView->DisplayData(strDataName, strDatalist[2] , strDatalist[3] ,  pView->m_ptRecvQCSG376_2.s_RcvDataBuf ,  pView->m_ptRecvQCSG376_2.s_RcvDataLen , 2);
							}
							else
							{
								pView->DisplayData(strDataName, strDatalist[2] , strDatalist[3] ,  pView->m_ptRecvQCSG376_2.s_RcvDataBuf ,  pView->m_ptRecvQCSG376_2.s_RcvDataLen , 1);
							}
						}
						else
						{
							pView->DisplayData(strDataName, strDatalist[2] , strDatalist[3] ,  pView->m_ptRecvQCSG376_2.s_RcvDataBuf ,  pView->m_ptRecvQCSG376_2.s_RcvDataLen);
						}
						break;
					case 0x30://SEQ不相同
						pView->DisplayData(strDataName,strDatalist[2] , strDatalist[3] ,  pView->m_ptRecvQCSG376_2.s_RcvDataBuf ,  pView->m_ptRecvQCSG376_2.s_RcvDataLen);
						break;
					}
				}
			}
			break;
		}
	}
	pView->m_btnSend.EnableWindow(TRUE);
	AfxEndThread(0);
	return 0;
}
static UINT ThreadSendRepeat (LPVOID pParam) 
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CFView3762 *pView=(CFView3762*)pParam;
	sPartQGDW376_2CreatFrame ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;

	sPartQCSG376_2CreatFrame ptSendQCSG376_2;//NW
	sPartQCSG376_2DeCodeFrame ptRecvQCSG376_2;//NW


	INT8U ack = 0 , u8SendAFN = 0 ,AddrBuf[7];
	INT8U F8DataHead[20];

	INT8U SendDatabuf[JZQ_MAX_BUFF_LEN];
	INT8U SendFramebuf[JZQ_MAX_BUFF_LEN];
	INT16U SendDatalen = 0 ,SendFramelen = 0 ,u16SendFN = 0 , temp16 = 0;
	CString strAFN_FN , strData , strWhere , strDataName , strDatalist[5] , strMAddress = _T("");
	CStringA str;

	INT32U u32SendFN =0;//南网fn
	CString str_32;//NW用


	int nHang= 0;
	pView->m_tools._str16tobuf16(pMain->m_strMAddress , AddrBuf , temp16 , true);
	pView->m_editAddress.GetWindowText(pView->m_strMessageData);
	pView->m_tools._str16tobuf16(pView->m_strMessageData , F8DataHead , temp16);

	//TRACE("\nSIZEOF %d\n",sizeof(sPartQCSG376_2CreatFrame));

	memset((INT8U*)&ptSendQGDW376_2, 0, sizeof(sPartQCSG376_2CreatFrame));
	memset((INT8U*)&ptRecvQGDW376_2, 0, sizeof(sPartQCSG376_2DeCodeFrame));
	ptSendQGDW376_2.s_SendDataLen = 0;
	ptSendQGDW376_2.s_RcvDataLen = 0;
	ptRecvQGDW376_2.s_RcvDataLen = 0;

	if (pMain->NW_OR_GW == 1)
	{
		memset((INT8U*)&ptSendQCSG376_2, 0, sizeof(sPartQCSG376_2CreatFrame));
		memset((INT8U*)&ptRecvQCSG376_2, 0, sizeof(sPartQCSG376_2DeCodeFrame));
		ptSendQCSG376_2.s_SendDataLen = 0;
		ptSendQCSG376_2.s_RcvDataLen = 0;
		ptRecvQCSG376_2.s_RcvDataLen = 0;
	}


#if DEF_TRACE
	TRACE("\nbuf \n");
	for (int i = 0; i<2048; i++)
	{
		TRACE("%x ", ptSendQGDW376_2.s_SendDataBuf[i]);
	}
	
	TRACE("\ninit: buf %x, len %x\n", ptSendQGDW376_2.s_SendDataBuf[0], ptSendQGDW376_2.s_SendDataLen);
#endif

	if (ptSendQGDW376_2.s_SendDataLen > (D3762_MAX_FRAME_LEN - 2))
	{
		pView->m_btnSend.EnableWindow(TRUE);
		AfxEndThread(0);
		return 0;
	}

	for(POSITION pos = pMain->m_FenzuFnList.GetHeadPosition(); pos != NULL;)
	{
		if (pMain->m_bCommunictStop)
		{
			pView->m_btnSend.EnableWindow(TRUE);
			pMain->m_bCommunictStop = false;
			return 0;
		}
		strAFN_FN=(CString)pMain->m_FenzuFnList.GetNext(pos);
		strDataName = strAFN_FN;
		str = strAFN_FN.Mid(0,2);
		u8SendAFN = (INT8U)strtol(str,NULL,16);//AFN
		pView->m_tools._strFto16(strAFN_FN.Mid(3,3),u16SendFN);//数据单元标识
		strAFN_FN = strAFN_FN.Mid(0,6);

		str_32=strAFN_FN.Mid(3,3);//NW
		u32SendFN=pView->getNWfn(u8SendAFN,str_32);//NW


		switch (u8SendAFN)
		{
		case 0x15:
			pView->SendUpdataData(strDataName, F8DataHead ,1);
			break;
		case 0xFE:
			pView->SendSecretData(strDataName ,1);
			break;
		default:
			strWhere = _T("AFN_FN='") + strAFN_FN + _T("'");
			//if(pView->m_accessData.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("DataMessage"),_T("Databuf,Datalen,UpBM,UpXS"),strWhere,&strData,nHang))
			if(pView->m_accessData.SelectDataFromTable(pMain->m_PeiZhi_db,_T("DataMessage"),_T("Databuf,Datalen,UpBM,UpXS"),strWhere,&strData,nHang))
			{
				if(pMain->NW_OR_GW==0)
				{
					pView->m_tools.strlistData(strData,_T("$"),strDatalist);
					pView->m_tools._str16tobuf16(strDatalist[0]  , SendDatabuf , SendDatalen);
//---------读运行日志  读STA版本号 特殊处理------------------------------------------------------------------------------------
					if(u8SendAFN == 0xF0 && u16SendFN == 0x0210)  // AFN=F0, F21 读运行日志
					{
						if(SendDatabuf[0] == 0x00 && SendDatabuf[1] == 0x00 && SendDatabuf[2] == 0x00
							&& SendDatabuf[3] == 0x00 && SendDatabuf[4] == 0x00 && SendDatabuf[5] == 0x00)
						{
							pView->RecvDebugData(strDataName, F8DataHead, 1);
							break;
						}
					}
					if(u8SendAFN == 0xF0 && u16SendFN == 0x1301)  // AFN=F0, F153 读STA版本号
					{
						if(SendDatabuf[0] == 0x00 && SendDatabuf[1] == 0x00 && SendDatabuf[2] == 0x00)
						{
							pView->RecvExtendStaVersion(strDataName, F8DataHead, 1);
							break;
						}
					}
					if (u8SendAFN == 0xF0 && u16SendFN == F158)  // AFN=F0, F158 读STA版本号
					{
						if (SendDatabuf[0] == 0x00 && SendDatabuf[1] == 0x00 && SendDatabuf[2] == 0x00)
						{
							pView->RecvExtendStaDevStatus(strDataName, F8DataHead, 1);
							break;
						}
					}
					if(u8SendAFN == 0x10 && u16SendFN == 0x0002)  // AFN=10, 2 读节点信息
					{
						if(SendDatabuf[0] == 0x00 && SendDatabuf[1] == 0x00 && SendDatabuf[2] == 0x00)
						{
							pView->RecvNodeInfo(strDataName, F8DataHead, 1);
							break;
						}
					}
//------------------------------------------------------------------------------------------------------------------
				////	TRACE("\nf0f8!\n");

					
					
					pView->m_gw13762.Code376_2_F0F008Data(0x43 , F8DataHead ,u8SendAFN ,u16SendFN ,SendDatabuf ,SendDatalen ,ptSendQGDW376_2);

			//		TRACE("\nbefore len!\n");

					

					pView->m_tools.Buf_To_LenBuf(ptSendQGDW376_2.s_SendDataBuf , ptSendQGDW376_2.s_SendDataLen , SendDatabuf , SendDatalen );


			//		TRACE("\nafter len!\n");

					//lc南网扩展标记
					ack = gSimJzq.HostSendRcv376_2BufNode(AddrBuf , 0xF0 , F8 , SendDatabuf , SendDatalen , pView->m_ptSendQGDW376_2 , pView->m_ptRecvQGDW376_2);
					switch(ack)
					{
					case 0x00://成功
						temp16 = pView->m_ptRecvQGDW376_2.s_RcvDataBuf[1]<<8 | pView->m_ptRecvQGDW376_2.s_RcvDataBuf[0];
						if ((temp16 + 2) == pView->m_ptRecvQGDW376_2.s_RcvDataLen)
						{
							TRACE("\ninit: buf %x, len %x\n", ptRecvQGDW376_2.s_RcvDataBuf[0], ptRecvQGDW376_2.s_RcvDataLen);
							pView->m_gw13762.Decode376_2Frame(&pView->m_ptRecvQGDW376_2.s_RcvDataBuf[2] , temp16 , ptRecvQGDW376_2);

							TRACE("\ninit: buf %x, len %x\n", ptRecvQGDW376_2.s_RcvDataBuf[0], ptRecvQGDW376_2.s_RcvDataLen);
							pView->DisplayData(strDataName ,strDatalist[2] , strDatalist[3] ,  ptRecvQGDW376_2.s_RcvDataBuf ,  ptRecvQGDW376_2.s_RcvDataLen);

						}
						break;
					case 0x13://失败
						break;
					case 0x30://SEQ不一致
						temp16 = pView->m_ptRecvQGDW376_2.s_RcvDataBuf[1]<<8 | pView->m_ptRecvQGDW376_2.s_RcvDataBuf[0];
						if ((temp16 + 2) == pView->m_ptRecvQGDW376_2.s_RcvDataLen)
						{
							pView->m_gw13762.Decode376_2Frame(&pView->m_ptRecvQGDW376_2.s_RcvDataBuf[2] , temp16 , ptRecvQGDW376_2);
							pView->DisplayData(strDataName ,strDatalist[2] , strDatalist[3] ,  ptRecvQGDW376_2.s_RcvDataBuf ,  ptRecvQGDW376_2.s_RcvDataLen);
						}
						break;
					case 0x0A://主节点不支持此命令
						break;
					default:
						break;
					}
				}

								/////NW
				else if(pMain->NW_OR_GW==1)
				{

					INT8U CSG_Srccn;//控制位
					sPartQCSG376_2_Head  tmpfame;
					tmpfame.u_con.s_conBit.s_Con_reserved = 0;
					tmpfame.u_con.s_conBit.s_Con_VER = 0;
					tmpfame.u_con.s_conBit.s_Con_ADD = Ccsg13762.GetADDFlag(u32SendFN);
					tmpfame.u_con.s_conBit.s_Con_DIR = DBIT_376_2Con_DIR ;
					tmpfame.u_con.s_conBit.s_Con_PRM = DV376_2CON_PRM_MASTER;
					CSG_Srccn=tmpfame.u_con.s_conByte;
					pView->m_tools.strlistData(strData,_T("$"),strDatalist);
					pView->m_tools._str16tobuf16(strDatalist[0]  , SendDatabuf , SendDatalen);
					pView->m_nw13762.Code376_2_F0F008Data(CSG_Srccn , F8DataHead ,u8SendAFN ,u32SendFN ,SendDatabuf ,SendDatalen ,ptSendQCSG376_2);
					pView->m_tools.Buf_To_LenBuf(ptSendQCSG376_2.s_SendDataBuf , ptSendQCSG376_2.s_SendDataLen , SendDatabuf , SendDatalen );
					//lc南网扩展标记
					ack = gSimJzq.HostSendRcv376_2BufNode(AddrBuf , 0xF0 , FN_F0_F8 , SendDatabuf , SendDatalen , pView->m_ptSendQCSG376_2 , pView->m_ptRecvQCSG376_2);
					switch(ack)
					{
					case 0x00://成功
						temp16 = pView->m_ptRecvQCSG376_2.s_RcvDataBuf[1]<<8 | pView->m_ptRecvQCSG376_2.s_RcvDataBuf[0];
						if ((temp16 + 2) == pView->m_ptRecvQCSG376_2.s_RcvDataLen)
						{
							pView->m_nw13762.Decode376_2Frame(&pView->m_ptRecvQCSG376_2.s_RcvDataBuf[2] , temp16 , ptRecvQCSG376_2);
							pView->DisplayData(strDataName ,strDatalist[2] , strDatalist[3] ,  ptRecvQCSG376_2.s_RcvDataBuf ,  ptRecvQCSG376_2.s_RcvDataLen);
						}
						break;
					case 0x13://失败
						break;
					case 0x30://SEQ不一致
						temp16 = pView->m_ptRecvQCSG376_2.s_RcvDataBuf[1]<<8 | pView->m_ptRecvQCSG376_2.s_RcvDataBuf[0];
						if ((temp16 + 2) == pView->m_ptRecvQCSG376_2.s_RcvDataLen)
						{
							pView->m_nw13762.Decode376_2Frame(&pView->m_ptRecvQCSG376_2.s_RcvDataBuf[2] , temp16 , ptRecvQCSG376_2);
							pView->DisplayData(strDataName ,strDatalist[2] , strDatalist[3] ,  ptRecvQCSG376_2.s_RcvDataBuf ,  ptRecvQCSG376_2.s_RcvDataLen);
						}
						break;
					case 0x0A://主节点不支持此命令
						break;
					default:
						break;
					}
				}

			}
			break;
		}
	}
	pView->m_btnSend.EnableWindow(TRUE);
	AfxEndThread(0);
	return 0;
}

void CFView3762::OnBnClickedButtonSend()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();

	CString strMessageAddress;
	m_editAddress.GetWindowText(strMessageAddress);
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{
		if (m_bZuZhen)
		{
			m_btnSend.EnableWindow(FALSE);
			m_hThreadsend=CreateThread (NULL,0,ThreadSendbufZuzhen,this,0,NULL);
		} 
		else
		{
			if (strMessageAddress == "")
			{
				AfxMessageBox(_T("请配置信息域与地址域数据！"));
				return;
			}

			//if (pMain->m_nChooseView == OPENNET)
			//{
			//	if (pMain->m_strMAddress == "")
			//	{
			//		AfxMessageBox(_T("请先连接CCO！"));
			//	#if (0==LOOPTEST)
			// return;
			//#endif
			//	}
			//}


			StorageListData();
			if (pMain->m_FenzuFnList.GetCount() == 0)
			{
				AfxMessageBox(_T("请勾选要操作的数据！"));
				return;
			}
			m_btnSend.EnableWindow(FALSE);
			switch(pMain->m_nChooseView)
			{
			case OPEN13762:
				//m_hThreadsend=CreateThread (NULL,0,ThreadSendbuf,this,0,NULL);
				AfxBeginThread(ThreadSendbuf, this);
				break;
			case OPENNET:
				//m_hThreadsend=CreateThread (NULL,0,ThreadSendRepeat,this,0,NULL);
				AfxBeginThread(ThreadSendRepeat, this);
				break;
			}
		}
		//CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("请打开串口！"));
	}
}

void CFView3762::OnBnClickedButtonXy()
{
	CDlgXYData dlgXY;
	dlgXY.DoModal();
	UpdataTreeData();
}

void CFView3762::OnBnClickedButtonStop()
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	pMain->m_bCommunictStop = true;
}

BOOL CFView3762::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			if (m_strPWData == "openfef001")
			{
				if (!m_bFEF001)
				{
					HTREEITEM hPrieant = m_treeData.InsertItem(_T("FEH内部协议"),m_hTree);
					m_treeData.InsertItem(_T("(F001)配置文件"),hPrieant);
					m_treeData.Expand(hPrieant,TVE_EXPAND);
					AfxMessageBox(_T("已打开内部命令:AFN=FE,F001"));
					m_bFEF001 = true;
				}
			}
			break;
		case VK_ESCAPE:
			m_strPWData = _T("");
			break;
		case 0x30:
			m_strPWData += _T("0");
			break;
		case 0x31:
			m_strPWData += _T("1");
			break;
		case 0x32:
			m_strPWData += _T("2");
			break;
		case 0x33:
			m_strPWData += _T("3");
			break;
		case 0x34:
			m_strPWData += _T("4");
			break;
		case 0x35:
			m_strPWData += _T("5");
			break;
		case 0x36:
			m_strPWData += _T("6");
			break;
		case 0x37:
			m_strPWData += _T("7");
			break;
		case 0x38:
			m_strPWData += _T("8");
			break;
		case 0x39:
			m_strPWData += _T("9");
			break;
		case 0x41:
			m_strPWData += _T("a");
			break;
		case 0x42:
			m_strPWData += _T("b");
			break;
		case 0x43:
			m_strPWData += _T("c");
			break;
		case 0x44:
			m_strPWData += _T("d");
			break;
		case 0x45:
			m_strPWData += _T("e");
			break;
		case 0x46:
			m_strPWData += _T("f");
			break;
		case 0x47:
			m_strPWData += _T("g");
			break;
		case 0x48:
			m_strPWData += _T("h");
			break;
		case 0x49:
			m_strPWData += _T("i");
			break;
		case 0x4a:
			m_strPWData += _T("j");
			break;
		case 0x4b:
			m_strPWData += _T("k");
			break;
		case 0x4c:
			m_strPWData += _T("l");
			break;
		case 0x4d:
			m_strPWData += _T("m");
			break;
		case 0x4e:
			m_strPWData += _T("n");
			break;
		case 0x4f:
			m_strPWData += _T("o");
			break;
		case 0x50:
			m_strPWData += _T("p");
			break;
		case 0x51:
			m_strPWData += _T("q");
			break;
		case 0x52:
			m_strPWData += _T("r");
			break;
		case 0x53:
			m_strPWData += _T("s");
			break;
		case 0x54:
			m_strPWData += _T("t");
			break;
		case 0x55:
			m_strPWData += _T("u");
			break;
		case 0x56:
			m_strPWData += _T("v");
			break;
		case 0x57:
			m_strPWData += _T("w");
			break;
		case 0x58:
			m_strPWData += _T("x");
			break;
		case 0x59:
			m_strPWData += _T("y");
			break;
		case 0x5a:
			m_strPWData += _T("z");
			break;
		}
	}
	return 0; 
}

void CFView3762::OnBnClickedButtonClear()
{
	m_editShow.SetWindowTextW(_T(""));
}


void CFView3762::OnBnClickedButtonZuzhen()
{
	CString strName = _T("");
	m_btnZuZhen.GetWindowTextW(strName);
	if(strName == "组帧")
	{
		CRect rect , frect;   //获取控件变化前大小 
		GetClientRect(frect); 
		GetDlgItem(IDC_TREE_DATA)->GetWindowRect(&rect); 
		ScreenToClient(&rect);//将控件大小转换为在对话框中的区域坐标 
		m_dlg13762Zuzhen.SetWindowPos(NULL,rect.left,rect.top,frect.right/2-50,rect.bottom - rect.top,SWP_SHOWWINDOW);

		GetDlgItem(IDC_EDIT_SHOW)->GetWindowRect(&rect); 
		ScreenToClient(&rect);
		m_lShowLeft = rect.left;
		rect.left = frect.right/2;
		GetDlgItem(IDC_EDIT_SHOW)->MoveWindow(rect);//设置控件位置 
		m_treeData.ShowWindow(SW_HIDE);
		m_btnZuZhen.SetWindowTextW(_T("返回"));
		m_combType.ShowWindow(SW_HIDE);
		m_editAddress.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_ADDRESS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		m_bZuZhen = true;
	}
	else
	{
		CRect rect; 
		GetDlgItem(IDC_EDIT_SHOW)->GetWindowRect(&rect); 
		ScreenToClient(&rect);
		rect.left = m_lShowLeft;
		GetDlgItem(IDC_EDIT_SHOW)->MoveWindow(rect);//设置控件位置 
		m_dlg13762Zuzhen.ShowWindow(SW_HIDE);
		m_treeData.ShowWindow(SW_SHOW);
		m_btnZuZhen.SetWindowTextW(_T("组帧"));
		m_combType.ShowWindow(SW_SHOW);
		m_editAddress.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_ADDRESS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
		m_bZuZhen = false;
	}
}

/////////////////////////NW
INT32U CFView3762::getNWfn(INT8U GW_AFN , CString GW_Fn)
{
	INT32U NW_Fn=0x00000000;
	switch(GW_AFN)
	{
	case 0x01:
		if(GW_Fn=="001")
		{
			NW_Fn=FN_01_F1;
		}
		else if(GW_Fn=="002")
		{
			NW_Fn=FN_01_F2;
		}
		else if(GW_Fn=="003")
		{
			NW_Fn=FN_01_F3;
		}
		break;
	case 0x02:
		if(GW_Fn=="001")
		{
			NW_Fn=FN_02_F1;
		}
		else if(GW_Fn=="002")
		{
			NW_Fn=FN_02_F2;
		}
		else if(GW_Fn=="003")
		{
			NW_Fn=FN_02_F3;
		}
		else if(GW_Fn=="004")
		{
			NW_Fn=FN_02_F4;
		}
		else if(GW_Fn=="005")
		{
			NW_Fn=FN_02_F5;
		}
		else if(GW_Fn=="006")
		{
			NW_Fn=FN_02_F6;
		}
		else if(GW_Fn=="007")
		{
			NW_Fn=FN_02_F7;
		}
		else if(GW_Fn=="008")
		{
			NW_Fn=FN_02_F8;
		}
		else if(GW_Fn=="009")
		{
			NW_Fn=FN_02_F9;
		}
		break;
	case 0x03:
		if(GW_Fn=="001")
		{
			NW_Fn=FN_03_F1;
		}
		else if(GW_Fn=="002")
		{
			NW_Fn=FN_03_F2;
		}
		else if(GW_Fn=="003")
		{
			NW_Fn=FN_03_F3;
		}
		else if(GW_Fn=="004")
		{
			NW_Fn=FN_03_F4;
		}
		else if(GW_Fn=="005")
		{
			NW_Fn=FN_03_F5;
		}
		else if(GW_Fn=="006")
		{
			NW_Fn=FN_03_F6;
		}
		else if(GW_Fn=="007")
		{
			NW_Fn=FN_03_F7;
		}
		else if(GW_Fn=="008")
		{
			NW_Fn=FN_03_F8;
		}
		break;
	case 0x04:
		if(GW_Fn=="001")
		{
			NW_Fn=FN_04_F1;
		}
		else if(GW_Fn=="002")
		{
			NW_Fn=FN_04_F2;
		}
		else if(GW_Fn=="003")
		{
			NW_Fn=FN_04_F3;
		}
		else if(GW_Fn=="004")
		{
			NW_Fn=FN_04_F4;
		}
		else if(GW_Fn=="005")
		{
			NW_Fn=FN_04_F5;
		}
		else if(GW_Fn=="006")
		{
			NW_Fn=FN_04_F6;
		}
		break;
	case 0x05:
		if(GW_Fn=="001")
		{
			NW_Fn=FN_05_F1;
		}
		else if(GW_Fn=="002")
		{
			NW_Fn=FN_05_F2;
		}
		else if(GW_Fn=="003")
		{
			NW_Fn=FN_05_F3;
		}
		else if(GW_Fn=="004")
		{
			NW_Fn=FN_05_F4;
		}
		else if(GW_Fn=="005")
		{
			NW_Fn=FN_05_F5;
		}
		break;
	case 0x06:
		if(GW_Fn=="001")
		{
			NW_Fn=FN_06_F1;
		}
		break;
	case 0x07:
		if(GW_Fn=="001")
		{
			NW_Fn=FN_07_F1;
		}
		else if(GW_Fn=="002")
		{
			NW_Fn=FN_07_F2;
		}
		else if(GW_Fn=="003")
		{
			NW_Fn=FN_07_F3;
		}
		else if(GW_Fn=="004")
		{
			NW_Fn=FN_07_F4;
		}
		else if(GW_Fn=="005")
		{
			NW_Fn=FN_07_F5;
		}
		break;
	case 0xF0:
		if(GW_Fn=="001")
		{
			NW_Fn=FN_F0_F1;
		}
		else if(GW_Fn=="002")
		{
			NW_Fn=FN_F0_F2;
		}
		else if(GW_Fn=="003")
		{
			NW_Fn=FN_F0_F3;
		}
		else if(GW_Fn=="004")
		{
			NW_Fn=FN_F0_F4;
		}
		else if(GW_Fn=="005")
		{
			NW_Fn=FN_F0_F5;
		}
		else if(GW_Fn=="006")
		{
			NW_Fn=FN_F0_F6;
		}
		else if(GW_Fn=="007")
		{
			NW_Fn=FN_F0_F7;
		}
		else if(GW_Fn=="008")
		{
			NW_Fn=FN_F0_F8;
		}
		else if(GW_Fn=="009")
		{
			NW_Fn=FN_F0_F9;
		}
		else if(GW_Fn=="010")
		{
			NW_Fn=FN_F0_F10;
		}
		else if(GW_Fn=="011")
		{
			NW_Fn=FN_F0_F11;
		}
		else if(GW_Fn=="012")
		{
			NW_Fn=FN_F0_F12;
		}
		else if(GW_Fn=="013")
		{
			NW_Fn=FN_F0_F13;
		}
		else if(GW_Fn=="014")
		{
			NW_Fn=FN_F0_F14;
		}
		else if(GW_Fn=="015")
		{
			NW_Fn=FN_F0_F15;
		}
		else if(GW_Fn=="016")
		{
			NW_Fn=FN_F0_F16;
		}
		else if(GW_Fn=="017")
		{
			NW_Fn=FN_F0_F17;
		}
		else if(GW_Fn=="018")
		{
			NW_Fn=FN_F0_F18;
		}
		else if(GW_Fn=="019")
		{
			NW_Fn=FN_F0_F19;
		}
		else if(GW_Fn=="020")
		{
			NW_Fn=FN_F0_F20;
		}
		else if(GW_Fn=="021")
		{
			NW_Fn=FN_F0_F21;
		}
		else if(GW_Fn=="022")
		{
			NW_Fn=FN_F0_F22;
		}
		else if(GW_Fn=="023")
		{
			NW_Fn=FN_F0_F23;
		}
		else if(GW_Fn=="024")
		{
			NW_Fn=FN_F0_F24;
		}
		else if(GW_Fn=="025")
		{
			NW_Fn=FN_F0_F25;
		}
		else if(GW_Fn=="026")
		{
			NW_Fn=FN_F0_F26;
		}
		else if(GW_Fn=="027")
		{
			NW_Fn=FN_F0_F27;
		}
		else if(GW_Fn=="028")
		{
			NW_Fn=FN_F0_F28;
		}
		else if(GW_Fn=="029")
		{
			NW_Fn=FN_F0_F29;
		}
		else if(GW_Fn=="030")
		{
			NW_Fn=FN_F0_F30;
		}
		else if(GW_Fn=="031")
		{
			NW_Fn=FN_F0_F31;
		}
		else if(GW_Fn=="032")
		{
			NW_Fn=FN_F0_F32;
		}
		else if(GW_Fn=="153")
		{
			NW_Fn=FN_F0_F153;
		}
		else if(GW_Fn=="154")
		{
			NW_Fn=FN_F0_F154;
		}
		else if(GW_Fn=="0155")
		{
			NW_Fn=FN_F0_F155;
		}
		else if(GW_Fn=="0156")
		{
			NW_Fn=FN_F0_F156;
		}
		else if(GW_Fn=="0157")
		{
			NW_Fn=FN_F0_F157;
		}
		break;
	case 0xF1:
		if(GW_Fn=="001")
		{
			NW_Fn=FN_F1_F1;
		}
		break;
	default:
		break;
	}
	return NW_Fn;
}//NW

void CFView3762::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}
