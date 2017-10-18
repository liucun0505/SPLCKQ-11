#include "StdAfx.h"
#include "Tools.h"
#include "direct.h"
#include "io.h"


CTools::CTools(void)
{
}


CTools::~CTools(void)
{
}

CString CTools::BeforeAddO(CString strData,int numb)
{
	int nlen = strData.GetLength();
	for(int n = 0;n<(numb-nlen);n++)
	{
		strData = _T("0") + strData;
	}
	return strData;
}
CString CTools::_strDaoxu(CString strData)
{
	CString strRdata;
	int len = strData.GetLength()/2;
	for(int n = 0;n<len;n++)
	{
		strRdata += strData.Mid(2*(len-1-n),2);
	}
	return strRdata;
}

void CTools::_16Daochar(char *testc,INT8U *buf)
{
	testc[0]=0;
	testc[1]=0;
	testc[0]=buf[0]>>4;
	if ((testc[0]>=0)&&(testc[0]<=9))
	{
		testc[0]+=48;
	}
	else
	{
		testc[0]+=0x37;
	}

	testc[1]=buf[0]&0x0f;
	if ((testc[1]>=0)&&(testc[1]<=9))
	{
		testc[1]+=48;
	}
	else
	{
		testc[1]+=0x37;
	}
}
CString CTools::_buf16tostr16(INT8U * buf16,INT16 len,bool bKongge,bool bDaoxu)
{
	char chaOne[3] = "";
	CString strtwo,strData;
	for(int n = 0;n < len;n++)
	{	
		if (bDaoxu)
		{
			_16Daochar(&chaOne[0],&buf16[len - n - 1]);
		} 
		else
		{
			_16Daochar(&chaOne[0],&buf16[n]);
		}

		strtwo=chaOne;
		if(bKongge)
		{
			strData += strtwo + _T(" ");
		}
		else
		{
			strData+=strtwo;
		}

	}
	return strData;
}

void CTools::_str16tobuf16(CString str16,INT8U * buf16,INT16U &len , bool bDaoxu)
{
	CString strData;
	int n = 0 ;
	for(n = 0 ;n<str16.GetLength();n++)
	{
		if (str16.Mid(n,1)!=" ")
		{
			strData +=str16.Mid(n,1);
		}
	}
	if (bDaoxu)
	{
		strData = _strDaoxu(strData);
	}
	len = strData.GetLength()/2;
	CStringA str = "";
	for(n = 0;n<len;n++)
	{
		str = strData.Mid(2*n,2);
		buf16[n] = (INT8U)strtol(str,NULL,16);
	}

}

