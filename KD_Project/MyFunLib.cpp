/*---------------------------------------------------------------------------------
* Copyright (c)  2016 TENHE  TECHNOLOGY
* All rights reserved.
*
* 文件名称：MyFunLib.cpp

* 摘    要： 自己调用的库函数，一些小算法等
*
* 当前版本：1.1
* 作    者：赵震
* 完成日期：2016年6月29日
*
* 取代版本：
* 原 作 者：
* 完成日期：
*------------------------------------------------------------------------------*/
#include "stdafx.h"
#include "MyFunLib.h"
//#include "User_Ack_Def.h"
void StaSucessCnt(INT8U ack,INT16U &allSucesscnt,INT16U &failCnt)
{
	if(ack == DACK_SUCESS)
	{
		allSucesscnt++;
	}
	else
	{
       failCnt++;
	}
}
INT8U QueAckFormAckCnt(INT16U failCnt)
{
	if(failCnt>0)
	{
		return DACK_FAILURE;
	}
	else
	{
		return DACK_SUCESS;
	}
}
 INT32U  GetSysTimeClk(void)
 {
	INT32U tmp32;
	 tmp32 = GetTickCount();
	return tmp32;
 }
 INT32U  GetSysTimeInterval(INT32U vSrcTime)
 {
	 INT32U tmp32;

	tmp32 = GetSysTimeClk();
	if (tmp32 >= vSrcTime)
	{
		tmp32 -= vSrcTime;
	}
	else
	{
		tmp32 += 0xFFFFFFFF - vSrcTime;
	}
	//tmp32 *= SYSTEM_TIMER_TIME;
	
	return tmp32;
 }
 INT32U QueSysTimeVal(INT32U vSrcTime,INT32U vSrcTime2)
 {
	  INT32U tmp32=vSrcTime2;

	if (tmp32 >= vSrcTime)
	{
		tmp32 -= vSrcTime;
	}
	else
	{
		tmp32 += 0xFFFFFFFF - vSrcTime;
	}
	
	return tmp32;
 }
INT16U ascii_2_hex(TH_IN INT8U *O_data, TH_OUT INT8U *N_data, TH_IN INT16U len)
{
   INT16U i,j;
   INT16U tmp_len;
   INT8U tmpData;
   INT8U *O_buf = O_data;
   INT8U *N_buf = N_data;   
   for(i=0; i<len; i++)
   {
      if ((O_buf[i] >= '0') && (O_buf[i] <= '9'))
      {
				tmpData = O_buf[i] - '0';
      }
      else  if ((O_buf[i] >= 'A') && (O_buf[i] <= 'F'))  //A....F
      {
				tmpData = O_buf[i] - 0x37;
			}
      else if((O_buf[i] >= 'a') && (O_buf[i] <= 'f'))  //a....f
      {
				tmpData = O_buf[i] - 0x57;
			}
			else
			{
				return 0;
			}
      O_buf[i] =  tmpData;
    }   
    for(tmp_len=0, j=0; j<i; j+=2)
    {
			N_buf[tmp_len++] = (O_buf[j]<<4) | O_buf[j+1];
    }   
    return tmp_len;	
}

//ASC码长度不清楚的情况下用
//ASC码转换成16进制，最大长度为512,返回数据长度
INT16U   ascii_2_hex_string(TH_IN INT8U *O_data, TH_IN INT16U vSrcLen1, TH_OUT INT8U *N_data, TH_IN INT16U vSrcLen2)
{
   INT16U i,j;
   INT16U tmp_len=0;
   INT8U tmpData;
   INT8U *O_buf = O_data;
   INT8U *N_buf = N_data;
   
   for(i = 0; i < vSrcLen1; i++)
   {
      if(O_buf[i]=='\0')
         break;
      if ((O_buf[i] >= '0') && (O_buf[i] <= '9'))
      {
				tmpData = O_buf[i] - '0';
      }
      else  if ((O_buf[i] >= 'A') && (O_buf[i] <= 'F'))  //A....F
      {
				tmpData = O_buf[i] - 0x37;
			}
      else if((O_buf[i] >= 'a') && (O_buf[i] <= 'f'))  //a....f
      {
				tmpData = O_buf[i] - 0x57;
			}
			else
			{
				return 0;
			}	
      O_buf[i] =  tmpData;
    }    
    for(tmp_len = 0,j = 0; j < i; j+=2)
    {
			if( tmp_len<vSrcLen2)
			N_buf[tmp_len++] = (O_buf[j]<<4) | O_buf[j+1];
    }    
    return tmp_len;	
}

