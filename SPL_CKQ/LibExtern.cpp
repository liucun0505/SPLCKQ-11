//#include "..\UserDefine\Define.h"
#include "stdafx.h"
#include "LibExtern.h"
//以下程序段为部分软件的库函数,上面的程序段为全部的硬件函数
//大端小端要考虑移植
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2
typedef union
{
    u_long LongValue;  //最多字节的要放最前面.保证起始地址会字(4字节)对齐.
    u_char Array[4];   //此处由大端改为小端,移植非常费劲,败笔!!尽量取消
    //移植完毕后的这个数组只用来传递数据首地址或者做纯数组使用
    struct
    {
        u_int Low, High;
    } IntValue;
    struct
    {
        u_char Low, Middle, Higher, Highest;
    } CharValue;
} Long_Char;



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// 函数名称: u_long Hex_Change_BCD(u_long HexValue)
// 调用范例: Send_Value.LongValue=Hex_Change_BCD(Temp_Value.LongValue);
// 功能描述: 将4字节16进制整数转换为压缩的4字节BCD码
// 调用模块: 无
// 备    注: 16进制数据不能太大,否则溢出部分会去掉,但不会出现错误,只是高位被去掉
// 输入参数: HexValue 16进制4字节整数
// 函数返回: 压缩BCD码 4字节整数
// 作　  者: 常某
// 最近修改日期: 2004.08.30
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
u_long Hex_Change_BCD(u_long HexValue)//thumb模式下15uS;ARM模式下4.3uS
{

    Long_Char BCDValue;

    BCDValue.LongValue = 0;
    BCDValue.CharValue.Low += (u_char)(HexValue % 10);
    HexValue /= 10;
    BCDValue.CharValue.Low += (u_char)(HexValue % 10) << 4;
    HexValue /= 10;
    if(HexValue == 0) goto RetBCD;
    BCDValue.CharValue.Middle += (u_char)(HexValue % 10);
    HexValue /= 10;
    if(HexValue == 0) goto RetBCD;
    BCDValue.CharValue.Middle += (u_char)(HexValue % 10) << 4;
    HexValue /= 10;
    if(HexValue == 0) goto RetBCD;
    BCDValue.CharValue.Higher += (u_char)(HexValue % 10);
    HexValue /= 10;
    if(HexValue == 0) goto RetBCD;
    BCDValue.CharValue.Higher += (u_char)(HexValue % 10) << 4;
    HexValue /= 10;
    if(HexValue == 0) goto RetBCD;
    BCDValue.CharValue.Highest += (u_char)(HexValue % 10);
    HexValue /= 10;
    if(HexValue == 0) goto RetBCD;
    BCDValue.CharValue.Highest += (u_char)(HexValue % 10) << 4;

RetBCD:
    return(BCDValue.LongValue);

}


/*
u_char Half_Char_Change_BCD(u_char HexValue)
  {
     if(HexValue>15) HexValue=0;
     if(HexValue>9) HexValue+=6;
     return(HexValue);

    }
*/
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// 函数名称: u_long Adjust_BCD_Code(u_long HexValue)
// 调用范例: Single_Phase.Energy.ActiveA=Adjust_BCD_Code(Single_Phase.Energy.ActiveA);
// 功能描述: 将压缩BCD码加 1-6 后,调整为压缩BCD码,加完低位会出现0xa等
// 调用模块: 无
// 备    注: 每次加的数据只能大于等于1而<=6,否则调整会错误,一般是+1然后做调整,这是BCD加的方法
// 输入参数: HexValue 压缩BCD码+1(或<6的其他数)后的数,有可能为非BCD码,
//                    比如0x89+1=0x8a,要调整为0x90,采用低位+6的方法调整
// 函数返回: 压缩BCD码 4字节整数
// 作　  者: 常某
// 最近修改日期: 2004.08.30
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
u_long Adjust_BCD_Code(u_long HexValue)
{
    Long_Char BCDValue;
    s_char i;

    BCDValue.LongValue = HexValue;

    for(i = 0; i < 4; i++) //如果为大端,则为 for(i=3;--...
    {
        if((BCDValue.Array[i] & 0xf) > 9) //判断低位,如果为非BCD码,则调整
        {
            BCDValue.Array[i] += 6;
            if((BCDValue.Array[i] & 0xf0) > 0x90)
            {
                BCDValue.Array[i] += 0x60;
                if(i == 3) break;
                BCDValue.Array[i + 1] += 1;
            }
            else break;
        }
        else break;
    }
    return(BCDValue.LongValue);
}



