// TESTCCO_AFN14.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTCCO_AFN14.h"

#include "ImitateMeterDlg.h"

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

#include "CDTL645.H"
extern CDTL645  gCDtl645Op;

IMPLEMENT_DYNAMIC(CTESTCCO_AFN14, CWnd)

CTESTCCO_AFN14::CTESTCCO_AFN14()
{

}

CTESTCCO_AFN14::~CTESTCCO_AFN14()
{
}


BEGIN_MESSAGE_MAP(CTESTCCO_AFN14, CWnd)
END_MESSAGE_MAP()
void CTESTCCO_AFN14::C3762_TEST(HTREEITEM hTree)
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
	INT16U allSucesscnt = 0;
	INT16U allfailcnt = 0;;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	pMainDlg->m_treeProject.Expand(hTree,TVE_EXPAND);//展开树节点
	HTREEITEM hNextItem = pMainDlg->m_treeProject.GetNextItem(hTree,TVGN_NEXTVISIBLE);
	CString strName;
		   ack = gSimJzq.SetHostAdd();
		   plog.saveLog_testresult(PARS_FILE,TIME,"设置从节点 ",ack,2);
		  

	while (hNextItem)
	{
		strName = pMainDlg->m_treeProject.GetItemText(hNextItem);
		if (pMainDlg->m_treeProject.GetCheck(hNextItem))
		{
			switch(atol(strName.Mid(0,2)))
			{
			case 1://	单地址实际表测试
				  {
					    plog.saveLog_strAll(TIME,"开始测试："+strName,2);
						ack= TestOneAdd(1);
						StaSucessCnt(ack,allSucesscnt,allfailcnt);
						plog.saveLog_testresultAll(TIME,strName ,ack,1);
						plog.saveLog_strAll(TIME,"结束测试："+strName,2);
				  }
				break;
			case 2://多地址测试
				 {
					    plog.saveLog_strAll(TIME,"开始测试："+strName,2);
						ack= TestMoreAdd(1);
						StaSucessCnt(ack,allSucesscnt,allfailcnt);
						plog.saveLog_testresultAll(TIME,strName ,ack,1);
						plog.saveLog_strAll(TIME,"结束测试："+strName,2);
				  }
				break;
            case 3://	单地址无反回
				  {
					    plog.saveLog_strAll(TIME,"开始测试："+strName,2);
						ack= AFN14OneMeterNoAck();
						StaSucessCnt(ack,allSucesscnt,allfailcnt);
						plog.saveLog_testresultAll(TIME,strName ,ack,1);
						plog.saveLog_strAll(TIME,"结束测试："+strName,2);
				  }
				break;
			case 4://多地址无返
				 {
					    plog.saveLog_strAll(TIME,"开始测试："+strName,2);
						ack= AFN14MoreMeterNoAck();
						StaSucessCnt(ack,allSucesscnt,allfailcnt);
						plog.saveLog_testresultAll(TIME,strName ,ack,1);
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

INT8U  CTESTCCO_AFN14::AFN14OneMeterNoAck(void)
{
	INT8U ack = FALSE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
//INT32U tmp32;
	INT32U ackfg=0;
	//dan地址参数设置
	 ack = TestOneAddSetPa();
	 ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
	sNoAckDiMsg  noackMsg;
	gSimMeter.SetSimMeterRunFg(1);//设置模拟表运行
//表都不返回
	gSimMeter.ClrALLNoAckDi();

	gSimMeter.SetNoAckDi(gReMeterDi[0]);
	for(INT8U m=0;m<5;m++)
	{
		ack = gSimJzq.AFN14F1ACK0001CmpAmt(0,0,0x02);
		StaSucessCnt(ack,resucnt,refailcnt);
		//模拟收到3次重发。
		ack=gSimMeter.QueNoDiAckmsg(gReMeterDi[0],noackMsg);
		ack=gSimMeter.CheckNoDiAckmsg(noackMsg);
		plog.saveLog_NoAckMsg(DATA_FILE,TIME,"表数据无返回",noackMsg,1);
		StaSucessCnt(ack,resucnt,refailcnt);
		
	}

				 
	  gSimMeter.ClrALLNoAckDi();
	         if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"单地址无回测试",1);
    return ack;

}
INT8U  CTESTCCO_AFN14::AFN14MoreMeterNoAck(void)
{
	INT8U ack = FALSE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
//	INT32U tmp32;
	INT32U ackfg=0;
	ack = TesMoreAddSetPa();
	ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
	sNoAckDiMsg  noackMsg;
	gSimMeter.SetSimMeterRunFg(1);//设置模拟表运行
//表都不返回
	gSimMeter.ClrALLNoAckDi();

	gSimMeter.SetNoAckDi(gReMeterDi[0]);
	for(INT8U m=0;m<5;m++)
	{
		ack = gSimJzq.AFN14F1ACK0001CmpAmt(m,0,0x02);
		StaSucessCnt(ack,resucnt,refailcnt);
		//模拟收到3次重发。
		ack=gSimMeter.QueNoDiAckmsg(gReMeterDi[0],noackMsg);
		ack=gSimMeter.CheckNoDiAckmsg(noackMsg);
		StaSucessCnt(ack,resucnt,refailcnt);
		plog.saveLog_NoAckMsg(DATA_FILE,TIME,"表数据无返回",noackMsg,1);
		
	}
	  gSimMeter.ClrALLNoAckDi();
	  ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
    for(INT8U m=0;m<5;m++)
		{
			
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,1);
			StaSucessCnt(ack,resucnt,refailcnt);
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,1);
			StaSucessCnt(ack,resucnt,refailcnt);
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,1);
			StaSucessCnt(ack,resucnt,refailcnt);
			
	  }		
	gSimMeter.ClrALLNoAckDi();

	
	for(INT8U m=0;m<5;m++)
	{
		gSimMeter.SetNoAckDi(gReMeterDi[0]);
		if(m!=2)
		{
          gSimMeter.ClrALLNoAckDi();
		}
		ack = gSimJzq.AFN14F1ACK0001CmpAmt(m,0,0x02);
		StaSucessCnt(ack,resucnt,refailcnt);
	    if(m!=2)
		{
		//模拟收到3次重发。
			ack=gSimMeter.QueNoDiAckmsg(gReMeterDi[0],noackMsg);
			ack=gSimMeter.CheckNoDiAckmsg(noackMsg);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
	}

	 gSimMeter.ClrALLNoAckDi();
    for(INT8U m=2;m<3;m++)
		{
			
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,1);
			StaSucessCnt(ack,resucnt,refailcnt);
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,1);
			StaSucessCnt(ack,resucnt,refailcnt);
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,1);
			StaSucessCnt(ack,resucnt,refailcnt);
			
	  }		 
	  gSimMeter.ClrALLNoAckDi();

		//抄表全部完成
		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);

	         if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"多表无回测试",1);
    return ack;

}
//------------------------------------------------------------------------------
//(一)	单地址测试（实际、模拟）
INT8U CAFN14ReadMeterFun :: TestOneAdd(INT8U CmpType)
{
    INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	//dan地址参数设置
	 ack = TestOneAddSetPa();
	 StaSucessCnt(ack,resucnt,refailcnt);
  //【1】正常抄表测试
	ack=TestOneAddReadMeter_OK(CmpType);
	StaSucessCnt(ack,resucnt,refailcnt);
	//步1的正常回复测试【失败、成功、抄表】
    ack= TestOneAddReadMeter_Step1Ack(CmpType);
    StaSucessCnt(ack,resucnt,refailcnt);
	//步1的异常回复测试  ackType: 0 不回复。 1：回复错SEQ
     ack= TestOneAddReadMeter_Step1ErrAck(0,CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack= TestOneAddReadMeter_Step1ErrAck(1,CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 //步3的异常回复测试  ackType: 0 不回复。 1：回复错SEQ,
     ack= TestOneAddReadMeter_Step3ErrAck(0, CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack= TestOneAddReadMeter_Step3ErrAck(1, CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 //步3的异常回复测试 回复否认帧
     ack= TestOneAddReadMeter_Step3ErrAckNo( CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 //单地址路由测试
       ack= TestOneAddRouter(CmpType);
	   StaSucessCnt(ack,resucnt,refailcnt);
	    if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
	 return ack;
}

//(一)	MORE地址测试（实际、模拟）
INT8U CAFN14ReadMeterFun :: TestMoreAdd(INT8U CmpType)
{
    INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	//地址参数设置
	 ack = TesMoreAddSetPa();
	 StaSucessCnt(ack,resucnt,refailcnt);
  //【1】正常抄表测试
	ack=TesMoreAddReadMeter(CmpType);
	StaSucessCnt(ack,resucnt,refailcnt);
	//步1的正常回复测试【失败、成功、抄表】
    ack= TestMoreAddReadMeter_Step1Ack(CmpType);
    StaSucessCnt(ack,resucnt,refailcnt);
	//步1的异常回复测试  ackType: 0 不回复。 1：回复错SEQ
     ack= TestMoreAddReadMeter_Step1errAck(0,CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	  ack= TestMoreAddReadMeter_Step1errAck(1,CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 //步3的异常回复测试  ackType: 0 不回复。 1：回复错SEQ,
     ack= TestMoreAddReadMeter_Step3ErrAck( CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 //步3的异常回复测试 回复否认帧
     ack= TestMoreAddReadMeter_Step3ErrAckNo( CmpType);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 //多地址路由测试
       ack= TestMoreAddRouter(CmpType);
	   StaSucessCnt(ack,resucnt,refailcnt);
	    if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
	 return ack;
}
//dan地址参数设置
INT8U CAFN14ReadMeterFun ::  TestOneAddSetPa(void)
{
  INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	//准备
	 ack = gSimJzq.SetNodeAdd(0,1);
	 StaSucessCnt(ack,resucnt,refailcnt);
	ack = gSimJzq. Router_Stop();
	 ack=gSimJzq. QueAllNetSta(0,1,60);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 if(ack==DACK_SUCESS)
         {
			 if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		 }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"单地址参数设置 ",1);
 return ack;
}

//【1】正常抄表测试
INT8U CAFN14ReadMeterFun ::  TestOneAddReadMeter_OK(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
   //
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Test14ReadMeterOneAdd07MoreDi(0,5,1,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
		//if(ack==DACK_SUCESS)
		{
		  ack = gSimJzq.AFN14F1ACK0001(0x01);
		  StaSucessCnt(ack,resucnt,refailcnt);
		}
    	//if(ack==DACK_SUCESS)
		{
	    	ack = gSimJzq.ZjqNoRcvData(30,50);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
		//StaSucessCnt(ack,resucnt,refailcnt);
		 
		  if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
	plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"【1】正常测试",1);	
    return ack;
}
//步1的正常回复测试【失败、成功、抄表】
INT8U  CAFN14ReadMeterFun :: TestOneAddReadMeter_Step1Ack(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
  //【2】步1的回复测试
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.AFN14F1ACK0001(0x00);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}

	    //if(ack==DACK_SUCESS)
		{
			ack=TestOneAddReadMeter_OK(CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
		//StaSucessCnt(ack,resucnt,refailcnt);

         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"步1的正常回复测试",1);
    return ack;
}

//AMT步1的异常回复测试  ackType: 0 不回复。 1：回复错SEQ
INT8U  CAFN14ReadMeterFun :: TestAddReadMeter_Step1ErrAck_Amt(INT32U AmtSeq,INT8U vSrcAckType,INT8U ReCnt,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	INT8U no14cnt=0;
	INT8U tmpseq;
	sNoAckDiMsg   AFNnoack;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;

		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Test14ReadMeterOneAdd07(AmtSeq,gReMeterDi[0],5,CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
		if((ack==DACK_SUCESS))
		{
			  ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
			  StaSucessCnt(ack,resucnt,refailcnt);
		}
		if((ack==DACK_SUCESS))
		{
			ack = DACK_FAILURE;
		  if((DstDecodeDataFrame.s_head.s_AFN==0x014)&&(DstDecodeDataFrame.s_head.s_FN==F1))
			{
				ack = DACK_SUCESS;
				AFNnoack.s_Di=DstDecodeDataFrame.s_head.s_Msg_Seq;
				AFNnoack.s_RcvCnt=1;
				AFNnoack.s_Time[0]=GetSysTimeClk();
				for(INT8U m=0;m<26;m++)
				{
					ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame_2);
					if(ack==DACK_SUCESS)
					{
						ack=gSimJzq.CmpDecode3762(DstDecodeDataFrame,DstDecodeDataFrame_2);
						if(ack==DACK_SUCESS)
						{
						   if(vSrcAckType==1)
						   {
							   tmpseq=DstDecodeDataFrame_2.s_head.s_Msg_Seq;
							   DstDecodeDataFrame_2.s_head.s_Msg_Seq+=3;
							   gSimJzq. SlaveAckAFN14F1(1,&DstDecodeDataFrame.s_RcvDataBuf[1],gReMeterDi[0],DstDecodeDataFrame,sQGDW376_2HostFrame);
							   DstDecodeDataFrame_2.s_head.s_Msg_Seq=tmpseq;
						   }
                           AFNnoack.s_RcvCnt++;
						   if(AFNnoack.s_RcvCnt<=4)
				          {
							  AFNnoack.s_Time[AFNnoack.s_RcvCnt-1]=GetSysTimeClk();
						   }
						}
						else
						{
							break;
						}

					}
				}
		   }
		}
	

		 if(ack==DACK_SUCESS)
	   {
		 ack= gSimJzq.CmpReSendCntTime(AFNnoack,ReCnt,10*1000,15*1000);
	   }
         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
	plog.saveLog_NoAckMsg(DATA_FILE,TIME,"",AFNnoack,1);
  if(vSrcAckType==0)
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"步1的回复测试--不回复",1);
  else
	plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"步1的异常回复测试---SEQ错",1);
    return ack;
}

//步1的异常回复测试  ackType: 0 不回复。 1：回复错SEQ
INT8U  CAFN14ReadMeterFun :: TestOneAddReadMeter_Step1ErrAck(INT8U vSrcAckType,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	INT8U no14cnt=0;
//	INT8U tmpseq;
//	sNoAckDiMsg   AFNnoack;
//	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
//	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2;
//	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
	      ack=TestAddReadMeter_Step1ErrAck_Amt(0,vSrcAckType,3,CmpType);
		  StaSucessCnt(ack,resucnt,refailcnt);
	
			ack=TestOneAddReadMeter_OK(CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }

    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"步1的异常回复测试",1);
    return ack;
}

//步3的异常回复测试  ackType: 0 不回复。 1：回复错SEQ,
INT8U  CAFN14ReadMeterFun :: TestOneAddReadMeter_Step3ErrAck_Amt(INT32U AmtSeq,INT8U vSrcAckType,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	INT8U no14cnt=0;
	INT8U tmpseq;
	sNoAckDiMsg   AFNnoack;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
		
		  ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		if((ack==DACK_SUCESS))
		{
			ack = DACK_FAILURE;
		  if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1))
			{
				 ack = gSimJzq.SlaveAckAFN14F1(0x02,&DstDecodeDataFrame.s_RcvDataBuf[1],gReMeterDi[0],DstDecodeDataFrame,sQGDW376_2HostFrame);
		    }
		}

	    if((ack==DACK_SUCESS))
		{
		 ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		}
		  if((ack==DACK_SUCESS))
		   {
			   ack = DACK_FAILURE;
			if(gSimJzq.CmpAFN14F1Data(&gNodeAddBuf[AmtSeq][0],gReMeterDi[0],sQGDW376_2HostFrame,DstDecodeDataFrame)==DACK_SUCESS)
			{
			    AFNnoack.s_Di=DstDecodeDataFrame.s_head.s_Msg_Seq;
				AFNnoack.s_RcvCnt=1;
				AFNnoack.s_Time[0]=GetSysTimeClk();
				for(INT8U m=0;m<26;m++)
				{
					ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame_2);
					if(ack==DACK_SUCESS)
					{
						ack=gSimJzq.CmpDecode3762(DstDecodeDataFrame,DstDecodeDataFrame_2);
						if(ack==DACK_SUCESS)
						{
						   if(vSrcAckType==1)
						   {
							   tmpseq=DstDecodeDataFrame_2.s_head.s_Msg_Seq;
							   DstDecodeDataFrame_2.s_head.s_Msg_Seq+=3;
							   Cgw13762.Code376_2_SlaveFrame(0x00,F1,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						       gSimJzq.SendHost3762ToCom(sQGDW376_2HostFrame);
							   DstDecodeDataFrame_2.s_head.s_Msg_Seq=tmpseq;
						   }
                           AFNnoack.s_RcvCnt++;
						   if(AFNnoack.s_RcvCnt<=4)
				          {
							  AFNnoack.s_Time[AFNnoack.s_RcvCnt-1]=GetSysTimeClk();
						   }
						}
						else
						{
							if(AFNnoack.s_RcvCnt!=3)
							{
								break;
							}
							else if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1))
							{
							   break;
							}
						}
					}
				  }
				}
			  }
		   
		 if(ack==DACK_SUCESS)
	   {
		  ack= gSimJzq.CmpReSendCntTime(AFNnoack,3,10*1000,15*1000);
	   }
		
         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
	 plog.saveLog_NoAckMsg(DATA_FILE,TIME,"",AFNnoack,1);
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"步1的异常回复测试",1);
    return ack;
}