INT16U  hex_2_ascii(TH_IN const INT8U *data, TH_OUT INT8U *buffer, TH_IN INT8U len)
{
    INT8U const  ascTable[17] = {"0123456789ABCDEF"};
    INT8U *tmp_p = buffer;   
    INT8U i;
    INT16U pos;
    pos = 0;
    
    for(i = 0; i < len; i++)
    {
    	tmp_p[pos++] = ascTable[data[i] >> 4];
    	tmp_p[pos++] = ascTable[data[i] & 0x0f]; 
    }    
    tmp_p[pos] = '\0';    
    return pos;    			
}

INT8U bin8_to_asciiBuf(TH_IN INT8U bcdbin, TH_OUT INT8U *buffer)
{
    
    INT8U   const  ascTable[17] = {"0123456789"};
    INT8U *tmp_p = buffer;
    INT8U temp;   
    INT8U i, pos;
    pos = 0;
    temp = bcdbin;
    i = temp/100;
    if(i)
    { 
      temp = temp%100;
      tmp_p[pos++] = ascTable[i];
    }
    i = temp/10;
    if(i)
    {
			temp = temp%10;
			tmp_p[pos++] = ascTable[i];
    }
    else if(pos != 0)
		{
			tmp_p[pos++] = ascTable[0];
		}
		tmp_p[pos++] = ascTable[temp];
		return pos;
}

INT8U ascii_to_bin8Buf(TH_IN INT8U len, TH_OUT INT8U *buffer)
{ 
    INT8U *tmp_p = buffer;
    INT8U temp,binbcd = 0;
    INT8U templen;
    INT8U i = 0;
    templen = len;
    if(templen > 3)
		{ 
			templen = 3;
			templen -= 1;
			binbcd = tmp_p[i++]-'0';
			binbcd *= 100;		 
		}
     
    if(templen == 2)
    {
     templen -= 1;
     temp = (tmp_p[i++]-'0');
     temp = temp*10;
     binbcd += temp;        
    }
    binbcd += (tmp_p[i++]-'0');
    return binbcd;
}

INT8U bin16_to_asciiBuf(TH_IN INT16U bcdbin, TH_OUT INT8U *buffer)
{    
		INT8U const  ascTable[17] = {"0123456789"};
		INT8U *tmp_p = buffer;
		INT16U temp;    
		INT8U i, pos;
		pos = 0;
		temp = bcdbin;
		i = temp/10000;
		if(i)
		{ 
			temp = temp%10000;
			tmp_p[pos++] = ascTable[i];
		}
    i = temp/1000;
    if(i)
    {
			temp = temp%1000;
			tmp_p[pos++] = ascTable[i];
    }
    else if(pos != 0)
		{
			tmp_p[pos++] = ascTable[0];
		}
		i = temp/100;     
		if(i)
    {
			temp = temp%100;
			tmp_p[pos++] = ascTable[i];
    }
    else if(pos != 0)
		{
			tmp_p[pos++] = ascTable[0];
		}
    i = temp/10 ;   
		if(i)
		{
			temp = temp%10;
			tmp_p[pos++] = ascTable[i];
		}
    else if(pos != 0)
		{
			tmp_p[pos++] = ascTable[0];
		}
     tmp_p[pos++] = ascTable[temp];
     return pos;
}

  //查义0到F的ASCII转换
