#ifndef _QCSG376_2_H
#define _QCSG376_2_H

#ifdef DSYSCFG_STD_CSG //南网标准

#include "User_Mcu_Cfg.h"
#include "User_Ack_Def.h"
#include "User_App_Cfg.h"
#include "User_DataFmt_Def.h"
//约定的定义

#define D376_2_MIN_FRAME_LEN        12   //6字节的固定长度和用户数据长度(最少6字节)
#define D376_2_NODATALEN            (D376_2_MIN_FRAME_LEN + 12)//除了数据帧以外的最大数据长度


//#define DMACADD_LEN    6
#define DZB_MAXZJ_CNT    3    
#define D376_2_ZQ_MAXNUM 4 //中继的最大个数

//#define DTMPZBBUFLEN     20//临时编码BUF长度是100
//操作类的定义
#define DBIT_376_2Msg_MDFLAG  Bit2//通信模块标识
#define DBIT_376_2Con_DIR     Bit7//Con中的传输方向 0
#define DBIT_376_2Con_PRM     Bit6//Con中的启动标志位
//常用值的定义 CON
#define DV376_2CON_COM_MODE     3 // D5～D0: 3	宽带载波通信	指采用电力线宽带载波通信
#define DV376_2CON_PRM_MASTER   1   //D6:PRM =1：表示此帧报文来自启动站；PRM =0：表示此帧报文来自从动站。
#define DV376_2CON_PRM_SLAVE    0
#define DV376_2CON_DIR_COMMD    1  //D7 DIR=0：表示此帧报文是由集中器发出的下行报文；DIR=1：表示此帧报文是由通信模块发出的上行报文。

//--------------信息区---------------------------------------------------------------------------------------
//D7	D6	D5	D4	D3	    D2            	D1	         D0	           BS   1
//     中继级别	         |   冲突检测   | 通信模块标识	|附属节点标识	|      路由标识		
//D7	D6	D5	D4	D3	    D2	                 D1	         D0	           BS	1
//        纠错编码标识	 |        信道标识
//D7-------------------------------------------------------------------------------D0		
//         预计应答字节数	                                                                   BIN	1
//D15	          D14?    D0	                                                                   BS	2
//速率单位标识	 |通信速率	
//D7-------------------------------------------------------------------------------D0		
//       报文序列号                                                                                 BIN	1	
//------------------------------------------------------------------------------------------------------------------	
#define DV376_2MSG_ROUTERFLAG_ON         1 // 路由标识：D0=0表示通信模块带路由或工作在路由模式，D0=1表示通信模块不带路由或工作在旁路模式。
#define DV376_2MSG_ROUTERFLAG_OFF        0 // 
#define DV376_2MSG_NODE_ON             1 // 附属节点标识：指从节点附属节点标识，0表示无附加节点，1表示有附加节点。
#define DV376_2MSG_NODE_OFF            0 
#define DV376_2MSG_COMFLAG_MASTER      1 //通信模块标识：0表示对主节点的操作，1表示对从节点操作
#define DV376_2MSG_COMFLAG_E_SLAVE     0 
#define DV376_2MSG_EVENT_ON            1 //事件标志：D0为0时无上报事件，D0为1时有上报事件。
#define DV376_2MSG_EVENT_OFF           0 // 
#define DV376_2MSG_PHASE_0             0 // 
#define DV376_2MSG_PHASE_1             1 // 
#define DV376_2MSG_PHASE_2             2 // 
#define DV376_2MSG_PHASE_3             3 // 

#define DV376_2MSG_ADDFLAG_MASTER      0 //通信模块标识：0表示对主节点的操作，1表示对从节点操作
#define DV376_2MSG_ADDFLAG_SLAVE       1 

//常用下行信息区的定义 CON  
typedef struct 
{
	INT8U      s_Con_reserved: 3;       // D2～D0: 保留
	INT8U      s_Con_VER:  2;           // D4~D3： 版本号
	INT8U      s_Con_ADD:  1;           //地址域标识
	INT8U      s_Con_PRM:  1;          //Con中的启动标志位 0：集中器  1：通信模块
	INT8U      s_Con_DIR:  1;          //Con中的传输方向 0：从动站 1：主动站
} sPartQCSG376_2_Con;

typedef struct 
{
	union
	{
    	sPartQCSG376_2_Con  s_conBit;
		INT8U s_conByte;
	} u_con;

	INT8U      s_MainAddBuf[DMACADD_LEN];   //主结点地址，源地址
	INT8U      s_RelayAddbuf[DMAC_RELAY_LEN];//中继地址,可用于并发抄表中的多节点单帧
  	INT8U      s_DestAddBuf[DMACADD_LEN];//目得地址
  	INT8U      s_AFN;            //应用功能码
	INT8U      s_Msg_Seq;        //报文序列号
	INT32U     s_FN;             //数据单元标识
} sPartQCSG376_2_Head;//帧头

