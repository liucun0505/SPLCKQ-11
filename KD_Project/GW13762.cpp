#include "StdAfx.h"
#include "User_gDefine.h"
#include "GW13762.h"
#include "CSG13762.h"
#include "MainFrm.h"

CGW13762::CGW13762(void)
{
	 m_376seq = 0;
	/* for(INT8U m = 0;m<6;m++)
	 {
		 m_376Mainadd[m]=m_HostNodeAddress[m];
	 }*/
}
CGW13762::~CGW13762(void)
{
}

void CGW13762::SetMainAdd(INT8U *vSrcBuf)
{
    for(INT8U m = 0;m<6;m++)
	 {
		 m_376Mainadd[m]=vSrcBuf[m];
	 }
}
void CGW13762::QueMainAdd(INT8U *vDstBuf)
{
	 for(INT8U m = 0;m<6;m++)
	 {
		 vDstBuf[m]=m_376Mainadd[m];
	 }
}
/*---------------------------------------------------------------------------------
* Copyright (c)  2016 TENHE  TECHNOLOGY
* All rights reserved.
*
* ÎÄ¼þÃû³Æ£ºcQGDW376_2.cpp

* Õª    Òª£º 376.2Ð­Òé
*
* µ±Ç°°æ±¾£º1.1
* ×÷    Õß£ºÑî»¢ÔÀ
* Íê³ÉÈÕÆÚ£º2016Äê6ÔÂ29ÈÕ
*
* È¡´ú°æ±¾£º
* Ô­ ×÷ Õß£º
* Íê³ÉÈÕÆÚ£º
*------------------------------------------------------------------------------*/



INT8U CGW13762::Creat376_2Cs(TH_IN const INT8U *vSrcBuf,TH_IN const INT16U vSrcLen)
{
	INT8U cs = 0;
	
	for(INT16U m = 0; m<vSrcLen; m++)
	{
		cs += vSrcBuf[m];
	}
	return cs;
}
 
INT8U CGW13762::Code376_2_Frame(TH_INOUT sPartQGDW376_2CreatFrame &SrcCodeDataFrame)
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

 if(SrcCodeDataFrame.s_SendDataBuf != DBUFNULL)
 {
		
		//¼òµ¥¼ì²é³¤¶È
		tmp16 = 6 + 6 + 3 + SrcCodeDataFrame.s_RcvDataLen;//¹Ì¶¨(6)(68+len+len+con+cs+16)+ÐÅÏ¢(6)+AFN(1)+Fn(2)

		if(SrcCodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_ComFlag)//ÅÐ¶ÏÊÇ·ñÓÐµØÖ·Óò
		{
			tmp16 += DMACADD_LEN + DMACADD_LEN;
		}

		if(tmp16 <= D376_MAXSENDBUFLEN)
		{
			 INT8U *ptempbuf = SrcCodeDataFrame.s_SendDataBuf;
			//27=6+18+1+2=lenth(R+A+AFN+DT) 6=lenth(ÆðÊ¼×Ö·û+³¤¶È+¿ØÖÆÂë+Ö¡Ð£ÑéºÍ+½áÊø·û)
				i=0;
				ptempbuf[i++] = 0x68;      //ÆðÊ¼×Ö·û
				ptempbuf[i++] = (INT8U)tmp16;        //³¤¶È
				ptempbuf[i++] = tmp16>>8;		 
				ptempbuf[i++] = SrcCodeDataFrame.s_head.u_con.s_conByte;         //con£¬¹Ì¶¨¿í´ú
				 
				//ÐÅÏ¢Óò´¦Àí
				for(INT8U m=0; m<5; m++)
				 {
						ptempbuf[i++] = SrcCodeDataFrame.s_head.u_msg.s_msgbuf[m];
				 }
				 //ÐòºÅ
				 ptempbuf[i++] = SrcCodeDataFrame.s_head.s_Msg_Seq;
				 
				//µØÖ·´¦Àí
				if(SrcCodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_ComFlag)//²»ÊÇ²É¼¯Æ÷Ä£¿é²ÅÓÐµØÖ·
				{
					for(j=0; j<DMACADD_LEN; j++)       //Ô´µØÖ·Óò    
					{
						ptempbuf[i++] = SrcCodeDataFrame.s_head.s_MainAddBuf[j];
					}
					//		for(j=0;j<(relaycnt*DMACADD_LEN);j++)       //ÖÐ¼ÌµØÖ·Óò    
					//		{
					//			cs+=SrcCodeDataFrame.s_RelayAddBuf[j];
					//			ptempbuf[i++]=SrcCodeDataFrame.s_RelayAddBuf[j];
					//		}
					for(j=0; j<DMACADD_LEN; j++)       //Ä¿µÃµØÖ·Óò    
					{
						ptempbuf[i++] = SrcCodeDataFrame.s_head.s_DestAddBuf[j];
					}
				}		
				
				ptempbuf[i++] = SrcCodeDataFrame.s_head.s_AFN;     //Ó¦ÓÃ¹¦ÄÜÂë
				ptempbuf[i++] = (INT8U)SrcCodeDataFrame.s_head.s_FN;              //Êý¾Ýµ¥Ôª±êÊ¶
				ptempbuf[i++] = SrcCodeDataFrame.s_head.s_FN>>8;
				
				//if(SrcCodeDataFrame.s_RcvDataLen < 2048)

			for(j=0; j<SrcCodeDataFrame.s_RcvDataLen; j++)     //Êý¾Ýµ¥Ôª
			{
				ptempbuf[i++] = SrcCodeDataFrame.s_RcvDataBuf[j];
			}

				
				cs = Creat376_2Cs(&ptempbuf[3],i-3); //Ö¡Ð£ÑéºÍ
				ptempbuf[i++] = cs;         
				ptempbuf[i++] = 0x16;        //½áÊø·û
				SrcCodeDataFrame.s_SendDataLen = i;                 //Ò»Ö¡µÄ³¤¶È
				ack = DACK_SUCESS;
		}
		else
		{
			ack = DACK_ERR_BUF;
		}
		
		
	}
		return ack;
}