INT8U Ascii0ToF(TH_IN INT8U vSrcData)
{
  INT8U   const  ascTable[17] = {"0123456789ABCDEF"};
  if( vSrcData <= 0x0f)
  {
    return 	 ascTable[vSrcData];
  }
  return '0' ;
}

//BCD 和 HEX  转换部分
INT8U BcdToHex(TH_IN INT8U data)
{
  INT8U temp;
  INT8U i;
  temp = data;
  i = temp&0xf0;
  i >>= 4;
  i *= 10;
  temp = temp&0x0f;
  i += temp;
  return i;
}

INT8U HexToBcd(TH_IN const INT8U data)
{
  INT8U temp;
  INT8U i;
  temp = data%100;
  i = temp/10;
  i <<= 4;
  temp = temp%10;
  i |= temp;
  return i;
}

INT32U BcdBuf4ToHex32(TH_IN const INT8U *buf)
{ 
	INT32U hex32 = 0x00;
	hex32 += (buf[3]>>4)*10000000;
	hex32 += (buf[3]&0x0f)*1000000;
	hex32 += (buf[2]>>4)*100000;
	hex32 += (buf[2]&0x0f)*10000;
	hex32 += (buf[1]>>4)*1000;
	hex32 += (buf[1]&0x0f)*100;
	hex32 += (buf[0]>>4)*10;
	hex32 += buf[0]&0x0f;
	return hex32;
}
 
void Hex32ToBcdBuf4(TH_IN INT32U Hex32, TH_OUT INT8U *buf)
{ 
	INT32U temp32;
	INT8U temp;
	temp32 = Hex32%100000000;
	temp = temp32/10000000;
	temp32 %= 10000000;
	buf[3] = temp;
	buf[3] <<= 4;
	temp = temp32/1000000;
	temp32 %= 1000000;
	buf[3] |= temp; 
	temp = temp32/100000;
	temp32 %= 100000;
	buf[2] = temp;
	buf[2] <<= 4;
	temp = temp32/10000;
	temp32 %= 10000;
	buf[2] |= temp;
	temp = temp32/1000;
	temp32 %= 1000;
	buf[1] = temp;
	buf[1] <<= 4;
	temp = temp32/100;
	temp32 %= 100;
	buf[1] |= temp;
	temp = temp32/10;
	temp32 %= 10;
	buf[0] = temp;
	buf[0] <<= 4;
	buf[0] |= temp32;  
}

INT32U BcdToHex32NByte(TH_IN INT8U *buf, TH_IN INT8U len)
{  
	INT32U hex32 = 0x00;
	INT8U i;
	for(i=len; i>0; i--)
	{
		hex32 *= 10;
		hex32 += (buf[i-1]>>4);
		hex32 *= 10;
		hex32 += (buf[i-1]&0x0f);  
  }
   return hex32;
}
  //Len是数组的长度，也就是位数，2个长度，表示BCD码四个。
void Hex32ToBcdNByte(TH_IN INT32U bcd32, TH_IN INT8U len, TH_OUT INT8U *buf)
{ 
	INT32U temp32;
	INT32U tempdiv = 1;
	INT8U i,j;
	temp32 = bcd32;
	for(i=len; i>0; i--)
	{
		tempdiv = 1;
		for(j=2*i-1; j>0; j--)
		tempdiv *= 10;
		buf[i-1] = temp32/tempdiv;
		buf[i-1] <<= 4;
		temp32 %= tempdiv;
		tempdiv /= 10;
		buf[i-1] |= temp32/tempdiv;
		temp32 %= tempdiv;
	}
}

INT16U Bcd16ToHex16(TH_IN INT16U data)
{
   INT16U hex16=0;
   hex16 += ((data>>12)&0x0f)*1000;
   hex16 += ((data>>8)&0x0f)*100;
   hex16 += ((data>>4)&0x0f)*10;
   hex16 += data&0x0f;
   return hex16;
}

