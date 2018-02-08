// TESTSearchMeter_M.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTSearchMeter_M.h"
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

// CTESTSearchMeter_M

IMPLEMENT_DYNAMIC(CTESTSearchMeter_M, CWnd)

CTESTSearchMeter_M::CTESTSearchMeter_M()
{

}

CTESTSearchMeter_M::~CTESTSearchMeter_M()
{
}


BEGIN_MESSAGE_MAP(CTESTSearchMeter_M, CWnd)
END_MESSAGE_MAP()

void CTESTSearchMeter_M::C3762_TEST(HTREEITEM hTree)
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
	INT16U allfailcnt = 0;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	 ack = gSimJzq.Router_PaRst();
	 ack = gSimJzq.Router_Stop();
	while (hNextItem)
	{
		if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
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
			case 3://3.	多STA、白名单内搜表（回确认、否认）【实际、模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestMoreOnStaNetAckType(0x05,0x01);
				StaSucessCnt(ack,resucnt,refailcnt);

				ack=TestMoreOnStaNetAckType(0x05,0x02);
				StaSucessCnt(ack,resucnt,refailcnt);


				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
			case 4://4.	多STA、白名单内搜表（部分回复）【实际、模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestSearchAllSta(0x05,0x03);
				StaSucessCnt(ack,resucnt,refailcnt);

				ack=TestSearchAllSta(0x05,0x04);
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
			

			case 7://7.	内部状态的测试（要详细补序）【模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestInCmd();
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
	      case 8://	单采集器、不白名单内搜表【模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestCjqNoNetList(32);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
				
	      case 9://	采集器不响应启动、查询、停止搜表命令【模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestCjqNoAck();
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;

			case 10://全STA的搜表测试【模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestSearchAllSta(1024,0x01);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
			case 11://全采集器的搜表测试【模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestSearchAllCjq(32);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
		case 12://混合模式的搜表测试【模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestSearchStaCjq(1024);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
		  	case 13://全STA的MAC地址影射测试【模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestMACAllSta(1024);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
			case 14://全采集器的MAC地址影射测试【模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestMACAllCjq(32);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
			case 15://混合模式的MAC地址影射测试【模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestMACStaCjq(1024);
				StaSucessCnt(ack,resucnt,refailcnt);
				ack = QueAckFormAckCnt(refailcnt);

			    StaSucessCnt(ack,allSucesscnt,allfailcnt);
				plog.saveLog_testresultAll(TIME,strName+"结果： ",ack,1);
				break;
			case 16:///MAC地址重复影射测试【模拟】

				plog.saveLog_strAll(TIME,"开始测试："+strName,1);
				ack=TestMACRePeat();
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

//内部状态的测试（要详细补序）【模拟】
INT8U CTESTSearchMeter_M::TestInCmd( void)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	
	  return DACK_SUCESS;
}

//	单采集器、不白名单内搜表【模拟】
INT8U CTESTSearchMeter_M::TestCjqNoNetList(INT8U vSrcCnt)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	ChangeAmtBps(9600);
	ack=TestCjqOnNetAckOKNo(32,0x01);
	StaSucessCnt(ack,resucnt,refailcnt);

	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	gSimMeter.SetAmtAddBp(32);
	gSimMeter.SetSearchSta(vSrcCnt,vSrcCnt,32,0);
	 //ack = gSimJzq.SetNodeAdd(0,32);
	 ack=StartSearchMeter(5,3);
	 StaSucessCnt(ack,resucnt,refailcnt);

	ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,0x01,DstDecodeDataFrame);
	StaSucessCnt(ack,resucnt,refailcnt);
	ack=CmpCjqOnSearchAmt(32,32,vSrcCnt,DstDecodeDataFrame);
	StaSucessCnt(ack,resucnt,refailcnt);
	
	 ack = gSimJzq.SearthMeterOpAFN06F2(60*1000*5,50,0x01,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=gSimJzq.ZjqNoRcvData(60*1000*3,50);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = gSimJzq.HostSendRcv376_2NoBuf_NoAck(0x11,F6);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpStaSearchAmt(1,vSrcCnt,32,vSrcCnt);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpCjqMacAmt(1,32,0,32,0,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = gSimJzq.RouterHardRst();
	  Sleep(1000*10);
	 StaSucessCnt(ack,resucnt,refailcnt);
	  ack=CmpStaSearchAmt(1,vSrcCnt,32,vSrcCnt);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpCjqMacAmt(1,32,0,32,0,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	  ack = QueAckFormAckCnt(refailcnt);
	  return ack;
}


//	采集器不响应启动、查询、停止搜表命令【模拟】
INT8U CTESTSearchMeter_M::TestCjqNoAck(void )
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	ChangeAmtBps(9600);
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	 sNoAckDiMsg  noackMsg;
	 gSimMeter.ClrALLNoAckDi();
	gSimMeter.SetNoAckDi(0x0B0A0B0A);
	gSimMeter.SetNoAckDi(0x0B0D0B0D);
	
	
	gSimMeter.SetAmtAddBp(0);
	gSimMeter.SetSearchSta(32,32,0,0);
	 ack = gSimJzq.SetNodeAdd(0,32);
	 ack=StartSearchMeter(2,3);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,0x01,DstDecodeDataFrame);
	ack=CmpCjqOnSearchAmt(0,0,0,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);

    gSimMeter.QueNoDiAckmsg(0x0B0A0B0A,noackMsg);
	ack=gSimMeter.CheckNoDiAckmsg(noackMsg);
	StaSucessCnt(ack,resucnt,refailcnt);

	gSimMeter.QueNoDiAckmsg(0x0B0D0B0D,noackMsg);
	ack=gSimMeter.CheckNoDiAckmsg(noackMsg);
	StaSucessCnt(ack,resucnt,refailcnt);
	 gSimMeter.ClrALLNoAckDi();
	 ack = QueAckFormAckCnt(refailcnt);
	  return ack;
}


