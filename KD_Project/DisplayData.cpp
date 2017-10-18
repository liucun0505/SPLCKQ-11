// DisplayData.cpp : implementation file
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DisplayData.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayData

CDisplayData::CDisplayData()
{
		m_nBits=0;
		m_nBit=0;
    	m_bBits=FALSE;
		m_nXiaoshu=0;
}

CDisplayData::~CDisplayData()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDisplayData message handlers
CString CDisplayData::GetGeshi(CString strXunhuan,CString strGeshi,int m,int n)
{
	int Geshulen,Cishulen=0,nnage=0;
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strGeshizong,strGeshiShiji,strGeshizuo,strGeshiyou,str;
	strGeshiShiji=strGeshi.Right(wcslen(strGeshi)-m+n+1);
	strGeshizuo=strGeshi.Left(m-n-1);
	strGeshiShiji=strGeshiShiji.Left(wcslen(strGeshiShiji)-1);
	CString strXunhuanGeishi;
	strXunhuan=strXunhuan.Right(wcslen(strXunhuan)-5)+_T(",");
	CString strBr,strBrzong;
	bool bBr= false;
	int a=1;
	for (a=1;a<(wcslen(strXunhuan)+1);a++)
	{
		if (strXunhuan.Left(a).Right(1)==",")
		{
			nnage++;
			if (nnage==1)
			{
				strXunhuanGeishi=strXunhuan.Left(a-1);
				for(int nJ=1;nJ<(wcslen(strXunhuanGeishi)+1);nJ++)
				{
					if (strXunhuanGeishi.Left(nJ).Right(1)=="-")
					{
						Geshulen=_ttoi(strXunhuanGeishi.Right(wcslen(strXunhuanGeishi)-nJ));
						break;
					}
					else
					{
						Geshulen=_ttoi(strXunhuanGeishi);
					}
				}
			}
			if (nnage==2)
			{
				if (strXunhuan.Left(a-1)=="n")
				{
					//Cishulen=pMain->m_nTimes;
				} 
				else
				{	
					if (strXunhuan.Left(1)=="n")
					{
						if (strXunhuan.Left(2).Right(1)=="b")
						{
							bBr = true;
							int nYouxiao = 0;
							CString strZhong=strXunhuan.Right(wcslen(strXunhuan)-2);
							strZhong=strZhong.Left(wcslen(strZhong)-1);
							Cishulen = 0;
							for(int nBr = 0;nBr<_ttoi(strZhong);nBr++)
							{
								if (m_RecvOldCishu[m_nOldRecvCi-nBr-1] == 1)
								{
									strBr.Format(_T("%d"),_ttoi(strZhong)-nBr);
									strBrzong=strBr+strBrzong;
								}
								Cishulen+=m_RecvOldCishu[m_nOldRecvCi-nBr-1];
							}
						}
						else
						{
							if (strXunhuan.Left(2).Right(1)=="f")
							{	
								CString strZhong=strXunhuan.Right(wcslen(strXunhuan)-2);
								strZhong=strZhong.Left(wcslen(strZhong)-1);
								Cishulen=m_RecvOldCishu[_ttoi(strZhong)];
							}
							else
							{
								CString strZhong=strXunhuan.Right(wcslen(strXunhuan)-1);
								strZhong=strZhong.Left(wcslen(strZhong)-1);
								Cishulen=m_RecvOldCishu[m_nOldRecvCi-_ttoi(strZhong)];
							}
						}

					} 
					else
					{
						Cishulen=_ttoi(strXunhuan.Left(a-1));
					}
				}

			}
			strXunhuan=strXunhuan.Right(wcslen(strXunhuan)-a);
			a=1;

		}

	}
	if (Cishulen>100)
	{
		Cishulen = 100;
	}
	nnage=0;
	for (a=1;a<(wcslen(strGeshiShiji)+1);a++)
	{
		if (strGeshiShiji.Left(a).Right(1)==";")
		{
			nnage++;
			if (nnage==Geshulen)
			{
				str=strGeshiShiji.Left(a);
				strGeshiyou=strGeshiShiji.Right(wcslen(strGeshiShiji)-a);
				break;
			}		
		}
	}

	bool bN=false;
	CString strA;
	int b=0;
	a=0;
	for(b=1;b<(int)(wcslen(str)+1);b++)
	{
		if (str.Left(b).Right(1)=="S")
		{
			bN=true;
			m_nstrN=_ttoi(str.Left(b+1).Right(1));
			if (m_nstrN>1&&m_nstrN<9)
			{
				a+=m_nstrN-1;
			}
			break;
		}
	}
	int nBr = 0;
	if (bBr)
	{
		for (;a<Cishulen;a++)
		{	
			strA = strBrzong.Mid(nBr,1);
			nBr++;
			if (bN==true)
			{	
				if (m_nstrN>1&&m_nstrN<9)
				{
					strGeshizong+=(str.Left(b-1)+strA+str.Right(wcslen(str)-b-1));
				}
				else
				{
					strGeshizong+=(str.Left(b-1)+strA+str.Right(wcslen(str)-b));
				}

			} 
			else
			{
				strGeshizong+=str;
			}	
		}
	} 
	else
	{
		for (;a<Cishulen;a++)
		{	
			strA.Format(_T("%d"),a+1);
			if (bN==true)
			{	
				if (m_nstrN>1&&m_nstrN<9)
				{
					strGeshizong+=(str.Left(b-1)+strA+str.Right(wcslen(str)-b-1));
				}
				else
				{
					strGeshizong+=(str.Left(b-1)+strA+str.Right(wcslen(str)-b));
				}

			} 
			else
			{
				strGeshizong+=str;
			}	
		}
	}

	strGeshizong=strGeshizuo+strGeshizong+strGeshiyou+_T("!");
	return strGeshizong;
}
CString CDisplayData::GetBeizhu(CString strXunhuan,CString strBeizhu)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int Geshulen,Cishulen=0,nnage=0;
	CString strBeizhuzong,strBeizhuyou,str;
	strBeizhu=strBeizhu.Right(wcslen(strBeizhu)-wcslen(strXunhuan)-1);
	strXunhuan=strXunhuan.Right(wcslen(strXunhuan)-5)+_T(",");
	CString strXunhuanBeizhu;
	int a=1;
	for (a=1;a<(wcslen(strXunhuan)+1);a++)
	{
		if (strXunhuan.Left(a).Right(1)==",")
		{

			nnage++;
			if (nnage==1)
			{
				strXunhuanBeizhu=strXunhuan.Left(a-1);
				for(int nJ=1;nJ<(wcslen(strXunhuanBeizhu)+1);nJ++)
				{
					if (strXunhuanBeizhu.Left(nJ).Right(1)=="-")
					{

						Geshulen=_ttoi(strXunhuanBeizhu.Left(nJ-1));
						break;
					}
					else
					{
						Geshulen=_ttoi(strXunhuanBeizhu);
					}
				}
			}
			if (nnage==2)
			{
				if (strXunhuan.Left(a-1)=="n")
				{
					//Cishulen=pMain->m_nTimes;
				} 
				else
				{
					if (strXunhuan.Left(1)=="n")
					{
						if (strXunhuan.Left(2).Right(1)=="b")
						{
							int nYouxiao = 0;
							CString strZhong=strXunhuan.Right(wcslen(strXunhuan)-2);
							strZhong=strZhong.Left(wcslen(strZhong)-1);
							Cishulen = 0;
							for(int nBr = 0;nBr<_ttoi(strZhong);nBr++)
							{
								Cishulen+=m_RecvOldCishu[m_nOldRecvCi-nBr-1];
							}
						}
						else
						{
							if (strXunhuan.Left(2).Right(1)=="f")
							{	
								CString strZhong=strXunhuan.Right(wcslen(strXunhuan)-2);
								strZhong=strZhong.Left(wcslen(strZhong)-1);
								Cishulen=m_RecvOldCishu[_ttoi(strZhong)];
							}
							else
							{
								CString strZhong=strXunhuan.Right(wcslen(strXunhuan)-1);
								strZhong=strZhong.Left(wcslen(strZhong)-1);
								Cishulen=m_RecvOldCishu[m_nOldRecvCi-_ttoi(strZhong)];
							}
						}
					} 
					else
					{
						Cishulen=_ttoi(strXunhuan.Left(a-1));
					}
				}
			}
			strXunhuan=strXunhuan.Right(wcslen(strXunhuan)-a);
			a=1;
		}

	}
	if (Cishulen>100)
	{
		Cishulen = 100;
	}
	nnage=0;
	for (a=1;a<(wcslen(strBeizhu)+1);a++)
	{
		if (strBeizhu.Left(a).Right(1)==";")
		{
			nnage++;
			if (nnage==Geshulen)
			{
				str=strBeizhu.Left(a);
				strBeizhuyou=strBeizhu.Right(wcslen(strBeizhu)-a);
				break;
			}		
		}
	}

	a=0;
	if (m_nstrN>1&&m_nstrN<9)
	{
		a+=m_nstrN-1;
	}
	for (;a<Cishulen;a++)
	{	
		strBeizhuzong+=str;
	}
	strBeizhuzong=strBeizhuzong+strBeizhuyou;
	return strBeizhuzong;
}
CString CDisplayData::DisplayShowMessage(CString strCode , CString strShowMsg , INT8U * databuf , INT16U datalen)
{
	int n=0,m=1,j=0;
	int a;
	int afor;
	int nGeBaifen=0,nGeFen=0;
	int lenMingcheng;
	bool bhuiche=FALSE;
	CString strData,strDatazong;
	CString strMessageData = _T("--------------------------------------------------------------------------------\r\n");
	CString strShuxingName;
	CString strName;
	CString strGeshi,strBeizhu;
	CString strShowDisplayData;

	strGeshi = strShowMsg;
	strBeizhu = strCode; 
	//CDisplayData m_dispData;
	m_nZondDataLen = 0;
	m_njiexi=0;


	strGeshi = strGeshi+_T("!");
	m_nOldRecvCi = 1;
	while((strGeshi.Left(m).Right(1)!="!")&&(m!=500))
	{	
		j++;
		n=0;
		bhuiche=FALSE;
BEGIN:
		while((strGeshi.Left(m).Right(1)!=";")&&(strGeshi.Left(m).Right(1)!="!")&&(n!=500))
		{
			n++;
			m++;
		}
		strName=strGeshi.Mid(m-1-n,n);
		nGeBaifen=0;
		lenMingcheng=0;
		for (afor=1;afor<(wcslen(strName)+1);afor++)
		{
			if (strName.Left(afor).Right(1)=="%")
			{
				nGeBaifen++;
				if (nGeBaifen==1)
				{
					lenMingcheng=afor-1;
				}
			}
			if (strName.Left(afor).Right(1)=="&")
			{
				bhuiche=TRUE;
			}
		}
		CString strMingcheng=strName.Left(lenMingcheng);

		strDatazong="";

		nGeFen=0;
		for(afor=1;afor<(wcslen(strBeizhu)+1);afor++)
		{
			if (strBeizhu.Left(afor).Right(1)==";")
			{

				strShuxingName=strBeizhu.Left(afor-1);

				if (strShuxingName.Left(5)!="ignor") 
				{
					nGeFen++;
				}
				if (strShuxingName.Left(6)=="loops,")
				{
					CString strYiban,strBeizhuG;
					strYiban=strGeshi.Right(wcslen(strGeshi)-m+n+1);
					strYiban=strYiban.Left(wcslen(strYiban)-1);
					strGeshi=strGeshi.Left(wcslen(strGeshi)-1);
					strBeizhu=strBeizhu.Right(wcslen(strBeizhu)-9);
					strBeizhuG=strBeizhu;
					int Cishulen=m_RecvOldCishu[m_nOldRecvCi-_ttoi(strShuxingName.Left(8).Right(1))];
					for (a=1;a<Cishulen;a++)
					{	
						strGeshi+=strYiban;
						strBeizhu+=strBeizhuG;
					}
					strGeshi+="!";
					goto BEGIN;
				}
				if ((strShuxingName.Left(4)=="loop")&&(strShuxingName.Left(5).Right(1)!="s"))
				{
					strGeshi=GetGeshi(strShuxingName,strGeshi,m,n);
					strBeizhu=GetBeizhu(strShuxingName,strBeizhu);
					goto BEGIN;
				}
				m_nXiaoshu=0;
				strData=DisplayJiexiData(strShuxingName,databuf,m_RecvOldCishu,m_nOldRecvCi);
				m_RecvOldCishu[m_nOldRecvCi]=_ttoi(strData);
				m_nOldRecvCi+=1;
				if (m_nXiaoshu!=0)
				{
					strData=strData.Left(wcslen(strData)-m_nXiaoshu)+"."+strData.Right(m_nXiaoshu);
				}
				strDatazong+=strData+_T(" ");

				if (m_bBits==FALSE)
				{
					strBeizhu=strBeizhu.Right(wcslen(strBeizhu)-afor);
				}			
				afor=0;
				if (nGeFen==nGeBaifen) break;
			}
		}
		for(int nMing=0;nMing<wcslen(strMingcheng);nMing++)
		{
			if (strMingcheng.Left(nMing+1).Right(1)=="&")
			{
				strMingcheng=strMingcheng.Left(nMing)+"\r\n>>>>"+strMingcheng.Right(wcslen(strMingcheng)-nMing-1);
			}
		}
		if (bhuiche==FALSE)
		{
			strMessageData += _T(">>>>") + strMingcheng+strDatazong+_T(";  ");
		} 
		else
		{
			strMessageData += _T(">>>>") + strMingcheng+strDatazong+ _T("\r\n");
		}
		if (strMingcheng!="备用:")
		{
			//m_strEditNeirong += str;
			//m_editXianshi.ReplaceSel(str);
		}
		m++;	
		if(m_njiexi>datalen) break;
	}
	strMessageData += _T("--------------------------------------------------------------------------------\r\n");
	return strMessageData;
}

