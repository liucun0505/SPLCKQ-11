// SetWriteDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KD_Project.h"
#include "SetWriteDataDlg.h"
#include "MainFrm.h"
#include "AccessData.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetWriteDataDlg dialog


CSetWriteDataDlg::CSetWriteDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetWriteDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetWriteDataDlg)
	m_bWrite = true;
	//}}AFX_DATA_INIT
}


void CSetWriteDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetWriteDataDlg)
	DDX_Control(pDX, IDC_EDIT_DATA, m_editData);
	DDX_Control(pDX, IDC_LIST_DATA, m_listData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetWriteDataDlg, CDialog)
	//{{AFX_MSG_MAP(CSetWriteDataDlg)
	ON_BN_CLICKED(IDC_BUTTON_CHAKAN, OnButtonChakan)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DATA, OnClickListData)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DATA, OnDblclkListData)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetWriteDataDlg message handlers

BOOL CSetWriteDataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(m_strWriteName);
	m_ntiaoguo=0;
	m_listData.InsertColumn(0 ,_T("名称") , LVCFMT_LEFT , 400);
	m_listData.InsertColumn(1 ,_T("值") , LVCFMT_LEFT , 200);
	m_listData.InsertColumn(2 ,_T("") , LVCFMT_LEFT , 200);
	m_listData.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_editData.ShowWindow( 0 );
	setData();   //添加相应的字符
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetWriteDataDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_editData.m_hWnd  !=  NULL)
	{
		m_editData.ShowWindow( 0 );
		if (m_hitRow  !=   - 1 )
		{
			CString text;
			m_editData.GetWindowText(text);
			m_listData.SetItemText(m_hitRow, m_hitCol, text);
		}
	}
	m_hitCol  =  m_hitRow  =   - 1 ;
	CDialog::OnLButtonUp(nFlags, point);
}

void CSetWriteDataDlg::OnClickListData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pNMItemActivate  =  reinterpret_cast < LPNMITEMACTIVATE > (pNMHDR);
	if (m_editData.m_hWnd  !=  NULL)
	{
		m_editData.ShowWindow( 0 );
		if (m_hitRow  !=   - 1 )
		{
			CString text;
			m_editData.GetWindowText(text);
			m_listData.SetItemText(m_hitRow, m_hitCol, text);
		}
	}
	m_hitCol  =  m_hitRow  =   - 1 ;
	*pResult = 0;
}

void CSetWriteDataDlg::OnDblclkListData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pNMItemActivate  =  reinterpret_cast < LPNMITEMACTIVATE > (pNMHDR);
	LVHITTESTINFO info;
	CString strName;
	info.pt  =  pNMItemActivate -> ptAction;
	if (m_listData.SubItemHitTest( & info)  !=   - 1  )
	{
		if (m_listData.GetItemText(info.iItem, info.iSubItem) == "") return;
		if (info.iSubItem == 1)
		{
			m_hitRow  =  info.iItem;
			m_hitCol  =  info.iSubItem;
			CRect rect;
			m_listData.GetSubItemRect(info.iItem, info.iSubItem, LVIR_BOUNDS, rect);
			rect.top  +=   0 ;
			rect.left  +=   2 ;
			rect.right  +=   2 ;
			rect.bottom  +=   200 ;
			m_editData.SetWindowText(m_listData.GetItemText( info .iItem,  info .iSubItem));
			m_editData.MoveWindow( & rect, TRUE);
			m_editData.ShowWindow( 1 );
			m_editData.SetFocus();
		}
    }
	*pResult = 0;
}

void CSetWriteDataDlg::setData()
{
	CString strlist[1000];
	CString strlistData[1000];
	int nNumb = 0;

	m_tools.Split(m_strWriteDataMessage ,_T("$") ,strlistData ,nNumb);
	m_tools.Split(m_strGeshi ,_T(";") ,strlist ,nNumb);
	
	for(int n = 0 ; n < nNumb ; n++)
	{
		m_nBaifenhao[n] = m_tools.FindFNumb(strlist[n] , _T("%"));
		strlist[n] = strlist[n].Mid(0 , strlist[n].Find(_T("%")));
		m_listData.InsertItem(n ,strlist[n]);
		m_listData.SetItemText(n , 1 ,strlistData[n]);
	}

	if (nNumb < 22)
	{
		for(int n = 0 ; n < 22 - nNumb ; n++)
		{
			m_listData.InsertItem(m_listData.GetItemCount() , _T(""));
		}
	}
}