//	全STA的搜表测试【模拟】测试回确认0x01、否认0x02,SEQ错0x03,不回复0x04
INT8U CTESTSearchMeter_M::TestSearchAllSta(INT16U vSrcCnt,INT8U ackType)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	 
	ChangeAmtBps(1200);
	  ack = gSimJzq.Router_PaRst();
	 ack = gSimJzq.SetNodeAdd(0,vSrcCnt);
	  gSimMeter.SetAmtAddBp(0);
	  NodeSeqHardRst(0);

	 ack=StartSearchMeter(60,3);
	 StaSucessCnt(ack,resucnt,refailcnt);

	 for(INT16U m=0;m<vSrcCnt;m++)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		 if((ackType==0x01)||(ackType==0x02))
        {
		 ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,ackType,DstDecodeDataFrame);
		
		}
		else
		{
           if((m==1)||(m==2)||(m==4))
		{
			ack = TestStaOnNetAckOKNoNoAckSeqErr_Amt(ackType,DstDecodeDataFrame);
		}
		   else
		   {
			   ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,0x01,DstDecodeDataFrame);
		   }
		 }
		  StaSucessCnt(ack,resucnt,refailcnt);
    	  ack=CmpStaOnSearchAmt(m,DstDecodeDataFrame);
	      StaSucessCnt(ack,resucnt,refailcnt);
		  gSimMeter.SetAmtAddBp(m+1);
	      NodeSeqHardRst(m);
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


//	全采集器的搜表测试【模拟】vSrcCnt:采集器的数量，块挂32块表
INT8U CTESTSearchMeter_M::TestSearchAllCjq(INT16U vSrcCnt)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	 
	ChangeAmtBps(9600);
	  ack = gSimJzq.Router_PaRst();
	 ack = gSimJzq.SetNodeAdd(0,vSrcCnt*32);
	  gSimMeter.SetAmtAddBp(0);
	  NodeSeqHardRst(0);

	 ack=StartSearchMeter(60,3);
	 StaSucessCnt(ack,resucnt,refailcnt);

	 for(INT16U m=0;m<vSrcCnt;m++)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		  gSimMeter.SetSearchSta(32,32,m*32,0);
		  ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,0x01,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
    	  ack=CmpCjqOnSearchAmt(m,m*32,32,DstDecodeDataFrame);
	      StaSucessCnt(ack,resucnt,refailcnt);
		  gSimMeter.SetAmtAddBp(m*32);
	      NodeSeqHardRst(m);
	 }

	 ack = gSimJzq.SearthMeterOpAFN06F2(60*1000*5,50,0x01,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=gSimJzq.ZjqNoRcvData(60*1000*3,50);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = gSimJzq.HostSendRcv376_2NoBuf_NoAck(0x11,F6);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpStaSearchAmt(1,vSrcCnt*32,0,vSrcCnt*32);
	 StaSucessCnt(ack,resucnt,refailcnt);
	
	 for(INT16U m=0;m<vSrcCnt;m++)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		 ack=CmpCjqMacAmt(m*32+1,32,m*32,32,m*32,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
	 }
	 ack = gSimJzq.RouterHardRst();
	  Sleep(1000*10);
	 StaSucessCnt(ack,resucnt,refailcnt);
	   ack=CmpStaSearchAmt(1,vSrcCnt*32,0,vSrcCnt*32);
	 StaSucessCnt(ack,resucnt,refailcnt);
	
	 for(INT16U m=0;m<vSrcCnt;m++)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		 ack=CmpCjqMacAmt(m*32+1,32,m*32,32,m*32,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
	 }

	 ack = QueAckFormAckCnt(refailcnt);
	  return ack;
}