CString CDisplayData::DisplayJiexiData(CString str,INT8U *DstBuf,int * RecvCishu,int nCishu)
{
	m_nRecvCi = nCishu;
	for(int n = 0; n<m_nRecvCi;n++)
	{
		m_RecvCishu[n] = RecvCishu[n];
	}
	CString strData = _T("");
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int len;
	if (str.Left(3)=="bin"&&str.Right(2)!="_n") 
	{
		strData=DisplayDatabin(str,DstBuf);
	}
	if (str.Left(3)=="bin_n")  
	{
		strData=DisplayDatabin_n(str,DstBuf);
	}
	if (str.Left(4)=="bits")
	{
		strData=DisplayDatabits(str,DstBuf);
	}
	if ((str.Left(3)=="bit")&&(str.Left(4).Right(1)!="s"))
	{
		strData=DisplayDatabit(str,DstBuf);
	}
	if (str.Left(5)=="ignor")
	{
		if (wcslen(str)==7)
		{
			len=_ttoi(str.Left(7).Right(1));
			m_nZondDataLen+=len;
			m_njiexi+=len;
		}
		if (wcslen(str)==8)
		{
			len=_ttoi(str.Left(8).Right(2));
			m_nZondDataLen+=len;
			m_njiexi+=len;
		}
		if (wcslen(str)==9)
		{
			len=_ttoi(str.Left(9).Right(3));
			m_nZondDataLen+=len;
			m_njiexi+=len;
		}
	}
	if (str.Left(5)=="ascii")
	{
		strData=DisplayDataascll(str,DstBuf);
	}
	if (str.Left(4)=="char")
	{
		strData=DisplayDatachar(str,DstBuf);
	}
	/*if (str.Left(4)=="Td_h")
	{
		m_nZondDataLen+=2;
		strData=DisplayDataTdh(DstBuf);
	}
	if (str.Left(4)=="Td_c")
	{
		m_nZondDataLen+=7;
		strData=DisplayDataTdc(DstBuf);
	}*/
	if (str.Left(4)=="Td_m")
	{
		str="A21";
	}
	if (str.Left(4)=="Td_d")
	{
		str="A20";
	}
	/*if (str.Left(4)=="DADT")
	{
		m_nZondDataLen+=4;
		strData=DisplayDataDADT(DstBuf);
	}
	if (str.Left(4)=="TIME")
	{
		m_nZondDataLen+=9;
		strData=DisplayDataTIME(DstBuf);
	}*/
	//switch(_ttoi(str.Left(3).Right(2)))
	//{
	//case 1:
	//	m_nZondDataLen+=6;
	//	//pMain->m_strNoew="A1";
	//	strData=DisplayDataA01(DstBuf);
	//	break;
	//case 2:
	//	m_nZondDataLen+=2;
	//	//pMain->m_strNoew="A2";
	//	strData=DisplayDataA02(DstBuf);
	//	break;
	//case 3:
	//	m_nZondDataLen+=4;
	//	//pMain->m_strNoew="A3";
	//	strData=DisplayDataA03(DstBuf);
	//	break;
	//case 4:
	//	m_nZondDataLen+=1;
	//	//pMain->m_strNoew="A4";
	//	strData=DisplayDataA04(DstBuf);
	//	break;
	//case 5:
	//	m_nZondDataLen+=2;
	//	//pMain->m_strNoew="A5";
	//	strData=DisplayDataA05(DstBuf);
	//	break;
	//case 6:
	//	m_nZondDataLen+=2;
	//	//pMain->m_strNoew="A6";
	//	strData=DisplayDataA06(DstBuf);
	//	break;
	//case 7:
	//	m_nZondDataLen+=2;
	//	//pMain->m_strNoew="A7";
	//	strData=DisplayDataA07(DstBuf);
	//	break;
	//case 8:
	//	m_nZondDataLen+=2;
	//	//pMain->m_strNoew="A8";
	//	strData=DisplayDataA08(DstBuf);
	//	break;
	//case 9:
	//	m_nZondDataLen+=3;
	//	//pMain->m_strNoew="A9";
	//	strData=DisplayDataA09(DstBuf);
	//	break;
	//case 10:
	//	m_nZondDataLen+=3;
	//	//pMain->m_strNoew="A10";
	//	strData=DisplayDataA10(DstBuf);
	//	break;
	//case 11:
	//	m_nZondDataLen+=4;
	//	//pMain->m_strNoew="A11";
	//	strData=DisplayDataA11(DstBuf);
	//	break;
	//case 12:
	//	m_nZondDataLen+=6;
	//	//pMain->m_strNoew="A12";
	//	strData=DisplayDataA12(DstBuf);
	//	break;
	//case 13:
	//	m_nZondDataLen+=4;
	//	//pMain->m_strNoew="A13";
	//	strData=DisplayDataA13(DstBuf);
	//	break;
	//case 14:
	//	m_nZondDataLen+=5;
	//	//pMain->m_strNoew="A14";
	//	strData=DisplayDataA14(DstBuf);
	//	break;
	//case 15:
	//	m_nZondDataLen+=5;
	//	//pMain->m_strNoew="A15";
	//	strData=DisplayDataA15(DstBuf);
	//	break;
	//case 16:
	//	m_nZondDataLen+=4;
	//	pMain->m_strNoew="A16";
	//	strData=DisplayDataA16(DstBuf);
	//	break;
	//case 17:
	//	m_nZondDataLen+=4;
	//	pMain->m_strNoew="A17";
	//	strData=DisplayDataA17(DstBuf);
	//	break;
	//case 18:
	//	m_nZondDataLen+=3;
	//	pMain->m_strNoew="A18";
	//	strData=DisplayDataA18(DstBuf);
	//	break;
	//case 19:
	//	m_nZondDataLen+=2;
	//	pMain->m_strNoew="A19";
	//	strData=DisplayDataA19(DstBuf);
	//	break;
	//case 20:
	//	m_nZondDataLen+=3;
	//	pMain->m_strNoew="A20";
	//	strData=DisplayDataA20(DstBuf);
	//	break;
	//case 21:
	//	m_nZondDataLen+=2;
	//	pMain->m_strNoew="A21";
	//	strData=DisplayDataA21(DstBuf);
	//	break;
	//case 22:
	//	m_nZondDataLen+=1;
	//	pMain->m_strNoew="A22";
	//	strData=DisplayDataA22(DstBuf);
	//	break;
	//case 23:
	//	switch(pMain->m_nProtocolType)
	//	{
	//	case GW1376_12013:
	//	case NEIMENGPTY:
	//	case JILINPTY:
	//		m_nZondDataLen+=3;
	//		break;
	//	case GUANGXIPTY:
	//		m_nZondDataLen+=2;
	//		break;
	//	default:
	//		m_nZondDataLen+=3;
	//		break;
	//	}
	//	pMain->m_strNoew="A23";
	//	strData=DisplayDataA23(DstBuf);
	//	break;
	//case 24:
	//	switch(pMain->m_nProtocolType)
	//	{
	//	case GW1376_12013:
	//	case NEIMENGPTY:
	//	case JILINPTY:
	//		m_nZondDataLen+=2;
	//		break;
	//	case GUANGXIPTY:
	//		m_nZondDataLen+=7;
	//		break;
	//	default:
	//		m_nZondDataLen+=2;
	//		break;
	//	}
	//	pMain->m_strNoew="A24";
	//	strData=DisplayDataA24(DstBuf);
	//	break;
	//case 25:
	//	m_nZondDataLen+=3;
	//	pMain->m_strNoew="A25";
	//	strData=DisplayDataA25(DstBuf);
	//	break;
	//case 26:
	//	m_nZondDataLen+=2;
	//	pMain->m_strNoew="A26";
	//	strData=DisplayDataA26(DstBuf);
	//	break;
	//case 27:
	//	switch(pMain->m_nProtocolType)
	//	{
	//	case GW1376_12013:
	//	case NEIMENGPTY:
	//	case JILINPTY:
	//		m_nZondDataLen+=4;
	//		break;
	//	case GUANGXIPTY:
	//		m_nZondDataLen+=1;
	//		break;
	//	default:
	//		m_nZondDataLen+=4;
	//		break;
	//	}
	//	pMain->m_strNoew="A27";
	//	strData=DisplayDataA27(DstBuf);
	//	break;
	//case 28:
	//	switch(pMain->m_nProtocolType)
	//	{
	//	case GW1376_12013:
	//	case NEIMENGPTY:
	//	case JILINPTY:
	//		m_nZondDataLen+=5;
	//		break;
	//	case GUANGXIPTY:
	//		m_nZondDataLen+=1;
	//		break;
	//	default:
	//		m_nZondDataLen+=5;
	//		break;
	//	}
	//	pMain->m_strNoew="A28";
	//	strData=DisplayDataA28(DstBuf);
	//	break;
	//case 29:
	//	m_nZondDataLen+=1;
	//	pMain->m_strNoew="A29";
	//	strData=DisplayDataA29(DstBuf);
	//	break;
	//case 30:
	//	m_nZondDataLen+=1;
	//	pMain->m_strNoew="A30";
	//	strData=DisplayDataA30(DstBuf);
	//	break;
	//case 31:
	//	m_nZondDataLen+=2;
	//	pMain->m_strNoew="A31";
	//	strData=DisplayDataA31(DstBuf);
	//	break;
	//case 32:
	//	m_nZondDataLen+=7;
	//	pMain->m_strNoew="A32";
	//	strData=DisplayDataA32(DstBuf);
	//	break;
	//case 33:
	//	m_nZondDataLen+=6;
	//	pMain->m_strNoew="A33";
	//	strData=DisplayDataA33(DstBuf);
	//	break;
	//case 35:
	//	m_nZondDataLen+=3;
	//	pMain->m_strNoew="A35";
	//	strData=DisplayDataA35(DstBuf);
	//	break;
	//case 36:
	//	m_nZondDataLen+=8;
	//	pMain->m_strNoew="A36";
	//	strData=DisplayDataA36(DstBuf);
	//	break;
	//case 37:
	//	m_nZondDataLen+=8;
	//	pMain->m_strNoew="A37";
	//	strData=DisplayDataA37(DstBuf);
	//	break;
	//case 40:
	//	switch(pMain->m_nProtocolType)
	//	{
	//	case GW1376_12013:
	//	case NEIMENGPTY:
	//	case JILINPTY:
	//		break;
	//	case GUANGXIPTY:
	//		m_nZondDataLen+=3;
	//		break;
	//	default:
	//		break;
	//	}
	//	pMain->m_strNoew="A40";
	//	strData=DisplayDataA40(DstBuf);
	//	break;
	//case 99:
	//	m_nZondDataLen+=2;
	//	pMain->m_strNoew="A99";
	//	strData=DisplayDataA99(DstBuf);
	//	break;
	//}
	return strData;
}

