/*---------------------------------------------------------------------------------
* Copyright (c)  2016 TENHE  TECHNOLOGY
* All rights reserved.
*
* 文件名称：cQCSG376_2.cpp

* 摘    要： 南网计量自动化系统本地通信规约
*
* 当前版本：1.1
* 作    者：陈小勇
* 完成日期：2017年3月12日
*
* 取代版本：
* 原 作 者：
* 完成日期：
*------------------------------------------------------------------------------*/
#ifdef DSYSCFG_STD_CSG //南网标准
#include "cQCSG376_2.h"
#include "RamManger.h"
#include "User_Fun_Def.h"
#include "MyFunLib.h"
extern INT8U QueMainMacAdd(INT8U *pDstBuf);
INT8U m_376_2_Seq =0;

INT8U cQCSG376_2::GetADDFlag(INT32U di)
{
	if(di == 0xE8020202 
		|| di == 0xE8020202
		|| di == 0xE8050502)
	{
		return 1;
	}
	return 0;
}
INT8U cQCSG376_2::Creat376_2Cs(TH_IN const INT8U *vSrcBuf,TH_IN const INT16U vSrcLen)
{
	INT8U cs = 0;
	
	for(INT16U m = 0; m<vSrcLen; m++)
	{
		cs += vSrcBuf[m];
	}
	return cs;
}
INT8U cQCSG376_2 :: ErrCodeTran(INT8U ErrType)
{
	INT8U ErrType376;
	  switch(ErrType)
			{
				case DACK_EER_OVERTIME:
						ErrType376 = 0;//通讯超时
						break;
							
				default:
						ErrType376 = ErrType;
						break;
			}
			return ErrType376;
}
//根据下行帧组上行帧用
INT8U cQCSG376_2:: Code376_2_FromDownHead(TH_IN const sPartQCSG376_2_Head  gframehead,TH_IN INT8U *vRcvBuf,TH_IN const INT16U Len,sCodeComCmdFrame  &CmdFram)
{
	 INT8U ack;
	 sPartQCSG376_2CreatFrame 		CSG376_2_UP;   
     CSG376_2_UP.s_head = Creat376_2UpFrameFormDownFrame(gframehead);
	 CSG376_2_UP.s_RcvDataBuf = vRcvBuf;
	 CSG376_2_UP.s_RcvDataLen = Len;
	 ack = Code376_2_Frame(CSG376_2_UP,CmdFram);

	 return ack;
}

INT8U cQCSG376_2::CodeAckOkFame(TH_IN const sPartQCSG376_2_Head  vSrcDownFameHead, sCodeComCmdFrame  &CmdFram)
{
	INT8U ack;
	sPartQCSG376_2_Head  gframehead;
	
//???	gframehead = Init376_2UpFrameNoMacAdd(vSrcDownFameHead.s_head.u_con.s_conBit.s_Con_ADD, 0x00, 0xE8010001);
	gframehead = Init376_2UpFrameNoMacAdd(0, 0x00, 0xE8010001);
	gframehead.s_Msg_Seq = vSrcDownFameHead.s_Msg_Seq;
	INT16U delaytime = gPLCONENODE_DLY_TIME; 

    INT8U tmpackbuf[3];	   	
	Hex16ToBuf2(delaytime,&tmpackbuf[0]);

	ack = Code376_2_FromDownHead(gframehead,tmpackbuf,2,CmdFram);
	return ack;
}

