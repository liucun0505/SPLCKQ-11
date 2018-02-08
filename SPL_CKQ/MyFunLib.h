#ifndef _MyFunLib_H
#define  _MyFunLib_H
#include "User_Mcu_Cfg.h"
 extern  INT32U QueSysTimeVal(INT32U vSrcTime,INT32U vSrcTime2);
extern void StaSucessCnt(INT8U ack,INT16U &allSucesscnt,INT16U &failCnt);
extern INT8U QueAckFormAckCnt(INT16U failCnt);
//ASCTT HEX 转换部分
//-------------------------------------------------
//【函数名称】        extern INT16U   ascii_2_hex
//【函数功能】        ASCII 到 HEX的转换函数 
//【参数说明】        
//【I:输入】          INT8U *O_data:转换数据的入口指针
//                    
//                    INT16U len: 需要转换的长度
//【O:输出】          INT8U *N_data:转换后新数据的入口指针
//【全局变量】       
//【返回值】          类型：INT16U 值：0: 转换失败  其它：转换后数据长度
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT16U   ascii_2_hex(TH_IN INT8U *O_data, TH_OUT INT8U *N_data, TH_IN INT16U len);

//-------------------------------------------------
//【函数名称】        extern INT8U   ascii_2_hex_string
//【函数功能】        ASC码长度不清楚的情况下用,ASC码转换成16进制，最大长度为512
//【参数说明】        
//【I:输入】          INT8U *O_data:转换数据的入口指针
//                    INT16U vSrcLen1:转换数据长度
//                    INT8U *N_data:转换后新数据的入口指针
//                    INT16U vSrcLen2: 转换后的长度
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT8U 值：0: 转换失败  其它：转换后数据长度
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT16U   ascii_2_hex_string(TH_IN INT8U *O_data,INT16U vSrcLen1, TH_OUT INT8U *N_data,TH_IN INT16U vSrcLen2);

//-------------------------------------------------
//【函数名称】        extern INT16U  hex_2_ascii
//【函数功能】        HEX 到 ASCII的转换函数
//【参数说明】        
//【I:输入】          INT8U *data:转换数据的入口指针
//                    
//                    INT8U len:需要转换的长度
//【O:输出】          INT8U *buffer:转换后数据入口指针
//【全局变量】       
//【返回值】          类型：INT8U 值：0: 转换失败  其它：转换后数据长度
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT16U  hex_2_ascii(TH_OUT const INT8U *data, TH_OUT INT8U *buffer, TH_OUT INT8U len);

//-------------------------------------------------
//【函数名称】        extern INT8U   bin8_to_asciiBuf
//【函数功能】        8进制转换成ASC码
//【参数说明】        
//【I:输入】          INT8U bcdbin:待转换数据
//                    
//【O:输出】         INT8U *buffer:转换后数据入口指针 
//【全局变量】       
//【返回值】          类型：INT8U 值：0: 转换失败  其它：转换后数据长度
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U  bin8_to_asciiBuf(TH_IN INT8U bcdbin, TH_OUT INT8U *buffer);

//-------------------------------------------------
//【函数名称】        extern INT8U   ascii_to_bin8Buf
//【函数功能】        ASC码转换成8进制
//【参数说明】        
//【I:输入】          INT8U len:长度
//                   
//【O:输出】           INT8U *buffer:转换后数据入口指针
//【全局变量】       
//【返回值】          类型：INT8U 值：转换后的长度
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern	INT8U ascii_to_bin8Buf(TH_IN INT8U len, TH_OUT INT8U *buffer);

//-------------------------------------------------
//【函数名称】        extern INT8U  bin16_to_asciiBuf
//【函数功能】        ASCII 到16进制 的转换函数
//【参数说明】        
//【I:输入】          INT8U bcdbin:待转换的数据
//                    
//【O:输出】          INT8U *buffer:转换后数据入口指针
//【全局变量】       
//【返回值】          类型：INT8U 值：0: 转换失败  其它：转换后数据长度
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U bin16_to_asciiBuf(TH_IN INT16U bcdbin, TH_OUT INT8U *buffer);



