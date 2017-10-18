#ifndef  _CDTL2007_H
#define  _CDTL2007_H



#include "User_Mcu_Cfg.h"
#include "GW13762.h"
#include "CSG13762.h"
#define FRAME645_MAX_LEN  254
#define DATA645_MAX_LEN  ( FRAME645_MAX_LEN-1)
#define PARALLEL376_2_MAX_CNT  13
typedef struct 
{
 INT8U 	s_pDstCmdBuf[FRAME645_MAX_LEN];//数据指针？
 INT8U 	s_vDstCmdLen;//
} sDtl2007_Read;	 //645-07读结构;

struct Stu_Dtl2007	 //645-07结构
{
 INT8U  s_Con;//控制吗
 INT32U s_Di;//DI
 INT8U  s_AmtBuf[6];//表地址
 INT8U  s_PwdBuf[8];//密钥，操作者代码
 INT8U  s_Len;//数据长度
 INT8U 	s_pDstBuf[FRAME645_MAX_LEN];//数据指针？
 INT8U  s_type;//协议类型
};

typedef struct 
{
 struct Stu_Dtl2007   DTLData;
 INT8U         Port;//端口号
} sDtl645_07OP;

typedef struct 
{
 INT8U  s_DataBuf[FRAME645_MAX_LEN];
 INT16U  s_DataLen;
 INT8U   Port;//端口号
} sDtl645_Buf;

//-----------------------------------------------------------------------------
//【类名称】       CDTL2007
//【类功能】       组、解析 645——07贞，组、解析广播校时贞
//【成员变量说明】 见下面说明 
//--------------------------------------------------------------
class cDTL2007
{

