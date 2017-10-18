#include "StdAfx.h"
#include "SimMeter.h"
#include "MyFunLib.h"
#include "KD_Project.h"
#include "cSerBuf_LoopRcv.h"
#include "User_App_Cfg.h"
#include "MainFrm.h"
extern cSerBuf_LoopRcv  m_loopRcv64507;

#include "LogFile.h"
extern CLogFile plog;
//07模拟表
static INT8U TYPE645_04000402[6]={0x00,0x00,0x00,0x00,0x00,0x00};//瞬时总有功功率
static INT8U LEN645_04000402 = 0x06;

static INT8U TYPE645_02030000[3]={0x00,0x00,0x00};//瞬时总有功功率
static INT8U LEN645_02030000=0x03;

static INT8U TYPE645_02030100[3]={0x00,0x00,0x00};
static INT8U LEN645_02030100=0x03;

static INT8U TYPE645_02030200[3]={0x00,0x00,0x00};
static INT8U LEN645_02030200=0x03;

static INT8U TYPE645_02030300[3]={0x00,0x00,0x00};
static INT8U LEN645_02030300=0x03;

static INT8U TYPE645_0203FF00[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static INT8U LEN645_0203FF00=0x0C;

static INT8U TYPE645_02040000[3]={0x00,0x00,0x00};//瞬时总无功功率
static INT8U LEN645_02040000=0x03;

static INT8U TYPE645_02040100[3]={0x00,0x00,0x00};
static INT8U LEN645_02040100=0x03;

static INT8U TYPE645_02040200[3]={0x00,0x00,0x00};
static INT8U LEN645_02040200=0x03;

static INT8U TYPE645_02040300[3]={0x00,0x00,0x00};
static INT8U LEN645_02040300=0x03;

static INT8U TYPE645_0204FF00[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static INT8U LEN645_0204FF00=0x0C;

static INT8U TYPE645_02010100[2]={0x00,0x00};//A 相电压
static INT8U LEN645_02010100=0x02;

static INT8U TYPE645_02010200[2]={0x00,0x00};
static INT8U LEN645_02010200=0x02;

static INT8U TYPE645_02010300[2]={0x00,0x00};
static INT8U LEN645_02010300=0x02;

static INT8U TYPE645_0201FF00[6]={0x01,0x02,0x03,0x04,0x05,0x06};
static INT8U LEN645_0201FF00=0x06;

static INT8U TYPE645_02020100[3]={0x00,0x00,0x00};//A 相电流
static INT8U LEN645_02020100=0x03;

static INT8U TYPE645_02020200[3]={0x00,0x00,0x00};
static INT8U LEN645_02020200=0x03;

static INT8U TYPE645_02020300[3]={0x00,0x00,0x00};
static INT8U LEN645_02020300=0x03;

static INT8U TYPE645_0202FF00[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static INT8U LEN645_0202FF00=0x09;

static INT8U TYPE645_00000000[4]={0x00,0x00,0x00,0x00};//(当前)组合有功总电能
static INT8U LEN645_00000000=0x04;

static INT8U TYPE645_00010000[4]={0x00,0x00,0x00,0x00};//(当前)正向有功总电能
static INT8U LEN645_00010000=0x04;

static INT8U TYPE645_0000FF00[20]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//(当前)组合有功电能数据块
static INT8U LEN645_0000FF00=0x14;

static INT8U TYPE645_0001FF00[20]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//(当前)正向有功电能数据块
static INT8U LEN645_0001FF00=0x14;

static INT8U TYPE645_00020000[4]={0x00,0x00,0x00,0x00};//(当前)反向有功总电能
static INT8U LEN645_00020000=0x04;

static INT8U TYPE645_0002FF00[20]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//(当前)反向有功电能数据块
static INT8U LEN645_0002FF00=0x14;

static INT8U TYPE645_00030000[4]={0x00,0x00,0x00,0x00};//(当前)组合无功 1 总电能
static INT8U LEN645_00030000=0x04;

static INT8U TYPE645_0003FF00[20]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//(当前)组合无功 1 电能数据块
static INT8U LEN645_0003FF00=0x14;

static INT8U TYPE645_00040000[4]={0x00,0x00,0x00,0x00};//(当前)组合无功 2 总电能
static INT8U LEN645_00040000=0x04;

static INT8U TYPE645_0004FF00[20]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//(当前)组合无功 2 电能数据块
static INT8U LEN645_0004FF00=0x14;

static INT8U TYPE645_04000102[3]={0x00,0x00,0x00};//时间
static INT8U LEN645_04000102=0x03;

static INT8U TYPE645_04000101[4]={0x00,0x00,0x00,0x00};//日期及星期(其中0代表星期天)
static INT8U LEN645_04000101=0x04;

static INT8U TYPE645_040005FF[14]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//电表运行状态字数据块
static INT8U LEN645_040005FF=0x0E;

static INT8U TYPE645_03300401[7]={0x00,0x00,0x00,0x00,0x00,0x00,0x00};//（上 1 次）校时记录：
static INT8U LEN645_03300401=0x07;

static INT8U TYPE645_05060001[5]={0x00,0x00,0x00,0x00,0x00};//（上 1 次）日冻结时间
static INT8U LEN645_05060001=0x05;

static INT8U TYPE645_05060101[20]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//（上 1 次）日冻结正向有功电能数据：
static INT8U LEN645_05060101=0x14;

static INT8U TYPE645_05060201[20]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//（上 1 次）日冻结反向有功电能数据：
static INT8U LEN645_05060201=0x14;

static INT8U TYPE645_05060301[20]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//（上 1 次）日冻结组合无功 1 电能数据：
static INT8U LEN645_05060301=0x14;

static INT8U TYPE645_05060401[20]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};//（上 1 次）日冻结组合无功 2 电能数据：
static INT8U LEN645_05060401=0x14;

static INT8U TYPE645_04001501[14]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xAA,0xAA};//状态字
static INT8U LEN645_04001501=0x0E;
static INT8U TYPE645_1901FF0101[179]={0};//过流
static INT8U LEN645_1901FF01=0xB3;

static INT8U TYPE645_04000401[20]={0x00,0x00,0x00,0x00,0x00,0x01};//表地址
static INT8U LEN645_04000401=0x6;
static INT8U TYPE64597_9010[4]={0X00,0X00,0X00,0X00};//（当前）正向有功总电能 4字节
static INT8U LEN64597_9010=0x04;
static INT8U TYPE64597_901F[60]={0x00};//(当前)正向有功电能数据块
static INT8U LEN64597_901F=0x3C;
static INT8U TYPE64597_9020[4]={0X00,0X00,0X00,0X00};//（当前）反向有功总电能 4字节
static INT8U LEN64597_9020=0x04;
static INT8U TYPE64597_B611[2]={0X00,0X00};//A 相电压 2字节
static INT8U LEN64597_B611=0x02;
static INT8U TYPE64597_B612[2]={0X00,0X00};//B 相电压 2字节
static INT8U LEN64597_B612=0x02;
static INT8U TYPE64597_B613[2]={0X00,0X00};//C 相电压 2字节
static INT8U LEN64597_B613=0x02;
static INT8U TYPE64597_B621[2]={0X00,0X00};//A 相电流 2字节
static INT8U LEN64597_B621=0x02;
static INT8U TYPE64597_B622[2]={0X00,0X00};//B 相电流 2字节
static INT8U LEN64597_B622=0x02;
static INT8U TYPE64597_B623[2]={0X00,0X00};//C 相电流 2字节
static INT8U LEN64597_B623=0x02;


sNoAckAllMsg   gNoAckDiAllMsg;
CSimMeter::CSimMeter(void)
{
	m_RunSta = 1;
	BufIs0((INT8U*)(&gNoAckDiAllMsg),sizeof(sNoAckAllMsg));
	m_ReadAmtCnt=0;
	m_AmtAckFg=1;
	ClrReadAmtCnt();
	m_SearchMeterData.s_AllCnt=1;
	m_SearchMeterData.s_SendCnt=1;
	m_SearchMeterData.s_SmtBpStart=0;
	m_SearchMeterData.s_Sta=0;
	  m_AmtAddBp=0;
}
CSimMeter::~CSimMeter(void)
{
}

void CSimMeter::SetAmtAddBp(INT16U vSrcBp)
{
 if(vSrcBp<D_MaxNodeCnt)
  m_AmtAddBp=vSrcBp;

}
void  CSimMeter::SetSearchSta(INT8U vSrcallcnt,INT8U vSrcSendCnt,INT16U vSrcAmtBp,INT8U vSrcSta)
{
	m_SearchMeterData.s_AllCnt=vSrcallcnt;
	m_SearchMeterData.s_SendCnt=vSrcSendCnt;
	m_SearchMeterData.s_SmtBpStart=vSrcAmtBp;
	m_SearchMeterData.s_Sta=vSrcSta;
}
void   CSimMeter::QueReadAmtMsg(sAckAmtMsg  &ReadAmtMsg)
{
	ReadAmtMsg=m_ReadAmtMsg;
}
void CSimMeter::ClrReadAmtCnt(void)
{
  m_ReadAmtCnt=0;
   m_ReadAmtMsg.s_RcvCnt=0;
  for(INT8U m=0;m<20;m++)
  {
	  m_ReadAmtMsg.s_Time[m]=0;
  }
}
void CSimMeter::SetAckAmtFg(INT8U Ackfg)
{
  m_AmtAckFg=Ackfg;
}
INT32U CSimMeter:: QueReadAmtCnt(void)
{
   return m_ReadAmtCnt;
}
void  CSimMeter::SetNoAckDi(INT32U vSrcDi)
{
	for(INT8U m=0;m<DNOACKDICNT;m++)
	{
     if(gNoAckDiAllMsg.s_NoAckMsg[m].s_Di==0)
	 {
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_Di=vSrcDi;
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_RcvCnt=0;
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[0]=0;
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[1]=0;
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[2]=0;
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[3]=0;
		 gNoAckDiAllMsg.s_NoAckDiCnt++;
		 break;
	 }
	}
}
void  CSimMeter::ClrNoAckDi(INT32U vSrcDi)
{
	for(INT8U m=0;m<DNOACKDICNT;m++)
	{
     if(gNoAckDiAllMsg.s_NoAckMsg[m].s_Di==vSrcDi)
	 {
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_Di=0;
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_RcvCnt=0;
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[0]=0;
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[1]=0;
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[2]=0;
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[3]=0;
		 gNoAckDiAllMsg.s_NoAckDiCnt--;
	 }
	}
}
void CSimMeter:: ClrALLNoAckDi(void)
{
  BufIs0((INT8U*)(&gNoAckDiAllMsg),sizeof(sNoAckAllMsg));
}
INT8U  CSimMeter::QueAckDiIsEn(INT32U vSrcDi)
{
	if(gNoAckDiAllMsg.s_NoAckDiCnt==0)
	{
      return DACK_SUCESS;
	}
	for(INT8U m=0;m<DNOACKDICNT;m++)
	{
     if(gNoAckDiAllMsg.s_NoAckMsg[m].s_Di==vSrcDi)
	 {
		if(gNoAckDiAllMsg.s_NoAckMsg[m].s_RcvCnt <= FRAME645_RESEND_MAXCNT)
		{
         gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[gNoAckDiAllMsg.s_NoAckMsg[m].s_RcvCnt]=GetSysTimeClk();
		}
		 gNoAckDiAllMsg.s_NoAckMsg[m].s_RcvCnt++;
		 return DACK_FAILURE;
	 }
	}
	return DACK_SUCESS;
}

INT8U CSimMeter::QueNoDiAckmsg(INT32U vSrcDi,sNoAckDiMsg  &ackMsg)
{
	ackMsg.s_Di = 0;
	ackMsg.s_RcvCnt=0;
	for(INT8U m=0;m<4;m++)
	{
		ackMsg.s_Time[m]=0x0;
	}
	for(INT8U m=0;m<DNOACKDICNT;m++)
	{
     if(gNoAckDiAllMsg.s_NoAckMsg[m].s_Di==vSrcDi)
	 {
		 ackMsg.s_Di = vSrcDi;
		 ackMsg.s_RcvCnt=gNoAckDiAllMsg.s_NoAckMsg[m].s_RcvCnt;
	   for(INT8U n=1;n<gNoAckDiAllMsg.s_NoAckMsg[m].s_RcvCnt;n++)
	   {
		   if(gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[n]>gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[n-1])
			{
				ackMsg.s_Time[n-1]=gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[n]-gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[n-1];
		    }
		   else
		   {
			   ackMsg.s_Time[n-1]=0xFFFFFFFF+gNoAckDiAllMsg.s_NoAckMsg[n].s_Time[n]-gNoAckDiAllMsg.s_NoAckMsg[m].s_Time[n-1];
		   }
	   }
	     plog.saveLog_NoAckMsg(DATA_FILE,TIME,_T(""),ackMsg,1);
	   return DACK_SUCESS;
	   
	 }
	}
	return DACK_FAILURE;
}
INT8U CSimMeter::CheckNoDiAckmsg(sNoAckDiMsg  noackMsg)
{
      if((noackMsg.s_RcvCnt<FRAME645_RESEND_MAXCNT)||(noackMsg.s_Time[0]<FRAME645_UARTFRAME_DLYTIME-200)||(noackMsg.s_Time[0]>FRAME645_UARTFRAME_DLYTIME+200)||(noackMsg.s_Time[1]>FRAME645_UARTFRAME_DLYTIME+200)||(noackMsg.s_Time[1]<FRAME645_UARTFRAME_DLYTIME-200))
		{
			return DACK_FAILURE;
		}
	  return DACK_SUCESS;
}
void CSimMeter::SendBufToCom(INT8U *vSrcBuf,INT16U vSrcLen)
{
	 CMainFrame * pMainDlg = (CMainFrame *)AfxGetApp()->GetMainWnd();;
	 pMainDlg->SendBufToCOMM(vSrcBuf ,vSrcLen , 1);	
}

INT8U CSimMeter::Cmp645DiDataAmt(INT8U *pSrcAddBuf,INT8U pcttype,INT32U vSrcDi,INT8U *vSrcBuf,INT16U vSrcLen,INT8U Cmptype)
{
	INT8U ack;	
  	Stu_Dtl2007  ackData645Frame;
	ack=Cmp645DiDataAndAck(pcttype,vSrcDi,vSrcBuf,vSrcLen,ackData645Frame,Cmptype);
	if((ack == DACK_SUCESS))
	{
      if(CompareNBuf(pSrcAddBuf,ackData645Frame.s_AmtBuf,6)==EQU)
	  {
         ack = DACK_SUCESS;
	  }
	}
    return ack;
}

INT8U CSimMeter::Cmp645DiDataAndAck(INT8U pcttype,INT32U vSrcDi,INT8U *vSrcBuf,INT16U vSrcLen,Stu_Dtl2007  &ackData645Frame,INT8U Cmptype)
{
	 INT8U ack;	
	

	
	

	ack = Decode2007(vSrcBuf,vSrcLen,ackData645Frame);
	if((ack == DACK_SUCESS))
	{
      if( ackData645Frame.s_Di == vSrcDi ) 
		{
		   if(Cmptype==1)
			{
				ack=CmpDeCode645DiData(ackData645Frame);
		   }
		   else
			{
				ack = DACK_SUCESS;
		   }
	   }
	  	else if((ackData645Frame.s_Con&Bit6))
		{
            ack = DACK_SUCESS;
		}
		else
		{
			ack = DACK_EER_645DATA;
		}
	}
	return ack;
}
INT8U CSimMeter::Cmp645DiData(INT8U pcttype,INT32U vSrcDi,INT8U *vSrcBuf,INT16U vSrcLen,INT8U Cmptype)
{
	 INT8U ack;	
	

	Stu_Dtl2007  ackData645Frame;
	ack=Cmp645DiDataAndAck(pcttype,vSrcDi,vSrcBuf,vSrcLen,ackData645Frame,Cmptype);
	return ack;
}
INT8U CSimMeter::CmpDeCode645DiData(Stu_Dtl2007 ackData645Frame)
{
//	 INT8U ack;	
	INT8U reack = DACK_FAILURE;
	sDtl645_Buf  data645;
	INT8U diack;
	 if(ackData645Frame.s_type==DPCT_97FG)
	 {
		diack= QueMeterData_64597(ackData645Frame.s_Di,data645);
	 }
    else
	{
		diack= QueMeterData_645(ackData645Frame.s_Di,data645);
    }
	
		if( diack == DACK_SUCESS)
		{
			if( ((data645.s_DataLen+4) == ackData645Frame.s_Len))
			{
				if(CompareNBuf(data645.s_DataBuf,ackData645Frame.s_pDstBuf,data645.s_DataLen)==EQU)
				{
					reack = DACK_SUCESS;
				}
				else
				{
				  reack = DACK_EER_645DATA;
				}
			}
		}
		else if((ackData645Frame.s_Con&Bit6))
		{
            reack = DACK_SUCESS;
		}
		else
		{
			reack = DACK_EER_645DATA;
		}
	return reack;
}
void CSimMeter::SendMeterData_645(Stu_Dtl2007 stDtl2007)
{
	
  if(QueAckDiIsEn(stDtl2007.s_Di)==DACK_SUCESS)
{
	sDtl645_Buf Meterdata;
	INT8U ack ;
	if(stDtl2007.s_Con==0x13)
	{
		 m_ReadAmtCnt++;
		if(m_ReadAmtMsg.s_RcvCnt<20)
		  {
             m_ReadAmtMsg.s_Time[m_ReadAmtMsg.s_RcvCnt]=GetSysTimeClk();
			  m_ReadAmtMsg.s_RcvCnt++;
		  }
		 
		  
		if(m_AmtAckFg==0)
			return ;
		stDtl2007.s_Con += 0x80;
		BufToBuf(Meterdata.s_DataBuf,&gNodeAddBuf[m_AmtAddBp][0],6);
		Meterdata.s_DataLen = 6;
		m_ReadAmtCnt++;
		BufToBuf(stDtl2007.s_AmtBuf,Meterdata.s_DataBuf,6);
	}
	else
	{
		ack = QueMeterData_645(stDtl2007.s_Di,Meterdata);
	if(ack == DACK_SUCESS)
	{
	   stDtl2007.s_Con += 0x80;
	}
	else
	{
		stDtl2007.s_Con = 0xD1;
		Meterdata.s_DataBuf[0]=0x02;
		Meterdata.s_DataLen = 1;
	}
	}
	CodeToAckData(stDtl2007,Meterdata.s_DataBuf,Meterdata.s_DataLen);

	SendBufToCom(stDtl2007.s_pDstBuf,stDtl2007.s_Len);
	plog.saveLog_HexBuf(PARS_FILE,OUTPUT,stDtl2007.s_pDstBuf,stDtl2007.s_Len);//打印接收帧数据
  }
  else
  {
	 plog.saveLog_str(PARS_FILE,TIME,_T("此DI不返回"),1);
  }
}


//从串口获取数据,645帧
void CSimMeter::GetCOMM645ToBuf(INT16U  getLen , INT16U nWaitFramTime , INT16U nWaiteByteTime ,INT8U * recvbuf,INT16U &recvlen)
{
	INT16U len = 0;
	INT16U dlycnt=0;
	INT16U acklen;
	INT16U tmp16;
	INT8U ack;
	while(true)
	{
		
			len = m_loopRcv64507.LoopReadRcvBufNByte(1 , recvbuf );
	
		if (1 == len) 
		{
			break;
		}
	if(nWaitFramTime >0 )
	{
		Sleep(10);
	}
	else
	{
        recvlen = 0;
		return ;
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
		
			tmp16= m_loopRcv64507.LoopReadRcvBufNByte(1, &recvbuf[len] );
			if( tmp16 ==0)
			{
				if(nWaiteByteTime > 0)
				{
					Sleep(nWaiteByteTime);
				}
			   tmp16= m_loopRcv64507.LoopReadRcvBufNByte(1, &recvbuf[len] );
			   if( tmp16 ==0)
			   {
                 break;
			   }
			}
			len  += tmp16;
			ack = Check645Full(recvbuf,len,acklen);
			if( ack == DACK_SUCESS)
			{
				break;
			}
		
		
		}
	recvlen = len;

	if(recvlen>0)
	{
		CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	   //CImitateMeterDlg * pMainDlg = (CImitateMeterDlg *)theApp.m_pMainWnd;
		plog.saveLog_HexBuf(DATA_FILE,INPUT_DATA,recvbuf,recvlen);//打印接收帧数据
	}
}

void CSimMeter::CheckMeterOP(void)
{
	if( m_RunSta >0)
	{	
		INT8U tmpbbuf[500];
		INT16U tmp16;
		INT8U ack;
		INT8U pct;
		Stu_Dtl2007 DstDecode2007DataFrame;
		GetCOMM645ToBuf(500,0,50,tmpbbuf,tmp16);
		if(tmp16>0)
		{
		    ack = CheckFull645Pct_All(tmpbbuf,tmp16,pct);
		   if(ack == DACK_SUCESS)
			{
			if(pct==DPCT_97FG)
			{
				ack = Decode2007(tmpbbuf,tmp16,DstDecode2007DataFrame);
				 if(ack == DACK_SUCESS)
				 {
					 SendMeterData_64597(DstDecode2007DataFrame);
				 }
			}
			else
			 {
				 ack = Decode2007(tmpbbuf,tmp16,DstDecode2007DataFrame);
			  if(ack == DACK_SUCESS)
			  {
				SendMeterData_645(DstDecode2007DataFrame);
			  }
			}
		   }
		}
	}
}
INT8U CSimMeter::Wait645ack(INT16U famedly,INT16U bytedly,Stu_Dtl2007 &DstDecode2007DataFrame)
{
	
		INT8U tmpbbuf[500];
		INT16U tmp16;
		INT8U ack = DACK_FAILURE;
		GetCOMM645ToBuf(500,famedly,bytedly,tmpbbuf,tmp16);
		if(tmp16>0)
		{
			ack = Decode2007(tmpbbuf,tmp16,DstDecode2007DataFrame);
		
		}
	return ack;
}
void CSimMeter::ClrSimMeterComData(void)
{
	m_loopRcv64507.ClrRcvBuf();
}
INT8U CSimMeter::QueMeterData_645(INT32U vSrcDi,sDtl645_Buf  &Meterdata )
{
	INT8U ack = DACK_SUCESS;
	switch(vSrcDi)
	{
	case 0x04000402:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_04000402,LEN645_04000402);  
		Meterdata.s_DataLen=LEN645_04000402;
		break;
	case 0x02030000:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02030000,LEN645_02030000);  
		Meterdata.s_DataLen=LEN645_02030000;
		break;
	case 0x02030100:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02030100,LEN645_02030100);  
		Meterdata.s_DataLen=LEN645_02030100;
		break;
	case 0x02030200:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02030200,LEN645_02030200);  
		Meterdata.s_DataLen=LEN645_02030200;
		break;
	case 0x02030300:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02030300,LEN645_02030300);  
		Meterdata.s_DataLen=LEN645_02030300;
		break;
	case 0x0203FF00:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_0203FF00,LEN645_0203FF00);  
		Meterdata.s_DataLen=LEN645_0203FF00;
		break;
	case 0x02040000:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02040000,LEN645_02040000);  
		Meterdata.s_DataLen=LEN645_02040000;
		break;
	case 0x02040100:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02040100,LEN645_02040100);  
		Meterdata.s_DataLen=LEN645_02040100;
		break;
	case 0x02040200:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02040200,LEN645_02040200);  
		Meterdata.s_DataLen=LEN645_02040200;
		break;
	case 0x02040300:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02040300,LEN645_02040300);  
		Meterdata.s_DataLen=LEN645_02040300;
		break;
	case 0x0204FF00:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_0204FF00,LEN645_0204FF00);  
		Meterdata.s_DataLen=LEN645_0204FF00;
		break;
	case 0x02010100:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02010100,LEN645_02010100);  
		Meterdata.s_DataLen=LEN645_02010100;
		break;
	case 0x02010200:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02010200,LEN645_02010200);  
		Meterdata.s_DataLen=LEN645_02010200;
		break;
	case 0x02010300:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02010300,LEN645_02010300);  
		Meterdata.s_DataLen=LEN645_02010300;
		break;
	case 0x0201FF00:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_0201FF00,LEN645_0201FF00);  
		Meterdata.s_DataLen=LEN645_0201FF00;
		break;
	case 0x02020100:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02020100,LEN645_02020100);  
		Meterdata.s_DataLen=LEN645_02020100;
		break;
	case 0x02020200:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02020200,LEN645_02020200);  
		Meterdata.s_DataLen=LEN645_02020200;
		break;
	case 0x02020300:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_02020300,LEN645_02020300);  
		Meterdata.s_DataLen=LEN645_02020300;
		break;
	case 0x0202FF00:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_0202FF00,LEN645_0202FF00);  
		Meterdata.s_DataLen=LEN645_0202FF00;
		break;
	case 0x00000000:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_00000000,LEN645_00000000);  
		Meterdata.s_DataLen=LEN645_00000000;
		break;
	case 0x00010000:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_00010000,LEN645_00010000);  
		Meterdata.s_DataLen=LEN645_00010000;
		break;
	case 0x0000FF00:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_0000FF00,LEN645_0000FF00);  
		Meterdata.s_DataLen=LEN645_0000FF00;
		break;
	case 0x0001FF00:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_0001FF00,LEN645_0001FF00);  
		Meterdata.s_DataLen=LEN645_0001FF00;
		break;
	case 0x00020000:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_00020000,LEN645_00020000);  
		Meterdata.s_DataLen=LEN645_00020000;
		break;
	case 0x0002FF00:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_0002FF00,LEN645_0002FF00);  
		Meterdata.s_DataLen=LEN645_0002FF00;
		break;
	case 0x00030000:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_00030000,LEN645_00030000);  
		Meterdata.s_DataLen=LEN645_00030000;
		break;
	case 0x0003FF00:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_0003FF00,LEN645_0003FF00);  
		Meterdata.s_DataLen=LEN645_0003FF00;
		break;
	case 0x00040000:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_00040000,LEN645_00040000);  
		Meterdata.s_DataLen=LEN645_00040000;
		break;
	case 0x0004FF00:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_0004FF00,LEN645_0004FF00);  
		Meterdata.s_DataLen=LEN645_0004FF00;
		break;
	case 0x04000102:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_04000102,LEN645_04000102);  
		Meterdata.s_DataLen=LEN645_04000102;
		break;
	case 0x04000101:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_04000101,LEN645_04000101);  
		Meterdata.s_DataLen=LEN645_04000101;
		break;
	case 0x040005FF:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_040005FF,LEN645_040005FF);  
		Meterdata.s_DataLen=LEN645_040005FF;
		break;
	case 0x03300401:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_03300401,LEN645_03300401);  
		Meterdata.s_DataLen=LEN645_03300401;
		break;
	case 0x05060001:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_05060001,LEN645_05060001);  
		Meterdata.s_DataLen=LEN645_05060001;
		break;
	case 0x05060101:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_05060101,LEN645_05060101);  
		Meterdata.s_DataLen=LEN645_05060101;
		break;
	case 0x05060201:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_05060201,LEN645_05060201);  
		Meterdata.s_DataLen=LEN645_05060201;
		break;
	case 0x05060301:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_05060301,LEN645_05060301);  
		Meterdata.s_DataLen=LEN645_05060301;
		break;
	case 0x05060401:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_05060401,LEN645_05060401);  
		Meterdata.s_DataLen=LEN645_05060401;
		break;
	case 0x04000401:
		BufToBuf(Meterdata.s_DataBuf,TYPE645_04000401,LEN645_04000401);  
		Meterdata.s_DataLen=LEN645_04000401;
		break;
	case 0x1901FF01:
		BufIsValue(Meterdata.s_DataBuf,179,0x00);
		Meterdata.s_DataLen=179;break;
	case 0x19010001:
		BufIsValue(Meterdata.s_DataBuf,240,0x33);
		Meterdata.s_DataLen=240;
		break;
	case 0x0B0A0B0A:
		Meterdata.s_DataLen=0;
		break;
	case 0x0B0D0B0D:
		Meterdata.s_DataBuf[1]=m_SearchMeterData.s_Sta;
		Meterdata.s_DataBuf[1]=m_SearchMeterData.s_AllCnt;
		Meterdata.s_DataBuf[2]=m_SearchMeterData.s_SendCnt;
		for(INT8U m=0;(m<m_SearchMeterData.s_SendCnt)&& (m<32);m++)
		{
			if(m_SearchMeterData.s_SmtBpStart+m<D_MaxNodeCnt)
			{
				BufToBuf(&Meterdata.s_DataBuf[3+m*7],&gNodeAddBuf[m_SearchMeterData.s_SmtBpStart+m][0],7);
			}
		}
		Meterdata.s_DataLen=m_SearchMeterData.s_SendCnt*7+3;
		break;
	default:
		ack = DACK_FAILURE;
		break;
	}
	return ack;
}

