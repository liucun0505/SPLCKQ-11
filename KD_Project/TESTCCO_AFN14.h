#pragma once


// CTESTCCO_AFN14
#include "Tools.h"
#include "GW13762.h"
class CAFN14ReadMeterFun
{

public:

	INT8U TestOneAdd(INT8U CmpType);
		INT8U TestMoreAdd(INT8U CmpType);

	//-------------------------------------------------
	//【函数名称】 INT8U  TestOneAddSetPa(void);
	//【函数功能】  dan地址参数设置
	//【参数说明】        
	//【I:	输入】   
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U  TestOneAddSetPa(void);
	//【1】正常抄表测试
	INT8U  TestOneAddReadMeter_OK(INT8U CmpType);
	//步1的正常回复测试
	INT8U  TestOneAddReadMeter_Step1Ack(INT8U CmpType);
	//步1的异常回复测试  ackType: 0 不回复。 1：回复错SEQ
	INT8U  TestOneAddReadMeter_Step1ErrAck(INT8U vSrcAckType,INT8U CmpType);

	//-------------------------------------------------
	//【函数名称】 INT8U  TestAddReadMeter_Step1ErrAck_Amt(INT32U AmtSeq,INT8U vSrcAckType,INT8U ReCnt,INT8U CmpType);
	//【函数功能】 AMT步1的异常回复测试  
	//【参数说明】        
	//【I:	输入】   AmtSeq: 从节点开始序号；vSrcAckType：回复类型 0 不回复。 1：回复错SEQ;   ReCnt 重发次数。  CmpType： 0实际表  1模拟表。
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U  TestAddReadMeter_Step1ErrAck_Amt(INT32U AmtSeq,INT8U vSrcAckType,INT8U ReCnt,INT8U CmpType);
	//步3的异常回复测试  ackType: 0 不回复。 1：回复错SEQ,
	INT8U  TestOneAddReadMeter_Step3ErrAck_Amt(INT32U AmtSeq,INT8U vSrcAckType,INT8U CmpType);
	//步3的异常回复测试  ackType: 0 不回复。 1：回复错SEQ,
	INT8U  TestOneAddReadMeter_Step3ErrAck(INT8U vSrcAckType,INT8U CmpType);
	//步3的异常回复测试 回复否认帧
	INT8U  TestOneAddReadMeter_Step3ErrAckNo_Amt(INT32U Amtseq,INT8U CmpType);
	//步3的异常回复测试 回复否认帧
	INT8U  TestOneAddReadMeter_Step3ErrAckNo(INT8U CmpType);
	//单地址路由测试
	INT8U TestOneAddRouter(INT8U CmpType);
	//多地址参数设置
	INT8U  TesMoreAddSetPa(void);
	//多表DI的正常测试
	INT8U  TesMoreAddReadMeter(INT8U CmpType);

	//步1的正常回复测试
	INT8U  TestMoreAddReadMeter_Step1Ack(INT8U CmpType);
	//步1的异常回复测试  ackType: 0 不回复。 1：回复错SEQ
	INT8U  TestMoreAddReadMeter_Step1errAck(INT8U Acktype,INT8U CmpType);
	//步3异常回复SEQ，不回复测试
	INT8U  TestMoreAddReadMeter_Step3ErrAck(INT8U CmpType);
	//步3异常回否认测试
	INT8U  TestMoreAddReadMeter_Step3ErrAckNo(INT8U CmpType);
	//MOre地址路由测试
    INT8U  TestMoreAddRouter(INT8U CmpType);

};
class CTESTCCO_AFN14 : public CWnd, public CAFN14ReadMeterFun
{
	DECLARE_DYNAMIC(CTESTCCO_AFN14)

public:
	CTESTCCO_AFN14();
	virtual ~CTESTCCO_AFN14();
	void C3762_TEST(HTREEITEM hTree);//方案处理函数
	CTools m_tool;
	CGW13762 m_Cgw13762;
	INT8U AFN14OneMeterNoAck(void);
	INT8U AFN14MoreMeterNoAck(void);

protected:
	DECLARE_MESSAGE_MAP()
	
};


