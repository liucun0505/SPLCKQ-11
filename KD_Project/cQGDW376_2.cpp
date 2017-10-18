/*---------------------------------------------------------------------------------
* Copyright (c)  2016 TENHE  TECHNOLOGY
* All rights reserved.
*
* 文件名称：cQGDW376_2.cpp

* 摘    要： 376.2协议
*
* 当前版本：1.1
* 作    者：杨虎岳
* 完成日期：2016年6月29日
*
* 取代版本：
* 原 作 者：
* 完成日期：
*------------------------------------------------------------------------------*/

#include "cCCOMsgOp.H"
extern cCCOMsgOP gCCoMsgOP;
#include "cQGDW376_2.h"
#include "RamManger.h"

INT8U cQGDW376_2::Creat376_2Cs(TH_IN const INT8U *vSrcBuf,TH_IN const INT16U vSrcLen)
{
	INT8U cs = 0;
	
	for(INT16U m = 0; m<vSrcLen; m++)
	{
		cs += vSrcBuf[m];
	}
	return cs;
}
 
INT8U cQGDW376_2::Code376_2_Frame(TH_INOUT sPartQGDW376_2CreatFrame &SrcCodeDataFrame)
{
	INT8U  cs = 0;
	INT16U i = 0;
	INT16U j;
	INT16U tmp16;
	INT8U ack = DACK_ERR_BUF;
	
	if((SrcCodeDataFrame.s_RcvDataLen > 0) && (SrcCodeDataFrame.s_RcvDataBuf == DBUFNULL))
	{
		ack = DACK_ERR_BUF;
		return ack;
	}

	ack=DACK_ERR_BUF;
  INT16U Cu376famelen = D376_2_NODATALEN + SrcCodeDataFrame.s_RcvDataLen;
	SrcCodeDataFrame.s_SendDataBuf = (INT8U*)QOS_DMalloc(Cu376famelen);
	SrcCodeDataFrame.s_SendDataBufMaxLen = Cu376famelen;
	
	
 if(SrcCodeDataFrame.s_SendDataBuf != DBUFNULL)
 {
		
		//简单检查长度
		tmp16 = 6 + 6 + 3 + SrcCodeDataFrame.s_RcvDataLen;//固定(6)(68+len+len+con+cs+16)+信息(6)+AFN(1)+Fn(2)
		
		if(SrcCodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_ComFlag)//判断是否有地址域
		{
			tmp16 += DMACADD_LEN + DMACADD_LEN;
		}
	 
		if(tmp16 <= SrcCodeDataFrame.s_SendDataBufMaxLen)
		{
			 INT8U *ptempbuf = SrcCodeDataFrame.s_SendDataBuf;
			//27=6+18+1+2=lenth(R+A+AFN+DT) 6=lenth(起始字符+长度+控制码+帧校验和+结束符)
				i=0;
				ptempbuf[i++] = 0x68;      //起始字符
				ptempbuf[i++] = (INT8U)tmp16;        //长度
				ptempbuf[i++] = tmp16>>8;		 
				ptempbuf[i++] = SrcCodeDataFrame.s_head.u_con.s_conByte;         //con，固定宽代
				 
				//信息域处理
				for(INT8U m=0; m<5; m++)
				 {
						ptempbuf[i++] = SrcCodeDataFrame.s_head.u_msg.s_msgbuf[m];
				 }
				 //序号
				 ptempbuf[i++] = SrcCodeDataFrame.s_head.s_Msg_Seq;
				 
				//地址处理
				if(SrcCodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_ComFlag)//不是采集器模块才有地址
				{
					for(j=0; j<DMACADD_LEN; j++)       //源地址域    
					{
						ptempbuf[i++] = SrcCodeDataFrame.s_head.s_MainAddBuf[j];
					}
					//		for(j=0;j<(relaycnt*DMACADD_LEN);j++)       //中继地址域    
					//		{
					//			cs+=SrcCodeDataFrame.s_RelayAddBuf[j];
					//			ptempbuf[i++]=SrcCodeDataFrame.s_RelayAddBuf[j];
					//		}
					for(j=0; j<DMACADD_LEN; j++)       //目得地址域    
					{
						ptempbuf[i++] = SrcCodeDataFrame.s_head.s_DestAddBuf[j];
					}
				}		
				
				ptempbuf[i++] = SrcCodeDataFrame.s_head.s_AFN;     //应用功能码
				ptempbuf[i++] = (INT8U)SrcCodeDataFrame.s_head.s_FN;              //数据单元标识
				ptempbuf[i++] = SrcCodeDataFrame.s_head.s_FN>>8;
				
				for(j=0; j<SrcCodeDataFrame.s_RcvDataLen; j++)     //数据单元
				{
					ptempbuf[i++] = SrcCodeDataFrame.s_RcvDataBuf[j];
				}
				
				cs = Creat376_2Cs(&ptempbuf[3],i-3); //帧校验和
				ptempbuf[i++] = cs;         
				ptempbuf[i++] = 0x16;        //结束符
				SrcCodeDataFrame.s_SendDataLen = i;                 //一帧的长度
				ack = DACK_SUCESS;
		}
		else
		{
			ack = DACK_ERR_BUF;
			QOS_DFree(SrcCodeDataFrame.s_SendDataBuf);
		}
		
		
	}
		return ack;
}

