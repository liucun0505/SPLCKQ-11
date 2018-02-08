// TEST_SimpleChaoB.cpp : implementation file
//

#include "stdafx.h"
#include "KD_Project.h"
#include "TEST_ReadMeterPublic.h"
#include "MainFrm.h"

#include "SimJZQ.h"
extern CSimJzq   gSimJzq;

#include "GW13762.h"
extern CGW13762 Cgw13762;

#include "SimMeter.h"
extern CSimMeter  gSimMeter;
#include "gPublicObjct.h"
#include "MyFunLib.h"
#include "LogFile.h"



extern CLogFile plog;//打引用


void CTEST_ReadMeterPublic:: StaSucessCnt(INT8U ack,INT8U &allSucesscnt,INT8U &failCnt)
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
INT8U  CTEST_ReadMeterPublic::TestSetPa(void)
{          
	 INT8U ack;
	 	INT8U allSucesscnt = 0;
	INT8U allfailcnt = 0;;
			//1.	设置CCO的主节点地址
			sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
			sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
			plog.saveLog_strAll(TIME,_T("开始：设置主节点"),1);
			ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,m_HostNodeAddress,6);
			StaSucessCnt(ack,allSucesscnt,allfailcnt);
			ack =gSimJzq.HostSendRcv376_2NoBuf(AFN03,F4,sQGDW376_2HostFrame,DstDecodeDataFrame);//读取主节点
			if (ack == DACK_SUCESS)
			{
				plog.saveLog_strAll(TIME,_T("设置主节点结果：成功"),1);
			}
			StaSucessCnt(ack,allSucesscnt,allfailcnt);
			//2.	删除CCO以前从节点。
             
			ack = gSimJzq.Router_PaRst();
			StaSucessCnt(ack,allSucesscnt,allfailcnt);
			if(ack == DACK_SUCESS)
			{
				plog.saveLog_str(DATA_FILE,NOTIME,_T("等待20秒"),0);
				Sleep(20000);//初始化成功后后延时20秒后新的从节点才能添加成功
			}
				
			//3.	添加CCO的从节点（和模拟电表地址一致）。
			plog.saveLog_strAll(TIME,_T("开始：添加CCO从节点"),1);	
			ack = gSimJzq.SetNodeAdd(0,1);
			StaSucessCnt(ack,allSucesscnt,allfailcnt);
			if(ack == DACK_SUCESS)
			{
			   ack = gSimJzq.CmpNodeAdd(0,1);
			   StaSucessCnt(ack,allSucesscnt,allfailcnt);
			}
			plog.saveLog_strAll(TIME,_T("开始：路由暂停操作"),1);	 
			ack = gSimJzq.Router_Stop();
			StaSucessCnt(ack,allSucesscnt,allfailcnt);
		
			ack = gSimJzq.QueAllNetSta(0,1,5*60);//跑这个函数出现内存错误
			StaSucessCnt(ack,allSucesscnt,allfailcnt);
	       if(allfailcnt==0)
			    ack = DACK_SUCESS;
		   else
			   ack = DACK_FAILURE;

			plog.saveLog_testresultAll(TIME,_T("参数设置结果： "),ack,1);
	
			return ack;
}
//	多次转发测试（实际表）（模拟表）
INT8U  CTEST_ReadMeterPublic::TestReadMeterCnt(INT32U vSrcCnt,INT8U vSrcAfntype,INT8U vSrcMeterType)
{
	INT8U ack;
	INT32U resucnt=0;
	INT32U failcnt=0;
	sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sAckTimeSta  ackclkSta;
	for(INT32U m=0;m<vSrcCnt;m++)
	{
		 ack = gSimJzq.ReadMeterAndCmpMterAckClk(vSrcAfntype,&gNodeAddBuf[0][0],gReMeterDi[0],sQGDW376_2HostFrame,DstDecodeDataFrame,ackclkSta,vSrcMeterType);
	
		 if(ack==DACK_SUCESS)
		 {
               resucnt++;
		 }
		 else
		 {
			 failcnt++;
		 }
	}

	if(failcnt == 0)
	{
        ack = DACK_SUCESS;
	}
	else
	{
		 ack = DACK_FAILURE;
	}
	plog.saveLog_StaCnt(resucnt,failcnt,DATA_FILE,TIME,_T("多次转发测试"),1);
	return ack;
}