//-------------------------------------------------
//【函数名称】        extern INT8U  Ascii0ToF
//【函数功能】        查义0到F的ASCII转换
//【参数说明】        
//【I:输入】          INT8U vSrcData:待转换的数据
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT8U 值：0: 转换失败  其它：转换后数据
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U Ascii0ToF(TH_IN INT8U vSrcData);


// BCD 和 HEX 相互转换部分
//-------------------------------------------------
//【函数名称】        extern INT8U  BcdToHex
//【函数功能】        BCd到的hex转换
//【参数说明】        
//【I:输入】          INT8U data:待转换的数据
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT8U 值：转换后的数据
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U BcdToHex(TH_IN INT8U data);

//-------------------------------------------------
//【函数名称】        extern INT8U  BcdToHex
//【函数功能】        hex到的bcd转换
//【参数说明】        
//【I:输入】          const INT8U data:待转换的数据
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT8U 值：转换后的数据
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U HexToBcd(TH_IN const INT8U data);

//-------------------------------------------------
//【函数名称】        extern INT32U  BcdBuf4ToHex32
//【函数功能】        bcd4字节到的32位hex转换
//【参数说明】        
//【I:输入】          const INT8U *buf:待转换的数据针
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT32U 值：转换后的数据
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT32U BcdBuf4ToHex32(TH_IN const INT8U *buf);

//-------------------------------------------------
//【函数名称】        extern INT32U  BcdToHex32NByte
//【函数功能】        bcd到的32位Byte转换
//【参数说明】        
//【I:输入】          const INT8U *buf:待转换的数据针
//                    INT8U len:转换的长度
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT32U 值：转换后的数据
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT32U BcdToHex32NByte(TH_IN INT8U *buf, TH_IN INT8U len);

//-------------------------------------------------
//【函数名称】        extern void Hex32ToBcdNByte
//【函数功能】        hex32到Byte转换
//【参数说明】        
//【I:输入】          INT32U bcd32:待转换的数据
//                    INT8U len:位数
//                    
//【O:输出】          INT8U *buf:转换后的数据指针
//【全局变量】       
//【返回值】          
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern void Hex32ToBcdNByte(TH_IN INT32U bcd32, TH_IN INT8U len, TH_OUT INT8U *buf);

//-------------------------------------------------
//【函数名称】        extern void Hex32ToBcdBuf4
//【函数功能】        hex32到BCD4字节转换
//【参数说明】        
//【I:输入】          INT32U bcd32:待转换的数据
//                    
//【O:输出】          INT8U *buf:转换后的数据指针
//【全局变量】       
//【返回值】          
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern void Hex32ToBcdBuf4(TH_IN INT32U bcd32, TH_OUT INT8U *buf);

//-------------------------------------------------
//【函数名称】        extern INT32U Bcd32ToHex32
//【函数功能】        BCD到hex转换
//【参数说明】       
//【I:输入】          INT32U pSrcBcd32:待转换的数据
//                    
//【O:输出】         
//【全局变量】       
//【返回值】          类型：INT32U 值：转换后的数据
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT32U Bcd32ToHex32(TH_IN INT32U pSrcBcd32);

//-------------------------------------------------
//【函数名称】        extern INT32U Hex32ToBcd32
//【函数功能】        hex32到BCD32转换
//【参数说明】        
//【I:输入】          INT32U pSrcHex32:待转换的数据
//                    
//【O:输出】         
//【全局变量】       
//【返回值】          类型：INT32U 值：转换后的数据
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT32U Hex32ToBcd32(TH_IN INT32U pSrcHex32);

