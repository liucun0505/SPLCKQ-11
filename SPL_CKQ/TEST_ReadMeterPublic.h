#pragma once



#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
class CTEST_ReadMeterPublic : public cDTL2007
{
	

public:


	void  StaSucessCnt(INT8U ack,INT8U &allSucesscnt,INT8U &failCnt);


protected:
		//-------------------------------------------------
	//【函数名称】   TestReadMeterLongFame(INT32U vSrcCnt,INT8U vSrcAfntype,INT8U vSrcMeterType);
	//【函数功能】   	长帧测试（实际表）（模拟表）
	//【参数说明】        
	//【I:	输入】   vSrcCnt 次数；vSrcAfntype 0: AFN=0x02,F1,1:   AFN =13F1；vSrcMeterType ： 0实际  1模拟
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U  TestReadMeterLongFame(INT32U vSrcCnt,INT8U vSrcAfntype,INT8U vSrcMeterType);
		//-------------------------------------------------
	//【函数名称】   INT8U  TestReadMeterErrDi(INT32U vSrcCnt,INT8U vSrcAfntype);
	//【函数功能】    错误DI测试（实际表）（模拟表）
	//【参数说明】        
	//【I:	输入】   vSrcCnt 次数；vSrcAfntype 0: AFN=0x02,F1,1:   AFN =13F1
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
    INT8U  TestReadMeterErrDi(INT32U vSrcCnt,INT8U vSrcAfntype);
	//-------------------------------------------------
	//【函数名称】   INT8U  TestReadMeterCnt(INT32U vSrcCnt,INT8U vSrcAfntype,INT8U vSrcMeterType)
	//【函数功能】 多次次转发测试（实际表）（模拟表）
	//【参数说明】        
	//【I:	输入】   vSrcCnt 次数；vSrcAfntype 0: AFN=0x02,F1,1:   AFN =13F1；vSrcMeterType ： 0实际  1模拟
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
    INT8U  TestReadMeterCnt(INT32U vSrcCnt,INT8U vSrcAfntype,INT8U vSrcMeterType);
	INT8U   TestSetPa(void);
		//-------------------------------------------------
	//【函数名称】  INT8U TestSeqNOAck645Di(INT32U vSrcCnt,INT8U Type)
	//【函数功能】  SEQ测试，无网络测试
	//【参数说明】        
	//【I:	输入】   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U TestSeqNONet(INT32U vSrcCnt,INT8U Type);
	//-------------------------------------------------
	//【函数名称】  INT8U TestSeqNOAck645Di(INT8U Type)
	//【函数功能】  SEQ测试，组网成功，STA NO回复
	//【参数说明】        
	//【I:	输入】   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U  TestSeqNOAck645Di(INT8U Type);
	//-------------------------------------------------
	//【函数名称】  INT8U TestSeqAck645Di(INT8U Type)
	//【函数功能】  SEQ测试，组网成功，STA有回复
	//【参数说明】        
	//【I:	输入】   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U  TestSeqAck645Di(INT8U Type);
		//-------------------------------------------------
	//【函数名称】  INT8U TestSeqAck645ErrDi(INT32U vSrcCnt,INT8U Type)
	//【函数功能】  回复DI不一致数据（模拟表）
	//【参数说明】        
	//【I:	输入】   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U  TestSeqAck645ErrDi(INT32U vSrcCnt,INT8U Type);
		//-------------------------------------------------
	//【函数名称】  INT8U TestPartAckNo(INT8U Type)
	//【函数功能】  表部分回复测试。
	//【参数说明】        
	//【I:	输入】   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U TestPartAckNo(INT8U Type);
	//-------------------------------------------------
	//【函数名称】  INT8U TestIntevalTime(INT8U Type)
	//【函数功能】  重发次数、间隔时间测试
	//【参数说明】        
	//【I:	输入】   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U TestIntevalTime(INT8U Type);


	//-------------------------------------------------
	//【函数名称】  INT8U TestMoreReadMeterNoRcv(INT8U Type)
	//【函数功能】  连续多帧测试（中间无接收）（实际表）（模拟表）
	//【参数说明】        
	//【I:	输入】   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	 INT8U  TestMoreReadMeterNoRcv(INT8U Type);

	 	//-------------------------------------------------
	//【函数名称】  INT8U TestMoreReadMeterRcv(INT8U Type)
	//【函数功能】 多帧测试（中间要接收）（实际表）（模拟表）
	//【参数说明】        
	//【I:	输入】   vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,
	//【O:	输出】    
	//【返回值	】    
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年6月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	 INT8U  TestMoreReadMeterRcv(INT8U Type);
};


