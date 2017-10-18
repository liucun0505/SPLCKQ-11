#ifndef _QGDW376_2_H
#define _QGDW376_2_H

#include "User_Mcu_Cfg.h"
#include "User_Ack_Def.h"
#include "User_App_Cfg.h"
//约定的定义
//#define DMACADD_LEN    6
#define DZB_MAXZJ_CNT    3    
#define D376_2_ZQ_MAXNUM 4 //中继的最大个数
#define D376_2_NODATALEN   (12+(2+D376_2_ZQ_MAXNUM)*6)//除了数据帧以外的数据长度
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
//常用下行信息区的定义 CON  
typedef struct 
{
	INT8U      s_Con_ComMode: 6;       // D5～D0: 3	宽带载波通信	指采用电力线宽带载波通信
	INT8U      s_Con_PRM:  1;          //Con中的启动标志位 0：集中器  1：通信模块
	INT8U      s_Con_DIR:  1;          //Con中的传输方向 0：从动站 1：主动站
} sPartQGDW376_2_Con;

typedef struct 
{
	//0:1
	INT8U      s_Msg_RouterFlag:  1;         // 路由标识：D0=0表示通信模块带路由或工作在路由模式，D0=1表示通信模块不带路由或工作在旁路模式?
	INT8U      s_reserved_1:      1;         //保留
	INT8U      s_Msg_ComFlag:     1;         //信息域中的通信模标识，Buf[0]的D2
	INT8U      s_reserved_2:      5;         //保留
	//1:1
	INT8U      s_chanle_num:      4;         //信道标识：取值0～15，0表示不分信道、1～15依次表示第1～15信道。
  INT8U      s_errcode:         4;
	//2:1
	INT8U      s_ackbyte;
	//3:2
	INT16U     s_rateFlag;                   // 	通信速率：表示通信波特率，BIN格式，0表示默认通信速率。
	
} sPartQGDW376_2_HeadDownMsg;//下行帧的头帧，请求帧


typedef struct 
{

	//0:1
	INT8U      s_Msg_RouterFlag:  1;         // 路由标识：D0=0表示通信模块带路由或工作在路由模式，D0=1表示通信模块不带路由或工作在旁路模式?
	INT8U      s_reserved_1:      1;         //保留
	INT8U      s_Msg_ComFlag:     1;         //信息域中的通信模标识，Buf[0]的D2
	INT8U      s_reserved_2:      5;         //保留
	//1:1
	INT8U      s_chanle_num:      4;         //信道标识：取值0～15，0表示不分信道、1～15依次表示第1～15信道。
  INT8U      s_reserved_3:      4;
	//2:1
	INT8U      s_Msg_phase:       4;         //	实测相线标识：实测从节点逻辑主信道所在电源相别，0为不确定，1～3依次表示相别为第1相、第2相、第3相。
  INT8U      s_Meter_flag:      4;         //电表通道特征：描述目的节点电表通道的特征，取值范围0～15，0保留，1为物理信道为单相供电，逻辑信道为单信道；2为物理信道为                                                //单相供电，逻辑信道为两信道；3为物理信道为单相供//电，逻辑信道为三信道；4为物理信道为三相供电，逻辑信道为三信道。
  //3: 1
	INT8U      s_CmdCsq:          4;         //信号品质：分为15级，取值范围0～15，0表示无信号品质，1表示最低品质。(能查到，变更不通知)
  INT8U      s_AckCsq:          4;
	//4: 1
	INT8U      s_Msg_Event:       1;         //事件标志：D0为0时无上报事件，D0为1时有上报事件。
	INT8U      s_reserved_4:      7;         //保留
	

	
} sPartQGDW376_2_HeadUpMsg;//下行帧的头帧，请求帧