INT16U Hex16ToBcd16(TH_IN INT16U data)
{
   INT16U temp32;
   INT8U temp;
   INT16U ack16 = 0;
   temp32 = data%10000;  
   temp = temp32/1000;
   temp32 %= 1000;
   ack16=temp;
   ack16 <<= 4;
   temp = temp32/100;
   temp32 %= 100;
   ack16 |= temp;
    ack16 <<= 4;
   temp = temp32/10;
   temp32 %= 10;
   ack16 |= temp;
   ack16 <<= 4;
   ack16 |= temp32;
   return ack16;
}

// BUF 转换 HEX部分
void Hex16ToBuf2(TH_IN INT16U data, TH_OUT INT8U *buf)
{
	buf[0] = (INT8U)data;
	buf[1] = (INT8U)(data>>8);
}

void Hex32ToBuf4(TH_IN INT32U data, TH_OUT INT8U *buf)
{
	buf[0] =  (INT8U)data;
	buf[1] =   (INT8U)(data>>8);
	buf[2] =  (INT8U)(data>>16);
	buf[3] =  (INT8U)(data>>24);
}
 
INT16U Buf2ToHex16(TH_IN const INT8U *buf)
{
	INT16U hex16 = 0;
	hex16 = buf[1];
	hex16 <<= 8;
	hex16 |= buf[0];
	return hex16; 
}
 
INT32U Buf4ToHex32(TH_IN const INT8U *buf)
{
	return(NBufToHex32(buf,4));
}

INT32U Buf3ToHex32(TH_IN const INT8U *buf)
{
	return(NBufToHex32(buf,3)); 
}
 
INT32U NBufToHex32(TH_IN const INT8U *buf,TH_IN INT8U len)
{
	INT32U hex32 = 0;
	INT8U i = len;
	if(i>4) i=4;//低4字节为主
	for(; i>0; i--)
	{
		hex32 <<= 8;
		hex32 |= buf[i-1];
	}
	return hex32;
}
	
INT32U Bcd32ToHex32(TH_IN INT32U pSrcBcd32)
{
	INT8U tmpbuf[4];
	INT32U tmp32;
	tmpbuf[0] = pSrcBcd32;
	tmpbuf[1] = pSrcBcd32>>8;
	tmpbuf[2] = pSrcBcd32>>16;
	tmpbuf[3] = pSrcBcd32>>24;
	tmp32 = BcdBuf4ToHex32(tmpbuf);
	return tmp32;
}

INT32U Hex32ToBcd32(TH_IN INT32U pSrcHex32)
{
 INT8U tmpbuf[4];
 INT32U tmp32;
 Hex32ToBcdBuf4(pSrcHex32,tmpbuf);
 tmp32 = Buf4ToHex32(tmpbuf);
 return tmp32;
}

void Hex32ToBuf3(TH_IN INT32U data, TH_OUT INT8U *buf)
{
	buf[0] = data;
	buf[1] = data>>8;
	buf[2] = data>>16;
}

// 数组操作部分
void BufToBuf(TH_OUT INT8U *buf1, TH_IN const INT8U *buf2,TH_IN INT16U len)
{
	INT16U i;
	INT16U j;
	j = len;
	for(i=0; i<j; i++)
	buf1[i] = buf2[i];
}

void BufIsValue(TH_IN INT8U *buf, TH_IN INT16U len, TH_IN INT8U data)
{
	for(INT16U m=0; m<len; m++)
	buf[m] = data;
}

void BufIs0(TH_IN INT8U *buf,TH_IN INT16U len)
{
	BufIsValue(buf,len,0);
}

  
//检测部分
//BCD码检测
INT8U Check_Bcd(TH_IN const INT8U *buf, TH_IN INT16U cnt)
{
	INT16U i;
	for(i=0; i<cnt; i++)
	{
		if(((buf[i]&0x0f) > 0x09) || ((buf[i]&0xf0) > 0x90)) 
		return DACK_FAILURE;
	}
	return DACK_SUCESS;
}

