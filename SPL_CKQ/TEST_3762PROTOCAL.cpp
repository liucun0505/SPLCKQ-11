// TEST_3762PROTOCAL.cpp : implementation file
//

#include "stdafx.h"
#include "KD_Project.h"
#include "TEST_3762PROTOCAL.h"
#include "gPublicObjct.h"
#include "SimJZQ.h"
extern CSimJzq   gSimJzq;
#include "MainFrm.h"
#include "GW13762.h"
extern CGW13762 Cgw13762;

#include "SimMeter.h"
extern CSimMeter  gSimMeter;
#include "gPublicObjct.h"
#include "MyFunLib.h"
#include "LogFile.h"
extern CLogFile plog;//打引用

#include "CDTL645.H"
extern CDTL645  gCDtl645Op;
// CTEST_3762PROTOCAL
#define DAFNLISTCNT 9
INT8U AFNLIST[DAFNLISTCNT]={AFN01,AFN02,AFN03,AFN04,AFN05,AFN10,AFN11,AFN12,AFN13};
#define DAFN00FNCNT 2
INT16U AFN00_FNLISTBUF[DAFN00FNCNT]={F1,F2};
#define DAFN01FNCNT 3
INT16U AFN01_FNLISTBUF[DAFN01FNCNT]={F1,F2,F3};
#define DAFN02FNCNT 1
INT16U AFN02_FNLISTBUF[DAFN02FNCNT]={F1};
#define DAFN03FNCNT 11
INT16U AFN03_FNLISTBUF[DAFN03FNCNT]={F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11};
#define DAFN04FNCNT 3
INT16U AFN04_FNLISTBUF[DAFN04FNCNT]={F1,F2,F3};
#define DAFN05FNCNT 5
INT16U AFN05_FNLISTBUF[DAFN05FNCNT]={F1,F2,F3,F4,F5};
#define DAFN06FNCNT 5
INT16U AFN06_FNLISTBUF[DAFN06FNCNT]={F1,F2,F3,F4,F5};
#define DAFN10FNCNT 10
INT16U AFN10_FNLISTBUF[DAFN10FNCNT]={F1,F2,F3,F4,F5,F6,F21,F100,F101,F201};
#define DAFN11FNCNT 6
INT16U AFN11_FNLISTBUF[DAFN11FNCNT]={F1,F2,F3,F4,F5,F6};
#define DAFN12FNCNT 3
INT16U AFN12_FNLISTBUF[DAFN12FNCNT]={F1,F2,F3};
#define DAFN13FNCNT 1
INT16U AFN13_FNLISTBUF[DAFN13FNCNT]={F1};
#define DAFN14FNCNT 3
INT16U AFN14_FNLISTBUF[DAFN14FNCNT]={F1,F2,F3};
#define DAFN15FNCNT 1
INT16U AFN15_FNLISTBUF[DAFN15FNCNT]={F1};
#define DAFNF0FNCNT 3
INT16U AFNF0_FNLISTBUF[DAFNF0FNCNT]={F1,F2,F3};


IMPLEMENT_DYNAMIC(CTEST_3762PROTOCAL, CWnd)


	CTEST_3762PROTOCAL::CTEST_3762PROTOCAL()
{

}

CTEST_3762PROTOCAL::~CTEST_3762PROTOCAL()
{
}


BEGIN_MESSAGE_MAP(CTEST_3762PROTOCAL, CWnd)
END_MESSAGE_MAP()