void CTools::strlistData(CString strData,CString strF,CString strDst[])
{
	int nlen = 0;
	int m = 0;
	for(int n = 0; n < (int)wcslen(strData); n++)
	{
		nlen = strData.Find(strF);
		strDst[m] = strData.Mid(0,nlen);
		strData = strData.Mid(nlen + 1);
		m++;
		n = 0;
	}
}
CString CTools::_str16toF(INT16U DT)
{
	INT8U dtbuf[2];
	CString str,strFZong;
	char chaOne[3]="";
	int nF;
	
	dtbuf[0]=DT;
	dtbuf[1]=DT>>8;

	for(int n = 0;n<8;n++)
	{
		if(((dtbuf[0]>>n)&0x01) == 0x01)
		{
			nF = n+1;
			_16Daochar(chaOne,&dtbuf[1]);
			str=chaOne;
			CString strDT2=_str16tostr10(str);
			CString strF;
			strF.Format(_T("%d"),nF+_ttoi(strDT2)*8);
			strF=_T("F")+strF;
			strFZong += strF;
		}
	}
	return strFZong;
}
void CTools::_strFto16(CString strF,INT16U &Fbuf)
{
	int n=_ttoi(strF);
	int n_10=n/8,n_2=n%8;
	CString str10;
	if (n_2==0)
	{
		n_10-=1;
	}
	CString str_2;
	Fbuf = (INT8U)n_10;
	switch(n_2)
	{
	case 0:
		Fbuf = (Fbuf<<8)|0x80;
		break;
	case 1:
		Fbuf = (Fbuf<<8)|0x01;
		break;
	case 2:
		Fbuf = (Fbuf<<8)|0x02;
		break;
	case 3:
		Fbuf = (Fbuf<<8)|0x04;
		break;
	case 4:
		Fbuf = (Fbuf<<8)|0x08;
		break;
	case 5:
		Fbuf = (Fbuf<<8)|0x10;
		break;
	case 6:
		Fbuf = (Fbuf<<8)|0x20;
		break;
	case 7:
		Fbuf = (Fbuf<<8)|0x40;
		break;
	}
}
CString CTools::_str10tostr2(CString str10,int len)
{
	int n10=_ttoi(str10);
	CString str2,strone;
	int n=0;
	while(n10!=0)
	{
		strone.Format(_T("%d"),n10%2);

		str2=strone+str2;
		n10/=2;
		n+=1;
	}
	CString str0=_T("");
	int len2=wcslen(str2);
	if ((len-len2)<0)
	{
		return _T("Ê§°Ü");
	}
	else
	{
		for(n=0;n<(len-len2);n++)
		{
			str0+="0";
		}
		str2=str0+str2;
	}	
	return str2;
}
CString CTools::_str2tostr16(CString str2)
{
	CString str16,str16zong;
	CString str;
	int len=wcslen(str2);
	switch(len%8)
	{
	case 1:
		str2=_T("0000000")+str2;
		break;
	case 2:
		str2=_T("000000")+str2;
		break;
	case 3:
		str2=_T("00000")+str2;
		break;
	case 4:
		str2=_T("0000")+str2;
		break;
	case 5:
		str2=_T("000")+str2;
		break;
	case 6:
		str2=_T("00")+str2;
		break;
	case 7:
		str2=_T("0")+str2;
		break;
	}
	len=wcslen(str2);
	for(int n=0;n<(len/4);n++)
	{
		str=str2.Left(4*n+4).Right(4);
		if (str=="0000")
		{
			str16="0";
		}
		if (str=="0001")
		{
			str16="1";
		}
		if (str=="0010")
		{
			str16="2";
		}
		if (str=="0011")
		{
			str16="3";
		}
		if (str=="0100")
		{
			str16="4";
		}
		if (str=="0101")
		{
			str16="5";
		}
		if (str=="0110")
		{
			str16="6";
		}
		if (str=="0111")
		{
			str16="7";
		}
		if (str=="1000")
		{
			str16="8";
		}
		if (str=="1001")
		{
			str16="9";
		}
		if (str=="1010")
		{
			str16="A";
		}
		if (str=="1011")
		{
			str16="B";
		}
		if (str=="1100")
		{
			str16="C";
		}
		if (str=="1101")
		{
			str16="D";
		}
		if (str=="1110")
		{
			str16="E";
		}
		if (str=="1111")
		{
			str16="F";
		}
		str16zong+=str16;
	}
	return str16zong;
}
CString CTools::_str16tostr10(CString str16)
{
	int len=wcslen(str16);
	DWORD n10=0;
	int x=0;
	DWORD _16Ncifang=1;
	for(int n=1;n<(len+1);n++)
	{
		_16Ncifang=1;
		for(int a=1;a<n;a++)
		{
			_16Ncifang*=16;
		}
		if (str16.Right(n).Left(1)=="0")
		{
			x=0;
		}
		if (str16.Right(n).Left(1)=="1")
		{
			x=1;
		}
		if (str16.Right(n).Left(1)=="2")
		{
			x=2;
		}
		if (str16.Right(n).Left(1)=="3")
		{
			x=3;
		}
		if (str16.Right(n).Left(1)=="4")
		{
			x=4;
		}
		if (str16.Right(n).Left(1)=="5")
		{
			x=5;
		}
		if (str16.Right(n).Left(1)=="6")
		{
			x=6;
		}
		if (str16.Right(n).Left(1)=="7")
		{
			x=7;
		}
		if (str16.Right(n).Left(1)=="8")
		{
			x=8;
		}
		if (str16.Right(n).Left(1)=="9")
		{
			x=9;
		}
		if (str16.Right(n).Left(1)=="A"||str16.Right(n).Left(1)=="a")
		{
			x=10;
		}
		if (str16.Right(n).Left(1)=="B"||str16.Right(n).Left(1)=="b")
		{
			x=11;
		}
		if (str16.Right(n).Left(1)=="C"||str16.Right(n).Left(1)=="c")
		{
			x=12;
		}
		if (str16.Right(n).Left(1)=="D"||str16.Right(n).Left(1)=="d")
		{
			x=13;
		}
		if (str16.Right(n).Left(1)=="E"||str16.Right(n).Left(1)=="e")
		{
			x=14;
		}
		if (str16.Right(n).Left(1)=="F"||str16.Right(n).Left(1)=="f")
		{
			x=15;
		}
		n10+=x*_16Ncifang;

	}
	
	CString str10 = _T("");
	str10.Format(_T("%d") , n10);
	return str10;
}
CString CTools::_str2tostr10(CString str2)
{
	CString str1,str10;
	int _2Ncifang=1;
	int n10=0;
	int len=wcslen(str2);
	for(int n=0;n<len;n++)
	{
		_2Ncifang=1;
		for(int a=0;a<n;a++)
		{
			_2Ncifang*=2;
		}
		str1=str2.Right(n+1).Left(1);
		if (str1=="1")
		{
			n10+=_2Ncifang;
		}
	}
	str10.Format(_T("%d"),n10);
	return str10;
}

