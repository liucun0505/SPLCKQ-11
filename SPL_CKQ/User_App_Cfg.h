#ifndef _USER_APP_H
#define _USER_APP_H
//--配制
//--参数
//--常量
#include "User_Mcu_Cfg.h"
//#define DSYSCFGWORKTYPE_CCO 
#ifdef DSYSCFGWORKTYPE_CCO
//---系统配置-----
const INT8U   SYSCFGWORKTYPE = 1;               //CCO 模式
#endif 

#ifdef DSYSCFGWORKTYPE_STA
const INT8U   SYSCFGWORKTYPE = 0;               //STA模式
#endif 

//#define ALIGN4BYTE(x)   (if(x%4)  (x) : (((x/4)+1)*4))
#define FLASH_SECTOR_CONTENT 4096
//--参数
const INT16U	 FILETRAN_FINISH_WAIT_TIME		= 60;		//单位S 升级操作等待时间：终端发送完最后一个升级数据包后，需要等待模块完成升级的时间长度?
//---------抄表相关----------
const INT16U	 READMETER_MAXDLY_TIME  = 60000; //单位MS
const INT16U	 PLCACK_MAXDLY_TIME  = 60000; //单位MS
const INT16U	 PLCFRAME_DLY_TIME =   5;//单播延时时间 单位MS
const INT16U   FARME376_2_UARTBYTE_DLYTIME = 20 ;//字节延时 单位MS
const INT16U   FRAME376_2_UARTFRAME_DLYTIME=200;//帧延时 单位MS?
const INT16U   FARME645_UARTBYTE_DLYTIME = 20 ;//字节延时 单位MS
const INT16U   FRAME645_UARTFRAME_DLYTIME=5000;//zz 测试一下 =200;//帧延时 单位MS?
const INT8U    FRAME645_RESEND_MAXCNT    = 3;//645重发的最大次数
const INT16U   CFG_UART_WAITACK_MAXDLYTIME = 20;//MS 通用串口最大等待时间// zz 测试一下 =20;//帧延时 单位MS?
//--配制----
const INT8U   CFG_READMETERPROCESS_MAXNUM = 16;//最多支持抄表进程数，并发，13F1，02F1.
const INT8U   CFG_READMETERPROCESS_MODE   =  0;////操作模式  0：满时不清以前的，提示 DACK_ERR_NODE_FULL， 1：满时要清以前的,提示成功，做错误统计 

//--常量-------抄表口定义----------
const INT8U PORT_UART = 0x00;	//串口
const INT8U PORT_PLC = 0x01;	//plc口
const INT8U PORT_CONSOLE = 0x02;	//控制台口
//-------------地址长度定义-----------
const INT8U		MAIN_ADD_LEN			= 6;
const INT8U		METER_ADD_LEN			= 6;
const INT8U   MAC_LEN  =  METER_ADD_LEN;
//const INT8U   DMACADD_LEN = MAC_LEN;
//------------系统相关结束--------------------

//------376.2帧的相关的定义----------
//--常量
//const INT16U	 FRAME376_2_MAX_LEN		= 1200;		//最大支持的376.2报文长度
//const INT8U 	PARALLEL376_2_MAX_CNT = 13;     //最大并发帧个数
//const INT8U 	PARALLEL645_MAX_LEN  = 40;     //并发帧 645每帧回复平均最大长度

//---645协议部分---------------------
//--常量
//const INT16U	 FRAME645_MAX_LEN	 = 254;
//const INT16U	 DATA645_MAX_LEN	 = FRAME645_MAX_LEN-16;//254-12(645格式)-4(FE)

