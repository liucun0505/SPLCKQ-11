#pragma once

class CTools
{
public:
	CTools(void);
	~CTools(void);
	CString	BeforeAddO(CString strData,int numb);
	CString _strDaoxu(CString strData);
	void _16Daochar(char *testc,INT8U *buf);
	CString _buf16tostr16(INT8U * buf16,INT16 len,bool bKongge = false,bool bDaoxu = false);
	void _str16tobuf16(CString str16,INT8U * buf16,INT16U &len , bool bDaoxu = false);
	void strlistData(CString strData,CString strF,CString strDst[]);
	void _strFto16(CString strF,INT16U &Fbuf);
	CString _str16toF(INT16U DT);
	CString _str10tostr2(CString str10,int len);
	CString _str2tostr16(CString str2);
	CString _str16tostr10(CString str16);
	CString _str10tostr16(CString str10,int len);
	CString _str2tostr10(CString str2);
	CString _str16tostr2(CString str16);
	void AsclltoHex(CString strAsc,INT8U asclen,INT8U * pDstBuf,INT8U &vDstLen);
	CString HextoAscll(INT8U *buf,int nJiexi,int zijielen,bool ForR);
	void Split(CString strData , CString strT , CString * strlist , int &nNumb);
	int FindFNumb(CString strData , CString strT);

	void Buf_To_LenBuf(INT8U * SrcDatabuf , INT16U SrcDatalen , INT8U * DstDatabuf , INT16U & DstDatalen);

	int AutoMakedir(char* path);
    void DecToBCD(__int64 Dec,INT8U * Bcd,unsigned char length);
};

