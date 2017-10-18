#if !defined(AFX_USER_MCU_CFG1_H__31A0FA83_734C_4E3B_9698_11C33B66C503__INCLUDED_)
#define AFX_USER_MCU_CFG1_H__31A0FA83_734C_4E3B_9698_11C33B66C503__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// User_Mcu_Cfg1.h : header file
//
typedef unsigned char  BOOLEAN;                 /* 布尔变量                                 */
typedef unsigned char  INT8U;                   /* 无符号8位整型变量                        */
typedef signed   char  INT8S;                   /* 有符号8位整型变量                        */
typedef unsigned short INT16U;                  /* 无符号16位整型变量                       */
typedef signed   short INT16S;                  /* 有符号16位整型变量                       */
typedef unsigned int   INT32U;                  /* 无符号32位整型变量                       */
typedef signed   int   INT32S;                  /* 有符号32位整型变量                       */
#define Max376_2ReadLen  3072//254 lwc 自定义的时候数据超过1KB
#define DZB_MAXZJ_CNT    3                              
#define DTMPZBBUFLEN     20//临时编码BUF长度是100 
#define  ACKTRUE        TRUE
#define  ACKERR         FALSE
#define  ACKNULL        NULL
#define Bit0   0x00000001
#define Bit1   0x00000002
#define Bit2   0x00000004
#define Bit3   0x00000008
#define Bit4   0x00000010
#define Bit5   0x00000020
#define Bit6   0x00000040
#define Bit7   0x00000080
#define Bit8   0x00000100
#define Bit9   0x00000200
#define Bit10  0x00000400
#define Bit11  0x00000800
#define Bit12  0x00001000
#define Bit13  0x00002000
#define Bit14  0x00004000
#define Bit15  0x00008000
#define Bit16  0x00010000
#define Bit17  0x00020000
#define Bit18  0x00040000
#define Bit19  0x00080000
#define Bit20  0x00100000
#define Bit21  0x00200000
#define Bit22  0x00400000
#define Bit23  0x00800000
#define Bit24  0x01000000
#define Bit25  0x02000000
#define Bit26  0x04000000
#define Bit27  0x08000000
#define Bit28  0x10000000
#define Bit29  0x20000000
#define Bit30  0x40000000
#define Bit31  0x80000000


#define F1 0x0001
#define F2 0x0002
#define F3 0x0004
#define F4 0x0008
#define F5 0x0010
#define F6 0x0020
#define F7 0x0040
#define F8 0x0080

#define F9 0x0101
#define F10 0x0102
#define F11 0x0104
#define F12 0x0108
#define F13 0x0110
#define F14 0x0120
#define F15 0x0140
#define F16 0x0180

#define F17 0x0201
#define F18 0x0202
#define F19 0x0204
#define F20 0x0208
#define F21 0x0210
#define F22 0x0220
#define F23 0x0240
#define F24 0x0280

#define F25 0x0301
#define F26 0x0302
#define F27 0x0304
#define F28 0x0308
#define F29 0x0310
#define F30 0x0320
#define F31 0x0340
#define F32 0x0380

#define F33 0x0401
#define F34 0x0402
#define F35 0x0404
#define F36 0x0408
#define F37 0x0410
#define F38 0x0420
#define F39 0x0440
#define F40 0x0480

#define F41 0x0501
#define F42 0x0502
#define F43 0x0504
#define F44 0x0508
#define F45 0x0510
#define F46 0x0520
#define F47 0x0540
#define F48 0x0580

#define F49 0x0601
#define F50 0x0602
#define F51 0x0604
#define F52 0x0608
#define F53 0x0610
#define F54 0x0620
#define F55 0x0640
#define F56 0x0680

#define F57 0x0701
#define F58 0x0702
#define F59 0x0704
#define F60 0x0708
#define F61 0x0710
#define F62 0x0720
#define F63 0x0740
#define F64 0x0780

#define F65 0x0801
#define F66 0x0802
#define F67 0x0804
#define F68 0x0808
#define F69 0x0810
#define F70 0x0820
#define F71 0x0840
#define F72 0x0880

#define F73 0x0901
#define F74 0x0902
#define F75 0x0904
#define F76 0x0908
#define F77 0x0910
#define F78 0x0920
#define F79 0x0940
#define F80 0x0980

#define F81 0x0a01
#define F82 0x0a02
#define F83 0x0a04
#define F84 0x0a08
#define F85 0x0a10
#define F86 0x0a20
#define F87 0x0a40
#define F88 0x0a80

#define F89 0x0b01
#define F90 0x0b02
#define F91 0x0b04
#define F92 0x0b08
#define F93 0x0b10
#define F94 0x0b20
#define F95 0x0b40
#define F96 0x0b80

#define F97 0x0c01
#define F98 0x0c02
#define F99 0x0c04
#define F100 0x0c08
#define F101 0x0c10
#define F102 0x0c20
#define F103 0x0c40
#define F104 0x0c80

#define F105 0x0d01
#define F106 0x0d02
#define F107 0x0d04
#define F108 0x0d08
#define F109 0x0d10
#define F110 0x0d20
#define F111 0x0d40
#define F112 0x0d80


#define F113 0x0e01
#define F114 0x0e02
#define F115 0x0e04
#define F116 0x0e08
#define F117 0x0e10
#define F118 0x0e20
#define F119 0x0e40
#define F120 0x0e80

#define F121 0x0f01
#define F122 0x0f02
#define F123 0x0f04
#define F124 0x0f08
#define F125 0x0f10
#define F126 0x0f20
#define F127 0x0f40
#define F128 0x0f80

#define F129 0x1001
#define F130 0x1002
#define F131 0x1004
#define F132 0x1008
#define F133 0x1010
#define F134 0x1020
#define F135 0x1040
#define F136 0x1080

#define F137 0x1101
#define F138 0x1102
#define F139 0x1104
#define F140 0x1108
#define F141 0x1110
#define F142 0x1120
#define F143 0x1140
#define F144 0x1180

#define F145 0x1201
#define F146 0x1202
#define F147 0x1204
#define F148 0x1208
#define F149 0x1210
#define F150 0x1220
#define F151 0x1240
#define F152 0x1280

#define F153 0x1301
#define F154 0x1302
#define F155 0x1304
#define F156 0x1308
#define F157 0x1310
#define F158 0x1320
#define F159 0x1340
#define F160 0x1380

#define F161 0x1401
#define F162 0x1402
#define F163 0x1404
#define F164 0x1408
#define F165 0x1410
#define F166 0x1420
#define F167 0x1440
#define F168 0x1480