//步3的异常回复测试  ackType: 0 不回复。 1：回复错SEQ,
INT8U  CAFN14ReadMeterFun :: TestOneAddReadMeter_Step3ErrAck(INT8U vSrcAckType,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	INT8U no14cnt=0;
//	INT8U tmpseq;
	//sNoAckDiMsg   AFNnoack;
//	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
//	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2;
//	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
	
		 ack=TestOneAddReadMeter_Step3ErrAck_Amt(0,vSrcAckType,CmpType);
		  StaSucessCnt(ack,resucnt,refailcnt); 
	   if(ack==DACK_SUCESS)
		{
			ack=TestOneAddReadMeter_OK(CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
		 if(ack==DACK_SUCESS)
	   {
		//  ack= gSimJzq.CmpReSendCntTime(AFNnoack,3,10*1000,15*1000);
	   }
		
         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
//	  plog.saveLog_NoAckMsg(DATA_FILE,TIME,"",AFNnoack,1);
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"步1的异常回复测试",1);
    return ack;
}
//步3的异常回复测试 回复否认帧
INT8U  CAFN14ReadMeterFun :: TestOneAddReadMeter_Step3ErrAckNo_Amt(INT32U Amtseq,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
		
		  ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		if((ack==DACK_SUCESS))
		{
			ack = DACK_FAILURE;
		  if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1))
			{
				 ack = gSimJzq.SlaveAckAFN14F1(0x02,&DstDecodeDataFrame.s_RcvDataBuf[1],gReMeterDi[0],DstDecodeDataFrame,sQGDW376_2HostFrame);
		    }
		}

	    if((ack==DACK_SUCESS))
		{
		 ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		}
		  if((ack==DACK_SUCESS))
		   {
			   ack = DACK_FAILURE;
			if(gSimJzq.CmpAFN14F1Data(&gNodeAddBuf[0][0],gReMeterDi[0],sQGDW376_2HostFrame,DstDecodeDataFrame)==DACK_SUCESS)
			{
					ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
					if(ack==DACK_SUCESS)
					{
						ack = DACK_FAILURE;
						 if((DstDecodeDataFrame.s_head.s_AFN==0x06)&&(DstDecodeDataFrame.s_head.s_FN==F2))
						{
						     Cgw13762.Code376_2_SlaveFrame(0x00,F2,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						      gSimJzq.SendHost3762ToCom(sQGDW376_2HostFrame);
							 ack=DACK_SUCESS;
						 }
					}          
			}
		  }
		   
		  if((ack==DACK_SUCESS))
		{
		   ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
		   StaSucessCnt(ack,resucnt,refailcnt);
		   if((ack==DACK_SUCESS))
			{
				ack = DACK_FAILURE;
			  if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1))
				{
					 ack = DACK_SUCESS;
				}
			}
		}

		 if(ack==DACK_SUCESS)
         {
			 if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		 }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"步3的异常回复测试--回否认帧",1);
    return ack;
}
//步3的异常回复测试 回复否认帧
INT8U  CAFN14ReadMeterFun :: TestOneAddReadMeter_Step3ErrAckNo(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
//	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
//	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//if(ack==DACK_SUCESS)
		{
			ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
	
		ack=TestOneAddReadMeter_Step3ErrAckNo_Amt(0,CmpType);
		StaSucessCnt(ack,resucnt,refailcnt);
	   if(ack==DACK_SUCESS)
		{
			ack=TestOneAddReadMeter_OK(CmpType);
		    StaSucessCnt(ack,resucnt,refailcnt);
		}
		
		 if(ack==DACK_SUCESS)
         {
			 if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		 }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"步1的异常回复测试",1);
    return ack;
}
//单地址路由测试
INT8U CAFN14ReadMeterFun :: TestOneAddRouter(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;

	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
	    StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.Router_Stop();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.Router_Resume();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.Router_Stop();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
	    StaSucessCnt(ack,resucnt,refailcnt);
		 ack=gSimJzq.HostRcv376_2(30*1000,50,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		if((ack==DACK_SUCESS))
		{
			ack = DACK_FAILURE;
		  if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1))
			{
				 ack=DACK_SUCESS;
		    }
		}
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.Router_Stop();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq.Test14ReadMeterOneAdd07(0,gReMeterDi[0],5,CmpType);
	    StaSucessCnt(ack,resucnt,refailcnt);
		ack = gSimJzq.AFN14F1AllOP(30*1000,50,0x01,DPCT_2007FG,0x00000100);
		StaSucessCnt(ack,resucnt,refailcnt);
		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
		 if(ack==DACK_SUCESS)
         {
			 if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		 }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"单地址路由测试",1);
    return ack;
}