//-------------------------------------------------
//【函数名称】        extern INT16U Bcd16ToHex16
//【函数功能】        BCD16到hex16转换
//【参数说明】        
//【I:输入】          INT16U data:待转换的数据
//                    
//【O:输出】         
//【全局变量】       
//【返回值】          类型：INT16U 值：转换后的数据
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT16U Bcd16ToHex16(TH_IN INT16U data);

//-------------------------------------------------
//【函数名称】        extern INT16U Hex16ToBcd16
//【函数功能】        hex16到bcd16转换
//【参数说明】        
//【I:输入】          INT16U data:待转换的数据
//                    
//【O:输出】         
//【全局变量】       
//【返回值】          类型：INT16U 值：转换后的数据
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT16U Hex16ToBcd16(TH_IN INT16U data);


//BUF组合部分
//-------------------------------------------------
//【函数名称】        extern void Hex16ToBuf2
//【函数功能】        hex16到bcd16转换
//【参数说明】        
//【I:输入】          INT16U data:待转换的数据
//                    
//【O:输出】          INT8U *buf:转换后的指针
//【全局变量】       
//【返回值】          
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern void Hex16ToBuf2(TH_IN INT16U data, TH_OUT INT8U *buf);

//-------------------------------------------------
//【函数名称】        extern void Hex32ToBuf4
//【函数功能】        hex32到Buf4转换
//【参数说明】        
//【I:输入】          INT32U data:待转换的数据
//                    
//【O:输出】          INT8U *buf:转换后的指针
//【全局变量】       
//【返回值】          
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern void Hex32ToBuf4(TH_IN INT32U data, TH_OUT INT8U *buf);

//-------------------------------------------------
//【函数名称】        extern INT16U Buf2ToHex16
//【函数功能】        Buf2到Hex16转换
//【参数说明】        
//【I:输入】          const INT8U *buf:待转换的数据指针
//                    
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT16U 值：转换后的指针
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT16U Buf2ToHex16(TH_IN const INT8U *buf);

//-------------------------------------------------
//【函数名称】        extern INT32U Buf3ToHex32
//【函数功能】        Buf3到Hex32转换
//【参数说明】        
//【I:输入】          const INT8U *buf:待转换的数据指针
//                    
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT32U 值：转换后的指针
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT32U Buf3ToHex32(TH_IN const INT8U *buf);

//-------------------------------------------------
//【函数名称】        extern INT32U Buf4ToHex32
//【函数功能】        Buf4到Hex32转换
//【参数说明】        
//【I:输入】          const INT8U *buf:待转换的数据指针
//                    
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT32U 值：转换后的指针
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT32U Buf4ToHex32(TH_IN const INT8U *buf);

//-------------------------------------------------
//【函数名称】        extern INT32U NBufToHex32
//【函数功能】        Buf到Hex32转换()
//【参数说明】        
//【I:输入】          const INT8U *buf:待转换的数据指针
//                    INT8U len:转换长度
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT32U 值：转换后的指针
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT32U NBufToHex32(TH_IN const INT8U *buf,TH_IN INT8U len);

//-------------------------------------------------
//【函数名称】        extern void Hex32ToBuf3
//【函数功能】        Hex32到Buf3转换()
//【参数说明】        
//【I:输入】          INT32U data:待转换的数据
//【O:输出】          INT8U *buf：转换后的指针
//【全局变量】       
//【返回值】         
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern void Hex32ToBuf3(TH_IN INT32U data, TH_OUT INT8U *buf);


// 数组操作部分
//-------------------------------------------------
//【函数名称】        extern void BufToBuf
//【函数功能】        Buf到Buf转换()
//【参数说明】        
//【I:输入】          INT8U *buf1:待转换的数据指针入口
//                    const INT8U *buf2:转换后的指针入口
//                    INT16U len:需要转换的长度
//【O:输出】          
//【全局变量】       
//【返回值】         
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern void BufToBuf(TH_OUT INT8U *buf1,const TH_IN  INT8U *buf2, TH_IN INT16U len);