void BCDValue_Add(u_long &BCDValue_Sum, u_long BCDValue_Data)
{
    s_char i;
    byte ByteValue = 0;

    volatile u_char *pBCDValue = (u_char *)&BCDValue_Sum;

    for(i = 0; i < 4; i++) //大端 为for(i=3;i>=0;i--)
    {
        ByteValue = (*(pBCDValue + i) & 0xf) + ((u_char)BCDValue_Data & 0xf) + (ByteValue >> 4);
        if(ByteValue > 9) ByteValue += 6;
        *(pBCDValue + i) = (*(pBCDValue + i) & 0xf0) + ByteValue;

        ByteValue = (*(pBCDValue + i) >> 4) + ((u_char)BCDValue_Data >> 4);
        if(ByteValue > 9) ByteValue += 6;
        *(pBCDValue + i) = (*(pBCDValue + i) & 0xf) + (ByteValue << 4);
        BCDValue_Data >>= 8;
    }

    BCDValue_Sum = *(u_long *)pBCDValue; //小端模式可以这样转换. 大端呢????

}


void BCDValue_Subb(u_long &BCDValue_Sub, u_long BCDValue_Data)
{
    s_char i;
    byte ByteValue = 0;
    volatile u_char *pBCDValue = (u_char *)&BCDValue_Sub;

    for(i = 0; i < 4; i++) //大端 for(i=3;i>=0;i--)
    {
        ByteValue += (u_char)BCDValue_Data & 0xf;
        if((*(pBCDValue + i) & 0xf) < ByteValue)
        {
            *(pBCDValue + i) += 10 - ByteValue;
            ByteValue = 1;
        }
        else
        {
            *(pBCDValue + i) -= ByteValue;
            ByteValue = 0;
        }

        ByteValue += (u_char)BCDValue_Data >> 4;
        if((*(pBCDValue + i) >> 4) < ByteValue)
        {
            *(pBCDValue + i) += (10 - ByteValue) << 4;
            ByteValue = 1;
        }
        else
        {
            *(pBCDValue + i) -= ByteValue << 4;
            ByteValue = 0;
        }
        BCDValue_Data >>= 8;

    }

    BCDValue_Sub = *(u_long *)pBCDValue; //小端模式可以这样转换. 大端呢????


}


/*
u_int BCD_Change_Hex(u_int BCDValue)//,u_char num_)
{

  u_int X=0,Y=1;
  for(u_char i=0;i<4;i++)
  {
    X+=(BCDValue&0xf)*Y;
    BCDValue>>=4;
    Y*=10;
   }
  return(X);
}  */

//#if isProtocol_Wasion!=0
u_long BCD_Change_Hex(u_long BCDValue)//,u_char num_)
{

    u_long X = 0, Y = 1;
    for(u_char i = 0; i < 8; i++)
    {
        X += (BCDValue & 0xf) * Y;
        BCDValue >>= 4;
        Y *= 10;
    }
    return(X);
    /*
      Long_Char Change_Value;
      Change_Value.LongValue=*pBCDValue;


      //大端 *pBCDValue=(Change_Value.Array[3]>>4)*10+(Change_Value.Array[3]&0xf)+(Change_Value.Array[2]>>4)*1000+(u_int)(Change_Value.Array[2]&0xf)*100
      //大端               +(Change_Value.Array[1]>>4)*100000+(u_long)(Change_Value.Array[1]&0xf)*10000+(Change_Value.Array[0]>>4)*10000000+(Change_Value.Array[0]&0xf)*1000000;
       *pBCDValue=(Change_Value.CharValue.Low>>4)*10+(Change_Value.CharValue.Low&0xf)+(Change_Value.CharValue.Middle>>4)*1000+(u_int)(Change_Value.CharValue.Middle&0xf)*100
                     +(u_long)(Change_Value.CharValue.Higher>>4)*100000+(u_long)(Change_Value.CharValue.Higher&0xf)*10000+(u_long)(Change_Value.CharValue.Highest>>4)*10000000+(u_long)(Change_Value.CharValue.Highest&0xf)*1000000;
    */
}
//#endif



void SBCDValue_Subb(u_long &BCDValue_Sub, u_long BCDValue_Data)
{
    s_long Hex_Sub, Hex_Data;
    if(BCDValue_Sub & 0x80000000) Hex_Sub = -BCD_Change_Hex(BCDValue_Sub & ~0x80000000);
    else Hex_Sub = BCD_Change_Hex(BCDValue_Sub);

    if(BCDValue_Data & 0x80000000) Hex_Data = -BCD_Change_Hex(BCDValue_Data & ~0x80000000);
    else Hex_Data = BCD_Change_Hex(BCDValue_Data);
    Hex_Sub -= Hex_Data;
    if(Hex_Sub < 0) BCDValue_Sub = (Hex_Change_BCD(-Hex_Sub)) | 0x80000000;
    else BCDValue_Sub = Hex_Change_BCD(Hex_Sub);

}





