#pragma once

#define Max698ReadLen  2048
#define  ACKTRUE        TRUE
#define  ACKERR         FALSE
#define  ACKNULL        NULL
typedef struct
{
	INT8U   vSrcC;          //控制码
	INT8U   pSrcAddrAF;  //地址标识
	INT8U   pSrcAddrSA[16];  //服务器地址
	INT8U   pSrcAddrCA;  //客户机地址
	INT8U	* pSrcAPDU;	//链路层APDU
	INT16U   pSrcAPDUlen;	//链路层APDU长度
}PartQGDW698_45;


class CDLT698_45
{
public:
	CDLT698_45(void);
	~CDLT698_45(void);
	INT16U pppfcs16(INT16U fcs,INT8U *cp, int len);
	INT16U tryfcs16(INT8U * cp,int len);
	INT8U Code698_45(PartQGDW698_45 DstQGDW698 ,INT8U *pSrcBuf , INT16U vMaxBuflen , INT16U &vSrcLen );
	INT8U Decode698_45(INT8U *pSrcBuf,INT16U vSrcLen,PartQGDW698_45 &DstQGDW698);
};

