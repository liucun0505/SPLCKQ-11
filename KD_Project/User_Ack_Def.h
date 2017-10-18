#ifndef _USER_ACK_H
#define _USER_ACK_H
//返回类型定义
#define		DACK_SUCESS					0x00	//成功
#define DACK_EER_OVERTIME 				0xA0//通信超时
#define DACK_EER_INVALID 					0x01//无效数据单元
#define	DACK_EER_LENERR						0x02//长度错误
#define	DACK_ERR_CS								0x03//校验错误
#define	DACK_EER_NO_AFNFN					0x04//信息类不存在    DACK_EER_NO_AFNFN
#define	DACK_ERR_FORMAT						0x05//格式错误
#define	DACK_EER_METERREPEAT			0x06//表号重复
#define	DACK_EER_METERNOFIND			0x07//表号不存在
#define	DACK_EER_METERNOACK				0x08//电表应用层无应答
#define	DACK_EER_CCO_BUSY					0x09//主节点忙					DACK_EER_CCO_BUSY
#define	DACK_EER_CCOCANNOTDO			0x0A//主节点不支持此命令
#define	DACK_EER_STANOACK					0x0B//从节点无应答
#define	DACK_EER_STAOUTNET				0x0C//从节点不在网
//并发扩展
#define	DACK_OVER376_2NUM					109//超过最大并发数
#define	DACK_OVER645NUM						110//645报文个数超限
#define	DACK_INREADING						111//此表正在抄读中

#define		DACK_FAILURE								19		//失败
#define		DACK_ERR_NULL								20		//空帧，长度少于13
#define		DACK_2_ERR_FAME							21		//帧错误，长度，少半帧
#define		DACK_ERR_BUF								22		//BUF不够
#define		DACK_ERR_FULL								23		//BUF满
#define		DACK_ERR_MSG								24		//消息不一致
#define		DACK_ERR_PRO								25		//进程要注销
#define		DACK_ERR_DELPRO							26		//进程要注销
#define		DACK_ERR_NODE_FULL					27		//结点满了
#define		DACK_ERR_NODE_NOFIND				28		//没有找到结点
#define		DACK_ERR_NODE_ERR						29		//结点异常末知原因，不应该出来些错误
#define		DACK_ERR_RAM_ERR						30		//结点异常末知原因，不应该出来些错误
#define		DACK_EER_MNODE_FOMFATNOBCD	31		//表从节点非BCD
#define		DACK_EER_MNODE_FOMFATBROAD	32		//表从节点是广播
#define		DACK_EER_MNODE_NOFIND				33		//表从节点没有找到
#define		DACK_EER_MNODE_REPEAT				34		//表从节点重添加
#define		DACK_EER_PCT								35		//协议错误
#define		DACK_EER_IN_LEN							36		//输入数组的长度不够
#define		DACK_EER_FLASH					  	37		//FALSH错误
//#define		DACK_EER_CCO_BUSY	 					38		//CCO忙
#define		DACK_EER_HEADPORT						39		//PLC接收报文的端口号错误
#define		DACK_EER_ID									40		//PLC接收报文的ID错误
#define		DACK_EER_HEADPCT				41		//PLC接收报文的报文头长度或协议版本号错误
#define		DACK_EER_ACKSTA							42		//PLC接收报文的抄表上行报文应答状态错误
#define		DACK_EER_EVENTFUNC					43		//事件的功能码错误
#define		DACK_EER_DIR								44		//传输方向错误
#define		DACK_EER_START							45		//起动位错误
#define		DACK_EER_REGPA							46		//从节点注册参数错误
#define		DACK_EER_DEVICETYPE					47		//产品类型错误
#define	    DACK_EER_CCOADD_REPEAT				48		//主节点地址重复设置
#endif