//-------------------------------------------------
//【函数名称】        extern void BufIsValue
//【函数功能】        为buf赋值
//【参数说明】        
//【I:输入】          INT8U *buf:转换后的指针入口
//                    INT8U data：待转换的数据
//                    INT16U len:需要转换的长度
//【O:输出】          
//【全局变量】       
//【返回值】         
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern void BufIsValue(TH_IN INT8U *buf, TH_IN INT16U len, TH_IN INT8U data);

//-------------------------------------------------
//【函数名称】        extern void BufIs0
//【函数功能】        Buf赋值为0
//【参数说明】        
//【I:输入】          INT8U *buf:转换后的指针入口
//                    INT16U len:需要转换的长度
//【O:输出】          
//【全局变量】       
//【返回值】         
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern void BufIs0(TH_IN INT8U *buf, TH_IN INT16U len);

//-------------------------------------------------
//【函数名称】        extern INT8U Check_Fmt2Bcd
//【函数功能】        数据转换后检测数据是否在合法的范围之内
//【参数说明】        
//【I:输入】         const INT16U vSrcData:待检测数据
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT8U 值：TRUE：合法 FALSE：非法
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U Check_Fmt2Bcd(TH_IN const INT16U vSrcData);

//检测部分
//-------------------------------------------------
//【函数名称】        extern INT8U Check_Bcd
//【函数功能】        检测数据是否在合法的范围之内
//【参数说明】        
//【I:输入】          const INT8U *buf:待检测的指针入口
//                    INT16U cnt:需要检测的长度
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT8U 值：TRUE：合法 FALSE：非法
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U Check_Bcd(TH_IN const INT8U *buf,INT16U cnt);

//-------------------------------------------------
//【函数名称】        extern INT8U Check_Bcd_Sign
//【函数功能】        BCD码检测
//【参数说明】        
//【I:输入】         const INT8U *vSrcBuf:待检测数据指针入口
//                   INT16U cnt:检测长度
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT8U 值：TRUE：合法 FALSE：非法
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U Check_Bcd_Sign(TH_IN const INT8U *buf,INT16U cnt);


//比较部分
//-------------------------------------------------
//【函数名称】        extern INT8U Check_Buf
//【函数功能】        两个数组进行比较
//【参数说明】        
//【I:输入】         const INT8U *pSrcBuf1:待比较的数组指针入口
//                   INT16U pSrcLen1:比较的数组长度
//                   const INT8U *pSrcBuf2:待比较的数组指针入口
//                   INT16U pSrcLen2:比较的长度
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT8U 值：TRUE：数组2是数组1的子集 FALSE：不是
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U Check_Buf(TH_IN const INT8U *pSrcBuf1,TH_IN INT16U pSrcLen1,TH_IN const INT8U *pSrcBuf2,TH_IN INT16U pSrcLen2);

//-------------------------------------------------
//【函数名称】        extern INT8U Compare4Buf
//【函数功能】        两个数组进行比较(只能最大4个字节比较)
//【参数说明】        
//【I:输入】         const INT8U *buf1:待比较的数组指针入口
//                   const INT8U *buf2:待比较的数组指针入口
//                   INT8U len:比较的长度
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT8U 值：BIG数组1>数组2,EQU相等，LIT小于
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U Compare4Buf(TH_IN const INT8U *buf1, TH_IN const INT8U *buf2, TH_IN INT8U len);

//-------------------------------------------------
//【函数名称】        extern INT8U Compare8Buf
//【函数功能】        两个数组进行比较(只能最大8个字节比较)
//【参数说明】        
//【I:输入】         const INT8U *buf1:待比较的数组指针入口
//                   const INT8U *buf2:待比较的数组指针入口
//                   INT8U len:比较的长度
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT8U 值：BIG数组1>数组2,EQU相等，LIT小于
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U Compare8Buf(TH_IN const INT8U *buf1, TH_IN const INT8U *buf2, TH_IN INT8U len);