//----从节点相关下定义----
const INT16U	METERNODE_MAXNUME		= 1024;											//
//--常量
const INT8U		METERNODE_ADDADD		= 0;	//从节点地址
const INT8U		METERNODE_ADDLEN		= METER_ADD_LEN;
const INT8U		METERNODE_PCTADD		= METERNODE_ADDADD+METERNODE_ADDLEN;	//协议
const INT8U		METERNODE_PCTLEN		= 1;
const INT8U		METERNODE_CJQSEQADD		= METERNODE_PCTADD+METERNODE_PCTLEN;	//采集器的seq
const INT8U		METERNODE_CJQSEQLEN		= 2;
const INT8U		METERNODE_DATALEN		= METERNODE_CJQSEQADD+METERNODE_CJQSEQLEN;	//从节点在flash中的存储长度	地址(6)+协议(1)+crc校验(1)
const INT8U		METERNODE_RESERVED		= 7;	//每个从节点存flash预留7字节,存flash地址必须4字节对齐
const INT16U	METERNODE_FLASHONELEN	= (METERNODE_DATALEN+METERNODE_RESERVED);	//每个从节点存flash长度为16，存flash地址必须4字节对齐
const INT16U	METERNODE_ONEFLASH_NUM	= (FLASH_SECTOR_CONTENT/METERNODE_FLASHONELEN);		//每个扇区可存的从节点个数
const INT8U		METERNODE_FALSHSECT		= ((METERNODE_MAXNUME/METERNODE_ONEFLASH_NUM)+1+1);	//需要的扇区个数
const INT8U		CRCLEN					= 2;

//采集器flash定义
const INT16U	CFG_CJQ_MAXNUME			= 1024;		//搜到的采集器的最大个数
const INT8U		CFG_CJQ_LIST_MAXNUM		= 32;	//采集器下搜表的最大个数

const INT8U		CJQFLASH_ADDADD			= 0;	//采集器地址
const INT8U		CJQFLASH_ADDLEN			= METER_ADD_LEN;	//采集器地址长度
const INT8U		CJQFLASH_DATALEN		= CJQFLASH_ADDADD+CJQFLASH_ADDLEN;	//采集器所有数据长度
const INT8U		CJQFLASH_RESERVED		= 2;
const INT16U	CJQFLASH_FLASHONELEN	= CJQFLASH_DATALEN+CJQFLASH_RESERVED;	//8个字节
const INT16U	CJQFLASH_ONEFLASH_NUM	= (FLASH_SECTOR_CONTENT/CJQFLASH_FLASHONELEN);	//每个扇区可存的从节点个数
const INT8U		CJQFLASH_FALSHSECT		= ((CFG_CJQ_MAXNUME/CJQFLASH_ONEFLASH_NUM)+1+1);



//----------搜表模块-----------------------------------------------------------
//--参数
const INT32U  PA_SEARCHMETER_QUE_INVALTIME = 10;//单位分钟， 查询从节间注册状态的间隔时间
const INT16U  PA_SEARCHMETER_ON_ReDly_TIME =300;//单位 MS AFN=06F2的等确认的最长时间。
const INT8U   PA_SEARCHMETER_ON_ReDly_NUM = 3;//AFN=06F2的无确认的重发次数。
const INT8U   PA_SEARCHMETER_FORCRACKFG = 0;//下行查询搜表结果中的强行应答标志
//--配制
const INT16U	CFG_SEARCHBLACK_MAXNUME    = 1024;	//搜到黑名单的最大个数，即不在白名单的从节点
const INT16U	CFG_SEARCHMETER_MAXNUME		= 1024;		//搜表的最大个数

const INT8U   PA_STA_SEARCH_MAXTIME = 120;//单位分钟，搜表的最长时间
//--常量
const INT8U   PRODUCTTYPE_METER  = 0; // 产品类型中的电表
const INT8U   PRODUCTTYPE_CJQ  = 1;// 产品类型中的采集器

//const INT8U		SEARCHMETER_NODELEN		= 8;	//上报从节的信息
//const INT8U		SEARCHMETER_CJQSEQ		= 2;
//const INT8U		SEARCHMETER_CARD_LEN	= SEARCHMETER_NODELEN+SEARCHMETER_CJQSEQ;
//const INT16U	SEARCHMETER_ONEFLASH_NUM= (FLASH_SECTOR_CONTENT/SEARCHMETER_CARD_LEN);	//每个扇区可存的从节点个数
//const INT8U		SEARCHMETER_FALSHSECT	= ((CFG_SEARCHMETER_MAXNUME/SEARCHMETER_ONEFLASH_NUM)+1);