INT8U Check_Bcd_Sign(TH_IN const INT8U *buf, TH_IN INT16U cnt)
{
	INT16U i;
	for(i=0; i<cnt; i++)
	{
		if(((buf[i]&0x0f)>0x09))//||((buf[i]&0xf0)>0x90)) yhynote :为了快速07，只判断半个BCD
		return DACK_FAILURE;
	}
	return DACK_SUCESS;
}

INT8U Check_Fmt2Bcd(TH_IN const INT16U vSrcData)
{
  INT8U tmpbuf[2];
  tmpbuf[0] = (INT8U)vSrcData;
  tmpbuf[1] = (INT8U)(vSrcData>>8);
  tmpbuf[1] &= 0x0f;
  return(Check_Bcd(tmpbuf,2));
}

//比较部分
//2个数组和第一个数组的子集，返因正确
INT8U Check_Buf(TH_IN const TH_IN INT8U *pSrcBuf1, TH_IN INT16U pSrcLen1,TH_IN const INT8U *pSrcBuf2, TH_IN INT16U pSrcLen2)
{
	INT16U i = 0,j = 0;
	while(i < pSrcLen1)
	//get_fse(0x0a,1,0x0a,2);//从第1个换行符，到第2个换行符
	{	 
	while(i < pSrcLen1) 
	{
		if(pSrcBuf1[i] == pSrcBuf2[0]) break;
		i++;
	}
	j = 0;
	while ((pSrcBuf2[j]!=0) && (i<pSrcLen1))
	{
		if(pSrcBuf1[i] != pSrcBuf2[j])
		{   
		break;
		}
		i++;
		j++;
		if(j >= pSrcLen2)
		return DACK_SUCESS;
	}
	i++;
	}
	return DACK_FAILURE;
}
//只能最大4个字节比较
INT8U Compare4Buf(TH_IN const INT8U *buf1, TH_IN const INT8U *buf2, TH_IN INT8U len)
{
	INT8U i;
	INT8U templen=len;
	INT32U cpmbase=0;
	INT32U cmpsrc=0;
	INT8U ack=EQU;
	if(templen>4)  
		templen=4;
	for(i=templen; i>0; i--)
	{
		cpmbase <<= 8;
		cmpsrc <<= 8;
		cpmbase |= buf1[i-1];
		cmpsrc |= buf2[i-1];
	}
	if(cpmbase > cmpsrc)
		 ack = BIG;
	else if(cpmbase == cmpsrc)
		 ack = EQU;
	else
		 ack = LIT;
	return ack; 
}
 
//最大8个字节的比较
INT8U Compare8Buf(TH_IN const INT8U *buf1, TH_IN const INT8U *buf2, TH_IN INT8U len)
{
	INT8U ack = EQU;
	INT8U len8 = len;
	if(len8 > 4)
	{
		len8 = 4;
		ack = Compare4Buf(&buf1[4],&buf2[4],len-4);
	}
	if(ack == EQU)
	{
		ack = Compare4Buf(buf1,buf2,len8);
	}
	return ack;
}
 
  //比较N个字节的大小,高位在后
INT8U  CompareNBuf(TH_IN const INT8U *pSrcBuf1, TH_IN const INT8U *pSrcBuf2, TH_IN const INT16U pSrcLen)
{
  INT16U i;
  INT8U ack;
  for(i=pSrcLen; i>0; i--)
    {
     if(pSrcBuf1[i-1] > pSrcBuf2[i-1]) 
       {
         ack=BIG;
         break;
       }
       if(pSrcBuf1[i-1] < pSrcBuf2[i-1]) 
       {
         ack=LIT;
         break;
       }
    }
	if(i == 0)
	ack=EQU; 
	return ack;
}