#define F169 0x1501
#define F170 0x1502
#define F171 0x1504
#define F172 0x1508
#define F173 0x1510
#define F174 0x1520
#define F175 0x1540
#define F176 0x1580

#define F177 0x1601
#define F178 0x1602
#define F179 0x1604
#define F180 0x1608
#define F181 0x1610
#define F182 0x1620
#define F183 0x1640
#define F184 0x1680

#define F185 0x1701
#define F186 0x1702
#define F187 0x1704
#define F188 0x1708
#define F189 0x1710
#define F190 0x1720
#define F191 0x1740
#define F192 0x1780


#define F193 0x1801
#define F194 0x1802
#define F195 0x1804
#define F196 0x1808
#define F197 0x1810
#define F198 0x1820
#define F199 0x1840
#define F200 0x1880

#define F201 0x1901
#define F202 0x1902
#define F203 0x1904
#define F204 0x1908
#define F205 0x1910
#define F206 0x1920
#define F207 0x1940
#define F208 0x1980

#define F209 0x1A01
#define F210 0x1A02
#define F211 0x1A04
#define F212 0x1A08
#define F213 0x1A10
#define F214 0x1A20
#define F215 0x1A40
#define F216 0x1A80

#define F217 0x1B01
#define F218 0x1B02
#define F219 0x1B04
#define F220 0x1B08
#define F221 0x1B10
#define F222 0x1B20
#define F223 0x1B40
#define F224 0x1B80

#define F225 0x1C01
#define F226 0x1C02
#define F227 0x1C04
#define F228 0x1C08
#define F229 0x1C10
#define F230 0x1C20
#define F231 0x1C40
#define F232 0x1C80

#define F233 0x1D01
#define F234 0x1D02
#define F235 0x1D04
#define F236 0x1D08
#define F237 0x1D10
#define F238 0x1D20
#define F239 0x1D40
#define F240 0x1D80

#define F241 0x1E01
#define F242 0x1E02
#define F243 0x1E04
#define F244 0x1E08
#define F245 0x1E10
#define F246 0x1E20
#define F247 0x1E40
#define F248 0x1E80

#define F249 0x1F01
#define F250 0x1F02
#define F251 0x1F04
#define F252 0x1F08
#define F253 0x1F10
#define F254 0x1F20
#define F255 0x1F40

#define F296 0x2480
#define F297 0x2501
#define F298 0x2502
#define F299 0x2504
#define  Max645DataLen  200
#define  ACKFAMEERR     1
#define  ACKTRUE        TRUE
#define  ACKERR         FALSE
#define  ACKNULL        NULL
#define  DPCT_97FG         0x01
#define  DPCT_2007FG       0x02

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
#define		DACK_EER_645DATA	 					38		//645数据错误
#define		DACK_EER_HEADPORT						39		//PLC接收报文的端口号错误
#define		DACK_EER_ID									40		//PLC接收报文的ID错误
#define		DACK_EER_HEADPCT				41		//PLC接收报文的报文头长度或协议版本号错误
#define		DACK_EER_ACKSTA							42		//PLC接收报文的抄表上行报文应答状态错误
#define		DACK_EER_EVENTFUNC					43		//事件的功能码错误
#define		DACK_EER_DIR								44		//传输方向错误
#define		DACK_EER_START							45		//起动位错误
#define		DACK_EER_REGPA							46		//从节点注册参数错误
#define		DACK_EER_DEVICETYPE					47		//产品类型错误
#define		DACK_EER_SEQERR				48		//SEQ不一致
#define		DACK_EER_645DI			    49		//645DI不一致
#define		DACK_EER_AMTADD				50		//表地址不一致

#define TH_INOUT 
#define TH_IN 
#define TH_OUT 

#define  DSYSTIMECMD  0xFFFE//定义读系统时间命令没有S
#define NCMDFG   0xFFFF//没有返回命令
#define  DSYSTIMELEN  5
#define AMMETERIDDI 0xc032//表号
#define AMMETERILEN 0x06
#define AUTORMD 0xc117//自动抄表日期 DDhh
#define AUTORMDLEN 2

//////////有无功脉冲常数
#define PPCONST 0xC030
#define QPCONST 0xC031
#define PPCONSTLEN 3
#define QPCONSTLEN 3

//瞬时有功功率
#define PPLEN 3
#define WPPG 0xB630
#define WPPA 0xb631
#define WPPB 0xb632
#define WPPC 0xb633
#define WPPF 0xb63f
#define WPPLEN 0x03
#define WPPFLEN 12
///瞬时无功功率
#if(BEIJINPCT_CMD645==1)
 #define WQPG 0xb660
 #define WQPA 0xb661
 #define WQPB 0xb662
 #define WQPC 0xb663
 #define WQPF 0xb66f
 #define WQPLEN 0x03
#else
 #define WQPG 0xb640
 #define WQPA 0xb641
 #define WQPB 0xb642
 #define WQPC 0xb643
 #define WQPF 0xb64f
 #define WQPLEN 0x03
#endif
 #define WQPFLEN 12
//瞬时功率因数
#define WSG 0xb650
#define WSA 0xb651
#define WSB 0xb652
#define WSC 0xb653
#define WSF 0xb65f
#define WSLEN 0x02
#define WSFLEN 8
//电压
#define WVA 0xb611
#define WVB 0xb612
#define WVC 0xb613
#define WVF 0xb61f
#define WVFLEN 6
#define WVLEN 0x02
//电流
#define WCA 0xb621
#define WCB 0xb622
#define WCC 0xb623
#define WCF 0xB62f
#if(GWPCTFG==0x07)
#define WCFLEN 9
#define WCLEN 0x03
#else
#define WCFLEN 6
#define WCLEN 0x02
#endif
//断相次数
#define BDG 0xb310//07无
#define BDA 0xb311
#define BDB 0xb312
#define BDC 0xb313
#define BDLEN 0x02
//断相计时间
#define BTG 0xb320//07无
#define BTA 0xb321
#define BTB 0xb322
#define BTC 0xb323
#define BTLEN 0x03
//第一次断相起始时刻
#define B1SKG 0xb330//07无
#define B1SKA 0xb331
#define B1SKB 0xb332
#define B1SKC 0xb333
#define B1SKLEN 0x04
//第一次断相结束时刻
#define B1EKG 0xb340//07无
#define B1EKA 0xb341
#define B1EKB 0xb342
#define B1EKC 0xb343
#define B1EKLEN 0x04
//电表日历时钟
#define TIMEDI  0xc011
#define TIMELEN 0x03
#define DATADI  0xc010
#define DATALEN 0x04
//电表运行状态字
#define AMTSTA 0xc020//07无
#define AMTSTALEN 0x01
//电网状态字
#define ELESTA 0xc021//07无
#define ELESTALEN 0x01
#define CAMTALLSTA 0xc02F
#define AMTALLSTALEN 14
//编程时间最近一次
#define PG1K 0xb210
#if(GWPCTFG==0x07)
  #define PG1KLEN 0x06
