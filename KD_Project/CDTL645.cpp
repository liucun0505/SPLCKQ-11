/****************************************Copyright (c)**************************************************
**                                      终端产品
**             
**--------------文件信息--------------------------------------------------------------------------------
**文   件   名: CDTL645.cpp
**创   建   人: 杨虎岳
**最后修改日期: 2006年6月7日
**描        述:645协议解码类
**              
**--------------历史版本信息----------------------------------------------------------------------------
** 创建人: 杨虎岳
** 版  本: v1.0
** 日　期: 2006年6月7日
** 描　述: 原始版本
**
**--------------当前版本修订------------------------------------------------------------------------------
**创 建  人: 杨虎岳
**日     期: 2006年6月7日
** 描　述: 
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#include "stdafx.h"
#include "CDTL645.h"
#include "CDTL2007.h"
#define    Max645ReadLen   200//编码读命令
 //INT32U s_Di;//DI
 //INT8U  s_AmtBuf[6];//表地址
 //INT8U  s_type;//操作模式，0：无FE， 1：有4个FE
 INT8U CDTL645:: CodeReadData97Cmd(TH_IN const INT16U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData)
{
	CodeReadData97(pSrcDi,pSrcAmtAddBuf,vDstCmdData.s_pDstCmdBuf,vDstCmdData.s_vDstCmdLen,type);
	return DACK_SUCESS;
}
 void CDTL645:: CodeToAck97Data(struct Stu_Dtl2007 &Dtl2007Buf,const INT8U *vSrcBuf,const INT16U vSrcLen)
{
	CodeReadAckData97((INT16U)Dtl2007Buf.s_Di,Dtl2007Buf.s_AmtBuf,vSrcBuf,vSrcLen,Dtl2007Buf.s_pDstBuf,Dtl2007Buf.s_Len,0);
 }
void CDTL645:: CodeWriteData97(const INT16U pSrcDi,const INT8U *pSrcAmtAddBuf,const INT8U *pSrcBuf,const INT8U pSrcLen,INT8U *pDstBuf,INT8U &pDstLen,INT8U type)
{
 INT8U cs=0;
 INT8U i=0;
 INT8U j;
 INT8U temp;

 INT8U Di0,Di1;
 INT8U *tempbuf=pDstBuf;
 Di0=(INT8U)pSrcDi;
 Di1=(INT8U)(pSrcDi>>8);
 if(type==0)
{
 tempbuf[i++]=0xfe;
}
 cs+=0x68;
 tempbuf[i++]=0x68;
 for(j=0;j<6;j++)
 {
   cs+=pSrcAmtAddBuf[j];
   tempbuf[i++]=pSrcAmtAddBuf[j];
  }

  cs+=0x68;
 tempbuf[i++]=0x68;
  cs+=0x04;
 tempbuf[i++]=0x04;//控制码
  cs+=0x02+0x04+pSrcLen;
 tempbuf[i++]=0x02+pSrcLen+0x04;//长度
 temp=Di0+0x33;
  cs+=temp;
 tempbuf[i++]=temp;
 temp=Di1+0x33;
  cs+=temp;
 tempbuf[i++]=temp;
  cs+=0x00+0x33;
 tempbuf[i++]=0x00+0x33;
   cs+=0x66+0x33;
 tempbuf[i++]=0x66+0x33;
   cs+=0x66+0x33;
 tempbuf[i++]=0x66+0x33;
   cs+=0x66+0x33;
 tempbuf[i++]=0x66+0x33;
 for(j=0;j<pSrcLen;j++)
  { 
    temp=pSrcBuf[j]+0x33;
    cs+=temp;
   tempbuf[i++]=temp;
  }
 tempbuf[i++]=cs;
 tempbuf[i++]=0x16;
 pDstLen=i;
}


	void CDTL645:: CodeReadData97(const INT16U pSrcDi,const INT8U *pSrcAmtAddBuf,INT8U *pDstBuf,INT8U &pDstLen,INT8U type)

{
 INT8U cs=0;
 INT8U i=0;
 INT8U *tempbuf;
 INT8U j;
 INT8U temp;
 INT8U Di0,Di1;
  tempbuf=pDstBuf;
 Di0=(INT8U)pSrcDi;
 Di1=(INT8U)(pSrcDi>>8);
 if(type==0)
{
 tempbuf[i++]=0xfe;
}
 cs+=0x68;
 tempbuf[i++]=0x68;
 for(j=0;j<6;j++)
 {
   cs+=pSrcAmtAddBuf[j];
   tempbuf[i++]=pSrcAmtAddBuf[j];
  }

  cs+=0x68;
 tempbuf[i++]=0x68;
  cs+=0x01;
 tempbuf[i++]=0x01;//控制码
  cs+=0x02;
 tempbuf[i++]=0x02;//长度
 temp=Di0+0x33;
  cs+=temp;
 tempbuf[i++]=temp;
 temp=Di1+0x33;
  cs+=temp;
 tempbuf[i++]=temp;
 tempbuf[i++]=cs;
 tempbuf[i++]=0x16;
 pDstLen=i;

}

INT8U CDTL645::Decode64597(const INT8U *pSrcBuf,const INT16U pSrcLen,const INT8U vSrcDataLen,INT8U *pDstAmtAddBuf,INT16U &pDstDi,INT8U *pDstBuf,INT8U &pDstLen)
{
 
 INT8U cs=0;
 INT8U temp;

 INT32U i=0;
 INT32U j=0;
 INT8U con;
 INT8U ack=ACKNULL;
 INT8U len8;
 pDstDi=0x0000;

 pDstLen=0;
  if(pSrcLen<=Max645ReadLen)
  {
   if(pSrcLen>10)  //防止不是645的其他帧引起读末知空间,引发末知错误
   {
      ack=ACKFAMEERR;
     i=0;//这以胶没有加。i=0;是比较危险的
   while(pSrcBuf[i++]!=0x68) 
   {
    if(i>pSrcLen) break;
   }
   if(i<pSrcLen)
   {
     cs+=0x68;
     if((i+10)<=pSrcLen) 
     {
      for(j=0;j<6;j++)
      {
       cs+=pSrcBuf[i];
       pDstAmtAddBuf[j]=pSrcBuf[i];
       i++;
      }
	  cs+=pSrcBuf[i];
	  if(pSrcBuf[i++]==0x68)
	  { 
	  con=pSrcBuf[i];//CON处理，用于区别是否有后续帧.81无后续帧,A1有后续帧,C1错误码
	  switch(con)
	  {
	   
	    case 0x81:
	    case 0xa1:
	    case 0x82:
	    case 0xa2:
	    
	        cs+=pSrcBuf[i++];
	        cs+=pSrcBuf[i];
	        if(pSrcBuf[i]>2)
	        {
	        pDstLen=pSrcBuf[i++]-2;//数据长度的处理
	        if(((pDstLen+14)<=pSrcLen)&&(pDstLen<=Max645DataLen)&&(pDstLen>0))//14是除有用数据以后的长度
	        {      
	         cs+=pSrcBuf[i];//DI0
	         temp=pSrcBuf[i++]-0x33;
	        cs+=pSrcBuf[i];//DI1
	        pDstDi=pSrcBuf[i++]-0x33;
	        pDstDi<<=8;
	        pDstDi|=temp;
	         for(j=0;j<pDstLen;j++)
	        {
	          cs+=pSrcBuf[i+j];
	   
	         }
	   
	         if((cs==pSrcBuf[i+j])&&(pSrcBuf[i+j+1]==0x16))
	         {
	             if((((pDstDi)&0x000f)==0x000f)&&((pDstDi)!=EBRCE))//块命令末尾有一个0XAA结束码。所以减一
		         {
		           if(pDstLen>1)
		           {
		           if(pSrcBuf[i+pDstLen-1]==0xdd)//是AA时才减，为了兼容块不代AA结尾的
		            pDstLen=(pDstLen)-1;
		           }
		       
		         } 
	         
	             if(pDstLen>vSrcDataLen)//数据缓冲区长度不够，返回前半部分数据，
	             {
	                pDstLen=vSrcDataLen;
	             }
		         for(j=0;j<pDstLen;j++)
		        {
		          pDstBuf[j]=pSrcBuf[i+j]-0x33;	
		         }
	    
	         
	        
	           ack=ACKTRUE;
	        
	         }
	        }
	        }
	        break;
	   default:  //只要帧格式对就算有效帧
	      //case 0xc1://是读正常帧处理
	    //case 0xc2://后续帧的异常帧处理
	    //case 0xc4://写数据的异常处理,此时没有进行以后的数据纠验,可以有一定的隐藏错误发生
	               cs+=pSrcBuf[i++];//控制吗
	               cs+=pSrcBuf[i];//长度
	               len8=pSrcBuf[i];
	               i++;
	               if((i+len8+2)<=pSrcLen)
	               {
                    for(INT8U m=0;m<len8;m++)
                    {
                      cs+=pSrcBuf[i++];
                    }
	                if((cs==pSrcBuf[i])&&(pSrcBuf[i+1]==0x16))
	                {
	                 ack = ACKERR;
	                }
	               }
	                  
	               break;
	      }
	      }
	      }
	     }
	    }
	    else
	     ack=ACKNULL;
	   }
	  if(ack!= ACKTRUE)
	  {
	    pDstLen=0;
	    pDstDi=0x00;
	  } 
   /*   先不判断BCD码
	 if(ack==ACKTRUE)
	 { 
	  	   temp=Di>>12;
	       switch(temp)
	     {
	      case 0x09:
	      case 0x0A:
	      case 0x0B:
	          if(Check_Bcd(pDstBuf,pDstLen)==FALSE)
	            ack645=ACKERR;
	           break;
	      default:
	          break;
	        
	     }
	}
	*/
	  return ack;
 }