/*
void BCDValue_Add(u_char *pBCDValue,u_long BCDValue_Data)
  {
     s_char i;
     byte ByteValue=0;

    for(i=0;i<4;i++)//大端 为for(i=3;i>=0;i--)
     {
      ByteValue=(*(pBCDValue+i)&0xf)+((u_char)BCDValue_Data&0xf)+(ByteValue>>4);
      if(ByteValue>9) ByteValue+=6;
      *(pBCDValue+i)=(*(pBCDValue+i)&0xf0)+ByteValue;

      ByteValue=(*(pBCDValue+i)>>4)+((u_char)BCDValue_Data>>4);
      if(ByteValue>9) ByteValue+=6;
      *(pBCDValue+i)=(*(pBCDValue+i)&0xf)+(ByteValue<<4);
      BCDValue_Data>>=8;
      }

     }


void BCDValue_Subb(u_char *pBCDValue,u_long BCDValue_Data)
  {
     s_char i;
     byte ByteValue=0;

     for(i=0;i<4;i++)  //大端 for(i=3;i>=0;i--)
     {
      ByteValue+=(u_char)BCDValue_Data&0xf;
      if((*(pBCDValue+i)&0xf)<ByteValue)
	{
	  *(pBCDValue+i)+=10-ByteValue;
	  ByteValue=1;
          }
      else
	{
	  *(pBCDValue+i)-=ByteValue;
	  ByteValue=0;
          }

      ByteValue+=(u_char)BCDValue_Data>>4;
      if((*(pBCDValue+i)>>4)<ByteValue)
	{
	  *(pBCDValue+i)+=(10-ByteValue)<<4;
	  ByteValue=1;
          }
      else
	{
	  *(pBCDValue+i)-=ByteValue<<4;
	  ByteValue=0;
          }
      BCDValue_Data>>=8;

      }

  }


#if isProtocol_Wasion!=0
void BCD_Change_Hex(u_long *pBCDValue)//,u_char num_)
{
  Long_Char Change_Value;
  Change_Value.LongValue=*pBCDValue;


  //大端 *pBCDValue=(Change_Value.Array[3]>>4)*10+(Change_Value.Array[3]&0xf)+(Change_Value.Array[2]>>4)*1000+(u_int)(Change_Value.Array[2]&0xf)*100
  //大端               +(Change_Value.Array[1]>>4)*100000+(u_long)(Change_Value.Array[1]&0xf)*10000+(Change_Value.Array[0]>>4)*10000000+(Change_Value.Array[0]&0xf)*1000000;
   *pBCDValue=(Change_Value.CharValue.Low>>4)*10+(Change_Value.CharValue.Low&0xf)+(Change_Value.CharValue.Middle>>4)*1000+(u_int)(Change_Value.CharValue.Middle&0xf)*100
                 +(u_long)(Change_Value.CharValue.Higher>>4)*100000+(u_long)(Change_Value.CharValue.Higher&0xf)*10000+(u_long)(Change_Value.CharValue.Highest>>4)*10000000+(u_long)(Change_Value.CharValue.Highest&0xf)*1000000;
  }
#endif

*/


u_long Int_Change_BCD(u_int HexValue)
{
    return(Hex_Change_BCD(HexValue));
}

u_int Char_Change_BCD(u_char HexValue)
{
    if(HexValue > 15) return((u_int)Hex_Change_BCD(HexValue));
    else if(HexValue > 9) HexValue += 6;
    return(HexValue);

}