#else
  #define PG1KLEN 0x04
#endif
//最大需要清零时间
#define MD1CZK 0xb211
#if(GWPCTFG==0x07)
    #define MD1CZKLEN 6
#else
    #define MD1CZKLEN 4
#endif
//编程次数
#define PGD 0xb212
#if(GWPCTFG==0x07)
 #define PGDLEN 3
#else
 #define PGDLEN 2
#endif
//最大需量清零次数
#define MDCZD 0xb213
#if(GWPCTFG==0x07)
   #define MDCZDLEN 3
#else
   #define MDCZDLEN 2
#endif
//电池工作时间
#define BAWT 0xb214
#if(GWPCTFG==0x07)
  #define BAWTLEN 4
#else
  #define BAWTLEN 3
#endif
//@@@@@@@@@@@@@@@@@电能量@@@@@@@@@@@@@@
//当前正向有功块
#define PELEN 4
#define QELEN 4
#define ILPEF 0x901f
#define ILPEG 0x9010
//当前反向有功块
#define IOPEF 0x902f
#define IOPEG 0x9020
//当前正向无功块
#define ILQEF 0x911f
#define ILQEG 0x9110
//当前反向无功块
#define IOQEF 0x912f
#define IOQEG 0x9120

#define IX1QEF 0x913f//当前一象限无功块
#define IX1QEG 0x9130//1象限无功总
#define IX4QEF 0x914f//当前四象限无功块
#define IX4QEG 0x9140//4象限无功总
//当前二象限无功块
#define IX2QEF 0x915f
#define IX2QEG 0x9150//2象限无功总
//当前三象限无功块
#define IX3QEF 0x916f
#define IX3QEG 0x9160//3象限无功总
//上月正向有功块
#define LMLPEF 0x941f
//上月反向有功块
#define LMOPEF 0x942f
//上月正向无功块
#define LMLQEF 0x951f
//上月反向无功块
#define LMOQEF 0x952f
//上月一象限功块
#define LMX1QEF 0x953f
//上月四象限无功块
#define LMX4QEF 0x954f
//上月二象限无功块
#define LMX2QEF 0x955f
//上月三象限无功块
#define LMX3QEF 0x956f
//上上月正向有功块
#define LLMLPEF 0x981f
//上上月反向有功块
#define LLMOPEF 0x982f
//上上月正向无功块
#define LLMLQEF 0x991f
//上上月反向无功块
#define LLMOQEF 0x992f
//上上月一象限功块
#define LLMX1QEF 0x993f
//上上月四象限无功块
#define LLMX4QEF 0x994f
//上上月二象限无功块
#define LLMX2QEF 0x995f
//上上月三象限无功块
#define LLMX3QEF 0x996f
#define QPELEN  4
//@@@@@@@@@@@@@@@@@需量@@@@@@@@@@@@@@
//#define MDLEN 3
//当前正向有功最大需量块
#define ILPMDF 0xa01f
#define ILPMDG 0xa010//总当前正向有功最大需量
//当前反向有功最大需量块
#define IOPMDF 0xa02f
#define IOPMDG 0xa020//当前反向有功最大需量 总
//当前正向无功最大需量块
#define ILQMDF 0xa11f
//当前反向无功最大需量块
#define IOQMDF 0xa12f
//当前一象无功最大需量块
#define IX1QMDF 0xa13f
//当前四象无功最大需量块
#define IX4QMDF 0xa14f
//当前二象无功最大需量块
#define IX2QMDF 0xa15f
//当前三象无功最大需量块
#define IX3QMDF 0xa16f
//上月正向有功最大需量块
#define LMLPMDF 0xa41f
//上有正向有功总最大需量
#define LMLPMDG 0xa410
//上月反向有功最大需量块
#define LMOPMDF 0xa42f
//上月正向无功最大需量块
#define LMLQMDF 0xa51f
//上月反向无功最大需量块
#define LMOQMDF 0xa52f
//上月一象无功最大需量块
#define LMX1QMDF 0xa53f
//上月四象无功最大需量块
#define LMX4QMDF 0xa54f
//上月二象无功最大需量块
#define LMX2QMDF 0xa55f
//上月三象无功最大需量块
#define LMX3QMDF 0xa56f
//上上月正向有功最大需量块
#define LLMLPMDF 0xa81f
//上上月反向有功最大需量块
#define LLMOPMDF 0xa82f
//上上月正向无功最大需量块
#define LLMLQMDF 0xa91f
//上上月反向无功最大需量块
#define LLMOQMDF 0xa92f
//上上月一象无功最大需量块
#define LLMX1QMDF 0xa93f
//上上月四象无功最大需量块
#define LLMX4QMDF 0xa94f
//上上月二象无功最大需量块
#define LLMX2QMDF 0xa95f
//上上月三象无功最大需量块
#define LLMX3QMDF 0xa96f
#define MDLEN 3
//@@@@@@@@@@@@@@@@@最大需量发生时间@@@@@@@@@@@@@@
//当前正向有功最大需量发生时间块
#define ILPMDKF 0xb01f
#define ILPMDKG 0xb010// 总 当前正向有功最大需量发生时间
//当前反向有功最大需量发生时间块
#define IOPMDKF 0xb02f
//当前反向有功最大需量发生时间 总
#define IOPMDKG 0xb020
//当前正向无功最大需量发生时间块
#define ILQMDKF 0xb11f
//当前反向无功最大需量发生时间块
#define IOQMDKF 0xb12f
//当前一象无功最大需量发生时间块
#define IX1QMDKF 0xb13f
//当前四象无功最大需量发生时间块
#define IX4QMDKF 0xb14f
//当前二象无功最大需量发生时间块
#define IX2QMDKF 0xb15f
//当前三象无功最大需量发生时间块
#define IX3QMDKF 0xb16f
//上月正向有功最大需量发生时间块
#define LMLPMDKF 0xb41f
#define LMLPMDKG 0xb410
//上月反向有功最大需量发生时间块
#define LMOPMDKF 0xb42f
//上月正向无功最大需量发生时间块
#define LMLQMDKF 0xb51f
//上月反向无功最大需量发生时间块
#define LMOQMDKF 0xb52f
//上月一象无功最大需量发生时间块
#define LMX1QMDKF 0xb53f
//上月四象无功最大需量发生时间块
#define LMX4QMDKF 0xb54f
//上月二象无功最大需量发生时间块
#define LMX2QMDKF 0xb55f
//上月三象无功最大需量发生时间块
#define LMX3QMDKF 0xb56f
//上上月正向有功最大需量发生时间块
#define LLMLPMDKF 0xb81f
//上上月反向有功最大需量发生时间块
#define LLMOPMDKF 0xb82f
//上上月正向无功最大需量发生时间块
#define LLMLQMDKF 0xb91f
//上上月反向无功最大需量发生时间块
#define LLMOQMDKF 0xb92f
//上上月一象无功最大需量发生时间块
#define LLMX1QMDKF 0xb93f
//上上月四象无功最大需量发生时间块
#define LLMX4QMDKF 0xb94f
//上上月二象无功最大需量发生时间块
#define LLMX2QMDKF 0xb95f
//上上月三象无功最大需量发生时间块
#define LLMX3QMDKF 0xb96f
#define MDKLEN  4
//@@@@@@@@@@@@@@@@@@@
//~~~~当前上月最大需量及发生时刻块~~~~~~~~
#define MDVKLEN      7// 长度为7
#define ILPMDVKF     0xB0A0//当前正向有功总及各率最大需量及总及各率发生时刻块
#define IOPMDVKF     0xB0B0//当前反向有功总及各率最大需量及总及各率发生时刻块
#define ILQMDVKF     0xB1A0//当前正向无功总及各率最大需量及总及各率发生时刻块
#define IOQMDVKF     0xB1B0//当前反向无功总及各率最大需量及总及各率发生时刻块