typedef struct 
{
	union
	{
    sPartQGDW376_2_Con  s_conBit;
		INT8U s_conByte;
	} u_con;
	union
	{
	  sPartQGDW376_2_HeadUpMsg    s_UpMsgBit;
	  sPartQGDW376_2_HeadDownMsg  s_DownMsgBit;//5个字节除了SEQ
		INT8U  s_msgbuf[5];
	} u_msg;
	INT8U      s_Msg_Seq;           //信息域中报文序列号
	INT8U      s_MainAddBuf[DMACADD_LEN];   //主结点地址，源地址
	INT8U      s_RelayAddbuf[DMAC_RELAY_LEN];//中继地址,可用于并发抄表中的多节点单帧
  INT8U      s_DestAddBuf[DMACADD_LEN];//目得地址
  INT8U      s_AFN;            //应用功能码
	INT16U     s_FN;             //数据单元标识
} sPartQGDW376_2_Head;//帧头

typedef struct 
{
  sPartQGDW376_2_Head  s_head;
	INT8U      s_RcvDataBuf[D376_MAXRCVBUFLEN];//接收数据区指针，高危指针，用前要检查是否有值，要指向合法空间
	INT16U     s_RcvDataLen;//接收数据的个数
	INT8U      s_SendDataBuf[D376_MAXSENDBUFLEN];//发送数据区指针，高危指针，用前要检查是否有值，要指向合法空间
	INT16U     s_SendDataLen;//实际发送数据区的长度。
	INT16U     s_SendDataBufMaxLen;//发送数据区的最大可用长度。
} sPartQGDW376_2CreatFrame;//组帧的结构

typedef struct 
{
  sPartQGDW376_2_Head  s_head;
	INT8U      *s_RcvDataBuf;//接收数据区指针，高危指针，用前要检查是否有值，要指向合法空间
	INT16U     s_RcvDataLen;//接收数据的个数
} sPartQGDW376_2DeCodeFrame;//组帧的结构

typedef struct 
{
	sPartQGDW376_2DeCodeFrame   s_Frame;
	INT8U Port;
	
}sPartQGDW376_2_Data;

//------组成的376.2发送帧，主要是串口中用，只保存有用的信息，其他不保存
typedef struct 
{
  INT8U      s_Msg_Seq;           //信息域中报文序列号
	INT8U      s_SendDataBuf[D376_MAXSENDBUFLEN];//发送数据区指针，高危指针，用前要检查是否有值，要指向合法空间
	INT16U     s_SendDataLen;//实际发送数据区的长度。
} sQGDW376_2UpFrame;//组帧的结构

class cQGDW376_2
{
public:
//-----------------------------------------------------------------------------
//name : sPartQGDW376_2_Head  Init376_2UpFrame(INT8U MsgComFg,INT8U *vDestAddBuf,INT8U vSrcAfn,INT16U vSrcFn);
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
	sPartQGDW376_2_Head Init376_2UpFrame(TH_IN  INT8U MsgComFg,TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn);
	
//-----------------------------------------------------------------------------
//sPartQGDW376_2_Head Creat376_2UpFrameFormDownFrame(sPartQGDW376_2_Head  downframe);
//Function:组建上行帧格式
// 参数描述:
//   Input：
//        downframe-----------------下行帧
//   output:
//        
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
	sPartQGDW376_2_Head Creat376_2UpFrameFormDownFrame(TH_IN const sPartQGDW376_2_Head  downframe);
	
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
//name :  INT8U cQGDW376_2::Code376_2(sPartQGDW376_2_Up SrcCodeDataFrame)
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
    INT8U  Code376_2_Frame(TH_INOUT  sPartQGDW376_2CreatFrame &SrcCodeDataFrame);



//----------------------------------------------------------------------------------
//name :  INT8U Code376_2_UpFrame(TH_IN  INT8U MsgComFg,TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,INT8U *pSrcRcvBuf,INT16U vSrcRcvLen,TH_OUT  sQGDW376_2UpFrame &sQGDW376_2UpFrame)
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
    INT8U  Code376_2_UpFrame(TH_IN  INT8U MsgComFg,TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,TH_IN INT8U *pSrcRcvBuf,TH_IN INT16U vSrcRcvLen,TH_OUT  sQGDW376_2UpFrame &sQGDW376_2UpFrame);
		
//----------------------------------------------------------------------------------------------------------
//name : INT8U Decode376_2Frame(const INT8U *pSrcBuf,const INT16U vSrcLen,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
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
   INT8U  Decode376_2Frame(TH_IN  INT8U *pSrcBuf,TH_IN  INT16U vSrcLen,TH_OUT  sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame);
};
#endif

