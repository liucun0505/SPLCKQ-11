#pragma once


// CTESTNODE
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
//typedef union
//{
//	BYTE bitByte;
//	struct 
//	{
//		BYTE comunate_mod:6;
//		BYTE prm:1;
//		BYTE dir:1;
//	}bits;
//}UN_C_DATA;//control data
//
//typedef union
//{
//	BYTE bitByte[6];
//	struct 
//	{
//		BYTE route			:1;//路由标识
//		BYTE subNode		:1;
//		BYTE module			:1;
//		BYTE collisDetect	:1;
//		BYTE routeLevel		:4;//byte1
//
//		BYTE channel		:4;
//		BYTE errCorrect		:4;//byte 2
//
//		BYTE prediAnserBn	;//byte 3 predictAnswerbyteNum
//
//		WORD rate			:15;
//		WORD rateUnit		:1;//速率单位 byte4-5
//
//		BYTE serialNum		;//byte 6
//	}bits;
//}UN_DOWN_R_DATA;//control data
//
//typedef union
//{
//	BYTE bitByte[6];
//	struct 
//	{
//		BYTE route			:1;//路由标识
//		BYTE resved1		:1;
//		BYTE module			:1;
//		BYTE resved2		:1;
//		BYTE routeLevel		:4;//byte1
//
//		BYTE channel		:4;
//		BYTE resved3		:4;//byte 2
//
//		BYTE RealPhaseLine	:4;//byte 3 predictAnswerbyteNum
//		BYTE meterChStyle	:4;
//
//		BYTE finalCmdQual	:4;
//		BYTE finalAnsQual	:4;//速率单位 byte4
//
//		BYTE events			:1;//byte 5
//		BYTE resved4		:7;
//
//		BYTE serialNum;			//byte6
//	}bits;
//}UN_UP_R_DATA;//上行信息数据
//
//typedef union
//{
//	UN_DOWN_R_DATA	R_down;
//	UN_UP_R_DATA	R_up;
//}UN_R_DATA;
//
//typedef union
//{
//	BYTE data[3];
//	struct 
//	{
//		BYTE test;
//		WORD route			:15;//路由标识
//		WORD K				:1;
//	}bits;
//}UN_ST_TEST;
//
//
//typedef struct
//{
//	BYTE DT1;
//	BYTE DT2;
//}ST_Fn;
//
//
//typedef struct tpd_ST_1376_2_FRAME{
//	WORD L;
//	UN_C_DATA C;
//
//	UN_R_DATA R;//上下行R可选
//
//	BYTE A1[6];
//	BYTE A2[6];
//	BYTE A3[6];
//
//	BYTE AFN;
//
//	ST_Fn Fn;
//
//	BYTE CS;
//}ST_1376_2_FRAME;
class CTESTNODE : public CWnd
{
	DECLARE_DYNAMIC(CTESTNODE)

public:
	CTESTNODE();
	virtual ~CTESTNODE();
	void C3762_TEST(HTREEITEM hTree);//方案处理函数
	//DWORD sendData2Module(unsigned char AFN, unsigned char fn, unsigned char prm);
	INT8U addNode(int tpe);
	//void FillDataUnit(unsigned char AFN, unsigned char fn, INT8U *pBufRecv);
	CTools m_tool;
	CGW13762 m_Cgw13762;

protected:
	DECLARE_MESSAGE_MAP()
};