#define LMLPMDVKF    0xB4A0//上月正向有功总及各率最大需量及总及各率发生时刻块
#define LMOPMDVKF    0xB4B0//上月反向有功总及各率最大需量及总及各率发生时刻块
#define LMLQMDVKF    0xB5A0//上月正向无功总及各率最大需量及总及各率发生时刻块
#define LMOQMDVKF    0xB5B0//上月反向无功总及各率最大需量及总及各率发生时刻块
//
#define ILPMDVKF_NT     0xB0A1//当前正向有功总及各率最大需量.发生时刻块,
#define IOPMDVKF_NT     0xB0B1//当前反向有功总及各率最大需量.发生时刻块
#define ILQMDVKF_NT     0xB1A1//当前正向无功总及各率最大需量.发生时刻块
#define IOQMDVKF_NT     0xB1B1//当前反向无功总及各率最大需量.发生时刻块

#define LMLPMDVKF_NT    0xB4A1//上月正向有功总及各率最大需量.发生时刻块
#define LMOPMDVKF_NT    0xB4B1//上月反向有功总及各率最大需量.发生时刻块
#define LMLQMDVKF_NT    0xB5A1//上月正向无功总及各率最大需量.发生时刻块
#define LMOQMDVKF_NT    0xB5B1//上月反向无功总及各率最大需量.发生时刻块

////////////////////////////////////////////////
#define CHRATE 0xc313//费率数
#define CHRATELEN 1
#define TIMEVIEW 0xc310//年时区数 P
#define TIMEVIEWLEN 1
#define DAYTIMES_CMD 0xc312//日时段切换数
#define DAYTIMES_LEN 1
#define DAYTIMESCH_CMD 0xc311//日时段表数
#define DAYTIMESCH_LEN 1
#define DAY_1_TIMESCH_CMD  0xc330//第一日时段所有费率的组合，
#define DAY_1_TIMESCH_LEN  42
#define DAY_1_TIME_1_CMD  0xc331//第一日时段第一时段费数，
#define DAY_1_TIME_1_LEN  3
#define EVENTALL_TJ 0xC02F
//失压数据项

//最近失压起始时刻
#define B1SNVA 0xB720
#define B1SNVB 0xB721
#define B1SNVC 0xB722
#define B1SNVLEN 0x04
//最近失压结束时刻
#define B1ENVA 0xB730
#define B1ENVB 0xB731
#define B1ENVC 0xB732
#define B1ENVLEN 0x04

//北京的扩展协议
#define CEVENT_NOVSTART_BJ 0xB720//失压开始  c
#define CEVENT_NOVEND_BJ   0xB730//失压结束 c
#define CEVENT_NOVLEN_BJ   15
/////////////////////扩展协议
//频率，温度，不平衡率
#define FCNC 0x3460//c
#define FCNCLEN 17