//比较BUF是否是一个值
INT8U CmpBufIsValue(TH_IN const INT8U *vSrcBuf, TH_IN const INT16U vSrcLen, TH_IN const INT8U vSrcCmpValue)
{
  for(INT16U m=0; m<vSrcLen; m++)
  {
		if(vSrcBuf[m] != vSrcCmpValue)
		return DACK_FAILURE;
  }
	return DACK_SUCESS;
}

 //查询长度转换成标识
 //返回数组的下标,BIT位
INT16U QueBufToFg(TH_IN INT16U vSrcLen, TH_IN INT8U &vDstBit)
{
  INT16U tmp16;
  tmp16 = vSrcLen/8;
  if(vSrcLen == 0)
     vDstBit = Bit0;
  else
   {
     vDstBit = (vSrcLen-1)%8;
     vDstBit = Bit0<<vDstBit;    
   }
   return tmp16;
}

 
//数组指针的自转换（前后数据换位）
void TranBufSelf(TH_INOUT INT8U *pDstBuf, TH_IN INT16U len)
{
	INT16U tranlen;
	INT8U tmp8;
	tranlen = len>>1;
	for(INT16U m=0; m<tranlen; m++)
	{
		tmp8 = pDstBuf[m];
		pDstBuf[m] = pDstBuf[len-1-m];
		pDstBuf[len-1-m] = tmp8;
	}
}
//数组指针的转换
void  TranBufToBuf(TH_IN const INT8U *pSrcBuf, TH_IN INT16U len, TH_OUT INT8U *pDstBuf)
{
	for(INT16U m=0; m<len; m++)
	{
		pDstBuf[len-1-m] = pSrcBuf[m];
	}
}

//总加和算法 ，返回CS
INT8U  CreadAddCs(TH_IN const INT8U *vSrcBuf, TH_IN INT16U vSrcLen)
{
	INT8U cs = 0;
	for(INT16U m=0; m<vSrcLen; m++)
	{
		cs += vSrcBuf[m];
	}
	return cs;
}
//比较CS是否正确，返回DACK_SUCESS，DACK_FAILURE
INT8U  CmpAddCs(TH_IN const INT8U *vSrcBuf, TH_IN INT16U vSrcLen, TH_IN INT8U vSrcCs)
{
   INT8U cs = CreadAddCs(vSrcBuf,vSrcLen);
   if(cs == vSrcCs)
      return DACK_SUCESS;
   else
      return DACK_FAILURE;
}

 /*
//BCD格式转换
INT8U BcdToHexFmt(INT8U data)
{
  INT8U temp;
  INT8U i;
  temp=data;
  i=temp&0xf0;
  i>>=4;
  i*=10;
  temp=temp&0x0f;
  i+=temp;
  return i;
}
INT8U HexToBcdFmt( INT8U data)
{
  INT8U temp;
  INT8U i;
  temp=data;
  i=temp/10;
  i<<=4;
  temp=temp%10;
  i|=temp;
  return i;
}


INT16U BcdToHexFmt(INT16U data)
{
   INT16U hex16=0;
   hex16+=((data>>12)&0x0f)*1000;
   hex16+=((data>>8)&0x0f)*100;
   hex16+=((data>>4)&0x0f)*10;
   hex16+=data&0x0f;
   return hex16;
}
INT16U HexToBcdFmt(INT16U data)
{
   INT16U temp32;
   INT8U temp;
   INT16U ack16=0;
   temp32=data;
   
   temp=temp32/1000;
   temp32%=1000;
   ack16=temp;
   ack16<<=4;
   temp=temp32/100;
   temp32%=100;
   ack16|=temp;
    ack16<<=4;
   temp=temp32/10;
   temp32%=10;
   ack16|=temp;
   ack16<<=4;
   ack16|=temp32;
   return ack16;
}
INT32U BcdToHexFmt(INT32U data)
{
  
 return  Bcd32ToHex32(data);
}
INT32U HexToBcdFmt(INT32U data)
{
 
  return Hex32ToBcd32(data);
}
*/

// --------------------------------------------------------------
//      CRC16计算方法1：使用2个256长度的校验表
// --------------------------------------------------------------
const INT8U CRCHTalbe[] =                                 // CRC高位字节表
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