const INT8U		SEARCHFLASH_STAADDADD		= 0;	//STA地址在flash中的相对地址
const INT8U		SEARCHFLASH_STAADDLEN		= METER_ADD_LEN;	//STA地址长度 6
const INT8U		SEARCHFLASH_METERCNTADD		= SEARCHFLASH_STAADDADD+SEARCHFLASH_STAADDLEN;	//STA下电表总数量地址
const INT8U		SEARCHFLASH_METERCNTLEN		= 1;	//STA下电表总数量长度
const INT8U		SEARCHFLASH_STATYPEADD		= SEARCHFLASH_METERCNTADD+SEARCHFLASH_METERCNTLEN;	//STA类型，地址
const INT8U		SEARCHFLASH_STATYPELEN		= 1;	//STA类型，0电能表，1采集器 长度
const INT8U		SEARCHFLASH_METERADDADD		= SEARCHFLASH_STATYPEADD+SEARCHFLASH_STATYPELEN;	//STA下电表地址长度 6 地址
const INT8U		SEARCHFLASH_METERADDLEN		= METER_ADD_LEN;	//STA下电表地址长度 6  长度
const INT8U		SEARCHFLASH_METERTYPEADD	= SEARCHFLASH_METERADDADD+SEARCHFLASH_METERADDLEN;	//STA下电表协议类型  地址
const INT8U		SEARCHFLASH_METERTYPELEN	= 1;	//STA下电表协议类型	长度
const INT8U		SEARCHFLASH_RESERVEDADD		= SEARCHFLASH_METERTYPEADD+SEARCHFLASH_METERTYPELEN;	//搜表flash保留长度
const INT8U		SEARCHFLASH_RESERVEDLEN		= 1;	//搜表flash保留长度

const INT8U		SEARCHFLASH_DATALEN			= SEARCHFLASH_RESERVEDADD;	//搜表flash有效数据长度
const INT8U		SEARCHFLASH_ALLLEN			= SEARCHFLASH_DATALEN+SEARCHFLASH_RESERVEDLEN;	//搜表flash总长度

const INT16U	SEARCHFLASH_ONEFLASH_NUM	= (FLASH_SECTOR_CONTENT/SEARCHFLASH_ALLLEN);	//每个扇区可存的从节点个数
const INT8U		SEARCHFLASH_FALSHSECT		= ((CFG_SEARCHMETER_MAXNUME/SEARCHFLASH_ONEFLASH_NUM)+1);
//----------搜表模块--end---------------------------------------------------------	


//-------事件相关-------------------------------------
const INT8U   CFG_CCO_EVENT_RECNT = 5;//STA事件重发的次数
const INT32U  CFG_CCO_EVENT_OK_WAITTIME = 30*60*1000;//30分钟
const INT8U   CFG_CCOEVENT_MAXNUM = 30;//最多支持进程数
const INT8U   CFG_CCOEVENT_MODE = 0;////操作模式  0：满时不清以前的，提示 DACK_ERR_NODE_FULL， 1：满时要清以前的,提示成功，做错误统计 
const INT8U   CFG_CCOEVENT_REPORTMAXNUM = 60;//最多支持进程数

const INT8U   CFG_STA_EVENT_RECNT = 5;//STA事件重发的次数
const INT32U   CFG_STA_EVENT_MAX_WATITIME = 60*1000;//　６０S，STA事件 等待PLC确信的事件
const INT32U   CFG_STA_EVENT_ONE_WATITIME = 20*1000;// 20S STA事件重发的次数额外等待PLC确信的事件