//多地址参数设置
INT8U CAFN14ReadMeterFun ::  TesMoreAddSetPa(void)
{
  INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	//准备
	 ack = gSimJzq.SetNodeAdd(0,5);
	 StaSucessCnt(ack,resucnt,refailcnt);
	ack = gSimJzq. Router_Stop();
	 ack=gSimJzq. QueAllNetSta(0,5,60);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 if(ack==DACK_SUCESS)
         {
			 if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		 }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"多地址参数设置 ",1);
 return ack;
}
  //多表DI的正常测试
INT8U  CAFN14ReadMeterFun :: TesMoreAddReadMeter(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
    ack = gSimJzq. Router_Start();
    StaSucessCnt(ack,resucnt,refailcnt);
	ack=gSimJzq.TestReadMeterMoreAdd07(0,5,0,5,CmpType);
	StaSucessCnt(ack,resucnt,refailcnt);
	ack=gSimJzq.ZjqNoRcvData(30*1000,50);
	StaSucessCnt(ack,resucnt,refailcnt);
	if(ack==DACK_SUCESS)
         {
			 if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		 }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"单地址路由测试",1);
    return ack;
}

  
//步1的正常回复测试
INT8U  CAFN14ReadMeterFun :: TestMoreAddReadMeter_Step1Ack(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
  //【2】步1的回复测试
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//收到表1-5的步1，依次回复抄表失败，切换表号,2轮
	  for(INT8U n=0;n<2;n++)
      {
		  for(INT8U m=0;m<5;m++)
		{
         ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x00,CmpType);
		 StaSucessCnt(ack,resucnt,refailcnt);
		}
	  }
		
      //第1轮收到表1-5的步1，偶数抄表2次，回成功, 奇数回抄表2次，回失败。
	  //第2轮奇数回抄表2次，回成功。
		  for(INT8U m=0;m<5;m++)
		{
				if((m%2)==0)
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			}
			else
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x00,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);

			}
	 }
		    for(INT8U m=0;m<5;m++)
		  {
		      if((m%2)==0)
			  {
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			  }
	      }