//当前电流不平时间
#define INOLVL  0x3570//上月电流不平衡运行时间 c
#define LMINOLVL 0x3575//c
#define LLMINOLVL 0x357A//c
#define INOLVLLEN 3
//当前电压不平时间
#define VNOLVL  0x3571//c
#define LMVNOLVL 0x3576//c
#define LLMVNOLVL 0x357B//c
#define VNOLVLLEN 3
////////////////////////////
//10次事件记录,清需量
#define ECLRM 0x343D//c
#define STATUSALL 0x340F//状 态字集合c
#define STATUSALLLEN 0x0D
#define STATUSALL_BJ 0xB741//c
#define STATUSALLLEN_BJ 10
#define STATUSALL_LN 0x340F
#define STATUSALLLEN_LN 0x0e
#define EBRAS  0x3411//10次事件记录,电压断相起始,a,b,c //c
#define EBRASLEN  18*10
#define EBRBS  0x3412//c
#define EBRBSLEN 18*10
#define EBRCS  0x3413//c
#define EBRCSLEN 18*10
#define EBRAE  0x341D//10次事件记录,电压断相结束,a,b,c //c
#define EBRAELEN 18*10 
#define EBRBE  0x341E//c
#define EBRBELEN 18*10
#define EBRCE  0x341F//c
#define EBRCELEN 18*10
#define EVOS    0x3435//10次事件记录,电压逆相序起始//c
#define EVOSLEN 18*10
#define EVOE    0x3436//10次事件记录,电压逆相序结束//c
#define EVOELEN 18*10
#define ECOS    0x3437//10次事件记录,电流逆相序起始//c
#define ECOSLEN 18*10
#define ECOE    0x3438//10次事件记录,电流逆相序结束//c
#define ECOELEN 18*10
#define ENVGE    0x3420//10次事件记录,失压结束总,A,B,C//c
#define ENVGELEN 18*10
#define ENVAE    0x3421
#define ENVAELEN 18*10
#define ENVBE    0x3422
#define ENVBELEN 18*10
#define ENVCE    0x3423
#define ENVCELEN 18*10
#define ENVGS    0x3414//10次事件记录,失压起始总,A,B,C
#define ENVGSLEN 18*10
#define ENVAS    0x3415
#define ENVASLEN 18*10
#define ENVBS    0x3416
#define ENVBSLEN 18*10
#define ENVCS   0x3417
#define ENVCSLEN  18*10
#define EONPW   0x3432
#define EONPWLEN 18*10
//#define ETIME   0x343E //10校时记录,校前年月日时分5字节,次数2字节,校后年月日时分5字节,用户ID号1字节,5字节0
//////////////////////////////////////
#define CFLEN    3
#define CFFVA   0x3531//A相电压正常运行时间
#define CFHVA   0x3532//A相电压超上限时间
#define CFLVA   0x3533//A相电压低下限时间
#define CFFVB   0x3534//B相电压正常运行时间
#define CFHVB   0x3535//B相电压超上限时间
#define CFLVB   0x3536//B相电压低下限时间
#define CFFVC   0x3537//C相电压正常运行时间
#define CFHVC   0x3538//C相电压超上限时间
#define CFLVC   0x3539//C相电压低下限时间
#define EONPW   0x3432//上电
#define ENODI   0x3433//掉电
#define EONPWLEN 18*10//上电
#define ENODILEN 18*10//掉电
#define FACTORLOW1  0x3572//当前功率因素<限制1运行时间
#define FACTORLOW2  0x3573//当前功率因素<限制2运行时间
#define FACTOROVER2 0x3574//当前功率因素>限制2运行时间
#define LMFACTORLOW1  0x3577//上月功率因素<限制1运行时间
#define LMFACTORLOW2  0x3578//上月功率因素<限制2运行时间
#define LMFACTOROVER2 0x3579//上月功率因素>限制2运行时间
#define LLMFACTORLOW1  0x357C//上上月功率因素<限制1运行时间
#define LLMFACTORLOW2  0x357D//上上月功率因素<限制2运行时间
#define LLMFACTOROVER2 0x357E//上上月功率因素>限制2运行时间
#define FACTORLEN  3
///////////////////////////
//吉林扩展命令
#define SYN_DAY_BIG_C_A_CMD  0x0000//F113 A相2~19次谐波电流日最大值及发生时间
#define SYN_DAY_BIG_C_A_LEN  114
#define SYN_DAY_BIG_C_B_CMD  0x0000//F114 B相2~19次谐波电流日最大值及发生时间
#define SYN_DAY_BIG_C_B_LEN  114
#define SYN_DAY_BIG_C_C_CMD  0x0000//F115 C相2~19次谐波电流日最大值及发生时间
#define SYN_DAY_BIG_C_C_LEN  114
#define SYN_DAY_CTN_V_A_CMD  0x0000//F116 A相2~19次谐波电压含有率及总畸变率日最大值及发生时间
#define SYN_DAY_CTN_V_A_LEN  114
#define SYN_DAY_CTN_V_B_CMD  0x0000//F117 B相2~19次谐波电压含有率及总畸变率日最大值及发生时间
#define SYN_DAY_CTN_V_A_LEN  114
#define SYN_DAY_CTN_V_C_CMD  0x0000//F118 C相2~19次谐波电压含有率及总畸变率日最大值及发生时间
#define SYN_DAY_CTN_V_A_LEN  114




#define CC0CNT      0xF001//电表清零总次数
#define C0CNTLEN     3
#define CC0STK      0xF002//电表第一次清零发生时间
#define C0STKL      6

#define CCEVENTCNT  0xF003//事件清零总次数
#define CEVENTLEN    3
#define CCEVENTSTK  0xF004//最近一次事件清0时该
#define CEVENTSTKLEN  6

#define CUPTIMECNT   0xF005//校时次数
#define UPTIMECNTLEN  3
#define CUPTIMESTK   0xF006//最近一次校时时间
#define UPTIMESTKLEN  6

//~~~~~~当前电量
#define CICUPE     0xF008//(当前)铜损有功总电能补偿量
#define CIFEPE     0xF009//(当前)铁损有功总电能补偿量
#define CLMCUPE     0xF00a//( 上一结算日)铜损有功总电能补偿量
#define CLMFEPE     0xF00b//(上一结算日)铁损有功总电能补偿量
//~~~~~分相电量~~~~~~~~~~~~
//当前分相电量
#define CIALPE     0xF00C//A相当前有正向有功
#define CIAOPE     0xF00D//A相当前有反向有功
#define CIALQE     0xF00E//A相当前有组合无功1
#define CIAOQE     0xF010//A相当前有组合无功2

#define CIBLPE     0xF011//B相当前有正向有功
#define CIBOPE     0xF012//B相当前有反向有功
#define CIBLQE     0xF013//B相当前有组合无功1
#define CIBOQE     0xF014//B相当前有组合无功2

#define CICLPE     0xF015//C相当前有正向有功
#define CICOPE     0xF016//C相当前有反向有功
#define CICLQE     0xF017//C相当前有组合无功1
#define CICOQE     0xF018//C相当前有组合无功2
// 上一结算日分相电量
#define CLMALPE     0xF019//上一结算日 A相 有正向有功
#define CLMAOPE     0xF01a//上一结算日 A相 有反向有功
#define CLMALQE     0xF01b//上一结算日 A相 有组合无功1
#define CLMAOQE     0xF01c//上一结算日 A相 有组合无功2

#define CLMBLPE     0xF01d//上一结算日 B相 有正向有功
#define CLMBOPE     0xF01e//上一结算日 B相 有反向有功
#define CLMBLQE     0xF020//上一结算日 B相 有组合无功1
#define CLMBOQE     0xF021//上一结算日 B相 有组合无功2

#define CLMCLPE     0xF022//上一结算日 C相 有正向有功
#define CLMCOPE     0xF023//上一结算日 C相 有反向有功
#define CLMCLQE     0xF024//上一结算日 C相 有组合无功1
#define CLMCOQE     0xF025//上一结算日 C相 有组合无功2


//失压和断相的数据项
#define NVVAALL     0xF101
#define NVVBALL     0xF102
#define NVVCALL     0xF103
#define NVVALLEN    195

#define BVVAALL     0xF201
#define BVVBALL     0xF202
#define BVVCALL     0xF203

#define BVVALLEN    195