INT16U *CTEST_3762PROTOCAL::QueAFNFNBufCnt(INT8U List,INT8U &vDstAFN,INT8U &ack,INT8U &vDstCnt)
{
	ack = DACK_SUCESS;
	INT16U *buf=NULL;
	switch(List)
	{
	case 1:
		vDstAFN=0x01;
		buf=AFN01_FNLISTBUF;
		vDstCnt=DAFN01FNCNT;
		break;
	case 2:
		vDstAFN=0x02;
		buf=AFN02_FNLISTBUF;
		vDstCnt=DAFN02FNCNT;
		break;
	case 3:
		vDstAFN=0x03;
		buf=AFN03_FNLISTBUF;
		vDstCnt=DAFN03FNCNT;
		break;
	case 4:
		vDstAFN=0x04;
		buf=AFN04_FNLISTBUF;
		vDstCnt=DAFN04FNCNT;
		break;
	case 5:
		vDstAFN=0x05;
		buf=AFN05_FNLISTBUF;
		vDstCnt=DAFN05FNCNT;
		break;
	case 6:
		vDstAFN=0x10;
		buf=AFN10_FNLISTBUF;
		vDstCnt=DAFN10FNCNT;
		break;
	case 7:
		vDstAFN=0x11;
		buf=AFN11_FNLISTBUF;
		vDstCnt=DAFN11FNCNT;
		break;
	case 8:
		vDstAFN=0x12;
		buf=AFN12_FNLISTBUF;
		vDstCnt=DAFN12FNCNT;
		break;
	case 9:
		vDstAFN=0x13;
		buf=AFN13_FNLISTBUF;
		vDstCnt=DAFN13FNCNT;
		break;
	default:
		ack = DACK_FAILURE;
		break;
	}
	return buf;
}
void CTEST_3762PROTOCAL::C3762_TEST(HTREEITEM hTree)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (!pMainDlg->m_bConnected)
	{
		AfxMessageBox(_T("请打开模拟集中器串口!"));
		return;
	}
	/*if (!pMainDlg->m_bConnected2)
	{
		AfxMessageBox(_T("请打开模拟表串口!"));
		return;
	}*/
	INT8U ack = DACK_SUCESS;
	INT8U allSucesscnt = 0;
	INT8U allfailcnt = 0;;
	INT8U resucnt=0;
	INT8U refailcnt=0;
	//pMainDlg->m_treeProject.Expand(hTree,TVE_EXPAND);//展开树节点
	HTREEITEM hNextItem = pMainDlg->m_treeProject.GetNextItem(hTree,TVGN_NEXTVISIBLE);
	CString strName;
	INT16U *AFNFNBuf;
	/*INT16U AFNFNBuf[15];*/
	INT8U AFN=0;
	INT8U FnCNT=0;
	INT8U listvalue=0;
	while (hNextItem)
	{
		strName = pMainDlg->m_treeProject.GetItemText(hNextItem);
		if (pMainDlg->m_treeProject.GetCheck(hNextItem))
		{
			listvalue=(_ttoi(strName.Mid(0,2)));
			AFNFNBuf = QueAFNFNBufCnt(listvalue,AFN,ack,FnCNT);
			if(ack== DACK_SUCESS)
			{
				//plog.saveLog_str(DATA_FILE,TIME,"开始测试："+strName);
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,m_HostNodeAddress,6);
				Cgw13762.SetMainAdd(m_HostNodeAddress);
				//plog.saveLog_testresult(PARS_FILE,TIME,"设置CCO的主节点地址 ",ack);
				ack = TEST_3762AFNMoreFN(AFN,AFNFNBuf,FnCNT);
				StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_testresult(DATA_FILE,TIME,"结果： ",ack);
				//plog.saveLog_str(DATA_FILE,TIME,"结束测试："+strName);
			}

		}
		hNextItem = pMainDlg->m_treeProject.GetNextItem(hNextItem,TVGN_NEXTVISIBLE);
	}
	//plog.saveLog_StaCnt(allSucesscnt,allfailcnt,DATA_FILE,TIME,"总测试项数： ");
	if(allfailcnt == 0)
		plog.saveLog_testresult(DATA_FILE,TIME,"总结果： ",DACK_SUCESS,2);
	else
		plog.saveLog_testresult(DATA_FILE,TIME,"总结果： ",DACK_FAILURE,2);	
}
void CTEST_3762PROTOCAL:: StaSucessCnt(INT8U ack,INT8U &allSucesscnt,INT8U &failCnt)
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
INT8U CTEST_3762PROTOCAL::Test376Pct_AFNF01(INT16U FN)
{
	INT8U AFN =0x01;
	INT8U ack = DACK_FAILURE;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	switch(FN)
	{
	case F1://--------硬件初始化

		ack =gSimJzq.HostSendRcv376_2NoBuf(AFN,FN,sQGDW376_2HostFrame,DstDecodeDataFrame);
		if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Wait3762Ack(120*100,100,DstDecodeDataFrame);//等待上报03 F10
			if(ack==DACK_SUCESS)
			{
				if((DstDecodeDataFrame.s_head.s_AFN == 0x03)&&(DstDecodeDataFrame.s_head.s_FN == F10))
				{

				}
				else
				{
					ack = DACK_FAILURE;
				}
			}
		}
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"",ack,1);
		break;
	case F2://---参数区初始化
		{
			gSimJzq.SetNodeAdd(0,5);//增加从节点信息			
			gSimJzq.CmpNodeAdd(0,5);//比较节点信息
			//ack =gSimJzq.HostSendRcv376_2NoBuf(0x10,F1,sQGDW376_2HostFrame,DstDecodeDataFrame,1);//读从节点数量
			ack =gSimJzq.HostSendRcv376_2NoBuf_NoAck(AFN,FN);//参数初始化删除节点信息
			gSimJzq.Wait3762Ack(120*1000,100,DstDecodeDataFrame);//等待120S再读节点数量
			if(ack == DACK_SUCESS)
			{
				ack =gSimJzq.HostSendRcv376_2NoBuf(0x10,F1,sQGDW376_2HostFrame,DstDecodeDataFrame,1);//读从节点数量
				if(ack == DACK_SUCESS)
				{     //判断节点数量为0
					if((DstDecodeDataFrame.s_RcvDataBuf[0]==0)&&(DstDecodeDataFrame.s_RcvDataBuf[1]==0)&&(DstDecodeDataFrame.s_RcvDataLen ==4))
					{

					}
					else
					{
						ack = DACK_FAILURE;
					}
				}
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"",ack,1);
		}
		break;
	case F3:
		ack =gSimJzq.HostSendRcv376_2NoBuf_NoAck(AFN,FN);
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"",ack,1);
		break;
	default:
		ack =DACK_EER_NO_AFNFN;
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"",ack,1);
		break;
	}
	return ack;
}
INT8U CTEST_3762PROTOCAL::Test376Pct_AFNF02(INT16U FN)
{
	INT8U AFN =0x02;
	INT8U ack;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	switch(FN)
	{
	case F1://F1：转发通信协议数据帧
		{
			INT8U tmpbuf[220];
			INT8U Amtaddbuf[7+1];
			INT8U dataBuf[250];
			//			INT8U tmp8;
			INT16U tmp16;
			INT8U recnt=0;
			BufToBuf(Amtaddbuf,&gNodeAddBuf[0][0],6);

			Amtaddbuf[6]=DPCT_97FG;
			ack = gSimJzq.ReadMeterAndCmpMter(0,Amtaddbuf,gReMeterDi[0], sQGDW376_2HostFrame,DstDecodeDataFrame);
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"645-97",ack,1);
			gSimJzq.Wait3762Ack(120*100,100,DstDecodeDataFrame);//等待
			if(ack == DACK_SUCESS)
			{
				recnt++;
			}

			Amtaddbuf[6]=DPCT_2007FG;
			ack = gSimJzq.ReadMeterAndCmpMter(0,Amtaddbuf,gReMeterDi[0], sQGDW376_2HostFrame,DstDecodeDataFrame);
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"07协议",ack,1);
			gSimJzq.Wait3762Ack(120*100,100,DstDecodeDataFrame);//等待
			if(ack == DACK_SUCESS)
			{
				recnt++;
			}
			//BufIsValue(&tmpbuf[2],200,0x33);
			tmpbuf[0]=0;
			//BufIsValue(Amtaddbuf,6,0xff);
			ack = gSimJzq.ReadMeterAndCmpMter(0,Amtaddbuf,gReMeterDi[0], sQGDW376_2HostFrame,DstDecodeDataFrame);
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"广播协议",ack,1);
			/*	tmpbuf[1]=200;
			ack = Cgw13762.Code376_2_HostBufNodeFrame(Amtaddbuf,AFN,FN,tmpbuf,202,sQGDW376_2HostFrame);
			gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen);

			gSimMeter.GetCOMM645ToBuf(250,0,10,dataBuf,tmp16);
			gSimMeter.SendBufToCom(dataBuf,tmp16);
			ack = gSimJzq.Wait3762AckCmpAFNFN(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);*/
			gSimJzq.Wait3762Ack(120*100,100,DstDecodeDataFrame);//等待
			if(ack == DACK_SUCESS)
			{
				recnt++;
			}
			if(recnt >= 2)
			{
				ack = DACK_SUCESS;
			}
			/*if((ack == DACK_SUCESS))
			{
			ack = DACK_FAILURE;
			if(DstDecodeDataFrame.s_RcvDataLen == 202)
			{
			if(CompareNBuf(DstDecodeDataFrame.s_RcvDataBuf,tmpbuf,202)==EQU)
			{
			if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[2],dataBuf,200)==EQU)
			{
			ack = DACK_SUCESS;
			}
			}
			}
			}*/

			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"透明传输",ack,1);
		}
		break;
	default:
		ack =DACK_EER_NO_AFNFN;
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"",ack,1);
		break;
	}
	return ack;
}