// INT8U CDTL645::AdjustTimeCode(const INT8U *buf,INT8U pSrcMaxLen,INT8U *tempbuf,INT8U &pDstLen,INT8U type)
//{
// INT8U cs=0;
// INT8U i=0;
// INT8U j;
// INT8U temp;
// INT8U ack=FALSE;
// pDstLen=0;
// if(pSrcMaxLen>50) 
//{
//if(type==0)
//{
// tempbuf[i++]=0xfe;
//}
// cs+=0x68;
// tempbuf[i++]=0x68;
// for(j=0;j<6;j++)
// {
//   cs+=0x99;
//   tempbuf[i++]=0x99;
//  }
//
//  cs+=0x68;
// tempbuf[i++]=0x68;
//  cs+=0x08;
// tempbuf[i++]=0x08;//控制码
//  cs+=0x06;
// tempbuf[i++]=0x06;//长度
// 
// for(j=0;j<6;j++)
//  { 
//  if(j==4)
//    temp=(buf[4]&0x1f)+0x33;
//  else
//    temp=buf[j]+0x33;
//    cs+=temp;
//   tempbuf[i++]=temp;
//  }
// tempbuf[i++]=cs;
// tempbuf[i++]=0x16;
// pDstLen=i;
// ack=TRUE;
//}
// return ack;
//}
 INT8U CDTL645:: CheckAmtAdd97(const INT8U *pSrcAdd,const INT8U *pSrcRcvAdd)
{
 INT8U ack=TRUE;
 INT8U temp8;
 INT8U temp28;
 for(INT8U m=0;m<6;m++)
 {
   temp8=pSrcAdd[m]&0x0F;
   temp28=pSrcRcvAdd[m]&0x0F;
  if((temp8!=0x0A)&&(temp8!=temp28)&&(temp28!=0x0A))
   {
     ack=FALSE;
     break;
   }
   temp8=pSrcAdd[m]&0xF0;
    temp28=pSrcRcvAdd[m]&0xF0;
  if((temp8!=0xA0)&&(temp8!=temp28)&&(temp28!=0xA0))
   {
     ack=FALSE;
     break;
   }
 }
 return ack;
}
INT8U CDTL645::CheckFullFrame64597(const INT8U *pSrcBuf,const INT16U pSrcLen)//检测帧的长度完整
{
  INT8U ack=FALSE;
  INT16U i=0;
  if(pSrcLen>10)  //防止不是645的其他帧引起读末知空间,引发末知错误
   {
    
     i=0;//这以胶没有加。i=0;是比较危险的
   while(pSrcBuf[i]!=0x68) 
   {
     i++;
    if(i>=pSrcLen) break;
   }
   if(i<pSrcLen)
   {
     if((i+12)<=pSrcLen) 
     {
       i+=9;//指向长度
      if((i+pSrcBuf[i]+2+1)<=pSrcLen)
        ack=TRUE;
	 }
   }
  }
 return ack;
}