INT8U cQCSG376_2::CodeAckNoFame(TH_IN const sPartQCSG376_2_Head  vSrcDownFameHead,TH_IN const INT8U ErrType,sCodeComCmdFrame  &CmdFrame)
{
	INT8U ack;
	sPartQCSG376_2_Head  gframehead;

	//???	gframehead = Init376_2UpFrameNoMacAdd(vSrcDownFameHead.s_head.u_con.s_conBit.s_Con_ADD, 0x00, 0xE8010002);
	gframehead = Init376_2UpFrameNoMacAdd(0, 0x00, 0xE8010002);
	gframehead.s_Msg_Seq = vSrcDownFameHead.s_Msg_Seq;
	
	INT8U ErrType376=ErrCodeTran(ErrType);
	ack=Code376_2_FromDownHead(gframehead,&ErrType376,1,CmdFrame);
	return ack;
}
INT8U cQCSG376_2::Code376_2_Frame(TH_INOUT sPartQCSG376_2CreatFrame SrcCodeDataFrame,sCodeComCmdFrame  &CmdFrame)
{
	INT8U tmpbuf[2];
	return(CodePart376_2_Frame(SrcCodeDataFrame,tmpbuf,0,CmdFrame));
}
INT8U cQCSG376_2::CodePart376_2_FormDownHead(TH_IN const sPartQCSG376_2_Head  vSrcDownFameHead,const INT8U *pSrcFirstBuf,INT16U vFirstLen,INT8U *vSrcSecBuf,INT16U vSrcSecLen,sCodeComCmdFrame  &CmdFrame)
{
	
		 sPartQCSG376_2CreatFrame 		GDW376_2_UP;   
		  GDW376_2_UP.s_head = Creat376_2UpFrameFormDownFrame(vSrcDownFameHead);
			 GDW376_2_UP.s_RcvDataBuf = vSrcSecBuf;
			 GDW376_2_UP.s_RcvDataLen = vSrcSecLen;
    return(CodePart376_2_Frame(GDW376_2_UP,pSrcFirstBuf,vFirstLen,CmdFrame));
}
INT8U  cQCSG376_2::Code376_2_FromOnHead(TH_IN const sPartQCSG376_2_Head  gframehead,TH_IN INT8U *vRcvBuf,TH_IN const INT16U Len,sCodeComCmdFrame  &CmdFrame)
{
		INT8U ack;
		sPartQCSG376_2CreatFrame 		GDW376_2_UP;   
		GDW376_2_UP.s_head = gframehead;//帧头赋值
		GDW376_2_UP.s_RcvDataBuf = vRcvBuf;
		GDW376_2_UP.s_RcvDataLen = Len;
		ack = Code376_2_Frame(GDW376_2_UP,CmdFrame);

		return ack;
}