/*
u_long Int_Change_BCD(u_int HexValue)
   {

     Long_Char BCDValue;
     Int_Char AddValue;

     BCDValue.LongValue=0;
     for(;BCDValue.CharValue.Highest<16;BCDValue.CharValue.Highest++)
     {
      if(HexValue&0x8000) AddValue.IntValue=1;
      else AddValue.IntValue=0;
      HexValue<<=1;
      AddValue.CharValue.Low=AddValue.CharValue.Low+(BCDValue.CharValue.Low&0xf)+(BCDValue.CharValue.Low&0xf);
      if(AddValue.CharValue.Low>9)  AddValue.CharValue.Low+=0x6;
      AddValue.IntValue=AddValue.IntValue+(BCDValue.CharValue.Low&0xf0)+(BCDValue.CharValue.Low&0xf0);
      if((AddValue.CharValue.High>=1)||(AddValue.CharValue.Low>0x99)) AddValue.IntValue+=0x60;
      BCDValue.CharValue.Low=AddValue.CharValue.Low;
      AddValue.IntValue=AddValue.CharValue.High;

      AddValue.CharValue.Low=AddValue.CharValue.Low+(BCDValue.CharValue.Middle&0xf)+(BCDValue.CharValue.Middle&0xf);
      if(AddValue.CharValue.Low>9)  AddValue.CharValue.Low+=0x6;
      AddValue.IntValue=AddValue.IntValue+(BCDValue.CharValue.Middle&0xf0)+(BCDValue.CharValue.Middle&0xf0);
      if((AddValue.CharValue.High>=1)||(AddValue.CharValue.Low>0x99)) AddValue.IntValue+=0x60;
      BCDValue.CharValue.Middle=AddValue.CharValue.Low;
      AddValue.IntValue=AddValue.CharValue.High;

      AddValue.CharValue.Low=AddValue.CharValue.Low+(BCDValue.CharValue.Higher&0xf)+(BCDValue.CharValue.Higher&0xf);
      if(AddValue.CharValue.Low>9)  AddValue.CharValue.Low+=0x6;
      AddValue.IntValue=AddValue.IntValue+(BCDValue.CharValue.Higher&0xf0)+(BCDValue.CharValue.Higher&0xf0);
      if((AddValue.CharValue.High>=1)||(AddValue.CharValue.Low>0x99)) AddValue.IntValue+=0x60;
      BCDValue.CharValue.Higher=AddValue.CharValue.Low;
      AddValue.IntValue=AddValue.CharValue.High;
      }
      BCDValue.CharValue.Highest=0;
      return(BCDValue.LongValue);
      }


u_int Char_Change_BCD(u_char HexValue)
   {

     Int_Char BCDValue;
     byte i;
     Int_Char AddValue;

     BCDValue.IntValue=0;
     for(i=8;i!=0;i--)
     {
      if(HexValue&0x80) AddValue.IntValue=1;
      else AddValue.IntValue=0;
      HexValue<<=1;
      AddValue.CharValue.Low=AddValue.CharValue.Low+(BCDValue.CharValue.Low&0xf)+(BCDValue.CharValue.Low&0xf);
      if(AddValue.CharValue.Low>9)  AddValue.CharValue.Low+=0x6;
      AddValue.IntValue=AddValue.IntValue+(BCDValue.CharValue.Low&0xf0)+(BCDValue.CharValue.Low&0xf0);
      if((AddValue.CharValue.High>=1)||(AddValue.CharValue.Low>0x99)) AddValue.IntValue+=0x60;
      BCDValue.CharValue.Low=AddValue.CharValue.Low;
      AddValue.IntValue=AddValue.CharValue.High;

      AddValue.CharValue.Low=AddValue.CharValue.Low+(BCDValue.CharValue.High&0xf)+(BCDValue.CharValue.High&0xf);
      if(AddValue.CharValue.Low>9)  AddValue.CharValue.Low+=0x6;
      AddValue.IntValue=AddValue.IntValue+(BCDValue.CharValue.High&0xf0)+(BCDValue.CharValue.High&0xf0);
      if((AddValue.CharValue.High>=1)||(AddValue.CharValue.Low>0x99)) AddValue.IntValue+=0x60;
      BCDValue.CharValue.High=AddValue.CharValue.Low;
      AddValue.IntValue=AddValue.CharValue.High;

      }

      return(BCDValue.IntValue);
      }


*/

bool CheckBCD(u_long Value)
{

    for(u_char i = 0; i < 8; i++)
    {
        if((Value & 0xf) > 9) return(false);
        Value >>= 4;
    }
    return(true);
}


bool CheckBCD(u_int Value)
{

    for(u_char i = 0; i < 4; i++)
    {
        if((Value & 0xf) > 9) return(false);
        Value >>= 4;
    }
    return(true);
}

bool CheckBCD(u_char Value)
{

    for(u_char i = 0; i < 2; i++)
    {
        if((Value & 0xf) > 9) return(false);
        Value >>= 4;
    }
    return(true);
}

// --------------------------------------------------------------
//      CRC16计算方法1:使用2个256长度的校验表
// --------------------------------------------------------------
const u_char CRCHTalbe[] =                                 // CRC 高位字节值表
{
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40
};

const u_char CRCLTalbe[] =                                 // CRC 低位字节值表
{
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
    0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
    0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
    0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
    0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
    0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
    0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
    0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
    0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
    0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
    0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
    0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
    0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40
};


u_int CalculateCRC(u_char *InputData, u_int DataLen)
{
    u_char CRCHi = 0xFF; // 高CRC字节初始化
    u_char CRCLo = 0xFF; // 低CRC字节初始化
    u_char Index;            // CRC循环中的索引

    while (DataLen--)
    {
        // 计算CRC
        Index = CRCLo ^ (*InputData);
        InputData++;
        CRCLo = CRCHi ^ CRCHTalbe[Index];
        CRCHi = CRCLTalbe[Index];
    }

    return (((u_int)CRCHi << 8) | CRCLo);
}