//增加没有Fe方式
INT8U CDTL645:: CodeReadDataNoFe97(const INT16U pSrcDi,const INT8U *pSrcAmtAddBuf,INT16U vSrcLen,INT8U *pDstBuf,INT8U &pDstLen)

{
 INT8U cs=0;
 INT8U i=0;
 INT8U *tempbuf;
 INT8U j;
 INT8U temp;
 INT8U Di0,Di1;
 INT8U ack=FALSE;
 if(vSrcLen>14)
 {
  tempbuf=pDstBuf;
 Di0=(INT8U)pSrcDi;
 Di1=(INT8U)(pSrcDi>>8);
 cs+=0x68;
 tempbuf[i++]=0x68;
 for(j=0;j<6;j++)
 {
   cs+=pSrcAmtAddBuf[j];
   tempbuf[i++]=pSrcAmtAddBuf[j];
  }

  cs+=0x68;
 tempbuf[i++]=0x68;
  cs+=0x01;
 tempbuf[i++]=0x01;//控制码
  cs+=0x02;
 tempbuf[i++]=0x02;//长度
 temp=Di0+0x33;
  cs+=temp;
 tempbuf[i++]=temp;
 temp=Di1+0x33;
  cs+=temp;
 tempbuf[i++]=temp;
 tempbuf[i++]=cs;
 tempbuf[i++]=0x16;
 ack=TRUE;
 }
 pDstLen=i;
 return ack;
}