INT8U cQCSG376_2::CodePart376_2_Frame(TH_INOUT sPartQCSG376_2CreatFrame SrcCodeDataFrame,const INT8U *pSrcFirstBuf,INT16U vFirstLen,sCodeComCmdFrame  &CmdFrame)
{
	INT8U  cs = 0;
	INT16U i = 0;
	INT16U j;
	INT16U tmp16;
	INT8U ack = DACK_ERR_BUF;
	INT16U SendDataBufMaxLen;
	if((SrcCodeDataFrame.s_RcvDataLen > 0) && (SrcCodeDataFrame.s_RcvDataBuf == DBUFNULL))
	{
		ack = DACK_ERR_BUF;
		return ack;
	}

	ack=DACK_ERR_BUF;
  	INT16U Cu376famelen = D376_2_NODATALEN + SrcCodeDataFrame.s_RcvDataLen + vFirstLen;
	CmdFrame.s_SendDataBuf = (INT8U*)QOS_DMalloc(Cu376famelen);
	SendDataBufMaxLen= Cu376famelen;
	
	if(CmdFrame.s_SendDataBuf != DBUFNULL)
	{
		//简单检查长度
		tmp16 = 6 + 6 + SrcCodeDataFrame.s_RcvDataLen+vFirstLen;//固定(6)(68+len+len+con+cs+16)+AFN(1)+SEQ(1)+Fn(4)
		
		if(SrcCodeDataFrame.s_head.u_con.s_conBit.s_Con_ADD)//判断是否有地址域
		{
			tmp16 += DMACADD_LEN + DMACADD_LEN;
		}
	 
		if(tmp16 <= SendDataBufMaxLen)
		{
			INT8U *ptempbuf = CmdFrame.s_SendDataBuf;
			
			i=0;
			ptempbuf[i++] = 0x68;      //起始字符
			ptempbuf[i++] = (INT8U)tmp16;        //长度
			ptempbuf[i++] = tmp16>>8;		 
			ptempbuf[i++] = SrcCodeDataFrame.s_head.u_con.s_conByte;         //con，固定宽代

			//地址处理
			if(SrcCodeDataFrame.s_head.u_con.s_conBit.s_Con_ADD)//不是采集器模块才有地址
			{
				for(j=0; j<DMACADD_LEN; j++)       //源地址域    
				{
					ptempbuf[i++] = SrcCodeDataFrame.s_head.s_MainAddBuf[j];
				}

				for(j=0; j<DMACADD_LEN; j++)       //目得地址域    
				{
					ptempbuf[i++] = SrcCodeDataFrame.s_head.s_DestAddBuf[j];
				}
			}		
			ptempbuf[i++] = SrcCodeDataFrame.s_head.s_AFN;     //应用功能码
			
			 //序号
			ptempbuf[i++] = SrcCodeDataFrame.s_head.s_Msg_Seq;
			 
			ptempbuf[i++] = (INT8U)SrcCodeDataFrame.s_head.s_FN;              //数据单元标识
			ptempbuf[i++] = SrcCodeDataFrame.s_head.s_FN >> 8;
			ptempbuf[i++] = SrcCodeDataFrame.s_head.s_FN >> 16;
			ptempbuf[i++] = SrcCodeDataFrame.s_head.s_FN >> 24;
			
			for(j=0; j<vFirstLen; j++)     //数据单元
			{
				ptempbuf[i++] = pSrcFirstBuf[j];
			}
			
			for(j=0; j<SrcCodeDataFrame.s_RcvDataLen; j++)     //数据单元
			{
				ptempbuf[i++] = SrcCodeDataFrame.s_RcvDataBuf[j];
			}
			
			cs = Creat376_2Cs(&ptempbuf[3],i-3); //帧校验和
			ptempbuf[i++] = cs;         
			ptempbuf[i++] = 0x16;        //结束符
			CmdFrame.s_SendDataLen = i;                 //一帧的长度
			ack = DACK_SUCESS;
		}
		else
		{
			ack = DACK_ERR_BUF;
			QOS_DFree(CmdFrame.s_SendDataBuf);
		}
	}
	return ack;
}

