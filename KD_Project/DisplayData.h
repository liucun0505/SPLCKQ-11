#if !defined(AFX_DISPLAYDATA_H__9233A61D_0F25_42DB_893D_6D06DBCF9FB3__INCLUDED_)
#define AFX_DISPLAYDATA_H__9233A61D_0F25_42DB_893D_6D06DBCF9FB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisplayData.h : header file
//
#include "Tools.h"
/////////////////////////////////////////////////////////////////////////////
// CDisplayData window

class CDisplayData
{
// Construction
public:
	CDisplayData();

// Attributes
public:
	int m_nstrN;
	int m_nOldRecvCi;
	int m_RecvOldCishu[5000];
	int m_RecvCishu[1000];
	int m_nRecvCi;
	int m_nZondDataLen;
	CTools m_tools;
	bool m_bBits;
	int m_nBits;
	int m_nBit;
	int m_njiexi;
	int m_nXiaoshu;
	CString GetGeshi(CString strXunhuan,CString strGeshi,int m,int n);//相关显示函数
	CString GetBeizhu(CString strXunhuan,CString strBeizhu);//相关显示函数
	CString DisplayShowMessage(CString strCode , CString strShowMsg , INT8U * databuf , INT16U datalen);
	CString DisplayJiexiData(CString str,INT8U *DstBuf,int * RecvCishu,int nCishu);  //显示主函数
	CString DisplayDatabin(CString strShuxingname,INT8U *DstBuf); //bin格式显示
	CString Bin(INT8U *buf,int nJiexi,int zijielen,bool ForR);
	CString DisplayDatabin_n(CString strShuxingname,INT8U *DstBuf); //bin_n格式显示
	CString DisplayDatabit(CString strShuxingname,INT8U *DstBuf);//bit 格式显示
	void Bit(INT8U *buf,int nJiexi,int zijielen,int mshujuNub,int *fanhuidata,bool ForR);
	void Bits(INT8U *buf,int nJiexi,int zijielen,int mshujuNub,CString * strshujulen,int *fanhuidata,bool ForR);
	CString DisplayDatabits(CString strShuxingname,INT8U *DstBuf);//bits格式显示
	CString DisplayDataascll(CString strShuxingname,INT8U *DstBuf);//ascll格式显示
	CString Char(INT8U *buf,int nJiexi,int zijielen,bool ForR);
	CString DisplayDatachar(CString strShuxingname,INT8U *DstBuf);//有无小数点的数字格式显示
	//CString DisplayDataA01(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA02(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA99(INT8U *DstBuf);
	//CString DisplayDataA03(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA04(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA05(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA06(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA07(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA08(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA09(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA10(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA11(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA12(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA13(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA14(INT8U *DstBuf);//A01格式显示  年月日 时分秒 星期
	//CString DisplayDataA15(INT8U *DstBuf);//A15格式显示  年月日 时分
	//CString DisplayDataA16(INT8U *DstBuf);//A16格式显示  月日时分秒
	//CString DisplayDataA17(INT8U *DstBuf);//A17格式显示  月日 时分
	//CString DisplayDataA18(INT8U *DstBuf);//A18格式显示  日时分
	//CString DisplayDataA19(INT8U *DstBuf);//A19格式显示  时分
	//CString DisplayDataA20(INT8U *DstBuf);//A20格式显示  年月日 
	//CString DisplayDataA21(INT8U *DstBuf);//A21格式显示  年月
	//CString DisplayDataA22(INT8U *DstBuf);
	//CString DisplayDataA23(INT8U *DstBuf);
	//CString DisplayDataA24(INT8U *DstBuf);
	//CString DisplayDataA25(INT8U *DstBuf);
	//CString DisplayDataA26(INT8U *DstBuf);
	//CString DisplayDataA27(INT8U *DstBuf);
	//CString DisplayDataA28(INT8U *DstBuf);

	//CString DisplayDataA29(INT8U *DstBuf);
	//CString DisplayDataA30(INT8U *DstBuf);
	//CString DisplayDataA31(INT8U *DstBuf);
	//CString DisplayDataA32(INT8U *DstBuf);
	//CString DisplayDataA33(INT8U *DstBuf);
	//CString DisplayDataA35(INT8U *DstBuf);
	//CString DisplayDataA36(INT8U *DstBuf);
	//CString DisplayDataA37(INT8U *DstBuf);
	//CString DisplayDataA40(INT8U *DstBuf);//广西用
	//CString DisplayDataTdc(INT8U *DstBuf);
	//CString DisplayDataTdh(INT8U *DstBuf);
	//CString DisplayDataDADT(INT8U *DstBuf);
	//CString DisplayDataTIME(INT8U *DstBuf);
	//CString DisTdh(int n); 

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayData)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDisplayData();

	// Generated message map functions
protected:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYDATA_H__9233A61D_0F25_42DB_893D_6D06DBCF9FB3__INCLUDED_)