 public:
	 // :vDstAmtBuf表地址, vDstFcnt:FE个数  vDstFctFg:协议类型 0 645-97，1  645-07， 3：广播校时命令 :返回TRUE：是645协议
     INT8U  CheckFull645Pct_All(const INT8U *pSrcBuf,const INT16U pSrcLen,INT8U &vDstFctFg);//检测帧的最小长度
	 void CodeToAckData(struct Stu_Dtl2007 &Dtl2007Buf,const INT8U *vSrcBuf,const INT16U vSrcLen);
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
	  INT8U CodeReadDataCmd(TH_IN const INT32U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData);
//-------------------------------------------------
//【函数名称】INT8U Decode2007(TH_IN const INT8U *pSrcBuf,TH_IN const INT16U pSrcLen,TH_OUT Stu_Dtl2007 &DstDecode2007DataFrame);
//【函数功能】      解码所有的2007协议 直接将结果输出到645-07结构体中   
//【参数说明】        
//【I:	输入】        *pSrcBuf :  需要解码贞内容   ,  pSrcLen ：需要解码贞长度                   
//【O:	输出】       DstDecode2007DataFrame ：正确的协议输出到结构体   
//【返回值	】     正确：DACK_SUCESS   错误：DACK_FAILURE   
//【全局变量】       
//【特殊说明】           
//【开发者	】  赵震   【日期】 2016年6月29日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INT8U Decode2007(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT Stu_Dtl2007 &DstDecode2007DataFrame);
 
//-------------------------------------------------
//【函数名称】void CodeToWatchData(TH_IN const struct Stu_Dtl2007 Dtl2007Buf,TH_IN INT8U type,TH_OUT INT8U *pDstBuf,TH_OUT INT8U &pDstLen)
//【函数功能】     645 结构 编码成连续的数据 写数据（密码明文形式）    
//【参数说明】        
//【I:	输入】     Dtl2007Buf :  645——07数据结构     type=0 ：	  type=0 0x68前有0xfe ,否则没有                
//【O:	输出】       *pDstBuf ： 总贞内容 ，  pDstLen ：总贞长度 
//【返回值	】     正确：DACK_SUCESS   错误：DACK_FAILURE   
//【全局变量】       
//【特殊说明】           
//【开发者	】  赵震   【日期】 2016年6月29日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CodeToWatchData(TH_IN const struct Stu_Dtl2007 Dtl2007Buf,TH_IN INT8U type,TH_OUT INT8U *pDstBuf,TH_OUT INT16U &pDstLen);

//-------------------------------------------------
//【函数名称】void CodeToWatchPData(TH_IN const struct Stu_Dtl2007 Dtl2007Buf,TH_OUT INT8U *pDstBuf,TH_OUT INT8U &pDstLen);
//【函数功能】     645 结构 编码成连续的数据 写数据（ESAM密文形式）    
//【参数说明】        
//【I:	输入】     Dtl2007Buf :  645——07数据结构     type=0 ：	  type=0 0x68前有0xfe ,否则没有                
//【O:	输出】       *pDstBuf ： 总贞内容 ，  pDstLen ：总贞长度 
//【返回值	】     正确：DACK_SUCESS   错误：DACK_FAILURE   
//【全局变量】       
//【特殊说明】           
//【开发者	】  赵震   【日期】 2016年6月29日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CodeToWatchPData(TH_IN const struct Stu_Dtl2007 Dtl2007Buf,TH_OUT INT8U *pDstBuf,TH_OUT INT16U &vDstLen);

//-------------------------------------------------
//【函数名称】void  CodeReadAmtAdd(TH_IN INT8U vSrcLen,TH_IN INT8U type,TH_OUT INT8U *pDstBuf,TH_OUT INT8U &vDstLen)
//【函数功能】  编码读表地址   
//【参数说明】        
//【I:	输入】      type=0 0x68前有0xfe ,否则没有               
//【O:	输出】       *pDstBuf ： 总贞内容 ，  pDstLen ：总贞长度 
//【返回值	】     正确：DACK_SUCESS   错误：DACK_FAILURE   
//【全局变量】       
//【特殊说明】           
//【开发者	】  赵震   【日期】 2016年6月29日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void  CodeReadAmtAdd(TH_IN INT8U type,TH_OUT INT8U *pDstBuf,TH_OUT INT16U &vDstLen);

//-------------------------------------------------
//【函数名称】INT8U DecodeReadAmtAdd(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT Stu_Dtl2007 &DstDecode2007DataFrame)
//【函数功能】       解码读表地址  
//【参数说明】        
//【I:	输入】     *vSrcBuf ：解码的贞内容  ， vSrcLen ：解码的贞长度	   type=0 0x68前有0xfe ,否则没有               
//【O:	输出】       *pDstBuf ： 总贞内容 ，  pDstLen ：总贞长度 
//【返回值	】     正确：DACK_SUCESS   错误：DACK_FAILURE   
//【全局变量】       
//【特殊说明】           
//【开发者	】  赵震   【日期】 2016年6月29日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INT8U DecodeReadAmtAdd(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT Stu_Dtl2007 &DstDecode2007DataFrame);

//-------------------------------------------------
//【函数名称】INT8U CheckFull645All(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT Stu_Dtl2007 &DstDecode2007DataFrame,TH_OUT INT8U &vDstFcnt,TH_OUT INT8U &vDstFctFg)
//【函数功能】     检测是否为645协议，以及长度
//【参数说明】        
//【I:	输入】     *vSrcBuf ：解码贞内容   ， vSrcLen ：解码贞长度                 
//【O:	输出】   pDstLen： 包含645帧的总长度
//【返回值	】     正确：DACK_SUCESS   错误：DACK_FAILURE   
//【全局变量】       
//【特殊说明】           
//【开发者	】  赵震   【日期】 2016年6月29日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INT8U Check645Full(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT INT16U &vDstLen);	

//-------------------------------------------------
//【函数名称】INT8U Check645Num(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT INT16U &vNum,TH_OUT INT8U *plenBuf);
//【函数功能】    检测并发 645帧的个数 长度
//【参数说明】        
//【I:	输入】     *vSrcBuf ：解码贞内容   ， vSrcLen ：解码贞长度                 
//【O:	输出】  vNum 帧的个数 ,plenBuf帧的 长度
//【返回值	】     正确：DACK_SUCESS   错误：DACK_FAILURE   
//【全局变量】       
//【特殊说明】           
//【开发者	】  赵震   【日期】 2016年8月16日
//【描  　述】 原始版本
//-------------------------------------------------
//【修改人	】     【日期】
//【描  　述】
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INT8U Check645Num(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT INT8U &vNum,TH_OUT INT16U *plenBuf);

};



#endif