CString CDisplayData::Bin(INT8U *buf,int nJiexi,int zijielen,bool ForR)
{
	CString str;
	char chaOnes[3]="";
	int n;
	CString str2,strzong;
	if (ForR==TRUE)
	{
		for(n=0;n<zijielen;n++)
		{
			m_tools._16Daochar(chaOnes,&buf[nJiexi+zijielen-n-1]);
			str2=chaOnes;
			strzong+=str2;
		}
	} 
	else
	{
		for(n=0;n<zijielen;n++)
		{
			m_tools._16Daochar(chaOnes,&buf[nJiexi+n]);
			str2=chaOnes;
			strzong+=str2;
		}
	}

	CString str10=m_tools._str16tostr10(strzong);
	return str10;
}
CString CDisplayData::DisplayDatabin_n(CString strShuxingname,INT8U *DstBuf)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nDataNub=0;
	int n=0;
	int j=0;
	int k=0;
	int m=1;
	CString strJIEGUO,str;
	CString strJJN;
	bool bForR=FALSE;
	int len;
	CString strShuxingNub,ForR;
	strShuxingNub=strShuxingname.Right(wcslen(strShuxingname)-6)+_T("!");
	ForR=strShuxingname.Left(5).Right(1);
	if(ForR=="f")
	{
		bForR=FALSE;
	}
	if (ForR=="r")
	{
		bForR=TRUE;
	}
	while((strShuxingNub.Left(m).Right(1)!="!")&&(m!=500))
	{
		j++;
		n=0;
		while((strShuxingNub.Left(m).Right(1)!=",")&&(strShuxingNub.Left(m).Right(1)!="!")&&(n!=500))
		{
			m++;
			n++;
		}
		if (j==1)
		{
			len=_ttoi(strShuxingNub.Left(m-1).Right(n));
			m_nZondDataLen+=len;
		}
		if (j==2)
		{
			m_nXiaoshu=_ttoi(strShuxingNub.Left(m-1).Right(n));
		}
		if (j==3)
		{
			strJJN=strShuxingNub.Left(m-1).Right(n);
		}
		m++;
	}
	strJIEGUO=Bin(DstBuf,m_njiexi,len,bForR);
	if (strJJN.Left(1) == "+")
	{
		strJIEGUO.Format(_T("%d"),_ttoi(strJIEGUO)+_ttoi(strJJN.Mid(1)));
	} 
	else if(strJJN.Left(1) == "-")
	{
		if (_ttoi(strJIEGUO)!=0)
		{
			strJIEGUO.Format(_T("%d"),_ttoi(strJIEGUO)-_ttoi(strJJN.Mid(1)));
		}
	}
	else
	{
		strJIEGUO.Format(_T("%d"),_ttoi(strJIEGUO)+_ttoi(strJJN.Mid(1)));
	}
	