//断相失压起始结束时间
//最近失压起始时刻
#define B1SNVA_07 0xF301
#define B1SNVB_07 0xF302
#define B1SNVC_07 0xF303
#define B1SNVLEN_07 0x05
//最近失压结束时刻
#define B1ENVA_07 0xF304
#define B1ENVB_07 0xF305
#define B1ENVC_07 0xF306
#define B1ENVLEN_07 0x05
//第一次断相起始时刻
#define B1SKA_07 0xF307
#define B1SKB_07 0xF308
#define B1SKC_07 0xF309
#define B1SKLEN_07  0x05
//第一次断相结束时刻
#define B1EKA_07 0xF30a
#define B1EKB_07 0xF31b
#define B1EKC_07 0xF31c
#define B1EKLEN_07 0x05

#define DCFreq_Cmd 	 0x3460
#define DCFreq_Len   2
#define DCTmpare_Cmd 0x3461
#define DCTmpare_Len     3 

//ÊÂ¼þÀà
#define NVL_CNT_CMD  0xF400//Ê§Ñ¹×Ü´ÎÊý
#define NVA_CNT_CMD  (NVL_CNT_CMD+1)
#define NVB_CNT_CMD  (NVA_CNT_CMD+1)
#define NVC_CNT_CMD  (NVB_CNT_CMD+1)
#define NV_CNT_LEN   3//Ê§Ñ¹×Ü´ÎÊý³¤¶È
#define ND_CNT_CMD   (NVC_CNT_CMD+1)//µôµç×Ü´ÎÊý
#define ND_CNT_LEN   3 //µôµç×Ü´ÎÊý³¤¶È
#define BRA_CNT_CMD  (ND_CNT_CMD+1)//A¶ÏÏà´ÎÊý
#define BRB_CNT_CMD  (BRA_CNT_CMD+1)//B¶ÏÏà´ÎÊý
#define BRC_CNT_CMD  (BRB_CNT_CMD+1)//C¶ÏÏà´ÎÊý
#define BRC_CNT_LEN  3

//µç±íÔËÐÐ×´Ì¬×ÖÊý¾Ý¿é
#define CAMTSTA_1_CMD    (BRC_CNT_CMD+1) 
#define CAMTSTA_2_CMD    (CAMTSTA_1_CMD+1)
#define CAMTSTA_3_CMD    (CAMTSTA_2_CMD+1)
#define CAMTSTA_4_CMD    (CAMTSTA_3_CMD+1)
#define CAMTSTA_5_CMD    (CAMTSTA_4_CMD+1)
#define CAMTSTA_6_CMD    (CAMTSTA_5_CMD+1)
#define CAMTSTA_7_CMD    (CAMTSTA_6_CMD+1)
#define CAMTALLSTA_07       (CAMTSTA_7_CMD+1) 
#define CAMTSTA_LEN   1
#define AMTALLSTALEN_07  14

//ÊÓÔÚ¹¦ÂÊ
#define LOOKP_G_CMD      (CAMTALLSTA_07+1)
#define LOOKP_A_CMD      (LOOKP_G_CMD+1)
#define LOOKP_B_CMD      (LOOKP_A_CMD+1)
#define LOOKP_C_CMD      (LOOKP_B_CMD+1)
#define LOOKP_F_CMD  (LOOKP_C_CMD+1)//ÊÓÔÚ¹¦ÂÊ×Ü,A,B,C
#define LOOKP_LEN  3
#define LOOKP_F_LEN 12


//4Î»Ð¡ÊýµÄÓÐ¹¦µçÄÜÊ¾Öµ
#define  ILPEG_4D  (LOOKP_F_CMD+1)//ÕýÏòÓÐ¹¦×Ü
#define  ILPEF_4D  (ILPEG_4D+1)//ÕýÏòÓÐ¹¦¿é
#define  IOPEG_4D  (ILPEF_4D+1)//·´ÏòÓÐ¹¦×Ü
#define  IOPEF_4D  (IOPEG_4D+1)//·´ÏòÓÐ¹¦¿é
#define  PELEN_4D  5

#define LMLPMDVKG   (IOPEF_4D+1)
#define LMLPMDVKA   (LMLPMDVKG+1)
#define LMLPMDVKB   (LMLPMDVKA+1)
#define LMLPMDVKC   (LMLPMDVKB+1)
#define LMLPMDVKLEN  6

#define CDNDFG_CMD   (LMLPMDVKC+1)//µç±íÍ¨¶Ïµç¼ÇÂ¼
#define CDNDFG_LEN   1

#if(D_GWPCT2013_EN==1)
#define CDONTIME_CMD (CDNDFG_CMD+1)//×î½üÒ»´ÎÔ¶³ÌÍ¨µçÊ±¼ä
#define CDONTIME_LEN 6
#define CDDOWNTIME_CMD (CDONTIME_CMD+1)//×î½üÒ»´ÎÔ¶³Ì¶ÏµçÊ±¼ä
#define CDDOWNTIME_LEN 6
#define CDOPTIME_CMD   (CDDOWNTIME_CMD+1)//±à³Ì¿ª¹Ø²Ù×÷Ê±¼ä
#define CDOPTIME_LEN   6
#define CDOPCNT_CMD   (CDOPTIME_CMD+1)//±à³Ì¿ª¹Ø²Ù×÷´ÎÊý
#define CDOPCNT_LEN   3
#define CDWGCNT_CMD   (CDOPCNT_CMD+1)//Î²¶Ë´ÎÊý
#define CDWGCNT_LEN   3
#define CDWGTIME_CMD   (CDWGCNT_CMD+1)//Î²¶ËµÚÒ»´Î´ò¿ªÊ±¼ä
#define CDWGTIME_LEN   6
#define CDRTCTIME_CMD  (CDWGTIME_CMD+1)//Ê±ÖÓÊ±¼ä
#define CDRTCTIME_LEN  6
#define CDRTCCNT_CMD   (CDRTCTIME_CMD+1)//Ê±ÖÓ´ÎÊý
#define CDRTCCNT_LEN   3
#define CDSCHTIME_CMD  (CDRTCCNT_CMD+1)//Ê±¶Î²ÎÊýÊ±¼ä
#define CDSCHTIME_LEN   6
#define CDSCHCNT_CMD   (CDSCHTIME_CMD+1)//Ê±¶Î²ÎÊý´ÎÊý
#define CDSCHCNT_LEN   3
#else
#define CDONTIME_CMD (CDNDFG_CMD+1)//×î½üÒ»´ÎÔ¶³ÌÍ¨µçÊ±¼ä
#define CDONTIME_LEN 5
#define CDDOWNTIME_CMD (CDONTIME_CMD+1)//×î½üÒ»´ÎÔ¶³Ì¶ÏµçÊ±¼ä
#define CDDOWNTIME_LEN 5
#define CDOPTIME_CMD   (CDDOWNTIME_CMD+1)//±à³Ì¿ª¹Ø²Ù×÷Ê±¼ä
#define CDOPTIME_LEN   5
#define CDOPCNT_CMD   (CDOPTIME_CMD+1)//±à³Ì¿ª¹Ø²Ù×÷´ÎÊý
#define CDOPCNT_LEN   2
#define CDWGCNT_CMD   (CDOPCNT_CMD+1)//Î²¶Ë´ÎÊý
#define CDWGCNT_LEN   2
#define CDWGTIME_CMD   (CDWGCNT_CMD+1)//Î²¶ËµÚÒ»´Î´ò¿ªÊ±¼ä
#define CDWGTIME_LEN   5
#define CDRTCTIME_CMD  (CDWGTIME_CMD+1)//Ê±ÖÓÊ±¼ä
#define CDRTCTIME_LEN  5
#define CDRTCCNT_CMD   (CDRTCTIME_CMD+1)//Ê±ÖÓ´ÎÊý
#define CDRTCCNT_LEN   2
#define CDSCHTIME_CMD  (CDRTCCNT_CMD+1)//Ê±¶Î²ÎÊýÊ±¼ä
#define CDSCHTIME_LEN   5
#define CDSCHCNT_CMD   (CDSCHTIME_CMD+1)//Ê±¶Î²ÎÊý´ÎÊý
#define CDSCHCNT_LEN   2
#endif