INT8U cQCSG376_2::Decode376_2Frame(TH_IN  INT8U *pSrcBuf,TH_IN  INT16U vSrcLen,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U  cs = 0;
	INT16U i = 0;
	INT16U j;
	INT8U  temp;
	INT8U  ack = DACK_ERR_NULL;     //ACKNULL需定义
	INT16U tmp16;
	
	if(vSrcLen >= D376_2_MIN_FRAME_LEN)//最少长度是12个长度
	{
		i=0;
				//把前导的不完整的帧都过去
		for(i=0; i<vSrcLen; i++)
		{
			if(pSrcBuf[i] != 0x68)   //找到帧头
			{
				continue;
			}
			if(i + D376_2_MIN_FRAME_LEN <= vSrcLen)
			{ 
				tmp16 = pSrcBuf[i+2];//长度
				tmp16 <<= 8;
				tmp16 |= pSrcBuf[i+1];          //用户数据单元长度度和6个字节的固定长度(起始字符、长度、控制域、校验和、结束字符)  
				if((tmp16 > 6) && ((tmp16+i) <= (vSrcLen)))//长度合法
				{
					if(pSrcBuf[tmp16+i-1] == 0x16)
					break;
				}
			}
		}
		if((i + D376_2_MIN_FRAME_LEN) <= vSrcLen)
		{ 
			i++;//过68
			tmp16 = pSrcBuf[i+1];//长度
			tmp16 <<= 8;
			tmp16 |= pSrcBuf[i];          //用户数据单元常度和6个字节的固定长度(起始字符、长度、控制域、校验和、结束字符)  
			if((tmp16 > 6)&&((tmp16+i) <= (vSrcLen+1)))//长度合法
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
						
					    if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_ADD)
						{
							if((i+12) <= vSrcLen)
							{
								for(j=0; j<6; j++)
								{
									DstDecodeDataFrame.s_head.s_MainAddBuf[j] = pSrcBuf[i+j];
								}
								i += 6;

								i += temp*6;
								for(j=0;j<6;j++)
								{
									DstDecodeDataFrame.s_head.s_DestAddBuf[j] = pSrcBuf[i+j];
								}
								i += 6;
							}
						  	else 
								return ack;
						}
							
						
						if(i + 8 <= vSrcLen)//有AFN，SEQ, FN,CS和16
						{
							 DstDecodeDataFrame.s_head.s_AFN = pSrcBuf[i++];      //应用功能码
							 DstDecodeDataFrame.s_head.s_Msg_Seq = pSrcBuf[i++];
							 
							 DstDecodeDataFrame.s_head.s_FN = pSrcBuf[i+3];
							 DstDecodeDataFrame.s_head.s_FN <<= 8;
							 DstDecodeDataFrame.s_head.s_FN |= pSrcBuf[i+2];
							 DstDecodeDataFrame.s_head.s_FN <<= 8;
							 DstDecodeDataFrame.s_head.s_FN |= pSrcBuf[i+1];
							 DstDecodeDataFrame.s_head.s_FN <<= 8;
							 DstDecodeDataFrame.s_head.s_FN |= pSrcBuf[i];             //数据单元标识
							 i += 4;
							 DstDecodeDataFrame.s_RcvDataLen = vSrcLen-i-2;
							 DstDecodeDataFrame.s_RcvDataBuf = &pSrcBuf[i];
							 ack = DACK_SUCESS;
						 }
					} 
					else
					{
						ack=DACK_ERR_CS;
						
					}
				}
			}
		}		
	}
	return ack;
}
 
INT8U cQCSG376_2::Check_376_2_Full(TH_IN const INT8U *pSrcBuf, TH_IN INT16U vSrcLen, TH_OUT INT16U &vDstLen)
{
	INT16U tmp16;
	INT16U i = 0;
	
	vDstLen=vSrcLen;
	if(vSrcLen >= D376_2_MIN_FRAME_LEN)//最少长度是12个长度
	{				
		for(i=0; i<vSrcLen; i++)
	    {
			if(pSrcBuf[i] == 0x68)   //找到帧头
				break;
		}
		if(i + D376_2_MIN_FRAME_LEN <= vSrcLen)
		{ 
			tmp16 = pSrcBuf[i+2];//长度
			tmp16 <<= 8;
			tmp16 |= pSrcBuf[i+1];          //用户数据单元常度和6个字节的固定长度(起始字符、长度、控制域、校验和、结束字符)  
			if((tmp16 > 6) && ((tmp16 + i) <= (vSrcLen)))//长度合法
			{
				if(pSrcBuf[tmp16+i-1] == 0x16)
				{
					vDstLen = tmp16 + i;
					return DACK_SUCESS;
				}
			}
		}	        
    }
	return DACK_ERR_NULL;
}

