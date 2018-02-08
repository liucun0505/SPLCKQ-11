#include "StdAfx.h"
#include "User_gDefine.h"
#include "CSG13762.h"
#include "MainFrm.h"
CCSG13762::CCSG13762(void)
{
	 m_376seq = 0;
	/* for(INT8U m = 0;m<6;m++)
	 {
		 m_376Mainadd[m]=m_HostNodeAddress[m];
	 }*/
}
CCSG13762::~CCSG13762(void)
{
}

void CCSG13762::SetMainAdd(INT8U *vSrcBuf)
{
    for(INT8U m = 0;m<6;m++)
	 {
		 m_376Mainadd[m]=vSrcBuf[m];
	 }
}
void CCSG13762::QueMainAdd(INT8U *vDstBuf)
{
	 for(INT8U m = 0;m<6;m++)
	 {
		 vDstBuf[m]=m_376Mainadd[m];
	 }
}
INT8U CCSG13762::GetADDFlag(TH_IN INT32U vSrcFn)
{
	if(FN_02_F1 == vSrcFn 
		|| FN_05_F1 == vSrcFn 
		|| FN_05_F2 == vSrcFn
		|| FN_F0_F153 == vSrcFn
		)
	{
		return 1;
	}
	return 0;
}
INT8U CCSG13762::Creat376_2Cs(TH_IN const INT8U *vSrcBuf,TH_IN const INT16U vSrcLen)
{
	INT8U cs = 0;
	
	for(INT16U m = 0; m<vSrcLen; m++)
	{
		cs += vSrcBuf[m];
	}
	return cs;
}
 
INT8U CCSG13762::Code376_2_Frame(TH_INOUT sPartQCSG376_2CreatFrame &SrcCodeDataFrame)
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
		//简单检查长度
		tmp16 = 6 + 6 + SrcCodeDataFrame.s_RcvDataLen;//�̶�(6)(68+len+len+con+cs+16)+AFN(1)+SEQ(1)+Fn(4)
		
		if(SrcCodeDataFrame.s_head.u_con.s_conBit.s_Con_ADD)//判断是否有地址域
		{
			tmp16 += DMACADD_LEN + DMACADD_LEN;
		}
	 
		if(tmp16 <= D376_MAXSENDBUFLEN)
		{
			INT8U *ptempbuf = SrcCodeDataFrame.s_SendDataBuf;
			
			i=0;
			ptempbuf[i++] = 0x68;      //起始字符
			ptempbuf[i++] = (INT8U)tmp16;       //长度
			ptempbuf[i++] = tmp16>>8;		 
			ptempbuf[i++] = SrcCodeDataFrame.s_head.u_con.s_conByte;         //con

			//��ַ����
			if(SrcCodeDataFrame.s_head.u_con.s_conBit.s_Con_ADD)   //地址域标志
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
			
			 //���
			ptempbuf[i++] = SrcCodeDataFrame.s_head.s_Msg_Seq;
			 
			ptempbuf[i++] = (INT8U)SrcCodeDataFrame.s_head.s_FN;              //数据单元标识
			ptempbuf[i++] = SrcCodeDataFrame.s_head.s_FN >> 8;
			ptempbuf[i++] = SrcCodeDataFrame.s_head.s_FN >> 16;
			ptempbuf[i++] = SrcCodeDataFrame.s_head.s_FN >> 24;
			
			
			for(j=0; j<SrcCodeDataFrame.s_RcvDataLen; j++)     //数据单元
			{
				ptempbuf[i++] = SrcCodeDataFrame.s_RcvDataBuf[j];
			}
			
			cs = Creat376_2Cs(&ptempbuf[3],i-3);//帧校验和
			ptempbuf[i++] = cs;         
			ptempbuf[i++] = 0x16;       //结束符

			SrcCodeDataFrame.s_SendDataLen = i;                 //一帧的长度
			m_376seq++;
			ack = DACK_SUCESS;
		}
		else
		{
			ack = DACK_ERR_BUF;
		}
	}
	return ack;
}

