// TESTSearchMeter_S.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTSearchMeter_S.h"
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
extern CLogFile plog;

// CTESTSearchMeter_S

IMPLEMENT_DYNAMIC(CTESTSearchMeter_S, CWnd)

CTESTSearchMeter_S::CTESTSearchMeter_S()
{

}

CTESTSearchMeter_S::~CTESTSearchMeter_S()
{
}


BEGIN_MESSAGE_MAP(CTESTSearchMeter_S, CWnd)
END_MESSAGE_MAP()

void CTESTSearchMeter_S::C3762_TEST(HTREEITEM hTree)
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
	INT8U ack;
	pMainDlg->m_treeProject.Expand(hTree,TVE_EXPAND);//展开树节点
	HTREEITEM hNextItem = pMainDlg->m_treeProject.GetNextItem(hTree,TVGN_NEXTVISIBLE);
	CString strName;
	INT16U allSucesscnt = 0;
	INT16U allfailcnt = 0;;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	 ack = gSimJzq.Router_PaRst();
	 ack = gSimJzq.Router_Stop();
	while (hNextItem)
	{
		strName = pMainDlg->m_treeProject.GetItemText(hNextItem);
		if (pMainDlg->m_treeProject.GetCheck(hNextItem))
		{
			switch(atol(strName.Mid(0,2)))
			{
			case 1://1.	单STA、白名单内搜表（回确认、否认）【实际、模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestStaOnNetAckOKNo(0x01);
				StaSucessCnt(ack,resucnt,refailcnt);

				ack=TestStaOnNetAckOKNo(0x02);
				StaSucessCnt(ack,resucnt,refailcnt);


				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				//plog.saveLog_strAll(TIME," 结束测试："+strName,0,2);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
			case 2://2.	单STA、白名单内搜表（不回复、回复确认SEQ不一致）【实际、模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestStaOnNetAckOKNo(0x03);
				StaSucessCnt(ack,resucnt,refailcnt);

				ack=TestStaOnNetAckOKNo(0x04);
				StaSucessCnt(ack,resucnt,refailcnt);


				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
			case 3://3.	多STA、白名单内搜表（回确认、否认）【实际】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestMoreOnStaNetAckType(0x05,0x01);
				StaSucessCnt(ack,resucnt,refailcnt);

				ack=TestMoreOnStaNetAckType(0x05,0x02);
				StaSucessCnt(ack,resucnt,refailcnt);


				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
                plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
			case 4://4.	多STA、白名单内搜表（部分回复）【实际】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestMoreOnStaNetAckType(0x05,0x03);
				StaSucessCnt(ack,resucnt,refailcnt);

				ack=TestMoreOnStaNetAckType(0x05,0x04);
				StaSucessCnt(ack,resucnt,refailcnt);


				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
			case 5://5.	单采集器、白名单内搜表（回确认、否认）【实际、模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestCjqOnNetAckOKNo(32,0x01);
				StaSucessCnt(ack,resucnt,refailcnt);

				ack=TestCjqOnNetAckOKNo(32,0x02);
				StaSucessCnt(ack,resucnt,refailcnt);


				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
			case 6://6.	单采集器、白名单内搜表（不回复、回复确认SEQ不一致）【实际、模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestCjqOnNetAckOKNo(32,0x03);
				StaSucessCnt(ack,resucnt,refailcnt);

				ack=TestCjqOnNetAckOKNo(32,0x04);
				StaSucessCnt(ack,resucnt,refailcnt);


				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
			default:

				break;
			}
			if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		}
		hNextItem = pMainDlg->m_treeProject.GetNextItem(hNextItem,TVGN_NEXTVISIBLE);	
	}
	plog.saveLog_StaCnt(allSucesscnt,allfailcnt,DATA_FILE,TIME,"总测试项数： ");
	ack = QueAckFormAckCnt(allfailcnt);
	plog.saveLog_testresult(DATA_FILE,TIME,"总结果： ",ack,2);
}

// CTESTSearchMeter_S message handlers