typedef struct 
{
  	sPartQCSG376_2_Head  s_head;
	INT8U      s_RcvDataBuf[D376_MAXSENDBUFLEN];//接收数据区指针，高危指针，用前要检查是否有值，要指向合法空间
	INT16U     s_RcvDataLen;//接收数据的个数
} sPartQCSG376_2CreatFrame;//组帧的结构


typedef struct 
{
  	sPartQCSG376_2_Head  s_head;
	INT8U      s_RcvDataBuf[D376_MAXRCVBUFLEN];//接收数据区指针，高危指针，用前要检查是否有值，要指向合法空间
	INT16U     s_RcvDataLen;//接收数据的个数
} sPartQCSG376_2DeCodeFrame;//组帧的结构

typedef struct 
{
	sPartQCSG376_2DeCodeFrame   s_Frame;
	INT8U Port;
	
}sPartQCSG376_2_Data;

//------组成的376.2发送帧，主要是串口中用，只保存有用的信息，其他不保存
typedef struct 
{
  INT8U      s_Msg_Seq;           //信息域中报文序列号
	INT8U      s_SendDataBuf[D376_MAXSENDBUFLEN];//发送数据区指针，高危指针，用前要检查是否有值，要指向合法空间
	INT16U     s_SendDataLen;//实际发送数据区的长度。
} sQCSG376_2UpFrame;//组帧的结构