//解码广播校时，用于数据+延时的的处理
// INT8U CDTL645::Decode645AdjustTime(const INT8U *pSrcBuf,const INT16U pSrcLen,const INT16U vSrcDataLen,INT8U *pDstBuf,INT8U &pDstLen)
//{
// 
// INT8U cs=0;
// //INT8U temp;
//
// INT32U i=0;
// INT32U j=0;
// INT8U con;
// INT8U ack=ACKNULL;
// //INT8U len8;
// pDstLen=0;
//  if((pSrcLen<=Max645ReadLen)&&(pSrcLen>10))
//  {
//      ack=ACKFAMEERR;
//     i=0;//这以胶没有加。i=0;是比较危险的
//   while(pSrcBuf[i++]!=0x68) 
//   {
//    if(i>pSrcLen) break;
//   }
//   if(i<pSrcLen)
//   {
//     cs+=0x68;
//     if((i+10)<=pSrcLen) 
//     {
//      for(j=0;j<6;j++)
//      {
//       cs+=pSrcBuf[i];
//       //pDstAmtAddBuf[j]=pSrcBuf[i];
//       i++;
//      }
//	  cs+=pSrcBuf[i];
//	  if(pSrcBuf[i++]==0x68)
//	  { 
//	   con=pSrcBuf[i];//CON处理，用于区别是否有后续帧.81无后续帧,A1有后续帧,C1错误码
//	   if(con==0x08)
//	   {
//		    cs+=pSrcBuf[i++];//控制吗
//	        cs+=pSrcBuf[i];//长度
//	        pDstLen=pSrcBuf[i];
//			i++;
//			if(pDstLen<=vSrcDataLen)
//			{
//			 for(j=0;j<pDstLen;j++)
//		        {
//		          pDstBuf[j]=pSrcBuf[i+j]-0x33;	
//		        }
//				 ack=ACKTRUE;
//			}
//			else
//			   pDstLen=0;
//	   }
//	 
//	   }
//	    }
//	   }
//	    
//	    }
//	    else
//	     ack=ACKNULL;
//	  
//	  if(ack!= ACKTRUE)
//	  {
//	    pDstLen=0;
//	 } 
// 
//	  return ack;
// }
INT8U CDTL645::CheckOk97(const INT8U *pSrcBuf,const INT8U pSrcLen)
{
 INT8U cs=0;
 //INT8U temp;
 INT32U i=0;
 INT32U j=0;
 INT8U con;
 INT8U ack=ACKERR;
  if(pSrcLen<=Max645ReadLen)
  {
   if(pSrcLen>10)  //防止不是645的其他帧引起读末知空间,引发末知错误
   {
    
     i=0;//这以胶没有加。i=0;是比较危险的
   while(pSrcBuf[i++]!=0x68) 
   {
    if(i>pSrcLen) break;
   }
   if(i<pSrcLen)
   {
     cs+=0x68;
     if((i+10)<=pSrcLen) 
     {
      for(j=0;j<6;j++)
      {
       cs+=pSrcBuf[i];
       //pDstAmtAddBuf[j]=pSrcBuf[i];
       i++;
      }
	  cs+=pSrcBuf[i];
	  if(pSrcBuf[i++]==0x68)
	  { 
	  con=pSrcBuf[i];//CON处理，用于区别是否有后续帧.81无后续帧,A1有后续帧,C1错误码
	  switch(con)
	  {
	    case 0x84://写数据的正常应答
	    case 0x9d://写数据的正常应答
	    
	        cs+=pSrcBuf[i++];
	        cs+=pSrcBuf[i];
	        if(pSrcBuf[i]==0)
	        {
	          i++;
	          if((cs==pSrcBuf[i])&&(pSrcBuf[i+1]==0x16))
	           ack=ACKTRUE;
	          i++;
	          
	         }
	       
	        break;
	      
	      default:  ack = ACKERR;break;
	      }
	      }
	      }
	     }
	    }
	    else
	     ack=ACKNULL;
	   }
	 
	  return ack;
  
  }