//第1轮表1-5的步1，奇数抄表2次，回成功, 偶数回抄表2次，回失败。
 //第2轮偶数回抄表2次，回成功。
        ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);

		  for(INT8U m=0;m<5;m++)
		{
				if((m%2)==1)
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			}
			else
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x00,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);

			}
	 }
		    for(INT8U m=0;m<5;m++)
		  {
		       if((m%2)==0)
			   {
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			  }
	      }

		 ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
   //第1轮抄表2次,最后一块表失败。
   //第2轮最后一块抄表2次,回成功。
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		  for(INT8U m=0;m<5;m++)
		{
			
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);

			   if(m==4)
				 {
					 ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x00,CmpType);
			   }
			   else
				{
					ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			   }
				StaSucessCnt(ack,resucnt,refailcnt);
			
	 }
       for(INT8U m=0;m<2;m++)
		{
          ack = gSimJzq.AFN14F1AllOPCmpAmt(4,gReMeterDi[0],1,0x02,CmpType);
		  StaSucessCnt(ack,resucnt,refailcnt);
	   }
	   ack = gSimJzq.AFN14F1AllOPCmpAmt(5,gReMeterDi[1],1,0x01,CmpType);
	    StaSucessCnt(ack,resucnt,refailcnt);
		 ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
//----------------------------------------------------------------------------

         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"步1的正常回复测试",1);
    return ack;
}