CString CSetWriteDataDlg::GetStatic(int n)
{
	return m_listData.GetItemText(n -1 ,0);
}
CString CSetWriteDataDlg::GetEdit(int n)
{
	return m_listData.GetItemText(n -1 ,1);
}

void CSetWriteDataDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strStatic,strEdit,strData,str;
	CString strFile;
	m_strWriteDataMessage = _T("");
	m_ntiaoguo=0;
	m_bYesOrNo=true;
	for(m_nFenhao=1;m_nFenhao<(m_nData+1);m_nFenhao++)
	{
		strStatic=GetStatic(m_nFenhao);
		strEdit=GetEdit(m_nFenhao);
		m_strWriteDataMessage += strEdit + _T("$");
		if (m_ntiaoguo==0)
		{
			str=GetData(m_nFenhao-1,strEdit);

			strData+=str;
		}
		else
		{
			m_ntiaoguo-=1;
		}	
	}
	if (m_bYesOrNo==false)
	{
		AfxMessageBox(_T("请重新输入!"));
		return;
	}
	m_strWriteData = strData;

	
	CDialog::OnOK();
}

CString CSetWriteDataDlg::GetData(int n,CString str)
{
	CString strData,strZhi;
	CString strbeizhu;
	int a,b;
	int x;
BEGIN:
	for(a=0;a<m_nBaifenhao[n];a++)
	{
		for(b=1;b<(int)(wcslen(m_strBeizhu)+1);b++)
		{
			if (m_strBeizhu.Left(b).Right(1)==";")
			{
				strbeizhu=m_strBeizhu.Left(b);
				m_strBeizhu=m_strBeizhu.Right(wcslen(m_strBeizhu)-b);
				if (strbeizhu.Left(4)=="loop")
				{
					goto BEGIN;
				}
				break;
			}
		}

		str=str+_T(",");
		int m=(int)(wcslen(str)+1);
		for (x=1;x<m;x++)
		{
			if (str.Left(x).Right(1)==",")
			{
				strZhi=str.Left(x-1);
				str=str.Right(wcslen(str)-x);
				break;
			}
		}
		
		if (strbeizhu.Left(4)=="bit,")
		{
			strData=GetBit(strbeizhu,n);
			break;
		}
		else
		{
			if (strbeizhu.Left(5)=="bits,")
			{
				strData=GetBits(strbeizhu,n);
				break;
			} 
			else
			{
				strData+=GetZijie(strbeizhu,strZhi);
			}
			
		}
		
	}

	return strData;
}
CString CSetWriteDataDlg::GetBit(CString strBeizhu,int n)
{
	CString strName,strZhi,strShizhi,strZongzhi,ForR;
	CString wcslenAndNum,strlong,strNun;
	CString strData,strDataNew;
	int nBitzong;
	BOOL bForR;
	int a;
	strName=GetStatic(n+1);
	strZhi=GetEdit(n+1);
	int nZhi=wcslen(strZhi);
	ForR=strBeizhu.Left(5).Right(1);
	if(ForR=="f")
	{
		bForR=FALSE;
	}
	if (ForR=="r")
	{
		bForR=TRUE;
	}
	wcslenAndNum=strBeizhu.Right(wcslen(strBeizhu)-6);
	wcslenAndNum=wcslenAndNum.Left(wcslen(wcslenAndNum)-1);
	if (wcslenAndNum.Left(2).Right(1)==",")
	{
		strlong=wcslenAndNum.Left(1);
		strNun=wcslenAndNum.Right(wcslen(wcslenAndNum)-2);
	}
	if (wcslenAndNum.Left(3).Right(1)==",")
	{
		strlong=wcslenAndNum.Left(2);
		strNun=wcslenAndNum.Right(wcslen(wcslenAndNum)-3);
	}
	nBitzong=_ttoi(strNun);

	CString str;
	if (nBitzong==m_nBaifenhao[n])
	{
		for(int a=0;a<(int)wcslen(strZhi);a++) 
		{
			strShizhi+=strZhi.Right(a+1).Left(1);
		}
		str=m_tools._str2tostr16(strShizhi);
		int b=wcslen(str)/2;
		if (ForR=="r")
		{
			for(a=0;a<b;a++)
			{
				strDataNew+=str.Right(2+2*a).Left(2);
			}
		} 
		else
		{
			for(a=0;a<b;a++)
			{
				strDataNew=str.Right(2+2*a).Left(2)+strDataNew;
			}
		}
		goto TIAOGUO;
	}
	while((nBitzong-m_nBaifenhao[n])>=0)
	{
		strZhi=GetEdit(n+1);
		strShizhi="";
		for(a=0;a<(int)wcslen(strZhi);a++) 
		{
			strShizhi+=strZhi.Right(a+1).Left(1);
		}
		if (bForR==FALSE)
		{
			strZongzhi+=strShizhi;
		} 
		else
		{
			strZongzhi=strShizhi+strZongzhi;
		}
		
		nBitzong=nBitzong-m_nBaifenhao[n];
		n++;
		m_ntiaoguo++;
	}
	m_ntiaoguo--;
	strData=m_tools._str2tostr16(strZongzhi);
	
	if (bForR)
	{
		for(a = 0 ; a<(wcslen(strData)/2);a++)
		{
			strDataNew += strData.Mid(wcslen(strData)-2*(a+1),2);
		}
	} 
	else
	{
		strDataNew = strData;
	}
TIAOGUO:
	int nCha=(_ttoi(strlong)-wcslen(strDataNew)/2);
	for(a=0;a<nCha;a++)
	{
		if(bForR)
		{
			strDataNew+=_T("00");
		}
		else
		{
			strDataNew=_T("00")+strDataNew;
		}
	}
	return strDataNew;
}

