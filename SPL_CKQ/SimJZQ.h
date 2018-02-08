#ifndef _SIMJZQ_H
#define _SIMJZQ_H
#include "User_Mcu_Cfg.h"



#include "gPublicObjct.h"
#include "CDTL2007.h"
#include "CDTL645.H"
#include "SimMeter.h"
#include "Tools.h"
typedef struct 
{
 INT8U s_Seq;
 INT8U ackFg[16+1];
 INT8U di645cnt;
 INT32U di645Buf[16+1];
	
} sBinFa376_2_HostMsg;

typedef struct 
{
 INT8U s_Seq;
 INT8U ackFg;//是否返回 1：返回
 INT8U dataack;//数据格式
 INT32U timeclk;
	
} sAckTimeSta;
class CSimJzq :public cDTL2007,public CDTL645
{
public:
	
// 	 CSimJzq(void);
// 	~CSimJzq(void);
public:
	CTools m_tools;
	INT8U * QueNodeBufAdd(INT16U vNodeBp);
	//从节点硬件复位
	INT8U NodeHardRst(INT8U *vSrcMacAdd);
	INT8U SearthMeterOpAFN06F4(INT32U famedly,INT16U bytedly,INT8U AckType,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	INT8U SearthMeterOpAFN06F2(INT32U famedly,INT16U bytedly,INT8U AckType,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	INT8U SetHostAdd(void);
	void ClrZjqComData(void);
	void SetMainAdd(INT8U * uMainAddress);
			  //-------------------------------------------------
	//【函数名称】 INT8U CmpReSendCntTime(sNoAckDiMsg   AFNnoack,INT8U Cnt,INT32U MinTime,INT32U MaxTime);
	//【函数功能】  比较重次数和时间是否合格。
	//【参数说明】     sNoAckDiMsg   AFNnoack，Cnt：次数，INT32U MinTime,INT32U MaxTime
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
	INT8U CmpReSendCntTime(sNoAckDiMsg   AFNnoack,INT8U Cnt,INT32U MinTime,INT32U MaxTime);
	INT8U  CmpDecode3762( sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_1,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2);
	INT8U  ZjqNoRcvData( INT32U nWaitFramTime , INT16U nWaiteByteTime);
	INT8U   QueAllNetSta(INT8U amtSeq,INT8U vSrcCnt,INT32U WaitTimeS);
		  //-------------------------------------------------
	//【函数名称】 INT8U QueNetSta(INT8U *vSrcAmtBuf,INT32U WaitTimeS);
	//【函数功能】  查询组网状态
	//【参数说明】        vSrcAmtBuf：表地址  WaitTimeS：最大等待时间单位 S
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
	INT8U QueNetSta(INT8U *vSrcAmtBuf,INT32U WaitTimeS);

	INT8U  AFN14F1ACK0001CmpAmt(INT32U amtseq,INT8U DiBp,INT8U AckType);
	INT8U  AFN14F1ACK0001(INT8U AckType);
	//-------------------------------------------------
	//【函数名称】TestReadMeterMoreAdd07(INT8U vSrcDiBp,INT8U DiCnt,INT8U AmtSeq,INT32U AmtCnt,INT32U TestCnt,INT8U CmpType=1)
	//【函数功能】 多地址，多DI测试
	//【参数说明】        
	//【I:	输入】    vSrcDiBp: Di位移，DiCnt: Di个数，INT8U AmtSeqStart： 表地址序号, AmtCnt：表号个数 INT32U TestCnt：测试次数，  INT8U CmpType 0：实际表 1模拟表。
	//【O:	输出】     
	//【返回值	】    DACK_SUCESS;
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年9月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
    INT8U TestReadMeterMoreAdd07(INT8U vSrcDiBp,INT8U DiCnt,INT8U AmtSeq,INT32U AmtCnt,INT32U TestCnt,INT8U CmpType=1);
	
		//-------------------------------------------------
	//【函数名称】 INT8U Test14ReadMeterOneAdd07MoreDi(INT8U vSrcDiBp,INT8U DiCnt,INT8U AmtSeq,INT32U TestCnt,INT8U CmpType=0);
	//【函数功能】 单地址，多DI测试，多次数。
	//【参数说明】        
	//【I:	输入】   vSrcDiBp: Di位移，DiCnt: Di个数，INT8U AmtSeqStart： 表地址序号,  INT32U TestCnt：测试次数，  INT8U CmpType 0：实际表 1模拟表。
	//【O:	输出】     
	//【返回值	】    DACK_SUCESS;
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年9月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
    INT8U Test14ReadMeterOneAdd07MoreDi(INT8U vSrcDiBp,INT8U DiCnt,INT8U AmtSeq,INT32U TestCnt,INT8U CmpType=0);

	//-------------------------------------------------
	//【函数名称】Test14ReadMeterOneAdd07(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U CmpType=1)
	//【函数功能】 单地址，单DI测试,多次
	//【参数说明】        
	//【I:	输入】  INT8U AmtSeqStart： 表地址序号,INT32U Di ： 数据DI， INT32U TestCnt：测试次数， INT8U CmpType 0：实际表 1模拟表。
	//【O:	输出】     
	//【返回值	】    DACK_SUCESS;
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年9月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U Test14ReadMeterOneAdd07(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U CmpType=1);
	
	//-------------------------------------------------
	//【函数名称】INT8U  AFN14F1AllOPCmpAmt(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U AckType,INT8U CmpType);
	//【函数功能】 单地址，单DI测试,多次
	//【参数说明】        
	//【I:	输入】 INT8U AmtSeqStart： 表地址序号;INT32U Di ： 数据DI; INT32U TestCnt：测试次数; AckType: 0 失败，1：成功，2：抄表，4，回复SEQ错误。 
	//             INT8U CmpType 0：实际表 1模拟表。
	//【O:	输出】     
	//【返回值	】    DACK_SUCESS;
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年9月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U  AFN14F1AllOPCmpAmt(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U AckType,INT8U CmpType);


	INT8U  AFN14F1AllOPCmpAmtCon06F2(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U AckType,INT8U Afn06F2AckFg,INT8U CmpType);
		//-------------------------------------------------
	//【函数名称】AFN14F1AllOPAckAmt(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U *vDstAmtBuf,INT8U CmpType=1);
	//【函数功能】 单地址，单DI测试,多次
	//【参数说明】        
	//【I:	输入】  nWaitFramTime：帧延时, nWaiteByteTime：字节延时  AckType: 0 失败，1：成功，2：抄表，4，回复SEQ错误。 
	//             vSrcPct: 协议类型，vDstAmtBuf：返回表址  INT8U CmpType 0：实际表 1模拟表。
	//【O:	输出】     
	//【返回值	】    DACK_SUCESS;
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年9月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U  AFN14F1AllOPAckAmt(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U *vDstAmtBuf,INT8U CmpType=1);
			//-------------------------------------------------
	//【函数名称】 AFN14F1AllOPCon06F2(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U Afn06F2AckFg,INT8U CmpType=1);
	//【函数功能】 单地址，单DI测试,多次
	//【参数说明】        
	//【I:	输入】  nWaitFramTime：帧延时, nWaiteByteTime：字节延时  AckType: 0 失败，1：成功，2：抄表，4，回复SEQ错误。 
	//             vSrcPct: 协议类型，Afn06F2AckFg: 0: 不返回，1：否认 ，2 SEQ，异常。vDstAmtBuf：返回表址  INT8U CmpType 0：实际表 1模拟表。
	//【O:	输出】     
	//【返回值	】    DACK_SUCESS;
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年9月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U AFN14F1AllOPCon06F2(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U Afn06F2AckFg,INT8U CmpType=1);
		//-------------------------------------------------
	//【函数名称】INT8U AFN14F1AllOPAckAmtCon06F2(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U Afn06F2AckFg,INT8U *vDstAmtBuf,INT8U CmpType);
	//【函数功能】 单地址，单DI测试,多次
	//【参数说明】        
	//【I:	输入】  nWaitFramTime：帧延时, nWaiteByteTime：字节延时  AckType: 0 失败，1：成功，2：抄表，4，回复SEQ错误。 
	//             vSrcPct: 协议类型，vSrcDi： 表DI，Afn06F2AckFg  : 06F2回复 1回，0不回；vDstAmtBuf：返回表址  INT8U CmpType 0：实际表 1模拟表。
	//【O:	输出】     
	//【返回值	】    DACK_SUCESS;
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年9月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	INT8U AFN14F1AllOPAckAmtCon06F2(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U Afn06F2AckFg,INT8U *vDstAmtBuf,INT8U CmpType=1);

	INT8U  AFN14F1AllOP(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U CmpType=1);
	INT8U  CmpAFN14F1Data(INT8U *pSrcAddBuf,INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,INT8U CmpType=1);
	INT8U  SlaveAckAFN14F1(INT8U AckType,INT8U *pSrcAddBuf,INT32U Di,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	INT8U  SlaveSend376_2Buf(INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	INT8U  SlaveSend376_2NoBuf(INT8U vSrcAFN,INT16U vSrcFn,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	INT8U  CmpAckTimeClk(INT8U vSrcTimeAllCnt,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,INT8U ack,sAckTimeSta *timeclk376);
			//-------------------------------------------------
	//【函数名称】INT8U  CmpBinFenRcvMeter(INT8U *amtbuf,INT8U vSrcPctType,INT8U vSrc645Cnt,INT8U CmpDataFg,INT32U FameDly,INT32U ByteDly,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//【函数功能】  并发测试功能 
	//【参数说明】        
	//【I:	输入】    vSrcType： 1，97，2 07；     amtbuf：表地址    vSrc645Cnt：645帧的个数.,INT32U vSrcAckFg 数据项有返回结果。CmpDataFg： 是否比较数据正确 .0只比DI，1比数据，模拟表才有此功能 INT32U FameDly帧延时,INT32U ByteDly 字节延时
	//【O:	输出】     sBinFa376_2_HostMsg  &BinDownmsg,   INT32U &vDstFg  成功标志
	//【返回值	】    DACK_SUCESS;
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年9月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	INT8U  CmpBinFenRcvMeter(INT8U *amtbuf,INT8U vSrcPctType,INT8U vSrc645Cnt,INT8U CmpDataFg,INT32U FameDly,INT32U ByteDly,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	INT8U  CmpDiIsOnDiBuf(INT32U Di,INT8U vSrcCnt,INT32U *DiBuf,INT8U &BpFg);
		//-------------------------------------------------
	//【函数名称】INT8U BinFenReadMeter(INT8U vSrcType,TH_IN  INT8U *amtbuf,INT8U vSrc645Cnt,INT32U vSrcAckFg,INT8U CmpDataFg,sBinFa376_2_HostMsg  &BinDownmsg,INT32U &vDstFg)
	//【函数功能】  并发测试功能 
	//【参数说明】        
	//【I:	输入】    vSrcType： 1，97，2 07；     amtbuf：表地址    vSrc645Cnt：645帧的个数.,INT32U vSrcAckFg 数据项有返回结果。CmpDataFg： 是否比较数据正确 .0只比DI，1比数据，模拟表才有此功能
	//【O:	输出】     sBinFa376_2_HostMsg  &BinDownmsg,   INT32U &vDstFg  成功标志
	//【返回值	】    DACK_SUCESS;
	//【全局变量】       
	//【特殊说明】           
	//【开发者	】  杨虎岳  【日期】 2016年9月28日
	//【描  　述】 原始版本
	//-------------------------------------------------
	//【修改人	】     【日期】
	//【描  　述】
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	INT8U BinFenReadMeter(INT8U vSrcType,TH_IN  INT8U *amtbuf,INT8U vSrc645Cnt,INT32U vSrcAckFg,INT8U CmpDataFg,sBinFa376_2_HostMsg  &BinDownmsg,INT32U &vDstFg);
	INT8U  QueMore645Fame(INT8U vSrcType,INT16U vSrcLen,INT8U *vSrcAmtBuf,INT8U cnt,INT8U *vDstBuf,INT16U &vDstLen,sBinFa376_2_HostMsg &ackHostMsg);
	void SendBufToCom(INT8U *vSrcBuf,INT16U vSrcLen);
	void BF_SendBufToCom(INT8U *vSrcBuf,INT16U vSrcLen);
	void SendHost3762ToCom(sPartQGDW376_2CreatFrame sQGDW376_2HostFrame);
	//-------------------------------------------------
	//【函数名称】void GetCOMM376_2ToBuf(INT16U  vSrcLen , INT16U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen);
	//【函数功能】  从串口得到完整376.2帧  
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

	  void GetCOMM376_2ToBuf(INT16U  getLen , INT32U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen);
	  void GetCOMMLENToBuf(INT16U  getLen , INT32U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen);
	  INT8U HostSendRcv376_2Buf_NoAck(INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen);
	  INT8U HostSendRcv376_2NoBuf_NoAck(INT8U vSrcAFN,INT16U vSrcFn);
	  INT8U  HostSendRcv376_2NoBuf(INT8U vSrcAFN,INT16U vSrcFn,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
	  INT8U  HostSendRcv376_2Buf(INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
	  INT8U  HostSendRcv376_2MsgAddrBuf(INT8U vSrcCn,INT8U * vSrcMsgAddr,INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame, INT32U timeout = 10000,INT8U vSrcAckCmp = 0);
	  INT8U  HostSendRcv376_2BufNode(TH_IN const INT8U *pSrcAddBuf ,INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
	  INT8U  HostSend376_2NoBuf(INT8U vSrcAFN,INT16U vSrcFn,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame );
	  INT8U  HostSend376_2Buf(INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	  INT8U  HostRcv376_2( INT32U nWaitFramTime , INT16U nWaiteByteTime ,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	  INT8U  HostSendRcv376_2F0F8(TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	  INT8U  HostSendRcv376_2F0F8MsgAddrBuf(INT8U vSrcCn,INT8U * vSrcMsgAddr, TH_IN const INT8U *pSrcAddBuf, TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	  //-------------------------------------------------
	//【函数名称】  void Check376OP(void)
	//【函数功能】  自动检查376.2串口的数据
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
	
	  void Check376OP(void);


	//【函数名称】 Wait3762Ack(INT16U nWaitFramTime , INT16U nWaiteByteTime,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//【函数功能】  等待376.2的返回
	//【参数说明】        
	//【I:	输入】   famedly：帧延时   bytedly：字节延时 DstDecodeDataFrame: 返回的帧信息
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
	  INT8U  Wait3762Ack(INT32U nWaitFramTime , INT16U nWaiteByteTime,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);

	 //-------------------------------------------------
	//【函数名称】   INT8U  Wait3762AckCmpSeq(INT16U nWaitFramTime , INT16U nWaiteByteTime,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
	//【函数功能】  等待376.2的返回，并判断帧序号是否确。
	//【参数说明】        
	//【I:	输入】   famedly：帧延时   bytedly：字节延时 vSrcDi：下发的645DI sQGDW376_2HostFrame： 下发的帧信息， DstDecodeDataFrame: 返回的帧信息
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
	  INT8U  Wait3762AckCmpSeq(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);

	  //-------------------------------------------------
	//【函数名称】   INT8U  Wait3762AckCmpAFNFN(INT16U nWaitFramTime , INT16U nWaiteByteTime,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
	//【函数功能】  等待376.2的返回，并判断帧序号是否确,并判断，AFN和FN
	//【参数说明】        
	//【I:	输入】   famedly：帧延时   bytedly：字节延时 vSrcDi：下发的645DI sQGDW376_2HostFrame： 下发的帧信息， DstDecodeDataFrame: 返回的帧信息
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
	  INT8U  Wait3762AckCmpAFNFN(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	  INT8U  Wait3762AckCmpAFN(INT32U nWaitFramTime, INT16U nWaiteByteTime, sPartQGDW376_2CreatFrame sQGDW376_2HostFrame, TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	 //-------------------------------------------------
	//【函数名称】  INT8U Router_Stop(void)
	//【函数功能】  停止路由
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
	  INT8U Router_Stop(void);
	  	  //-------------------------------------------------
	//【函数名称】  Router_Start(void)
	//【函数功能】  重启路由
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
	  INT8U Router_Start(void);
	  	  //-------------------------------------------------
	//【函数名称】  INT8U Router_Resume(void)
	//【函数功能】  恢复路由
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
	  INT8U Router_Resume(void);
	  	  //-------------------------------------------------
	//【函数名称】  Router_PaRst(void)
	//【函数功能】  参数区复位
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
	  INT8U Router_PaRst(void);
	  	  //-------------------------------------------------
	//【函数名称】  void Router_DataRst(void)
	//【函数功能】  数据区复位
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
	  INT8U Router_DataRst(void);
	  	  //-------------------------------------------------
	//【函数名称】  void RouterHardRst(void)
	//【函数功能】  硬件复位
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
	  INT8U RouterHardRst(void);

	 //-------------------------------------------------
	//【函数名称】  INT8U SetNodeAdd(INT16U vSrcBp,INT16U vSrcCnt);
	//【函数功能】  设置全局BUF中的从节点 ，vSrcBp开始的vSrcCnt个从节点
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
	  INT8U SetNodeAdd(INT16U vSrcBp,INT16U vSrcCnt);
	  	 //-------------------------------------------------
	//【函数名称】  INT8U CmpNodeAdd(INT16U vSrcBp,INT16U vSrcCnt);
	//【函数功能】  比较全局BUF中的从节点 ，vSrcBp开始的vSrcCnt个从节点
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
	  INT8U CmpNodeAdd(INT16U vSrcBp,INT16U vSrcCnt);
	 //-------------------------------------------------
	//【函数名称】  INT8U QueNodeCnt(INT16U &vDstCnt);
	//【函数功能】  查询从节点数量
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
	  INT8U QueNodeCnt(INT16U &vDstCnt);
	//-------------------------------------------------
	//【函数名称】  INT8U ReadMeterAFN02F1(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//【函数功能】  AFN02F1读表数据，发送并返回376.2帧
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
	  INT8U ReadMeterAFN02F1(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
	  INT8U ReadMeterAFN02F1AckClk(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U vSrcAckCmp=0);
	  	//-------------------------------------------------
	//【函数名称】   CodeReadMeterAFN02F1Cmd(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	//【函数功能】  组帧AFN02F1读表数据，没有发送
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
	  INT8U CodeReadMeterAFN02F1Cmd(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	  	//-------------------------------------------------
	//【函数名称】  INT8U ReadMeterAFN13F1(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//【函数功能】  AFN13F1读表数据，发送并返回376.2帧
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
	  INT8U ReadMeterAFN13F1(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
	   INT8U ReadMeterAFN13F1AckClk(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U vSrcAckCmp = 0);
	    	//-------------------------------------------------
	//【函数名称】   CodeReadMeterAFN02F1Cmd(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);
	//【函数功能】  组帧AFN13F1读表数据，没有发送
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
	  INT8U CodeReadMeterAFN13F1Cmd(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);

	  	  //-------------------------------------------------
	//【函数名称】  INT8U ReadMeterAFN02F1AndCmpMter(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//【函数功能】  AFN02F1读表数据，发送并返回376.2帧，并比较和模拟表的数据一致。
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

	  INT8U ReadMeterAFN02F1AndCmpMter(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType=1);
	  INT8U ReadMeterAFN02F1AndCmpMterAckClk(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U CmpType=1);
	  //-------------------------------------------------
	//【函数名称】  INT8U ReadMeterAFN13F1AndCmpMter(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//【函数功能】  AFN13F1读表数据，发送并返回376.2帧，并比较和模拟表的数据一致。
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
	   INT8U ReadMeterAFN13F1AndCmpMter(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType=1);
	   INT8U ReadMeterAFN13F1AndCmpMterAckClk(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U CmpType=1);
	//-------------------------------------------------
	//【函数名称】 WaitReadMeterAFN02F1AckAndCmp((INT16U famedly,INT16U bytedly,TH_IN  INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
	//【函数功能】  等待02F1的返回，并判断645的DI，判断数据的正确性。应保证读表时，值不能变。
	//【参数说明】        
	//【I:	输入】   famedly：帧延时   bytedly：字节延时 vSrcDi：下发的645DI sQGDW376_2HostFrame： 下发的帧信息， DstDecodeDataFrame: 返回的帧信息
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
	   INT8U WaitReadMeterAFN02F1AckAndCmp(INT32U famedly,INT16U bytedly, INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType=0);

	   //-------------------------------------------------
	//【函数名称】 WaitReadMeterAFN13F1AckAndCmp((INT16U famedly,INT16U bytedly,TH_IN  INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
	//【函数功能】  等待13F1的返回，并判断645的DI，判断数据的正确性。应保证读表时，值不能变。
	//【参数说明】        
	//【I:	输入】   famedly：帧延时   bytedly：字节延时 vSrcDi：下发的645DI sQGDW376_2HostFrame： 下发的帧信息， DstDecodeDataFrame: 返回的帧信息
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
	   INT8U WaitReadMeterAFN13F1AckAndCmp(INT32U famedly,INT16U bytedly, INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType=0);
    //-------------------------------------------------
	//【函数名称】  CodeReadMeter3762Cmd(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame)
	//【函数功能】  组帧读表数据，没有发送
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
       INT8U CodeReadMeter3762Cmd(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame);

	    //-------------------------------------------------
	//【函数名称】   ReadMeterAndCmpMter(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//【函数功能】  读表数据，发送并返回376.2帧，并比较和模拟表的数据一致。
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
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	   INT8U  ReadMeterAndCmpMter(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType=0);
	   INT8U  ReadMeterAndCmpMterAckClk(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U CmpType=0);


	   	    //-------------------------------------------------
	//【函数名称】   Read3762Meter(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//【函数功能】  读表数据，发送并返回376.2帧.
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
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	   INT8U  Read3762Meter(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	   INT8U  Read3762MeterAckClk(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta);


	   
   //-------------------------------------------------
	//【函数名称】 INT8U  WaitReadMeterAckAndCmp(INT8U vSrcType,INT16U famedly,INT16U bytedly, INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
	//【函数功能】  等待抄表的返回，并判断645的DI，判断数据的正确性。应保证读表时，值不能变。
	//【参数说明】        
	//【I:	输入】  vSrcType 0: AFN=0x02,F1,1:   AFN =13F1,  famedly：帧延时   bytedly：字节延时 vSrcDi：下发的645DI sQGDW376_2HostFrame： 下发的帧信息， DstDecodeDataFrame: 返回的帧信息
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

	   INT8U  WaitReadMeterAckAndCmp(INT8U vSrcType,INT32U famedly,INT16U bytedly, INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType=0);
	   	 //-------------------------------------------------
//【函数名称】CodeReadData9707Cmd(INT8U pcttype, TH_IN const INT32U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData)；
//【函数功能】     //编码读命令
//【参数说明】        
//【I:	输入】    pcttype  :0:  97 ,1: 07
//              	   INT32U s_Di;//DI
//                    INT8U  s_AmtBuf[6];//表地址
//                    INT8U  s_type;//操作模式，0：无FE， 1：有4个FE                
//【O:	输出】       sDtl2007_Read &vDstCmdData
//【返回值	】     正确：DACK_SUCESS   错误：DACK_FAILURE   
//【全局变量】       
//【特殊说明】           
//【开发者	】  杨虎岳   【日期】 2016年8月01日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	   INT8U   CodeReadData9707Cmd(INT8U pcttype,TH_IN const INT32U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData);


	   INT8U  EventOp(INT32U famedly,INT16U bytedly,INT8U AckType,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U *vDstAmtBuf,INT8U CmpType);
#ifdef _STD_CSG  //南网标准
		INT8U HostSendRcv376_2NoBuf_NoAck(INT8U vSrcAFN,INT32U vSrcFn);
		INT8U HostSendRcv376_2Buf_NoAck(INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen);
		INT8U HostSendRcv376_2MsgAddrBuf(INT8U vSrcCn,INT8U * vSrcMsgAddr,INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
		INT8U HostSendRcv376_2Buf(INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
		INT8U HostSendRcv376_2NoBuf(INT8U vSrcAFN,INT32U vSrcFn,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
		INT8U HostSendRcv376_2BufNode(TH_IN const INT8U *pSrcAddBuf, INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp = 0);
		
		INT8U HostSendRcv376_2F0F8(TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame);
		INT8U HostSend376_2Buf(INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQGDW376_2HostFrame);
		INT8U HostSend376_2NoBuf(INT8U vSrcAFN,INT32U vSrcFn,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame);
		INT8U HostRcv376_2( INT32U nWaitFramTime , INT16U nWaiteByteTime ,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame);
		void SendHost3762ToCom(sPartQCSG376_2CreatFrame sQCSG376_2HostFrame);
		INT8U   Wait3762Ack(INT32U nWaitFramTime , INT16U nWaiteByteTime,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame);
		INT8U   Wait3762AckCmpSeq(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartQCSG376_2CreatFrame sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame);
		INT8U   Wait3762AckCmpAFNFN(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartQCSG376_2CreatFrame sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame);
		INT8U CodeReadMeter3762Cmd(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame);
		INT8U CmpAckTimeClk(INT8U vSrcTimeAllCnt,sPartQCSG376_2DeCodeFrame DstDecodeDataFrame,INT8U ack,sAckTimeSta *timeclk376);
		INT8U SlaveSend376_2Buf(INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2DeCodeFrame DstDecodeDataFrame,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame);
		INT8U SlaveSend376_2NoBuf(INT8U vSrcAFN,INT16U vSrcFn,sPartQCSG376_2DeCodeFrame DstDecodeDataFrame,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame);
		INT8U CmpDecode3762( sPartQCSG376_2DeCodeFrame DstDecodeDataFrame_1,sPartQCSG376_2DeCodeFrame DstDecodeDataFrame_2);

#endif
};

#endif
