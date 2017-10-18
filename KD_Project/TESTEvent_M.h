#pragma once


// CTESTEvent_M
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
class  CEventPublic
{
public:
protected:
	//-------------------------------------------------
	//【函数名称】 INT8U CmpEventIsOnSta(INT8U *vSrcAmtAdd,INT8U vSrcSeq,INT8U vSrcCnt,INT8U CmpType);
	//【函数功能】 比对事件是否在列表中
	//【参数说明】        
	//【I:	输入】   vSrcCnt： 当前发送的次数，CmpType：0 比对正在上报列表  1 比对已上报列表。
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】

INT8U CmpEventIsOnSta(INT8U *vSrcAmtAdd,INT8U vSrcSeq,INT8U vSrcCnt,INT8U CmpType);
//dan地址参数设置
INT8U   TestOneAddSetPa(void);
//测试回确认0x01、否认0x02
INT8U   TestOneEventAckOKNO(INT8U acktype,INT8U CmpType);

	//-------------------------------------------------
	//【函数名称】 INT8U   TestOneEventNoAckSeqErr_Amt(INT8U acktype,INT8U CmpType)
	//【函数功能】 测试SEQ错0x03,不回复0x04
	//【参数说明】        
	//【I:	输入】   acktype：SEQ错0x03,不回复0x04。 CmpType： 0 实际，1模改
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
INT8U   TestOneEventNoAckSeqErr_Amt(INT8U acktype,INT8U CmpType);
//测试acktype SEQ错0x03,不回复0x04  ; CmpType:0 实际表 1 摸拟表 
INT8U   TestOneEventNoAckSeqErr(INT8U acktype,INT8U CmpType);
//多地址参数设置
INT8U  TesMoreAddSetPa(void);
//多地址测试回确认0x01、否认0x02
INT8U   TestMoreEventAckOKNO(INT8U acktype,INT8U CmpType);
//多地址测试SEQ错0x03,不回复0x04
INT8U   TestMoreEventNoAckSeqErr(INT8U acktype,INT8U CmpType);
//	部分回复测试
INT8U   TestMoreEventPartNoAck(INT8U CmpType);
};

class CTESTEvent_M : public CWnd,public CEventPublic
{
	DECLARE_DYNAMIC(CTESTEvent_M)

public:
	CTESTEvent_M();
	virtual ~CTESTEvent_M();
	void C3762_TEST(HTREEITEM hTree);//方案处理函数
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
	INT8U  TestStaNoAck(void);
	INT8U  TestStaStaDataNoChang(void);
};