sPartQCSG376_2_Head cQCSG376_2::Creat376_2UpFrameFormDownFrame(TH_IN const sPartQCSG376_2_Head  downframe)
{
	sPartQCSG376_2_Head  tmpfame;
	tmpfame.u_con.s_conBit.s_Con_reserved = 0;
	tmpfame.u_con.s_conBit.s_Con_VER = 0;
	tmpfame.u_con.s_conBit.s_Con_ADD = GetADDFlag(downframe.s_FN);
	tmpfame.u_con.s_conBit.s_Con_DIR = DV376_2CON_DIR_COMMD;
	tmpfame.u_con.s_conBit.s_Con_PRM = DV376_2CON_PRM_SLAVE;
	
	if(tmpfame.u_con.s_conBit.s_Con_ADD == 1)
	{
		for(INT8U m=0; m<DMACADD_LEN; m++)
		{
			tmpfame.s_MainAddBuf[m] = downframe.s_DestAddBuf[m];
		}
		
		for(INT8U m=0; m<DMACADD_LEN; m++)
		{
			tmpfame.s_DestAddBuf[m] = downframe.s_MainAddBuf[m];
		}
	}
	tmpfame.s_AFN = downframe.s_AFN;
	tmpfame.s_Msg_Seq = downframe.s_Msg_Seq;
	tmpfame.s_FN = downframe.s_FN;
	
	return tmpfame;
}
sPartQCSG376_2_Head cQCSG376_2::Init376_2UpFrameNoMacAdd(TH_IN  INT8U AddFg, TH_IN INT8U vSrcAfn, TH_IN INT32U vSrcFn)
{
	INT8U tmpbuf[DMACADD_LEN];
	
	BufIsValue(tmpbuf, DMACADD_LEN, 0xCC);
	return(Init376_2UpFrame(AddFg, tmpbuf, vSrcAfn, vSrcFn));
	
}
sPartQCSG376_2_Head cQCSG376_2::Init376_2UpFrame(TH_IN  INT8U AddFg, TH_IN const INT8U *pSrcAddBuf, TH_IN INT8U vSrcAfn, TH_IN INT32U vSrcFn)
{	
	sPartQCSG376_2_Head  tmpfame;

	tmpfame.u_con.s_conBit.s_Con_reserved = 0;
	tmpfame.u_con.s_conBit.s_Con_VER = 0;
	tmpfame.u_con.s_conBit.s_Con_ADD = AddFg;
	tmpfame.u_con.s_conBit.s_Con_DIR = DV376_2CON_DIR_COMMD;
	tmpfame.u_con.s_conBit.s_Con_PRM = DV376_2CON_PRM_MASTER;

	QueMainMacAdd(tmpfame.s_DestAddBuf);
	
	for(INT8U m = 0; m<DMACADD_LEN; m++)
	{
		tmpfame.s_MainAddBuf[m] = pSrcAddBuf[m];
	}
	
	tmpfame.s_AFN = vSrcAfn;

	m_376_2_Seq++;
	tmpfame.s_Msg_Seq=m_376_2_Seq;
	
	tmpfame.s_FN = vSrcFn;
	return tmpfame;
}

INT8U  cQCSG376_2::  Code376_2_UpFrame(TH_IN  INT8U MsgComFg,TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,INT8U *pSrcRcvBuf,INT16U vSrcRcvLen,TH_OUT  sQCSG376_2UpFrame &sQCSG376_2UpFrame)
{
	INT8U ack;
	sCodeComCmdFrame  CmdFrame;
	sPartQCSG376_2CreatFrame  upframe;
	upframe.s_head = Init376_2UpFrame(MsgComFg,pSrcAddBuf,vSrcAfn,vSrcFn);
	upframe.s_RcvDataBuf = pSrcRcvBuf;
	upframe.s_RcvDataLen= vSrcRcvLen;
	ack = Code376_2_Frame(upframe,CmdFrame);
	if(ack == DACK_SUCESS)
	{
		sQCSG376_2UpFrame.s_Msg_Seq = upframe.s_head.s_Msg_Seq;
		sQCSG376_2UpFrame.s_SendDataBuf = CmdFrame.s_SendDataBuf;
		sQCSG376_2UpFrame.s_SendDataLen = CmdFrame.s_SendDataLen;
		
	}
	return ack;
}
#endif //DSYSCFG_STD_CSG