INT8U cQGDW376_2::Decode376_2Frame(TH_IN  INT8U *pSrcBuf,TH_IN  INT16U vSrcLen,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U  cs = 0;
	INT16U i = 0;
	INT16U j;
	INT8U  temp;
	INT8U  ack = DACK_ERR_NULL;     //ACKNULL需定义
	INT16U tmp16;
		if(vSrcLen >= 13)//最少长度是13个长度
			{
				i=0;
					//把前导的不完整的帧都过去
			for(i=0; i<vSrcLen; i++)
			{
				if(pSrcBuf[i] != 0x68)   //找到帧头
				{
					continue;
				}
				if(i+13 <= vSrcLen)
				{ 
					tmp16 = pSrcBuf[i+2];//长度
					tmp16 <<= 8;
					tmp16 |= pSrcBuf[i+1];          //用户数据单元常度和6个字节的固定长度(起始字符、长度、控制域、校验和、结束字符)  
					if((tmp16>6) && ((tmp16+i) <= (vSrcLen)))//长度合法
					{
						if(pSrcBuf[tmp16+i-1] == 0x16)
						break;
					}
				}
			}
			if((i+13) <= vSrcLen)
			{ 
				i++;//过68
				tmp16 = pSrcBuf[i+1];//长度
				tmp16 <<= 8;
				tmp16 |= pSrcBuf[i];          //用户数据单元常度和6个字节的固定长度(起始字符、长度、控制域、校验和、结束字符)  
				if((tmp16>6)&&((tmp16+i) <= (vSrcLen+1)))//长度合法
				{
					i += 2;
					for(j=0;j<tmp16-5;j++)//去掉CS 和16
					{
						cs += pSrcBuf[i+j];//
					}
					if(0x16 == pSrcBuf[i+j+1])//16合法
					{
						if(cs == pSrcBuf[i+j])//CS合法
						{
								//控制域					
							DstDecodeDataFrame.s_head.u_con.s_conByte = pSrcBuf[i++];	
							
							for(INT8U m=0; m<5; m++)
							{
								DstDecodeDataFrame.s_head.u_msg.s_msgbuf[m] = pSrcBuf[i++];
							}						
					    DstDecodeDataFrame.s_head.s_Msg_Seq = pSrcBuf[i++];	
							
						  if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_Msg_ComFlag) //不是采集器模块才有地址
							{
								//temp=DstDecodeDataFrame.s_MsgBuf[0]>>4;//中继级别
								temp = 0;//120525yhychange 上行报文时中继级别不判断
								if((i+(temp+2)*6) <= vSrcLen)
								{
									for(j=0; j<6; j++)
									DstDecodeDataFrame.s_head.s_MainAddBuf[j] = pSrcBuf[i+j];
									i+=6;
	//					    if(temp<=DZB_MAXZJ_CNT)
	//					    {
	//					      for(j=0;j<(temp*6);j++)
	//					       DstDecodeDataFrame.s_RelayAddBuf[j]=pSrcBuf[i+j];
	//					    }
	//					    else
	//					    {
	//					       for(j=0;j<(DZB_MAXZJ_CNT+2)*6;j++)
	//					       DstDecodeDataFrame.s_RelayAddBuf[j]=pSrcBuf[i+j];
	//					    }
									i += temp*6;
									for(j=0;j<6;j++)
									DstDecodeDataFrame.s_head.s_DestAddBuf[j] = pSrcBuf[i+j];
									i += 6;
								}
							  else 
									return ack;
							}
							
							if(i+5<=vSrcLen)//有AFN，和FN,CS和16
							{
								 DstDecodeDataFrame.s_head.s_AFN = pSrcBuf[i++];      //应用功能码
								 DstDecodeDataFrame.s_head.s_FN = pSrcBuf[i+1];
								 DstDecodeDataFrame.s_head.s_FN <<= 8;
								 DstDecodeDataFrame.s_head.s_FN |= pSrcBuf[i];             //数据单元标识
								 i += 2;
								 DstDecodeDataFrame.s_RcvDataLen = vSrcLen-i-2;
								 DstDecodeDataFrame.s_RcvDataBuf = &pSrcBuf[i];
								 ack = DACK_SUCESS;
							 }
							
						} 
						else
							ack=DACK_ERR_CS;
					}
				}
			}		
		}
	return ack;
}
 