//步1的异常回复测试  ackType: 0 不回复。 1：回复错SEQ
INT8U  CAFN14ReadMeterFun :: TestMoreAddReadMeter_Step1errAck(INT8U Acktype,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
  //【2】步1的回复测试
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//收到表1-5的步1，依次回复SEQ不一致，切换表号,2轮
	 
		  for(INT8U m=0;m<5;m++)
		{
			 ack = TestAddReadMeter_Step1ErrAck_Amt(m,Acktype,3,CmpType);
			 StaSucessCnt(ack,resucnt,refailcnt);
		}
	
		
      //第1轮收到表1-5的步1，偶数抄表2次，回成功, 奇数回抄表2次，回失败。
	  //第2轮奇数回抄表2次，回成功。
		  for(INT8U m=0;m<5;m++)
		{
				if((m%2)==0)
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			}
			else
			{
				 ack = TestAddReadMeter_Step1ErrAck_Amt(m,Acktype,3,CmpType);
			     StaSucessCnt(ack,resucnt,refailcnt);

			}
	 }
		    for(INT8U m=0;m<5;m++)
		  {
		      if((m%2)==0)
			  {
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			  }
	      }

//第1轮表1-5的步1，奇数抄表2次，回成功, 偶数回抄表2次，回失败。
 //第2轮偶数回抄表2次，回成功。
        ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);

		  for(INT8U m=0;m<5;m++)
		{
				if((m%2)==1)
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			}
			else
			{
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				 ack = TestAddReadMeter_Step1ErrAck_Amt(m,Acktype,3,CmpType);
			     StaSucessCnt(ack,resucnt,refailcnt);
		

			}
	 }
		    for(INT8U m=0;m<5;m++)
		  {
		       if((m%2)==0)
			   {
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
			  }
	      }

		 ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
   //第1轮抄表2次,最后一块表失败。
   //第2轮最后一块抄表2次,回成功。
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		  for(INT8U m=0;m<5;m++)
		{
			
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[0],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
				StaSucessCnt(ack,resucnt,refailcnt);

			   if(m==4)
				 {
					 ack = TestAddReadMeter_Step1ErrAck_Amt(m,Acktype,3,CmpType);
			    }
			   else
				{
					ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			   }
				StaSucessCnt(ack,resucnt,refailcnt);
			
	 }
       for(INT8U m=0;m<2;m++)
		{
          ack = gSimJzq.AFN14F1AllOPCmpAmt(4,gReMeterDi[0],1,0x02,CmpType);
		  StaSucessCnt(ack,resucnt,refailcnt);
	   }
	   ack = gSimJzq.AFN14F1AllOPCmpAmt(5,gReMeterDi[1],1,0x01,CmpType);
	    StaSucessCnt(ack,resucnt,refailcnt);
		 ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