CString CTools::_str16tostr2(CString str16)
{
	CString str2,str2zong;
	CString str10;
	int len=wcslen(str16);
	for(int n=0;n<len;n++)
	{
		str10=str16.Left(n+1).Right(1);
		if (str10=="0")
		{
			str2="0000";
		}
		if (str10=="1")
		{
			str2="0001";
		}
		if (str10=="2")
		{
			str2="0010";
		}
		if (str10=="3")
		{
			str2="0011";
		}
		if (str10=="4")
		{
			str2="0100";
		}
		if (str10=="5")
		{
			str2="0101";
		}
		if (str10=="6")
		{
			str2="0110";
		}
		if (str10=="7")
		{
			str2="0111";
		}
		if (str10=="8")
		{
			str2="1000";
		}
		if (str10=="9")
		{
			str2="1001";
		}
		if (str10=="A")
		{
			str2="1010";
		}
		if (str10=="B")
		{
			str2="1011";
		}
		if (str10=="C")
		{
			str2="1100";
		}
		if (str10=="D")
		{
			str2="1101";
		}
		if (str10=="E")
		{
			str2="1110";
		}
		if (str10=="F")
		{
			str2="1111";
		}
		str2zong+=str2;
	}
	return str2zong;
}
CString CTools::_str10tostr16(CString str10,int len)
{
	DWORD64 n10=_ttol(str10);
	CString str16,strone;
	int n=0;
	while(n10!=0)
	{
		strone.Format(_T("%d"),n10%16);
		int non=_ttoi(strone);
		switch(non)
		{
		case 10:
			strone="A";
			break;
		case 11:
			strone="B";
			break;
		case 12:
			strone="C";
			break;
		case 13:
			strone="D";
			break;
		case 14:
			strone="E";
			break;
		case 15:
			strone="F";
			break;
		}
		str16=strone+str16;
		n10/=16;
		n+=1;
	}
	CString str0=_T("");
	for(n=0;n<(int)(2*len-wcslen(str16));n++)
	{
		str0+="0";
	}
	str16=str0+str16;
	return str16;
}

void CTools::Split(CString strData , CString strT, CString * strlist , int &nNumb)
{
	int nBegin = 0;
	nNumb = 0;
	while(true)
	{
		nBegin = strData.Find(strT); 
		if(nBegin == -1) break;
		strlist[nNumb++] = strData.Mid(0 , nBegin);
		strData = strData.Mid(nBegin + 1);
	}
}
int CTools::FindFNumb(CString strData , CString strT)
{
	int nBegin = 0;
	int nNumb = 0; 
	while(true)
	{
		nBegin = strData.Find(strT); 
		if(nBegin == -1) break;
		strData = strData.Mid(nBegin + 1);
		nNumb++;
	}
	return nNumb;
}
void CTools::AsclltoHex(CString strAsc,INT8U asclen,INT8U * pDstBuf,INT8U &vDstLen)
{
	int nlen = wcslen(strAsc);
	pDstBuf=(unsigned char*)strAsc.GetBuffer(nlen);
	for(int n = 0 ; n<asclen-nlen;n++)
	{
		pDstBuf[nlen+n] = 0;
	}
	vDstLen = asclen;
}
CString CTools::HextoAscll(INT8U *buf,int nJiexi,int zijielen,bool ForR)
{
	CString str;
	int n;
	CString str2,strzong;
	if (ForR==TRUE)
	{
		for(n=0;n<zijielen;n++)
		{
			str2=(TCHAR)buf[nJiexi+zijielen-n-1];
			if (str2!="")
			{
				strzong+=str2;
			}

		}
	} 
	else
	{
		for(n=0;n<zijielen;n++)
		{
			str2=(TCHAR)buf[nJiexi+n];
			strzong+=str2;
		}
	}
	return strzong;
}

void CTools::Buf_To_LenBuf(INT8U * SrcDatabuf , INT16U SrcDatalen , INT8U * DstDatabuf , INT16U & DstDatalen)
{
	DstDatabuf[0] = (INT8U)SrcDatalen;
	DstDatabuf[1] = (INT8U)(SrcDatalen>>8);
	for(INT16U n = 0 ; n < SrcDatalen ; n++)
	{
		DstDatabuf[2 + n] = SrcDatabuf[n];
	}
	DstDatalen = SrcDatalen + 2;
}

int CTools::AutoMakedir(char * path)
{
	char *tag;
	for (tag = path; *tag; tag++)
	{
		if (*tag == '\\')
		{
			char buf[1000], dir[1000];
			strcpy(buf, path);
			buf[strlen(path) - strlen(tag) + 1] = NULL;
			strcpy(dir, buf);
			if (access(dir, 6) == -1)
			{
				mkdir(dir);
			}
		}
	}
	return 0;
}

void CTools::DecToBCD(__int64 Dec,INT8U * Bcd,unsigned char length)
{
    INT8U i;
    __int64 temp;
    for(i=0; i<length; i++)
    {
        temp=Dec%100;
        Bcd[i]=((temp/10)<<4)+((temp%10)&0x0f);
        Dec/=100;
    }
}