INT8U CCSG13762::Decode376_2Frame(TH_IN  INT8U *pSrcBuf,TH_IN  INT16U vSrcLen,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U  cs = 0;
	INT16U i = 0;
	INT16U j;
	INT8U  temp;
	INT8U  ack = DACK_ERR_NULL;    //ACKNULL需定义
	INT16U tmp16;
	
	if(vSrcLen >= D376_2_MIN_FRAME_LEN)//最少长度是12个长度���
	{
		i=0;
				//把前导的不完整的帧都过去
		for(i=0; i<vSrcLen; i++)
		{
			if(pSrcBuf[i] != 0x68)  //找到帧头
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

								//i += temp*6;//5月25对比陈工代码去掉的 没验证
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
							 DstDecodeDataFrame.s_head.s_FN |= pSrcBuf[i];            //数据单元标识
							 i += 4;
							 DstDecodeDataFrame.s_RcvDataLen = vSrcLen-i-2;
							 for(INT16U mm = 0; mm<DstDecodeDataFrame.s_RcvDataLen; mm++)
							 {
								 DstDecodeDataFrame.s_RcvDataBuf[mm] = pSrcBuf[i++];//i改成i++
							 }							 
//							 DstDecodeDataFrame.s_RcvDataBuf = &pSrcBuf[i];
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
 
INT8U CCSG13762::Check_376_2_Full(TH_IN const INT8U *pSrcBuf, TH_IN INT16U vSrcLen, TH_OUT INT16U &vDstLen)
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
			tmp16 |= pSrcBuf[i+1];         //用户数据单元常度和6个字节的固定长度(起始字符、长度、控制域、校验和、结束字符)  
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

sPartQCSG376_2_Head CCSG13762::Creat376_2UpFrameFormDownFrame(TH_IN const sPartQCSG376_2_Head  downframe)
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
	
sPartQCSG376_2_Head CCSG13762::Init376_2HostFrameNode( TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn, TH_IN INT32U vSrcFn)
{
	return Init376_2UpFrame(pSrcAddBuf,vSrcAfn,vSrcFn,1);

}

sPartQCSG376_2_Head CCSG13762::Init376_2HostFrameNoNode( TH_IN INT8U vSrcAfn, TH_IN INT32U vSrcFn)
{
	 INT8U tmpbuf[8];
	return Init376_2UpFrame(tmpbuf,vSrcAfn,vSrcFn,0);
}
sPartQCSG376_2_Head CCSG13762::Init376_2UpFrame(TH_IN const INT8U *pSrcAddBuf, TH_IN INT8U vSrcAfn, TH_IN INT32U vSrcFn, TH_IN  INT8U AddFg)
{	
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	sPartQCSG376_2_Head  tmpfame;

	tmpfame.u_con.s_conBit.s_Con_reserved = 0;
	tmpfame.u_con.s_conBit.s_Con_VER = 0;
	tmpfame.u_con.s_conBit.s_Con_ADD = AddFg;
	tmpfame.u_con.s_conBit.s_Con_DIR = DBIT_376_2Con_DIR;
	tmpfame.u_con.s_conBit.s_Con_PRM = DV376_2CON_PRM_MASTER;

	for(INT8U m =0;m<6;m++)
	{
		tmpfame.s_MainAddBuf[m]=m_376Mainadd[m];
	}
	
	for(INT8U m = 0; m<DMACADD_LEN; m++)
	{
		tmpfame.s_DestAddBuf[m] = pSrcAddBuf[m];
	}
	
	tmpfame.s_AFN = vSrcAfn;

	m_376seq++;
	tmpfame.s_Msg_Seq=m_376seq;
	
	tmpfame.s_FN = vSrcFn;
	return tmpfame;
}
INT8U  CCSG13762::Code376_2_F0F008Data(TH_IN INT8U vSrcCn,TH_IN INT8U * vSrcMsgAddr,TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn, TH_IN INT8U *pSrcSendBuf,TH_IN INT16U vSrcSendLen,TH_OUT  sPartQCSG376_2CreatFrame &sQCSG376_2UpFrame)
{//??????
	INT8U ack , n = 0;
	sQCSG376_2UpFrame.s_head.u_con.s_conByte = vSrcCn;

	sQCSG376_2UpFrame.s_head.s_Msg_Seq = m_376seq;
	if (sQCSG376_2UpFrame.s_head.u_con.s_conByte&Bit5)
	{
		for(n = 0 ; n < 6 ; n++)
		{
			sQCSG376_2UpFrame.s_head.s_MainAddBuf[n] = vSrcMsgAddr[n];
		}
		for(n = 0 ; n < 6 ; n++)
		{
			sQCSG376_2UpFrame.s_head.s_DestAddBuf[n] = vSrcMsgAddr[6 + n];
		}
	}
	
	sQCSG376_2UpFrame.s_head.s_FN = vSrcFn;
	sQCSG376_2UpFrame.s_head.s_AFN = vSrcAfn;

#if RXTX_BUF_SET_ARRAY
	memcpy((INT8U *)sQCSG376_2UpFrame.s_RcvDataBuf, pSrcSendBuf, vSrcSendLen);
#else
	sQCSG376_2UpFrame.s_RcvDataBuf = pSrcRcvBuf;
#endif
	

	sQCSG376_2UpFrame.s_RcvDataLen= vSrcSendLen;
	ack = Code376_2_Frame(sQCSG376_2UpFrame);
	return ack;
}
INT8U  CCSG13762::  Code376_2_HostFrame(TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,TH_OUT  sPartQCSG376_2CreatFrame &sQCSG376_2UpFrame)
{
	INT8U ack;

	sQCSG376_2UpFrame.s_head = Init376_2HostFrameNoNode(vSrcAfn,vSrcFn);
#if RXTX_BUF_SET_ARRAY
	memset((INT8U *)sQCSG376_2UpFrame.s_RcvDataBuf, 0, D3762_MAX_FRAME_LEN);
#else
	sQCSG376_2UpFrame.s_RcvDataBuf = DBUFNULL;
#endif
	sQCSG376_2UpFrame.s_RcvDataLen= 0;
	ack = Code376_2_Frame(sQCSG376_2UpFrame);
	return ack;
}
INT8U  CCSG13762::  Code376_2_HostNodeFrame(TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,TH_OUT  sPartQCSG376_2CreatFrame &sQCSG376_2UpFrame)
{
	INT8U ack;

	sQCSG376_2UpFrame.s_head = Init376_2UpFrame(pSrcAddBuf,vSrcAfn,vSrcFn,0);
#if RXTX_BUF_SET_ARRAY
	memset((INT8U *)sQCSG376_2UpFrame.s_RcvDataBuf, 0, D3762_MAX_FRAME_LEN);
#else
	sQCSG376_2UpFrame.s_RcvDataBuf = DBUFNULL;
#endif
	sQCSG376_2UpFrame.s_RcvDataLen= 0;
	ack = Code376_2_Frame(sQCSG376_2UpFrame);
	return ack;
}
INT8U  CCSG13762::  Code376_2_HostBufFrame(TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,INT8U *pSrcRcvBuf,INT16U vSrcRcvLen,TH_OUT  sPartQCSG376_2CreatFrame &sQCSG376_2UpFrame)
{
	INT8U ack;

	sQCSG376_2UpFrame.s_head = Init376_2HostFrameNoNode(vSrcAfn,vSrcFn);

#if RXTX_BUF_SET_ARRAY
	memcpy((INT8U *)sQCSG376_2UpFrame.s_RcvDataBuf, pSrcRcvBuf, vSrcRcvLen);
#else
	sQCSG376_2UpFrame.s_RcvDataBuf = pSrcRcvBuf;
#endif
	
	sQCSG376_2UpFrame.s_RcvDataLen= vSrcRcvLen;
	ack = Code376_2_Frame(sQCSG376_2UpFrame);
	return ack;
}
INT8U  CCSG13762::  Code376_2_HostBufNodeFrame(TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,INT8U *pSrcRcvBuf,INT16U vSrcRcvLen,TH_OUT  sPartQCSG376_2CreatFrame &sQCSG376_2UpFrame)
{
	INT8U ack;

	sQCSG376_2UpFrame.s_head = Init376_2UpFrame(pSrcAddBuf,vSrcAfn,vSrcFn,1);
#if RXTX_BUF_SET_ARRAY
	memcpy((INT8U *)sQCSG376_2UpFrame.s_RcvDataBuf, pSrcRcvBuf, vSrcRcvLen);
#else
	sQCSG376_2UpFrame.s_RcvDataBuf = pSrcRcvBuf;
#endif

	sQCSG376_2UpFrame.s_RcvDataLen= vSrcRcvLen;
	ack = Code376_2_Frame(sQCSG376_2UpFrame);
	return ack;
}
INT8U CCSG13762::DeDecode376_2(const INT8U *pSrcBuf,INT16U vSrcLen,INT16U vDstBufLen,struct PartQCSG376_2 &DstDecodeDataFrame)
	{
	INT8U  cs=0;
	INT8U  SEQ=0;
	INT16U i=0;
	INT16U j;
	INT8U  temp=0;
	INT8U  ack=ACKNULL;     //ACKNULL需定义
	INT16U tmp16;
	INT8U con;
	DstDecodeDataFrame.s_DataLen=0;
	if(vSrcLen<=Max376_2ReadLen)   //Max376ReadLen需定义
	{
		if(vSrcLen>=D376_2_MIN_FRAME_LEN)//最少长度是13个长度
		{
			i=0;
			//把前导的不完整的帧都过去
			for(i=0;i<vSrcLen;i++)
			{
				if(pSrcBuf[i]!=0x68)   //找到帧头
				{
					continue;
				}
				if(i+D376_2_MIN_FRAME_LEN<=vSrcLen)
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
			if((i+D376_2_MIN_FRAME_LEN)<=vSrcLen)
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

						if(DstDecodeDataFrame.s_Con&Bit5) //不是采集器模块才有地址
						{
							if((i+12) <= vSrcLen)
							{
								for(j=0; j<6; j++)
								{
									DstDecodeDataFrame.s_MainAddBuf[j] = pSrcBuf[i+j];
								}
								i += 6;

								i += temp*6;
								for(j=0;j<6;j++)
								{
									DstDecodeDataFrame.s_DestAddBuf[j] = pSrcBuf[i+j];
								}
								i += 6;
							}
						  	else 
								return ack;
						}
						if(i + 8 <= vSrcLen)//有AFN，SEQ, FN,CS和16
						{
							 DstDecodeDataFrame.s_AFN = pSrcBuf[i++];      //应用功能码
							 DstDecodeDataFrame.s_Msg_Seq = pSrcBuf[i++];
							 
							 DstDecodeDataFrame.s_FN = pSrcBuf[i+3];        //数据单元标识
							 DstDecodeDataFrame.s_FN <<= 8;
							 DstDecodeDataFrame.s_FN |= pSrcBuf[i+2];
							 DstDecodeDataFrame.s_FN <<= 8;
							 DstDecodeDataFrame.s_FN |= pSrcBuf[i+1];
							 DstDecodeDataFrame.s_FN <<= 8;
							 DstDecodeDataFrame.s_FN |= pSrcBuf[i];            
							 i += 4;
							 DstDecodeDataFrame.s_DataLen = vSrcLen-i-2;
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
//							 DstDecodeDataFrame.s_RcvDataBuf = &pSrcBuf[i];
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

INT8U CCSG13762::Code376_2_Type(struct PartQCSG376_2 SrcCodeDataFrame,INT16U vSrcDstBufLen,INT8U *pDstBuf,INT16U &vDstLen)
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
	tmp16 = 6 + 6 + SrcCodeDataFrame.s_DataLen;
	//tmp16=6+6+3+(SrcCodeDataFrame.s_DataLen);//固定6+信息6+AFN1+Fn+数据长度；
	
	if(SrcCodeDataFrame.s_Con&Bit5)//如果通讯模块标识为0，有地址域
	{
		tmp16 += 6;
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


		if(SrcCodeDataFrame.s_Con&Bit5)//不是采集器模块才有地址
		{
			for(j=0;j<6;j++)       //地址域    
			{
				cs+=SrcCodeDataFrame.s_MainAddBuf[j];
				ptempbuf[i++]=SrcCodeDataFrame.s_MainAddBuf[j];
			}

			for(j=0;j<6;j++)       //地址域    
			{
				cs+=SrcCodeDataFrame.s_DestAddBuf[j];
				ptempbuf[i++]=SrcCodeDataFrame.s_DestAddBuf[j];
			}
		}
		cs+=SrcCodeDataFrame.s_AFN;  
		ptempbuf[i++] = SrcCodeDataFrame.s_AFN;     //Ӧ�ù�����
			
		//���
		cs+=SrcCodeDataFrame.s_Msg_Seq;  
		ptempbuf[i++] = SrcCodeDataFrame.s_Msg_Seq;	

		//���ݵ�Ԫ��ʶ
		D1=(INT8)SrcCodeDataFrame.s_FN;
		cs+=D1;
		ptempbuf[i++]=D1;
		D1=(INT8)(SrcCodeDataFrame.s_FN >> 8);
		cs+=D1;
		ptempbuf[i++]=D1;
		D1=(INT8)(SrcCodeDataFrame.s_FN >> 16);
		cs+=D1;
		ptempbuf[i++]=D1;
		D1=(INT8)(SrcCodeDataFrame.s_FN >> 24);
		cs+=D1;
		
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

INT8U  CCSG13762::Code376_2_SlaveFrame(TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,TH_IN const sPartQCSG376_2_Head  downframe,TH_OUT  sPartQCSG376_2CreatFrame &sQGDW376_2UpFrame)
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
INT8U  CCSG13762::Code376_2_SlaveNodeFrame(TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,TH_IN const sPartQCSG376_2_Head  downframe,TH_OUT  sPartQCSG376_2CreatFrame &sQGDW376_2UpFrame)
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
INT8U  CCSG13762::Code376_2_SlaveBufFrame(TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,INT8U *pSrcRcvBuf,INT16U vSrcRcvLen,TH_IN const sPartQCSG376_2_Head  downframe,TH_OUT  sPartQCSG376_2CreatFrame &sQGDW376_2UpFrame)
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
INT8U  CCSG13762::Code376_2_SlaveBufNodeFrame(TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,INT8U *pSrcRcvBuf,INT16U vSrcRcvLen,TH_IN const sPartQCSG376_2_Head  downframe,TH_OUT  sPartQCSG376_2CreatFrame &sQGDW376_2UpFrame)
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