class cQCSG376_2
{
public:
	INT8U  Code376_2_FromOnHead(TH_IN const sPartQCSG376_2_Head  gframehead,TH_IN INT8U *vRcvBuf,TH_IN const INT16U Len,sCodeComCmdFrame  &CmdFrame);
	INT8U  CodePart376_2_FormDownHead(TH_IN const sPartQCSG376_2_Head  vSrcDownFameHead,const INT8U *pSrcFirstBuf,INT16U vFirstLen,INT8U *vSrcSecBuf,INT16U vSrcSecLen,sCodeComCmdFrame  &CmdFrame);
	INT8U  CodePart376_2_Frame(TH_INOUT sPartQCSG376_2CreatFrame SrcCodeDataFrame,const INT8U *pSrcFirstBuf,INT16U vFirstLen,sCodeComCmdFrame  &CmdFrame);
	sPartQCSG376_2_Head Init376_2UpFrameNoMacAdd(TH_IN  INT8U MsgComFg, TH_IN INT8U vSrcAfn, TH_IN INT32U vSrcFn);
	INT8U Code376_2_FromDownHead(TH_IN const sPartQCSG376_2_Head  gframehead,TH_IN INT8U *vRcvBuf,TH_IN const INT16U Len,sCodeComCmdFrame  &CmdFrame);
	INT8U ErrCodeTran(INT8U ErrType);
	INT8U  CodeAckOkFame(TH_IN const sPartQCSG376_2_Head  vSrcDownFameHead,sCodeComCmdFrame  &CmdFram);
	INT8U  CodeAckNoFame(TH_IN const sPartQCSG376_2_Head  vSrcDownFameHead,TH_IN const INT8U ErrType,sCodeComCmdFrame  &CmdFrame);
//-----------------------------------------------------------------------------
//name : sPartQCSG376_2_Head  Init376_2UpFrame(INT8U MsgComFg,INT8U *vDestAddBuf,INT8U vSrcAfn,INT32U vSrcFn);
//Function:上行帧格式
// 参数描述:
//   Input：
//        MsgComFg-----------------信息域中的通信模标识
//        vSrcAfn------------------AFN
//        vSrcFn-------------------Fn
//   output:
//        &vDestAddBuf:  目的地址
//Return:
//        sPartQGDW376_2_Head 结构体
//全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//描   　述: 原始版本
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	sPartQCSG376_2_Head Init376_2UpFrame(TH_IN  INT8U MsgComFg,TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn);
	
//-----------------------------------------------------------------------------
//sPartQCSG376_2_Head Creat376_2UpFrameFormDownFrame(sPartQCSG376_2_Head  downframe);
//Function:组建上行帧格式
// 参数描述:
//   Input：
//        downframe-----------------下行帧
//   output:
//        
//Return:
//        sPartQCSG376_2_Head 结构体
//全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//描   　述: 原始版本
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	sPartQCSG376_2_Head Creat376_2UpFrameFormDownFrame(TH_IN const sPartQCSG376_2_Head  downframe);
	
//----------------------------------------------------------------------------------
//name :  INT8U cQGDW376_2::Creat376_2Cs(const INT8U *vSrcBuf,INT16U vSrcLen)
//Function:生成CS
// 参数描述:
//    Input：
//        vSrcBuf: Cs帧地址
//   　　SrcLen：长度
//    Return:
//        ＣＳ值　
//全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//描   　述: 原始版本
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:
//描   　述:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
INT8U Creat376_2Cs(TH_IN const INT8U *vSrcBuf,TH_IN INT16U vSrcLen);

//-----------------------------------------------------------------------------
//name : INT8U  Check_376_2_Full(const INT8U *pSrcBuf,INT16U vSrcLen,INT16U &vDstLen))
//Function:检测pSrcBuf帧是否是完整的376.2的帧,不判断CS是否正确
// 参数描述:
//   Input：
//        pSrcBuf-----------------收到的帧数据
//        vSrcLen-----------------收到的帧长度  
//   output:
//        &vDstLen:  376.2帧的结束地址。
//Return:
//        ack: DACK_ERR_NULL，DACK_SUCESS
//全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//描   　述: 原始版本
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  INT8U Check_376_2_Full(TH_IN const INT8U *pSrcBuf,TH_IN  INT16U vSrcLen,TH_OUT  INT16U &vDstLen);

//----------------------------------------------------------------------------------
//name :  INT8U cQCSG376_2::Code376_2(sPartQCSG376_2_Up SrcCodeDataFrame)
//Function:将上行报文的数据或下行报文的数据组成帧  
// 参数描述:
//    InOutput：
//        SrcCodeDataFrame: 见定义，

//Return:
//        ack: DACK_ERR_BUF，DACK_SUCESS
//全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//描   　述: 原始版本
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    INT8U  Code376_2_Frame(TH_INOUT  sPartQCSG376_2CreatFrame SrcCodeDataFrame,sCodeComCmdFrame  &CmdFrame);



//----------------------------------------------------------------------------------
//name :  INT8U Code376_2_UpFrame(TH_IN  INT8U MsgComFg,TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,INT8U *pSrcRcvBuf,INT16U vSrcRcvLen,TH_OUT  sQCSG376_2UpFrame &sQCSG376_2UpFrame)
//Function:将上行报文的数据或下行报文的数据组成帧  
// 参数描述:
//   Input：
//        MsgComFg-----------------信息域中的通信模标识
//        pSrcAddBuf------------目标地址
//        vSrcAfn------------------AFN
//        vSrcFn-------------------Fn
//        pSrcRcvBuf -------------收到的数据源
//        vSrcRcvLen -------------收到的数据长度
//   output:
//        &sQGDW376_2UpFrame:  

//Return:
//        ack: DACK_ERR_BUF，DACK_SUCESS
//全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//描   　述: 原始版本
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    INT8U  Code376_2_UpFrame(TH_IN  INT8U MsgComFg,TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,TH_IN INT8U *pSrcRcvBuf,TH_IN INT16U vSrcRcvLen,TH_OUT  sQCSG376_2UpFrame &sQCSG376_2UpFrame);
		
//----------------------------------------------------------------------------------------------------------
//name : INT8U Decode376_2Frame(const INT8U *pSrcBuf,const INT16U vSrcLen,sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame)
//Function:将一帧报文进行解码
// 参数描述:
//    Input：
//        pSrcBuf-----------------收到的帧数据
//        vSrcLen-----------------收到的帧长度    
//    Output:
//        DstDecodeDataFrame--------返回结构体
//Return:
//        ack: DACK_ERR_NULL,DACK_ERR_CS,DACK_SUCESS
//全局变量: 无
//创 建  人: 杨虎岳
//日     期: 2006年6月16日
//描   　述: 原始版本
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   INT8U  Decode376_2Frame(TH_IN  INT8U *pSrcBuf,TH_IN  INT16U vSrcLen,TH_OUT  sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame);
//----------------------------------------------------------------------------------------------------------
//name : INT8U GetADDFlag(INT32U di)
//Function:根据数据标识判断地址标志
// 参数描述:
//    Input：
//        di-----------------数据标识
//    Output:
//        
//Return:
//        返回地址标志
//全局变量: 无
//创 建  人:  
//日     期: 2017年3月12日
//描   　述: 原始版本
//-------------------------------------------------------------------------------------------------------
//修改人:
//日　期:

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   INT8U  GetADDFlag(INT32U di);
};
#endif //DSYSCFG_STD_CSG
#endif