//allTime 持续时间 ； cnt 重发次数
INT8U  CSearchAmtPublic::StartSearchMeter(INT16U allTime,INT8U Cnt)
{
	INT8U tmpbuf[50];
	INT8U ack;
	BufIs0(tmpbuf,6);
	Hex16ToBuf2(allTime,&tmpbuf[6]);
	tmpbuf[8]=Cnt;
	tmpbuf[9]=0x00;
	ack=gSimJzq.HostSendRcv376_2Buf_NoAck(0x11,F5,tmpbuf,10);
	return ack;
}
INT8U  CSearchAmtPublic::QueSearchResult(INT16U StartSeq,INT8U Cnt,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT16U &vdstAllCnt)
{
    INT8U ack = DACK_FAILURE;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	INT8U tmpbuf[3];
	vdstAllCnt=0;
	Hex16ToBuf2(StartSeq,tmpbuf);
	tmpbuf[2]=Cnt;
	ack = gSimJzq.HostSendRcv376_2Buf(0x11,F6,tmpbuf,3,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
	if(ack== DACK_SUCESS)
	{
		ack = DACK_FAILURE;
        if(DstDecodeDataFrame.s_RcvDataLen==(DstDecodeDataFrame.s_RcvDataBuf[2]*8+3))
		{
			vdstAllCnt = Buf2ToHex16(DstDecodeDataFrame.s_RcvDataBuf);
			if( Cnt == DstDecodeDataFrame.s_RcvDataBuf[2])
			{
				ack = DACK_SUCESS;
			}
		}
	}
	return ack;
}
INT8U  CSearchAmtPublic::CmpStaOnSearchAmt(INT16U cmpSeq,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame)
{
INT8U ack=DACK_FAILURE;
	if(DstDecodeDataFrame.s_RcvDataLen==1*7+12)
	{
		if(1==DstDecodeDataFrame.s_RcvDataBuf[11])
		{
            if((1==DstDecodeDataFrame.s_RcvDataBuf[0])&&(1==DstDecodeDataFrame.s_RcvDataBuf[10]))
			{
                if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[0], gSimJzq.QueNodeBufAdd(cmpSeq),6)==EQU)
				{
					 ack = DACK_SUCESS;
					for(INT16U m=0;m<1;m++)
					{
                      if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[12+m*7], gSimJzq.QueNodeBufAdd(cmpSeq+m),7)!=EQU)
					  {
                            ack=DACK_FAILURE;
							break;

					  }

					}

				}
			}
		}
	}
	return ack;

}
INT8U  CSearchAmtPublic::CmpStaSearchAmt(INT16U StartSeq,INT16U Cnt,INT16U cmpSeq,INT16U CmpCnt)
{
	INT8U ack = DACK_FAILURE;
	INT16U allcnt;
	INT8U readcnt=0;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
  for(INT16U n=0;n<Cnt;n+=readcnt)
   {
	   if(Cnt-32>32)
	   {
			  readcnt=32;
	   }
	   else
		{
			readcnt=Cnt-32;
	   }
	   ack = QueSearchResult(StartSeq+n,readcnt,DstDecodeDataFrame,allcnt);
		if(ack==DACK_SUCESS)
		{
			for(INT8U m=0;(m<readcnt);m++)
			{
				if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[3+m*8], gSimJzq.QueNodeBufAdd(cmpSeq+n+m),7)!=EQU)
				{
				   ack = DACK_FAILURE;
				   break;
				 }
					if(((DstDecodeDataFrame.s_RcvDataBuf[3+m*8+8+1]>>3)&0x07)!=0x02)
					{
					 ack = DACK_FAILURE;
					   break;
					 }

			}
		}
		if(ack!=DACK_SUCESS)
	 {
		 break;
	  }
	}
	plog.saveLog_testresult(DATA_FILE,TIME,"查询STA搜表结果并比较 ：  ",ack,0);
 return  ack;
}
INT8U CSearchAmtPublic:: CmpStaMacAmt(INT16U StartSeq,INT16U Cnt,INT16U cmpSeq,INT16U CmpCnt,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U ack = DACK_FAILURE;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	INT16U allcnt;
	INT8U readcnt=0;
	INT8U tmpbuf[3];

	for(INT16U n=0;n<Cnt;n++)
	{
		Hex16ToBuf2(StartSeq+n,tmpbuf);

		 if(Cnt-32>32)
	   {
			  readcnt=32;
	   }
	   else
		{
			readcnt=Cnt-32;
	   }
	   tmpbuf[2]=readcnt;
	ack = gSimJzq.HostSendRcv376_2Buf(0x10,F202,tmpbuf,3,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
	if(ack== DACK_SUCESS)
	{
		ack = DACK_FAILURE;
        if(DstDecodeDataFrame.s_RcvDataLen==(DstDecodeDataFrame.s_RcvDataBuf[2]*23+3))
		{
			allcnt = Buf2ToHex16(DstDecodeDataFrame.s_RcvDataBuf);
			if( readcnt == DstDecodeDataFrame.s_RcvDataBuf[2])
			{
				ack = DACK_SUCESS;
			}
		}
	}
	if(ack==DACK_SUCESS)
	{
		for(INT8U m=0;(m<readcnt);m++)
		{
			if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[3+m*23], gSimJzq.QueNodeBufAdd(cmpSeq+n+m),6)!=EQU)
			{
               ack = DACK_FAILURE;
			   break;
             }
			
			if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[3+m*23+6], gSimJzq.QueNodeBufAdd(cmpSeq+n+m),6)!=EQU)
			{
               ack = DACK_FAILURE;
			   break;
             }
		}

	}

	if(ack!=DACK_SUCESS)
	 {
		 break;
	  }
	}
	plog.saveLog_testresult(DATA_FILE,TIME,"比较STA的MAC地址 ：  ",ack,0);
	return ack;
}
INT8U  CSearchAmtPublic:: NodeSeqHardRst(INT16U vSrcSeq)
{
	INT8U ack = DACK_FAILURE;
	if(vSrcSeq<=gMaxNodeCnt)
	{
		ack = gSimJzq.NodeHardRst(&gNodeAddBuf[vSrcSeq][0]);
	}
	return ack;
}