INT8U CTEST_3762PROTOCAL::Test376Pct_AFNF03(INT16U FN)
{
	INT8U AFN =0x03;
	INT8U ack;
	INT16U tmp16;
	INT8U tmpbuf[50];
	INT8U recnt=0;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	switch(FN)
	{
	case F1://F1：厂商代码和版本信息
		{
			ack =gSimJzq.HostSendRcv376_2NoBuf(AFN,FN,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
			if(ack==DACK_SUCESS)
			{
				if(DstDecodeDataFrame.s_RcvDataLen==9)
				{

				}
				else
				{
					ack = DACK_FAILURE;
				}
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F1：厂商代码和版本信息",ack,1);
		}
		break;
	case F2://F2：噪声值
		{
			ack =gSimJzq.HostSendRcv376_2NoBuf(AFN,FN,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
			if(ack==DACK_SUCESS)
			{
				if((DstDecodeDataFrame.s_RcvDataLen==1)&&(DstDecodeDataFrame.s_RcvDataBuf[0]==0))
				{

				}
				else
				{
					ack = DACK_FAILURE;
				}
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F2：噪声值",ack,1);
		}
		break;
	case F3://F3：从节点侦听信息
		{
			/*INT8U tmpbuf[50];*/
			tmpbuf[0]=1;
			tmpbuf[1]=1;
			ack =gSimJzq.HostSendRcv376_2Buf(AFN,FN,tmpbuf,2,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
			if(ack == DACK_EER_CCOCANNOTDO)
			{
				if((DstDecodeDataFrame.s_RcvDataLen==1)&&(DstDecodeDataFrame.s_RcvDataBuf[0]==0x0A))
				{
					ack = DACK_SUCESS;
				}
				else
				{
					ack = DACK_FAILURE;
				}
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F3：从节点侦听信息",ack,1);
		}
		break;
	case F4://F4：主节点地址
		{
			//INT8U tmpbuf[50];

			for(INT8U m=0; m<6; m++)
			{
				tmpbuf[m] = m;
			}
			ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,tmpbuf,6);
			if(ack==DACK_SUCESS)
			{
				ack =gSimJzq.HostSendRcv376_2NoBuf(AFN,FN,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
				if((DstDecodeDataFrame.s_RcvDataLen==6) &&(CompareNBuf(DstDecodeDataFrame.s_RcvDataBuf,m_HostNodeAddress,6)==EQU))
				{
					ack = DACK_SUCESS;
				}
				else
				{
					ack = DACK_FAILURE;
				}
			}
			if(ack==DACK_SUCESS)
			{
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,tmpbuf,6);
			}
			if(ack==DACK_SUCESS)
			{
				ack =gSimJzq.HostSendRcv376_2NoBuf(AFN,FN,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
				if(ack==DACK_SUCESS)
				{
					ack = DACK_FAILURE;
					if((DstDecodeDataFrame.s_RcvDataLen==6) &&(CompareNBuf(DstDecodeDataFrame.s_RcvDataBuf,tmpbuf,6)==EQU))
					{
						ack=DACK_SUCESS;
					}
					else
					{
						ack = DACK_FAILURE;
					}
				}
			}
			ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,m_HostNodeAddress,6);

			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F4：主节点地址",ack,1);
		}
		break;
	case F5://F5：主节点状态字和通信速率
		//INT8U tmpbuf[50];
		tmpbuf[0]=1;
		tmpbuf[1]=1;
		ack =gSimJzq.HostSendRcv376_2NoBuf(AFN,FN,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
		if(ack==DACK_SUCESS)
		{
			ack = DACK_FAILURE;
			if(DstDecodeDataFrame.s_RcvDataLen == 4)
			{
				if(((DstDecodeDataFrame.s_RcvDataBuf[0]>>6) ==0x00) && (((DstDecodeDataFrame.s_RcvDataBuf[0]>>4)&0x02) ==0x02))
				{
					ack=DACK_SUCESS;
				}
			}

		}
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F5：主节点状态字和通信速率",ack,1);
		break;
	case F6://F6：主节点干扰状态
		tmpbuf[0]=0;
		ack =gSimJzq.HostSendRcv376_2Buf(AFN,FN,tmpbuf,1,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
		if(ack==DACK_SUCESS)
		{
			if((DstDecodeDataFrame.s_RcvDataLen==1)&&(DstDecodeDataFrame.s_RcvDataBuf[0]==0))
			{

			}
			else
			{
				ack = DACK_FAILURE;
			}
		}
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F6：主节点干扰状态",ack,1);
		break;
	case F7://F7：读取从节点监控最大超时时间
		{
			ack =gSimJzq.HostSendRcv376_2NoBuf(AFN,FN,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
			if(ack==DACK_SUCESS)
			{
				ack = DACK_FAILURE;
				if((DstDecodeDataFrame.s_RcvDataLen==1))
				{
					//tmp16=Buf2ToHex16(DstDecodeDataFrame.s_RcvDataBuf);
					if((DstDecodeDataFrame.s_RcvDataBuf[0] <= 120) && (DstDecodeDataFrame.s_RcvDataBuf[0] >= 60))
					{
						ack=DACK_SUCESS;
					}
				}
			}
			for(INT8U i=0; i<5; i++)
			{
				if(ack==DACK_SUCESS)
				{
					tmpbuf[0] = 60 + i*10;
					ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F4,tmpbuf,1);
				}
				if(ack==DACK_SUCESS)
				{
					ack = DACK_FAILURE;
					if((DstDecodeDataFrame.s_RcvDataLen==1))
					{
						ack =gSimJzq.HostSendRcv376_2NoBuf(AFN,FN,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
						if((DstDecodeDataFrame.s_RcvDataBuf[0] <= 120) && (DstDecodeDataFrame.s_RcvDataBuf[0] >= 60) && (DstDecodeDataFrame.s_RcvDataBuf[0] == tmpbuf[0]))
						{
							ack=DACK_SUCESS;
						}
					}

				}
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F7：读取从节点监控最大超时时间",ack,1);
		}
		break;
	case F8://F8：查询无线通信参数
		{
			ack =gSimJzq.HostSendRcv376_2NoBuf(AFN,FN,sQGDW376_2HostFrame,DstDecodeDataFrame);
			if(ack==DACK_SUCESS)
			{
				ack = DACK_FAILURE;
				if((DstDecodeDataFrame.s_head.s_AFN ==0x00)&&(DstDecodeDataFrame.s_head.s_FN ==F2))
				{
					if(DstDecodeDataFrame.s_RcvDataBuf[0]==DACK_EER_CCOCANNOTDO)
					{
						ack=DACK_SUCESS;
					}
				}

			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F8：查询无线通信参数",ack,1);
		}
		break;
	case F9://F9：通信延时相关广播延时
		{
			INT8U Amtaddbuf[7+1];
			INT8U DataBuf[200];
			INT8U tmp8;
			//INT8U recnt=0;
			BufIsValue(Amtaddbuf,6,0x99);
			sDtl2007_Read  vDst645CmdData;
			CodeReadDataCmd(0x00010000,Amtaddbuf,0,vDst645CmdData);
			DataBuf[0]=0x00;
			DataBuf[1]=vDst645CmdData.s_vDstCmdLen;
			BufToBuf(&DataBuf[2],vDst645CmdData.s_pDstCmdBuf,vDst645CmdData.s_vDstCmdLen);
			for(INT8U m =0; m<3;m++)
			{
				if(m==1)
				{
					DataBuf[0]=0x02;
				}
				ack =gSimJzq.HostSendRcv376_2Buf(AFN,FN,DataBuf,vDst645CmdData.s_vDstCmdLen+2,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
				if(ack==DACK_SUCESS)
				{
					ack = DACK_FAILURE;
					if(DstDecodeDataFrame.s_RcvDataLen == vDst645CmdData.s_vDstCmdLen+2+2)
					{
						if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[2],DataBuf,vDst645CmdData.s_vDstCmdLen+2)==EQU)
						{
							ack=DACK_SUCESS;
							recnt++;
						}
					}
				}

			}

			gCDtl645Op.CodeReadData97(0x9010,Amtaddbuf,&DataBuf[2],tmp8);
			DataBuf[0]=0x00;
			DataBuf[1]=tmp8;
			for(INT8U m =0; m<3;m++)
			{
				if(m==2)
				{
					DataBuf[0]=0x01;
				}
				ack =gSimJzq.HostSendRcv376_2Buf(AFN,FN,DataBuf,tmp8+2,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
				if(ack==DACK_SUCESS)
				{
					ack = DACK_FAILURE;
					if(DstDecodeDataFrame.s_RcvDataLen == tmp8+2+2)
					{
						if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[2],DataBuf,tmp8+2)==EQU)
						{
							ack=DACK_SUCESS;
							recnt++;
						}
					}
				}
			}

			if(recnt==6)
			{
				ack=DACK_SUCESS;
			}
			else
			{
				ack = DACK_FAILURE; 
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F9：通信延时相关广播延时",ack,1);
		}
		break;
	case F10://F10：本地模块运行模式
		{
			ack =gSimJzq.HostSendRcv376_2NoBuf(AFN,FN,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
			if(ack==DACK_SUCESS)
			{
				ack = DACK_FAILURE;
				if((DstDecodeDataFrame.s_RcvDataLen==41))
				{

					ack=DACK_SUCESS;

				}

			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F10：本地模块运行模式",ack,1);
		}
		break;
	case F11://F11：本地模块I376.2支持信息
		{
			INT8U tpbuf[15]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x10,0x11,0x12,0x13,0x14,0x15,0xF0,0xF1};			
			for(INT8U i=0; i<15; i++)
			{
				ack =gSimJzq.HostSendRcv376_2Buf(AFN,FN,&tpbuf[i],1,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
				if(ack==DACK_SUCESS)
				{
					ack = DACK_FAILURE;
					if((DstDecodeDataFrame.s_RcvDataLen==33))
					{
						ack = DACK_SUCESS;
					}

				}

			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F11：本地模块I376.2支持信息",ack,1);
		}
		break;
	default:
		ack =DACK_EER_NO_AFNFN;
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"",ack,1);
		break;
	}
	return ack;
}

INT8U CTEST_3762PROTOCAL::Test376Pct_AFNF04(INT16U FN)
{
	INT8U AFN =0x04;
	INT8U ack;
	//	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	switch(FN)
	{
	case F1://F1：发送测试
		{
			INT8U tmpbuf[50];
			tmpbuf[0]=0;
			ack=gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,tmpbuf,1);
			if(ack==DACK_SUCESS)
			{
				tmpbuf[0]=0;
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,tmpbuf,1);
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F1：发送测试",ack,1);
		}
		break;
	case F2://F2：从节点点名

		ack=gSimJzq.HostSendRcv376_2NoBuf_NoAck(AFN,FN);
		if(ack == DACK_EER_NO_AFNFN)//AFN不存在
		{
			ack = DACK_SUCESS;
		}
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F2：从节点点名",ack,1);
		break;
	case F3://F3：本地通信模块报文通信测试
		{
			gSimMeter.SetSimMeterRunFg(0);
			gSimMeter.ClrSimMeterComData();
			INT8U Amtaddbuf[7+1];
			INT8U DataBuf[200];
			INT8U tmpbuf[250];
			INT8U tmp8;
			INT8U recnt=0;
			INT16U tmp16;
			BufToBuf(Amtaddbuf,&gNodeAddBuf[0][0],6);
			Amtaddbuf[6]=0x01;
			sDtl2007_Read  vDst645CmdData;

			DataBuf[0]=0x00;
			BufToBuf(&DataBuf[1],Amtaddbuf,6);

			//-------07-------------
			CodeReadDataCmd(0x00000100,Amtaddbuf,0,vDst645CmdData);
			DataBuf[7]=0x02;
			DataBuf[8]=vDst645CmdData.s_vDstCmdLen;
			BufToBuf(&DataBuf[9],vDst645CmdData.s_pDstCmdBuf,vDst645CmdData.s_vDstCmdLen);
			ack=gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,DataBuf,vDst645CmdData.s_vDstCmdLen+9);

			if(ack==DACK_SUCESS)
			{
				ack=DACK_FAILURE;
				gSimMeter.GetCOMM645ToBuf(250,1000,10,tmpbuf,tmp16);
				if(vDst645CmdData.s_vDstCmdLen ==tmp16)
				{
					if(CompareNBuf(tmpbuf,&DataBuf[9],tmp16) == EQU)
					{
						ack=DACK_SUCESS;
						recnt++;
						plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"645-07",ack,1);
					}
				}
			}
			//-------97-------------
			//if(ack==DACK_SUCESS)
			{
				gCDtl645Op.CodeReadData97(0x9010,Amtaddbuf,&DataBuf[9],tmp8);
				DataBuf[7]=0x01;
				DataBuf[8]=tmp8;
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,DataBuf,tmp8+9);

				gSimJzq.Wait3762Ack(120*100,100,DstDecodeDataFrame);//等待
				if(ack==DACK_SUCESS)
				{
					ack=DACK_FAILURE;
					gSimMeter.GetCOMM645ToBuf(250,1000,10,tmpbuf,tmp16);
					if(tmp8 ==tmp16)
					{
						if(CompareNBuf(tmpbuf,&DataBuf[9],tmp16) == EQU)
						{
							ack=DACK_SUCESS;
							recnt++;
							plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"645-97",ack,1);
						}
					}
				}
			}

			//if(ack==DACK_SUCESS)
			{
				DataBuf[7]=0x00;
				DataBuf[8]=100;
				BufIs0(&DataBuf[9],100);
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,DataBuf,DataBuf[8]+9);
				gSimJzq.Wait3762Ack(120*100,100,DstDecodeDataFrame);//等待

				if(ack==DACK_SUCESS)
				{
					ack=DACK_FAILURE;
					gSimMeter.GetCOMM645ToBuf(250,2000,10,tmpbuf,tmp16);
					if(100 ==tmp16)
					{
						if(CompareNBuf(tmpbuf,&DataBuf[9],tmp16) == EQU)
						{
							ack=DACK_SUCESS;
							recnt++;
							plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"透明传输",ack,1);
						}
					}
				}
			}
			if(recnt == 3)
			{
				ack = DACK_SUCESS;
			}
			gSimMeter.SetSimMeterRunFg(1);
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F3：本地通信模块报文通信测试",ack,1);
		}
		break;
	default:
		ack =DACK_EER_NO_AFNFN;
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"",ack,1);
		break;
	}
	return ack;
}
INT8U CTEST_3762PROTOCAL::Test376Pct_AFNF05(INT16U FN)
{
	INT8U AFN =0x05;
	INT8U ack;
	INT8U tmpbuf[50];
	INT8U recnt=0;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	switch(FN)
	{
	case F1://F1：设置主节点地址
		{

			//INT8U tmpbuf[50];

			for(INT8U m=0; m<6; m++)
			{
				tmpbuf[m] = m;
			}
			ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,m_HostNodeAddress,6);
			if((ack==DACK_SUCESS) || (ack==DACK_EER_CCOADD_REPEAT))
			{
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,tmpbuf,6);
			}
			if(ack==DACK_SUCESS)
			{
				for(INT8U i=0; i<5; i++)
				{
					ack =gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,tmpbuf,6);
					if((ack==DACK_SUCESS) || (ack==DACK_EER_CCOADD_REPEAT))
					{
						ack = DACK_SUCESS;
					}
				}
			}
			if(ack==DACK_SUCESS)
			{
				BufIsValue(tmpbuf,6,0);
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,tmpbuf,6);
				if(ack == DACK_ERR_FORMAT )
				{
					ack=DACK_SUCESS;
				}
			}

			if(ack==DACK_SUCESS)
			{
				BufIsValue(tmpbuf,6,0x99);
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,tmpbuf,6);
				/*if(ack == DACK_EER_INVALID )
				{
				ack=DACK_SUCESS;
				}*/
			}
			if(ack==DACK_SUCESS)
			{
				BufIsValue(tmpbuf,6,0xFF);
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,tmpbuf,6);
				if(ack == DACK_ERR_FORMAT )
				{
					ack=DACK_SUCESS;
				}
			}
			if(ack==DACK_SUCESS)
			{
				BufIsValue(tmpbuf,6,0x1F);
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,tmpbuf,6);
				if(ack == DACK_ERR_FORMAT )
				{
					ack=DACK_SUCESS;
				}
				BufIsValue(&tmpbuf[1],5,0x0);
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,tmpbuf,6);
				if(ack == DACK_ERR_FORMAT )
				{
					ack=DACK_SUCESS;
				}
			}
			gSimJzq.HostSendRcv376_2Buf_NoAck(0x05,F1,m_HostNodeAddress,6);


			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F1：设置主节点地址",ack,1);
		}
		break;
	case F2://F2：允许/禁止从节点上报
		{
			//INT8U tmpbuf[50];
			tmpbuf[0] = 0;
			ack=gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,tmpbuf,1);
			if(ack==DACK_SUCESS)
			{
				tmpbuf[0] = 1;
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,tmpbuf,1);
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F2：允许/禁止从节点上报",ack,1);
		}
		break;
	case F3://F3：启动广播
		{
			INT8U Amtaddbuf[7+1];
			INT8U DataBuf[200];
			INT8U tmp8;
			//INT8U recnt=0;
			BufIsValue(Amtaddbuf,6,0x99);
			sDtl2007_Read  vDst645CmdData;
			CodeReadDataCmd(0x00000100,Amtaddbuf,0,vDst645CmdData);
			DataBuf[0]=0x00;
			DataBuf[1]=vDst645CmdData.s_vDstCmdLen;
			BufToBuf(&DataBuf[2],vDst645CmdData.s_pDstCmdBuf,vDst645CmdData.s_vDstCmdLen);
			ack =gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,DataBuf,vDst645CmdData.s_vDstCmdLen+2);
			if(ack==DACK_SUCESS)
			{
				recnt++;
			}
			DataBuf[0]=0x01;
			ack =gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,DataBuf,vDst645CmdData.s_vDstCmdLen+2);

			if(ack==DACK_SUCESS)
			{
				recnt++;

			}
			DataBuf[0]=0x02;
			ack =gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,DataBuf,vDst645CmdData.s_vDstCmdLen+2);
			if(ack==DACK_SUCESS)
			{
				recnt++;

			}
			gCDtl645Op.CodeReadData97(0x9010,Amtaddbuf,&DataBuf[2],tmp8);
			DataBuf[0]=0x00;
			DataBuf[1]=tmp8;
			ack =gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,DataBuf,tmp8+2);
			if(ack==DACK_SUCESS)
			{
				recnt++;

			}
			DataBuf[0]=0x01;
			ack =gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,DataBuf,tmp8+2);
			if(ack==DACK_SUCESS)
			{
				recnt++;

			}

			DataBuf[0]=0x02;
			ack =gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,DataBuf,tmp8+2);
			if(ack==DACK_SUCESS)
			{
				recnt++;

			}
			if(ack == DACK_EER_CCO_BUSY)
			{
				recnt = 6;
			}
			if(recnt==6)
			{
				ack=DACK_SUCESS;
			}
			else
			{
				ack = DACK_FAILURE; 
			}

			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F3：启动广播",ack,1);
		}
		break;
	case F4://F4：设置从节点监控最大超时时间
		{
			/*INT8U tmpbuf[50];
			INT8U recnt=0;*/

			for(INT8U m=0; m<8; m++)
			{
				tmpbuf[0] =m*50;
				/*tmpbuf[0] = (INT8U)tmp16;
				tmpbuf[1] = (INT8U)(tmp16>>8);*/
				ack=gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,tmpbuf,1);
				if(ack==DACK_SUCESS)
				{
					ack =gSimJzq.HostSendRcv376_2NoBuf(0x03,F7,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
					if(ack == DACK_SUCESS)
					{

						if((DstDecodeDataFrame.s_RcvDataLen==1) &&(CompareNBuf(DstDecodeDataFrame.s_RcvDataBuf,tmpbuf,1)==EQU))
						{
							recnt++;
						}
					}
					else
					{
						/*if((tmp16==0) ||(tmp16>300))
						{
						recnt++;
						}*/
					}
				}
			}
			if(recnt==8)
			{
				ack=DACK_SUCESS;
			}
			else
			{
				ack = DACK_FAILURE; 
			}

			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F4：设置从节点监控最大超时时间",ack,1);
		}
		break;
	case F5://F5：设置无线通信参数
		{
			//INT8U tmpbuf[50];
			tmpbuf[0]=1;
			tmpbuf[1]=1;
			ack=gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,tmpbuf,2);
			if(ack==DACK_EER_CCOCANNOTDO)
			{
				ack = DACK_SUCESS;
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F5：设置无线通信参数",ack,1);
		}
		break;

	default:
		ack =DACK_EER_NO_AFNFN;
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"",ack,1);
		break;
	}
	return ack;
}