//	错误DI测试（实际表）（模拟表）
INT8U  CTEST_ReadMeterPublic::TestReadMeterErrDi(INT32U vSrcCnt,INT8U vSrcAfntype)
{
	INT8U ack;
	INT32U resucnt=0;
	INT32U failcnt=0;
	sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sAckTimeSta  ackclkSta;
	for(INT32U m=0;m<vSrcCnt;m++)
	{
		 ack = gSimJzq.Read3762MeterAckClk(vSrcAfntype,&gNodeAddBuf[0][0],0x99998877,sQGDW376_2HostFrame,DstDecodeDataFrame,ackclkSta);
	
		 if(ack==DACK_SUCESS)
		 {
               resucnt++;
		 }
		 else
		 {
			 failcnt++;
		 }
	}

	if(failcnt == 0)
	{
        ack = DACK_SUCESS;
	}
	else
	{
		 ack = DACK_FAILURE;
	}
	plog.saveLog_StaCnt(resucnt,failcnt,DATA_FILE,TIME,_T("多次转发测试"),1);
	return ack;
}
//连续多帧测试（中间无接收）（实际表）（模拟表）
INT8U CTEST_ReadMeterPublic::TestMoreReadMeterNoRcv(INT8U Type)
{
		INT16U noack=0;
		INT16U  errack=0;
		INT16U  okack=0;
		INT8U ack;
		INT8U reack = DACK_SUCESS;
		//INT8U tmpack;
		INT16U dataerrack=0;				     
		gSimMeter.ClrSimMeterComData();
		sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		Stu_Dtl2007 DstDecode2007DataFrame;
		INT8U seqbuf[100];
		INT8U sucfgbuf[100];
		BufIs0(sucfgbuf,100);
		INT8U readcnt =17;
		for(INT8U m=0; m<readcnt;m++)
		{
			gSimJzq.CodeReadMeter3762Cmd(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame);
			gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen );
			seqbuf[m] = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
		}
		for(INT16U m=0; m<readcnt;m++)
		{
			ack = gSimJzq.Wait3762Ack(10000,100,DstDecodeDataFrame);
			if((ack == DACK_SUCESS))
			{                    
				if((DstDecodeDataFrame.s_head.s_AFN == sQGDW376_2HostFrame.s_head.s_AFN) && (DstDecodeDataFrame.s_head.s_FN == sQGDW376_2HostFrame.s_head.s_FN))
				{ 
					ack = Decode2007(DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen,DstDecode2007DataFrame);
					if(ack == DACK_SUCESS)
					{
						for(INT16U n=0;n < readcnt; n++)
						{
							if(seqbuf[n]==DstDecodeDataFrame.s_head.s_Msg_Seq)
							{
								if((DstDecode2007DataFrame.s_Di ==gReMeterDi[0]))
								{
									sucfgbuf[n]=0x01;	  
								}
								else
								{
									sucfgbuf[n]=0x03;
								}
								break;
							}
						}
					}
				}
				else  if( (DstDecodeDataFrame.s_head.s_AFN ==0x00)&&(DstDecodeDataFrame.s_head.s_FN == F2))
				{
					for(INT16U n=0;n < readcnt; n++)
					{
						if(seqbuf[n] == DstDecodeDataFrame.s_head.s_Msg_Seq)
						{
							sucfgbuf[n]=0x02;
							break;
						}
					}
				}					 
			}
		}
						
	//比较结果 
		for(INT16U n=0;n < readcnt; n++)
		{
			if(sucfgbuf[n] == 0x01)
			{
				okack++;
			}
			else if(sucfgbuf[n] == 0x02)
			{
				errack++;
			}
			else if(sucfgbuf[n] == 0x03)
			{
				dataerrack++;
			}
			else
			{
				noack++;
			}
		}
		plog.saveLog_StaBuf8(sucfgbuf,readcnt,DATA_FILE,TIME,_T("多帧测试，发送中间无接收"));
		if((okack+errack == readcnt) && (okack >= 13))
		{

			plog.saveLog_testresult(DATA_FILE,TIME,_T("多帧测试，发送中间无接收"),DACK_SUCESS,1);

		}
		else
		{
			plog.saveLog_testresult(DATA_FILE,TIME,_T("多帧测试，发送中间无接收"),DACK_FAILURE,1);
			reack = DACK_FAILURE;
		}
		gSimMeter.ClrSimMeterComData();
		return reack;
}
//多帧测试（中间要接收）（实际表）（模拟表）
INT8U CTEST_ReadMeterPublic::TestMoreReadMeterRcv(INT8U Type)
{

		INT16U noack=0;
		INT16U  errack=0;
		INT16U  okack=0;
		INT8U ack;
		INT8U reack = DACK_SUCESS;
		//INT8U tmpack;
		INT16U dataerrack;
		gSimMeter.ClrSimMeterComData();
		sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		Stu_Dtl2007 DstDecode2007DataFrame;
		INT8U seqbuf[100+2];
		INT8U sucfgbuf[100+2];
		BufIs0(sucfgbuf,100);
		INT8U readcnt =100;
		INT8U m=0;
		for( m=0; m<readcnt;m++)
		{
			gSimJzq.CodeReadMeter3762Cmd(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame);
			gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen);
			seqbuf[m] = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
			ack = gSimJzq.Wait3762Ack(0,100,DstDecodeDataFrame);
			if(ack == DACK_SUCESS)
			{
				if((DstDecodeDataFrame.s_head.s_AFN == sQGDW376_2HostFrame.s_head.s_AFN) && (DstDecodeDataFrame.s_head.s_FN == sQGDW376_2HostFrame.s_head.s_FN))
				{ 
					ack = Decode2007(DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen,DstDecode2007DataFrame);

					if(ack == DACK_SUCESS)
					{
						for(INT16U n=0;n <= m; n++)
						{
							if(seqbuf[n]==DstDecodeDataFrame.s_head.s_Msg_Seq)
							{
								if((DstDecode2007DataFrame.s_Di ==gReMeterDi[0]))
								{
									sucfgbuf[n]=0x01;

								}
								else
								{
									sucfgbuf[n]=0x03;
								}
								break;
							}
						}

					}
				}
				else  if( (DstDecodeDataFrame.s_head.s_AFN ==0x00)&&(DstDecodeDataFrame.s_head.s_FN == F2))
				{
					for(INT16U n=0;n <= m; n++)
					{
						if(seqbuf[n] == DstDecodeDataFrame.s_head.s_Msg_Seq)
						{
							sucfgbuf[n]=0x02;
							break;
						}
					}
				}

			}
		}
					//------------------------
		for( m=0; m<readcnt;m++)
		{
			if( sucfgbuf[m]==0)
			{
				ack = gSimJzq.Wait3762Ack(10000,100,DstDecodeDataFrame);
				if((ack == DACK_SUCESS))
				{
					if((DstDecodeDataFrame.s_head.s_AFN == sQGDW376_2HostFrame.s_head.s_AFN) && (DstDecodeDataFrame.s_head.s_FN == sQGDW376_2HostFrame.s_head.s_FN))
					{ 
						ack = Decode2007(DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen,DstDecode2007DataFrame);

						if(ack == DACK_SUCESS)
						{
							for(INT16U n=0;n < readcnt; n++)
							{
								if(seqbuf[n]==DstDecodeDataFrame.s_head.s_Msg_Seq)
								{
									if((DstDecode2007DataFrame.s_Di ==gReMeterDi[0]))
									{
										sucfgbuf[n]=0x01;

									}
									else
									{
										sucfgbuf[n]=0x03;
									}
									break;
								}
							}

						}
					}
					else  if( (DstDecodeDataFrame.s_head.s_AFN ==0x00)&&(DstDecodeDataFrame.s_head.s_FN == F2))
					{
						for(INT16U n=0;n < readcnt; n++)
						{
							if(seqbuf[n] == DstDecodeDataFrame.s_head.s_Msg_Seq)
							{
								sucfgbuf[n]=0x02;
								break;
							}
						}
					}
				}

			}
		}
    //比较结果 
		for(INT16U n=0;n < readcnt; n++)
		{
			if(sucfgbuf[n] == 0x01)
			{
				okack++;
			}
			else if(sucfgbuf[n] == 0x02)
			{
                errack++;
			}
			else if(sucfgbuf[n] == 0x03)
			{
                dataerrack++;
			}
			else
			{
				noack++;
			}


		}
		plog.saveLog_StaBuf8(sucfgbuf,readcnt,DATA_FILE,TIME,"多帧测试，发送中间有接收");
		if((okack+errack == readcnt) && (okack >= 50))
		{

			plog.saveLog_testresult(DATA_FILE,TIME,"多帧测试，发送中间有接收",DACK_SUCESS,1);

		}
		else
		{
			plog.saveLog_testresult(DATA_FILE,TIME,"多帧测试，发送中间有接收",DACK_FAILURE,1);
			reack = DACK_FAILURE;
		}
		gSimMeter.ClrSimMeterComData();
		return reack;

}
INT8U  CTEST_ReadMeterPublic::TestReadMeterLongFame(INT32U vSrcCnt,INT8U vSrcAfntype,INT8U vSrcMeterType)
{
	INT8U ack;
	INT32U resucnt=0;
	INT32U failcnt=0;
	sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sAckTimeSta  ackclkSta;
	for(INT32U m=0;m<vSrcCnt;m++)
	{
		 ack = gSimJzq.ReadMeterAndCmpMterAckClk(vSrcAfntype,&gNodeAddBuf[0][0],0x19010001,sQGDW376_2HostFrame,DstDecodeDataFrame,ackclkSta,vSrcMeterType);
	
		 if(ack==DACK_SUCESS)
		 {
               resucnt++;
		 }
		 else
		 {
			 failcnt++;
		 }
	}

	if(failcnt == 0)
	{
        ack = DACK_SUCESS;
	}
	else
	{
		 ack = DACK_FAILURE;
	}
	plog.saveLog_StaCnt(resucnt,failcnt,DATA_FILE,TIME,"多次转发测试",1);
	return ack;
}
//	组网未成功抄表（实际表）（模拟表）
INT8U  CTEST_ReadMeterPublic::TestSeqNONet(INT32U vSrcCnt,INT8U Type)
{

	
		INT8U resucnt=0;
		INT8U ack;
		sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		INT32U succnt=0;
		INT32U failcnt=0;
		resucnt = 0; 
		//查看下发的SEQ与回复的SEQ一致，且错误代码为0x0c（从节点不在网）。
		for(INT32U m = 0; m<vSrcCnt; m++)
		{
		    ack = gSimJzq.Read3762Meter(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame,DstDecodeDataFrame);
			if((ack == DACK_SUCESS)&&(DstDecodeDataFrame.s_head.s_AFN==0x00)&&(DstDecodeDataFrame.s_head.s_FN==F2)&&(DstDecodeDataFrame.s_RcvDataLen==1)&&(DstDecodeDataFrame.s_RcvDataBuf[0]==0x0C))
			{
			    succnt++;
			}
			else
			{
			    failcnt++;
			}
		}
		plog.saveLog_StaCnt(resucnt,failcnt,DATA_FILE,TIME,"子步骤-不在网测试",1);
		if(failcnt==0)
		{
			  ack = DACK_SUCESS;
		}
		else
		{
			 ack = DACK_FAILURE;
			
		}
				
		return 	ack;
}
INT8U  CTEST_ReadMeterPublic::TestSeqNOAck645Di(INT8U Type)
{

	 gSimMeter.SetSimMeterRunFg(0);
	 gSimMeter.ClrSimMeterComData();
		INT8U resucnt=0;
		INT8U ack;
		sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		INT16U succnt=0;
		INT16U failcnt=0;
		resucnt = 0; 
		//查看下发的SEQ与回复的SEQ一致，且错误代码为0x00（电表无返回）。
		for(INT8U m = 0; m<1; m++)
		{
		    ack = gSimJzq.Read3762Meter(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame,DstDecodeDataFrame);
			if((ack == DACK_SUCESS)&&(DstDecodeDataFrame.s_head.s_AFN==0x00)&&(DstDecodeDataFrame.s_head.s_FN==F2)&&(DstDecodeDataFrame.s_RcvDataLen==1)&&(DstDecodeDataFrame.s_RcvDataBuf[0]==0x00))
			{
			    succnt++;
			}
			else
			{
			    failcnt++;
			}
		}
		plog.saveLog_StaCnt(resucnt,failcnt,PARS_FILE,TIME,"子步骤--表无数据返回",1);
		if(failcnt==0)
		{
			if( Type == 0)
			   plog.saveLog_testresult_AfnFn(0x02,F1,PARS_FILE,TIME,"",DACK_SUCESS,1);
			else
			    plog.saveLog_testresult_AfnFn(0x13,F1,PARS_FILE,TIME,"",DACK_SUCESS,1); 
		}
		else
		{
			if( Type == 0)
		    	plog.saveLog_testresult_AfnFn(0x02,F1,PARS_FILE,TIME,"",DACK_FAILURE,1);
			else
			   plog.saveLog_testresult_AfnFn(0x13,F1,PARS_FILE,TIME,"",DACK_FAILURE,1);
		}
				
		gSimMeter.ClrSimMeterComData();
		gSimMeter.SetSimMeterRunFg(1);
		return 	ack;
}
//回复DI不一致数据（模拟表）
INT8U  CTEST_ReadMeterPublic::TestSeqAck645ErrDi(INT32U vSrcCnt,INT8U Type)
{
		INT32U succnt=0;
		INT32U failcnt=0;
		INT8U ack;
		INT8U reack = DACK_SUCESS;
		gSimMeter.SetSimMeterRunFg(0);
		gSimMeter.ClrSimMeterComData();
		sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		Stu_Dtl2007 DstDecode2007DataFrame;
		for(INT32U m = 0; m<vSrcCnt; m++)
		{
			ack = gSimJzq.CodeReadMeter3762Cmd(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame);
			if(ack == DACK_SUCESS)
			{
				gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen );
				ack = gSimMeter. Wait645ack(6000,100,DstDecode2007DataFrame);
				if(ack == DACK_SUCESS)
				{
					 ack= DACK_EER_645DATA;
					if(DstDecode2007DataFrame.s_Di ==gReMeterDi[0] )
					{
						DstDecode2007DataFrame.s_Di =gReMeterDi[1];
						gSimMeter. SendMeterData_645(DstDecode2007DataFrame);
						if( Type == 0)
						{
							ack = gSimJzq.WaitReadMeterAFN02F1AckAndCmp(10000,100,gReMeterDi[1],sQGDW376_2HostFrame,DstDecodeDataFrame);
						}
						else
						{
							ack = gSimJzq.WaitReadMeterAFN13F1AckAndCmp(10000,100,gReMeterDi[1],sQGDW376_2HostFrame,DstDecodeDataFrame);
						}
					}
				}
	  		}
		}
		plog.saveLog_StaCnt(succnt,failcnt,PARS_FILE,TIME,"回复DI不一致数据",1);
		if(failcnt==0)
		{
			  ack = DACK_SUCESS;
		}
		else
		{
			 ack = DACK_FAILURE;
			
		}
		
		plog.saveLog_testresult(PARS_FILE,TIME,"回复DI不一致数据 ",ack,1);
		
		gSimMeter.ClrSimMeterComData();
		gSimMeter.SetSimMeterRunFg(1);

   return 		ack;
}
//	表部分回复测试。（模拟表）
INT8U CTEST_ReadMeterPublic::TestPartAckNo(INT8U Type)
{
	         INT8U resucnt=0;
	           INT8U  refailcnt=0;
			   INT8U ack;
			   INT8U reack = DACK_SUCESS;
			   INT8U tmpack;
				        gSimMeter.SetSimMeterRunFg(0);
					    gSimMeter.ClrSimMeterComData();
				      sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
					  sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
					  Stu_Dtl2007 DstDecode2007DataFrame;
					
					  for(INT8U m=0; m<8;m++)
				    {
						 gSimJzq.CodeReadMeter3762Cmd(Type,&gNodeAddBuf[0][0],gReMeterDi[m], sQGDW376_2HostFrame);
						gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen );
					}
					    for(INT8U m=0; m<8;m++)
				       {
					      ack = gSimMeter. Wait645ack(6000,100,DstDecode2007DataFrame);
						   if((ack == DACK_SUCESS)&&(DstDecode2007DataFrame.s_Di ==gReMeterDi[m] ))
						   {
							 if((m<3)||(m>4))
                              {
								  gSimMeter. SendMeterData_645(DstDecode2007DataFrame);
							  }
						   }
						}
                       
						for(INT8U m=0; m<8;m++)
				       {
						 ack = gSimJzq.Wait3762Ack(10000,100,DstDecodeDataFrame);
						 if((ack == DACK_SUCESS))
						 {
                           if((m<3)||(m>4))
						   {
							  if(( DstDecodeDataFrame.s_head.s_AFN ==0x00)&&(DstDecodeDataFrame.s_head.s_FN == F2))
							  {
								  resucnt++;
							  }
							  else
							  {
								  refailcnt++;
							  }
						    }
						   else
						   {
							   tmpack = DACK_FAILURE;
							    if((Type==0)&&( DstDecodeDataFrame.s_head.s_AFN ==0x02)&&(DstDecodeDataFrame.s_head.s_FN == F1))
								{ 
								     tmpack = DACK_SUCESS;
								}
								else  if((Type==1)&&( DstDecodeDataFrame.s_head.s_AFN ==0x13)&&(DstDecodeDataFrame.s_head.s_FN == F1))
								{
								   tmpack = DACK_SUCESS;
								}
			                  if( tmpack == DACK_SUCESS)
							  {
								  ack = Decode2007(DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen,DstDecode2007DataFrame);
								  if((ack == DACK_SUCESS)&&(DstDecode2007DataFrame.s_Di ==gReMeterDi[m]))
								 {
									 resucnt++;
								  }
								  else
								  {
									refailcnt++;
									}
							  }
							  
						   }
						 }
					   }

						if((resucnt==6)&&(refailcnt==2))
					 {
						
					     //plog.saveLog_testresult(PARS_FILE,TIME,"部分成功否认帧测试",DACK_SUCESS,1);
						
					 }
					else
					{
					    // plog.saveLog_testresult(PARS_FILE,TIME,"部分成功否认帧测试",DACK_FAILURE,1);
						  reack = DACK_FAILURE;
					}
				     gSimMeter.ClrSimMeterComData();
					 gSimMeter.SetSimMeterRunFg(1);
		return reack;
}
//重发次数、间隔时间测试
//  Type  0: 02, 1:   13:
INT8U CTEST_ReadMeterPublic::TestIntevalTime(INT8U Type)
{
			   INT8U resucnt=0;
	           INT8U  refailcnt=0;
			   INT8U ack;
			   INT8U reack = DACK_SUCESS;
				        gSimMeter.SetSimMeterRunFg(0);
					    gSimMeter.ClrSimMeterComData();
				      sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
					  sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
					  Stu_Dtl2007 DstDecode2007DataFrame;
					  INT32U timeclk376Rcvbuf[100+2];
					  INT32U timeclk645Rcvbuf[100+2];
					  INT32U tmpstartclk;
					  INT8U readcnt=100;
						for(INT8U m=0; m<readcnt;m++)
						{
							timeclk376Rcvbuf[m]=0xFFFFFFFF;
							timeclk645Rcvbuf[m]=0xFFFFFFFF;
							 tmpstartclk = GetSysTimeClk();

                            gSimJzq.CodeReadMeter3762Cmd(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame);
					
							gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen );
							ack = gSimMeter. Wait645ack(6000,100,DstDecode2007DataFrame);
							if((ack == DACK_SUCESS)&&(DstDecode2007DataFrame.s_Di ==gReMeterDi[0] ))
							{
								timeclk645Rcvbuf[m]=GetSysTimeInterval(tmpstartclk);
								gSimMeter. SendMeterData_645(DstDecode2007DataFrame);
								ack = gSimJzq.Wait3762Ack(10000,100,DstDecodeDataFrame);
								if((ack == DACK_SUCESS))
								{
									if((Type==0)&&( DstDecodeDataFrame.s_head.s_AFN ==0x02)&&(DstDecodeDataFrame.s_head.s_FN == F1))
									 {
										 timeclk376Rcvbuf[m]=GetSysTimeInterval(tmpstartclk);
									 }
									else if((Type==1)&&( DstDecodeDataFrame.s_head.s_AFN ==0x13)&&(DstDecodeDataFrame.s_head.s_FN == F1))
									 {
										 timeclk376Rcvbuf[m]=GetSysTimeInterval(tmpstartclk);
									 }
								}
							}
						}
                      //判断合格
					    for(INT8U m=0; m<readcnt;m++)
						{
							if((timeclk376Rcvbuf[m] < 500) && (timeclk645Rcvbuf[m] < 100))
							{
								resucnt++;
							}
							else
							{
								refailcnt++;
							}
					    }
					//打印间隔时间：

                         plog.saveLog_StaBuf32(timeclk376Rcvbuf,readcnt,PARS_FILE,TIME,"间隔时间测试，有返回--3762时间");
						 plog.saveLog_StaBuf32(timeclk645Rcvbuf,readcnt,PARS_FILE,TIME,"间隔时间测试，有返回--645时间");
                     // -------------------
						if(refailcnt>0) 
					 {
						
					     plog.saveLog_testresult(PARS_FILE,TIME,"----子步骤-》 间隔时间测试-》有数据返回",DACK_SUCESS,1);
					 }
					else
					{
    
					     plog.saveLog_testresult(PARS_FILE,TIME,"----子步骤-》间隔时间测试-》有数据返回",DACK_FAILURE,1);
						 reack = DACK_FAILURE;
					}

                //-------------测试无数据返回子项-----------------------------
						readcnt=3;
                         for(INT8U m=0; m<readcnt;m++)
						{
							timeclk376Rcvbuf[m]=0xFFFFFFFF;
							timeclk645Rcvbuf[m]=0xFFFFFFFF;
							 tmpstartclk = GetSysTimeClk();
							 gSimJzq.CodeReadMeter3762Cmd(Type,&gNodeAddBuf[0][0],gReMeterDi[0], sQGDW376_2HostFrame);
							gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen );
							ack = gSimMeter. Wait645ack(6000,100,DstDecode2007DataFrame);
							if((ack == DACK_SUCESS)&&(DstDecode2007DataFrame.s_Di ==gReMeterDi[0] ))
							{
								timeclk645Rcvbuf[m]=GetSysTimeInterval(tmpstartclk);
							    //gSimMeter. SendMeterData_645(DstDecode2007DataFrame);
								ack = gSimJzq.Wait3762Ack(20*1000,100,DstDecodeDataFrame);
								if((ack == DACK_SUCESS)&&( DstDecodeDataFrame.s_head.s_AFN ==0x00)&&(DstDecodeDataFrame.s_head.s_FN == F2))
								{
									timeclk376Rcvbuf[m]=GetSysTimeInterval(tmpstartclk);
								}
							}
						}
                      //判断合格
					    for(INT8U m=0; m<readcnt;m++)
						{
							if((timeclk376Rcvbuf[m] >90*1000) &&(timeclk376Rcvbuf[m] < 150*1000) && (timeclk645Rcvbuf[m] < 100))
							{
								resucnt++;
							}
							else
							{
								refailcnt++;
							}
					    }
					//打印间隔时间：

                        plog.saveLog_StaBuf32(timeclk376Rcvbuf,readcnt,PARS_FILE,TIME,"间隔时间测试 无返回--3762时间");
						 plog.saveLog_StaBuf32(timeclk645Rcvbuf,readcnt,PARS_FILE,TIME,"间隔时间测试 无返回--645时间");
						
                     // -------------------
						if(refailcnt>0) 
					 {
						
					     plog.saveLog_testresult(PARS_FILE,TIME,"子步骤-》 间隔时间测试-》无数据返回",DACK_SUCESS,1);
					 }
					else
					{
     
					      plog.saveLog_testresult(PARS_FILE,TIME,"子步骤-》间隔时间测试-》无数据返回",DACK_FAILURE,1);
						  reack = DACK_FAILURE;
					}



				    gSimMeter.ClrSimMeterComData();
					 gSimMeter.SetSimMeterRunFg(1);
					 return reack;
}