INT8U CSimMeter::ChangeMeterData_645(INT32U vSrcDi)
{
 INT8U tmp8;
 INT8U ack = DACK_SUCESS;
	switch(vSrcDi)
	{
	case 0x04000402:
	   tmp8=TYPE645_04000402[1];
	   tmp8=BcdToHex(tmp8);
	   tmp8++;
	   tmp8=HexToBcd(tmp8);
	   TYPE645_04000402[1] =tmp8;
		break;
	case 0x04000401:
		tmp8=TYPE645_04000401[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_04000401[1] =tmp8;
		break;
	case 0x02030000:
		tmp8=TYPE645_02030000[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02030000[1] =tmp8;
		break;
	case 0x02030100:
		tmp8=TYPE645_02030100[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02030100[1] =tmp8;
		break;
	case 0x02030200:
		tmp8=TYPE645_02030200[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02030200[1] =tmp8;
		break;
	case 0x02030300:
		tmp8=TYPE645_02030300[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02030300[1] =tmp8;
		break;
	case 0x0203FF00:
		tmp8=TYPE645_0203FF00[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_0203FF00[1] =tmp8;
		break;
	case 0x02040000:
		tmp8=TYPE645_02040000[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02040000[1] =tmp8;
		break;
	case 0x02040100:
		tmp8=TYPE645_02040100[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02040100[1] =tmp8;
		break;
	case 0x02040200:
		tmp8=TYPE645_02040200[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02040200[1] =tmp8;
		break;
	case 0x02040300:
		tmp8=TYPE645_02040300[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02040300[1] =tmp8;
		break;
	case 0x0204FF00:
		tmp8=TYPE645_0204FF00[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_0204FF00[1] =tmp8;
		break;
	case 0x02010100:
		tmp8=TYPE645_02010100[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02010100[1] =tmp8;
		break;
	case 0x02010200:
		tmp8=TYPE645_02010200[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02010200[1] =tmp8;
		break;
	case 0x02010300:
		tmp8=TYPE645_02010300[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02010300[1] =tmp8;
		break;
	case 0x0201FF00:
		tmp8=TYPE645_0201FF00[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_0201FF00[1] =tmp8;
		break;
	case 0x02020100:
		tmp8=TYPE645_02020100[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02020100[1] =tmp8;
		break;
	case 0x02020200:
		tmp8=TYPE645_02020200[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02020200[1] =tmp8;
		break;
	case 0x02020300:
		tmp8=TYPE645_02020300[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_02020300[1] =tmp8;
		break;
	case 0x0202FF00:
		tmp8=TYPE645_0202FF00[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_0202FF00[1] =tmp8;
		break;
	case 0x00000000:
		tmp8=TYPE645_00000000[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_00000000[1] =tmp8;
		break;
	case 0x00010000:
		tmp8=TYPE645_00010000[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_00010000[1] =tmp8;
		break;
	case 0x0000FF00:
		tmp8=TYPE645_0000FF00[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_0000FF00[1] =tmp8;
		break;
	case 0x0001FF00:
		tmp8=TYPE645_0001FF00[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_0001FF00[1] =tmp8;
		break;
	case 0x00020000:
		tmp8=TYPE645_00020000[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_00020000[1] =tmp8;
		break;
	case 0x0002FF00:
		tmp8=TYPE645_0002FF00[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_0002FF00[1] =tmp8;
		break;
	case 0x00030000:
		tmp8=TYPE645_00030000[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_00030000[1] =tmp8;
		break;
	case 0x0003FF00:
		tmp8=TYPE645_0003FF00[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_0003FF00[1] =tmp8;
		break;
	case 0x00040000:
		tmp8=TYPE645_00040000[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_00040000[1] =tmp8;
		break;
	case 0x0004FF00:
		tmp8=TYPE645_0004FF00[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_0004FF00[1] =tmp8;
		break;
	case 0x04000102:
		tmp8=TYPE645_04000102[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_04000102[1] =tmp8;
		break;
	case 0x04000101:
		tmp8=TYPE645_04000101[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_04000101[1] =tmp8;
		break;
	case 0x040005FF:
		tmp8=TYPE645_040005FF[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_040005FF[1] =tmp8;
		break;
	case 0x03300401:
		tmp8=TYPE645_03300401[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_03300401[1] =tmp8;
		break;
	case 0x05060001:
		tmp8=TYPE645_05060001[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_05060001[1] =tmp8;
		break;
	case 0x05060101:
		tmp8=TYPE645_05060101[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_05060101[1] =tmp8;
		break;
	case 0x05060201:
		tmp8=TYPE645_05060201[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_05060201[1] =tmp8;
		break;
	case 0x05060301:
		tmp8=TYPE645_05060301[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_05060301[1] =tmp8;
		break;
	case 0x05060401:
		tmp8=TYPE645_05060401[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_05060401[1] =tmp8;
		break;
	case 0x04001501:
		tmp8=TYPE645_04001501[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_04001501[1] =tmp8;
		break;
	case 0x1901FF0101:
		tmp8=TYPE645_1901FF0101[1];
		tmp8=BcdToHex(tmp8);
		tmp8++;
		tmp8=HexToBcd(tmp8);
		TYPE645_1901FF0101[1] =tmp8;
		break;
	default:
		ack = DACK_FAILURE;
		break;
	}
	
	return ack;
}


void CSimMeter::SetSimMeterRunFg(INT8U type)
{
  m_RunSta = type;
}
void CSimMeter::SetAckFg(INT8U type)
{
	m_NoFg = type;
}
void CSimMeter::SendMeterData_64597(Stu_Dtl2007 stDtl2007)
{
	sDtl645_Buf Meterdata;
	INT8U ack ;
	ack = QueMeterData_64597((INT16U)stDtl2007.s_Di,Meterdata);
	if(ack == DACK_SUCESS)
	{
	   stDtl2007.s_Con += 0x80;
	}
	else
	{
		stDtl2007.s_Con = 0xD1;
		Meterdata.s_DataBuf[0]=0x02;
		Meterdata.s_DataLen = 1;
	}
	CodeToAck97Data(stDtl2007,Meterdata.s_DataBuf,Meterdata.s_DataLen);

	
	SendBufToCom(stDtl2007.s_pDstBuf,stDtl2007.s_Len);
	plog.saveLog_HexBuf(DATA_FILE,OUTPUT,stDtl2007.s_pDstBuf,stDtl2007.s_Len);//打印接收帧数据
}
INT8U CSimMeter::QueMeterData_64597(INT32U vSrcDi,sDtl645_Buf  &Meterdata )
{
	INT8U ack = DACK_SUCESS;
	switch(vSrcDi)
	{
	case 0x9010:
		BufToBuf(Meterdata.s_DataBuf,TYPE64597_9010,LEN64597_9010);  
		Meterdata.s_DataLen=LEN64597_9010;
		break;
	case 0x901F:
		BufToBuf(Meterdata.s_DataBuf,TYPE64597_901F,LEN64597_901F);  
		Meterdata.s_DataLen=LEN64597_901F;
		break;
	case 0x9020:
		BufToBuf(Meterdata.s_DataBuf,TYPE64597_9020,LEN64597_9020);  
		Meterdata.s_DataLen=LEN64597_9020;
		break;
	case 0xB611:
		BufToBuf(Meterdata.s_DataBuf,TYPE64597_B611,LEN64597_B611);  
		Meterdata.s_DataLen=LEN64597_B611;
		break;
	case 0xB612:
		BufToBuf(Meterdata.s_DataBuf,TYPE64597_B612,LEN64597_B612);  
		Meterdata.s_DataLen=LEN64597_B612;
		break;
	case 0xB613:
		BufToBuf(Meterdata.s_DataBuf,TYPE64597_B613,LEN64597_B613);  
		Meterdata.s_DataLen=LEN64597_B613;
		break;
	case 0xB621:
		BufToBuf(Meterdata.s_DataBuf,TYPE64597_B621,LEN64597_B621);  
		Meterdata.s_DataLen=LEN64597_B621;
		break;
	case 0xB622:
		BufToBuf(Meterdata.s_DataBuf,TYPE64597_B622,LEN64597_B622);  
		Meterdata.s_DataLen=LEN64597_B622;
		break;
	case 0xB623:
		BufToBuf(Meterdata.s_DataBuf,TYPE64597_B623,LEN64597_B623);  
		Meterdata.s_DataLen=LEN64597_B623;
		break;
	default:
		ack = DACK_FAILURE;
		break;
	}
	return ack;
}

INT8U CSimMeter::ChangeMeterData_645_97(INT16U vSrcDi)
{
 INT8U tmp8;
 INT8U ack = DACK_SUCESS;
 switch(vSrcDi)
 {
 case 0x9010:
	 tmp8=TYPE64597_9010[1];
	 tmp8=BcdToHex(tmp8);
	 tmp8++;
	 tmp8=HexToBcd(tmp8);
	 TYPE64597_9010[1] =tmp8;
	 break;
 case 0x901F:
	 tmp8=TYPE64597_901F[1];
	 tmp8=BcdToHex(tmp8);
	 tmp8++;
	 tmp8=HexToBcd(tmp8);
	 TYPE64597_901F[1] =tmp8;
	 break;
 case 0x9020:
	 tmp8=TYPE64597_9020[1];
	 tmp8=BcdToHex(tmp8);
	 tmp8++;
	 tmp8=HexToBcd(tmp8);
	 TYPE64597_9020[1] =tmp8;
	 break;
 case 0xB611:
	 tmp8=TYPE64597_B611[1];
	 tmp8=BcdToHex(tmp8);
	 tmp8++;
	 tmp8=HexToBcd(tmp8);
	 TYPE64597_B611[1] =tmp8;
	 break;
 case 0xB612:
	 tmp8=TYPE64597_B612[1];
	 tmp8=BcdToHex(tmp8);
	 tmp8++;
	 tmp8=HexToBcd(tmp8);
	 TYPE64597_B612[1] =tmp8;
	 break;
 case 0xB613:
	 tmp8=TYPE64597_B613[1];
	 tmp8=BcdToHex(tmp8);
	 tmp8++;
	 tmp8=HexToBcd(tmp8);
	 TYPE64597_B613[1] =tmp8;
	 break;
 case 0xB621:
	 tmp8=TYPE64597_B621[1];
	 tmp8=BcdToHex(tmp8);
	 tmp8++;
	 tmp8=HexToBcd(tmp8);
	 TYPE64597_B621[1] =tmp8;
	 break;
 case 0xB622:
	 tmp8=TYPE64597_B622[1];
	 tmp8=BcdToHex(tmp8);
	 tmp8++;
	 tmp8=HexToBcd(tmp8);
	 TYPE64597_B622[1] =tmp8;
	 break;
 case 0xB623:
	 tmp8=TYPE64597_B623[1];
	 tmp8=BcdToHex(tmp8);
	 tmp8++;
	 tmp8=HexToBcd(tmp8);
	 TYPE64597_B623[1] =tmp8;
	 break;
 default:
	 ack = DACK_FAILURE;
	 break;
 }

 return  ack;
}
INT8U CSimMeter::ChangeMeterData(INT8U pctype,INT32U vSrcDi)
{
   if(pctype == DPCT_97FG)
   {
	  return(ChangeMeterData_645_97((INT16U)vSrcDi));
   }
   else
   {
	   return( ChangeMeterData_645(vSrcDi));
   }
}

INT8U  CSimMeter::QueMeterData(INT8U pctype,INT32U vSrcDi,sDtl645_Buf  &Meterdata )
{

 if(pctype == DPCT_97FG)
   {
	  return(QueMeterData_64597((INT16U)vSrcDi,Meterdata));
   }
   else
   {
	   return( QueMeterData_645(vSrcDi,Meterdata));
   }
}