INT8U cQGDW376_2::Check_376_2_Full(TH_IN const INT8U *pSrcBuf, TH_IN INT16U vSrcLen, TH_OUT INT16U &vDstLen)
{
	INT16U tmp16;
  INT16U i=0;
	vDstLen=vSrcLen;
		   if(vSrcLen >= 13)//最少长度是13个长度
			{				
				for(i=0; i<vSrcLen; i++)
		    {
					if(pSrcBuf[i] == 0x68)   //找到帧头
					break;
			  }
				if(i+13 <= vSrcLen)
				{ 
					tmp16 = pSrcBuf[i+2];//长度
					tmp16 <<= 8;
					tmp16 |= pSrcBuf[i+1];          //用户数据单元常度和6个字节的固定长度(起始字符、长度、控制域、校验和、结束字符)  
					if((tmp16>6)&&((tmp16+i) <= (vSrcLen)))//长度合法
					{
						if(pSrcBuf[tmp16+i-1] == 0x16)
						{
							vDstLen = tmp16+i;
							return DACK_SUCESS;
						}
					}
	      }	        
	    }
	return DACK_ERR_NULL;
}

sPartQGDW376_2_Head cQGDW376_2::Creat376_2UpFrameFormDownFrame(TH_IN const sPartQGDW376_2_Head  downframe)
{
	sPartQGDW376_2_Head  tmpfame;
	tmpfame.u_con.s_conBit.s_Con_ComMode = DV376_2CON_COM_MODE;
	tmpfame.u_con.s_conBit.s_Con_DIR = DV376_2CON_DIR_COMMD;
	tmpfame.u_con.s_conBit.s_Con_PRM = DV376_2CON_PRM_SLAVE;
	tmpfame.u_msg.s_UpMsgBit.s_AckCsq = 0;//应答信号品质
	tmpfame.u_msg.s_UpMsgBit.s_chanle_num = 0;
	tmpfame.u_msg.s_UpMsgBit.s_CmdCsq = 0;//命令信号品质
	tmpfame.u_msg.s_UpMsgBit.s_Meter_flag = 0;
	tmpfame.u_msg.s_UpMsgBit.s_Msg_ComFlag = downframe.u_msg.s_DownMsgBit.s_Msg_ComFlag;
	tmpfame.u_msg.s_UpMsgBit.s_Msg_Event = DV376_2MSG_EVENT_OFF;
	tmpfame.u_msg.s_UpMsgBit.s_Msg_phase = 0;
	tmpfame.u_msg.s_UpMsgBit.s_Msg_RouterFlag = 1;
	tmpfame.s_Msg_Seq = downframe.s_Msg_Seq;
	
	for(INT8U m=0; m<DMACADD_LEN; m++)
	{
		tmpfame.s_MainAddBuf[m] = downframe.s_DestAddBuf[m];
	}
	
	for(INT8U m=0; m<DMACADD_LEN; m++)
	{
		tmpfame.s_DestAddBuf[m] = downframe.s_MainAddBuf[m];
	}
	//	if((downframe.s_AFN==0x14)&&(downframe.s_FN==F1))
	//	{
	//		tmpfame.s_AFN=0x06;
	//	  tmpfame.s_FN=F2;
	//	}
	//	else
	{
		tmpfame.s_AFN = downframe.s_AFN;
	  tmpfame.s_FN = downframe.s_FN;
	}
	return tmpfame;
}