//----------------------------------------------------------------------------

         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"步1的异常回复测试",1);
    return ack;
}

//步3异常回复SEQ，不回复测试
INT8U  CAFN14ReadMeterFun :: TestMoreAddReadMeter_Step3ErrAck(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
  //【2】步3的回复测试
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//收到表１，步３回SEQ不致
	     for(INT8U m=0;m<5;m++)
		{
         ack = TestOneAddReadMeter_Step3ErrAck_Amt(0,0,CmpType);
		 StaSucessCnt(ack,resucnt,refailcnt);
		}
        //收到表１，步３不返回
		  for(INT8U m=0;m<5;m++)
		{
         ack = TestOneAddReadMeter_Step3ErrAck_Amt(0,1,CmpType);
		 StaSucessCnt(ack,resucnt,refailcnt);
		}
		  //收到表1-5，一次，步３回SEQ错误，一次回正确数据，一次回抄表成功
		    for(INT8U m=0;m<5;m++)
		{
          ack = TestOneAddReadMeter_Step3ErrAck_Amt(m,0,CmpType);
		 StaSucessCnt(ack,resucnt,refailcnt);
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
	    ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
  //收到表1-5，一次，步３不回，一次回正确数据，一次回抄表成功
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
         for(INT8U m=0;m<5;m++)
		{
			 ack = TestOneAddReadMeter_Step3ErrAck_Amt(m,1,CmpType);
		 StaSucessCnt(ack,resucnt,refailcnt);
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		 }
		 ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);


		//1-5正常抄表
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
         for(INT8U m=0;m<5;m++)
		{
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		 }
		  ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
//----------------------------------------------------------------------------

         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"步3异常回复SEQ，不回复测试",1);
    return ack;
}