#define CDBUYCNT_CMD   (CDSCHCNT_CMD+1)//¹ºµç´ÎÊý
#define CDBUYCNT_LEN   2
#define CDREMONEY_CMD  (CDBUYCNT_CMD+1)//Ê£Óà½ð¶î
#define CDREMONEY_LEN  5
#define CDBUYMONEY_CMD  (CDREMONEY_CMD+1)//ÀÛ¼Æ¹ºµç½ð¶î
#define CDBUYMONEY_LEN   5
#define CDREMEMG_CMD    (CDBUYMONEY_CMD+1)//Ê£Óà½ð¶îµçÁ¿
#define CDREMEMG_LEN      4
#define CDOVEREMG_CMD    (CDREMEMG_CMD+1)//Í¸Ö§µçÁ¿
#define CDOVEREMG_LEN     4
#define CDBUYEMG_CMD     (CDOVEREMG_CMD+1)//ÀÛ¼Æ¹ºµçÁ¿
#define CDBUYEMG_LEN      4
#define CDLIMITEMG_CMD   (CDBUYEMG_CMD+1)//ÉÞÇ·µçÁ¿
#define CDLIMITEMG_LEN    4
#define CDALARMEMG_CMD   (CDLIMITEMG_CMD+1)//±¨¾¯µçÁ¿
#define CDALARMEMG_LEN    4
#define CDJUMPEMG_CMD    (CDALARMEMG_CMD+1)//ÌøÕ¢µçÁ¿
#define CDJUMPEMG_LEN     4

//ÉÏÒ»´ÎÈÕ¶³½áÊ±¼ä
#define CDLD1TIME_CMD   (CDJUMPEMG_CMD+1)
#define CDLDTIME_LEN    5
//ÕýÏòÓÐ¹¦
#define CDLD1LPEF_CMD   (CDLD1TIME_CMD+1)
//·´ÏòÓÐ¹¦ 
#define CDLD1OPEF_CMD   (CDLD1LPEF_CMD+1)
//ÕýÏòÎÞ¹¦ 
#define CDLD1LQEF_CMD   (CDLD1OPEF_CMD+1)
//·´ÏòÎÞ¹¦ 
#define CDLD1OQEF_CMD   (CDLD1LQEF_CMD+1)
//1ÏóÏÞÎÞ¹¦ 
#define CDLD1X1QEF_CMD   (CDLD1OQEF_CMD+1)
//2ÏóÏÞÎÞ¹¦ 
#define CDLD1X2QEF_CMD   (CDLD1X1QEF_CMD+1)
//3ÏóÏÞÎÞ¹¦ 
#define CDLD1X3QEF_CMD   (CDLD1X2QEF_CMD+1)
//4ÏóÏÞÎÞ¹¦ 
#define CDLD1X4QEF_CMD   (CDLD1X3QEF_CMD+1)
//ÕýÏòÓÐ¹¦×î´óÐèÁ¿
#define CDLD1LPMDVKF_CMD   (CDLD1X4QEF_CMD+1)
//ÕýÏòÓÐ¹¦×î´óÐèÁ¿
#define CDLD1OPMDVKF_CMD   (CDLD1LPMDVKF_CMD+1)
//ÕýÏòÓÐ¹¦×î´óÐèÁ¿
#define CDLD1LQMDVKF_CMD   (CDLD1OPMDVKF_CMD+1)
//ÕýÏòÓÐ¹¦×î´óÐèÁ¿
#define CDLD1OQMDVKF_CMD   (CDLD1LQMDVKF_CMD+1)
//ÁãÏòµçÁ÷
#define  WCZ               (CDLD1OQMDVKF_CMD+1)
//µçÑ¹Ïà½ÇÊý¾Ý¿é
#define CDPHASEANGLE_CMD   (WCZ+1)
#define CDPHASEANGLE_LEN    6
//AÏàµçÑ¹Ð³²¨º¬Á¿1-19´Î
#define CDSYNCONTENT_VA_CMD  (CDPHASEANGLE_CMD+1)
//BÏàµçÑ¹Ð³²¨º¬Á¿1-19´Î
#define CDSYNCONTENT_VB_CMD  (CDSYNCONTENT_VA_CMD+1)
//CÏàµçÑ¹Ð³²¨º¬Á¿1-19´Î
#define CDSYNCONTENT_VC_CMD  (CDSYNCONTENT_VB_CMD+1)
//AÏàµçÁ÷Ð³²¨º¬Á¿1-19´Î
#define CDSYNCONTENT_CA_CMD  (CDSYNCONTENT_VC_CMD+1)
//BÏàµçÁ÷Ð³²¨º¬Á¿1-19´Î
#define CDSYNCONTENT_CB_CMD  (CDSYNCONTENT_CA_CMD+1)
//CÏàµçÁ÷Ð³²¨º¬Á¿1-19´Î
#define CDSYNCONTENT_CC_CMD  (CDSYNCONTENT_CB_CMD+1)
#define CDSYNCONTENT_LEN      38
//1·ÖÖÓÆ½¾ù×ÜÓÐ¹¦¹¦ÂÊ
#define CAGVWPPG (CDSYNCONTENT_CC_CMD+1)
#define CDLASTHOURFRZ_1_CMD   (CAGVWPPG+1)
#define CDLASTHOURFRZ_2_CMD   (CDLASTHOURFRZ_1_CMD+1)
#define CDLASTHOURFRZ_LEN     13

