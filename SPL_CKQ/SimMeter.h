
#ifndef _SIMMTER_H
#define _SIMMTER_H
#include "User_Mcu_Cfg.h"
#include "User_App_Cfg.h"

#define DNOACKDICNT   16

typedef struct 
{
 INT32U s_Di;
 INT32U s_Time[FRAME645_RESEND_MAXCNT+1];
 INT8U  s_RcvCnt;
	
} sNoAckDiMsg;//下行帧的头帧，请求帧

typedef struct 
{
 INT32U s_Time[20];
 INT8U  s_RcvCnt;
	
} sAckAmtMsg;//下行帧的头帧，请求帧

typedef struct 
{
  INT8U s_NoAckDiCnt;
  sNoAckDiMsg   s_NoAckMsg[DNOACKDICNT];
} sNoAckAllMsg;

typedef struct 
{
 INT8U s_Sta;//当前搜表状态，格式BIN。00H 表示搜表结束；01H 表示搜表中。
 INT8U s_SendCnt;//本次报文返回的实际电表通信地址个数，格式BIN。
 INT8U  s_AllCnt;//实际电表数量，格式BIN
 INT16U s_SmtBpStart;
	
} sSearchMeterData;//下行帧的头帧，请求帧

#include "CDTL645.H"
#include "CDTL2007.h"
class CSimMeter: public cDTL2007,public CDTL645
{
public:
	
	CSimMeter(void);
	~CSimMeter(void);
public:
	void SetAmtAddBp(INT16U vSrcBp);
	void SetSearchSta(INT8U vSrcallcnt,INT8U vSrcSendCnt,INT16U vSrcAmtBp,INT8U vSrcSta);
	INT8U  Cmp645DiDataAmt(INT8U *pSrcAddBuf,INT8U pcttype,INT32U vSrcDi,INT8U *vSrcBuf,INT16U vSrcLen,INT8U Cmptype=1);
	INT8U  Cmp645DiDataAndAck(INT8U pcttype,INT32U vSrcDi,INT8U *vSrcBuf,INT16U vSrcLen,Stu_Dtl2007  &ackData645Frame,INT8U Cmptype=1);
	INT8U CmpDeCode645DiData(Stu_Dtl2007 ackData645Frame);
	INT8U CheckNoDiAckmsg(sNoAckDiMsg  noackMsg);
//-------------------------------------------------
//【函数名称】 QueNoDiAckmsg(INT32U vSrcDi,sNoAckDiMsg  &ackMsg)
//【函数功能】 查询无返回的信息
//【参数说明】        
//【I:	输入】  
//【O:	输出】    
//【返回值	】    DACK_SUCESS:
//【全局变量】       
//【特殊说明】           
//【开发者	】  杨虎岳  【日期】 2016年6月28日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	INT8U QueNoDiAckmsg(INT32U vSrcDi,sNoAckDiMsg  &ackMsg);