CString CSetWriteDataDlg::GetChina(CString strEdit)
{
	CString strData;
	char * cn;
	cn=(LPSTR)(LPCTSTR)strEdit;
	int cnl=wcslen(strEdit)/2;
	DWORD * dwcn=new DWORD[cnl];
	memset(dwcn,0,cnl*sizeof(DWORD));
	WORD * wcn=(WORD *)cn;

	CString str;
	for(int n=0;n<cnl;n++)
	{
		dwcn[n]=wcn[n];
		str.Format(_T("%d"),dwcn[n]);
		str=m_tools._str10tostr16(str,2);
		strData+=str.Right(2)+str.Left(2);
	}
	return strData;
}

CString CSetWriteDataDlg::GetZijie(CString strBeizhu,CString strEdit)
{
	CString strData;
	CString strDataGeshi;
	int a=1;
	for(a=1;a<(int)(wcslen(strBeizhu)+1);a++)
	{
		if((strBeizhu.Left(a).Right(1)==",")||(strBeizhu.Left(a).Right(1)==";"))
		{
			strDataGeshi=strBeizhu.Left(a-1);
			strBeizhu=strBeizhu.Right(wcslen(strBeizhu)-a);
			break;
		}
	}

	if (strDataGeshi=="bin")
	{
		strData=GetBin(strBeizhu,strEdit);
	}
	if (strDataGeshi=="ignor")
	{	
		int len=0;
		if (wcslen(strBeizhu)==2)
		{
			len=_ttoi(strBeizhu.Left(1));	
		}
		if (wcslen(strBeizhu)==3)
		{
			len=_ttoi(strBeizhu.Left(2));
		}
		if (wcslen(strBeizhu)==4)
		{
			len=_ttoi(strBeizhu.Left(3));
		}
		CString str0=_T("");
		for(a=0;a<2*len;a++)
		{
			str0+="0";
		}
		strData=str0;
		m_nFenhao-=1;

	}
	if (strDataGeshi=="DADT")
	{
		strData=GetDADT(strEdit);
	}
	if (strDataGeshi=="char")
	{
		strData=GetChar(strBeizhu,strEdit);
	}
	if (strDataGeshi=="ascll")
	{
		strData=GetAscll(strBeizhu,strEdit);
	}
	if (strDataGeshi=="TIME")
	{
		strData=GetTIME(strEdit);
	}
//	AfxMessageBox(strData);
	return strData;
}