//-------------------------------------------------------
//-----------PLC通信相关------------------
//--参数
const INT8U PA_PLC_INVAL_TIME = 20;		//单位 MS ，PLC发送数据间隔时间，
const INT8U PA_PLC_DATA_HEAD_LEN = 22;		//，PLC发送 接收 数据结构 头 长度
//-----------PLCAPP协议 相关------------------
//--配制
//--参数
const INT8U PLCAPPPCT_TIMEOUT = 10;		//抄表下行报文超时时间，单位100ms,先暂定1s=100*10
const INT8U PLCAPPPCT_MULTIME = 10;		//抄表下行报文并发报文间隔时间，单位10ms,先暂定100ms＝10*10
//--常量
const INT8U PLCAPPPCT_HEADPORT = 0x10;	//plc协议头端口号固定为0x10
const INT8U PLCAPPPCT_HEADCON = 0x00;	//plc协议头控制字固定为0x00
const INT8U PLCAPPPCT_NUM = 1;			//协议版本号现在都是1
const INT32U	PLCAPPPCT_RESERVED		= 0;		//保留位都写0
const INT32U	PLCAPPPCT_QUEREGPA		= 0;		//查询从节点注册中的从节点注册参数
const INT32U	PLCAPPPCT_STARTREGPA	= 1;		//起动从节点注册中的从节点注册参数
const INT32U	PLCAPPPCT_FORCEACK		= 0;		//起动从节点注册中的强制应答标志
const INT8U		PLCAPPPCT_ACKSTA		= 0;		//抄表上行报文应答状态
const INT8U		PLCAPPPCT_PCT_TRANSMIT	= 0;		//透明传输
const INT8U		PLCAPPPCT_PCT_97		= 1;		//97
const INT8U		PLCAPPPCT_PCT_07		= 2;		//07
const INT8U		PLCAPPPCT_EVENTOKDOWN	= 1;		//事件功能码下行，CCO应答确认给STA
const INT8U		PLCAPPPCT_EVENTENDOWN	= 2;		//事件功能码下行，CCO允许事件主动上报给STA
const INT8U		PLCAPPPCT_EVENTSTOPDOWN	= 3;		//事件功能码下行，CCO禁止事件主动上报给STA
const INT8U		PLCAPPPCT_EVENTFULLDOWN	= 4;		//事件功能码下行，CCO缓冲区满给STA
const INT8U		PLCAPPPCT_EVENTUP		= 1;		//事件功能码上行，STA主动上报事件给CCO
const INT8U		PLCAPPPCT_METER			= 0;		//电能表
const INT8U		PLCAPPPCT_COLLECTOR		= 1;		//采集器
const INT8U		PLCAPPPCT_EVENTDIR		= 0;		//事件下行方向位

//-----CCO相关-----------------------------------------
//--配制
const INT8U		CCOPAMSGRESERVED		= 16;		//CCO参数保存flash时预留16字节
//--参数------AFN03-F10----------
const INT8U AFN03F10_MAX_INVAL_TIME = 2;		//AFN03,F10上报无反回，重发的间隔时间  S
const INT8U AFN03F10_MAX_INVAL_NUN = 1;		//AFN03,F10上报无反回， 最大重发次数
//--常量
const INT8U AFN03F10_MAX_DATA_LEN = 41;	//AFN03,F10上报数据的长度
const INT8U AFN14F1_MAX_REQ_CNT = 3;
//--常量------主节点状态字和通信速率
const INT8U   CCOSTAWORD_RATENUM = 1;//速率数量n
const	INT8U   CCOSTAWORD_CHANNELTYPE = 2;//主节点信道特征：0表示微功率无线；1表示单相供电单相传输；2表示单相供电三相传输；3表示三相供电三相传输。
const	INT8U   CCOSTAWORD_METERTYPE = 0;//周期抄表模式：00表示通信模块对两种抄表模式都支持；01表示通信模块仅支持集中器主导的抄表模式?
																			    //10 表示通信模块仅支持路由主导的抄表模式。
const	INT8U   CCOSTAWORD_CHANNELNUM = 1;  //信道数量
const	INT16U  CCOSTAWORD_METERRATE = 0;//通信速率：表示通信波特率，BIN格式，0表示默认通信速率。
const	INT8U   CCOSTAWORD_METERRATEUNIT = 0;//速率单位：
const	INT8U   CCODISTURBSTA = 0;//注：干扰状态：0表示没有干扰，1表示有干扰。Lu_窄带东西，没用

//--常量-----通用----------------
const INT8U		ONLINEFG				= 1;		//上下线标志中的上线
const INT8U		OFFLINEFG				= 2;		//上下线标志中的下线


#endif