void CDTL645:: CodeReadAckData97(const INT16U pSrcDi,const INT8U *pSrcAmtAddBuf,const INT8U *pSrcBuf,const INT16U pSrcLen,INT8U *pDstBuf,INT8U &pDstLen,INT8U type)
{
	INT8U cs=0;
	INT8U i=0;
	INT8U j;
	INT8U temp;

	INT8U Di0,Di1;
	INT8U *tempbuf=pDstBuf;
 Di0=(INT8U)pSrcDi;
 Di1=(INT8U)(pSrcDi>>8);
	if(type==0)
	{
		tempbuf[i++]=0xfe;
	}
	cs+=0x68;
	tempbuf[i++]=0x68;
	for(j=0;j<6;j++)
	{
		cs+=pSrcAmtAddBuf[j];
		tempbuf[i++]=pSrcAmtAddBuf[j];
	}

	cs+=0x68;
	tempbuf[i++]=0x68;
	cs+=0x04;
	tempbuf[i++]=0x04;//控制码
	cs+=0x02+0x04+pSrcLen;
	tempbuf[i++]=0x02+pSrcLen+0x04;//长度
	temp=Di0+0x33;
	cs+=temp;
	tempbuf[i++]=temp;
	temp=Di1+0x33;
	cs+=temp;
	tempbuf[i++]=temp;
	for(j=0;j<pSrcLen;j++)
	{ 
		temp=pSrcBuf[j]+0x33;
		cs+=temp;
		tempbuf[i++]=temp;
	}
	tempbuf[i++]=cs;
	tempbuf[i++]=0x16;
	pDstLen=i;
}