CString CSetWriteDataDlg::GetBits(CString strBeizhu,int nZhi)
{
	int nbits=0;
	int len=0;
	int nDataNub=0;
	int n=0,j=0,k=0,m=1;
	int a,b;
	CString strDatalen[50];
	CString strData16,strData;



	strBeizhu=strBeizhu.Right(wcslen(strBeizhu)-5);
	bool bForR=FALSE;
	if (strBeizhu.Left(1)=="f")
	{
		bForR=TRUE;
	}
	strBeizhu=strBeizhu.Right(wcslen(strBeizhu)-2)+_T("!");
	
	
	while(strBeizhu.Left(m).Right(1)!="!")
	{
		j++;
		n=0;
		while((strBeizhu.Left(m).Right(1)!=",")&&(strBeizhu.Left(m).Right(1)!="!"))
		{
			m++;
			n++;
		}
		if (j==1)
		{
			len=_ttoi(strBeizhu.Left(m-1).Right(n));
		}
		if (j==2)
		{
			nDataNub=_ttoi(strBeizhu.Left(m-1).Right(n));
		}
		if (j>2)
		{
			strDatalen[k] = strBeizhu.Left(m-1).Right(n);
			k++;
		}
		m++;
	}
	CString strZhi,strZAfter;
	CString strJJ = _T("");
	int nJJN=0;
	int nDou=0;
	int Datalen = 0;
	CString str2zong=_T("");
	for(a=0;;a++)
	{
		strZhi=GetEdit(nZhi+1+a);
		strZhi+=",";
		for(b=0;b<(int)wcslen(strZhi);)
		{
			strJJ = _T("");
			if (strZhi.Left(b+1).Right(1)==",")
			{
				nDou++;
				for(int m = 0;m<wcslen(strDatalen[nDou-1]);m++)
				{
					if (strDatalen[nDou-1].Mid(m,1) == "+"||strDatalen[nDou-1].Mid(m,1) == "-")
					{
						strJJ = strDatalen[nDou-1].Mid(m,1);
						break;
					}
				}
				Datalen = _ttoi(strDatalen[nDou-1].Left(m));
				if (strJJ == "+")
				{
					nJJN = _ttoi(strDatalen[nDou-1].Mid(m+1));
					strZAfter.Format(_T("%d"),_ttoi(strZhi.Left(b))-nJJN);
					str2zong=m_tools._str10tostr2(strZAfter,Datalen)+str2zong;
				} 
				else if (strJJ == "-")
				{
					nJJN = _ttoi(strDatalen[nDou-1].Mid(m+1));
					strZAfter.Format(_T("%d"),_ttoi(strZhi.Left(b))+nJJN);
					str2zong=m_tools._str10tostr2(strZAfter,Datalen)+str2zong;
				}
				else
				{
					str2zong=m_tools._str10tostr2(strZhi.Left(b),Datalen)+str2zong;
				}
				strZhi=strZhi.Right(wcslen(strZhi)-b-1);
				b=0;
			}
			else
			{
				b++;
			}
		}
		if (nDataNub==nDou)
		{
			break;
		}
		m_ntiaoguo++;
	}
	strData16=m_tools._str2tostr16(str2zong);
	if (bForR==false)
	{
		for(a=0;a<(int)wcslen(strData16)/2;a++)
		{
			strData+=strData16.Right(2*a+2).Left(2);
		}
	}
	else
	{
		strData = strData16;
	}
	return strData;
}
			

CString CSetWriteDataDlg::GetBin(CString strBeizhu,CString strEdit)
{
	int Zijielen=0;
	bool bForR=FALSE;
	CString strData16,strData;
	if (strBeizhu.Left(1)=="f")
	{
		bForR=TRUE;
	}
	strBeizhu=strBeizhu.Right(wcslen(strBeizhu)-2);
	if (strBeizhu.Left(2).Right(1)==",")
	{
		Zijielen=_ttoi(strBeizhu.Left(1));
	}
	if (strBeizhu.Left(3).Right(1)==",")
	{
		Zijielen=_ttoi(strBeizhu.Left(2));
	}
	if (strBeizhu.Left(4).Right(1)==",")
	{
		Zijielen=_ttoi(strBeizhu.Left(3));
	}
	strData16=m_tools._str10tostr16(strEdit,Zijielen);
	if (bForR==FALSE)
	{
		for(int a=0;a<Zijielen;a++)
		{
			strData+=strData16.Right(2*a+2).Left(2);
		}
	} 
	else
	{
		strData=strData16;
	}
	return strData;
}

CString CSetWriteDataDlg::GetChar(CString strBeizhu,CString strEdit)
{
	int Zijielen=0;
	bool bForR=FALSE;
	CString strData;
	if (strBeizhu.Left(1)=="f")
	{
		bForR=TRUE;
	}
	strBeizhu=strBeizhu.Right(wcslen(strBeizhu)-2);
	if (strBeizhu.Left(2).Right(1)==",")
	{
		Zijielen=_ttoi(strBeizhu.Left(1));
	}
	if (strBeizhu.Left(3).Right(1)==",")
	{
		if (strBeizhu.Left(1) == "n")
		{
			Zijielen = wcslen(strEdit)/2;
		}
		else
		{
			Zijielen=_ttoi(strBeizhu.Left(2));
		}
		
	}
	if (strBeizhu.Left(4).Right(1)==",")
	{
		Zijielen=_ttoi(strBeizhu.Left(3));
	}
	if (bForR==FALSE)
	{
		for(int a=0;a<Zijielen;a++)
		{
			strData+=strEdit.Right(2*a+2).Left(2);
		}
	} 
	else
	{
		strData=strEdit;
	}

	return strData;
}