//-------------------------------------------------
//【函数名称】        extern INT8U CompareNBuf
//【函数功能】        比较N个字节的大小,高位在后
//【参数说明】        
//【I:输入】         const INT8U *pSrcBuf1:待比较的数组指针入口
//                   const INT8U *pSrcBuf2:待比较的数组指针入口
//                   const INT8U pSrcLen:比较的长度
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT8U 值：BIG数组1>数组2,EQU相等，LIT小于
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U  CompareNBuf(TH_IN const INT8U *pSrcBuf1, TH_IN const INT8U *pSrcBuf2,TH_IN const INT16U pSrcLen);


//比较BUF是否是一个值
//-------------------------------------------------
//【函数名称】        extern INT8U CmpBufIsValue
//【函数功能】        比较BUF是否是一个值
//【参数说明】        
//【I:输入】         const INT8U *vSrcBuf:待比较的数组指针入口
//                   const INT8U pSrcLen:比较的数组长度
//                   INT8U vSrcCmpValue:比较的数据
//【O:输出】          
//【全局变量】       
//【返回值】          类型：INT8U 值：TRUE：是一个值 FALSE：不是
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U CmpBufIsValue(TH_IN const INT8U *vSrcBuf, TH_IN const INT16U vSrcLen, TH_IN const INT8U vSrcCmpValue);


//-------------------------------------------------
//【函数名称】        extern void TranBufSelf
//【函数功能】        数组指针的自转换（前后数据换位）
//【参数说明】        
//【I:输入】          INT8U *pDstBuf：待转换的数据指针
//                    INT16U len:待转换的长度
//【O:输出】          INT8U *pDstBuf:转换后的指针
//【全局变量】       
//【返回值】          
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern    void TranBufSelf(TH_INOUT INT8U *pDstBuf,TH_IN INT16U len);

//-------------------------------------------------
//【函数名称】        extern void TranBufToBuf
//【函数功能】        数组指针的转换
//【参数说明】        
//【I:输入】          const INT8U *pSrcBuf：待转换的数据指针
//                    INT16U len:待转换的长度
//【O:输出】          INT8U *pDstBuf:转换后的指针
//【全局变量】       
//【返回值】          
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern void TranBufToBuf(TH_IN const INT8U *pSrcBuf, TH_IN INT16U len, TH_OUT INT8U *pDstBuf);

//-------------------------------------------------
//【函数名称】        CreadAddCs
//【函数功能】        总加和算法
//【参数说明】        
//【I:输入】           const INT8U *pSrcBuf：待求和的数据指针
//                    INT16U len:数据的长度
//【O:输出】          
//【全局变量】       
//【返回值】          CS
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U  CreadAddCs(TH_IN const INT8U *vSrcBuf, TH_IN INT16U vSrcLen);

//-------------------------------------------------
//【函数名称】        CreadAddCs
//【函数功能】        比较CS是否正确
//【参数说明】        
//【I:输入】           const INT8U *pSrcBuf：待比较的数据指针
//                    INT16U len:数据的长度
//										vSrcCs:校验码
//【O:输出】          
//【全局变量】       
//【返回值】          TRUE，FALSE
//【函数属性】        public
//【备注】           
//【开发者及日期】
//-------------------------------------------------
extern INT8U  CmpAddCs(TH_IN const INT8U *vSrcBuf, TH_IN INT16U vSrcLen, TH_IN INT8U vSrcCs);

  //-----------------------------------------------------------------------------
	//【函数名称】	INT16U CalculateCRC(INT8U* InputData, INT16U DataLen)
	//【函数功能】	CRC16校验
	//【I：输入】		InputData:要校验的数据  DataLen：数据长度
	//【O:输出】		 无                   
	//【全局变量】		无
	//【返回值】		INT16U 类型的结果 
	//【函数属性】		
	//【备注】           
	//【开发者及日期】   
	//【版本】           
	//【更改记录】       
	//【修改人】
	//【修改日期】
	//【更改原因概要】    
	//-----------------------------------------------------------------------------
