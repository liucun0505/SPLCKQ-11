// View698.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "View698.h"
#include "APDUdata.h"
#include "MainFrm.h"
#include "Tools.h"
// CView698

IMPLEMENT_DYNCREATE(CView698, CFormView)

CView698::CView698()
	: CFormView(CView698::IDD)
{

}

CView698::~CView698()
{
}

void CView698::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SHOW, m_editShow);
}

BEGIN_MESSAGE_MAP(CView698, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CView698::OnBnClickedButton1)
END_MESSAGE_MAP()


// CView698 诊断

#ifdef _DEBUG
void CView698::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CView698::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CView698 消息处理程序
void CView698::_str16tobuf16(CString str16,INT8U * buf16,INT16U &len)
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
	len = strData.GetLength()/2;
	CStringA str = "";
	for(n = 0;n<len;n++)
	{
		str = strData.Mid(2*n,2);
		buf16[n] = (INT8U)strtol(str,NULL,16);
	}

}
void CView698::_16Daochar(char *testc,INT8U *buf)
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
CString CView698::_buf16tostr16(INT8U * buf16,int len,bool bKongge,bool bDaoxu)
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
u_long CView698::BCD_Change_Hex(u_long BCDValue)//,u_char num_)
{

	u_long X = 0, Y = 1;
	for(u_char i = 0; i < 8; i++)
	{
		X += (BCDValue & 0xf) * Y;
		BCDValue >>= 4;
		Y *= 10;
	}
	return(X);
}
INT8U CView698::BCDtoInteger(INT8U integer, INT8U * pDstbuf , INT8U & Dstlen)
{
	if (integer >> 7)
	{
		integer &= 0x7f;
		integer = (INT8U)BCD_Change_Hex(integer);
		integer = ~integer + 1;
	}
	else
	{
		integer = (INT8U)BCD_Change_Hex(integer);
	}
	pDstbuf[0] = integer;
	Dstlen = 1;
	return true;
}

void CView698::OnBnClickedButton1()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CTools tools;
	CString strConnect = _T("68 38 00 43 05 01 00 00 00 00 00 10 E0 08 02 00 00 10 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 04 00 04 00 01 04 00 00 00 00 64 00 00 DB 79 16");
	CString strGetReadV = _T("68 17 00 43 05 01 00 00 00 00 00 10 26 F6 05 01 00 20 00 02 00 00 E5 BE 16");
	CString strGetReadA = _T("68 17 00 43 05 01 00 00 00 00 00 10 26 F6 05 01 00 20 01 02 00 00 5E A2 16");
	
	CString strSetTime = _T("68 1F 00 81 05 07 09 19 05 16 20 00 F1 65 06 01 02 40 00 02 00 1C 20 16 01 20 16 27 11 00 3A 60 16");
	CString strSetStruct = _T("68 25 00 43 05 07 09 19 05 16 20 00 F8 58 06 01 02 30 00 05 00 02 04 12 00 00 12 00 00 05 00 00 00 00 11 00 9D D0 16");

	CString strAction = _T("68 19 00 81 05 07 09 19 05 16 20 00 86 90 07 01 05 00 10 01 00 0F 00 00 84 7D 16");
	CString strActionlist = _T("68 20 00 81 05 07 09 19 05 16 20 00 72 EA 07 02 05 02 00 10 01 00 0F 00 00 10 02 00 0F 01 00 2F 51 16");
	CString strMACData = _T("68 2B 00 43 05 01 00 29 01 16 20 0A FC 65 10 00 08 05 01 01 40 01 02 00 00 00 85 01 02 03 06 12 34 56 78 90 12 04 12 34 56 78 31 CC 16 ");


	CString strjl = _T("68 2F 00 81 05 07 09 19 05 16 20 00 3E F6 05 03 03 50 04 02 00 01 20 21 02 00 1C 20 16 01 20 00 00 00 02 00 20 21 02 00 00 00 10 02 00 00 2E E5 16");
	CString str = _T("68 17 00 81 05 07 09 19 05 16 20 00 5B D9 05 01 01 40 01 02 00 00 C6 07 16");
	CString str1 = _T("81 00 80 20 16 05 19 08 05 00 00 89 20 16 05 19 08 05 01 02 5F 20 16 05 19 08 05 02 02 DA");
	CString strAPDUAct = _T("070102F10004000202090D400202000800000000000000015E812A000105001440000004A7268F10");
	CDLT698_45 dlt698;//
	INT8U buf[1024];
	INT8U Recvbuf[1024];
	INT16U len = 0;
	INT8U dstAPDU[1024];
	INT16U dstAPDUlen = 0;
	PartQGDW698_45 Sendpart698 , Recvpart698;
	_str16tobuf16(strGetReadV,buf,len);
	//INT8U ack = dlt698.Decode698_45(buf ,len ,Sendpart698);



	m_SrcAPDUlen = 0;
	m_pSrcAPDUbuf = m_pSrcAPDUbuf + m_SrcAPDUlen;
	m_pSrcAPDUbuf = &buf[2];
	m_SrcAPDUlen += len - 2;
	m_pbSrcAPDUbuf = m_pSrcAPDUbuf;

	_str16tobuf16(strGetReadA,buf,len);
	m_pSrcAPDUbuf = m_pSrcAPDUbuf + m_SrcAPDUlen;
	m_pSrcAPDUbuf = &buf[2];
	m_SrcAPDUlen += len - 2;

	m_editShow.SetWindowText(_buf16tostr16(m_pbSrcAPDUbuf , m_SrcAPDUlen , true ,false));
	return;
	//if(ack == ACKTRUE)
	{
		tools._str16tobuf16(strAPDUAct , Sendpart698.pSrcAPDU , Sendpart698.pSrcAPDUlen);
		INT8U  tmpbuf[500];
		Data pData[100];
		CAPDUdata apdudata(tmpbuf,500 ,pData, 100 );
		apdudata.CoadAPDU(Sendpart698 , dstAPDU , dstAPDUlen);
		Recvpart698.pSrcAPDUlen = dstAPDUlen;
		Recvpart698.pSrcAPDU = dstAPDU;
		Recvpart698.vSrcC = 0x01;
		Recvpart698.pSrcAddrAF = 0x05;
		Recvpart698.pSrcAddrSA[0] = 0x07;
		Recvpart698.pSrcAddrSA[1] = 0x09;
		Recvpart698.pSrcAddrSA[2] = 0x19;
		Recvpart698.pSrcAddrSA[3] = 0x05;
		Recvpart698.pSrcAddrSA[4] = 0x16;
		Recvpart698.pSrcAddrSA[5] = 0x20;
		Recvpart698.pSrcAddrCA = 0x10;
		INT8U ack = dlt698.Code698_45(Recvpart698 , Recvbuf , 255 ,  len);
		m_editShow.SetWindowText(_buf16tostr16(Recvbuf,len,1,0));
	}

}