	//-------------------------------------------------
//【函数名称】 void SetNoAckDi(INT32U vSrcDi);
//【函数功能】 设置不返回的DI值
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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void SetNoAckDi(INT32U vSrcDi);
//-------------------------------------------------
//【函数名称】 void ClrALLNoAckDi(INT32U vSrcDi);
//【函数功能】 清除不返回的DI值
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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void ClrNoAckDi(INT32U vSrcDi);
//-------------------------------------------------
//【函数名称】 ClrALLNoAckDi(void);
//【函数功能】 清除所有不返回的DI值
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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void ClrALLNoAckDi(void);
	//-------------------------------------------------
//【函数名称】 INT8U QueAckDiIsEn(INT32U vSrcDi);
//【函数功能】 查询此DI返回
//【参数说明】        
//【I:	输入】   
//【O:	输出】    
//【返回值	】  DACK_SUCESS ：要返回  
//【全局变量】       
//【特殊说明】           
//【开发者	】  杨虎岳  【日期】 2016年6月28日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
	INT8U QueAckDiIsEn(INT32U vSrcDi);
	INT8U ChangeMeterData(INT8U pctype,INT32U vSrcDi);
	INT8U  QueMeterData(INT8U pctype,INT32U vSrcDi,sDtl645_Buf  &Meterdata );
	void SendMeterData_64597(Stu_Dtl2007 stDtl2007);
	void SendBufToCom(INT8U *vSrcBuf,INT16U vSrcLen);
	void SendMeterData_645(Stu_Dtl2007 stDtl2007);
	void Send_BADD_645(Stu_Dtl2007 stDtl2007, INT8U * BufRecv , INT8U & BufRecvlen);
	INT8U  QueMeterData_645(INT32U vSrcDi,sDtl645_Buf  &Meterdata );
	INT8U ChangeMeterData_645(INT32U vSrcDi);
	//-------------------------------------------------
//【函数名称】void GetCOMM645ToBuf(INT16U  vSrcLen , INT16U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen);
//【函数功能】  从串口得到完整645帧  
//【参数说明】        
//【I:	输入】    vSrcLen 返回数组的最大长度，      nWaitFramTime：帧延时       nWaiteByteTime：字节延时  .
//【O:	输出】     recvbuf  recvlen：帧长度
//【返回值	】    
//【全局变量】       
//【特殊说明】           
//【开发者	】  杨虎岳  【日期】 2016年9月28日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void GetCOMM645ToBuf(INT16U  vSrcLen , INT16U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen);
//-------------------------------------------------
//【函数名称】  void CheckMeterOP(void)
//【函数功能】  自动检查串口的数据
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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void CheckMeterOP(void);

	//-------------------------------------------------
//【函数名称】  void SetSimMeterRunFg(INT8U type)
//【函数功能】  
//【参数说明】        
//【I:	输入】  1:运行 0：不运行 
//【O:	输出】    
//【返回值	】    
//【全局变量】       
//【特殊说明】           
//【开发者	】  杨虎岳  【日期】 2016年6月28日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void SetSimMeterRunFg(INT8U type);
	void SetAckFg(INT8U type);
	void ClrSimMeterComData(void);
//-------------------------------------------------
//【函数名称】  INT8U  Wait645ack(INT16U famedly,INT16U bytedly,Stu_Dtl2007 &DstDecode2007DataFrame)
//【函数功能】  等645返回
//【参数说明】        
//【I:	输入】  famedly：帧延时   bytedly：字节延时 
//【O:	输出】    DstDecode2007DataFrame ： 645返回
//【返回值	】    DACK_SUCESS 
//【全局变量】       
//【特殊说明】           
//【开发者	】  杨虎岳  【日期】 2016年6月28日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	INT8U Wait645ack(INT16U famedly,INT16U bytedly,Stu_Dtl2007 &DstDecode2007DataFrame);

//-------------------------------------------------
//【函数名称】  INT8U Cmp645DiData(INT32U vSrcDi,INT8U *vSrcBuf,INT16U vSrcLen,INT8U Cmptype)
//【函数功能】  比较645帧的值
//【参数说明】        
//【I:	输入】   vSrcDi：   vSrcBuf:645帧 vSrcLen：长度
//【O:	输出】   
//【返回值	】    DACK_SUCESS 
//【全局变量】       
//【特殊说明】           
//【开发者	】  杨虎岳  【日期】 2016年6月28日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	INT8U Cmp645DiData(INT8U pcttype,INT32U vSrcDi,INT8U *vSrcBuf,INT16U vSrcLen,INT8U Cmptype=1);


	INT8U  QueMeterData_64597(INT32U vSrcDi,sDtl645_Buf  &Meterdata );
	INT8U  ChangeMeterData_645_97(INT16U vSrcDi);
	void ClrReadAmtCnt(void);
	INT32U QueReadAmtCnt(void);
	void  SetAckAmtFg(INT8U Ackfg);
	void  QueReadAmtMsg(sAckAmtMsg  &ReadAmtMsg);
private:
	  INT8U m_RunSta;
	  sAckAmtMsg  m_ReadAmtMsg;
	  sSearchMeterData   m_SearchMeterData;
	  INT16U  m_AmtAddBp;
public:
	INT8U m_NoFg;//无返回标记 0:不启用 1:启用  
	INT32U  m_ReadAmtCnt;//读表地址统计
	INT8U   m_AmtAckFg;//1： 是  0：否    回复读书表地址
	
	
};

#endif