//ÄÚÃÉÐÂ¼ÓµÄÐ­Òé
#define CDOVERMONEY_CMD    (CDLASTHOURFRZ_2_CMD+1)//Í¸Ö§½ð¶î
#define CDOVERMONEY_LEN     5

#define ICPEF_CMD          (CDOVERMONEY_CMD+1)//×éºÏÓÐ¹¦
#define CMETERSTA3_CMD     (ICPEF_CMD+1)//µç±í×´Ì¬×Ö3
#define CMETERSTA3_LEN      2

#define CMETERSTA7_CMD     (CMETERSTA3_CMD+1)//µç±í×´Ì¬×Ö3
#define CMETERSTA7_LEN      2

#define CMETERPCTRELAYSTA_CMD     (CMETERSTA7_CMD+1)//µçÄÜ±í±£µç×´Ì¬/¼ÌµçÆ÷×´Ì¬ D0 ±£µç D1 ¼ÌµçÆ÷×´Ì¬Î»£¬
#define CMETERPCTRELAYSTA_LEN     1
// £¨ÉÏ1´Î£©¿ª±í¸Ç¼ÇÂ¼£º
#define CLAST_WGCRAD_CMD   (CMETERPCTRELAYSTA_CMD+1)
#define CLAST_WGCRAD_LEN   60
//ÉÏ1´Î£©¿ª¶ËÅ¥ºÐ¼ÇÂ¼(Í¬¿ª±í¸Ç)
#define CLAST_NGCRAD_CMD   (CLAST_WGCRAD_CMD+1)
#define CLAST_NGCRAD_LEN   60
//
#define MAX_G_PMDF_CMD     (CLAST_NGCRAD_CMD+1)//AÏà×î´óÐèÒª¼°·µ»ØÊ±¼ä
#define MAX_A_PMDF_CMD     (MAX_G_PMDF_CMD+1)//AÏà×î´óÐèÒª¼°·µ»ØÊ±¼ä
#define MAX_B_PMDF_CMD     (MAX_A_PMDF_CMD+1)//AÏà×î´óÐèÒª¼°·µ»ØÊ±¼ä
#define MAX_C_PMDF_CMD     (MAX_B_PMDF_CMD+1)//AÏà×î´óÐèÒª¼°·µ»ØÊ±¼ä
#define MAX_ABC_PMDF_LEN    3  


#define CJUSTTIME_CMD   (MAX_C_PMDF_CMD+1)//Ð£Ê±Ç°Ê±¼ä,ºÍÐ£Ê±ºóÊ±¼ä
#define CJUSTTIME_LEN   12
#define CLAST_BCPEF_CMD   (CJUSTTIME_CMD+1)//ÉÏÒ»½áËãÈÕ×éºÏÓÐ¹¦µçÄÜÊ¾Öµ
#define CTIME_ALLCMD	(CLAST_BCPEF_CMD+1)
#define CTIME_ALL_LEN    7
#define CTIME_ALLTEMI_CMD	(CTIME_ALLCMD+1)
#define CTIME_ALLTEMI_LEN    6  

#define CLAST_NDCRAD_CMD   (CTIME_ALLTEMI_CMD+1)
#define CLAST_NDCRAD_LEN   12



#define Bit0   0x00000001
#define Bit1   0x00000002
#define Bit2   0x00000004
#define Bit3   0x00000008
#define Bit4   0x00000010
#define Bit5   0x00000020
#define Bit6   0x00000040
#define Bit7   0x00000080
#define Bit8   0x00000100
#define Bit9   0x00000200
#define Bit10  0x00000400
#define Bit11  0x00000800
#define Bit12  0x00001000
#define Bit13  0x00002000
#define Bit14  0x00004000
#define Bit15  0x00008000
#define Bit16  0x00010000
#define Bit17  0x00020000
#define Bit18  0x00040000
#define Bit19  0x00080000
#define Bit20  0x00100000
#define Bit21  0x00200000
#define Bit22  0x00400000
#define Bit23  0x00800000
#define Bit24  0x01000000
#define Bit25  0x02000000
#define Bit26  0x04000000
#define Bit27  0x08000000
#define Bit28  0x10000000
#define Bit29  0x20000000
#define Bit30  0x40000000
#define Bit31  0x80000000

#ifdef NDEBUG
#ifdef STD_CSG
#ifndef _STD_CSG
#define _STD_CSG
#endif
#endif
#endif


/**********************************************************************************************************
*                    定义与编译器无关的数据类型
**********************************************************************************************************/

typedef unsigned char  BOOLEAN;                 /* 布尔变量                                 */
typedef unsigned char  INT8U;                   /* 无符号8位整型变量                        */
typedef signed   char  INT8S;                   /* 有符号8位整型变量                        */
typedef unsigned short INT16U;                  /* 无符号16位整型变量                       */
typedef signed   short INT16S;                  /* 有符号16位整型变量                       */
typedef unsigned int   INT32U;                  /* 无符号32位整型变量                       */
typedef signed   int   INT32S;                  /* 有符号32位整型变量                       */

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef True
#define True 1
#endif

#ifndef False
#define False 0
#endif

#ifndef High
#define High 1
#endif

#ifndef Low
#define Low  0
#endif

#ifndef HIGH
#define HIGH 1
#endif

#ifndef LOW
#define LOW 0
#endif

//比较值的返回
#ifndef BIG 
 #define BIG   0x01
#endif
#ifndef LIT 
  #define LIT   0x02
#endif
#ifndef EQU 
  #define EQU  0x00 
#endif
/////////////////////////////////////////////////////////////////////////////
// CUser_Mcu_Cfg window

class CUser_Mcu_Cfg
{
// Construction
public:
	CUser_Mcu_Cfg();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUser_Mcu_Cfg)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUser_Mcu_Cfg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUser_Mcu_Cfg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USER_MCU_CFG1_H__31A0FA83_734C_4E3B_9698_11C33B66C503__INCLUDED_)
