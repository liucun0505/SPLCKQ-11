// TESTCCO_BingFChaoB.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTCCO_BingFChaoB.h"
#include "ImitateMeterDlg.h"
#include "MyFunLib.h"
#include "SimJZQ.h"
extern CSimJzq  gSimJzq;
extern CSimMeter  gSimMeter;

#include "GW13762.h"
extern CGW13762 Cgw13762;
#include "LogFile.h"
extern CLogFile plog;//打引用

#include "User_Mcu_Cfg.h"
#include "User_App_Cfg.h"
IMPLEMENT_DYNAMIC(CTESTCCO_BingFChaoB, CWnd)





	CTESTCCO_BingFChaoB::CTESTCCO_BingFChaoB()
{
	//m_RunFg = 0;
}

CTESTCCO_BingFChaoB::~CTESTCCO_BingFChaoB()
{
}


BEGIN_MESSAGE_MAP(CTESTCCO_BingFChaoB, CWnd)
END_MESSAGE_MAP()

void CTESTCCO_BingFChaoB::C3762_TEST(HTREEITEM hTree)
{
	CImitateMeterDlg * pMainDlg = (CImitateMeterDlg *)theApp.m_pMainWnd;
	if (!pMainDlg->m_bConnected)
	{
		AfxMessageBox("请打开模拟集中器串口!");
		return;
	}
	if (!pMainDlg->m_bConnected2)
	{
		AfxMessageBox("请打开模拟表串口!");
		return;
	}
	INT8U ack = FALSE;
	pMainDlg->m_treeProject.Expand(hTree,TVE_EXPAND);//展开树节点
	HTREEITEM hNextItem = pMainDlg->m_treeProject.GetNextItem(hTree,TVGN_NEXTVISIBLE);
	CString strName;
    INT16U allSucesscnt = 0;
	INT16U allfailcnt = 0;;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	INT8U amtbuf[7+1]={0x01,0x00,0x00,0x00,0x00,0x00};
	BufToBuf(amtbuf,&gNodeAddBuf[0][0],7);
//	Stu_Dtl2007 DstDecode2007DataFrame;
		sBinFa376_2_HostMsg  BinDownmsg;
	gSimMeter.ClrSimMeterComData();
//	gSimJzq.ClrZjqComData();
	//ack=gSimJzq.HostSendRcv376_2NoBuf_NoAck(0x01,F2);
	//plog.saveLog_testresult(PARS_FILE,TIME,"参数区初始化 ",ack);
		 ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,m_HostNodeAddress,6);
		  plog.saveLog_testresult(PARS_FILE,TIME,"设置CCO的主节点地址 ",ack,2);
		  ack = gSimJzq.SetNodeAdd(0,1);
		  plog.saveLog_testresult(PARS_FILE,TIME,"设置从节点 ",ack,2);
	while (hNextItem)
	{
		 

		strName = pMainDlg->m_treeProject.GetItemText(hNextItem);
		if (pMainDlg->m_treeProject.GetCheck(hNextItem))
		{
			switch(atol(strName.Mid(0,2)))
			{
			case 1://单帧并发（实际表）-（多个645）
				{
			        resucnt=0;
					refailcnt=0;
				    plog.saveLog_strAll(TIME,"开始测试："+strName,2);
					INT32U tmp32;
					INT32U ackfg;
					gSimMeter.SetSimMeterRunFg(0);//设置模拟表运行
					for(INT8U i=1; i<16; i++)//循环组645帧发送从1-15个645
					{
						ackfg=0;
						for(INT8U m=0;m<i;m++)
			            {
							ackfg |= Bit0<<m;
						}
						ack = gSimJzq.BinFenReadMeter(DPCT_2007FG,amtbuf,i,ackfg,0,BinDownmsg,tmp32);
						if(ack == DACK_SUCESS)
						{
	                      resucnt++;
						}
						else
						{
                           refailcnt++;
						}
						 
					}	

					 if(refailcnt == 0)
		               {
						   ack=DACK_SUCESS;
					   }
					 else
						{
							ack = DACK_FAILURE;
					     }
				 StaSucessCnt(ack,allSucesscnt,allfailcnt);
				  plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"",1);
			      plog.saveLog_testresultAll(TIME,strName ,DACK_SUCESS,1);
			      plog.saveLog_strAll(TIME,"结束测试："+strName,2);
		
				}
				break;
			case 2://单帧并发（模拟表）-（多个645）
					{
			        resucnt=0;
					refailcnt=0;
				    plog.saveLog_strAll(TIME,"开始测试："+strName,2);
					INT32U tmp32;
					INT32U ackfg;
					gSimMeter.SetSimMeterRunFg(1);//设置模拟表运行
					for(INT8U i=1; i<16; i++)//循环组645帧发送从1-15个645
					{
			             ackfg=0;
						for(INT8U m=0;m<i;m++)
			            {
							ackfg |= Bit0<<m;
						}
						ack = gSimJzq.BinFenReadMeter(DPCT_2007FG,amtbuf,i,ackfg,0,BinDownmsg,tmp32);
						if(ack == DACK_SUCESS)
						{
	                      resucnt++;
						}
						else
						{
                           refailcnt++;
						}
						 
					}	

					 if(refailcnt == 0)
		               {
						   ack=DACK_SUCESS;
					   }
					 else
						{
							ack = DACK_FAILURE;
					     }
				  StaSucessCnt(ack,allSucesscnt,allfailcnt);
				  plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"",1);
			      plog.saveLog_testresultAll(TIME,strName ,DACK_SUCESS,1);
			      plog.saveLog_strAll(TIME,"结束测试："+strName,2);
		
				}
				break;
		
			case 3://单帧并发（模拟表）-（部分返回）
				{

					 resucnt=0;
					 refailcnt=0;
				     plog.saveLog_strAll(TIME,"开始测试："+strName,2);
					 INT32U tmp32;
					 INT32U ackfg=0;
//					 INT32U  noackvaltimebuf[4];
//					 sNoAckDiMsg  noackMsg;
					 gSimMeter.SetSimMeterRunFg(1);//设置模拟表运行
					//1）376.2报文中发送13帧645报文，模拟表接收到奇数帧是正常返回，接收到偶数帧时不返回
					 gSimMeter.ClrALLNoAckDi();
						ackfg=0x1FFF;
						for(INT8U i=1; i<13; i+=2)//
						{
							gSimMeter.SetNoAckDi(gBinFangDi[i]);
							ackfg&=~(Bit0<<i);
						}
						ack = gSimJzq.BinFenReadMeter(DPCT_2007FG,amtbuf,13,ackfg,1,BinDownmsg,tmp32);
						if((ack == DACK_FAILURE))
						{
	                      resucnt++;
						}
						else
						{
                           refailcnt++;
						}
						 plog.saveLog_testresultAll(TIME,"1）376.2报文中发送13帧645报文，模拟表接收到奇数帧是正常返回，接收到偶数帧时不返回" ,DACK_SUCESS,1);
                      //2）376.2报文中发送13帧645报文，模拟表接收到偶数帧是正常返回，接收到奇数帧时不返回。
						 gSimMeter.ClrALLNoAckDi();
						ackfg=0x1FFF;
						for(INT8U i=0; i<13; i+=2)//
						{
							gSimMeter.SetNoAckDi(gBinFangDi[i]);
							ackfg&=~(Bit0<<i);
						}
						ack = gSimJzq.BinFenReadMeter(DPCT_2007FG,amtbuf,13,ackfg,1,BinDownmsg,tmp32);
						if((ack == DACK_FAILURE))
						{
	                      resucnt++;
						}
						else
						{
                           refailcnt++;
						}

						 plog.saveLog_testresultAll(TIME,"2）376.2报文中发送13帧645报文，模拟表接收到偶数帧是正常返回，接收到奇数帧时不返回" ,DACK_SUCESS,1);

                      //3）376.2报文中发送13帧645报文，接收到1-3不返回，接收到9--11不返回
						 gSimMeter.ClrALLNoAckDi();
						ackfg=0x1FFF;
						for(INT8U i=0; i<13; i+=1)//
						{
						   if(((i>=1)&&(i<=3))||((i>=9)&&(i<=11)))
						   {
							gSimMeter.SetNoAckDi(gBinFangDi[i]);
							ackfg&=~(Bit0<<i);
						   }
						}
						ack = gSimJzq.BinFenReadMeter(DPCT_2007FG,amtbuf,13,ackfg,1,BinDownmsg,tmp32);
						if((ack == DACK_FAILURE))
						{
	                      resucnt++;
						}
						else
						{
                           refailcnt++;
						}
						 plog.saveLog_testresultAll(TIME,"3）376.2报文中发送13帧645报文，接收到1-3不返回，接收到9--11不返回" ,DACK_SUCESS,1);

				     //4）376.2报文中发送13帧645报文，都不返回
						 gSimMeter.ClrALLNoAckDi();
						ackfg=0x1FFF;
						   for(INT8U i=0; i<13; i++)
						{
							gSimMeter.SetNoAckDi(gBinFangDi[i]);
							ackfg&=~(Bit0<<i);
						}
					
						ack = gSimJzq.BinFenReadMeter(DPCT_2007FG,amtbuf,13,ackfg,1,BinDownmsg,tmp32);
						if((ack == DACK_FAILURE))
						{
	                      resucnt++;
						}
						else
						{
                           refailcnt++;
						}

                    if(ack == DACK_SUCESS)
					{
						if(refailcnt == 0)
		               {
						   ack=DACK_SUCESS;
					   }
					 else
						{
							ack = DACK_FAILURE;
					     }
					}
					 plog.saveLog_testresultAll(TIME,"4）376.2报文中发送13帧645报文，都不返回" ,DACK_SUCESS,1);

				  StaSucessCnt(ack,allSucesscnt,allfailcnt);
				  plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"",1);
			      plog.saveLog_testresultAll(TIME,strName ,DACK_SUCESS,1);
			      plog.saveLog_strAll(TIME,"结束测试："+strName,2);
				  gSimMeter.ClrALLNoAckDi();
				 }	
				break;
			
			case 4://4.	多帧并发（实际表）-（多帧645）
				{

				    plog.saveLog_strAll(TIME,"开始测试："+strName,2);
					INT8U tmpbuf[1000];
					INT16U len16;
					INT8U sucnt = 0;
					INT8U failcnt = 0;
					sBinFa376_2_HostMsg  BinDownmsg;
					sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;	
					sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
					for(INT8U i=1; i<11; i++)//循环组645帧发送从1-15个645
					{
						tmpbuf[0] = DPCT_2007FG;//规约类型
						tmpbuf[1] = 0x00;//附属节点数量
						
						gSimJzq.QueMore645Fame(DPCT_2007FG,1000,amtbuf,13,&tmpbuf[4],len16,BinDownmsg);//获取标识组645帧
						Hex16ToBuf2(len16,&tmpbuf[2]);//报文长度
						//模拟集中器发送与接收
						ack = Cgw13762.Code376_2_HostBufNodeFrame(amtbuf,0xF1,F1,tmpbuf,len16+4,sQGDW376_2HostFrame);
						if(ack == DACK_SUCESS)
						{
                           gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen);
						}
					}
					for(INT8U i=1; i<11; i++)
					{
                          ack = gSimJzq.CmpBinFenRcvMeter(amtbuf,DPCT_2007FG,13,0,100*1000,100,DstDecodeDataFrame);
						  if(ack == DACK_SUCESS)
						 {
                                sucnt++;
						 }
						  else
						  {
							    failcnt++;
						  }

					}
				  if(ack == DACK_SUCESS)
					{
						if(refailcnt == 0)
		               {
						   ack=DACK_SUCESS;
					   }
					 else
						{
							ack = DACK_FAILURE;
					     }
					}
				  StaSucessCnt(ack,allSucesscnt,allfailcnt);
				  plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"",1);
			      plog.saveLog_testresultAll(TIME,strName ,DACK_SUCESS,1);
			      plog.saveLog_strAll(TIME,"结束测试："+strName,2);	
				}
				break;
			case 5://5.	多帧并发（模拟表）-（多帧645）
					{

				    plog.saveLog_strAll(TIME,"开始测试："+strName,2);
					INT8U tmpbuf[1000];
					INT16U len16;
					INT8U sucnt = 0;
					INT8U failcnt = 0;
					sBinFa376_2_HostMsg  BinDownmsg;
					sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;	
					sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
					for(INT8U i=1; i<11; i++)//循环组645帧发送从1-15个645
					{
						tmpbuf[0] = DPCT_2007FG;//规约类型
						tmpbuf[1] = 0x00;//附属节点数量
						
						gSimJzq.QueMore645Fame(DPCT_2007FG,1000,amtbuf,13,&tmpbuf[4],len16,BinDownmsg);//获取标识组645帧
						Hex16ToBuf2(len16,&tmpbuf[2]);//报文长度
						//模拟集中器发送与接收
						ack = Cgw13762.Code376_2_HostBufNodeFrame(amtbuf,0xF1,F1,tmpbuf,len16+4,sQGDW376_2HostFrame);
						if(ack == DACK_SUCESS)
						{
                           gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen);
						}
					}
					for(INT8U i=1; i<11; i++)
					{
                         ack = gSimJzq.CmpBinFenRcvMeter(amtbuf,DPCT_2007FG,13,1,100*1000,100,DstDecodeDataFrame);
						  if(ack == DACK_SUCESS)
						 {
                                sucnt++;
						 }
						  else
						  {
							    failcnt++;
						  }

					}
				  if(ack == DACK_SUCESS)
					{
						if(refailcnt == 0)
		               {
						   ack=DACK_SUCESS;
					   }
					 else
						{
							ack = DACK_FAILURE;
					     }
					}
				  StaSucessCnt(ack,allSucesscnt,allfailcnt);
				  plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"",1);
			      plog.saveLog_testresultAll(TIME,strName ,DACK_SUCESS,1);
			      plog.saveLog_strAll(TIME,"结束测试："+strName,2);	
				}
				break;
			case 6://		多帧并发成功率统计（多帧645）：
					 {
						 plog.saveLog_strAll(TIME,"开始测试："+strName,2);
					   INT8U tmpbuf[1000];

						INT8U resucnt=0;
						INT8U  refailcnt=0;
						INT8U ack;
						INT8U reack = DACK_SUCESS;
				        gSimMeter.SetSimMeterRunFg(1);
					    gSimMeter.ClrSimMeterComData();
						  sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
						  sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
//						  Stu_Dtl2007 DstDecode2007DataFrame;
						  sAckTimeSta timeclk376[100+2];
						  INT32U tmpstartclk;
						  INT8U readcnt=100;
						  INT16U len16;
						for(INT8U m=0; m<readcnt;m++)
						{
							
				            timeclk376[m].ackFg=0;
                            tmpbuf[0] = DPCT_2007FG;//规约类型
						    tmpbuf[1] = 0x00;//附属节点数量
						
						gSimJzq.QueMore645Fame(DPCT_2007FG,1000,amtbuf,13,&tmpbuf[4],len16,BinDownmsg);//获取标识组645帧
						Hex16ToBuf2(len16,&tmpbuf[2]);//报文长度
						//模拟集中器发送与接收
						ack = Cgw13762.Code376_2_HostBufNodeFrame(amtbuf,0xF1,F1,tmpbuf,len16+4,sQGDW376_2HostFrame);
						if(ack == DACK_SUCESS)
						{
                           gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen);
						   timeclk376[m].timeclk=GetSysTimeClk();
						   timeclk376[m].s_Seq = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
						}
						    ack = gSimJzq.CmpBinFenRcvMeter(amtbuf,DPCT_2007FG,13,0,0,100,DstDecodeDataFrame);
							//if((ack == DACK_SUCESS))
							{
							   gSimJzq.CmpAckTimeClk(m+1,DstDecodeDataFrame,ack,timeclk376);
									
							}
						}
						for(INT8U m=0; m<readcnt;m++)
						{
							if(timeclk376[m].ackFg ==0)
							{
								ack = gSimJzq.CmpBinFenRcvMeter(amtbuf,DPCT_2007FG,13,0,200*1000,100,DstDecodeDataFrame);
								gSimJzq.CmpAckTimeClk(m+1,DstDecodeDataFrame,ack,timeclk376);	
							}
						}
                      //判断合格
					    for(INT8U m=0; m<readcnt;m++)
						{
							if((timeclk376[m].ackFg ==1) && (timeclk376[m].dataack ==DACK_SUCESS)&& (timeclk376[m].timeclk< READMETER_MAXDLY_TIME*2))
							{
								resucnt++;
							}
							else
							{
								refailcnt++;
							}
					    }

						if(refailcnt == 0)
		                {
						   ack=DACK_SUCESS;
					    }
					 else
						{
							ack = DACK_FAILURE;
					     }
				  StaSucessCnt(ack,allSucesscnt,allfailcnt);
	
				  plog.saveLog_ClkSta(timeclk376,100,DATA_FILE,TIME,"strName",1);
			      plog.saveLog_testresultAll(TIME,strName ,DACK_SUCESS,1);
			      plog.saveLog_strAll(TIME,"结束测试："+strName,2);	
				}
				break;
			case 7://7.	连续20帧测试
					{

				    plog.saveLog_strAll(TIME,"开始测试："+strName,2);
					INT8U tmpbuf[1000];
					INT16U len16;
					INT8U sucnt = 0;
					INT8U failcnt = 0;
					INT8U othererr=0;
					INT8U allerr=0;
					sBinFa376_2_HostMsg  BinDownmsg;
					sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;	
					sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
					sAckTimeSta timeclk376[30+2];
				for(INT8U n=0;n<5;n++)
				{
					for(INT8U m=0; m<20; m++)//循环组645帧发送从1-15个645
					{
						tmpbuf[0] = DPCT_2007FG;//规约类型
						tmpbuf[1] = 0x00;//附属节点数量
						timeclk376[m].ackFg=0;
						gSimJzq.QueMore645Fame(DPCT_2007FG,1000,amtbuf,13,&tmpbuf[4],len16,BinDownmsg);//获取标识组645帧
						Hex16ToBuf2(len16,&tmpbuf[2]);//报文长度
						//模拟集中器发送与接收
						ack = Cgw13762.Code376_2_HostBufNodeFrame(amtbuf,0xF1,F1,tmpbuf,len16+4,sQGDW376_2HostFrame);
						if(ack == DACK_SUCESS)
						{
                           gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen);
						   timeclk376[m].timeclk=GetSysTimeClk();
						   timeclk376[m].s_Seq = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
						}
					}
					for(INT8U m=0; m<20; m++)
					{
                         ack = gSimJzq.CmpBinFenRcvMeter(amtbuf,DPCT_2007FG,13,0,100*1000,100,DstDecodeDataFrame);
						 gSimJzq.CmpAckTimeClk(m+1,DstDecodeDataFrame,ack,timeclk376);

					}
				    for(INT8U m=0; m<20; m++)
					{
                       if(timeclk376[m].ackFg==1)
					   {
                          if(timeclk376[m].dataack==DACK_SUCESS)
						  {
							  sucnt++;
						  }
						  else if(timeclk376[m].dataack==DACK_SUCESS)
						  {
							  refailcnt++;
						  }
						  else
						  {
							  othererr++;
						  }
					   }
					}
						if(othererr == 0)
		               {
						   ack=DACK_SUCESS;
					   }
					  else
						{
							ack = DACK_FAILURE;
							allerr++;
					     }
				  plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"",1);
				  plog.saveLog_ClkSta(timeclk376,20,DATA_FILE,TIME,"strName",1);
				}

				
						if(allerr == 0)
		               {
						   ack=DACK_SUCESS;
					   }
					  else
						{
							ack = DACK_FAILURE;
					     }
				  StaSucessCnt(ack,allSucesscnt,allfailcnt);
				  
			      plog.saveLog_testresultAll(TIME,strName ,DACK_SUCESS,1);
			      plog.saveLog_strAll(TIME,"结束测试："+strName,2);	
				}
				break;

			case 8://单帧并发97表（模拟表）-（多个645）
					{
			        resucnt=0;
					refailcnt=0;
				    plog.saveLog_strAll(TIME,"开始测试："+strName,2);
					INT32U tmp32;
					INT32U ackfg;
					gSimMeter.SetSimMeterRunFg(1);//设置模拟表运行
					for(INT8U i=1; i<16; i++)//循环组645帧发送从1-15个645
					{
			             ackfg=0;
						for(INT8U m=0;m<i;m++)
			            {
							ackfg |= Bit0<<m;
						}
						ack = gSimJzq.BinFenReadMeter(DPCT_97FG,amtbuf,i,ackfg,1,BinDownmsg,tmp32);
						if(ack == DACK_SUCESS)
						{
	                      resucnt++;
						}
						else
						{
                           refailcnt++;
						}
						 
					}	

					 if(refailcnt == 0)
		               {
						   ack=DACK_SUCESS;
					   }
					 else
						{
							ack = DACK_FAILURE;
					     }
				  StaSucessCnt(ack,allSucesscnt,allfailcnt);
				  plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"",1);
			      plog.saveLog_testresultAll(TIME,strName ,DACK_SUCESS,1);
			      plog.saveLog_strAll(TIME,"结束测试："+strName,2);
		
				}
				break;
			default:
				break;
			}
		}
		hNextItem = pMainDlg->m_treeProject.GetNextItem(hNextItem,TVGN_NEXTVISIBLE);
	}
	plog.saveLog_StaCnt(allSucesscnt,allfailcnt,DATA_FILE,TIME,"总测试项数： ");
	if(allfailcnt == 0)
         plog.saveLog_testresult(DATA_FILE,TIME,"总结果： ",DACK_SUCESS,2);
	else
	    plog.saveLog_testresult(DATA_FILE,TIME,"总结果： ",DACK_FAILURE,2);	
}


INT8U CTESTCCO_BingFChaoB::QueMeterRunSta()
{
	return m_RunFg;
}