INT8U CTEST_3762PROTOCAL::Test376Pct_AFNF10(INT16U FN)
{
	INT8U AFN =0x10;
	INT8U ack;
	INT8U tmpbuf[50];
	INT16U allcnt = 0;
	INT16U reacnt = 0;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	switch(FN)
	{
	case F1://F1：从节点数量
		{
			ack =gSimJzq.Router_PaRst();
			gSimJzq.Wait3762Ack(120*100,100,DstDecodeDataFrame);//等待
			if(ack == DACK_SUCESS)
			{
				gSimJzq.SetNodeAdd(0,5);
			}
			if(ack == DACK_SUCESS)
			{
				gSimJzq.CmpNodeAdd(0,5);//比较节点信息
			}
			if(ack == DACK_SUCESS)
			{
				ack =gSimJzq.HostSendRcv376_2NoBuf(0x10,F1,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
				if(ack == DACK_SUCESS)
				{
					ack = DACK_FAILURE; 
					if((DstDecodeDataFrame.s_RcvDataBuf[0]==5)&&(DstDecodeDataFrame.s_RcvDataBuf[1]==0)&&(DstDecodeDataFrame.s_RcvDataLen ==4))
					{
						ack = DACK_SUCESS;
					}
				}
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F1：从节点数量\n",ack,1);
		}
		break;
	case F2://F2：从节点信息
		ack =gSimJzq.Router_PaRst();
		Sleep(30000);////等待
		if(ack == DACK_SUCESS)
		{
			gSimJzq.SetNodeAdd(0,5);
		}
		if(ack == DACK_SUCESS)
		{
			ack =gSimJzq.CmpNodeAdd(0,5);
		}
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F2：从节点信息\n",ack,1);
		break;
	case F3://F3：指定从节点的上一级中继路由信息

		ack = gSimJzq.HostSendRcv376_2Buf(AFN,FN,&gNodeAddBuf[0][0],6,sQGDW376_2HostFrame,DstDecodeDataFrame);
		if(ack == DACK_SUCESS)
		{

		}
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F3：指定从节点的上一级中继路由信息\n",ack,1);
		break;
	case F4://F4：路由运行状态
		ack =gSimJzq.HostSendRcv376_2NoBuf(AFN,FN,sQGDW376_2HostFrame,DstDecodeDataFrame);
		if(ack == DACK_SUCESS)
		{

		}
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F4：路由运行状态\n",ack,1);
		break;
	case F5://F5：未抄读成功的从节点信息
		{			
			tmpbuf[0]=01;
			tmpbuf[1]=0;
			tmpbuf[2]=0x05;
			gSimJzq.SetNodeAdd(0,5);
			ack = gSimJzq.HostSendRcv376_2Buf(AFN,FN,tmpbuf,3,sQGDW376_2HostFrame,DstDecodeDataFrame);
			if(ack == DACK_SUCESS)
			{

			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F5：未抄读成功的从节点信息\n",ack,1);
		}
		break;
	case F6:
		{
			tmpbuf[0]=01;
			tmpbuf[1]=0;
			tmpbuf[2]=0x05;
			//gSimJzq.SetNodeAdd(0,5);
			ack = gSimJzq.HostSendRcv376_2Buf(AFN,FN,tmpbuf,3,sQGDW376_2HostFrame,DstDecodeDataFrame);
			if((ack == DACK_SUCESS) || (ack == DACK_ERR_NODE_NOFIND))
			{
				ack = DACK_SUCESS;
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F6：主动注册的从节点信息\n",ack,1);
		}
		break;
	case F21:
		{			
			ack = gSimJzq.QueNodeCnt(allcnt);
			if((ack == DACK_SUCESS))
			{
				for(INT16U m=1; m<allcnt; m++)
				{
					Hex16ToBuf2(m,tmpbuf);
					tmpbuf[2]=1;
					//gSimJzq.SetNodeAdd(0,5);
					ack = gSimJzq.HostSendRcv376_2Buf(AFN,FN,tmpbuf,3,sQGDW376_2HostFrame,DstDecodeDataFrame);
					if(ack == DACK_SUCESS)
					{
						reacnt++;
					}
				}
				if((reacnt+1) == allcnt)
				{
					ack = DACK_SUCESS;
				}
				else
				{
					ack = DACK_FAILURE;
				}
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F21：节点拓扑信息\n",ack,1);
		}
		break;
	case F100:
		{
			ack = gSimJzq.QueNodeCnt(allcnt);
			if(ack == DACK_SUCESS)
			{
				ack =gSimJzq.HostSendRcv376_2NoBuf(AFN,FN,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
				if(ack == DACK_SUCESS)
				{
					ack = DACK_FAILURE;
					if(allcnt == Buf2ToHex16(DstDecodeDataFrame.s_RcvDataBuf))
					{
						ack = DACK_SUCESS;
					}
				}
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F100：查询网络规模\n",ack,1);
		}
		break;
	case F101:
		{
			ack = gSimJzq.QueNodeCnt(allcnt);
			if((ack == DACK_SUCESS))
			{
				for(INT16U m=0; m<allcnt; m++)
				{
					Hex16ToBuf2(m,tmpbuf);
					tmpbuf[2]=1;
					//gSimJzq.SetNodeAdd(0,5);
					ack = gSimJzq.HostSendRcv376_2Buf(AFN,FN,tmpbuf,3,sQGDW376_2HostFrame,DstDecodeDataFrame);
					if(ack == DACK_SUCESS)
					{
						reacnt++;
					}
				}
				if(reacnt == allcnt)
				{
					ack = DACK_SUCESS;
				}
				else
				{
					ack = DACK_FAILURE;
				}
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F101：从节点版本信息\n",ack,1);
		}
		break;
	case F201:		
		{
			ack = gSimJzq.QueNodeCnt(allcnt);
			if((ack == DACK_SUCESS))
			{
				for(INT16U m=1; m<allcnt; m++)
				{
					Hex16ToBuf2(m,tmpbuf);
					tmpbuf[2] = 1;
					ack = gSimJzq.HostSendRcv376_2Buf(0x10,F2,tmpbuf,3,sQGDW376_2HostFrame,DstDecodeDataFrame);
					if(ack == DACK_SUCESS)
					{
						ack = gSimJzq.HostSendRcv376_2Buf(AFN,FN,&DstDecodeDataFrame.s_RcvDataBuf[3],6,sQGDW376_2HostFrame,DstDecodeDataFrame);					
					}
				}
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F201：从节点状态\n",ack,1);
		}
		break;
	default:
		ack =DACK_EER_NO_AFNFN;
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"",ack,1);
		break;
	}
	return ack;
}
INT8U CTEST_3762PROTOCAL::Test376Pct_AFNF11(INT16U FN)
{
	INT8U AFN =0x11;
	INT8U ack;
	INT16U tmp16;
	INT8U tmpbuf[50];
	//sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	switch(FN)
	{
	case F1://F1：添加从节点
		{
			ack =gSimJzq.Router_PaRst();
			//if(ack == DACK_SUCESS)
			{
				ack =gSimJzq.SetNodeAdd(0,5);
			}
			//if(ack == DACK_SUCESS)
			{
				ack =gSimJzq.CmpNodeAdd(0,5);
			}
			//if(ack == DACK_SUCESS)
			{
				//全0结点
				tmpbuf[0] = 0x01;
				BufIsValue(&tmpbuf[1],7,0x00);
				ack =gSimJzq. HostSendRcv376_2Buf_NoAck(0x11,F1,tmpbuf,1*7+1);
				if(ack == DACK_ERR_FORMAT)
				{
					ack = DACK_SUCESS;
				}
				else
				{
					ack = DACK_FAILURE;
				}
				plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"全0结点",ack,1);
				//----------------------------------------------
				BufIsValue(&tmpbuf[1],7,0x99);
				ack =gSimJzq. HostSendRcv376_2Buf_NoAck(0x11,F1,tmpbuf,1*7+1);
				if(ack == DACK_EER_MNODE_FOMFATBROAD)
				{
					ack = DACK_SUCESS;
				}
				else
				{
					ack = DACK_FAILURE;
				}
				plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"广播结点",ack,1);

				//----------------------------------------------
				BufIsValue(&tmpbuf[1],7,0xEE);
				ack =gSimJzq. HostSendRcv376_2Buf_NoAck(0x11,F1,tmpbuf,1*7+1);
				if(ack == DACK_EER_MNODE_FOMFATNOBCD)
				{
					ack = DACK_SUCESS;
				}
				else
				{
					ack = DACK_FAILURE;
				}
				plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"非BCD结点",ack,1);

				//----------------------------------------------
				for(INT8U m=0;m<6;m++)
				{
					tmpbuf[m+1]=m;
				}
				tmpbuf[7]=0x09;
				ack =gSimJzq. HostSendRcv376_2Buf_NoAck(0x11,F1,tmpbuf,1*7+1);
				if(ack == DACK_EER_PCT)
				{
					ack = DACK_SUCESS;
				}
				else
				{
					ack = DACK_FAILURE;
				}
				plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"协议错结点",ack,1);
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F1：添加从节点",ack,1);
		}
		break;
	case F2://F2：删除从节点
		{
			//INT8U tmpbuf[50];

			//ack =gSimJzq.Router_PaRst();
			//if(ack == DACK_SUCESS)
			{
				ack =gSimJzq.SetNodeAdd(0,5);
			}
			//if(ack == DACK_SUCESS)
			{
				tmpbuf[0]=1;
				//tmpbuf[1]=0;
				BufToBuf(&tmpbuf[1],&gNodeAddBuf[4][0],6);
				ack = gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,tmpbuf,7);
				if(ack == DACK_SUCESS)
				{
					ack = gSimJzq.QueNodeCnt(tmp16);
				}
				if(ack == DACK_SUCESS)
				{
					if(tmp16 != 4)
					{
						ack = DACK_FAILURE;
					}
				}
			}

			if(ack == DACK_SUCESS)
			{
				ack =gSimJzq.CmpNodeAdd(0,4);
			}
			//删掉不存在节点
			if(ack == DACK_SUCESS)
			{
				tmpbuf[0]=1;
				//tmpbuf[1]=0;
				BufToBuf(&tmpbuf[1],&gNodeAddBuf[4][0],6);
				ack = gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,tmpbuf,7);
				if(ack == DACK_EER_MNODE_NOFIND)
				{
					ack = DACK_SUCESS;
				}
				else
				{
					ack = DACK_FAILURE;
				}
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F2：删除从节点",ack,1);
		}
		break;
	case F3://F3：设置从节点固定中继路径
		{
			//INT8U tmpbuf[50];
			BufToBuf(&tmpbuf[0],&gNodeAddBuf[4][0],6);
			tmpbuf[7]=0;
			ack = gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,tmpbuf,8);
			if(ack == DACK_EER_CCOCANNOTDO)
			{
				ack = DACK_SUCESS;
			}
			else
			{
				ack = DACK_FAILURE;
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F3：设置从节点固定中继路径",ack,1);
		}
		break;
	case F4://F4：设置工作模式
		{
			//INT8U tmpbuf[50];
			BufIs0(tmpbuf,3);
			ack = gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,tmpbuf,3);
			if(ack == DACK_EER_CCOCANNOTDO)
			{
				ack = DACK_SUCESS;
			}
			else
			{
				ack = DACK_FAILURE;
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F4：设置工作模式",ack,1);
		}
		break;
	case F5://F5：激活从节点主动注册
		{
			//INT8U tmpbuf[50];
			tmpbuf[0]=0x00;
			tmpbuf[1]=0x00;
			tmpbuf[2]=0x01;
			tmpbuf[3]=0x01;
			tmpbuf[4]=0x10;
			tmpbuf[5]=0x16;
			Hex16ToBuf2(200,&tmpbuf[6]);
			tmpbuf[8]=0x00;
			tmpbuf[9]=0x00;
			ack = gSimJzq.HostSendRcv376_2Buf_NoAck(AFN,FN,tmpbuf,10);
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F5：激活从节点主动注册",ack,1);
		}
		break;
	case F6://F6：终止从节点主动注册
		{
			ack = gSimJzq.HostSendRcv376_2NoBuf_NoAck(AFN,FN);
			ack = gSimJzq.Wait3762Ack(120*1000,100,DstDecodeDataFrame);//等待上报06 F3路由工矿变动
			if(ack==DACK_SUCESS)
			{
				if((DstDecodeDataFrame.s_head.s_AFN == 0x06)&&(DstDecodeDataFrame.s_head.s_FN == F3))
				{

				}
				else
				{
					ack = DACK_FAILURE;
				}
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F6：终止从节点主动注册",ack,1);
		}
		break;

	default:
		ack =DACK_EER_NO_AFNFN;
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"",ack,1);
		break;
	}
	return ack;
}
INT8U CTEST_3762PROTOCAL::Test376Pct_AFNF12(INT16U FN)
{
	INT8U AFN =0x12;
	INT8U ack;
	//	INT16U tmp16;

	switch(FN)
	{
	case F1://F1：重启
		ack =gSimJzq.Router_Start();
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F1：重启",ack,1);
		break;
	case F2://F2：暂停
		ack =gSimJzq.Router_Stop();
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F2：暂停",ack,1);
		break;
	case F3://F3：恢复
		ack =gSimJzq.Router_Resume();
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"F3：恢复",ack,1);
		break;
	default:
		ack =DACK_EER_NO_AFNFN;
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"",ack,1);
		break;
	}
	return ack;
}

INT8U CTEST_3762PROTOCAL::Test376Pct_AFNF13(INT16U FN)
{
	INT8U AFN =0x13;
	INT8U ack;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	switch(FN)
	{
	case F1://F1：转发通信协议数据帧
		{
			INT8U tmpbuf[220];
			INT8U Amtaddbuf[7+1];
			INT8U dataBuf[250];
			//			INT8U tmp8;
			INT16U tmp16;
			INT8U recnt=0;
			BufToBuf(Amtaddbuf,&gNodeAddBuf[0][0],6);

			Amtaddbuf[6]=DPCT_97FG;
			ack = gSimJzq.ReadMeterAndCmpMter(1,Amtaddbuf,gReMeterDi[0], sQGDW376_2HostFrame,DstDecodeDataFrame);
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"645-97",ack,1);
			gSimJzq.Wait3762Ack(120*100,100,DstDecodeDataFrame);//等待
			if(ack == DACK_SUCESS)
			{
				recnt++;
			}

			Amtaddbuf[6]=2;
			ack = gSimJzq.ReadMeterAndCmpMter(1,Amtaddbuf,gReMeterDi[0], sQGDW376_2HostFrame,DstDecodeDataFrame);
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"07协议",ack,1);
			gSimJzq.Wait3762Ack(120*100,100,DstDecodeDataFrame);//等待
			if(ack == DACK_SUCESS)
			{
				recnt++;
			}

			BufIsValue(&tmpbuf[4],200,0x33);
			tmpbuf[0]=0;
			tmpbuf[1]=0;
			tmpbuf[2]=0;
			tmpbuf[3]=200;
			ack = Cgw13762.Code376_2_HostBufNodeFrame(Amtaddbuf,AFN,FN,tmpbuf,200+4,sQGDW376_2HostFrame);
			gSimJzq.SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen);
			gSimJzq.Wait3762Ack(150*1000,100,DstDecodeDataFrame);//等待

			gSimMeter.GetCOMM645ToBuf(250,4000,10,dataBuf,tmp16);
			//gSimMeter.SendBufToCom(dataBuf,tmp16);
			//ack = gSimJzq.Wait3762AckCmpAFNFN(10000 ,1000 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
			//gSimJzq.Wait3762Ack(120*100,100,DstDecodeDataFrame);//等待
			//if((ack == DACK_SUCESS))
			{
				ack = DACK_FAILURE;
				if(tmp16 == 200+4)
				{
					if(CompareNBuf(dataBuf,&tmpbuf[4],200)==EQU)
					{
						if(CompareNBuf(dataBuf,dataBuf,200)==EQU)
						{
							ack = DACK_SUCESS;
							recnt++;
						}
					}
				}
			}
			if(recnt >= 2)
			{
				ack = DACK_SUCESS;
			}
			plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"透明传输",ack,1);
		}
		break;
	default:
		ack =DACK_EER_NO_AFNFN;
		plog.saveLog_testresult_AfnFn(AFN,FN,DATA_FILE,TIME,"",ack,1);
		break;
	}
	return ack;
}
INT8U CTEST_3762PROTOCAL::TEST_3762AFNFN(INT8U AFN,INT16U FN)
{

	INT8U ack;
	switch(AFN)
	{
	case AFN01:
		ack=Test376Pct_AFNF01(FN);
		break;
	case AFN02:
		ack=Test376Pct_AFNF02(FN);
		break;
	case AFN03:

		ack=Test376Pct_AFNF03(FN);
		break;
	case AFN04:

		ack=Test376Pct_AFNF04(FN);
		break;
	case AFN05:

		ack=Test376Pct_AFNF05(FN);
		break;
	case AFN10:
		ack=Test376Pct_AFNF10(FN);
		break;
	case AFN11:
		ack=Test376Pct_AFNF11(FN);
		break;
	case AFN12:
		ack=Test376Pct_AFNF12(FN);
		break;
	case AFN13:
		ack=Test376Pct_AFNF13(FN);
		break;
	default:
		ack =DACK_EER_NO_AFNFN;
		break;
	}

	return ack;
}

INT8U CTEST_3762PROTOCAL::TEST_3762AFNMoreFN(INT8U AFN,INT16U *vSrcFnBuf,INT8U vSrcFnCnt)
{
	INT8U succnt=0;
	INT8U failcnt=0;
	INT8U ack;
	for(INT8U m=0; m<vSrcFnCnt;m++)
	{
		ack=TEST_3762AFNFN(AFN,vSrcFnBuf[m]);
		if(ack == DACK_SUCESS)
		{
			succnt++;
		}
		else
		{
			failcnt++;
		}
	}

	plog.saveLog_StaCnt(succnt,failcnt,DATA_FILE,TIME,"",1);

	if(failcnt==0)
	{
		return DACK_SUCESS;
	}
	else
	{
		return DACK_FAILURE;
	}
}