/*	CString str0;
	for(int a=0;a<(int)(2*len-strlen(strJIEGUO));a++)
	{
		str0+="0";
	}
	strJIEGUO=str0+strJIEGUO;
*/
	m_njiexi+=len;
	//pMain->m_strNoew="bin";
	return strJIEGUO;
}

CString CDisplayData::DisplayDatabin(CString strShuxingname,INT8U *DstBuf)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nDataNub=0;
	int n=0;
	int j=0;
	int k=0;
	int m=1;
	CString strJIEGUO,str;
	bool bForR=FALSE;
	int len;
	CString strShuxingNub,ForR;
	strShuxingNub=strShuxingname.Right(wcslen(strShuxingname)-6)+_T("!");
	ForR=strShuxingname.Left(5).Right(1);
	if(ForR=="f")
	{
		bForR=FALSE;
	}
	if (ForR=="r")
	{
		bForR=TRUE;
	}
	while((strShuxingNub.Left(m).Right(1)!="!")&&(m!=500))
	{
		j++;
		n=0;
		while((strShuxingNub.Left(m).Right(1)!=",")&&(strShuxingNub.Left(m).Right(1)!="!")&&(n!=500))
		{
			m++;
			n++;
		}
		if (j==1)
		{
			len=_ttoi(strShuxingNub.Left(m-1).Right(n));
			m_nZondDataLen+=len;
		}
		if (j==2)
		{
			m_nXiaoshu=_ttoi(strShuxingNub.Left(m-1).Right(n));
		}
		m++;
	}
	strJIEGUO=Bin(DstBuf,m_njiexi,len,bForR);

/*	CString str0;
	for(int a=0;a<(int)(2*len-strlen(strJIEGUO));a++)
	{
		str0+="0";
	}
	strJIEGUO=str0+strJIEGUO;
*/
	m_njiexi+=len;
	//pMain->m_strNoew="bin";
	return strJIEGUO;
}
void CDisplayData::Bit(INT8U *buf,int nJiexi,int zijielen,int mshujuNub,int *fanhuidata,bool ForR)
{
	CString str;
	char chaOnes[3]="";
	int n;

	CString str2,strzong,str2to10,str10;

	int b=0;
	CString str2zong;
	if (ForR==TRUE)
	{
		for(n=0;n<zijielen;n++)
		{
			m_tools._16Daochar(chaOnes,&buf[nJiexi+zijielen-n-1]);
			str2=chaOnes;
			strzong+=str2;
		}
		str2zong=m_tools._str16tostr2(strzong);
		for(n=0;n<mshujuNub;n++)
		{
			str2to10=str2zong.Right(n+1).Left(1);
			fanhuidata[n]=_ttoi(m_tools._str2tostr10(str2to10));
		}
	} 
	else
	{
		for(n=0;n<zijielen;n++)
		{
			m_tools._16Daochar(chaOnes,&buf[nJiexi+n]);
			str2=chaOnes;

			str2zong=m_tools._str16tostr2(str2);
			for(int a=0;a<8;a++,b++)
			{
				str2to10=str2zong.Right(a+1).Left(1);
				fanhuidata[b]=_ttoi(m_tools._str2tostr10(str2to10));
			}
		}
	}
}
CString CDisplayData::DisplayDatabit(CString strShuxingname,INT8U *DstBuf)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nData[10000];
	int len=0;
	int nDataNub=0;
	int n=0;
	int j=0;
	int k=0;
	int m=1;
	bool bForR=FALSE;
	CString ForR;
	CString strShuxingNub,strchild,strData,str;
	strShuxingNub=strShuxingname.Right(wcslen(strShuxingname)-6)+_T("!");

	ForR=strShuxingname.Left(5).Right(1);
	if(ForR=="f")
	{
		bForR=FALSE;
	}
	if (ForR=="r")
	{
		bForR=TRUE;
	}

	while((strShuxingNub.Left(m).Right(1)!="!")&&(m!=500))
	{
		j++;
		n=0;
		while((strShuxingNub.Left(m).Right(1)!=",")&&(strShuxingNub.Left(m).Right(1)!="!")&&(n!=500))
		{
			m++;
			n++;
		}
		if (j==1)
		{
			len=_ttoi(strShuxingNub.Left(m-1).Right(n));
			if (m_bBits==FALSE)
			{
				m_nZondDataLen+=len;
			}	
		}
		if (j==2)
		{
			nDataNub=_ttoi(strShuxingNub.Left(m-1).Right(n));
		}
		m++;
	}
	Bit(DstBuf,m_njiexi,len,nDataNub,nData,bForR);
	m_bBits=TRUE;

	strData.Format(_T("%d"),nData[m_nBit]);

	m_nBit+=1;

	if ((m_nBit)==nDataNub)
	{
		m_nBit=0;
		m_bBits=FALSE;
		m_njiexi+=len;
	}
	//pMain->m_strNoew="bit";
	return strData;
}
void CDisplayData::Bits(INT8U *buf,int nJiexi,int zijielen,int mshujuNub,CString * strshujulen,int *fanhuidata,bool ForR)
{
	CString str;
	char chaOnes[3]="";
	int n;

	CString str2,strzong,str2to10,str10;

	if (ForR==TRUE)
	{
		for(n=0;n<zijielen;n++)
		{
			m_tools._16Daochar(chaOnes,&buf[nJiexi+zijielen-n-1]);
			str2=chaOnes;
			strzong+=str2;
		}
	} 
	else
	{
		for(n=0;n<zijielen;n++)
		{
			m_tools._16Daochar(chaOnes,&buf[nJiexi+n]);
			str2=chaOnes;
			strzong+=str2;
		}
	}

	CString str2zong=m_tools._str16tostr2(strzong);
	int shujulen = 0;
	int nJJN = 0;
	CString strFH = _T("");
	for(n=0;n<mshujuNub;n++)
	{
		strFH = "";
		int m = 0;
		for(m = 0;m<wcslen(strshujulen[n]);m++)
		{
			if (strshujulen[n].Mid(m,1) == "+"||strshujulen[n].Mid(m,1) == "-")
			{
				strFH = strshujulen[n].Mid(m,1);
				break;
			}
		}
		shujulen = _ttoi(strshujulen[n].Left(m));
		if(strFH == "+")
		{
			nJJN = _ttoi(strshujulen[n].Mid(m+1));
			str2to10=str2zong.Right(shujulen);
			str2zong=str2zong.Left(wcslen(str2zong)-shujulen);
			fanhuidata[n]=_ttoi(m_tools._str2tostr10(str2to10))+nJJN;
		}else if(strFH == "-")
		{
			nJJN = _ttoi(strshujulen[n].Mid(m+1));
			str2to10=str2zong.Right(shujulen);
			str2zong=str2zong.Left(wcslen(str2zong)-shujulen);
			fanhuidata[n]=_ttoi(m_tools._str2tostr10(str2to10))-nJJN;
		}
		else
		{
			str2to10=str2zong.Right(shujulen);
			str2zong=str2zong.Left(wcslen(str2zong)-shujulen);
			fanhuidata[n]=_ttoi(m_tools._str2tostr10(str2to10));
		}

	}

}
CString CDisplayData::DisplayDatabits(CString strShuxingname,INT8U *DstBuf)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int nbits=0;
	int nData[100];
	int len=0;
	int nDataNub=0;
	CString strDatalen[50];
	int n=0;
	int j=0;
	int k=0;
	int m=1;
	bool bForR=FALSE;
	CString ForR;
	CString strShuxingNub,strchild,strData,str;
	strShuxingNub=strShuxingname.Right(wcslen(strShuxingname)-7)+_T("!");

	ForR=strShuxingname.Left(6).Right(1);
	if(ForR=="f")
	{
		bForR=FALSE;
	}
	if (ForR=="r")
	{
		bForR=TRUE;
	}

	while((strShuxingNub.Left(m).Right(1)!="!")&&(m!=500))
	{
		j++;
		n=0;
		while((strShuxingNub.Left(m).Right(1)!=",")&&(strShuxingNub.Left(m).Right(1)!="!")&&(n!=500))
		{
			m++;
			n++;
		}
		if (j==1)
		{
			len=_ttoi(strShuxingNub.Left(m-1).Right(n));
			
		}
		if (j==2)
		{
			nDataNub=_ttoi(strShuxingNub.Left(m-1).Right(n));
		}
		if (j>2)
		{
			strDatalen[k] = strShuxingNub.Left(m-1).Right(n);
	//		Datalen[k]=atoi(strShuxingNub.Left(m-1).Right(n));
			k++;
		}
		m++;
	}

	Bits(DstBuf,m_njiexi,len,nDataNub,strDatalen,nData,bForR);
