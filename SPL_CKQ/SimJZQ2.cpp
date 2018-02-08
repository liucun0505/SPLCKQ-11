#include "StdAfx.h"

#include "KD_Project.h"
#include "MainFrm.h"
#include "cSerBuf_LoopRcv.h"
extern cSerBuf_LoopRcv  m_loopRcv64507;
extern cSerBuf_LoopRcv m_loopRcv13762;

#include "GW13762.h"
extern CGW13762 Cgw13762;
#include "CSG13762.h"
extern CCSG13762 Ccsg13762;
#include "SimJZQ.h"


#include "MyFunLib.h"

#include "SimMeter.h"
extern CSimMeter  gSimMeter;

#include "LogFile.h"
extern CLogFile plog;//打引用


void CSimJzq::SetMainAdd(INT8U * uMainAddress)
{
	#ifdef _STD_CSG  //南网标准
	Ccsg13762.SetMainAdd(uMainAddress);
	#endif
	Cgw13762.SetMainAdd(uMainAddress);
}
void CSimJzq::ClrZjqComData(void)
{
	m_loopRcv13762.ClrRcvBuf();
}
INT8U * CSimJzq::QueNodeBufAdd(INT16U vNodeBp)
{
	if(vNodeBp<D_MaxNodeCnt)
	{
		return(INT8U*)(&gNodeAddBuf[vNodeBp][0]);
	}
	else
	{
		return(INT8U*)(&gNodeAddBuf[0][0]);
	}
}
//376.2的通用函数
//从串口获取数据，nType=0 为 模拟集中器串口，nType=1 为 模拟表串口，
void CSimJzq::GetCOMM376_2ToBuf(INT16U  getLen , INT32U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen)
{
	INT16U len = 0;
	INT32U dlycnt=0;
	INT16U acklen;
	INT16U tmp16;
	INT8U ack;
	while(true)
	{

		len = m_loopRcv13762.LoopReadRcvBufNByte(1 , recvbuf );

		if (1 == len) 
		{
			break;
		}
		if(nWaitFramTime >0 )
		{
			Sleep(10);
		}
		if (dlycnt == nWaitFramTime/10)
		{
			recvlen = 0;
			return ;
		}
		dlycnt++;
	}

	for(;len < getLen; )
	{

		tmp16= m_loopRcv13762.LoopReadRcvBufNByte(1, &recvbuf[len] );
		if( tmp16 ==0)
		{
			if(nWaiteByteTime > 0)
			{
				Sleep(nWaiteByteTime);
			}
			tmp16= m_loopRcv13762.LoopReadRcvBufNByte(1, &recvbuf[len] );
			if( tmp16 ==0)
			{
				break;
			}
		}
		len  += tmp16;
#ifdef _STD_CSG  //南网标准
		ack = Ccsg13762.Check_376_2_Full(recvbuf,len,acklen);
#else
		ack = Cgw13762.Check_376_2_Full(recvbuf,len,acklen);
#endif
		if( ack == DACK_SUCESS)
		{
			break;
		}


	}
	recvlen = len;
}
INT8U CSimJzq::HostSendRcv376_2NoBuf_NoAck(INT8U vSrcAFN,INT16U vSrcFn)//针对无数据单元只回确认否认帧类型的判断
{
	INT8U ack;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	ack = HostSendRcv376_2NoBuf(vSrcAFN,vSrcFn,sQGDW376_2HostFrame,DstDecodeDataFrame);
	sAckTimeSta  ackSta;
	ackSta.timeclk = GetSysTimeClk();
	ackSta.s_Seq = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
	ackSta.ackFg=0;
	if(sQGDW376_2HostFrame.s_head.s_Msg_Seq == DstDecodeDataFrame.s_head.s_Msg_Seq)
	{
		if((DstDecodeDataFrame.s_head.s_AFN == 0x00) &&(DstDecodeDataFrame.s_head.s_FN == F1))
		{
			ack = DACK_SUCESS;
		}
		else if((DstDecodeDataFrame.s_head.s_AFN == 0x00) &&(DstDecodeDataFrame.s_head.s_FN == F2))
		{
			ack =DstDecodeDataFrame.s_RcvDataBuf[0];
		}

		else
		{
			ack = DACK_FAILURE;
		}
	}
	else
	{
		ack = DACK_EER_SEQERR;
	}
	CmpAckTimeClk(1,DstDecodeDataFrame,ack,&ackSta);
	plog.saveLog_ClkSta(&ackSta,1,DATA_FILE,NOTIME,_T("单帧结果"),1);      
	return ack;
}
INT8U CSimJzq::HostSendRcv376_2Buf_NoAck(INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen)//设置专用
{
	INT8U ack;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	ack =HostSendRcv376_2Buf(vSrcAFN,vSrcFn,vSrcBuf,vSrcLen,sQGDW376_2HostFrame,DstDecodeDataFrame);
	if(sQGDW376_2HostFrame.s_head.s_Msg_Seq == DstDecodeDataFrame.s_head.s_Msg_Seq)
	{
		if((DstDecodeDataFrame.s_head.s_AFN == 0x00) &&(DstDecodeDataFrame.s_head.s_FN == F1))
		{
			ack = DACK_SUCESS;
		}
		else if((DstDecodeDataFrame.s_head.s_AFN == 0x00) &&(DstDecodeDataFrame.s_head.s_FN == F2))
		{
			ack =DstDecodeDataFrame.s_RcvDataBuf[0];
		}

		else
		{
			ack = DACK_FAILURE;
		}
	}
	else
	{
		ack = DACK_EER_SEQERR;
	}     
	return ack;
}
INT8U CSimJzq::HostSendRcv376_2MsgAddrBuf(INT8U vSrcCn,INT8U * vSrcMsgAddr,INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp)
{
	INT8U ack;

	ack = Cgw13762.Code376_2_F0F008Data(vSrcCn ,vSrcMsgAddr ,vSrcAFN,vSrcFn,vSrcBuf,vSrcLen,sQGDW376_2HostFrame);//无节点
	sAckTimeSta  ackSta;
	ackSta.timeclk = GetSysTimeClk();
	ackSta.s_Seq = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
	ackSta.ackFg=0;
	if(ack == DACK_SUCESS)
	{
		for(INT8U mm = 0; mm < 1; mm ++)
		{
			SendHost3762ToCom(sQGDW376_2HostFrame);
			if(vSrcAckCmp == 0)
			{
				ack = Wait3762AckCmpSeq(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
			}
			else
			{
				ack = Wait3762AckCmpAFNFN(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
			}
			if(ack == DACK_SUCESS)
			{
				break;
			}
		}
	}
	CmpAckTimeClk(1,DstDecodeDataFrame,ack,&ackSta);
	plog.saveLog_ClkSta(&ackSta,1,DATA_FILE,NOTIME,_T("单帧结果"),1);
	return ack;
}
//有数据单元的组帧
INT8U CSimJzq::HostSendRcv376_2Buf(INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp)
{
	INT8U ack;
	
	ack = Cgw13762.Code376_2_HostBufFrame(vSrcAFN,vSrcFn,vSrcBuf,vSrcLen,sQGDW376_2HostFrame);//无节点
	sAckTimeSta  ackSta;
	ackSta.timeclk = GetSysTimeClk();
    ackSta.s_Seq = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
	ackSta.ackFg=0;

	if(ack == DACK_SUCESS)
	{
	  for(INT8U mm = 0; mm < 1; mm ++)
	  {
		SendHost3762ToCom(sQGDW376_2HostFrame);
		if(vSrcAckCmp == 0)
		{
			ack = Wait3762AckCmpSeq(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
		}
		else
		{
			ack = Wait3762AckCmpAFNFN(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
		}
		if(ack == DACK_SUCESS)
		{
			break;
		}
	  }
	}
	CmpAckTimeClk(1,DstDecodeDataFrame,ack,&ackSta);
	plog.saveLog_ClkSta(&ackSta,1,DATA_FILE,NOTIME,_T("单帧结果"),1);
     return ack;
 }
//376.2的通用函数 无数据单元的
 INT8U CSimJzq::HostSendRcv376_2NoBuf(INT8U vSrcAFN,INT16U vSrcFn,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp)
 {
    INT8U ack;

	ack = Cgw13762.Code376_2_HostFrame(vSrcAFN,vSrcFn,sQGDW376_2HostFrame);
	sAckTimeSta  ackSta;
	ackSta.timeclk = GetSysTimeClk();
	ackSta.s_Seq = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
	ackSta.ackFg=0;
	if(ack == DACK_SUCESS)
	{
		for(INT8U mm = 0; mm < 1; mm ++)
		{
			SendHost3762ToCom(sQGDW376_2HostFrame);
			if(vSrcAckCmp == 0)
			{
				ack = Wait3762AckCmpSeq(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
			}
			else
			{
				ack = Wait3762AckCmpAFNFN(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
			}
			if(ack == DACK_SUCESS)
			{
				break;
			}
		}
	}

	CmpAckTimeClk(1,DstDecodeDataFrame,ack,&ackSta);
	plog.saveLog_ClkSta(&ackSta,1,DATA_FILE,NOTIME,_T("单帧结果"),1);
     return ack;
 }
 
 //有目的地址和buf的
INT8U CSimJzq::HostSendRcv376_2BufNode(TH_IN const INT8U *pSrcAddBuf, INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp)
{
	INT8U ack;

	ack = Cgw13762.Code376_2_HostBufNodeFrame(pSrcAddBuf,vSrcAFN,vSrcFn,vSrcBuf,vSrcLen,sQGDW376_2HostFrame);//有目的地址的
	sAckTimeSta  ackSta;
	ackSta.timeclk = GetSysTimeClk();
	ackSta.s_Seq = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
	ackSta.ackFg=0;
	if(ack == DACK_SUCESS)
	{
		for(INT8U mm = 0; mm < 1; mm ++)
		{
			SendHost3762ToCom(sQGDW376_2HostFrame);
			if(vSrcAckCmp == 0)
			{
				ack = Wait3762AckCmpSeq(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
			}
			else
			{
				ack = Wait3762AckCmpAFNFN(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
			}
			if(ack == DACK_SUCESS)
			{
				break;
			}

		}
	}
	CmpAckTimeClk(1,DstDecodeDataFrame,ack,&ackSta);
	plog.saveLog_ClkSta(&ackSta,1,DATA_FILE,NOTIME,_T("单帧结果"),1);
	return ack;
}

INT8U CSimJzq::HostSendRcv376_2F0F8(TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U SendDatabuf[JZQ_MAX_BUFF_LEN];
	INT16U SendDatalen = 0 ;
	INT16U temp16 = 0;
	INT16U n = 0;
	sPartQGDW376_2CreatFrame ptSendQGDW376_2;
	for(n = 0 ; n < vSrcLen ; n++)
	{
		ptSendQGDW376_2.s_SendDataBuf[n] = vSrcBuf[n];
	}
	ptSendQGDW376_2.s_SendDataLen = vSrcLen;

	if (vSrcLen != 0)
	{
		Cgw13762.Code376_2_HostBufFrame(vSrcAfn,vSrcFn,vSrcBuf,vSrcLen ,ptSendQGDW376_2);
	}
	else
	{
		Cgw13762.Code376_2_HostFrame(vSrcAfn,vSrcFn,ptSendQGDW376_2);
	}
	
	m_tools.Buf_To_LenBuf(ptSendQGDW376_2.s_SendDataBuf , ptSendQGDW376_2.s_SendDataLen , SendDatabuf , SendDatalen );
	//南网扩展标记
	INT8U ack = HostSendRcv376_2BufNode(pSrcAddBuf , 0xF0 , F8 , SendDatabuf , SendDatalen , sQGDW376_2HostFrame , DstDecodeFrame);
	switch(ack)
	{
	case 0:
		temp16 = DstDecodeFrame.s_RcvDataBuf[1]<<8 | DstDecodeFrame.s_RcvDataBuf[0];
		if ((temp16 + 2) == DstDecodeFrame.s_RcvDataLen)
		{
			ack = Cgw13762.Decode376_2Frame(&DstDecodeFrame.s_RcvDataBuf[2] , temp16 , DstDecodeDataFrame);
		}
		break;
	}
	return ack;
}
INT8U CSimJzq::HostSendRcv376_2F0F8MsgAddrBuf(INT8U vSrcCn,INT8U * vSrcMsgAddr, TH_IN const INT8U *pSrcAddBuf, TH_IN INT8U vSrcAfn,TH_IN INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U SendDatabuf[JZQ_MAX_BUFF_LEN];
	INT16U SendDatalen = 0 ;
	INT16U temp16 = 0;
	INT16U n = 0;
	sPartQGDW376_2CreatFrame ptSendQGDW376_2;

	Cgw13762.Code376_2_F0F008Data(vSrcCn , vSrcMsgAddr ,vSrcAfn , vSrcFn , vSrcBuf , vSrcLen , ptSendQGDW376_2);
	m_tools.Buf_To_LenBuf(ptSendQGDW376_2.s_SendDataBuf , ptSendQGDW376_2.s_SendDataLen , SendDatabuf , SendDatalen );
	//南网扩展标记
	INT8U ack = HostSendRcv376_2BufNode(pSrcAddBuf , 0xF0 , F8 , SendDatabuf , SendDatalen , sQGDW376_2HostFrame , DstDecodeFrame);
	switch(ack)
	{
	case 0:
		temp16 = DstDecodeFrame.s_RcvDataBuf[1]<<8 | DstDecodeFrame.s_RcvDataBuf[0];
		if ((temp16 + 2) == DstDecodeFrame.s_RcvDataLen)
		{
			ack = Cgw13762.Decode376_2Frame(&DstDecodeFrame.s_RcvDataBuf[2] , temp16 , DstDecodeDataFrame);
		}
		break;
	}
	return ack;
}
//以下收发分开-有vSrcBuf-无vSrcBuf-收
INT8U CSimJzq::HostSend376_2Buf(INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame)
{
	INT8U ack;

	ack = Cgw13762.Code376_2_HostBufFrame(vSrcAFN,vSrcFn,vSrcBuf,vSrcLen,sQGDW376_2HostFrame);
	if(ack == DACK_SUCESS)
	{
		SendHost3762ToCom(sQGDW376_2HostFrame);
	}
	return ack;
}

//376.2的通用函数
INT8U CSimJzq::HostSend376_2NoBuf(INT8U vSrcAFN,INT16U vSrcFn,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame)
{
	INT8U ack;

	ack = Cgw13762.Code376_2_HostFrame(vSrcAFN,vSrcFn,sQGDW376_2HostFrame);
	if(ack == DACK_SUCESS)
	{	
		SendHost3762ToCom(sQGDW376_2HostFrame);	
	}
	return ack;
}

INT8U CSimJzq::HostRcv376_2( INT32U nWaitFramTime , INT16U nWaiteByteTime ,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U ack = DACK_FAILURE;

	ack = Wait3762Ack(nWaitFramTime,nWaiteByteTime,DstDecodeDataFrame);

	return ack;
}
void CSimJzq::SendBufToCom(INT8U *vSrcBuf,INT16U vSrcLen)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	pMainDlg->SendBufToCOMM(vSrcBuf ,vSrcLen , 0);	
	plog.saveLog_HexBuf(DATA_FILE,OUTPUT,vSrcBuf,vSrcLen);//打印发送帧数据

}
void CSimJzq::SendHost3762ToCom(sPartQGDW376_2CreatFrame sQGDW376_2HostFrame)
{
	SendBufToCom(sQGDW376_2HostFrame.s_SendDataBuf ,sQGDW376_2HostFrame.s_SendDataLen );
	plog.saveInformation_send(sQGDW376_2HostFrame);

}
INT8U   CSimJzq::Wait3762Ack(INT32U nWaitFramTime , INT16U nWaiteByteTime,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	INT8U ack = DACK_FAILURE;
	INT8U recvbuf[D376_MAXRCVBUFLEN];
	INT16U recvbuflen=0;
	int nItem = 0;
	GetCOMM376_2ToBuf(D376_MAXRCVBUFLEN , nWaitFramTime , nWaiteByteTime , recvbuf , recvbuflen);
	if(recvbuflen>0)
	{
		ack = Cgw13762.Decode376_2Frame(recvbuf,recvbuflen,DstDecodeDataFrame);
		plog.saveLog_HexBuf(DATA_FILE,INPUT_DATA,recvbuf,recvbuflen);//打印接收帧数据
		nItem = pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemCount();
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.InsertItem( nItem,pMainDlg-> m_strSysDateTime);
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 1, _T("接收<<"));
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 2 , pMainDlg->m_tools._buf16tostr16(recvbuf , recvbuflen , true));
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.EnsureVisible(nItem,FALSE);
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.RedrawItems(nItem,nItem);
		if(ack == DACK_SUCESS)
		{
			plog.saveInformation_rev(DstDecodeDataFrame);
		}
		else
		{
		    plog.saveLog_err(DATA_FILE,NOTIME,_T(""),DACK_ERR_FORMAT);
		}

	}
	return ack;
}
INT8U   CSimJzq::Wait3762AckCmpSeq(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U reack = DACK_FAILURE;
	INT8U ack = Wait3762Ack(nWaitFramTime,nWaiteByteTime,DstDecodeDataFrame);
	if(ack == DACK_SUCESS)
	{
		reack = ack;
		/*if(sQGDW376_2HostFrame.s_head.s_Msg_Seq == DstDecodeDataFrame.s_head.s_Msg_Seq)
		{
			reack = DACK_SUCESS;
		}
		else
		{
			reack = DACK_EER_SEQERR;
		}*/
	}
	else
	{
		reack = ack;
	}
	return reack;
}
INT8U   CSimJzq::Wait3762AckCmpAFNFN(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U reack = DACK_FAILURE;
	INT8U ack = Wait3762AckCmpSeq(nWaitFramTime,nWaiteByteTime,sQGDW376_2HostFrame,DstDecodeDataFrame);
	if(ack == DACK_SUCESS) 
	{
		if ((sQGDW376_2HostFrame.s_head.s_AFN == DstDecodeDataFrame.s_head.s_AFN)&& (sQGDW376_2HostFrame.s_head.s_FN == DstDecodeDataFrame.s_head.s_FN))
		{
			reack = DACK_SUCESS;
		}
		else
		{
			reack = DACK_EER_CCOCANNOTDO;
		}
	}
	else
	{
		reack = ack;
	}
	return reack;
}


INT8U  CSimJzq::Router_Start(void)
{
	INT8U ack;
	ack = HostSendRcv376_2NoBuf_NoAck(0x12,(INT16U)F1);
	plog.saveLog_testresultAll(TIME,_T("重启路由") ,ack,1);
	return ack;
}
INT8U  CSimJzq::Router_Stop(void)
{
	INT8U ack;
	ack = HostSendRcv376_2NoBuf_NoAck(0x12,(INT16U)F2);
	plog.saveLog_testresultAll(TIME,_T("暂停路由") ,ack,1);
	return ack;
}

INT8U  CSimJzq::Router_Resume(void)
{
	INT8U ack;
	ack = HostSendRcv376_2NoBuf_NoAck(0x12,(INT16U)F3);
	plog.saveLog_testresultAll(TIME,_T("恢复路由") ,ack,1);
	return ack;
}
INT8U  CSimJzq::NodeHardRst(INT8U *vSrcMacAdd)
{
	INT8U ack;
	//南网扩展标记
	ack = HostSendRcv376_2Buf_NoAck(0xF0,(INT16U)F5,vSrcMacAdd,6);
	plog.saveLog_testresultAll(TIME,_T("从节点硬件复位") ,ack,1);
	return ack;
}
INT8U  CSimJzq::RouterHardRst(void)
{
	INT8U ack;
	plog.saveLog_strAll(TIME,_T("开始硬件复位"),1);
	ack = HostSendRcv376_2NoBuf_NoAck(0x01,(INT16U)F1);
	plog.saveLog_testresultAll(TIME,_T("硬件复位") ,ack,0);
	plog.saveLog_strAll(NOTIME,_T(""),1);
	return ack;
}
INT8U  CSimJzq::Router_PaRst(void)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	plog.saveLog_strAll(TIME,_T("开始参数区复位"),1);
	INT8U ack;
	ack = HostSendRcv376_2NoBuf_NoAck(0x01,(INT16U)F2);
	plog.saveLog_testresultAll(TIME,_T("参数区复位") ,ack,0);
	plog.saveLog_strAll(NOTIME,_T(""),1);
	//Sleep(10*1000);
	for (int i=0;i<10;i++)
	{
		CString str;
		Sleep(1000); 
		str.Format(_T("%d秒 "),i);
		//pMainDlg->m_flashData.ReplaceSel(str);
	}
	return ack;
}
INT8U  CSimJzq::Router_DataRst(void)
{
	INT8U ack;
	plog.saveLog_strAll(TIME,_T("开始：数据区复位"),1);
	ack = HostSendRcv376_2NoBuf_NoAck(0x01,(INT16U)F3);
	plog.saveLog_testresultAll(TIME,_T("数据区复位") ,ack,0);
	plog.saveLog_strAll(NOTIME,_T("数据区复位"),1);
	return ack;
}
INT8U CSimJzq::QueNodeCnt(INT16U &vDstCnt)
{
	   INT8U ack = DACK_FAILURE;
	  sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
	  sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
      ack = HostSendRcv376_2NoBuf(0x10,F1,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
		if(ack == DACK_SUCESS)
		{
				ack = DACK_FAILURE; 
			if((DstDecodeDataFrame.s_RcvDataLen ==4))
			{
				ack = DACK_SUCESS;
				vDstCnt= Buf2ToHex16(DstDecodeDataFrame.s_RcvDataBuf);
			}
		}
		plog.saveLog_testresultAll(TIME,_T("查询从节点个数") ,ack,1);
		return ack;
}
//设置从节点
INT8U CSimJzq::SetNodeAdd(INT16U vSrcBp,INT16U vSrcCnt)
{
	INT8U ack = DACK_FAILURE;
	INT8U reack = DACK_FAILURE;
	INT8U tmpbuf[200];
	INT8U cucnt;
	if(((vSrcBp+vSrcCnt) <= gMaxNodeCnt)&&((vSrcBp+vSrcCnt) <= D_MaxNodeCnt))
	{
		reack = DACK_SUCESS;
		for(INT8U m =0;m<vSrcCnt;)
		{
			if((vSrcCnt-m) >= 10)
			{
				tmpbuf[0] = 10;
				for(INT8U n=0; n<10;n++)
				{
					BufToBuf(&tmpbuf[1+n*7],&gNodeAddBuf[vSrcBp+m+n][0],7);
				}
				ack = HostSendRcv376_2Buf_NoAck(0x11,(INT16U)F1,tmpbuf,81);
				m += 10;
				if(ack != DACK_SUCESS)
				{
					reack = ack;
				}
			}
			else
			{
				cucnt = vSrcCnt-m;
				tmpbuf[0] =cucnt;
				for(INT8U n=0; n<cucnt;n++)
				{
					BufToBuf(&tmpbuf[1+n*7],&gNodeAddBuf[vSrcBp+m+n][0],7);
				}
				ack = HostSendRcv376_2Buf_NoAck(0x11,(INT16U)F1,tmpbuf,cucnt*7+1);//添加节点
				if(ack != DACK_SUCESS)
				{
					reack = ack;
				}
				m += cucnt;

			}
		}
	}
	plog.saveLog_testresultAll(TIME,_T("设置从节点") ,ack,1);
	return reack;
}
//比对从节点
INT8U CSimJzq::CmpNodeAdd(INT16U vSrcBp,INT16U vSrcCnt)
{
	INT8U ack = DACK_FAILURE;
	INT8U tmpbuf[200];
	INT16U nodecnt;
	sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	if(((vSrcBp+vSrcCnt) <= gMaxNodeCnt)&&((vSrcBp+vSrcCnt) <= D_MaxNodeCnt))
	{
		Hex16ToBuf2(vSrcBp+1,&tmpbuf[0]);//起始序号
		Hex16ToBuf2(vSrcCnt,&tmpbuf[2]);//个数
		ack = HostSendRcv376_2Buf(0x10,F2,tmpbuf,3,sQGDW376_2HostFrame,DstDecodeDataFrame);
		//ack = HostSendRcv376_2NoBuf(0x13,F1,sQGDW376_2HostFrame,DstDecodeDataFrame);
		if((ack == DACK_SUCESS) && (sQGDW376_2HostFrame.s_head.s_Msg_Seq==DstDecodeDataFrame.s_head.s_Msg_Seq))
		{
			//以下看不懂
			nodecnt=Buf2ToHex16(DstDecodeDataFrame.s_RcvDataBuf);
			for(INT16U m = 0; m <= nodecnt; m++)
			{
				Hex16ToBuf2(1,&tmpbuf[0]);
				Hex16ToBuf2(m,&tmpbuf[2]);
				//ack = HostSendRcv376_2Buf(0x10,F2,tmpbuf,3,sQGDW376_2HostFrame,DstDecodeDataFrame);
				//if((ack == DACK_SUCESS) && (sQGDW376_2HostFrame.s_head.s_Msg_Seq==DstDecodeDataFrame.s_head.s_Msg_Seq))
				//{
					for(INT16U n =0 ;n<vSrcCnt;n++)
					{
						if(CompareNBuf(&gNodeAddBuf[vSrcBp+n][0],&DstDecodeDataFrame.s_RcvDataBuf[3],6)==EQU)
						{
							if(gNodeAddBuf[vSrcBp+n][6] == ((DstDecodeDataFrame.s_RcvDataBuf[10]>>3)&0x07))
							{
								break;
							}
						}
						if((n+1) == vSrcCnt)
							return DACK_FAILURE;
					}
				//}
				//else
				//{
				//	break;
				//}
			}

		}


	}

	return ack;
}
    

INT8U CSimJzq:: CodeReadData9707Cmd(INT8U pcttype,TH_IN const INT32U pSrcDi,TH_IN const INT8U *pSrcAmtAddBuf,TH_IN INT8U type,TH_OUT  sDtl2007_Read &vDstCmdData)
{
	if(pcttype==DPCT_97FG)
	{
		return(CodeReadData97Cmd((INT16U)pSrcDi,pSrcAmtAddBuf,1,vDstCmdData));
	}
	else
	{
		return(CodeReadDataCmd(pSrcDi,pSrcAmtAddBuf,1,vDstCmdData));
	}
 }

INT8U CSimJzq::ReadMeterAFN02F1(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp)
{
	 sAckTimeSta  ackSta;
	 return (ReadMeterAFN02F1AckClk( pSrcAddBuf, vSrcDi,sQGDW376_2HostFrame, DstDecodeDataFrame,ackSta, vSrcAckCmp));
}
INT8U CSimJzq::ReadMeterAFN02F1AckClk(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U vSrcAckCmp)
{
	INT8U ack;	
	INT8U reack = DACK_FAILURE;
	ack =CodeReadMeterAFN02F1Cmd(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame);
	
	ackSta.timeclk = GetSysTimeClk();
    ackSta.s_Seq = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
	ackSta.ackFg=0;
	if(ack == DACK_SUCESS)
	{
	  for(INT8U mm = 0; mm < 1; mm ++)
		{
			SendHost3762ToCom(sQGDW376_2HostFrame);
			if(vSrcAckCmp == 0)
			{
				ack = Wait3762AckCmpSeq(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
			}
			else
			{
				ack = Wait3762AckCmpAFNFN(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
			}
			if(ack == DACK_SUCESS)
			{
				reack = DACK_SUCESS;
				break;
			}
			else
			{
				reack = ack;
			}
		}
	}
	CmpAckTimeClk(1,DstDecodeDataFrame,ack,&ackSta);
	plog.saveLog_ClkSta(&ackSta,1,DATA_FILE,NOTIME,_T("单帧结果"),1);
	return reack;
}
INT8U CSimJzq::CodeReadMeterAFN02F1Cmd(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame)
{

	INT8U tmpbuf[100];
	INT16U len16;
	INT8U ack;			
	sDtl2007_Read CmdData645;
	CodeReadData9707Cmd(pSrcAddBuf[6],vSrcDi,pSrcAddBuf,1,CmdData645);
	tmpbuf[0]=pSrcAddBuf[6];
	tmpbuf[1]=CmdData645.s_vDstCmdLen;
	BufToBuf(&tmpbuf[2],CmdData645.s_pDstCmdBuf,CmdData645.s_vDstCmdLen);
	len16 = CmdData645.s_vDstCmdLen+ 2;
	ack = Cgw13762.Code376_2_HostBufNodeFrame(pSrcAddBuf,0x02,F1,tmpbuf,len16,sQGDW376_2HostFrame);//有目的地址的
	return ack;
}

INT8U CSimJzq::ReadMeterAFN13F1(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp)
{
	 sAckTimeSta  ackSta;
	 return (ReadMeterAFN02F1AckClk( pSrcAddBuf, vSrcDi,sQGDW376_2HostFrame, DstDecodeDataFrame,ackSta, vSrcAckCmp));
}
INT8U CSimJzq::ReadMeterAFN13F1AckClk(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U vSrcAckCmp )
{
	INT8U ack;	
	INT8U reack = DACK_FAILURE;
	ack =CodeReadMeterAFN13F1Cmd(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame);
	ackSta.timeclk = GetSysTimeClk();
    ackSta.s_Seq = sQGDW376_2HostFrame.s_head.s_Msg_Seq;
	ackSta.ackFg=0;
	if(ack == DACK_SUCESS)
	{
	  for(INT8U mm = 0; mm < 1; mm ++)
		{
			SendHost3762ToCom(sQGDW376_2HostFrame);
			if(vSrcAckCmp == 0)
			{
				ack = Wait3762AckCmpSeq(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
			}
			else
			{
				ack = Wait3762AckCmpAFNFN(10000 , 20 ,sQGDW376_2HostFrame,DstDecodeDataFrame);
			}
			if((ack == DACK_SUCESS))
			{
				reack = DACK_SUCESS;
				break;
			}
			else
			{
				reack = ack;
			}
		}
	}
	CmpAckTimeClk(1,DstDecodeDataFrame,ack,&ackSta);
	plog.saveLog_ClkSta(&ackSta,1,DATA_FILE,NOTIME,_T("单帧结果"),1);
	return reack;
}

INT8U CSimJzq::CodeReadMeterAFN13F1Cmd(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame)
{
	INT8U ack;	
	INT8U tmpbuf[100];
	INT16U len16;

	sDtl2007_Read CmdData645;
	CodeReadData9707Cmd(pSrcAddBuf[6],vSrcDi,pSrcAddBuf,1,CmdData645);
	tmpbuf[0]=pSrcAddBuf[6];
	tmpbuf[1]=0;
	tmpbuf[2]=0;
	tmpbuf[3]=CmdData645.s_vDstCmdLen;
	BufToBuf(&tmpbuf[4],CmdData645.s_pDstCmdBuf,CmdData645.s_vDstCmdLen);
	len16 = CmdData645.s_vDstCmdLen+ 4;
	ack = Cgw13762.Code376_2_HostBufNodeFrame(pSrcAddBuf,0x13,F1,tmpbuf,len16,sQGDW376_2HostFrame);//有目的地址的
	return ack;
}

INT8U CSimJzq::ReadMeterAFN02F1AndCmpMter(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType)
{
	 sAckTimeSta  ackSta;
	return(ReadMeterAFN02F1AndCmpMterAckClk(pSrcAddBuf, vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,ackSta,CmpType));
}
INT8U CSimJzq::ReadMeterAFN02F1AndCmpMterAckClk(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U CmpType)
{
	INT8U ack;	
	INT8U reack = DACK_FAILURE;

	gSimMeter.ChangeMeterData(pSrcAddBuf[6],vSrcDi);

	ack = ReadMeterAFN02F1AckClk(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,ackSta,1);
	if(ack == DACK_SUCESS)
	{
           reack = gSimMeter.Cmp645DiData(pSrcAddBuf[6],vSrcDi,DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen,CmpType);
	} 
	else
	{
		reack = ack;

	}
	return reack;
}
INT8U CSimJzq::ReadMeterAFN13F1AndCmpMter(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType)
{
	 sAckTimeSta  ackSta;
	return(ReadMeterAFN13F1AndCmpMterAckClk(pSrcAddBuf, vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,ackSta,CmpType));
}
INT8U CSimJzq::ReadMeterAFN13F1AndCmpMterAckClk(TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U CmpType)
{
	INT8U ack;	
	INT8U reack = DACK_FAILURE;

         gSimMeter.ChangeMeterData(pSrcAddBuf[6],vSrcDi);

	ack = ReadMeterAFN13F1AckClk(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,ackSta,1);
	if((ack == DACK_SUCESS))
	{
            reack = gSimMeter.Cmp645DiData(pSrcAddBuf[6],vSrcDi,DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen,CmpType);

	}
	else
	{
		reack = ack;
	}

	return reack;
}

INT8U CSimJzq::WaitReadMeterAFN02F1AckAndCmp(INT32U famedly,INT16U bytedly, INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType)
{

	INT8U ack;	
	INT8U reack = DACK_FAILURE;

	ack = Wait3762AckCmpAFNFN(famedly , bytedly ,sQGDW376_2HostFrame,DstDecodeDataFrame);
	if((ack == DACK_SUCESS))
	{
		if(DstDecodeDataFrame.s_RcvDataBuf[0] ==sQGDW376_2HostFrame.s_SendDataBuf[26])//协议号的判断 note 这要改一下
		{
				  reack = gSimMeter.Cmp645DiData(DstDecodeDataFrame.s_RcvDataBuf[0],vSrcDi,DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen,CmpType);
		}
		else
		{
			reack = DACK_EER_PCT;
		}
	}
	return reack;
}

INT8U CSimJzq::WaitReadMeterAFN13F1AckAndCmp(INT32U famedly,INT16U bytedly, INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType)
{

	INT8U ack;	
	INT8U reack = DACK_FAILURE;

	ack = Wait3762AckCmpAFNFN(famedly , bytedly ,sQGDW376_2HostFrame,DstDecodeDataFrame);
	if((ack == DACK_SUCESS))
	{
		if(DstDecodeDataFrame.s_RcvDataBuf[0] ==sQGDW376_2HostFrame.s_SendDataBuf[26])//协议号的判断 note 这要改一下
		{
				  reack = gSimMeter.Cmp645DiData(DstDecodeDataFrame.s_RcvDataBuf[0],vSrcDi,DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen,CmpType);
		}
		else
		{
			reack = DACK_EER_PCT;
		}
	}
	return reack;
}

//vSrcType 0: AFN=0x02,F1,1:AFN =13F1,
INT8U CSimJzq::CodeReadMeter3762Cmd(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame)
{
	if(vSrcType==0)
	{
		return(CodeReadMeterAFN02F1Cmd(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame));
	}
	else
	{
		return(CodeReadMeterAFN13F1Cmd(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame));
	}
}

INT8U CSimJzq::ReadMeterAndCmpMter(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType)
{


	if(vSrcType==0)
	{
		return(ReadMeterAFN02F1AndCmpMter(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,CmpType));
	}
	else
	{
		return(ReadMeterAFN13F1AndCmpMter(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame, CmpType));
	}
}
INT8U CSimJzq::ReadMeterAndCmpMterAckClk(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta,INT8U CmpType)
{


	if(vSrcType==0)
	{
		return(ReadMeterAFN02F1AndCmpMterAckClk(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,ackSta,CmpType));
	}
	else
	{
		return(ReadMeterAFN13F1AndCmpMterAckClk(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,ackSta, CmpType));
	}
}

INT8U CSimJzq::Read3762Meter(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{


	if(vSrcType==0)
	{
		return(ReadMeterAFN02F1(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,1));
	}
	else
	{
		return(ReadMeterAFN13F1(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,1));
	}
}
INT8U CSimJzq::Read3762MeterAckClk(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame,TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,sAckTimeSta  &ackSta)
{


	if(vSrcType==0)
	{
		return(ReadMeterAFN02F1AckClk(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,ackSta,1));
	}
	else
	{
		return(ReadMeterAFN13F1AckClk(pSrcAddBuf,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,ackSta,1));
	}
}

INT8U CSimJzq::WaitReadMeterAckAndCmp(INT8U vSrcType,INT32U famedly,INT16U bytedly, INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U CmpType)
{
	if(vSrcType==0)
	{
		return(WaitReadMeterAFN02F1AckAndCmp(famedly , bytedly ,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame, CmpType));
	}
	else
	{
		return(WaitReadMeterAFN13F1AckAndCmp(famedly , bytedly ,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame, CmpType));
	}
}
INT8U CSimJzq:: QueMore645Fame(INT8U vSrcType,INT16U vSrcLen,INT8U *vSrcAmtBuf,INT8U cnt,INT8U *vDstBuf,INT16U &vDstLen,sBinFa376_2_HostMsg &ackHostMsg)
{
	INT8U ack;
	vDstLen=0;
	sDtl2007_Read    read645;
	ackHostMsg.di645cnt = 0;
	for(INT8U m =0 ;(m <cnt) && (m < DBinFangDiMaxCnt);m++)
	{
	   if(vSrcType==DPCT_97FG)
	   {
		    ack = CodeReadData97Cmd(gBinFang97Di[m],vSrcAmtBuf,1,read645);
	   }
	   else
		{ 
		  ack = CodeReadDataCmd(gBinFangDi[m],vSrcAmtBuf,1,read645);
	   }
		if(ack == DACK_SUCESS)
		{
			if(vDstLen+read645.s_vDstCmdLen <= vSrcLen)
			{
              if(vSrcType==DPCT_97FG)
				{
					ackHostMsg.di645Buf[ackHostMsg.di645cnt] = gBinFang97Di[m];
			  }
			  else
			  {
				  ackHostMsg.di645Buf[ackHostMsg.di645cnt] = gBinFangDi[m];
			  }
				ackHostMsg.ackFg[ackHostMsg.di645cnt]=0;
				ackHostMsg.di645cnt++;
				BufToBuf(&vDstBuf[vDstLen],read645.s_pDstCmdBuf,read645.s_vDstCmdLen);
				vDstLen+=read645.s_vDstCmdLen;
			}
		}
	}
	return  DACK_SUCESS;
}
INT8U   CSimJzq:: CmpDiIsOnDiBuf(INT32U Di,INT8U vSrcCnt,INT32U *DiBuf,INT8U &BpFg)
{
	for(INT8U m=0;m<vSrcCnt;m++)
	{
      if(DiBuf[m]==Di)
	  {
        BpFg=m;
		return DACK_SUCESS;
	  }
	}
  return DACK_FAILURE;
}
INT8U CSimJzq:: BinFenReadMeter(INT8U vSrcPctType,TH_IN  INT8U *amtbuf,INT8U vSrc645Cnt,INT32U vSrcAckFg,INT8U CmpDataFg,sBinFa376_2_HostMsg  &BinDownmsg,INT32U &vDstFg)
{
	 	            INT8U  resucnt=0;
	                INT8U  refailcnt=0;
					INT8U tmpbuf[1000];
					INT8U num645;
					INT16U len645buf[20];
					INT16U lendeallen=0;
					INT16U len16=0;
					INT8U sucnt = 0;
					INT8U ack;
				    INT8U dibp;
					INT8U reack=DACK_SUCESS;
				
					sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
					sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
			         Stu_Dtl2007 DstDecode2007DataFrame;
						tmpbuf[0] = vSrcPctType;//规约类型
						tmpbuf[1] = 0x00;//附属节点数量
						vDstFg=0;
						QueMore645Fame(vSrcPctType,1000,amtbuf,vSrc645Cnt,&tmpbuf[4],len16,BinDownmsg);//获取标识组645帧
						Hex16ToBuf2(len16,&tmpbuf[2]);//报文长度
						//模拟集中器发送与接收
						ack = HostSendRcv376_2BufNode(amtbuf,0xF1,F1,tmpbuf,len16+4,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
						if(ack == DACK_SUCESS)
						{

							ack = Check645Num(&DstDecodeDataFrame.s_RcvDataBuf[3],DstDecodeDataFrame.s_RcvDataLen-3,num645,len645buf);
							if((ack == DACK_SUCESS))
							{
								 for(INT8U n=0;n <= num645;n++)
							  	 {
									
										ack = Decode2007(&DstDecodeDataFrame.s_RcvDataBuf[3+lendeallen],len645buf[n],DstDecode2007DataFrame);
									    if(ack == DACK_SUCESS)
										{
											 ack = CmpDiIsOnDiBuf(DstDecode2007DataFrame.s_Di,BinDownmsg.di645cnt,BinDownmsg.di645Buf,dibp);
											  if(ack == DACK_SUCESS)
											  {
												  if(CmpDataFg==1)
												  {
													  ack =gSimMeter.CmpDeCode645DiData(DstDecode2007DataFrame);
												  }
												
											  }
											 
											 if(ack == DACK_SUCESS)
											{
													BinDownmsg.ackFg[dibp]=1;
													vDstFg |= Bit0<<dibp;
													resucnt++;
											}
											else
											{
												refailcnt++;
											}
									
										}
										lendeallen+=len645buf[n];
								   }
									
									
								
							}

						 }	
					if(CmpDataFg==1)
					{
						sNoAckDiMsg  noackMsg;
                        for(INT8U i=0; i<vSrc645Cnt; i++)//
						{
							if((vSrcAckFg&(Bit0<<i))==0)
							{
							 ack =gSimMeter.QueNoDiAckmsg(gBinFangDi[i],noackMsg);
								if(ack == DACK_SUCESS)
								{
									ack = gSimMeter.CheckNoDiAckmsg(noackMsg);
									if(ack != DACK_SUCESS)
							        {
										reack=DACK_FAILURE;
										 plog.saveLog_strAll(TIME,_T("重发次数或间隔时间错误"),0);
									}
								}
								plog.saveLog_NoAckMsg(PARS_FILE,TIME,_T("NODI返回信息"),noackMsg,1);
							}
						}
					}

		   if(reack==DACK_SUCESS)
			{
				if(vDstFg == vSrcAckFg)
				{
					
				    reack=DACK_SUCESS;
			    }
				else
				{
					reack = DACK_FAILURE;
				}
		   }
				  plog.saveLog_StaCnt(resucnt,refailcnt,PARS_FILE,TIME,_T(""),1);
				  plog.saveLog_BingF(PARS_FILE,TIME,_T("并发测试信息"),BinDownmsg,1);
			      plog.saveLog_testresult(PARS_FILE,TIME,_T("并发测试") ,reack,1);
		return 	   reack;
}

INT8U CSimJzq:: CmpBinFenRcvMeter(INT8U *amtbuf,INT8U vSrcPctType,INT8U vSrc645Cnt,INT8U CmpDataFg,INT32U FameDly,INT32U ByteDly,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	 	            INT8U  resucnt=0;
	                INT8U  refailcnt=0;
					INT8U tmpbuf[1000];
					INT8U num645;
					INT16U len645buf[20];
					INT16U lendeallen=0;
					INT16U len16=0;
					INT8U sucnt = 0;
					INT8U ack;
				    INT8U dibp;
					INT8U reack=DACK_SUCESS;
					sBinFa376_2_HostMsg  BinDownmsg;
//					sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;

			         Stu_Dtl2007 DstDecode2007DataFrame;
						tmpbuf[0] = vSrcPctType;//规约类型
						tmpbuf[1] = 0x00;//附属节点数量
						
						QueMore645Fame(vSrcPctType,1000,amtbuf,vSrc645Cnt,&tmpbuf[4],len16,BinDownmsg);//获取标识组645帧
						Hex16ToBuf2(len16,&tmpbuf[2]);//报文长度
						//模拟集中器发送与接收
						ack = Wait3762Ack(FameDly,ByteDly,DstDecodeDataFrame);
						if(ack == DACK_SUCESS)
						{
               
							ack = Check645Num(&DstDecodeDataFrame.s_RcvDataBuf[3],DstDecodeDataFrame.s_RcvDataLen-3,num645,len645buf);
							if((ack == DACK_SUCESS))
							{
								 for(INT8U n=0;n <= num645;n++)
							  	 {
									
										ack = Decode2007(&DstDecodeDataFrame.s_RcvDataBuf[3+lendeallen],len645buf[n],DstDecode2007DataFrame);
									    if(ack == DACK_SUCESS)
										{
											 ack = CmpDiIsOnDiBuf(DstDecode2007DataFrame.s_Di,BinDownmsg.di645cnt,BinDownmsg.di645Buf,dibp);
											  if(ack == DACK_SUCESS)
											  {
												  if(CmpDataFg==1)
												  {
													  ack  =gSimMeter.CmpDeCode645DiData(DstDecode2007DataFrame);
												  }
												
											  }
											 
											 if(ack == DACK_SUCESS)
											{
													BinDownmsg.ackFg[dibp]=1;
													
													resucnt++;
											}
											else
											{
												refailcnt++;
											}
									
										}
										lendeallen+=len645buf[n];
								   }
									
									
								
							}

						 }	
					if(CmpDataFg==1)
					{
						sNoAckDiMsg  noackMsg;
                        for(INT8U i=0; i<vSrc645Cnt; i++)//
						{
							
							 ack =gSimMeter.QueNoDiAckmsg(gBinFangDi[i],noackMsg);
								if(ack == DACK_SUCESS)
								{
									ack = gSimMeter.CheckNoDiAckmsg(noackMsg);
									if(ack != DACK_SUCESS)
							        {
										reack=DACK_FAILURE;
										 plog.saveLog_strAll(TIME,_T("重发次数或间隔时间错误"),0);
									}
								}
								plog.saveLog_NoAckMsg(PARS_FILE,TIME,_T("NODI返回信息"),noackMsg,1);
							}
					}

		   if(reack==DACK_SUCESS)
			{
				if(refailcnt>0)
				{
					
				    reack=DACK_SUCESS;
			    }
				else
				{
					reack = DACK_FAILURE;
				}
		   }
				  plog.saveLog_StaCnt(resucnt,refailcnt,PARS_FILE,TIME,_T(""),1);
				  plog.saveLog_BingF(PARS_FILE,TIME,_T("并发测试信息"),BinDownmsg,1);
			      plog.saveLog_testresult(PARS_FILE,TIME,_T("并发测试") ,reack,1);
		return reack;
			   
}
INT8U CSimJzq:: CmpAckTimeClk(INT8U vSrcTimeAllCnt,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,INT8U ack,sAckTimeSta *timeclk376)
{

	for(INT8U m=0;m<vSrcTimeAllCnt;m++)
	{
	  if(timeclk376[m].ackFg ==0)
	  {
       if(timeclk376[m].s_Seq == DstDecodeDataFrame.s_head.s_Msg_Seq)
	   {
		   timeclk376[m].timeclk=GetSysTimeInterval(timeclk376[m].timeclk);
		    timeclk376[m].ackFg =1;
			timeclk376[m].dataack = ack;
			return DACK_SUCESS;
	   }
	  }
	}
	return DACK_FAILURE;
}
 
	INT8U CSimJzq::SlaveSend376_2Buf(INT8U vSrcAFN,INT16U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame)
{
	INT8U ack;

	ack = Cgw13762.Code376_2_SlaveBufFrame(vSrcAFN,vSrcFn,vSrcBuf,vSrcLen,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
	if(ack == DACK_SUCESS)
	{
		SendHost3762ToCom(sQGDW376_2HostFrame);
	}
	return ack;
}

//376.2的通用函数
INT8U CSimJzq::SlaveSend376_2NoBuf(INT8U vSrcAFN,INT16U vSrcFn,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame)
{
	INT8U ack;

	ack = Cgw13762.Code376_2_SlaveFrame(vSrcAFN,vSrcFn,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
	if(ack == DACK_SUCESS)
	{	
		SendHost3762ToCom(sQGDW376_2HostFrame);	
	}
	return ack;
}


	INT8U CSimJzq::SlaveAckAFN14F1(INT8U AckType,INT8U *pSrcAddBuf,INT32U vSrcDi,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame)
{
	INT8U ack;
	INT8U tmpbuf[300];
	INT16U len16=0;
		tmpbuf[0]=AckType;
		tmpbuf[1]=0;
		tmpbuf[2]=0;
		tmpbuf[3]=0;
		len16=4;
	  if(AckType==2)
	{
		sDtl2007_Read CmdData645;
		CodeReadData9707Cmd(pSrcAddBuf[6],vSrcDi,pSrcAddBuf,1,CmdData645);
		tmpbuf[2]=CmdData645.s_vDstCmdLen;
		BufToBuf(&tmpbuf[3],CmdData645.s_pDstCmdBuf,CmdData645.s_vDstCmdLen);
		tmpbuf[3+CmdData645.s_vDstCmdLen]=0;
		len16 += CmdData645.s_vDstCmdLen;
	}
	ack = Cgw13762.Code376_2_SlaveBufFrame(0x14,F1,tmpbuf,len16,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
	if(ack == DACK_SUCESS)
	{
		SendHost3762ToCom(sQGDW376_2HostFrame);
	}
	return ack;
}

INT8U CSimJzq::CmpAFN14F1Data(INT8U *pSrcAddBuf,INT32U vSrcDi,sPartQGDW376_2CreatFrame sQGDW376_2HostFrame,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame,INT8U CmpType)
{
	INT8U ack = DACK_FAILURE;
	if(sQGDW376_2HostFrame.s_head.s_Msg_Seq == DstDecodeDataFrame.s_head.s_Msg_Seq)
	{
		if((DstDecodeDataFrame.s_head.s_AFN ==0x06)&&(DstDecodeDataFrame.s_head.s_FN ==F2))
		{
			if(DstDecodeDataFrame.s_RcvDataLen >= 5)
			{
			  if(DstDecodeDataFrame.s_RcvDataBuf[2]==pSrcAddBuf[6])
			   {   
				   ack = gSimMeter.Cmp645DiDataAmt(pSrcAddBuf,pSrcAddBuf[6],vSrcDi,&DstDecodeDataFrame.s_RcvDataBuf[6],DstDecodeDataFrame.s_RcvDataBuf[5],CmpType);
			   }
			}
		}
	}
	return ack;
}

	INT8U CSimJzq::AFN14F1AllOPCon06F2(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U Afn06F2AckFg,INT8U CmpType)
{
	INT8U amtbuf[7+1];
	return (AFN14F1AllOPAckAmtCon06F2(famedly,bytedly,AckType,vSrcPct,vSrcDi,Afn06F2AckFg,amtbuf,CmpType));
}
INT8U CSimJzq::AFN14F1AllOP(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U CmpType)
{
	INT8U amtbuf[7+1];
	return (AFN14F1AllOPAckAmt(famedly,bytedly,AckType,vSrcPct,vSrcDi,amtbuf,CmpType));
}
INT8U CSimJzq::AFN14F1AllOPAckAmtCon06F2(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U Afn06F2AckFg,INT8U *vDstAmtBuf,INT8U CmpType)
{
	INT8U ack;
	INT8U tmpacktype=AckType;
//	INT16U tmp16;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	ack = Wait3762Ack(famedly , bytedly ,DstDecodeDataFrame);
	if(ack==DACK_SUCESS)
	{
		if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1)&&(DstDecodeDataFrame.s_RcvDataLen == 9))
		{
			 BufToBuf(vDstAmtBuf,&DstDecodeDataFrame.s_RcvDataBuf[1],6);
			  ack = SlaveAckAFN14F1(AckType,&DstDecodeDataFrame.s_RcvDataBuf[1],vSrcDi,DstDecodeDataFrame,sQGDW376_2HostFrame);
			  if(ack==DACK_SUCESS)
			  {
				if(AckType==2)
				{
					ack = Wait3762Ack(famedly , bytedly ,DstDecodeDataFrame);
				   if(ack==DACK_SUCESS)
				   {
					   ack = CmpAFN14F1Data(vDstAmtBuf,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,CmpType);

					   if(Afn06F2AckFg==1)
					   {
						    
						   Cgw13762.Code376_2_SlaveFrame(0x00,F1,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						  SendHost3762ToCom(sQGDW376_2HostFrame);
					   }
					   else if(Afn06F2AckFg==2)
					   {
                             Cgw13762.Code376_2_SlaveFrame(0x00,F2,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						     SendHost3762ToCom(sQGDW376_2HostFrame);

					   }
					    else if(Afn06F2AckFg==3)
					   {
						   DstDecodeDataFrame.s_head.s_Msg_Seq+=3;
                          Cgw13762.Code376_2_SlaveFrame(0x00,F1,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						  SendHost3762ToCom(sQGDW376_2HostFrame);

					   }
				   }
				}
			  }
	
		}
	}
	return ack;
}
INT8U CSimJzq::AFN14F1AllOPAckAmt(INT32U famedly,INT16U bytedly,INT8U AckType,INT8U vSrcPct,INT32U vSrcDi,INT8U *vDstAmtBuf,INT8U CmpType)
{
INT8U ack;
	INT8U tmpacktype=AckType;
//	INT16U tmp16;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	ack = Wait3762Ack(famedly , bytedly ,DstDecodeDataFrame);
	if(ack==DACK_SUCESS)
	{
		if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1)&&(DstDecodeDataFrame.s_RcvDataLen == 9))
		{
			 BufToBuf(vDstAmtBuf,&DstDecodeDataFrame.s_RcvDataBuf[1],6);
			 if(AckType==4)
			 {
				  AckType=0x02;
				  DstDecodeDataFrame.s_head.s_Msg_Seq+=2;
				 
			 }
			
			  ack = SlaveAckAFN14F1(AckType,&DstDecodeDataFrame.s_RcvDataBuf[1],vSrcDi,DstDecodeDataFrame,sQGDW376_2HostFrame);
			   AckType=tmpacktype;
			  if(ack==DACK_SUCESS)
			  {
				if(AckType==2)
				{
					ack = Wait3762Ack(famedly , bytedly ,DstDecodeDataFrame);
				   if(ack==DACK_SUCESS)
				   {
					   ack = CmpAFN14F1Data(vDstAmtBuf,vSrcDi,sQGDW376_2HostFrame,DstDecodeDataFrame,CmpType);

						 Cgw13762.Code376_2_SlaveFrame(0x00,F1,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						 SendHost3762ToCom(sQGDW376_2HostFrame);
					  

				   }
				}
			  }
	
		}
	}
	return ack;
}

//单地址，单DI测试,多次
INT8U CSimJzq::AFN14F1ACK0001(INT8U AckType)
{
	INT8U ack;
//	INT16U tmp16;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	ack = Wait3762Ack(100*1000 , 50 ,DstDecodeDataFrame);
	if(ack==DACK_SUCESS)
	{
		if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1)&&(DstDecodeDataFrame.s_RcvDataLen == 9))
		{
			  ack = SlaveAckAFN14F1(AckType,&DstDecodeDataFrame.s_RcvDataBuf[1],gReMeterDi[0],DstDecodeDataFrame,sQGDW376_2HostFrame);
	
		}
	}
	return ack;
}

INT8U CSimJzq::AFN14F1ACK0001CmpAmt(INT32U AmtSeq,INT8U DiBp,INT8U AckType)
{
	INT8U ack;
//	INT16U tmp16;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	ack = Wait3762Ack(100*1000 , 50 ,DstDecodeDataFrame);
	if(ack==DACK_SUCESS)
	{
		if((DstDecodeDataFrame.s_head.s_AFN==0x14)&&(DstDecodeDataFrame.s_head.s_FN==F1)&&(DstDecodeDataFrame.s_RcvDataLen == 9))
		{
			  ack = SlaveAckAFN14F1(AckType,&DstDecodeDataFrame.s_RcvDataBuf[1],gReMeterDi[DiBp],DstDecodeDataFrame,sQGDW376_2HostFrame);
			 if(ack==DACK_SUCESS)
			 {
				 if(CompareNBuf(DstDecodeDataFrame.s_head.s_DestAddBuf,&gNodeAddBuf[AmtSeq][0],6)!=EQU)
			  {
						  ack = DACK_EER_AMTADD;
			  }
			 }
		}
	}
	return ack;
}

INT8U CSimJzq::AFN14F1AllOPCmpAmt(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U AckType,INT8U CmpType)
{
	
INT8U ack;
	INT8U AmtBuf[7+1];
	INT32U errcnt=0;
	 for(INT32U m=0; m<TestCnt; m++)
    {
	ack = AFN14F1AllOPAckAmt(10000 , 50 ,AckType,DPCT_2007FG,Di,AmtBuf,CmpType);
	if(ack==DACK_SUCESS)
	{
	  if(CompareNBuf(AmtBuf,&gNodeAddBuf[AmtSeq][0],6)!=EQU)
	  {
		  ack = DACK_EER_AMTADD;
	  }

	  }
	 }
 if(errcnt==0)
 {
		ack = DACK_SUCESS;
   }
   else
   {
      ack = DACK_FAILURE;
   }
	return ack;
}

INT8U CSimJzq::AFN14F1AllOPCmpAmtCon06F2(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U AckType,INT8U Afn06F2AckFg,INT8U CmpType)
{
	
INT8U ack;
	INT8U AmtBuf[7+1];
	INT32U errcnt=0;
	 for(INT32U m=0; m<TestCnt; m++)
    {
	ack = AFN14F1AllOPAckAmtCon06F2(10000 , 50 ,AckType,DPCT_2007FG,Di,Afn06F2AckFg,AmtBuf,CmpType);
	if(ack==DACK_SUCESS)
	{
	  if(CompareNBuf(AmtBuf,&gNodeAddBuf[AmtSeq][0],6)!=EQU)
	  {
		  ack = DACK_EER_AMTADD;
	  }

	  }
	 }
 if(errcnt==0)
 {
		ack = DACK_SUCESS;
   }
   else
   {
      ack = DACK_FAILURE;
   }
	return ack;
}
INT8U CSimJzq::Test14ReadMeterOneAdd07(INT8U AmtSeq,INT32U Di,INT32U TestCnt,INT8U CmpType)
{
	
	INT8U ack;
	INT8U AmtBuf[7+1];
	INT32U errcnt=0;
	 for(INT32U m=0; m<TestCnt; m++)
    {
	ack = AFN14F1AllOPAckAmt(10000 , 50 ,0x02,DPCT_2007FG,Di,AmtBuf,CmpType);
	if(ack==DACK_SUCESS)
	{
	  if(CompareNBuf(AmtBuf,&gNodeAddBuf[AmtSeq][0],6)!=EQU)
	  {
		  ack = DACK_EER_AMTADD;
	  }

	  }
	 }
 if(errcnt==0)
 {
		ack = DACK_SUCESS;
   }
   else
   {
      ack = DACK_FAILURE;
   }
	return ack;
}
//单地址，多DI测试
INT8U  CSimJzq:: Test14ReadMeterOneAdd07MoreDi(INT8U vSrcDiBp,INT8U DiCnt,INT8U AmtSeq,INT32U TestCnt,INT8U CmpType)
{
	
	INT8U ack;
	INT32U errcnt=0;
   for(INT32U m=0; (m<DiCnt)&&(m+DiCnt<DReadMeterMaxCnt); m++)
   {
      ack = Test14ReadMeterOneAdd07(AmtSeq,gReMeterDi[vSrcDiBp+m],TestCnt,CmpType);
		if(ack!=DACK_SUCESS)
		{
			errcnt++;
		}
		
   }
   if(errcnt==0)
	{
		ack = DACK_SUCESS;
   }
   else
   {
      ack = DACK_FAILURE;
   }

   plog.saveLog_testresultAll(TIME,_T("单地址，多DI测试") ,ack,1);
	return ack;
}
//多地址，多DI测试
    INT8U  CSimJzq::TestReadMeterMoreAdd07(INT8U vSrcDiBp,INT8U DiCnt,INT8U AmtSeq,INT32U AmtCnt,INT32U TestCnt,INT8U CmpType)
	{
		   INT8U ack;
			INT8U errcnt=0;
		   for(INT32U m=0; m<AmtCnt; m++)
		   {
			  ack = Test14ReadMeterOneAdd07MoreDi(vSrcDiBp,DiCnt,AmtSeq+m,TestCnt,CmpType);
				if(ack!=DACK_SUCESS)
				{
					errcnt++;
				}
				AFN14F1ACK0001(0x01);
		   }
		   if(errcnt==0)
			{
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }

		   plog.saveLog_testresultAll(TIME,_T("单地址，多DI测试") ,ack,1);
			return ack;

	}

INT8U  CSimJzq::QueNetSta(INT8U *vSrcAmtBuf,INT32U WaitTimeS)
{
	   INT8U ack;
	   sPartQGDW376_2CreatFrame  sQGDW376_2HostFrame;
		sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
		for(INT32U m = 0; m<WaitTimeS; m++)
		{
        ack = HostSendRcv376_2Buf(0x10,F201,vSrcAmtBuf,6,sQGDW376_2HostFrame,DstDecodeDataFrame);
		if((ack == DACK_SUCESS)&&(DstDecodeDataFrame.s_head.s_AFN ==0x01)&&(DstDecodeDataFrame.s_head.s_FN ==F201))
		{
            if(DstDecodeDataFrame.s_RcvDataBuf[12]==0x01)
			{
				ack = DACK_SUCESS;
				plog.saveLog_strAll(TIME,_T("  在线"),1);
				break;
			}
			Sleep(1000);
		}
	}
		plog.saveLog_strAll(TIME,_T("  不在线"),1);
		return DACK_FAILURE;
}

INT8U  CSimJzq::QueAllNetSta(INT8U amtSeq,INT8U vSrcCnt,INT32U WaitTimeS)
{
	INT8U ack;
	INT8U errcnt=0;
		for(INT32U m = 0; m<vSrcCnt; m++)
		{
           ack = QueNetSta(&gNodeAddBuf[amtSeq+m][0],WaitTimeS);
			if(ack != DACK_SUCESS)
			{
			   errcnt++;
			}
		}

		if(errcnt==0)
			{
				ack = DACK_SUCESS;
		   }
		   else
		   {
			  ack = DACK_FAILURE;
		   }
		plog.saveLog_testresult(PARS_FILE,TIME,_T("所有从节点组网状态 "),ack,0);
		return ack;
}

INT8U CSimJzq::ZjqNoRcvData( INT32U nWaitFramTime , INT16U nWaiteByteTime)
{
	
	INT8U ack = DACK_FAILURE;
	INT8U recvbuf[10];
	INT16U recvbuflen=0;
	ClrZjqComData();
	GetCOMM376_2ToBuf(10 , nWaitFramTime , nWaiteByteTime , recvbuf , recvbuflen);
	if(recvbuflen==0)
	{
      ack = DACK_SUCESS;
	}
	return ack;
	/*sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	ack = Wait3762Ack(nWaitFramTime , nWaiteByteTime ,DstDecodeDataFrame);
	if(ack==DACK_SUCESS)
	{
		return DACK_FAILURE;
	}
	else
	{
     return DACK_SUCESS;
	}
	*/
}

INT8U CSimJzq::CmpDecode3762( sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_1,sPartQGDW376_2DeCodeFrame DstDecodeDataFrame_2)
{
	INT16U len16=sizeof(sPartQGDW376_2DeCodeFrame);
	if(CompareNBuf((INT8U*)(&DstDecodeDataFrame_1),(INT8U*)(&DstDecodeDataFrame_2),len16)==EQU)
	{
		if(CompareNBuf(DstDecodeDataFrame_1.s_RcvDataBuf,DstDecodeDataFrame_2.s_RcvDataBuf,DstDecodeDataFrame_1.s_RcvDataLen)==EQU)
		{
			return DACK_SUCESS;
		}
	}
	return DACK_FAILURE;
}

INT8U CSimJzq::CmpReSendCntTime(sNoAckDiMsg   AFNnoack,INT8U Cnt,INT32U MinTime,INT32U MaxTime)
{
  INT32U tmpbuf[3];
             if(AFNnoack.s_RcvCnt==Cnt)
		   {
			   tmpbuf[0]=QueSysTimeVal(AFNnoack.s_Time[0],AFNnoack.s_Time[1]);
			   tmpbuf[1]=QueSysTimeVal(AFNnoack.s_Time[1],AFNnoack.s_Time[2]);
			   if((tmpbuf[0]>=MinTime)&&(tmpbuf[0]<=MaxTime))
			   {
				    if((tmpbuf[1]>=MinTime)&&(tmpbuf[1]<=MaxTime))
					{
                       return DACK_SUCESS;
					}
			   }
		   }
 return DACK_FAILURE;
}

INT8U CSimJzq::SetHostAdd(void)
{
	INT8U ack;
	 ack= HostSendRcv376_2Buf_NoAck(0x05,(INT16U)F1,m_HostNodeAddress,6);
      plog.saveLog_testresult(PARS_FILE,TIME,_T("设置CCO的主节点地址 "),ack,0);
    return ack;
}

INT8U CSimJzq::EventOp(INT32U famedly,INT16U bytedly,INT8U AckType,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame,INT8U *vDstAmtBuf,INT8U CmpType)
{
	INT8U ack;
	INT8U tmpacktype=AckType;
   INT8U tmpseq;
    Stu_Dtl2007 DstDecode2007DataFrame;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	ack = Wait3762Ack(famedly , bytedly ,DstDecodeDataFrame);
	if(ack==DACK_SUCESS)
	{
		if((DstDecodeDataFrame.s_head.s_AFN==0x06)&&(DstDecodeDataFrame.s_head.s_FN==F5))
		{
			
			ack =gSimMeter. Cmp645DiDataAndAck(DPCT_2007FG,0x04001501,&DstDecodeDataFrame.s_RcvDataBuf[3],DstDecodeDataFrame.s_RcvDataLen-3,DstDecode2007DataFrame,CmpType);
			 BufToBuf(vDstAmtBuf,DstDecode2007DataFrame.s_AmtBuf,6);
			  
					   if(AckType==1)//回复确认
					   {
						    
						   Cgw13762.Code376_2_SlaveFrame(0x00,F1,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						  SendHost3762ToCom(sQGDW376_2HostFrame);
					   }
					   else if(AckType==2)//回复否认
					   {
                             Cgw13762.Code376_2_SlaveFrame(0x00,F2,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						     SendHost3762ToCom(sQGDW376_2HostFrame);

					   }
					    else if(AckType==3)//回复SEQ不一致
					   {
						   tmpseq=DstDecodeDataFrame.s_head.s_Msg_Seq;
						   DstDecodeDataFrame.s_head.s_Msg_Seq+=3;
                          Cgw13762.Code376_2_SlaveFrame(0x00,F1,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						  SendHost3762ToCom(sQGDW376_2HostFrame);
						  DstDecodeDataFrame.s_head.s_Msg_Seq=tmpseq;
					   }
						else//不回复
						{

						}
				   }
				}
			 
	return ack;
}

INT8U CSimJzq::SearthMeterOpAFN06F4(INT32U famedly,INT16U bytedly,INT8U AckType,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U ack;
	INT8U tmpacktype=AckType;
   INT8U tmpseq;
    Stu_Dtl2007 DstDecode2007DataFrame;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	ack = Wait3762Ack(famedly , bytedly ,DstDecodeDataFrame);
	if(ack==DACK_SUCESS)
	{
		if((DstDecodeDataFrame.s_head.s_AFN==0x06)&&(DstDecodeDataFrame.s_head.s_FN==F4))
		{
			
			  
					   if(AckType==1)//回复确认
					   {
						    
						   Cgw13762.Code376_2_SlaveFrame(0x00,F1,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						  SendHost3762ToCom(sQGDW376_2HostFrame);
					   }
					   else if(AckType==2)//回复否认
					   {
                             Cgw13762.Code376_2_SlaveFrame(0x00,F2,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						     SendHost3762ToCom(sQGDW376_2HostFrame);

					   }
					    else if(AckType==3)//回复SEQ不一致
					   {
						   tmpseq=DstDecodeDataFrame.s_head.s_Msg_Seq;
						   DstDecodeDataFrame.s_head.s_Msg_Seq+=3;
                          Cgw13762.Code376_2_SlaveFrame(0x00,F1,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						  SendHost3762ToCom(sQGDW376_2HostFrame);
						  DstDecodeDataFrame.s_head.s_Msg_Seq=tmpseq;
					   }
						else//不回复
						{

						}
				   }
				}
			 
	return ack;
}


INT8U CSimJzq::SearthMeterOpAFN06F2(INT32U famedly,INT16U bytedly,INT8U AckType,sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U ack;
	INT8U tmpacktype=AckType;
   INT8U tmpseq;
    Stu_Dtl2007 DstDecode2007DataFrame;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	ack = Wait3762Ack(famedly , bytedly ,DstDecodeDataFrame);
	if(ack==DACK_SUCESS)
	{
		if((DstDecodeDataFrame.s_head.s_AFN==0x06)&&(DstDecodeDataFrame.s_head.s_FN==F4))
		{
			
			  
					   if(AckType==1)//回复确认
					   {
						    
						   Cgw13762.Code376_2_SlaveFrame(0x00,F1,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						  SendHost3762ToCom(sQGDW376_2HostFrame);
					   }
					   else if(AckType==2)//回复否认
					   {
                             Cgw13762.Code376_2_SlaveFrame(0x00,F2,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						     SendHost3762ToCom(sQGDW376_2HostFrame);

					   }
					    else if(AckType==3)//回复SEQ不一致
					   {
						   tmpseq=DstDecodeDataFrame.s_head.s_Msg_Seq;
						   DstDecodeDataFrame.s_head.s_Msg_Seq+=3;
                          Cgw13762.Code376_2_SlaveFrame(0x00,F1,DstDecodeDataFrame.s_head,sQGDW376_2HostFrame);
						  SendHost3762ToCom(sQGDW376_2HostFrame);
						  DstDecodeDataFrame.s_head.s_Msg_Seq=tmpseq;
					   }
						else//不回复
						{

						}
				   }
				}
			 
	return ack;
}



//--------------------------------------------------------------------------
#ifdef _STD_CSG  //南网标准
INT8U CSimJzq::HostSendRcv376_2NoBuf_NoAck(INT8U vSrcAFN,INT32U vSrcFn)//针对无数据单元只回确认否认帧类型的判断
{
	INT8U ack;
	sPartQCSG376_2CreatFrame sQCSG376_2HostFrame;
	sPartQCSG376_2DeCodeFrame DstDecodeDataFrame;
	ack = HostSendRcv376_2NoBuf(vSrcAFN,vSrcFn,sQCSG376_2HostFrame,DstDecodeDataFrame);
	sAckTimeSta  ackSta;
	ackSta.timeclk = GetSysTimeClk();
	ackSta.s_Seq = sQCSG376_2HostFrame.s_head.s_Msg_Seq;
	ackSta.ackFg=0;
	if(sQCSG376_2HostFrame.s_head.s_Msg_Seq == DstDecodeDataFrame.s_head.s_Msg_Seq)
	{
		if((DstDecodeDataFrame.s_head.s_AFN == 0x00) &&(DstDecodeDataFrame.s_head.s_FN == FN_00_F1))
		{
			ack = DACK_SUCESS;
		}
		else if((DstDecodeDataFrame.s_head.s_AFN == 0x00) &&(DstDecodeDataFrame.s_head.s_FN == FN_00_F2))
		{
			ack =DstDecodeDataFrame.s_RcvDataBuf[0];
		}

		else
		{
			ack = DACK_FAILURE;
		}
	}
	else
	{
		ack = DACK_EER_SEQERR;
	}
	CmpAckTimeClk(1,DstDecodeDataFrame,ack,&ackSta);
	plog.saveLog_ClkSta(&ackSta,1,DATA_FILE,NOTIME,_T("单帧结果"),1);      
	return ack;
}
INT8U CSimJzq::HostSendRcv376_2Buf_NoAck(INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen)//设置专用
{
	INT8U ack;
	sPartQCSG376_2CreatFrame sQCSG376_2HostFrame;
	sPartQCSG376_2DeCodeFrame DstDecodeDataFrame;
	ack =HostSendRcv376_2Buf(vSrcAFN,vSrcFn,vSrcBuf,vSrcLen,sQCSG376_2HostFrame,DstDecodeDataFrame);
	if(sQCSG376_2HostFrame.s_head.s_Msg_Seq == DstDecodeDataFrame.s_head.s_Msg_Seq)
	{
		if((DstDecodeDataFrame.s_head.s_AFN == 0x00) &&(DstDecodeDataFrame.s_head.s_FN == FN_00_F1))
		{
			ack = DACK_SUCESS;
		}
		else if((DstDecodeDataFrame.s_head.s_AFN == 0x00) &&(DstDecodeDataFrame.s_head.s_FN == FN_00_F2))
		{
			ack =DstDecodeDataFrame.s_RcvDataBuf[0];
		}

		else
		{
			ack = DACK_FAILURE;
		}
	}
	else
	{
		ack = DACK_EER_SEQERR;
	}     
	return ack;
}
INT8U CSimJzq::HostSendRcv376_2MsgAddrBuf(INT8U vSrcCn,INT8U * vSrcMsgAddr,INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp)
{
	INT8U ack;

	ack = Ccsg13762.Code376_2_F0F008Data(vSrcCn ,vSrcMsgAddr ,vSrcAFN,vSrcFn,vSrcBuf,vSrcLen,sQCSG376_2HostFrame);//无节点
	sAckTimeSta  ackSta;
	ackSta.timeclk = GetSysTimeClk();
	ackSta.s_Seq = sQCSG376_2HostFrame.s_head.s_Msg_Seq;
	ackSta.ackFg=0;
	if(ack == DACK_SUCESS)
	{
		for(INT8U mm = 0; mm < 1; mm ++)
		{
			SendHost3762ToCom(sQCSG376_2HostFrame);
			if(vSrcAckCmp == 0)
			{
				ack = Wait3762AckCmpSeq(10000 , 20 ,sQCSG376_2HostFrame,DstDecodeDataFrame);
			}
			else
			{
				ack = Wait3762AckCmpAFNFN(10000 , 20 ,sQCSG376_2HostFrame,DstDecodeDataFrame);
			}
			if(ack == DACK_SUCESS)
			{
				break;
			}
		}
	}
	CmpAckTimeClk(1,DstDecodeDataFrame,ack,&ackSta);
	plog.saveLog_ClkSta(&ackSta,1,DATA_FILE,NOTIME,_T("单帧结果"),1);
	return ack;
}
//有数据单元的组帧
//有数据单元的组帧
INT8U CSimJzq::HostSendRcv376_2Buf(INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp)
{
	INT8U ack;
	
	ack = Ccsg13762.Code376_2_HostBufFrame(vSrcAFN,vSrcFn,vSrcBuf,vSrcLen,sQCSG376_2HostFrame);//无节点
	sAckTimeSta  ackSta;
	ackSta.timeclk = GetSysTimeClk();
    ackSta.s_Seq = sQCSG376_2HostFrame.s_head.s_Msg_Seq;
	ackSta.ackFg=0;

	if(ack == DACK_SUCESS)
	{
	  for(INT8U mm = 0; mm < 1; mm ++)
	  {
		SendHost3762ToCom(sQCSG376_2HostFrame);
		if(vSrcAckCmp == 0)
		{
			ack = Wait3762AckCmpSeq(10000 , 20 ,sQCSG376_2HostFrame,DstDecodeDataFrame);
		}
		else
		{
			ack = Wait3762AckCmpAFNFN(10000 , 20 ,sQCSG376_2HostFrame,DstDecodeDataFrame);
		}
		if(ack == DACK_SUCESS)
		{
			break;
		}
	  }
	}
	CmpAckTimeClk(1,DstDecodeDataFrame,ack,&ackSta);
	plog.saveLog_ClkSta(&ackSta,1,DATA_FILE,NOTIME,_T("单帧结果"),1);
     return ack;
 }

//376.2的通用函数 无数据单元的
 INT8U CSimJzq::HostSendRcv376_2NoBuf(INT8U vSrcAFN,INT32U vSrcFn,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp)
 {
    INT8U ack;

	ack = Ccsg13762.Code376_2_HostFrame(vSrcAFN,vSrcFn,sQCSG376_2HostFrame);
	sAckTimeSta  ackSta;
	ackSta.timeclk = GetSysTimeClk();
	ackSta.s_Seq = sQCSG376_2HostFrame.s_head.s_Msg_Seq;
	ackSta.ackFg=0;
	if(ack == DACK_SUCESS)
	{
		for(INT8U mm = 0; mm < 1; mm ++)
		{
			SendHost3762ToCom(sQCSG376_2HostFrame);
			if(vSrcAckCmp == 0)
			{
				ack = Wait3762AckCmpSeq(10000 , 20 ,sQCSG376_2HostFrame,DstDecodeDataFrame);
			}
			else
			{
				ack = Wait3762AckCmpAFNFN(10000 , 20 ,sQCSG376_2HostFrame,DstDecodeDataFrame);
			}
			if(ack == DACK_SUCESS)
			{
				break;
			}
		}
	}

	CmpAckTimeClk(1,DstDecodeDataFrame,ack,&ackSta);
	plog.saveLog_ClkSta(&ackSta,1,DATA_FILE,NOTIME,_T("单帧结果"),1);
     return ack;
 }
 
 //有目的地址和buf的
INT8U CSimJzq::HostSendRcv376_2BufNode(TH_IN const INT8U *pSrcAddBuf, INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame,INT8U vSrcAckCmp)
{
	INT8U ack;

	ack = Ccsg13762.Code376_2_HostBufNodeFrame(pSrcAddBuf,vSrcAFN,vSrcFn,vSrcBuf,vSrcLen,sQCSG376_2HostFrame);//有目的地址的
	sAckTimeSta  ackSta;
	ackSta.timeclk = GetSysTimeClk();
	ackSta.s_Seq = sQCSG376_2HostFrame.s_head.s_Msg_Seq;
	ackSta.ackFg=0;
	if(ack == DACK_SUCESS)
	{
		for(INT8U mm = 0; mm < 1; mm ++)
		{
			SendHost3762ToCom(sQCSG376_2HostFrame);
			if(vSrcAckCmp == 0)
			{
				ack = Wait3762AckCmpSeq(10000 , 20 ,sQCSG376_2HostFrame,DstDecodeDataFrame);
			}
			else
			{
				ack = Wait3762AckCmpAFNFN(10000 , 20 ,sQCSG376_2HostFrame,DstDecodeDataFrame);
			}
			if(ack == DACK_SUCESS)
			{
				break;
			}

		}
	}
	CmpAckTimeClk(1,DstDecodeDataFrame,ack,&ackSta);
	plog.saveLog_ClkSta(&ackSta,1,DATA_FILE,NOTIME,_T("单帧结果"),1);
	return ack;
}

INT8U CSimJzq::HostSendRcv376_2F0F8(TH_IN const INT8U *pSrcAddBuf,TH_IN INT8U vSrcAfn,TH_IN INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U SendDatabuf[JZQ_MAX_BUFF_LEN];
	INT16U SendDatalen = 0 ;
	INT16U temp16 = 0;
	INT16U n = 0;
	sPartQCSG376_2CreatFrame ptSendQCSG376_2;
	for(n = 0 ; n < vSrcLen ; n++)
	{
		ptSendQCSG376_2.s_SendDataBuf[n] = vSrcBuf[n];
	}
	ptSendQCSG376_2.s_SendDataLen = vSrcLen;

	if (vSrcLen != 0)
	{
		Ccsg13762.Code376_2_HostBufFrame(vSrcAfn,vSrcFn,vSrcBuf,vSrcLen ,ptSendQCSG376_2);
	}
	else
	{
		Ccsg13762.Code376_2_HostFrame(vSrcAfn,vSrcFn,ptSendQCSG376_2);
	}
	
	m_tools.Buf_To_LenBuf(ptSendQCSG376_2.s_SendDataBuf , ptSendQCSG376_2.s_SendDataLen , SendDatabuf , SendDatalen );
	//南网扩展标记
	INT8U ack = HostSendRcv376_2BufNode(pSrcAddBuf , 0xF0 , FN_F0_F8 , SendDatabuf , SendDatalen , sQCSG376_2HostFrame , DstDecodeFrame);

	switch(ack)
	{
	case 0:
		temp16 = DstDecodeFrame.s_RcvDataBuf[1]<<8 | DstDecodeFrame.s_RcvDataBuf[0];
		if ((temp16 + 2) == DstDecodeFrame.s_RcvDataLen)
		{
			ack = Ccsg13762.Decode376_2Frame(&DstDecodeFrame.s_RcvDataBuf[2] , temp16 , DstDecodeDataFrame);
		}
		break;
	}
	return ack;
}
//以下收发分开-有vSrcBuf-无vSrcBuf-收
INT8U CSimJzq::HostSend376_2Buf(INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame)
{
	INT8U ack;

	ack = Ccsg13762.Code376_2_HostBufFrame(vSrcAFN,vSrcFn,vSrcBuf,vSrcLen,sQCSG376_2HostFrame);
	if(ack == DACK_SUCESS)
	{
		SendHost3762ToCom(sQCSG376_2HostFrame);
	}
	return ack;
}

//376.2的通用函数
INT8U CSimJzq::HostSend376_2NoBuf(INT8U vSrcAFN,INT32U vSrcFn,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame)
{
	INT8U ack;

	ack = Ccsg13762.Code376_2_HostFrame(vSrcAFN,vSrcFn,sQCSG376_2HostFrame);
	if(ack == DACK_SUCESS)
	{	
		SendHost3762ToCom(sQCSG376_2HostFrame);	
	}
	return ack;
}

INT8U CSimJzq::HostRcv376_2( INT32U nWaitFramTime , INT16U nWaiteByteTime ,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U ack = DACK_FAILURE;

	ack = Wait3762Ack(nWaitFramTime,nWaiteByteTime,DstDecodeDataFrame);

	return ack;
}

void CSimJzq::SendHost3762ToCom(sPartQCSG376_2CreatFrame sQCSG376_2HostFrame)
{
	SendBufToCom(sQCSG376_2HostFrame.s_SendDataBuf ,sQCSG376_2HostFrame.s_SendDataLen );
//???	plog.saveInformation_send(sQCSG376_2HostFrame);

}
INT8U   CSimJzq::Wait3762Ack(INT32U nWaitFramTime , INT16U nWaiteByteTime,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	INT8U ack = DACK_FAILURE;
	INT8U recvbuf[D376_MAXRCVBUFLEN];
	INT16U recvbuflen=0;
	int nItem = 0;
	GetCOMM376_2ToBuf(D376_MAXRCVBUFLEN , nWaitFramTime , nWaiteByteTime , recvbuf , recvbuflen);
	if(recvbuflen>0)
	{
		ack = Ccsg13762.Decode376_2Frame(recvbuf,recvbuflen,DstDecodeDataFrame);
		plog.saveLog_HexBuf(DATA_FILE,INPUT_DATA,recvbuf,recvbuflen);//打印接收帧数据
		nItem = pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemCount();
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.InsertItem( nItem,pMainDlg-> m_strSysDateTime);
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 1, _T("接收<<"));
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 2 , pMainDlg->m_tools._buf16tostr16(recvbuf , recvbuflen , true));
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.EnsureVisible(nItem,FALSE);
		pMainDlg->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.RedrawItems(nItem,nItem);
		if(ack == DACK_SUCESS)
		{
//???			plog.saveInformation_rev(DstDecodeDataFrame);
		}
		else
		{
//???		    plog.saveLog_err(DATA_FILE,NOTIME,_T(""),DACK_ERR_FORMAT);
		}

	}
	return ack;
}
INT8U   CSimJzq::Wait3762AckCmpSeq(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartQCSG376_2CreatFrame sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U reack = DACK_FAILURE;
	INT8U ack = Wait3762Ack(nWaitFramTime,nWaiteByteTime,DstDecodeDataFrame);
	if(ack == DACK_SUCESS)
	{
		reack = ack;
		/*if(sQGDW376_2HostFrame.s_head.s_Msg_Seq == DstDecodeDataFrame.s_head.s_Msg_Seq)
		{
			reack = DACK_SUCESS;
		}
		else
		{
			reack = DACK_EER_SEQERR;
		}*/
	}
	else
	{
		reack = ack;
	}
	return reack;
}
INT8U   CSimJzq::Wait3762AckCmpAFNFN(INT32U nWaitFramTime , INT16U nWaiteByteTime,sPartQCSG376_2CreatFrame sQCSG376_2HostFrame,TH_OUT sPartQCSG376_2DeCodeFrame &DstDecodeDataFrame)
{
	INT8U reack = DACK_FAILURE;
	INT8U ack = Wait3762AckCmpSeq(nWaitFramTime,nWaiteByteTime,sQCSG376_2HostFrame,DstDecodeDataFrame);
	if(ack == DACK_SUCESS) 
	{
		if ((sQCSG376_2HostFrame.s_head.s_AFN == DstDecodeDataFrame.s_head.s_AFN)&& (sQCSG376_2HostFrame.s_head.s_FN == DstDecodeDataFrame.s_head.s_FN))
		{
			reack = DACK_SUCESS;
		}
		else
		{
			reack = DACK_EER_CCOCANNOTDO;
		}
	}
	else
	{
		reack = ack;
	}
	return reack;
}


//vSrcType 0: AFN=0x02,F1,1:AFN =13F1,
INT8U CSimJzq::CodeReadMeter3762Cmd(INT8U vSrcType,TH_IN const INT8U *pSrcAddBuf, INT32U vSrcDi,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame)
{
	//???????????????????
	return DACK_FAILURE;
}
INT8U CSimJzq:: CmpAckTimeClk(INT8U vSrcTimeAllCnt,sPartQCSG376_2DeCodeFrame DstDecodeDataFrame,INT8U ack,sAckTimeSta *timeclk376)
{

	for(INT8U m=0;m<vSrcTimeAllCnt;m++)
	{
	  if(timeclk376[m].ackFg ==0)
	  {
       if(timeclk376[m].s_Seq == DstDecodeDataFrame.s_head.s_Msg_Seq)
	   {
		   timeclk376[m].timeclk=GetSysTimeInterval(timeclk376[m].timeclk);
		    timeclk376[m].ackFg =1;
			timeclk376[m].dataack = ack;
			return DACK_SUCESS;
	   }
	  }
	}
	return DACK_FAILURE;
} 
INT8U CSimJzq::SlaveSend376_2Buf(INT8U vSrcAFN,INT32U vSrcFn,INT8U *vSrcBuf,INT16U vSrcLen,sPartQCSG376_2DeCodeFrame DstDecodeDataFrame,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame)
{
	INT8U ack;

	ack = Ccsg13762.Code376_2_SlaveBufFrame(vSrcAFN,vSrcFn,vSrcBuf,vSrcLen,DstDecodeDataFrame.s_head,sQCSG376_2HostFrame);
	if(ack == DACK_SUCESS)
	{
		SendHost3762ToCom(sQCSG376_2HostFrame);
	}
	return ack;
}

//376.2的通用函数
INT8U CSimJzq::SlaveSend376_2NoBuf(INT8U vSrcAFN,INT16U vSrcFn,sPartQCSG376_2DeCodeFrame DstDecodeDataFrame,sPartQCSG376_2CreatFrame &sQCSG376_2HostFrame)
{
	INT8U ack;

	ack = Ccsg13762.Code376_2_SlaveFrame(vSrcAFN,vSrcFn,DstDecodeDataFrame.s_head,sQCSG376_2HostFrame);
	if(ack == DACK_SUCESS)
	{	
		SendHost3762ToCom(sQCSG376_2HostFrame);	
	}
	return ack;
}

INT8U CSimJzq::CmpDecode3762( sPartQCSG376_2DeCodeFrame DstDecodeDataFrame_1,sPartQCSG376_2DeCodeFrame DstDecodeDataFrame_2)
{
	INT16U len16=sizeof(sPartQCSG376_2DeCodeFrame);
	if(CompareNBuf((INT8U*)(&DstDecodeDataFrame_1),(INT8U*)(&DstDecodeDataFrame_2),len16)==EQU)
	{
		if(CompareNBuf(DstDecodeDataFrame_1.s_RcvDataBuf,DstDecodeDataFrame_2.s_RcvDataBuf,DstDecodeDataFrame_1.s_RcvDataLen)==EQU)
		{
			return DACK_SUCESS;
		}
	}
	return DACK_FAILURE;
}

#endif //_STD_CSG