CString CSetWriteDataDlg::GetAscll(CString strBeizhu,CString strEdit)
{
	int Zijielen;
	INT8U * N_data;
	char d[2];
	CString strtwo,strzong;
	bool bForR=FALSE;
	CString ForR;
	
	ForR=strBeizhu.Left(1);
	if(ForR=="f")
	{
		bForR=FALSE;
	}
	if (ForR=="r")
	{
		bForR=TRUE;
	}
	strBeizhu=strBeizhu.Right(wcslen(strBeizhu)-2)+_T("!");
	if (strBeizhu.Left(2).Right(1)==";")
	{
		Zijielen=_ttoi(strBeizhu.Left(1));
	}
	if (strBeizhu.Left(3).Right(1)==";")
	{
		Zijielen=_ttoi(strBeizhu.Left(2));
	}
	if (strBeizhu.Left(4).Right(1)==";")
	{
		Zijielen=_ttoi(strBeizhu.Left(3));
	}

	N_data=(unsigned char*)strEdit.GetBuffer(wcslen(strEdit));
	
	int a=0;
	for(a=0;a<(int)wcslen(strEdit);a++)
	{
		sprintf(d, "%X",N_data[a]);
		strtwo.Format(_T("%s"),d);
		if (bForR==FALSE)
		{
			strzong+=strtwo;
		}
		else
		{
			strzong = strtwo+strzong;
		}
	}
	CString strData=_T("");
	if (bForR==FALSE)
	{
		strData=strzong;
		
		CString str0=_T("");
		for(int b=0;b<(int)(Zijielen-wcslen(strEdit));b++)
		{
			str0+="00";
		}
		strData=strData+str0;
	}
	else
	{
		for(a=0;a<(int)wcslen(strEdit);a++)
		{
			strData+=strzong.Left(2*a+2).Right(2);
		}
		CString str0=_T("");
		for(int b=0;b<(int)(Zijielen-wcslen(strEdit));b++)
		{
			str0+="00";
		}
		strData=str0+strData;
	}

	return strData;
}

CString CSetWriteDataDlg::GetTIME(CString strEdit)
{
	CString strData;
	INT8U buf[50];
	INT16U nlen=0;
	if (wcslen(strEdit)!=20&&strEdit.Mid(8,1)&&strEdit.Mid(15,1)!="-")
	{
		m_bYesOrNo=false;
		AfxMessageBox(_T("TIME格式错误"));
		return _T("");
	}
	strData = strEdit.Mid(0,8)+strEdit.Mid(9,6)+strEdit.Mid(16,4);
	m_tools._str16tobuf16(strData,buf,nlen);
	strData = m_tools._buf16tostr16(buf,nlen,false,true);
	return strData;
}
CString CSetWriteDataDlg::GetDADT(CString strEdit)
{
	CString strData;
	/*CString strF,strP;
	for(int n=0;n<(int)wcslen(strEdit);n++)
	{
	if (strEdit.Left(n+1).Right(1)=="P")
	{
	strF=strEdit.Left(n).Right(n-1);
	strP=strEdit.Right(wcslen(strEdit)-n-1);
	break;
	}
	}
	INT8U chP[2];
	INT8U chF[2];
	m_tools._strFto16(strF,chF);
	m_tools._strPto16(strP,chP);
	char chaOne[3]="";
	CString strtwo;
	strF="";
	m_tools._16Daochar(chaOne,&chF[0]);
	strtwo=chaOne;
	strF+=strtwo;
	m_tools._16Daochar(chaOne,&chF[1]);
	strtwo=chaOne;
	strF+=strtwo;
	if (strP=="0")
	{
	strP="0000";
	} 
	else if (strP == "FF00")
	{
	strP = "FF00";
	}
	else
	{
	strP="";
	m_tools._16Daochar(chaOne,&chP[0]);
	strtwo=chaOne;
	strP+=strtwo;
	m_tools._16Daochar(chaOne,&chP[1]);
	strtwo=chaOne;
	strP+=strtwo;
	}


	strData=strP+strF;*/
	return strData;
}
void CSetWriteDataDlg::OnButtonChakan() 
{
	// TODO: Add your control notification handler code here
	//ShellExecute(NULL,"open",".\\写数据格式.txt",NULL,NULL,SW_SHOWNORMAL);
}