sPartQGDW376_2_Head cQGDW376_2::Init376_2UpFrame(TH_IN  INT8U MsgComFg, TH_IN const INT8U *pSrcAddBuf, TH_IN INT8U vSrcAfn, TH_IN INT16U vSrcFn)
{	
	sPartQGDW376_2_Head  tmpfame;
	
	tmpfame.u_con.s_conBit.s_Con_ComMode = DV376_2CON_COM_MODE;
	tmpfame.u_con.s_conBit.s_Con_DIR = DV376_2CON_DIR_COMMD;
	tmpfame.u_con.s_conBit.s_Con_PRM = DV376_2CON_PRM_MASTER;	
	
	tmpfame.u_msg.s_UpMsgBit.s_Msg_RouterFlag = 1;		
	tmpfame.u_msg.s_UpMsgBit.s_reserved_1	= 0;
	tmpfame.u_msg.s_UpMsgBit.s_Msg_ComFlag = MsgComFg;
	tmpfame.u_msg.s_UpMsgBit.s_reserved_2	= 0;	

	tmpfame.u_msg.s_UpMsgBit.s_chanle_num = 0;
	tmpfame.u_msg.s_UpMsgBit.s_reserved_3	= 0;

	tmpfame.u_msg.s_UpMsgBit.s_Msg_phase = 0;	
	tmpfame.u_msg.s_UpMsgBit.s_Meter_flag = 0;	
	
	tmpfame.u_msg.s_UpMsgBit.s_CmdCsq = 0;	
	tmpfame.u_msg.s_UpMsgBit.s_AckCsq = 0;	
	
	tmpfame.u_msg.s_UpMsgBit.s_Msg_Event = DV376_2MSG_EVENT_OFF;
	tmpfame.u_msg.s_UpMsgBit.s_reserved_4	= 0;
	
	tmpfame.s_Msg_Seq=gCCoMsgOP.Cread376_2_SEQ();
	
	gCCoMsgOP.QueMainAdd(tmpfame.s_MainAddBuf);
	
	for(INT8U m = 0; m<DMACADD_LEN; m++)
	{
		tmpfame.s_DestAddBuf[m] = pSrcAddBuf[m];
	}
	
	tmpfame.s_AFN = vSrcAfn;
	tmpfame.s_FN = vSrcFn;
	return tmpfame;
}

INT8U  cQGDW376_2::  Code376_2_UpFrame(TH_IN  INT8U MsgComFg,TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,INT8U *pSrcRcvBuf,INT16U vSrcRcvLen,TH_OUT  sQGDW376_2UpFrame &sQGDW376_2UpFrame)
{
	INT8U ack;
	sPartQGDW376_2CreatFrame  upframe;
	upframe.s_head = Init376_2UpFrame(MsgComFg,pSrcAddBuf,vSrcAfn,vSrcFn);
	upframe.s_RcvDataBuf = pSrcRcvBuf;
	upframe.s_RcvDataLen= vSrcRcvLen;
	ack = Code376_2_Frame(upframe);
	if(ack == DACK_SUCESS)
	{
		sQGDW376_2UpFrame.s_Msg_Seq = upframe.s_head.s_Msg_Seq;
		sQGDW376_2UpFrame.s_SendDataBuf = upframe.s_SendDataBuf;
		sQGDW376_2UpFrame.s_SendDataLen = upframe.s_SendDataLen;
		
	}
	return ack;
}
//void Init376_2DownFrame(INT8U MsgComFg,INT8U *vDestAddBuf,INT8U vSrcAfn,INT16U vSrcFn)
//{
//	
//}
