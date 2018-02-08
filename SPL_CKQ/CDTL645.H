#ifndef _CDTL645_H
#define _CDTL645_H
#include "User_Mcu_Cfg.h"
#include "CDTL2007.h"

class CDTL645
{

  public:
	  void   CodeToAck97Data(struct Stu_Dtl2007 &Dtl2007Buf,const INT8U *vSrcBuf,const INT16U vSrcLen);
	  	 	 //-------------------------------------------------
//【函数名称】CodeReadDataCmd(TH_IN const INT32U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData)；
//【函数功能】     //编码读命令
//【参数说明】        
//【I:	输入】        INT32U s_Di;//DI
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
	  INT8U CodeReadData97Cmd(TH_IN const INT16U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData);
	  //-------------------------------------------------
     //INT8U  AdjustTimeCode(const INT8U *buf,INT8U pSrcMaxLen,INT8U *tempbuf,INT8U &pDstLen,INT8U type=0);
     INT8U  CheckAmtAdd97(const INT8U *pSrcAdd,const INT8U *pSrcRcvAdd);
     void   CodeReadData97(const INT16U pSrcDi,const INT8U *pSrcAmtAddBuf,INT8U *pDstBuf,INT8U &pDstLen,INT8U type=0);
     INT8U  Decode64597(const INT8U *pSrcBuf,const INT16U pSrcLen,const INT8U vSrcDataLen,INT8U *pDstAmtAddBuf,INT16U &pDstDi,INT8U *pDstBuf,INT8U &pDstLen);
     virtual void  CodeWriteData97(const INT16U pSrcDi,const INT8U *pSrcAmtAddBuf,const INT8U *pSrcBuf,const INT8U pSrcLen,INT8U *pDstBuf,INT8U &pDstLen,INT8U type=0);
     INT8U CheckFullFrame64597(const INT8U *buf,const INT16U pSrcLen);
     //增加没有Fe方式
     INT8U CodeReadDataNoFe97(const INT16U pSrcDi,const INT8U *pSrcAmtAddBuf,INT16U vSrcLen,INT8U *pDstBuf,INT8U &pDstLen);
      //数据转换,07的数据要转换成国网07的数据格式
   //INT8U  Tran97ToGW07(INT16U pSrcDi,INT8U *vDstBuf,INT8U &vDstLen);
   //数据转换,97的数据要转换成国网05的数据格式
   //INT8U  Meter97ToGW05(INT16U pSrcDi,INT8U *vDstBuf,INT8U &vDstLen);
   
    INT8U TranDi97(INT16U vSrcDi16,INT8U vSrcLen,INT16U &vDstDi16,INT8U &vDstLen);
    INT8U ReDecode_GWPCT97(INT16U Di,INT8U len,INT8U *tempbuf,INT8U outlen);
	//解码广播校时，用于数据+延时的的处理
     //INT8U  Decode645AdjustTime(const INT8U *pSrcBuf,const INT16U pSrcLen,const INT16U vSrcDataLen,INT8U *pDstBuf,INT8U &pDstLen);
	 INT8U CheckOk97(const INT8U *pSrcBuf,const INT8U pSrcLen);
	 void CodeReadAckData97(const INT16U pSrcDi,const INT8U *pSrcAmtAddBuf,const INT8U *pSrcBuf,const INT16U pSrcLen,INT8U *pDstBuf,INT8U &pDstLen,INT8U type);


};
#endif