INT8U CGW13762::Decode376_2Frame(TH_IN  INT8U *pSrcBuf,TH_IN  INT16U vSrcLen,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U  cs = 0;
	INT16U i = 0;
	INT16U j;
	INT8U  temp;
	INT8U  ack = DACK_ERR_NULL;     //ACKNULLÐè¶¨Òå
	INT16U tmp16;
		if(vSrcLen >= 13)//×îÉÙ³¤¶ÈÊÇ13¸ö³¤¶È
			{
				i=0;
					//°ÑÇ°µ¼µÄ²»ÍêÕûµÄÖ¡¶¼¹ýÈ¥
			for(i=0; i<vSrcLen; i++)
			{
				if(pSrcBuf[i] != 0x68)   //ÕÒµ½Ö¡Í·
				{
					continue;
				}
				if(i+13 <= vSrcLen)
				{ 
					tmp16 = pSrcBuf[i+2];//³¤¶È
					tmp16 <<= 8;
					tmp16 |= pSrcBuf[i+1];          //ÓÃ»§Êý¾Ýµ¥Ôª³£¶ÈºÍ6¸ö×Ö½ÚµÄ¹Ì¶¨³¤¶È(ÆðÊ¼×Ö·û¡¢³¤¶È¡¢¿ØÖÆÓò¡¢Ð£ÑéºÍ¡¢½áÊø×Ö·û)  
					if((tmp16>6) && ((tmp16+i) <= (vSrcLen)))//³¤¶ÈºÏ·¨
					{
						if(pSrcBuf[tmp16+i-1] == 0x16)
						break;
					}
				}
			}
			if((i+13) <= vSrcLen)
			{ 
				i++;//¹ý68
				tmp16 = pSrcBuf[i+1];//³¤¶È
				tmp16 <<= 8;
				tmp16 |= pSrcBuf[i];          //ÓÃ»§Êý¾Ýµ¥Ôª³£¶ÈºÍ6¸ö×Ö½ÚµÄ¹Ì¶¨³¤¶È(ÆðÊ¼×Ö·û¡¢³¤¶È¡¢¿ØÖÆÓò¡¢Ð£ÑéºÍ¡¢½áÊø×Ö·û)  
				if((tmp16>6)&&((tmp16+i) <= (vSrcLen+1)))//³¤¶ÈºÏ·¨
				{
					i += 2;
					for(j=0;j<tmp16-5;j++)//È¥µôCS ºÍ16
					{
						cs += pSrcBuf[i+j];//
					}
					if(0x16 == pSrcBuf[i+j+1])//16ºÏ·¨
					{
						if(cs == pSrcBuf[i+j])//CSºÏ·¨
						{
								//¿ØÖÆÓò					
							DstDecodeDataFrame.s_head.u_con.s_conByte = pSrcBuf[i++];	
							
							for(INT8U m=0; m<5; m++)
							{
								DstDecodeDataFrame.s_head.u_msg.s_msgbuf[m] = pSrcBuf[i++];
							}						
					    DstDecodeDataFrame.s_head.s_Msg_Seq = pSrcBuf[i++];	
							
						  if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_Msg_ComFlag) //²»ÊÇ²É¼¯Æ÷Ä£¿é²ÅÓÐµØÖ·
							{
								//temp=DstDecodeDataFrame.s_MsgBuf[0]>>4;//ÖÐ¼Ì¼¶±ð
								temp = 0;//120525yhychange ÉÏÐÐ±¨ÎÄÊ±ÖÐ¼Ì¼¶±ð²»ÅÐ¶Ï
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
							else
							{
								if((pSrcBuf[i] == 0xF1)&&(pSrcBuf[i+1] == 0x01)&&(pSrcBuf[i+2] == 0x00))//AFN
								{
								INT16U SlaveNodeNum = pSrcBuf[i+4];//AFN:1,FN:2,Pct:1
									for(j=0;j<6;j++)
									DstDecodeDataFrame.s_head.s_DestAddBuf[j] = pSrcBuf[i+4+SlaveNodeNum*6+4+j];//AFN:1,FN:2,Pct:1,SlaveNodeNum:1,L:2,68:1	
								}									
							}
								
							
							if(i+5<=vSrcLen)//ÓÐAFN£¬ºÍFN,CSºÍ16
							{
								 DstDecodeDataFrame.s_head.s_AFN = pSrcBuf[i++];      //Ó¦ÓÃ¹¦ÄÜÂë
								 DstDecodeDataFrame.s_head.s_FN = pSrcBuf[i+1];
								 DstDecodeDataFrame.s_head.s_FN <<= 8;
								 DstDecodeDataFrame.s_head.s_FN |= pSrcBuf[i];             //Êý¾Ýµ¥Ôª±êÊ¶
								 i += 2;
								 DstDecodeDataFrame.s_RcvDataLen = vSrcLen-i-2;
								 for(INT16U mm = 0; mm<DstDecodeDataFrame.s_RcvDataLen; mm++)
								 {
									 DstDecodeDataFrame.s_RcvDataBuf[mm] = pSrcBuf[i++];//i改成i++
								 }
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
 
INT8U CGW13762::Check_376_2_Full(TH_IN const INT8U *pSrcBuf, TH_IN INT16U vSrcLen, TH_OUT INT16U &vDstLen)
{
	INT16U tmp16;
  INT16U i=0;
	vDstLen=vSrcLen;
		   if(vSrcLen >= 13)//×îÉÙ³¤¶ÈÊÇ13¸ö³¤¶È
			{				
				for(i=0; i<vSrcLen; i++)
		    {
					if(pSrcBuf[i] == 0x68)   //ÕÒµ½Ö¡Í·
					break;
			  }
				if(i+13 <= vSrcLen)
				{ 
					tmp16 = pSrcBuf[i+2];//³¤¶È
					tmp16 <<= 8;
					tmp16 |= pSrcBuf[i+1];          //ÓÃ»§Êý¾Ýµ¥Ôª³£¶ÈºÍ6¸ö×Ö½ÚµÄ¹Ì¶¨³¤¶È(ÆðÊ¼×Ö·û¡¢³¤¶È¡¢¿ØÖÆÓò¡¢Ð£ÑéºÍ¡¢½áÊø×Ö·û)  
					if((tmp16>6)&&((tmp16+i) <= (vSrcLen)))//³¤¶ÈºÏ·¨
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

sPartQGDW376_2_Head CGW13762::Creat376_2UpFrameFormDownFrame(TH_IN const sPartQGDW376_2_Head  downframe)
{
	sPartQGDW376_2_Head  tmpfame;
	tmpfame.u_con.s_conBit.s_Con_ComMode = DV376_2CON_COM_MODE;
	tmpfame.u_con.s_conBit.s_Con_DIR = DV376_2CON_DIR_COMMD;
	tmpfame.u_con.s_conBit.s_Con_PRM = DV376_2CON_PRM_SLAVE;
	tmpfame.u_msg.s_UpMsgBit.s_AckCsq = 0;//Ó¦´ðÐÅºÅÆ·ÖÊ
	tmpfame.u_msg.s_UpMsgBit.s_chanle_num = 0;
	tmpfame.u_msg.s_UpMsgBit.s_CmdCsq = 0;//ÃüÁîÐÅºÅÆ·ÖÊ
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
	
sPartQGDW376_2_Head CGW13762::  Init376_2HostFrameNode( TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn, TH_IN INT16U vSrcFn)
{
	return Init376_2DownFrame(pSrcAddBuf,vSrcAfn,vSrcFn,1);

}

sPartQGDW376_2_Head CGW13762::Init376_2HostFrameNoNode( TH_IN INT8U vSrcAfn, TH_IN INT16U vSrcFn)
{
	 INT8U tmpbuf[8];
	return Init376_2DownFrame(tmpbuf,vSrcAfn,vSrcFn,0);
}
sPartQGDW376_2_Head CGW13762::Init376_2UpFrame(TH_IN const INT8U *pSrcAddBuf, TH_IN INT8U vSrcAfn, TH_IN INT16U vSrcFn,INT8U type)
{	
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	sPartQGDW376_2_Head  tmpfame;
	
	tmpfame.u_con.s_conBit.s_Con_ComMode = DV376_2CON_COM_MODE;
	tmpfame.u_con.s_conBit.s_Con_DIR = DV376_2CON_DIR_COMMD;
	tmpfame.u_con.s_conBit.s_Con_PRM = DV376_2CON_PRM_MASTER;	
	
	tmpfame.u_msg.s_UpMsgBit.s_Msg_RouterFlag = 1;		
	tmpfame.u_msg.s_UpMsgBit.s_reserved_1	= 0;
	tmpfame.u_msg.s_UpMsgBit.s_Msg_ComFlag = type;
	tmpfame.u_msg.s_UpMsgBit.s_reserved_2	= 0;	

	tmpfame.u_msg.s_UpMsgBit.s_chanle_num = 0;
	tmpfame.u_msg.s_UpMsgBit.s_reserved_3	= 0;

	tmpfame.u_msg.s_UpMsgBit.s_Msg_phase = 0;	
	tmpfame.u_msg.s_UpMsgBit.s_Meter_flag = 0;	
	
	tmpfame.u_msg.s_UpMsgBit.s_CmdCsq = 0;	
	tmpfame.u_msg.s_UpMsgBit.s_AckCsq = 0;	
	
	tmpfame.u_msg.s_UpMsgBit.s_Msg_Event = DV376_2MSG_EVENT_OFF;
	tmpfame.u_msg.s_UpMsgBit.s_reserved_4	= 0;
	
	tmpfame.s_Msg_Seq= pMain->m_376seq;
	pMain->m_376seq++;
	
	for(INT8U m =0;m<6;m++)
	{
		tmpfame.s_MainAddBuf[m]=m_376Mainadd[m];
	}
	
	for(INT8U m = 0; m<DMACADD_LEN; m++)
	{
		tmpfame.s_DestAddBuf[m] = pSrcAddBuf[m];
	}
	
	tmpfame.s_AFN = vSrcAfn;
	tmpfame.s_FN = vSrcFn;
	return tmpfame;
}
sPartQGDW376_2_Head CGW13762::Init376_2DownFrame(TH_IN const INT8U *pSrcAddBuf, TH_IN INT8U vSrcAfn, TH_IN INT16U vSrcFn, INT8U type)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	sPartQGDW376_2_Head  tmpfame;

	tmpfame.u_con.s_conBit.s_Con_ComMode = DV376_2CON_COM_MODE;
	tmpfame.u_con.s_conBit.s_Con_DIR = 0;
	tmpfame.u_con.s_conBit.s_Con_PRM = DV376_2CON_PRM_MASTER;

	tmpfame.u_msg.s_UpMsgBit.s_Msg_RouterFlag = 0;
	tmpfame.u_msg.s_UpMsgBit.s_reserved_1 = 0;
	tmpfame.u_msg.s_UpMsgBit.s_Msg_ComFlag = type;
	tmpfame.u_msg.s_UpMsgBit.s_reserved_2 = 0;

	tmpfame.u_msg.s_UpMsgBit.s_chanle_num = 0;
	tmpfame.u_msg.s_UpMsgBit.s_reserved_3 = 0;

	tmpfame.u_msg.s_UpMsgBit.s_Msg_phase = 0;
	tmpfame.u_msg.s_UpMsgBit.s_Meter_flag = 0;

	tmpfame.u_msg.s_UpMsgBit.s_CmdCsq = 0;
	tmpfame.u_msg.s_UpMsgBit.s_AckCsq = 0;

	tmpfame.u_msg.s_UpMsgBit.s_Msg_Event = DV376_2MSG_EVENT_OFF;
	tmpfame.u_msg.s_UpMsgBit.s_reserved_4 = 0;

	tmpfame.s_Msg_Seq = pMain->m_376seq;
	pMain->m_376seq++;

	for (INT8U m = 0; m<6; m++)
	{
		tmpfame.s_MainAddBuf[m] = m_376Mainadd[m];
	}

	for (INT8U m = 0; m<DMACADD_LEN; m++)
	{
		tmpfame.s_DestAddBuf[m] = pSrcAddBuf[m];
	}

	tmpfame.s_AFN = vSrcAfn;
	tmpfame.s_FN = vSrcFn;
	return tmpfame;
}
INT8U  CGW13762::  Code376_2_F0F008Data(TH_IN INT8U vSrcCn,TH_IN INT8U * vSrcMsgAddr,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn, TH_IN INT8U *pSrcSendBuf,TH_IN INT16U vSrcSendLen,TH_OUT  sPartQGDW376_2CreatFrame &sQGDW376_2UpFrame)
{
	INT8U ack , n = 0;
	sQGDW376_2UpFrame.s_head.u_con.s_conByte = vSrcCn;
	for(n = 0 ; n < 5 ; n++)
	{
		sQGDW376_2UpFrame.s_head.u_msg.s_msgbuf[n] = vSrcMsgAddr[n];
	}
	sQGDW376_2UpFrame.s_head.s_Msg_Seq = vSrcMsgAddr[5];
	if ((vSrcMsgAddr[0]>>2)&0x01)
	{
		for(n = 0 ; n < 6 ; n++)
		{
			sQGDW376_2UpFrame.s_head.s_MainAddBuf[n] = vSrcMsgAddr[6 + n];
		}
		for(n = 0 ; n < 6 ; n++)
		{
			sQGDW376_2UpFrame.s_head.s_DestAddBuf[n] = vSrcMsgAddr[12 + n];
		}
	}
	
	sQGDW376_2UpFrame.s_head.s_FN = vSrcFn;
	sQGDW376_2UpFrame.s_head.s_AFN = vSrcAfn;
	
#if RXTX_BUF_SET_ARRAY
	memcpy((INT8U *)sQGDW376_2UpFrame.s_RcvDataBuf, pSrcSendBuf, vSrcSendLen);
#else
	sQGDW376_2UpFrame.s_RcvDataBuf = pSrcRcvBuf;
#endif


	sQGDW376_2UpFrame.s_RcvDataLen= vSrcSendLen;
	ack = Code376_2_Frame(sQGDW376_2UpFrame);
	return ack;
}
INT8U  CGW13762::  Code376_2_HostFrame(TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,TH_OUT  sPartQGDW376_2CreatFrame &sQGDW376_2UpFrame)
{
	INT8U ack;

	sQGDW376_2UpFrame.s_head = Init376_2HostFrameNoNode(vSrcAfn,vSrcFn);
#if RXTX_BUF_SET_ARRAY
	memset((INT8U *)sQGDW376_2UpFrame.s_RcvDataBuf,0,D3762_MAX_FRAME_LEN);
#else
	sQGDW376_2UpFrame.s_RcvDataBuf = DBUFNULL;
#endif
	sQGDW376_2UpFrame.s_RcvDataLen= 0;
	ack = Code376_2_Frame(sQGDW376_2UpFrame);
	return ack;
}
INT8U  CGW13762::  Code376_2_HostNodeFrame(TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,TH_OUT  sPartQGDW376_2CreatFrame &sQGDW376_2UpFrame)
{
	INT8U ack;

	sQGDW376_2UpFrame.s_head = Init376_2UpFrame(pSrcAddBuf,vSrcAfn,vSrcFn,0);
#if RXTX_BUF_SET_ARRAY
	memset((INT8U *)sQGDW376_2UpFrame.s_RcvDataBuf, 0, D3762_MAX_FRAME_LEN);
#else
	sQGDW376_2UpFrame.s_RcvDataBuf = DBUFNULL;
#endif
	ack = Code376_2_Frame(sQGDW376_2UpFrame);
	return ack;
}
INT8U  CGW13762::Code376_2_HostBufFrame(TH_IN INT8U vSrcAfn, TH_IN INT16U vSrcFn, INT8U *pSrcRcvBuf, INT16U vSrcRcvLen, TH_OUT  sPartQGDW376_2CreatFrame &sQGDW376_2UpFrame)
{
	INT8U ack;

	sQGDW376_2UpFrame.s_head = Init376_2HostFrameNoNode(vSrcAfn,vSrcFn);

#if RXTX_BUF_SET_ARRAY
	memcpy(sQGDW376_2UpFrame.s_RcvDataBuf, pSrcRcvBuf, vSrcRcvLen);
#else
	sQGDW376_2UpFrame.s_RcvDataBuf = pSrcRcvBuf;
#endif
	sQGDW376_2UpFrame.s_RcvDataLen= vSrcRcvLen;
	ack = Code376_2_Frame(sQGDW376_2UpFrame);
	return ack;
}
INT8U  CGW13762::Code376_2_HostBufNodeFrame(TH_IN const INT8U *pSrcAddBuf, TH_IN INT8U vSrcAfn, TH_IN INT16U vSrcFn, INT8U *pSrcRcvBuf, INT16U vSrcRcvLen, TH_OUT  sPartQGDW376_2CreatFrame &sQGDW376_2UpFrame)
{
	INT8U ack;

	sQGDW376_2UpFrame.s_head = Init376_2UpFrame(pSrcAddBuf,vSrcAfn,vSrcFn,1);

#if RXTX_BUF_SET_ARRAY
	memcpy((INT8U *)sQGDW376_2UpFrame.s_RcvDataBuf, pSrcRcvBuf, vSrcRcvLen);
#else
	sQGDW376_2UpFrame.s_RcvDataBuf = pSrcRcvBuf;
#endif
	
	sQGDW376_2UpFrame.s_RcvDataLen= vSrcRcvLen;
	ack = Code376_2_Frame(sQGDW376_2UpFrame);
	return ack;
}
INT8U CGW13762::DeDecode376_2(const INT8U *pSrcBuf,INT16U vSrcLen,INT16U vDstBufLen,struct PartQGDW376_2 &DstDecodeDataFrame)
	{
	INT8U  cs=0;
	INT8U  SEQ=0;
	INT16U i=0;
	INT16U j;
	INT8U  temp;
	INT8U  ack=ACKNULL;     //ACKNULL需定义
	INT16U tmp16;
	INT8U con;
	DstDecodeDataFrame.s_DataLen=0;
	if(vSrcLen<=Max376_2ReadLen)   //Max376ReadLen需定义
	{
		if(vSrcLen>=13)//最少长度是13个长度
		{
			i=0;
			//把前导的不完整的帧都过去
			for(i=0;i<vSrcLen;i++)
			{
				if(pSrcBuf[i]!=0x68)   //找到帧头
				{
					continue;
				}
				if(i+13<=vSrcLen)
				{ 
					tmp16=pSrcBuf[i+2];//长度
					tmp16<<=8;
					tmp16|=pSrcBuf[i+1];          //用户数据单元常度和6个字节的固定长度(起始字符、长度、控制域、校验和、结束字符)  
					if((tmp16>6)&&((tmp16+i)<=(vSrcLen)))//长度合法
					{
						if(pSrcBuf[tmp16+i-1]==0x16)
							break;

					}

				}
			}
			if((i+13)<=vSrcLen)
			{ 
				i++;//过68
				tmp16=pSrcBuf[i+1];//长度
				tmp16<<=8;
				tmp16|=pSrcBuf[i];          //用户数据单元常度和6个字节的固定长度(起始字符、长度、控制域、校验和、结束字符)  
				if((tmp16>6)&&((tmp16+i)<=(vSrcLen+1)))//长度合法
				{

					i+=2;
					for(j=0;j<tmp16-5;j++)//去掉CS 和16
					{
						cs+=pSrcBuf[i+j];//
					}
					if((cs==pSrcBuf[i+j])&&(0x16==pSrcBuf[i+j+1]))//CS和16合法
					{
						ack=ACKERR;
						con=pSrcBuf[i];  //控制域
						DstDecodeDataFrame.s_Con = con;
						i++;//       
						for(j=0;j<6;j++)
						{
							DstDecodeDataFrame.s_MsgBuf[j]=pSrcBuf[i++];  //信息域
						}    
						SEQ=DstDecodeDataFrame.s_MsgBuf[5];
						if(DstDecodeDataFrame.s_MsgBuf[0]&Bit2) //不是采集器模块才有地址
						{
							//temp=DstDecodeDataFrame.s_MsgBuf[0]>>4;//中继级别
							temp=0;//120525yhychange 上行报文时中继级别不判断
							if((i+(temp+2)*6)<=vSrcLen)
							{
								for(j=0;j<6;j++)
									DstDecodeDataFrame.s_MainAddBuf[j]=pSrcBuf[i+j];
								i+=6;
								if(temp<=DZB_MAXZJ_CNT)
								{
									for(j=0;j<(temp*6);j++)
										DstDecodeDataFrame.s_RelayAddBuf[j]=pSrcBuf[i+j];
								}
								else
								{
									for(j=0;j<(DZB_MAXZJ_CNT+2)*6;j++)
										DstDecodeDataFrame.s_RelayAddBuf[j]=pSrcBuf[i+j];
								}
								i+=temp*6;
								for(j=0;j<6;j++)
									DstDecodeDataFrame.s_DestAddBuf[j]=pSrcBuf[i+j];
								i+=6;
							}
							else 
								return ack;
						}
						if(i+5<=vSrcLen)//有AFN，和FN,CS和16
						{
							DstDecodeDataFrame.s_AFN=pSrcBuf[i++];      //应用功能码
							DstDecodeDataFrame.s_FN=pSrcBuf[i+1];
							DstDecodeDataFrame.s_FN<<=8;
							DstDecodeDataFrame.s_FN|=pSrcBuf[i];             //数据单元标识
							i+=2;
							DstDecodeDataFrame.s_DataLen=vSrcLen-i-2;//计算出原始数据的长度
							if(vDstBufLen>=DstDecodeDataFrame.s_DataLen)//如果原始数据区的大小能容纳相应数据长度的数据，则复制数据到13762的结构体数据缓存区
							{//原始数据区的大小
								for(j=0;j<DstDecodeDataFrame.s_DataLen;j++)
								{
									DstDecodeDataFrame.s_DataBuf[j]=pSrcBuf[i+j];
								}
								ack=ACKTRUE; 
							}
							else//否则认为是错误
								DstDecodeDataFrame.s_DataLen=0;
						}
					} 
				}
			}

		}
	}
	if(ack!=ACKTRUE)
	{
		DstDecodeDataFrame.s_DataLen=0;
		DstDecodeDataFrame.s_AFN=0;
		DstDecodeDataFrame.s_FN=0;	
	}
	return ack;
}

INT8U CGW13762::Code376_2_Type(struct PartQGDW376_2 SrcCodeDataFrame,INT16U vSrcDstBufLen,INT8U *pDstBuf,INT16U &vDstLen)
{
INT8U  cs=0;
INT8U  SEQ=0;
INT16U i=0;
INT16U j;
INT8U  D1,D2;
INT16U tmp16;
INT8U  *ptempbuf=pDstBuf; 
INT8U relaycnt;
INT8U ack=TRUE;
tmp16=6+6+3+(SrcCodeDataFrame.s_DataLen);//固定6+信息6+AFN1+Fn+数据长度；
relaycnt=SrcCodeDataFrame.s_MsgBuf[0]>>4;
if(relaycnt>DZB_MAXZJ_CNT)
	relaycnt=DZB_MAXZJ_CNT;
if(SrcCodeDataFrame.s_MsgBuf[0]&Bit2)//如果通讯模块标识为0，有地址域
{
	tmp16+=(relaycnt+2)*6;
}
if(tmp16<=vSrcDstBufLen)
{
	i=0;
	D1=(INT8U)tmp16;                   
	D2=(INT8U)(tmp16>>8);
	ptempbuf[i++]=0x68;      //起始字符
	ptempbuf[i++]=D1;        //长度
	ptempbuf[i++]=D2;
	D1 = SrcCodeDataFrame.s_Con;
	cs+=D1;
	ptempbuf[i++]=D1;      //控制域 东软一定要 41

	for(j=0;j<6;j++) //信息域,要判断中继级数
	{
		D1=SrcCodeDataFrame.s_MsgBuf[j];
		if(j==0)
		{
			D1&=0x0f;
			D1|=relaycnt<<4;
		}
		cs+=D1;
		ptempbuf[i++]=D1;      
	}
	SEQ=ptempbuf[5];
	if(SrcCodeDataFrame.s_MsgBuf[0]&Bit2)//不是采集器模块才有地址
	{
		for(j=0;j<6;j++)       //地址域    
		{
			cs+=SrcCodeDataFrame.s_MainAddBuf[j];
			ptempbuf[i++]=SrcCodeDataFrame.s_MainAddBuf[j];
		}
		for(j=0;j<(relaycnt*6);j++)       //地址域    
		{
			cs+=SrcCodeDataFrame.s_RelayAddBuf[j];
			ptempbuf[i++]=SrcCodeDataFrame.s_RelayAddBuf[j];
		}
		for(j=0;j<6;j++)       //地址域    
		{
			cs+=SrcCodeDataFrame.s_DestAddBuf[j];
			ptempbuf[i++]=SrcCodeDataFrame.s_DestAddBuf[j];
		}
	}
	cs+=SrcCodeDataFrame.s_AFN;      
	ptempbuf[i++]=SrcCodeDataFrame.s_AFN;     //应用功能码
	D1=(INT8)SrcCodeDataFrame.s_FN;
	cs+=D1;
	ptempbuf[i++]=D1;              //数据单元标识
	D2=SrcCodeDataFrame.s_FN>>8;
	cs+=D2;
	ptempbuf[i++]=D2;
	for(j=0;j<SrcCodeDataFrame.s_DataLen;j++)     //数据单元
	{
		cs+=SrcCodeDataFrame.s_DataBuf[j];
		ptempbuf[i++]=SrcCodeDataFrame.s_DataBuf[j];
	}
	ptempbuf[i++]=cs;          //帧校验和
	ptempbuf[i++]=0x16;        //结束符
	vDstLen=i;                 //一帧的长度
	return TRUE;
}
return FALSE;
}

INT8U  CGW13762::Code376_2_SlaveFrame(TH_IN INT8U vSrcAfn, TH_IN INT16U vSrcFn, TH_IN const sPartQGDW376_2_Head  downframe, TH_OUT  sPartQGDW376_2CreatFrame &sQGDW376_2UpFrame)
{
	INT8U ack;
	sQGDW376_2UpFrame.s_head = Creat376_2UpFrameFormDownFrame(downframe);

#if RXTX_BUF_SET_ARRAY
	memset((INT8U *)sQGDW376_2UpFrame.s_RcvDataBuf, 0, D3762_MAX_FRAME_LEN);
#else
	sQGDW376_2UpFrame.s_RcvDataBuf = DBUFNULL;
#endif
	
	sQGDW376_2UpFrame.s_RcvDataLen= 0;
	sQGDW376_2UpFrame.s_head.s_AFN = vSrcAfn;
	sQGDW376_2UpFrame.s_head.s_FN = vSrcFn;
	ack = Code376_2_Frame(sQGDW376_2UpFrame);
	return ack;
}
INT8U  CGW13762::Code376_2_SlaveNodeFrame(TH_IN INT8U vSrcAfn, TH_IN INT16U vSrcFn, TH_IN const sPartQGDW376_2_Head  downframe, TH_OUT  sPartQGDW376_2CreatFrame &sQGDW376_2UpFrame)
{
	INT8U ack;

	sQGDW376_2UpFrame.s_head = Creat376_2UpFrameFormDownFrame(downframe);

#if RXTX_BUF_SET_ARRAY
	memset((INT8U *)sQGDW376_2UpFrame.s_RcvDataBuf, 0, D3762_MAX_FRAME_LEN);
#else
	sQGDW376_2UpFrame.s_RcvDataBuf = DBUFNULL;
#endif

	
	sQGDW376_2UpFrame.s_RcvDataLen= 0;
	sQGDW376_2UpFrame.s_head.s_AFN = vSrcAfn;
	sQGDW376_2UpFrame.s_head.s_FN = vSrcFn;
	ack = Code376_2_Frame(sQGDW376_2UpFrame);
	return ack;
}
INT8U  CGW13762::Code376_2_SlaveBufFrame(TH_IN INT8U vSrcAfn, TH_IN INT16U vSrcFn, INT8U *pSrcRcvBuf, INT16U vSrcRcvLen, TH_IN const sPartQGDW376_2_Head  downframe, TH_OUT  sPartQGDW376_2CreatFrame &sQGDW376_2UpFrame)
{
	INT8U ack;

	sQGDW376_2UpFrame.s_head = Creat376_2UpFrameFormDownFrame(downframe);

#if RXTX_BUF_SET_ARRAY
	memcpy((INT8U *)sQGDW376_2UpFrame.s_RcvDataBuf, pSrcRcvBuf, vSrcRcvLen);
#else
	sQGDW376_2UpFrame.s_RcvDataBuf = pSrcRcvBuf;
#endif


	
	sQGDW376_2UpFrame.s_RcvDataLen= vSrcRcvLen;
	sQGDW376_2UpFrame.s_head.s_AFN = vSrcAfn;
	sQGDW376_2UpFrame.s_head.s_FN = vSrcFn;
	ack = Code376_2_Frame(sQGDW376_2UpFrame);
	return ack;
}
INT8U  CGW13762::Code376_2_SlaveBufNodeFrame(TH_IN INT8U vSrcAfn, TH_IN INT16U vSrcFn, INT8U *pSrcRcvBuf, INT16U vSrcRcvLen, TH_IN const sPartQGDW376_2_Head  downframe, TH_OUT  sPartQGDW376_2CreatFrame &sQGDW376_2UpFrame)
{
	INT8U ack;

	sQGDW376_2UpFrame.s_head = Creat376_2UpFrameFormDownFrame(downframe);
#if RXTX_BUF_SET_ARRAY
	memcpy((INT8U *)sQGDW376_2UpFrame.s_RcvDataBuf, pSrcRcvBuf, vSrcRcvLen);
#else
	sQGDW376_2UpFrame.s_RcvDataBuf = pSrcRcvBuf;
#endif
	sQGDW376_2UpFrame.s_RcvDataLen= vSrcRcvLen;
	sQGDW376_2UpFrame.s_head.s_AFN = vSrcAfn;
	sQGDW376_2UpFrame.s_head.s_FN = vSrcFn;
	ack = Code376_2_Frame(sQGDW376_2UpFrame);
	return ack;
}