//步3异常回否认测试
INT8U  CAFN14ReadMeterFun :: TestMoreAddReadMeter_Step3ErrAckNo(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		//收到表1-5的步1，依次回复否认，抄表，抄表成功

	     for(INT8U m=0;m<5;m++)
		{
         ack = TestOneAddReadMeter_Step3ErrAckNo_Amt(m,CmpType);
		 	StaSucessCnt(ack,resucnt,refailcnt);
		  ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		   ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		 StaSucessCnt(ack,resucnt,refailcnt);
		}
		 ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
//----------------------------------------------------------------------------
         if(refailcnt==0)
		  {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"步1的正常回复测试",1);
    return ack;
}
//More地址路由测试
INT8U CAFN14ReadMeterFun :: TestMoreAddRouter(INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
//	   sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	   //重启路由，前1-3块抄表
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		for(INT8U m=0;m<3;m++)
		{
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		    ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
		//暂停路由
			ack=gSimJzq.Router_Stop();
         ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
		//重启路由，前1-3块抄表
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		for(INT8U m=0;m<3;m++)
		{
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		    ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
		//暂停路由
		ack=gSimJzq.Router_Stop();
        ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);

      //恢复路由，4-5块抄表
		ack=gSimJzq.Router_Resume();
		StaSucessCnt(ack,resucnt,refailcnt);

		for(INT8U m=3;m<5;m++)
		{
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		    ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
       //抄表全部完成
		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);


		//恢复路由，无表请求
		ack=gSimJzq.Router_Resume();
		StaSucessCnt(ack,resucnt,refailcnt);

		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);

		//重启路由，前1-5块抄表
		ack = gSimJzq. Router_Start();
		StaSucessCnt(ack,resucnt,refailcnt);
		for(INT8U m=0;m<5;m++)
		{
			ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x02,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		    ack = gSimJzq.AFN14F1AllOPCmpAmt(m,gReMeterDi[1],1,0x01,CmpType);
			StaSucessCnt(ack,resucnt,refailcnt);
		}
		//抄表全部完成
		ack=gSimJzq.ZjqNoRcvData(30*1000,50);
		StaSucessCnt(ack,resucnt,refailcnt);
		

			 if(refailcnt==0)
		   {
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		
    plog.saveLog_StaCnt(resucnt,refailcnt,DATA_FILE,TIME,"单地址路由测试",1);
    return ack;
}