//	m_Cdtl2007.Bits(DstBuf,m_njiexi,len,nDataNub,Datalen,nData,bForR);
	
	
	if (m_bBits==FALSE)
	{
		m_nZondDataLen+=len;
	}
	m_bBits=TRUE;

	

	strData.Format(_T("%d"),nData[m_nBits]);
	m_nBits+=1;
	if ((m_nBits)==nDataNub)
	{
		m_nBits=0;
		m_bBits=FALSE;
		m_njiexi+=len;
	}

	

	//pMain->m_strNoew="bits";
	return strData;
	
}

CString CDisplayData::DisplayDataascll(CString strShuxingname,INT8U *DstBuf)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strJIEGUO,str;
	CString strLen;
	bool bForR=FALSE;
	int len ,nNumb = 0;
	char chaOne[3]="";
	CString ForR;
	CString strlist[5];
	strShuxingname += _T(",");
	m_tools.Split(strShuxingname , _T(",") , strlist ,nNumb);

	if(strlist[2].Mid(0,1) == "n")
	{
		if (strlist[2].Mid(1,1)=="f")
		{	
			len=m_RecvCishu[_ttoi(strlist[2].Mid(2))];
		}
		else
		{
			len=m_RecvCishu[m_nRecvCi-_ttoi(strlist[2].Mid(1))];
		}
	}
	else
	{
		len = _ttoi(strlist[2]);
	}
	m_nZondDataLen+=len;
	ForR=strShuxingname.Left(7).Right(1);
	if(strlist[1]=="f")
	{
		bForR=FALSE;
	}
	else
	{
		bForR=TRUE;
	}
	
	strJIEGUO=m_tools.HextoAscll(DstBuf,m_njiexi,len,bForR);
	m_njiexi+=len;

	//pMain->m_strNoew="ascll";
	return strJIEGUO;

}
CString CDisplayData::Char(INT8U *buf,int nJiexi,int zijielen,bool ForR)
{
	CString str;
	int n;
	CString str2,strzong;
	char chaOne[3]="";
	if (ForR==TRUE)
	{
		for(n=0;n<zijielen;n++)
		{
			//			str2=buf[nJiexi+zijielen-n-1];
			m_tools._16Daochar(chaOne,&buf[nJiexi+zijielen-n-1]);
			str2=chaOne;
			strzong+=str2;
		}
	} 
	else
	{
		for(n=0;n<zijielen;n++)
		{
			m_tools._16Daochar(chaOne,&buf[nJiexi+n]);
			str2=chaOne;
			strzong+=str2;
		}
	}
	return strzong;
}
CString CDisplayData::DisplayDatachar(CString strShuxingname,INT8U *DstBuf)
{
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	int n=0;
	int j=0;
	int k=0;
	int m=1;
	CString strJIEGUO,str;
	bool bForR=FALSE;
	int len;
	CString strShuxingNub,ForR;
	strShuxingNub=strShuxingname.Right(wcslen(strShuxingname)-7)+_T("!");
	
	while((strShuxingNub.Left(m).Right(1)!="!")&&(m!=500))
	{
		j++;
		n=0;
		while((strShuxingNub.Left(m).Right(1)!=",")&&(strShuxingNub.Left(m).Right(1)!="!")&&(n!=500))
		{
			m++;
			n++;
		}
		if (j==1)
		{
			CString strXunhuan,strNumb;
			CString strTeshu = strShuxingNub.Left(m-1).Right(n);
			if (strTeshu.Left(1) == "n")
			{
				bool charN_N = false;
				for (int a = 0;a<wcslen(strTeshu);a++)
				{
					if (strTeshu.Mid(a,1) == "-")
					{
						strXunhuan = strTeshu.Left(a);
						strNumb = strTeshu.Mid(a+1);
						charN_N = true;
						break;
					}
				}
				if(charN_N)
				{
					if (strXunhuan.Left(2).Right(1)=="f")
					{	
						CString strZhong=strXunhuan.Mid(2);
						len=m_RecvCishu[_ttoi(strZhong)]-_ttoi(strNumb);
					}
					else
					{
						CString strZhong=strXunhuan.Mid(1);
						len=m_RecvCishu[m_nRecvCi-_ttoi(strZhong)]-_ttoi(strNumb);
					}
				}
				else
				{
					if (strTeshu.Left(2).Right(1)=="f")
					{	
						CString strZhong=strTeshu.Mid(2);
						len=m_RecvCishu[_ttoi(strZhong)];
					}
					else
					{
						CString strZhong=strTeshu.Mid(1);
						len=m_RecvCishu[m_nRecvCi-_ttoi(strZhong)];
					}
				}
				
				
			} 
			else
			{
				len=_ttoi(strTeshu);
			}
			m_nZondDataLen+=len;
		}
		if (j==2)
		{
			m_nXiaoshu=_ttoi(strShuxingNub.Left(m-1).Right(n));
		}
		m++;
	}
	ForR=strShuxingname.Left(6).Right(1);
	if(ForR=="f")
	{
		bForR=FALSE;
	}
	if (ForR=="r")
	{
		bForR=TRUE;
	}
	
	strJIEGUO=Char(DstBuf,m_njiexi,len,bForR);
	m_njiexi+=len;
//	AfxMessageBox(strJIEGUO);
	//pMain->m_strNoew="char";
	return strJIEGUO;
}