extern INT16U CalculateCRC(TH_IN INT8U* InputData, TH_IN INT16U DataLen); ///CRC16校验

  //-----------------------------------------------------------------------------
	//【函数名称】	void CalculateCRCToBuf2(TH_IN INT8U* InputData, TH_IN INT16U DataLen,TH_OUT INT8U *vDstBuf);
	//【函数功能】	CRC16校验，输出到数组中
	//【I：输入】		InputData:要校验的数据  DataLen：数据长度
	//【O:输出】		  vDstBuf ：输出的校验码                  
	//【全局变量】		无
	//【返回值】		 void  
	//【函数属性】		
	//【备注】           
	//【开发者及日期】   
	//【版本】           
	//【更改记录】       
	//【修改人】
	//【修改日期】
	//【更改原因概要】    
	//-----------------------------------------------------------------------------
extern void CalculateCRCToBuf2(TH_IN INT8U* InputData, TH_IN INT16U DataLen,TH_OUT INT8U *vDstBuf);

extern INT16U FileCalculateCRC(INT8U &CRCHi,INT8U &CRCLo,INT8U* InputData,INT16U DataLen);

extern INT32U  GetSysTimeClk(void);
extern INT32U  GetSysTimeInterval(INT32U vSrcTime);
//【类名称】       （必需）CEpMgBpFg
//【类功能】       （必需）对标志类的操作
//【成员变量说明】  (若有参数则必需注明 ，直接注到参数后面） 

class CEpMgBpFg
{

 public:
	 
			//-----------------------------------------------------------------------------
			//【函数名称】        CEpMgBpFg
			//【函数功能】        读写终端参数
			//【参数说明】          
			//【I:输入】          INT32U StartEp_Add:EP起始地址
			//                    INT32U EpAllLen：EP总长度
			//【O:输出】          
			//【全局变量】       
			//【返回值】          
			//【函数属性】        public
			//【备注】           
			//【开发者及日期】
			//-----------------------------------------------------------------------------
			CEpMgBpFg(INT8U *pSrcBuf,INT16U vSrcLen);

			//-----------------------------------------------------------------------------
			//【函数名称】        void SetEpFg
			//【函数功能】        设置标志
			//【参数说明】          
			//【I:输入】          INT16U vSrcFgBit：bit位
			//                    INT8U vSrcAck：0 和 1
			//【O:输出】          
			//【全局变量】       
			//【返回值】          
			//【函数属性】        public
			//【备注】           
			//【开发者及日期】
			//-----------------------------------------------------------------------------
			void SetEpFg(INT16U vSrcFgBit,INT8U vSrcAck);

			//-----------------------------------------------------------------------------
			//【函数名称】        INT8U QueEpFg
			//【函数功能】        读取标志（0开始）
			//【参数说明】          
			//【I:输入】          INT16U vSrcFgBit：bit位
			//【O:输出】          
			//【全局变量】       
			//【返回值】          
			//【函数属性】        public
			//【备注】           
			//【开发者及日期】
			//-----------------------------------------------------------------------------
			INT8U QueEpFg(INT16U vSrcFgBit);

			//-----------------------------------------------------------------------------
			//【函数名称】        INT8U QueEpAllFgIsOk
			//【函数功能】        读取所有标志（0开始）
			//【参数说明】          
			//【I:输入】          INT16U vSrcFgBit：bit位
			//【O:输出】          
			//【全局变量】       
			//【返回值】          
			//【函数属性】        public
			//【备注】           
			//【开发者及日期】
			//-----------------------------------------------------------------------------
			INT8U QueEpAllFgIsOk(INT16U vSrcFgBit);

 private:
	  INT8U *pFgBuf;
    INT16U FgLen;

};
#endif

