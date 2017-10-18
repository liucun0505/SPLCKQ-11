// CDTL2007.cpp : implementation file
//

#include "stdafx.h"
#include "CDTL2007.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
/*
* 文件名称：cDTL2007.cpp

* 摘    要： 97-07-645 编码转换
*
* 当前版本：1.1
* 作    者：赵震
* 完成日期：2006年6月29日
*
* 取代版本：
* 原 作 者：
* 完成日期：
*------------------------------------------------------------------------------*/

#include "CDTL2007.h"
const INT8U  READCMD_645_07_MAXLEN = 30;

void cDTL2007:: CodeToAckData(struct Stu_Dtl2007 &Dtl2007Buf,const INT8U *vSrcBuf,const INT16U vSrcLen)
{
	INT8U m=0;
	INT8U cs=0;
	INT8U i=0;
	INT8U *tempbuf;
	INT8U j;
	INT8U temp;
	INT8U di0,di1,di2,di3;
	
	if(vSrcLen+28<=FRAME645_MAX_LEN)
	{
		tempbuf=Dtl2007Buf.s_pDstBuf;
		di0=Dtl2007Buf.s_Di;
		di1=Dtl2007Buf.s_Di>>8;
		di2=Dtl2007Buf.s_Di>>16;
		di3=Dtl2007Buf.s_Di>>24;
		//tempbuf[i++]=0xfe;
		//tempbuf[i++]=0xfe;
		//tempbuf[i++]=0xfe;
		//tempbuf[i++]=0xfe;
		cs+=0x68;
		tempbuf[i++]=0x68;
		for(j=0;j<6;j++)
		{
			cs+=Dtl2007Buf.s_AmtBuf[j];
			tempbuf[i++]=Dtl2007Buf.s_AmtBuf[j];
		}

		cs+=0x68;
		tempbuf[i++]=0x68;
		cs+=Dtl2007Buf.s_Con;
		tempbuf[i++]=Dtl2007Buf.s_Con;//控制码

		switch (Dtl2007Buf.s_Con)
		{
		case 0x91:
			temp = vSrcLen+4;
			cs+=temp;
			tempbuf[i++]=temp;//长度

			temp=di0+0x33;
			cs+=temp;
			tempbuf[i++]=temp;
			temp=di1+0x33;
			cs+=temp;
			tempbuf[i++]=temp;
			temp=di2+0x33;
			cs+=temp;
			tempbuf[i++]=temp;
			temp=di3+0x33;
			tempbuf[i++]=temp;
			cs+=temp;


			for(m=0;m<vSrcLen;m++)
			{
				temp=vSrcBuf[m]+0x33;
				tempbuf[i++]=temp;
				cs+=temp;
			}
			
			break;
		case 0x93:
			temp = 0x06;
			cs += temp;
			tempbuf[i++] = temp;//长度
			
			for(m=0; m<vSrcLen; m++)
			{
				temp = vSrcBuf[m]+0x33;
				tempbuf[i++] = temp;
				cs += temp;
			}
			

			break;
		case 0x88:
		case 0x94:
			temp=0;
			cs+=temp;
			tempbuf[i++]=temp;//长度
			break;

		case 0xC8:
		case 0xD1:
		case 0xD4:
			temp=1;
			cs+=temp;
			tempbuf[i++]=temp;//长度

			temp=0x34;
			tempbuf[i++]=temp;
			cs+=temp;
			break;

		default:
			break;
		}

		tempbuf[i++]=cs;
		tempbuf[i++]=0x16;
		Dtl2007Buf.s_Len=i;
	}
	Dtl2007Buf.s_Len=i;
}
//编码读命令
 //INT32U s_Di;//DI
 //INT8U  s_AmtBuf[6];//表地址
 //INT8U  s_type;//操作模式，0：无FE， 1：有4个FE
 INT8U cDTL2007:: CodeReadDataCmd(TH_IN const INT32U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData)
  {
		INT8U ack = DACK_ERR_NULL;
	 INT8U cs=0;
	 INT8U i=0;
	 INT8U *tempbuf = vDstCmdData.s_pDstCmdBuf;
	 
		vDstCmdData.s_vDstCmdLen = 0;

	 INT8U j;
	 INT8U temp;
	 INT8U di0,di1,di2,di3;
	 di0=pSrcDi;
	 di1=pSrcDi>>8;
	 di2=pSrcDi>>16;
	 di3=pSrcDi>>24;
		
   if(type==0)
	{
		 tempbuf[i++]=0xfe;
		 tempbuf[i++]=0xfe;
		 tempbuf[i++]=0xfe;
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
	  cs+=0x11;
	 tempbuf[i++]=0x11;//
	 tempbuf[i++]=0x04;//
	 cs+=0x04;
	 
	 temp=di0+0x33;
	  cs+=temp;
	 tempbuf[i++]=temp;
	 temp=di1+0x33;
	  cs+=temp;
	 tempbuf[i++]=temp;
	 //
	 temp=di2+0x33;
	  cs+=temp;
	 tempbuf[i++]=temp;
	 temp=di3+0x33;
	 tempbuf[i++]=temp;
	  cs+=temp;
	 tempbuf[i++]=cs;
	 tempbuf[i++]=0x16;
	 vDstCmdData.s_vDstCmdLen = i;
	 ack = DACK_SUCESS;

	 return ack;
}
//解码所有的2007协议 ，直接将结果输出到645-07结构体中
INT8U cDTL2007::Decode2007(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT Stu_Dtl2007 &DstDecode2007DataFrame)
{
 
	 INT8U cs = 0;
	 INT16U i = 0;
	 INT8U ack = DACK_ERR_NULL;
   INT8U len8 = 0;
   DstDecode2007DataFrame.s_Di = 0xffffffff;//代表数据项中没有s_Di;
	
    if((pSrcLen<=FRAME645_MAX_LEN)&&(pSrcLen>11))//防止不是645的其他帧引起读末知空间,引发末知错误
    {
			ack = DACK_2_ERR_FAME;//只要有数据就算有返回，不能算空值
      i = 0;//这以胶没有加。i=0;是比较危险的
			
			while(pSrcBuf[i] != 0x68) //查找第一个0x68
			{
				i++;
				if(i >= pSrcLen) 
				break;
			}
			
			if((i+12) <= pSrcLen)
			{
	      //i 为第一个68
	      len8 = pSrcBuf[i + 9];//长度
	      if(len8<=DATA645_MAX_LEN)
	      {
					if((i + len8 + 12) <= pSrcLen)//检测总长度
					{
						if((pSrcBuf[i+7] == 0x68) && (pSrcBuf[i + 10 + len8 + 1] == 0x16))//检测第二个68和结束码为0x16
						{
							cs = 0;
							for(INT8U m = 0;m < (10 + len8);m++)
							cs += pSrcBuf[i+m];
	  
							if(cs == pSrcBuf[i + 10 + len8])//校验和
							{
								DstDecode2007DataFrame.s_Len = len8;//提取长度zz
								for(INT8U m = 0;m < 6;m++)
								DstDecode2007DataFrame.s_AmtBuf[m] = pSrcBuf[i + 1 + m];//提取表号	    
								DstDecode2007DataFrame.s_Con = pSrcBuf[i + 8];//提取控制码
                               //DstDecode2007DataFrame.s_Con  &= 0x1f;
								switch(DstDecode2007DataFrame.s_Con)
								{
									 case 0x01:
									 case 0x02:
									// case 0x03:07命令用于安全认证部分
									 case 0x04:				 
									 case 0x0a:
									 case 0x0c:
									 case 0x0f:
									 case 0x10:
											DstDecode2007DataFrame.s_type = 0x01;
											break;
									 
									 case 0x08:	//是广播校时命令
											DstDecode2007DataFrame.s_type = 0x00;
											break;
									 case 0x13:
										 DstDecode2007DataFrame.s_Di = 0x04000401;
										 DstDecode2007DataFrame.s_type = 0x02;
										 break;
									 case 0x11:
										 if(len8 >= 4)
										{
											 DstDecode2007DataFrame.s_Di = (INT8U)(pSrcBuf[i+13] - 0x33);//提取di0-di3
											 DstDecode2007DataFrame.s_Di <<= 8;
											 DstDecode2007DataFrame.s_Di |= (INT8U)(pSrcBuf[i+12] - 0x33);
											 if(0x00 == DstDecode2007DataFrame.s_type )//97_645
											{
													 DstDecode2007DataFrame.s_Di =0x0;
													 DstDecode2007DataFrame.s_Di =0x0;
													 len8 -= 2;
													 i += 2;
											 } 
											else
											 {
													 DstDecode2007DataFrame.s_Di <<= 8;
													 DstDecode2007DataFrame.s_Di |= (INT8U)(pSrcBuf[i+11] - 0x33);
													 DstDecode2007DataFrame.s_Di <<= 8;
													 DstDecode2007DataFrame.s_Di |= (INT8U)(pSrcBuf[i+10] - 0x33);
													 len8 -= 4;
													 i += 4;
											 }
										}
										 break;
									 
									 default:
											DstDecode2007DataFrame.s_type = 0x02;
											break;		    
								}	
			   
								//对读数据的特殊处理
								if((DstDecode2007DataFrame.s_Con == 0x91) 
									|| (DstDecode2007DataFrame.s_Con == 0xB1)
								  || (DstDecode2007DataFrame.s_Con == 0x92)
								  || (DstDecode2007DataFrame.s_Con == 0xB2)
								  || (DstDecode2007DataFrame.s_Con == 0x6A)
								  || (DstDecode2007DataFrame.s_Con == 0x83))//是读数据或读后续帧
								{
									if(len8 >= 4)
										{
											 DstDecode2007DataFrame.s_Di = (INT8U)(pSrcBuf[i+13] - 0x33);//提取di0-di3
											 DstDecode2007DataFrame.s_Di <<= 8;
											 DstDecode2007DataFrame.s_Di |= (INT8U)(pSrcBuf[i+12] - 0x33);
											 if(0x00 == DstDecode2007DataFrame.s_type )//97_645
											{
													 DstDecode2007DataFrame.s_Di =0x0;
													 DstDecode2007DataFrame.s_Di =0x0;
													 len8 -= 2;
													 i += 2;
											 } 
											else
											 {
													 DstDecode2007DataFrame.s_Di <<= 8;
													 DstDecode2007DataFrame.s_Di |= (INT8U)(pSrcBuf[i+11] - 0x33);
													 DstDecode2007DataFrame.s_Di <<= 8;
													 DstDecode2007DataFrame.s_Di |= (INT8U)(pSrcBuf[i+10] - 0x33);
													 len8 -= 4;
													 i += 4;
											 }
										}
								}						 
								for(INT8U m = 0;m < len8;m++)//提取数据         
								DstDecode2007DataFrame.s_pDstBuf[m] = pSrcBuf[i + 10 + m] - 0x33;				
								ack = DACK_SUCESS;
							}
						}
						
					}
				}
	    }
	  }
		
	  if(ack != DACK_SUCESS)
	  {
	   DstDecode2007DataFrame.s_Con = 0;
	   DstDecode2007DataFrame.s_Len = 0;
	  }
	  return ack;
 }

//编码密码明文写数据
void cDTL2007::CodeToWatchData(TH_IN const struct Stu_Dtl2007 Dtl2007Buf,TH_IN INT8U type,TH_OUT INT8U *pDstBuf,TH_OUT INT16U &pDstLen)
  {
	 INT8U cs = 0;
	 INT16U i = 0;
	 INT8U *tempbuf;
	 INT8U j;
	 INT8U temp;
	 INT8U di0,di1,di2,di3;
	 pDstLen = 0;
		
	 tempbuf = pDstBuf;
	 di0=Dtl2007Buf.s_Di;
	 di1=Dtl2007Buf.s_Di >> 8;
	 di2=Dtl2007Buf.s_Di >> 16;
	 di3=Dtl2007Buf.s_Di >> 24;
		
   if( type == 0)
	 {
			tempbuf[i++] = 0xfe;
	 }
	 
	 cs += 0x68;
	 tempbuf[i++] = 0x68;
	 for(j = 0;j < 6;j++)
	 {
	   cs += Dtl2007Buf.s_AmtBuf[j];
	   tempbuf[i++] = Dtl2007Buf.s_AmtBuf[j];
	 }

	 cs += 0x68;
	 tempbuf[i++] = 0x68;
	 cs += Dtl2007Buf.s_Con;
	 tempbuf[i++] = Dtl2007Buf.s_Con;//控制码
	 temp = Dtl2007Buf.s_Len;
	 cs += temp;
	 tempbuf[i++] = temp;//长度
	 
	 temp = di0 + 0x33;
	 cs += temp;
	 tempbuf[i++] = temp;
	 temp = di1 + 0x33;
	 cs += temp;
	 tempbuf[i++] = temp;	 
	 temp = di2 + 0x33;
	 cs += temp;
	 tempbuf[i++] = temp;
	 temp = di3 + 0x33;
	 tempbuf[i++] = temp;
	 cs += temp;
	 
	 for(INT8U m = 0;m < 8;m++)
	 {
	  temp = Dtl2007Buf.s_PwdBuf[m] + 0x33;
	  tempbuf[i++] = temp;
	  cs += temp;
	 }
	 
	  for(INT8U m = 0;m < (Dtl2007Buf.s_Len - 12);m++)
	 {
	  temp = Dtl2007Buf.s_pDstBuf[m] + 0x33;
	  tempbuf[i++] = temp;
	  cs += temp;
	 }
	 
	 tempbuf[i++] = cs;
	 tempbuf[i++] = 0x16;
	 pDstLen = i;
}
	
//编码 通过ESAM 密文写数据
void cDTL2007::CodeToWatchPData(TH_IN const struct Stu_Dtl2007 Dtl2007Buf,TH_OUT INT8U *pDstBuf,TH_OUT INT16U &pDstLen)
  {
	 INT8U cs = 0;
	 INT16U i = 0;
	 INT8U *tempbuf;
	 INT8U j;
	 INT8U temp;
	 INT8U di0,di1,di2,di3;
	 pDstLen = 0;
		
	 tempbuf = pDstBuf;
	 di0 = Dtl2007Buf.s_Di;
	 di1 = Dtl2007Buf.s_Di >> 8;
	 di2 = Dtl2007Buf.s_Di >> 16;
	 di3 = Dtl2007Buf.s_Di >> 24;
		
	 tempbuf[i++] = 0xfe;
	 cs += 0x68;
	 tempbuf[i++] = 0x68;
	 for(j = 0;j < 6;j++)
	 {
	   cs += Dtl2007Buf.s_AmtBuf[j];
	   tempbuf[i++] = Dtl2007Buf.s_AmtBuf[j];
	  }

	 cs += 0x68;
	 tempbuf[i++] = 0x68;
	 cs += Dtl2007Buf.s_Con;
	 tempbuf[i++] = Dtl2007Buf.s_Con;//控制码
	 temp = Dtl2007Buf.s_Len;
	 cs += temp;
	 tempbuf[i++] = temp;//长度
	 
	 temp = di0+0x33;
	 cs += temp;
	 tempbuf[i++] = temp;
	 temp = di1+0x33;
	 cs += temp;
	 tempbuf[i++] = temp;	 
	 temp = di2 + 0x33;
	 cs += temp;
	 tempbuf[i++] = temp;
	 temp = di3 + 0x33;
	 tempbuf[i++] = temp;
	 cs += temp;
	 
	 for(INT8U m = 0;m < 4;m++)//比明文少4个密码//zz
	 {
	  temp = Dtl2007Buf.s_PwdBuf[m] + 0x33;
	  tempbuf[i++] = temp;
	  cs += temp;
	 }
	 
	  for(INT8U m = 0;m < (Dtl2007Buf.s_Len - 8);m++)
	 {
	  temp = Dtl2007Buf.s_pDstBuf[m] + 0x33;
	  tempbuf[i++] = temp;
	  cs += temp;
	 }
	 tempbuf[i++] = cs;
	 tempbuf[i++] = 0x16;
	 pDstLen = i;

}
	
//编码读表地址
void  cDTL2007::CodeReadAmtAdd(TH_IN INT8U type,TH_OUT INT8U *pDstBuf,TH_OUT INT16U &vDstLen)
 {
    INT16U i = 0;
		
     if(type == 0)
		{
			pDstBuf[i++] = 0xFE;
		}		
    pDstBuf[i++] = 0x68;
    pDstBuf[i++] = 0xAA;
    pDstBuf[i++] = 0xAA;
    pDstBuf[i++] = 0xAA;
    pDstBuf[i++] = 0xAA;
    pDstBuf[i++] = 0xAA;
    pDstBuf[i++] = 0xAA;
    pDstBuf[i++] = 0x68;
    pDstBuf[i++] = 0x13;
    pDstBuf[i++] = 0x00;
    pDstBuf[i++] = 0xDF;
    pDstBuf[i++] = 0x16;
    vDstLen = i;
 }
 
//解码读表地址
INT8U cDTL2007::DecodeReadAmtAdd(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT Stu_Dtl2007 &DstDecode2007DataFrame)
{
 INT16U i = 0;
 INT8U ack = DACK_FAILURE;
	
 if(pSrcLen == 0)
 {
	 return DACK_FAILURE;
 }
 for(i = 0;i < pSrcLen;i++)
 {
  if(pSrcBuf[i] == 0x68)//查找第一个数68   
	break;
 }
 
 if((i + 18) <= pSrcLen)
 {
  if((pSrcBuf[i + 7] == 0x68)&&(pSrcBuf[i + 17] == 0x16) && (pSrcBuf[i + 8] == 0x93) && (pSrcBuf[i + 9] == 0x06))
  {
    for(INT8U m = 0;m < 6;m++)
    {
     DstDecode2007DataFrame.s_AmtBuf[m] = pSrcBuf[i + 10 + m] - 0x33;
    }
    ack = DACK_SUCESS;
  }
 }
 
 return ack;
}

//检测是否645协议
INT8U cDTL2007::Check645Full(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT INT16U &vDstLen)
{
    
	 INT16U i = 0;
	 INT8U ack = DACK_FAILURE;
   INT16U len8 = 0;
		 
	 if(pSrcLen > 11)//防止不是645的其他帧引起读末知空间,引发末知错误
	 {
		i = 0;//这以胶没有加。i=0;是比较危险的
		while(pSrcBuf[i] !=	0x68) //查找第一个0x68
		{
			i++;
			if(i >= pSrcLen)
			break;
	  }
		
	  if((i + 12) <= pSrcLen)//最小长度
	  {			      
		   if(pSrcBuf[i + 7] == 0x68) //为第二个68	
	     {	 
				i += 9;
	      len8 = pSrcBuf[i];//长度
			  if((i + len8 + 2 + 1) <= pSrcLen)//检测总长度
			  {	
					if(pSrcBuf[i + len8 + 2] == 0x16)//检测0x16
					{
						vDstLen = i + len8 + 2 + 1; //i从0开始 的 
						ack = DACK_SUCESS;
					}
				}						
	     }		 
	   }
	 }
	 
	  return ack;
}

//检测并发 645帧的个数 长度
INT8U cDTL2007::Check645Num(TH_IN const INT8U *pSrcBuf,TH_IN INT16U pSrcLen,TH_OUT INT8U &vNum,TH_OUT INT16U *plenBuf)
{
    
	 INT16U i = 0;
	 INT8U ack = DACK_FAILURE;
	// INT8U  reack = DACK_2_ERR_FAME;
	 INT16U lenIn = 0;//剩余长度
   INT16U lenOut = 0;
	  vNum = 0;
	 lenIn = pSrcLen;
	
	 for(i = 0;i < PARALLEL376_2_MAX_CNT;i++)
	 {
		 if(lenIn >= lenOut)
		 {
			 lenIn -= lenOut;	
		 }
		 else
		 {	 
			 break;
		 }
		 if(lenIn < 11)//剩余长度 不足是645的帧
     {
			 break;	
     }			 
		// reack = 
		 Check645Full(&pSrcBuf[pSrcLen-lenIn],lenIn,lenOut);
		 plenBuf[vNum] = lenOut;
		// if(DACK_SUCESS == reack)//若其中有一帧错误的话   后面考虑处理？
		 vNum++;
	 }
	 if(0 != vNum)
	 ack = DACK_SUCESS;
	 
	 return ack;
}

// :vDstAmtBuf表地址, vDstFcnt:FE个数  vDstFctFg:协议类型 1 645-97，2  645-07， 3：广播校时命令 :返回TRUE：是645协议
   INT8U cDTL2007::CheckFull645Pct_All(const INT8U *pSrcBuf,const INT16U pSrcLen,INT8U &vDstFctFg)//检测帧的最小长度
   {
    
	 INT16U i=0;
	 INT8U ack = DACK_FAILURE;
     INT8U len8=0;
	 INT8U con;
     if(pSrcLen>11)//防止不是645的其他帧引起读末知空间,引发末知错误
     {
      i=0;//这以胶没有加。i=0;是比较危险的
	   while(pSrcBuf[i]!=0x68) //查找第一个0x68
	   {
	     i++;
	    if(i>=pSrcLen) break;
	   }
	   if((i+12)<=pSrcLen)//最小长度
	   {
	       //vDstFcnt=i;
		  //i 为第一个68
		  
         // BufToBuf(vDstAmtBuf,&pSrcBuf[i+1],6);
	      
		 if(pSrcBuf[i+7]==0x68)
	     {
		    con=pSrcBuf[i+8];
		    con&=0x1f;
		    switch(con)
		    {
		     case 0x01:
		     case 0x02:
		    // case 0x03:07命令用于安全认证部分
		     case 0x04:
		     
		     case 0x0a:
		     case 0x0c:
		     case 0x0f:
		     case 0x10:
		          vDstFctFg=0x01;
		          break;
			 case 0x08:	//是广播校时命令
			     vDstFctFg=0x03;
			      break;
		     default:
		          vDstFctFg=0x02;
		          break;
		    
		    }

				 i+=9;
	        len8=pSrcBuf[i];//长度
	       if((i+len8+2+1)<=pSrcLen)//检测总长度
	       {
	          
					 //检测0x16
					 if(pSrcBuf[i+len8+2]==0x16)
					 {
						 ack = DACK_SUCESS;
					 }
	       }
		 }
	   }
	  }
	 
	  return ack;
   }