const INT8U CRCLTalbe[] =                                 // CRC 低位字节表
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


INT16U CalculateCRC(TH_IN INT8U* InputData, TH_IN INT16U DataLen)
{
	INT8U CRCHi = 0xFF; //高CRC字节初始化
	INT8U CRCLo = 0xFF; // 低CRC字节初始化
	INT8U Index;            // CRC循环中的索引

	while (DataLen--)
	{
					//计算CRC
					Index = CRCLo ^ (*InputData);
					InputData++;
					CRCLo = CRCHi ^ CRCHTalbe[Index]; 
					CRCHi = CRCLTalbe[Index];
	} 
	return (((INT16U)CRCHi << 8) | CRCLo);
}

void CalculateCRCToBuf2(TH_IN INT8U* InputData, TH_IN INT16U DataLen, TH_OUT INT8U *vDstBuf)
{
	INT16U tmp16;
	tmp16 = CalculateCRC(InputData,DataLen);
	Hex16ToBuf2(tmp16,vDstBuf);
}



INT16U FileCalculateCRC(TH_OUT INT8U &CRCHi, TH_OUT INT8U &CRCLo, TH_IN INT8U* InputData, TH_IN INT16U DataLen)
{       
	INT8U Index;            // CRC?-?·?Dμ??÷òy
	while(DataLen--)
	{
		//????CRC
		Index = CRCLo ^ (*InputData);
		InputData++;
		CRCLo = CRCHi ^ CRCHTalbe[Index]; 
		CRCHi = CRCLTalbe[Index];
	} 
	return(((INT16U)CRCHi << 8) | CRCLo);
}


//~~~~~~~~~~~~标志类操作~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 CEpMgBpFg::CEpMgBpFg(INT8U *pSrcBuf,INT16U vSrclen)
 {
   pFgBuf = pSrcBuf;
	 FgLen = vSrclen;
 }
//vSrcFgBit 0开始  vSrcAck: 0 和 1
void CEpMgBpFg::SetEpFg(INT16U vSrcFgBit,INT8U vSrcAck)
{
 INT32U tmp32;
 INT8U tmpbit;
	 tmp32=vSrcFgBit/8;
     tmpbit=vSrcFgBit%8;
	 if(FgLen>tmp32)
   {
    if(vSrcAck==1)
      pFgBuf[tmp32]|=0x01<<tmpbit;
    else
      pFgBuf[tmp32]&=~(0x01<<tmpbit);
 
  }
}
//vSrcFgBit 0开始
INT8U CEpMgBpFg::QueEpFg(INT16U vSrcFgBit)
{
  INT32U tmp32;
  INT8U tmpbit;
  tmp32=vSrcFgBit/8;
  tmpbit=vSrcFgBit%8;
 if(FgLen>tmp32)
 {
      if(pFgBuf[tmp32]&(0x01<<tmpbit))
			{
				return DACK_SUCESS;
			}
      else
      {
				return DACK_FAILURE;
			}
  }
  return DACK_SUCESS;
   
}
//
INT8U CEpMgBpFg::QueEpAllFgIsOk(INT16U vSrcFgBit)
{
  INT32U tmp32;
  INT8U tmpb;
  INT8U tmpbit;
  tmp32=vSrcFgBit/8;
  tmpbit=vSrcFgBit%8;
 if(FgLen>tmp32)
 {
   for(INT32U m=0;m<tmp32;m++)
    {
	    if(pFgBuf[m]!=0xFF)
	     return DACK_FAILURE;
    }
	 tmpb=0;
	 for(INT8U m=0;m<tmpbit;m++)
	 {
		 tmpb|=0x01<<m;
	 }
	 
     if((pFgBuf[tmp32]&tmpb)==tmpb)
		 {
			 return DACK_SUCESS;
		 }
      else
      {
				return DACK_FAILURE;
			}
  }
  return DACK_SUCESS;

}

