#ifndef __LibExtern
#define __LibExtern

//#include "..\UserDefine\Define.h"
//#include "..\UserTarget\CClock.h" //用到TIME结构.



typedef unsigned char  byte;                    //无符号8位数据
typedef unsigned char b_flag;                   //替代以前的bit 定义

typedef unsigned char  u_char;                    /* 无符号8位整型变量                        */
typedef signed   char  s_char;                    /* 有符号8位整型变量                        */
//typedef unsigned short u_int;                     /* 无符号16位整型变量                       */
typedef signed   short s_int;                     /* 有符号16位整型变量                       */
//typedef unsigned int   u_long;                    /* 无符号32位整型变量                       */
typedef signed   int   s_long;                    /* 有符号32位整型变量                       */
typedef float    single_float;                    /* 单精度浮点数（32位长度）                 */
typedef double   double_float;                    /* 双精度浮点数（64位长度）                 */


extern u_long Hex_Change_BCD(u_long HexValue);
extern u_long Int_Change_BCD(u_int HexValue);
extern u_long BCD_Change_Hex(u_long BCDValue);
//extern u_int BCD_Change_Hex(u_int BCDValue);
//extern u_char Half_Char_Change_BCD(u_char HexValue);
extern u_int Char_Change_BCD(u_char HexValue);
extern u_long Adjust_BCD_Code(u_long HexValue);
extern void BCDValue_Add(u_long &BCDValue_Sum, u_long BCDValue_Data);
extern void BCDValue_Subb(u_long &BCDValue_Sub, u_long BCDValue_Data);
extern void SBCDValue_Subb(u_long &BCDValue_Sub, u_long BCDValue_Data);

extern bool CheckBCD(u_long Value);
extern bool CheckBCD(u_int Value);
extern bool CheckBCD(u_char Value);
extern u_int CalculateCRC(u_char *InputData, u_int DataLen); ///CRC16校验

#endif