//测试回确认0x01、否认0x02,SEQ错0x03,不回复0x04
INT8U  CSearchAmtPublic::TestStaOnNetAckOKNo(INT8U  ackType )
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
//	INT16U allcnt;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	 ack = gSimJzq.SetNodeAdd(0,1);
	 ack=StartSearchMeter(3,3);
	 StaSucessCnt(ack,resucnt,refailcnt);
	  if((ackType==0x01)||(ackType==0x02))
     {
	  ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,ackType,DstDecodeDataFrame);
	   StaSucessCnt(ack,resucnt,refailcnt);
	   ack=CmpStaOnSearchAmt(0,DstDecodeDataFrame);
	   StaSucessCnt(ack,resucnt,refailcnt);
	  }
	  else
	  {
          ack=TestStaOnNetAckOKNoNoAckSeqErr_Amt(ackType,DstDecodeDataFrame);
	      StaSucessCnt(ack,resucnt,refailcnt);
		 ack=CmpStaOnSearchAmt(0,DstDecodeDataFrame);
	   StaSucessCnt(ack,resucnt,refailcnt);

	  }
	 ack = gSimJzq.SearthMeterOpAFN06F2(60*1000*5,50,0x01,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=gSimJzq.ZjqNoRcvData(60*1000*3,50);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = gSimJzq.HostSendRcv376_2NoBuf_NoAck(0x11,F6);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpStaSearchAmt(1,1,0,1);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpStaMacAmt(1,1,0,1,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = gSimJzq.RouterHardRst();
	  Sleep(1000*10);
	 StaSucessCnt(ack,resucnt,refailcnt);
	  ack=CmpStaSearchAmt(1,1,0,1);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpStaMacAmt(1,1,0,1,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = QueAckFormAckCnt(refailcnt);
	  return ack;
}


//测试SEQ错0x03,不回复0x04
INT8U  CSearchAmtPublic:: TestStaOnNetAckOKNoNoAckSeqErr_Amt(INT8U acktype,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
		INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
//	INT16U allcnt;

		sNoAckDiMsg   AFNnoack;
	
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2;;
	 ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,acktype,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	    if((ack==DACK_SUCESS))
		   {
			   ack = DACK_FAILURE;
			    AFNnoack.s_Di=DstDecodeDataFrame.s_head.s_Msg_Seq;
				AFNnoack.s_RcvCnt=1;
				AFNnoack.s_Time[0]=GetSysTimeClk();
				for(INT8U m=0;m<26;m++)
				{
					     ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,acktype,DstDecodeDataFrame_2);
						 if(ack==DACK_SUCESS)
						 {
						  ack=gSimJzq.CmpDecode3762(DstDecodeDataFrame,DstDecodeDataFrame_2);
						 }
						if(ack==DACK_SUCESS)
						{
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
						if(AFNnoack.s_RcvCnt>=3)
						{
							break;
						}
				  
				}
		}
		ack = QueAckFormAckCnt(refailcnt);
			if(ack==DACK_SUCESS)
		   {
			  ack= gSimJzq.CmpReSendCntTime(AFNnoack,3,60*1000,180*1000);
		   }

			    plog.saveLog_NoAckMsg(DATA_FILE,TIME,"主动上报从节点信息次数及间隔时间",AFNnoack,1);
		return ack;

}

//测试回确认0x01、否认0x02,SEQ错0x03,不回复0x04
INT8U  CSearchAmtPublic::TestMoreOnStaNetAckType(INT8U vSrcCnt,INT8U  ackType )
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
//	INT16U allcnt;
	  ack = gSimJzq.Router_PaRst();
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	 ack = gSimJzq.SetNodeAdd(0,vSrcCnt);
	 ack=StartSearchMeter(5,3);
	 StaSucessCnt(ack,resucnt,refailcnt);

  if((ackType==0x01)||(ackType==0x02))
  {
	for(INT8U m=0;m<vSrcCnt;m++)
	{
		ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,ackType,DstDecodeDataFrame);
	    StaSucessCnt(ack,resucnt,refailcnt);
		 ack=CmpStaOnSearchAmt(m,DstDecodeDataFrame);
	   StaSucessCnt(ack,resucnt,refailcnt);
	}
  }
  else
  {
	  	 for(INT8U m=0;m<vSrcCnt;m++)
	{
	 if((m==1)||(m==2)||(m==4))
		{
			ack = TestStaOnNetAckOKNoNoAckSeqErr_Amt(ackType,DstDecodeDataFrame);
			 StaSucessCnt(ack,resucnt,refailcnt);
			 ack=CmpStaOnSearchAmt(m,DstDecodeDataFrame);
		   StaSucessCnt(ack,resucnt,refailcnt);
	    }
	 else
        {
			ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,0x01,DstDecodeDataFrame);
	        StaSucessCnt(ack,resucnt,refailcnt);
	    }
	}

  }
	 ack = gSimJzq.SearthMeterOpAFN06F2(60*1000*5,50,0x01,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=gSimJzq.ZjqNoRcvData(60*1000*3,50);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = gSimJzq.HostSendRcv376_2NoBuf_NoAck(0x11,F6);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpStaSearchAmt(1,vSrcCnt,0,vSrcCnt);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpStaMacAmt(1,vSrcCnt,0,vSrcCnt,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = gSimJzq.RouterHardRst();
	  Sleep(1000*10);
	 StaSucessCnt(ack,resucnt,refailcnt);
	  ack=CmpStaSearchAmt(1,vSrcCnt,0,vSrcCnt);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpStaMacAmt(1,vSrcCnt,0,vSrcCnt,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = QueAckFormAckCnt(refailcnt);
	  return ack;
}
INT8U  CSearchAmtPublic::CmpCjqMacAmt(INT16U StartSeq,INT8U Cnt,INT16U cmpSeq,INT8U CmpCnt,INT16U CjqBp,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U ack = DACK_FAILURE;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	INT16U allcnt;
	INT8U tmpbuf[3];
	Hex16ToBuf2(StartSeq,tmpbuf);
	tmpbuf[2]=Cnt;
	ack = gSimJzq.HostSendRcv376_2Buf(0x10,F202,tmpbuf,3,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
	if(ack== DACK_SUCESS)
	{
		ack = DACK_FAILURE;
        if(DstDecodeDataFrame.s_RcvDataLen==(DstDecodeDataFrame.s_RcvDataBuf[2]*23+3))
		{
			allcnt = Buf2ToHex16(DstDecodeDataFrame.s_RcvDataBuf);
			if( Cnt == DstDecodeDataFrame.s_RcvDataBuf[2])
			{
				ack = DACK_SUCESS;
			}
		}
	}
	if(ack==DACK_SUCESS)
	{
		for(INT8U m=0;(m<Cnt)&&(StartSeq+m<=allcnt);m++)
		{
			if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[3+m*23],&gNodeAddBuf[cmpSeq+m][0],6)!=EQU)
			{
               ack = DACK_FAILURE;
			   break;
             }
			
			if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[3+m*23+6],&gNodeAddBuf[CjqBp][0],6)!=EQU)
			{
               ack = DACK_FAILURE;
			   break;
             }
		}

	}

	plog.saveLog_testresult(DATA_FILE,TIME,"比较CJQ的MAC地址：  ",ack,0);
	return ack;
}
INT8U  CSearchAmtPublic::CmpCjqOnSearchAmt(INT16U CjqBp,INT16U cmpSeq,INT8U CmpCnt,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame)
{
	INT8U ack=DACK_FAILURE;
	if(DstDecodeDataFrame.s_RcvDataLen==CmpCnt*7+12)
	{
		if(CmpCnt==DstDecodeDataFrame.s_RcvDataBuf[11])
		{
            if((1==DstDecodeDataFrame.s_RcvDataBuf[0])&&(0==DstDecodeDataFrame.s_RcvDataBuf[10]))
			{
                if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[0], gSimJzq.QueNodeBufAdd(CjqBp),6)==EQU)
				{
					 ack = DACK_SUCESS;
					for(INT16U m=0;m<CmpCnt;m++)
					{
                      if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[12+m*7], gSimJzq.QueNodeBufAdd(cmpSeq+m),7)!=EQU)
					  {
                            ack=DACK_FAILURE;
							break;
					  }

					}

				}
			}
		}
	}
	plog.saveLog_testresult(DATA_FILE,TIME,"比较CJQ上报结果 ：  ",ack,0);
	return ack;
}
//测试回确认0x01、否认0x02,SEQ错0x03,不回复0x04
INT8U CSearchAmtPublic:: TestCjqOnNetAckOKNo(INT8U vSrcCnt,INT8U  ackType )
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
//	INT16U allcnt;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	gSimMeter.SetAmtAddBp(0);
	gSimMeter.SetSearchSta(32,32,0,0);
	  ack = gSimJzq.SetNodeAdd(0,32);
	 ack=StartSearchMeter(5,3);
	 StaSucessCnt(ack,resucnt,refailcnt);
	  if((ackType==0x01)||(ackType==0x02))
     {
	  ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,ackType,DstDecodeDataFrame);
	   StaSucessCnt(ack,resucnt,refailcnt);
	   ack=CmpCjqOnSearchAmt(0,0,32,DstDecodeDataFrame);
	   StaSucessCnt(ack,resucnt,refailcnt);
	  }
	  else
	  {
          ack=TestStaOnNetAckOKNoNoAckSeqErr_Amt(ackType,DstDecodeDataFrame);
	      StaSucessCnt(ack,resucnt,refailcnt);
		  ack=CmpCjqOnSearchAmt(0,0,32,DstDecodeDataFrame);
	      StaSucessCnt(ack,resucnt,refailcnt);

	  }
	 ack = gSimJzq.SearthMeterOpAFN06F2(60*1000*5,50,0x01,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=gSimJzq.ZjqNoRcvData(60*1000*3,50);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = gSimJzq.HostSendRcv376_2NoBuf_NoAck(0x11,F6);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpStaSearchAmt(1,32,0,32);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpCjqMacAmt(1,32,0,32,0,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = gSimJzq.RouterHardRst();
	  Sleep(1000*10);
	 StaSucessCnt(ack,resucnt,refailcnt);
	  ack=CmpStaSearchAmt(1,32,0,32);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpCjqMacAmt(1,32,0,32,0,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	  ack = QueAckFormAckCnt(refailcnt);
	  return ack;
}