//混合模式的搜表测试【模拟】
INT8U CTESTSearchMeter_M::TestSearchStaCjq(INT16U vSrcCnt)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	 
	ChangeAmtBps(1200);
	  ack = gSimJzq.Router_PaRst();
	 ack = gSimJzq.SetNodeAdd(0,vSrcCnt);
	  gSimMeter.SetAmtAddBp(0);
	  NodeSeqHardRst(0);

	 ack=StartSearchMeter(60,3);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 INT16U m=0;
	 for(;(m<vSrcCnt)&&(m<5);m++)
	{
		  ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,0x01,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
    	  ack=CmpStaOnSearchAmt(m,DstDecodeDataFrame);
	      StaSucessCnt(ack,resucnt,refailcnt);
		  gSimMeter.SetAmtAddBp(m+1);
	      NodeSeqHardRst(m);
	 }
	 
	ChangeAmtBps(9600);
		for(;(m<vSrcCnt)&&(m<32);)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		  gSimMeter.SetSearchSta(27,27,m,0);
		  ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,0x01,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
    	  ack=CmpCjqOnSearchAmt(m,m,27,DstDecodeDataFrame);
	      StaSucessCnt(ack,resucnt,refailcnt);
		  gSimMeter.SetAmtAddBp(m+27);
	      NodeSeqHardRst(m);
		  m+=27;
	 }
			for(;(m<vSrcCnt)&&(m<64);)
	{
		  gSimMeter.SetSearchSta(32,32,m,0);
		  ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,0x01,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
    	  ack=CmpCjqOnSearchAmt(m,m,32,DstDecodeDataFrame);
	      StaSucessCnt(ack,resucnt,refailcnt);
		  gSimMeter.SetAmtAddBp(m+32);
	      NodeSeqHardRst(m);
		  m+=32;
	 }
			
	ChangeAmtBps(1200);
    for(;(m<vSrcCnt)&&(m<512);m++)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		  ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,0x01,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
    	  ack=CmpStaOnSearchAmt(m,DstDecodeDataFrame);
	      StaSucessCnt(ack,resucnt,refailcnt);
		  gSimMeter.SetAmtAddBp(m+1);
	      NodeSeqHardRst(m);
	 }
	
	ChangeAmtBps(9600);
	 	for(;(m<vSrcCnt)&&(m<1024);)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		  gSimMeter.SetSearchSta(32,32,m,0);
		  ack = gSimJzq.SearthMeterOpAFN06F4(60*1000*5,50,0x01,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
    	  ack=CmpCjqOnSearchAmt(m,m,32,DstDecodeDataFrame);
	      StaSucessCnt(ack,resucnt,refailcnt);
		  gSimMeter.SetAmtAddBp(m+32);
	      NodeSeqHardRst(m);
		  m+=32;
	 }
	 ack = gSimJzq.SearthMeterOpAFN06F2(60*1000*5,50,0x01,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=gSimJzq.ZjqNoRcvData(60*1000*3,50);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = gSimJzq.HostSendRcv376_2NoBuf_NoAck(0x11,F6);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack=CmpStaSearchAmt(1,vSrcCnt,0,vSrcCnt);
	 StaSucessCnt(ack,resucnt,refailcnt);
	//-------------------------------------
	 m=0;
    for(;(m<vSrcCnt)&&(m<5);m++)
	{
		  ack = CmpStaMacAmt(m+1,5,m,5,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
	 }
	 

		 	for(;(m<vSrcCnt)&&(m<32);)
	{
		 ack=CmpCjqMacAmt(m+1,27,m,27,m,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
		  m=32;
	 }
		 	for(;(m<vSrcCnt)&&(m<64);)
	{
		 ack=CmpCjqMacAmt(m+1,32,m,32,m,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
		  m+=32;
	 }

    for(;(m<vSrcCnt)&&(m<512);)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		   ack = CmpStaMacAmt(m+1,32,m,32,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		  m+=32;
	 }
	 	for(;(m<vSrcCnt)&&(m<1024);m++)
	{
		  ack=CmpCjqMacAmt(m+1,32,m,32,m,DstDecodeDataFrame);
	 	  StaSucessCnt(ack,resucnt,refailcnt);
		  m+=32;
	 }
	 ack = gSimJzq.RouterHardRst();
	  StaSucessCnt(ack,resucnt,refailcnt);

	  Sleep(1000*10);
	//---------------------------------------------
	   ack=CmpStaSearchAmt(1,vSrcCnt*32,0,vSrcCnt*32);
	 StaSucessCnt(ack,resucnt,refailcnt);
	
	 m=0;
    for(;(m<vSrcCnt)&&(m<5);m++)
	{
		  ack = CmpStaMacAmt(m+1,5,m,5,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
	 }
	 

		 	for(;(m<vSrcCnt)&&(m<32);)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		 ack=CmpCjqMacAmt(m+1,27,m,27,m,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
		  m=32;
	 }
		 	for(;(m<vSrcCnt)&&(m<64);)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		 ack=CmpCjqMacAmt(m+1,32,m,32,m,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
		  m+=32;
	 }

    for(;(m<vSrcCnt)&&(m<512);)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		   ack = CmpStaMacAmt(m+1,32,m,32,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		  m+=32;
	 }
	 	for(;(m<vSrcCnt)&&(m<1024);m++)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		  ack=CmpCjqMacAmt(m+1,32,m,32,m,DstDecodeDataFrame);
	 	  StaSucessCnt(ack,resucnt,refailcnt);
		  m+=32;
	 }

	 ack = QueAckFormAckCnt(refailcnt);
	  gSimMeter.SetAmtAddBp(0);
	  
	ChangeAmtBps(1200);
	  return ack;
}

INT8U CTESTSearchMeter_M::CmpMacIsOk(INT16U AmtBp,INT16U MacBp,INT32U WaitTimeS)
{

	 INT8U ack;
	 INT8U reack=DACK_FAILURE;
	   sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		for(INT32U m = 0; m<WaitTimeS; m++)
		{
        ack =gSimJzq. HostSendRcv376_2Buf(0x10,F201,gSimJzq.QueNodeBufAdd(AmtBp),6,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
		if((ack == DACK_SUCESS)&&(DstDecodeDataFrame.s_RcvDataLen==23))
		{
            if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[0],gSimJzq.QueNodeBufAdd(AmtBp),6)==EQU)
			{
				 if(CompareNBuf(&DstDecodeDataFrame.s_RcvDataBuf[6],gSimJzq.QueNodeBufAdd(MacBp),6)==EQU)
				{
				 reack = DACK_SUCESS;
				
				break;
				}
			}
			if(CmpBufIsValue(&DstDecodeDataFrame.s_RcvDataBuf[6],6,0)==DACK_FAILURE)
			{
                break;
			}
			Sleep(1000);
		}
	}
	return reack;
}
//全STA的MAC地址影射测试【模拟】
INT8U CTESTSearchMeter_M::TestMACAllSta(INT16U vSrcCnt)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	
	ChangeAmtBps(1200);
	  ack = gSimJzq.Router_PaRst();
	 ack = gSimJzq.SetNodeAdd(0,vSrcCnt);
	  gSimMeter.SetAmtAddBp(0);
	  NodeSeqHardRst(0);

	 for(INT16U m=0;m<vSrcCnt;m++)
	{
		ack=CmpMacIsOk(m,m,60*5);
		StaSucessCnt(ack,resucnt,refailcnt); 
		gSimMeter.SetAmtAddBp(m+1);
		NodeSeqHardRst(m);
	 }
	 ack=CmpStaMacAmt(1,vSrcCnt,0,vSrcCnt,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);
	 ack = gSimJzq.RouterHardRst();
	  Sleep(1000*10);
	 ack=CmpStaMacAmt(1,vSrcCnt,0,vSrcCnt,DstDecodeDataFrame);
	 StaSucessCnt(ack,resucnt,refailcnt);

	 ack = QueAckFormAckCnt(refailcnt);
	  return ack;
}

//全采集器的MAC地址影射测试【模拟】vSrcCnt指采集器块数，每块32只
INT8U CTESTSearchMeter_M::TestMACAllCjq(INT16U vSrcCnt)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	
	ChangeAmtBps(9600);
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	 
	  ack = gSimJzq.Router_PaRst();
	 ack = gSimJzq.SetNodeAdd(0,vSrcCnt*32);
	  gSimMeter.SetAmtAddBp(0);
	  NodeSeqHardRst(0);

	 ack=StartSearchMeter(60,3);
	 StaSucessCnt(ack,resucnt,refailcnt);

	
	 for(INT16U m=0;m<vSrcCnt;m++)
	{
		ack=CmpMacIsOk(m*32,m*32+1,60*5);
		StaSucessCnt(ack,resucnt,refailcnt); 
		gSimMeter.SetAmtAddBp((m+1)*32);
		NodeSeqHardRst(m);
		if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
	 }

	 
	 for(INT16U m=0;m<vSrcCnt;m++)
	{
		 ack=CmpCjqMacAmt(m*32+1,32,m*32,32,m*32,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
	 }
	 ack = gSimJzq.RouterHardRst();
	  StaSucessCnt(ack,resucnt,refailcnt);
	  Sleep(1000*10);
	
	  
	 for(INT16U m=0;m<vSrcCnt;m++)
	{
		 ack=CmpCjqMacAmt(m*32+1,32,m*32,32,m*32,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
	 }
	  gSimMeter.SetAmtAddBp(0);
	 ack = QueAckFormAckCnt(refailcnt);
	  return ack;
}


//混合模式的MAC地址影射测试【模拟】
INT8U CTESTSearchMeter_M::TestMACStaCjq(INT16U vSrcCnt)
{
INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	 
	ChangeAmtBps(1200);
	  ack = gSimJzq.Router_PaRst();
	 ack = gSimJzq.SetNodeAdd(0,vSrcCnt);
	  gSimMeter.SetAmtAddBp(0);
	  NodeSeqHardRst(0);

	
	 INT16U m=0;
	 for(;(m<vSrcCnt)&&(m<5);m++)
	{
		ack=CmpMacIsOk(m,m,60*5);
		StaSucessCnt(ack,resucnt,refailcnt); 
		gSimMeter.SetAmtAddBp(m+1);
		NodeSeqHardRst(m);
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
	 }
	 
	ChangeAmtBps(9600);
		for(;(m<vSrcCnt)&&(m<32);)
	{
		  ack=CmpMacIsOk(m,m,60*5);
	      StaSucessCnt(ack,resucnt,refailcnt);
		  gSimMeter.SetAmtAddBp(m+27);
	      NodeSeqHardRst(m);
		  m+=27;
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
	 }
			for(;(m<vSrcCnt)&&(m<64);)
	{
		  ack=CmpMacIsOk(m,m,60*5);
	      StaSucessCnt(ack,resucnt,refailcnt);
		  gSimMeter.SetAmtAddBp(m+32);
	      NodeSeqHardRst(m);
		  m+=32;
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
	 }

			
	ChangeAmtBps(1200);
    for(;(m<vSrcCnt)&&(m<512);m++)
	{
		  ack=CmpMacIsOk(m,m,60*5);
	      StaSucessCnt(ack,resucnt,refailcnt);
		  gSimMeter.SetAmtAddBp(m+1);
	      NodeSeqHardRst(m);
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
	 }
	
	ChangeAmtBps(9600);
	 	for(;(m<vSrcCnt)&&(m<1024);)
	{
		  ack=CmpMacIsOk(m,m,60*5);
	      StaSucessCnt(ack,resucnt,refailcnt);
		  gSimMeter.SetAmtAddBp(m+32);
	      NodeSeqHardRst(m);
		  m+=32;
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
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
	//-------------------------------------
	 m=0;
    for(;(m<vSrcCnt)&&(m<5);m++)
	{
		  ack = CmpStaMacAmt(m+1,5,m,5,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
	 }
	 

		 	for(;(m<vSrcCnt)&&(m<32);)
	{
		 ack=CmpCjqMacAmt(m+1,27,m,27,m,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
		  m=32;
	 }
		 	for(;(m<vSrcCnt)&&(m<64);)
	{
		 ack=CmpCjqMacAmt(m+1,32,m,32,m,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
		  m+=32;
	 }

    for(;(m<vSrcCnt)&&(m<512);)
	{
		   ack = CmpStaMacAmt(m+1,32,m,32,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		  m+=32;
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
	 }
	 	for(;(m<vSrcCnt)&&(m<1024);m++)
	{
		  ack=CmpCjqMacAmt(m+1,32,m,32,m,DstDecodeDataFrame);
	 	  StaSucessCnt(ack,resucnt,refailcnt);
		  m+=32;
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
	 }
	 ack = gSimJzq.RouterHardRst();
	  StaSucessCnt(ack,resucnt,refailcnt);

	  Sleep(1000*10);
	//---------------------------------------------
	   ack=CmpStaSearchAmt(1,vSrcCnt*32,0,vSrcCnt*32);
	 StaSucessCnt(ack,resucnt,refailcnt);
	
	 m=0;
    for(;(m<vSrcCnt)&&(m<5);m++)
	{
		  ack = CmpStaMacAmt(m+1,5,m,5,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
	 }
	 

		 	for(;(m<vSrcCnt)&&(m<32);)
	{
		 ack=CmpCjqMacAmt(m+1,27,m,27,m,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
		  m=32;
	 }
		 	for(;(m<vSrcCnt)&&(m<64);)
	{
		 ack=CmpCjqMacAmt(m+1,32,m,32,m,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
		  m+=32;
	 }

    for(;(m<vSrcCnt)&&(m<512);)
	{
		   ack = CmpStaMacAmt(m+1,32,m,32,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		  m+=32;
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
	 }
	 	for(;(m<vSrcCnt)&&(m<1024);m++)
	{
		 if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		  ack=CmpCjqMacAmt(m+1,32,m,32,m,DstDecodeDataFrame);
	 	  StaSucessCnt(ack,resucnt,refailcnt);
		  m+=32;
	 }

	 ack = QueAckFormAckCnt(refailcnt);
	  gSimMeter.SetAmtAddBp(0);
	  
	ChangeAmtBps(1200);
	  return ack;
}


//MAC地址重复影射测试【模拟】
INT8U CTESTSearchMeter_M::TestMACRePeat(void)
{
	INT8U ack = DACK_FAILURE;
	INT16U resucnt=0;
	INT16U refailcnt=0;
	INT16U vSrcCnt =32;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	 
	ChangeAmtBps(9600);
	  ack = gSimJzq.Router_PaRst();
	 ack = gSimJzq.SetNodeAdd(0,32*32);
	  gSimMeter.SetAmtAddBp(0);
	  NodeSeqHardRst(0);

	 ack=StartSearchMeter(60,3);
	 StaSucessCnt(ack,resucnt,refailcnt);

	
	for(INT16U n=0;n<10;n++)
	{

		if (m_hThreadsend==NULL)//用于中途停止测试
			{
				break;
			}
		 for(INT16U m=0;m<vSrcCnt;m++)
		{
			ack=CmpMacIsOk(m*32,n+m,60*5);
			StaSucessCnt(ack,resucnt,refailcnt); 
			gSimMeter.SetAmtAddBp(n+m);
			NodeSeqHardRst(m);
		 }

		 for(INT16U m=0;m<vSrcCnt;m++)
		{
		  ack=CmpCjqMacAmt(m*32+1,32,m*32,32,n+m,DstDecodeDataFrame);
		  StaSucessCnt(ack,resucnt,refailcnt);
		 }
	}
	 
	 for(INT16U m=0;m<vSrcCnt;m++)
	{
		ack=CmpMacIsOk(m*32,m*32+1,60*5);
		StaSucessCnt(ack,resucnt,refailcnt); 
		gSimMeter.SetAmtAddBp((m+1)*32);
		NodeSeqHardRst(m);
	 }

	 for(INT16U m=0;m<vSrcCnt;m++)
	{
		 ack=CmpCjqMacAmt(m*32+1,32,m*32,32,m*32,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
	 }
	 ack = gSimJzq.RouterHardRst();
	  StaSucessCnt(ack,resucnt,refailcnt);
	  Sleep(1000*20);
	
	  
	 for(INT16U m=0;m<vSrcCnt;m++)
	{
		 ack=CmpCjqMacAmt(m*32+1,32,m*32,32,m*32,DstDecodeDataFrame);
		 StaSucessCnt(ack,resucnt,refailcnt);
	 }
	  gSimMeter.SetAmtAddBp(0);
	 ack = QueAckFormAckCnt(refailcnt);
	 
	ChangeAmtBps(1200);
	  return ack;
}