//CString CDisplayData::DisplayDataA01(INT8U *DstBuf)
//{
//	CString strJIEGUO,str8,strss,strmm,strhh,strDD,strMM,strYY,strXingqi,strMMandXingqi;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strss=chaOne;
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strmm=chaOne;
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strhh=chaOne;
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strDD=chaOne;
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strMMandXingqi=chaOne;//这个字节0123为月的个位,4为月的十位,567为星期(0无效,1-7为星期一到星期日)
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strYY=chaOne;
//
//	str8=m_Cdtl2007._str16tostr2(strMMandXingqi);
//
//
//	if (str8.Left(4).Right(1)=="0")
//	{
//		strMM=strMMandXingqi.Right(1);
//	} 
//	else
//	{
//		strMM=str8.Left(4).Right(1)+strMMandXingqi.Right(1);
//	}
//	strXingqi=m_Cdtl2007._str2tostr10(str8.Left(3));
//	switch(atoi(strXingqi))
//	{
//	case 0:
//		strXingqi="";
//		break;
//	case 1:
//		strXingqi="星期一";
//		break;
//	case 2:
//		strXingqi="星期二";
//		break;
//	case 3:
//		strXingqi="星期三";
//		break;
//	case 4:
//		strXingqi="星期四";
//		break;
//	case 5:
//		strXingqi="星期五";
//		break;
//	case 6:
//		strXingqi="星期六";
//		break;
//	case 7:
//		strXingqi="星期日";
//		break;
//	}
//	strJIEGUO="20"+strYY+"-"+strMM+"-"+strDD+"  "+strhh+":"+strmm+":"+strss+"  "+strXingqi;
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA02(INT8U *DstBuf)
//{
//	CString strJIEGUO,strGeShi,strBai,strWanShiwan,strBaiwan,str,strzong,str8;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strGeShi=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	str=chaOne;
//	if (strGeShi=="EE"&&str=="EE")
//	{
//		return "EEEE";
//	}
//	if (strGeShi=="FF"&&str=="FF")
//	{
//		return "FFFF";
//	}
//
//	strBai=str.Right(1);
//
//	str8=m_Cdtl2007._str16tostr2(str);
//	switch(atoi(m_Cdtl2007._str2tostr10(str8.Left(3))))
//	{
//	case 0:
//		strzong=strBai+strGeShi+"0000";
//		break;
//	case 1:
//		strzong=strBai+strGeShi+"000";
//		break;
//	case 2:
//		strzong=strBai+strGeShi+"00";
//		break;
//	case 3:
//		strzong=strBai+strGeShi+"0";
//		break;
//	case 4:
//		strzong=strBai+strGeShi;
//		break;
//	case 5:
//		strzong=strBai+strGeShi.Left(1)+"."+strGeShi.Right(1);
//		break;
//	case 6:
//		strzong=strBai+"."+strGeShi;
//		break;
//	case 7:
//		strzong="0."+strBai+strGeShi;
//		break;
//	}
//	if (str8.Left(4).Right(1)=="0")
//	{
//		if (strzong=="0")
//		{
//			strJIEGUO="0.00 KW";
//		} 
//		else
//		{
//			strJIEGUO=strzong+" KW";
//		}
//	} 
//	else
//	{
//		if (strzong=="0")
//		{
//			strJIEGUO="-0.00 KW";
//		} 
//		else
//		{
//			strJIEGUO="-"+strzong+" KW";
//		}
//	}
//
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA99(INT8U *DstBuf)
//{
//	CString strJIEGUO,strGeShi,strBai,strWanShiwan,strBaiwan,str,strzong,str8;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strGeShi=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	str=chaOne;
//	if (strGeShi=="EE"&&str=="EE")
//	{
//		return "EEEE";
//	}
//	if (strGeShi=="FF"&&str=="FF")
//	{
//		return "FFFF";
//	}
//	
//	strBai=str.Right(1);
//	if (strBai != "0")
//	{
//		strzong = strBai+strGeShi;
//	}
//	else
//	{
//		strzong = strGeShi;
//	}
//	
//	str8=m_Cdtl2007._str16tostr2(str);
//	if (str8.Left(4).Right(1)=="0")
//	{
//		strJIEGUO=strzong+" dBm";
//	} 
//	else
//	{
//		strJIEGUO="-"+strzong+" dBm";
//	}
//	
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA03(INT8U *DstBuf)
//{
//	CString strJIEGUO,strGeShi,strBaiQian,strWanShiwan,strBaiwan,str,strzong,str8;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strGeShi=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strBaiQian=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strWanShiwan=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	str=chaOne;
//	strBaiwan=str.Right(1);
//	
//	str8=m_Cdtl2007._str16tostr2(str);
//	strzong = strBaiwan+strWanShiwan+strBaiQian+strGeShi;
//
//	if (str8.Left(2).Right(1)=="0")
//	{
//		if (str8.Left(4).Right(1)=="0")
//		{
//			strJIEGUO=strzong+" kWh、厘";
//		} 
//		else
//		{
//			strJIEGUO="-"+strzong+" kWh、厘";
//		}
//	} 
//	else
//	{
//		if (str8.Left(4).Right(1)=="0")
//		{
//			strJIEGUO=strzong+" MWh、元";
//		} 
//		else
//		{
//			strJIEGUO="-"+strzong+" MWh、元";
//		}
//	}
//
//	return strJIEGUO;
//}
//
//CString CDisplayData::DisplayDataA04(INT8U *DstBuf)
//{
//	CString strJIEGUO,str,strGe,strShi,str8,strzong;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	str=chaOne;
//
//	strGe=str.Right(1);
//
//	str8=m_Cdtl2007._str16tostr2(str.Left(1));
//
//	strShi=m_Cdtl2007._str2tostr16(str8.Left(4).Right(3));
//	strShi=strShi.Right(1);
//	strzong=strShi+strGe;
//
//	if (str8.Left(1)=="0")
//	{
//		strJIEGUO="上浮"+strzong;
//	} 
//	else
//	{
//		strJIEGUO="下浮"+strzong;
//	}
//
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA05(INT8U *DstBuf)
//{
//	CString strJIEGUO,strGeShifen,strBai,strShi,str,str8,strzong;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strGeShifen=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	str=chaOne;
//
//	strShi=str.Right(1);
//
//	str8=m_Cdtl2007._str16tostr2(str);
//
//	strBai=m_Cdtl2007._str2tostr10(str8.Left(4).Right(3));
//
//	strzong=strBai+strShi+strGeShifen.Left(1)+"."+strGeShifen.Right(1);
//
////	strzong.Format("%g",atof(strBai+strShi+strGeShifen.Left(1)+"."+strGeShifen.Right(1)));
//
//	if (str8.Left(1)=="0")
//	{
//		strJIEGUO=strzong;
//	} 
//	else
//	{
//		strJIEGUO="-"+strzong;
//	}
//
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA06(INT8U *DstBuf)
//{
//	CString strJIEGUO,strShifenBaifen,strGe,strShi,str,str8,strzong;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strShifenBaifen=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	str=chaOne;
//	
//	strGe=str.Right(1);
//	
//	str8=m_Cdtl2007._str16tostr2(str);
//	
//	strShi=m_Cdtl2007._str2tostr10(str8.Left(4).Right(3));
//	strzong=strShi+strGe+"."+strShifenBaifen.Left(1)+strShifenBaifen.Right(1);
//	
//	if (str8.Left(1)=="0")
//	{
//		strJIEGUO=strzong;
//	} 
//	else
//	{
//		strJIEGUO="-"+strzong;
//	}
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA07(INT8U *DstBuf)
//{
//	CString strJIEGUO,strGeShifen,strBaiShi;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[ m_njiexi++]);
//	strGeShifen=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strBaiShi=chaOne;
//	
//	strJIEGUO=strBaiShi+strGeShifen.Left(1)+"."+strGeShifen.Right(1);
////	strJIEGUO.Format("%g",atof(strBaiShi+strGeShifen.Left(1)+"."+strGeShifen.Right(1)));
//
//	return strJIEGUO;
//}
//
//
//CString CDisplayData::DisplayDataA08(INT8U *DstBuf)
//{
//	CString strJIEGUO,strShiGe,strQianBai;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strShiGe=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strQianBai=chaOne;
//	strJIEGUO = strQianBai+strShiGe;
////	strJIEGUO.Format("%d",atoi(strQianBai+strShiGe));
//	return strJIEGUO;
//}
//
//
//CString CDisplayData::DisplayDataA09(INT8U *DstBuf)
//{
//	CString strJIEGUO,strQianfenWanfen,strShifenBaifen,strGe,strShi,str,str8,strzong;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strQianfenWanfen=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strShifenBaifen=chaOne;
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	str=chaOne;
//
//	strGe=str.Right(1);
//
//	str8=m_Cdtl2007._str16tostr2(str);
//
//	strShi=m_Cdtl2007._str2tostr10(str8.Left(4).Right(3));
//
//	strzong=strShi+strGe+"."+strShifenBaifen+strQianfenWanfen;
//	
//	
//	if (str8.Left(1)=="0")
//	{
//		strJIEGUO=strzong;
//	} 
//	else
//	{
//		strJIEGUO="-"+strzong;
//	}
//	
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA10(INT8U *DstBuf)
//{
//	CString strJIEGUO,strGeShi,strBaiQian,strWanShiwan;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strGeShi=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strBaiQian=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strWanShiwan=chaOne;
//	strJIEGUO = strWanShiwan+strBaiQian+strGeShi;
////	strJIEGUO.Format("%d",atoi(strWanShiwan+strBaiQian+strGeShi));
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA11(INT8U *DstBuf)
//{
//	CString strJIEGUO,strShifenBaifen,strGeShi,strBaiQian,strWanShiwan;
//	char chaOne[3]="";
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strShifenBaifen=chaOne;
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strGeShi=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strBaiQian=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strWanShiwan=chaOne;
//
//	strJIEGUO=strWanShiwan+strBaiQian+strGeShi+"."+strShifenBaifen;
//	
////	strJIEGUO.Format("%g",atof(strWanShiwan+strBaiQian+strGeShi+"."+strShifenBaifen));
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA12(INT8U *DstBuf)
//{
//	CString strJIEGUO,strGeShi,strBaiQian,strWanShiwan,strBaiwanQianwan,strYiShiyi,strBaiyiQianyi;
//	char chaOne[3]="";
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strGeShi=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strBaiQian=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strWanShiwan=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strBaiwanQianwan=chaOne;
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strYiShiyi=chaOne;
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strBaiyiQianyi=chaOne;
//
//	strJIEGUO=strBaiyiQianyi+strYiShiyi+strBaiwanQianwan+strWanShiwan+strBaiQian+strGeShi;
////	strJIEGUO.Format("%d",atoi(strBaiyiQianyi+strYiShiyi+strBaiwanQianwan+strWanShiwan+strBaiQian+strGeShi));
////	AfxMessageBox(strJIEGUO);
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA13(INT8U *DstBuf)
//{
//	CString strJIEGUO,strQianfenWanfen,strShifenBaifen,strGeShi,strBaiQian;
//	char chaOne[3]="";
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strQianfenWanfen=chaOne;
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strShifenBaifen=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strGeShi=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strBaiQian=chaOne;
//
//	strJIEGUO=strBaiQian+strGeShi+"."+strShifenBaifen+strQianfenWanfen;
//	
////	strJIEGUO.Format("%g",atof(strBaiQian+strGeShi+"."+strShifenBaifen+strQianfenWanfen));
//	
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA14(INT8U *DstBuf)
//{
//	CString strJIEGUO,strQianfenWanfen,strShifenBaifen,strGeShi,strBaiQian,strWanShiwan;
//	char chaOne[3]="";
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strQianfenWanfen=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strShifenBaifen=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strGeShi=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strBaiQian=chaOne;
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strWanShiwan=chaOne;
//	
//	strJIEGUO=strWanShiwan+strBaiQian+strGeShi+"."+strShifenBaifen+strQianfenWanfen;
//	return strJIEGUO;
//}
//
//CString CDisplayData::DisplayDataA15(INT8U *DstBuf)
//{
//	CString strJIEGUO,strmm,strhh,strDD,strMM,strYY;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strmm=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strhh=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strDD=chaOne;
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strMM=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strYY=chaOne;
//
//	strJIEGUO="20"+strYY+"-"+strMM+"-"+strDD+"  "+strhh+":"+strmm;
//
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA16(INT8U *DstBuf)
//{
//	CString strJIEGUO,strss,strmm,strhh,strDD;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strss=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strmm=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strhh=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strDD=chaOne;
//	
//	
//	strJIEGUO=strDD+"日  "+strhh+":"+strmm+":"+strss;
//	
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA17(INT8U *DstBuf)
//{
//	CString strJIEGUO,strmm,strhh,strDD,strMM;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strmm=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strhh=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strDD=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strMM=chaOne;
//	
//	strJIEGUO=strMM+"月"+strDD+"日  "+strhh+":"+strmm;
//	
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA18(INT8U *DstBuf)
//{
//	CString strJIEGUO,strmm,strhh,strDD;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strmm=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strhh=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strDD=chaOne;
//	
//	strJIEGUO=strDD+"日  "+strhh+":"+strmm;
//	
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA19(INT8U *DstBuf)
//{
//	CString strJIEGUO,strmm,strhh;
//	char chaOne[3]="";
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strmm=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strhh=chaOne;
//	
//	
//	strJIEGUO=strhh+":"+strmm;
//	
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA20(INT8U *DstBuf)
//{
//	CString strJIEGUO,strDD,strMM,strYY;
//	char chaOne[3]="";
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strDD=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strMM=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strYY=chaOne;
//	
//	strJIEGUO="20"+strYY+"-"+strMM+"-"+strDD;
//	
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA21(INT8U *DstBuf)
//{
//	CString strJIEGUO,strMM,strYY;
//	char chaOne[3]="";
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strMM=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strYY=chaOne;
//	
//	strJIEGUO="20"+strYY+"年"+strMM+"月";
//	
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA22(INT8U *DstBuf)
//{
//	CString strJIEGUO,strGeShi;
//	char chaOne[3]="";
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strGeShi=chaOne;
//	strJIEGUO=strGeShi.Left(1)+"."+strGeShi.Left(2).Right(1);
//
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA23(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJIEGUO;
//	CString strQianfenWanfen,strShifenBaifen,strGeShi;
//	CString strY,strR;
//	char chaOne[3]="";
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strQianfenWanfen=chaOne;
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strShifenBaifen=chaOne;
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strGeShi=chaOne;
//		strJIEGUO = strGeShi+"."+strShifenBaifen+strQianfenWanfen;
//		break;
//	case GUANGXIPTY:
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strR=chaOne;
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strY=chaOne;
//		
//		strJIEGUO = strY+"月 "+strR+"日";
//		break;
//	}
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA24(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJIEGUO;
//	CString strhh,strDD;
//	CString str1,str2,str3,str4,strY,strM,strD;
//	char chaOne[3]="";
//
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strhh=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strDD=chaOne;	
//		strJIEGUO=strDD+"日  "+strhh+"时";
//		break;
//	case GUANGXIPTY:
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str1=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str2=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str3=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str4=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strD=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strM=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strY=chaOne;
//		strJIEGUO = strY+"月"+strM+"日"+strD+"时    "+str4+str3+str2+"."+str1;
//		break;
//	}
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA25(INT8U *DstBuf)
//{
//	CString strJIEGUO,strBaifenQianfen,strGeShifen,str,strShi,strBai,str8,strzong;
//	char chaOne[3]="";
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strBaifenQianfen=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strGeShifen=chaOne;
//	
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	str=chaOne;
//
//	strShi=str.Right(1);
//
//	str=m_Cdtl2007._str16tostr2(str.Left(1));
//
//	strBai=m_Cdtl2007._str2tostr10(str.Left(4).Right(3));
//
//	strzong=strBai+strShi+strGeShifen.Left(1)+"."+strGeShifen.Right(1)+strBaifenQianfen;
//
////	strzong.Format("%g",atof(strBai+strShi+strGeShifen.Left(1)+"."+strGeShifen.Right(1)+strBaifenQianfen));
//
//	if (str.Left(1)=="0")
//	{
////		strzong.Format("%f",atof(strzong));
//		strJIEGUO=strzong;
//	} 
//	else
//	{
////		strzong.Format("%f",atof(strzong));
//		strJIEGUO="-"+strzong;
//	}
//
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA26(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJIEGUO;
//	CString strBaifenQianfen,strGeShifen;
//	CString strRi,strShi;
//	char chaOne[3]="";
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strBaifenQianfen=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strGeShifen=chaOne;
//		strJIEGUO=strGeShifen.Left(1)+"."+strGeShifen.Right(1)+strBaifenQianfen;
//		break;
//	case GUANGXIPTY:
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strShi=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strRi=chaOne;
//		strJIEGUO = strRi+"日 "+ strShi+"时";
//		break;
//	}
//	
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataA27(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJIEGUO;
//	CString strGeShi,strBaiQian,strWanShiwan,strBaiwanQianwan;
//	CString strXZ,strG,strH;
//	char chaOne[3]="";
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strGeShi=chaOne;
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strBaiQian=chaOne;
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strWanShiwan=chaOne;
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strBaiwanQianwan=chaOne;
//		strJIEGUO = strBaiwanQianwan+strWanShiwan+strBaiQian+strGeShi;
//		break;
//	case GUANGXIPTY:
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strXZ=chaOne;
//		switch(atoi(strXZ.Left(1)))
//		{
//		case 0:
//			strG = "普通485表";
//			break;
//		case 1:
//			strG = "载波表";
//			break;
//		case 2:
//			strG = "简易多功能表";
//			break;
//		case 3:
//			strG = "多功能总表（台区考核）";
//			break;
//		case 4:
//			strG = "中继器";
//			break;
//		}
//		switch(atoi(strXZ.Right(1)))
//		{
//		case 0:
//			strH = "预付电量表";
//			break;
//		case 1:
//			strH = "预付费表";
//			break;
//		case 2:
//			strH = "非预付费（电量）表";
//			break;
//		}
//		strJIEGUO = strG+" , "+strH;
//		break;
//	}
//	return strJIEGUO;
//}
//
//CString CDisplayData::DisplayDataA28(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJieguo;
//	char chaOne[3]="";
//	CString strJX,strS,strG;
//	CString strMBaifenShifen,strMGeShi,strFGeShi,strDGeShi,strDBai,strF,strFD;
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strMBaifenShifen=chaOne;
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strMGeShi=chaOne;
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strFGeShi=chaOne;
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strDGeShi=chaOne;
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strFD=chaOne;
//		strDBai=strFD.Right(1);
//		
//		if (m_Cdtl2007._str16tostr2(strFD).Left(1)=="1")
//		{
//			strF="西经或南纬";
//		}
//		else
//		{
//			strF="东经或北纬";
//		}
//		strJieguo=strF+" "+strDBai+strDGeShi+"度 "+strFGeShi+"分 "+strMGeShi+"."+strMBaifenShifen;
//		break;
//	case GUANGXIPTY:
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strJX=chaOne;
//		strJX = m_Cdtl2007._str16tostr2(strJX);
//		if (strJX.Right(1) == "0")
//		{
//			strS = "直接接线";
//		}
//		else
//		{
//			strS = "经互感器接线";
//		}
//		if (strJX.Right(2).Left(1) == "0")
//		{
//			strG = "单相表";
//		}
//		else
//		{
//			strG = "三相表";
//		}
//		strJieguo = strS+" , "+strG;
//		break;
//	}
//	return strJieguo;
//}
//
//CString CDisplayData::DisplayDataA29(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJieguo;
//	char chaOne[3]="";
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		break;
//	case GUANGXIPTY:
//		CString strXZ,strG,strH;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strXZ=chaOne;
//		switch(atoi(strXZ.Right(1)))
//		{
//		case 0:
//			strG = "对应总电量";
//			break;
//		case 2:
//			strG = "对应总、1、2电量";
//			break;
//		case 3:
//			strG = "对应总、1、2、3电量";
//			break;
//		case 4:
//			strG = "对应总、1、2、3、4电量";
//			break;
//		}
//		switch(atoi(strXZ.Left(1)))
//		{
//		case 0:
//			strH = "单费率电表";
//			break;
//		case 1:
//			strH = "启用的费率方案号1";
//			break;
//		case 2:
//			strH = "启用的费率方案号2";
//			break;
//		case 3:
//			strH = "启用的费率方案号3";
//			break;
//		case 4:
//			strH = "启用的费率方案号4";
//			break;
//		case 5:
//			strH = "启用的费率方案号5";
//			break;
//		case 6:
//			strH = "启用的费率方案号6";
//			break;
//		case 7:
//			strH = "启用的费率方案号7";
//			break;
//		case 8:
//			strH = "启用的费率方案号8";
//			break;
//		}
//		strJieguo = strG+" , "+strH;
//		break;
//	}
//	return strJieguo;
//}
//CString CDisplayData::DisplayDataA30(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJieguo;
//	char chaOne[3]="";
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		break;
//	case GUANGXIPTY:
//		CString strJX,strS,strG,strH,strK,strF;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strJX=chaOne;
//		strJX = m_Cdtl2007._str16tostr2(strJX);
//		switch(atoi(strJX.Right(2)))
//		{
//		case 0:
//			strG = "不确定";
//			break;
//		case 1:
//			strG = "A相";
//			break;
//		case 10:
//			strG = "B相";
//			break;
//		case 11:
//			strG = "C相";
//			break;
//		}
//		if (strJX.Mid(5,1) == "0")
//		{
//			strS = "不带拉闸";
//		}
//		else
//		{
//			strS = "带拉闸";
//		}
//		if (strJX.Mid(4,1) == "0")
//		{
//			strH = "普通用户";
//		}
//		else
//		{
//			strH = "重点用户";
//		}
//		if (strJX.Mid(3,1) == "0")
//		{
//			strK = "不选抄";
//		}
//		else
//		{
//			strK = "选抄";
//		}
//		if (strJX.Mid(2,1) == "0")
//		{
//			strF = "允许断电";
//		}
//		else
//		{
//			strF = "不允许断电";
//		}
//		
//		strJieguo = strG+" , "+strS+" , "+strH+" , "+strK+" , "+strF;
//		break;
//	}
//	return strJieguo;
//}
//CString CDisplayData::DisplayDataA31(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJieguo;
//	char chaOne[3]="";
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		break;
//	case GUANGXIPTY:
//		CString str1,str2;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str1=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str2=chaOne;
//		strJieguo = "主:"+str2.Left(1)+" ,一:"+str2.Right(1)+" ,二:"+str1.Left(1)+" ,三:"+str1.Right(1);
//		break;
//	}
//	return strJieguo;
//}
//
//CString CDisplayData::DisplayDataA32(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJieguo;
//	char chaOne[3]="";
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		break;
//	case GUANGXIPTY:
//		CString str1,str2,str3,str4,strY,strM,strD;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str1=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str2=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str3=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str4=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strD=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strM=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strY=chaOne;
//		strJieguo = strY+"年"+strM+"月"+strD+"日    "+str4+str3+str2+"."+str1;
//		break;
//	}
//	return strJieguo;
//}
//CString CDisplayData::DisplayDataA33(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJieguo;
//	char chaOne[3]="";
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		break;
//	case GUANGXIPTY:
//		CString str1,str2,str3,str4,strY,strM;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str1=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str2=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str3=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str4=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strM=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strY=chaOne;
//		strJieguo = strY+"年"+strM+"月    "+str4+str3+str2+"."+str1;
//		break;
//	}
//	return strJieguo;
//}
//CString CDisplayData::DisplayDataA35(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJieguo;
//	char chaOne[3]="";
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		break;
//	case GUANGXIPTY:
//		CString str1,str2,str3;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str1=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str2=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str3=chaOne;
//		
//		strJieguo=str3+"."+str2+str1;
//		break;
//	}
//
//	return strJieguo;
//}
//CString CDisplayData::DisplayDataA36(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJieguo;
//	char chaOne[3]="";
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		break;
//	case GUANGXIPTY:
//		CString str1,str2,str3,str4,str5,str6,str7,str8;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str1=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str2=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str3=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str4=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str5=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str6=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str7=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str8=chaOne;	
//		strJieguo="厂商代码:"+str2+str1+"\r\n软件类型:"+str3+"\r\n版本:"+str4.Left(1)+"."+str4.Right(1)+"."+str5+
//			"\r\n附加信息:"+str6+"\r\n地方制定信息:"+str7+str8;
//		break;
//	}
//	return strJieguo;
//}
//CString CDisplayData::DisplayDataA37(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJieguo;
//	char chaOne[3]="";
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		break;
//	case GUANGXIPTY:
//		CString str1,str2,str3,str4,str5,str6,str7,str8;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str1=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str2=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str3=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str4=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str5=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str6=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str7=chaOne;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		str8=chaOne;
//		
//		strJieguo=str8+str7+str6+str5+str4+str3+str2+str1;
//		break;
//	}
//	return strJieguo;
//}
//CString CDisplayData::DisplayDataA40(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strJIEGUO;
//	char chaOne[3]="";
//	switch(pMain->m_nProtocolType)
//	{
//	case GW1376_12013:
//	default:
//	case NEIMENGPTY:
//	case JILINPTY:
//		break;
//	case GUANGXIPTY:
//		CString strQianfenWanfen,strShifenBaifen,strGeShi;
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strQianfenWanfen=chaOne;
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strShifenBaifen=chaOne;
//		
//		m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//		strGeShi=chaOne;
//		strJIEGUO = strGeShi+"."+strShifenBaifen+strQianfenWanfen;
//		break;
//	}
//
//	return strJIEGUO;
//}
//CString CDisplayData::DisplayDataTIME(INT8U *DstBuf)
//{
//	CString strData,strMS;
//	strData = m_Cdtl2007._buf16tostr16(&DstBuf[m_njiexi],9,false,true);
//	m_njiexi += 9;
//	strMS.Format("%d",atoi(strData.Right(4)));
//	strData = strData.Mid(0,4)+"/"+strData.Mid(4,2)+"/"+strData.Mid(6,2)+"  "+strData.Mid(8,2)+":"+strData.Mid(10,2)+":"+strData.Mid(12,2)+"  "+strMS;
//	return strData;
//}
//
//CString CDisplayData::DisplayDataTdc(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strData;
//	char chaOne[3]="";
//	CString strMidu,strDianshu;
//	CString strHeadTime=DisplayDataA15(DstBuf);
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strMidu=chaOne;
//	strMidu=m_Cdtl2007._str16tostr10(strMidu);
//
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strDianshu=chaOne;
//	strDianshu=m_Cdtl2007._str16tostr10(strDianshu);
//	pMain->m_nTimes=atoi(strDianshu);
//
//	strData="起始时间:"+strHeadTime+"  数据冻结密度:"+strMidu+"  数据点数:"+strDianshu;
//
//	return strData;
//}
//
//CString CDisplayData::DisplayDataTdh(INT8U *DstBuf)
//{
//	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString strData,strXunhuan;
//	char chaOne[3]="";
//	CString strTime,strH,strM;
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strTime=chaOne;
//	strTime=m_Cdtl2007._str16tostr2(strTime);
//	strM=m_Cdtl2007._str2tostr10(strTime.Right(4));
//	strH=m_Cdtl2007._str2tostr10(strTime.Right(6).Left(2));
//	CString strMidu;
//	m_Cdtl2007._16Daochar(chaOne,&DstBuf[m_njiexi++]);
//	strMidu=chaOne;
//	strMidu=m_Cdtl2007._str16tostr10(strMidu);
//	switch(atoi(strMidu))
//	{
//	case 0:
//		strMidu="  冻结密度:0  不冻结";
//		pMain->m_nTimes=0;
//		break;
//	case 1:
//		strMidu="  冻结密度:1  冻结间隔时间(15min) 每整点依次的冻结时刻 15分 30分 45分 0分";
//		pMain->m_nTimes=4;
//		break;
//	case 2:
//		strMidu="  冻结密度:2  冻结间隔时间(30min) 每整点依次的冻结时刻 30分 0分";
//		pMain->m_nTimes=2;
//		break;
//	case 3:
//		strMidu="  冻结密度:3  冻结间隔时间(60min) 每整点依次的冻结时刻 0分";
//		pMain->m_nTimes=1;
//		break;
//	case 254:
//		strMidu="  冻结密度:254  冻结间隔时间(5min)  每整点依次的冻结时刻 5分 10分 15分...0分";
//		pMain->m_nTimes=12;
//		break;
//	case 255:
//		strMidu="  冻结密度:255  冻结间隔时间(1min)  每整点依次的冻结时刻 1分 2分 3分...0分";
//		pMain->m_nTimes=60;
//		break;
//	default:
//		strMidu="备用";
//	}
//
//	strData="时间  "+strH+strM+strMidu;
//
//	return strData;
//}
//
//CString CDisplayData::DisplayDataDADT(INT8U *DstBuf)
//{	
//	unsigned char  temp=0;
//	CString strData;
//	INT16U vSrcDA,vSrcDT;
//	temp=DstBuf[m_njiexi++];
//	vSrcDA=DstBuf[m_njiexi++];
//	vSrcDA<<=8;
//	vSrcDA|=temp;
//	CString strDa;
//	if (vSrcDA == 0x00FF)
//	{
//		strDa="所有有效测量点";
//	}
//	else
//	{
//		strDa=m_Cdtl2007._str16toP(vSrcDA);
//	}
//	
//	
//	temp=DstBuf[m_njiexi++];
//	vSrcDT=DstBuf[m_njiexi++];
//	vSrcDT<<=8;
//	vSrcDT|=temp;
//	CString strDt=m_Cdtl2007._str16toF(vSrcDT);
//
//	strData=strDt+"  "+strDa;
//	return strData;
//}
