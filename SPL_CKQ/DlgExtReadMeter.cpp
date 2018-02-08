// DlgExtReadMeter.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include <algorithm>
#include "SPL_CKQ.h"
#include "Tools.h"
#include "MainFrm.h"
#include "GW13762.h"
#include "DlgExtReadMeter.h"



extern CGW13762 Cgw13762;
#include "CSG13762.h"
extern CCSG13762 Ccsg13762;
#include "SimJzq.h"
extern CSimJzq  gSimJzq;

CMutex g_cMutex;


bool IsNotMet(s_NodeList task)
{
	return (task.is_met == 0);
}

bool IsFail(s_NodeList task)
{
	return (task.status == 0);
}

class vector_finder
{
public:
	vector_finder(const CString a) :m_findelm(a){}
	bool operator ()(std::vector<struct s_NodeList>::value_type &value)
	{
		return (value.node == m_findelm);
	}
private:
	CString m_findelm;
};


CString ErrorCode(INT8U code)
{
	switch (code)
	{
	case 1:
		return _T("14H-F1下行报文后的报文不是06H-F2");
	case 2:
		return _T("06H-F2的序号错误");
	case 3:
		return _T("确认帧的序号错误");
	case 4:
		return _T("14H-F1下行报文后的报文超时");
	case 0xff:
		return _T("未定义错误");
	case 0xcc:
		return _T("指针错误");
	default:
		return _T("未知错误");
	}
}

enum e_eventid{
	e_nop,
	e_syncnodefile,
	e_savenodefile,
	e_router_start,
	e_router_suspend,
	e_router_resume,
	e_readmeter,
	e_set_status,
};

// DlgExtReadMeter dialog

IMPLEMENT_DYNAMIC(DlgExtReadMeter, CDialogEx)

DlgExtReadMeter::DlgExtReadMeter(CWnd* pParent /*=NULL*/)
: CDialogEx(DlgExtReadMeter::IDD, pParent)
{
	m_bSettimer = 0;
	m_nTotal = 0;
	m_nReadFail = 0;
	m_nReadSuccess = 0;
	m_iRound = 0;
	dlgfile = new Dlgfile(_T("ConfigName='抄表信息'"));
}

DlgExtReadMeter::~DlgExtReadMeter()
{
	delete dlgfile;
}

void DlgExtReadMeter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, m_editReadCycle);
	DDX_Control(pDX, IDC_EDIT5, m_editReadLast);
	DDX_Control(pDX, IDC_EDIT2_RM, m_editShow);
	DDX_Control(pDX, IDC_BUTTON4_RM, m_btnStartReadMT);
	DDX_Control(pDX, IDC_BUTTON5_RM, m_btnStopReadMT);
	DDX_Control(pDX, IDC_COMBO1_RM, m_cbtnDi);

	DDX_Control(pDX, IDC_EDIT8_RM_STAT, m_RmStatus);
	DDX_Control(pDX, IDC_EDIT2_RM_TOTAL, m_RmTotal);
	DDX_Control(pDX, IDC_EDIT4_RM_SUCCESS, m_RmSuccess);
	DDX_Control(pDX, IDC_EDIT7_FAIL, m_RmFail);
	DDX_Control(pDX, IDC_EDIT1, m_editRound);
}


BEGIN_MESSAGE_MAP(DlgExtReadMeter, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1_RM, &DlgExtReadMeter::OnBnClickedButton1Rm)
	ON_BN_CLICKED(IDC_BUTTON2_RM, &DlgExtReadMeter::OnBnClickedButton2Rm)
	ON_BN_CLICKED(IDC_BUTTON3_RM, &DlgExtReadMeter::OnBnClickedButton3Rm)
	ON_BN_CLICKED(IDC_BUTTON4_RM, &DlgExtReadMeter::OnBnClickedButton4Rm)
	ON_BN_CLICKED(IDC_BUTTON6_RM, &DlgExtReadMeter::OnBnClickedButton6Rm)
	ON_BN_CLICKED(IDC_BUTTON5_RM, &DlgExtReadMeter::OnBnClickedButton5Rm)

	ON_WM_TIMER()


	ON_BN_CLICKED(IDC_BUTTON1, &DlgExtReadMeter::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, &DlgExtReadMeter::OnBnClickedButton7)
END_MESSAGE_MAP()


// DlgExtReadMeter message handlers


void DlgExtReadMeter::SetWindowText(INT32U idata)
{
	CString strtmp;
	strtmp.Format(_T("%d"), idata);
	SetWindowText(strtmp);
}

void DlgExtReadMeter::OnTimer(UINT_PTR nIDEvent)
{


	switch (nIDEvent)
	{
	case TIMER_ID_CYCLE:
		MyThread = AfxBeginThread(ThreadReadMeter, this);
		KillTimer(TIMER_ID_CYCLE);
		break;
	case TIMER_ID_LAST:
		m_bReadMeterStatus = 0;
		KillTimer(TIMER_ID_CYCLE);
		KillTimer(TIMER_ID_LAST);
		break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void DlgExtReadMeter::router_start()
{
	gSimJzq.HostSendRcv376_2NoBuf_NoAck(0x12, (INT16U)F1);
	SetWindowText(_T(">>>>重启路由\r\n"));
	Sleep(3000);
}

void DlgExtReadMeter::router_suspend()
{
	gSimJzq.HostSendRcv376_2NoBuf_NoAck(0x12, (INT16U)F2);
	SetWindowText(_T(">>>>暂停路由\r\n"));
}

void DlgExtReadMeter::router_resume()
{
	gSimJzq.HostSendRcv376_2NoBuf_NoAck(0x12, (INT16U)F3);
	SetWindowText(_T(">>>>恢复路由\r\n"));
}


BOOL DlgExtReadMeter::router_status()
{
	INT8U ack = -1;
	INT8U ret = 0xff;
	CString str = _T("");

	gSimJzq.ClrZjqComData();
	ack = gSimJzq.HostSendRcv376_2NoBuf(0xF0, F3, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);

	if (ack == DACK_SUCESS)
	{
		switch (m_ptRecvQGDW376_2.s_RcvDataBuf[0])
		{
		case 0:
			m_RmStatus.SetWindowTextW(_T("停止"));
			ret = 0;
			break;
		case 1:
			m_RmStatus.SetWindowTextW(_T("工作"));
			ret = 1;
			break;
		default:
			m_RmStatus.SetWindowTextW(_T("异常"));
			ret = 0;
			break;
		}
	}

	if (m_ptRecvQGDW376_2.s_head.s_AFN == 0x14)
		ret = 1;

	return ret;
}

INT32U DlgExtReadMeter::ReadNodeNumber()
{
	int ack = -1;
	CString str = _T("");
	INT32U ntotal = 0;
	ack = gSimJzq.HostSendRcv376_2NoBuf(0x10, F1, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);
	if (0 == ack)
	{
		if (m_ptRecvQGDW376_2.s_head.s_AFN == 0x10 && m_ptRecvQGDW376_2.s_head.s_FN == F1)
		{
			ntotal = m_ptRecvQGDW376_2.s_RcvDataBuf[1];
			ntotal <<= 8;
			ntotal += m_ptRecvQGDW376_2.s_RcvDataBuf[0];
			SetWindowText(_T(">>>>从节点数量:") + m_tools._str16tostr10(m_tools._buf16tostr16(&m_ptRecvQGDW376_2.s_RcvDataBuf[0], 2, false, true)) + _T("\r\n"));
			//TRACE("\nnumber: %d\n", ntotal);
			str.Format(_T("%d"), ntotal);
			m_RmTotal.SetWindowTextW(str);
			m_nTotal = ntotal;
			return ntotal;
		}
		else
		{
			SetWindowText(_T(">>>>数据包有误:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf, m_ptRecvQGDW376_2.s_RcvDataLen, false, true)) + _T("\r\n"));
			return 0;
		}
	}
	else
	{

		//TRACE("\nnoack: %d\n", ntotal);
		//TRACE("\nnum:afn %x fn %x\n", m_ptRecvQGDW376_2.s_head.s_AFN, m_ptRecvQGDW376_2.s_head.s_FN);
		return 0;
	}
}

bool DlgExtReadMeter::ReadMasterMAC(INT8U MAC[6])
{
	int ack = -1;
	int i = 0;
	ack = gSimJzq.HostSendRcv376_2NoBuf(0x03, F4, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);
	if (0 == ack)
	{
		if (m_ptRecvQGDW376_2.s_head.s_AFN == 0x03 && m_ptRecvQGDW376_2.s_head.s_FN == F4)
		{
			for (i = 0; i < 6; i++)
			{

				MAC[i] = m_ptRecvQGDW376_2.s_RcvDataBuf[i];
			}

			SetWindowText(_T(">>>>主节点地址:") + (m_tools._buf16tostr16(MAC, 6, false, true)) + _T("\r\n"));
			return TRUE;
		}
		else
		{
			SetWindowText(_T(">>>>数据包有误:") + m_tools._str16tostr10(m_tools._buf16tostr16(m_ptRecvQGDW376_2.s_RcvDataBuf, m_ptRecvQGDW376_2.s_RcvDataLen, false, true)) + _T("\r\n"));
			return FALSE;
		}
	}
	return TRUE;
}



void DlgExtReadMeter::SetWindowText(CString strData)
{
	CString strEditXianshi;
	m_editShow.GetWindowText(strEditXianshi);
	m_editShow.SetSel(strEditXianshi.GetLength(), strEditXianshi.GetLength());
	m_editShow.ReplaceSel(strData);
}

#define DRET_MAC_MATCH 0
#define DRET_MAC_REPEAT 1
#define DRET_OUT_OF_RANGE 2

INT8U DlgExtReadMeter::MatchNode_CheckRepeat(CString SearchStaMac,INT16U &StaIndex)
{
	INT8U ret=0xcc;
	INT32U n=0;
			for (n = 0; n < v_snodelist.size(); n++)
			{
				if (v_snodelist[n].node == SearchStaMac)
				{
					if (v_snodelist[n].is_met != 1)
					{
						v_snodelist[n].is_met = 1;
						StaIndex = n;
						ret=DRET_MAC_MATCH;
					}
					else
					{
						StaIndex = n;
						ret = DRET_MAC_REPEAT;
					}
					break;
				}
			}
			if (n == v_snodelist.size())
            {         
				ret=DRET_OUT_OF_RANGE;
                StaIndex=0;
             }
			return ret;
}

void DlgExtReadMeter::SaveFailureNode()
{
	CString strtmp=_T("");
	CString strSaveinfo = _T("");
	INT16U n = 0;

	for (n = 0; n < v_snodelist.size(); n++)
	{
		if (v_snodelist[n].status == 0)
		{
			strtmp += (v_snodelist[n].node + _T(",  "));
		}
	}


	if (m_nReadFail != 0)
	{
		SetWindowText(_T(">>>>读取失败从节点： ") + strtmp + _T("\r\n\r\n"));
		strSaveinfo = _T("Fail node, ") + strtmp + _T("\n");
		dlgfile->SaveInfo(strSaveinfo);
	}

}

#define FREME645DATALEN_STARTSITE   15
#define FREME645DI_STARTSITE        FREME645DATALEN_STARTSITE+1
#define FREME645DATA_STARTSITE      FREME645DI_STARTSITE+4

int DlgExtReadMeter::ReadMeter()
{

	INT8U ack = -1;
	INT8U n = 0;
	INT8U i = 0;
	INT8U MsgAddrBuf[18];
	INT16U Recvbuflen = 0;
	INT8U Sendbufdata[JZQ_MAX_BUFF_LEN];
	INT16U Sendbuflen = 3;
	sPartQGDW376_2CreatFrame ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
	cDTL2007 c_dtl2007;
	sDtl2007_Read sdtl2007read;
	INT32U nReadStart = 0;
	INT8U slaveMAC[8];
	CString strslave;
	INT8U datablockflg = 0;
	CString strn;
	CString dataitem = _T("");
	INT8U dataitemlen = 0;
	INT8U ReadNodeStatus = 0;
	CString strSaveinfo = _T("");
	CString strSeg[20] = { _T("") };
	INT8U nstrSeg = 0;
	CString strtmp;
	s_NodeList findelm;
	BOOL bRepeat = 0;
	INT16U iIndex = 0;
	INT8U tmpret=0;

	m_RmTotal.SetWindowTextW(_T("0"));
	m_RmSuccess.SetWindowTextW(_T("0"));
	m_RmFail.SetWindowTextW(_T("0"));
	m_nReadFail = 0;
	m_nReadSuccess = 0;

	strtmp.Format(_T("%d"), m_iRound);
	m_editRound.SetWindowTextW(strtmp);

	if (!m_bTerminateButtun)
	{
		dlgfile->FileNameIndexChange();
		dlgfile->SaveInfo(_T("SN,STA_MAC,Di,A_DATA,B_DATA,C_DATA,ERR_CODE\n"));
		ReadMasterMAC(&MsgAddrBuf[6]);

		GetNodeTable(ReadNodeNumber());
		strtmp.Format(_T("%x"), m_Di);
		SetWindowText(_T(">>>>数据标识:") + strtmp + _T("\r\n"));
	}
	MsgAddrBuf[0] = 0x04;
	for (n = 1; n < 6; n++)
		MsgAddrBuf[n] = 0;


	while (nReadStart < m_nTotal)
	{

		if (m_bTerminateButtun)
		{
			//SetWindowText(_T("抄表结束\r\n"));
			return false;
		}


		nstrSeg = 0;
		strSaveinfo = _T("");

		strSeg[nstrSeg++].Format(_T("%d"), nReadStart + 1);

		gSimJzq.ClrZjqComData();
		ptSendQGDW376_2.s_head.s_AFN = 0x14;
		ptSendQGDW376_2.s_head.s_FN = F1;
		if (DACK_SUCESS == gSimJzq.Wait3762AckCmpAFNFN(10000, 20, ptSendQGDW376_2, ptRecvQGDW376_2))//RX 14-F1
		{

			MsgAddrBuf[5] = ptRecvQGDW376_2.s_head.s_Msg_Seq;
			//prev_seq = MsgAddrBuf[5];


			for (n = 0; n < 6; n++)
			{
				slaveMAC[n] = Sendbufdata[n + 5] = MsgAddrBuf[n + 12] = ptRecvQGDW376_2.s_RcvDataBuf[n + 1];
			}
			


			strslave = m_tools._buf16tostr16(slaveMAC, 6, false, true);


			tmpret=MatchNode_CheckRepeat(strslave, iIndex);
			if(tmpret==DRET_MAC_REPEAT)
            {
                if(v_snodelist[iIndex].status==1)
                {
                    Sendbufdata[0] = 0;
				    Sendbufdata[1] = 0;
					Sendbufdata[2] = 0;
					Sendbufdata[3] = 0;
					ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43, MsgAddrBuf, 0x14, F1, Sendbufdata, 4, ptSendQGDW376_2, ptRecvQGDW376_2);
					
                }
                else
                {
                
                    Sendbufdata[0] = 1;
                    Sendbufdata[1] = 0;
                    Sendbufdata[2] = 0;
                    Sendbufdata[3] = 0;
                    ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43, MsgAddrBuf, 0x14, F1, Sendbufdata, 4, ptSendQGDW376_2, ptRecvQGDW376_2);
                 
                }
                continue;
				
            }
            else if(tmpret==DRET_OUT_OF_RANGE)
				break;


			SetWindowText(_T(">>>>当前从节点地址:") + strslave);


			Sendbufdata[0] = 0x02;
			Sendbufdata[1] = 0x00;
			c_dtl2007.CodeReadDataCmd(m_Di, &MsgAddrBuf[12], 0, sdtl2007read);
			Sendbufdata[2] = sdtl2007read.s_vDstCmdLen;
			memcpy_s(&Sendbufdata[3], 256, sdtl2007read.s_pDstCmdBuf, sdtl2007read.s_vDstCmdLen);
			Sendbufdata[3 + sdtl2007read.s_vDstCmdLen] = 0;


			ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43, MsgAddrBuf, 0x14, F1, Sendbufdata, Sendbufdata[2] + 4, ptSendQGDW376_2, ptRecvQGDW376_2);
			if (ack == DACK_SUCESS)//14-F1 ACK
			{
				if ((ptRecvQGDW376_2.s_head.s_AFN == 0x06) && (ptRecvQGDW376_2.s_head.s_FN == F2))//RX 06-F2
				{
                    //CString strtmp1;
                    //strtmp1=m_tools._buf16tostr16(ptRecvQGDW376_2.s_RcvDataBuf,ptRecvQGDW376_2.s_RcvDataLen,False,False);
					//AfxMessageBox(strtmp1);
                    
                
					if (ptRecvQGDW376_2.s_head.s_Msg_Seq == MsgAddrBuf[5])
					{
						//MsgAddrBuf[5] += 1;

						strSeg[nstrSeg++] = m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[7], 6, false, true);
						//SetWindowText(_T(">>>>从节点地址:") + strSeg[nstrSeg-1]);


                        
                        
						for (n = 0; n < 4; n++)
						{
							if (ptRecvQGDW376_2.s_RcvDataBuf[FREME645DI_STARTSITE + n] == 0x32)
								datablockflg = 1;
							ptRecvQGDW376_2.s_RcvDataBuf[FREME645DI_STARTSITE + n] -= 0x33;
						}

						strSeg[nstrSeg++] = m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[FREME645DI_STARTSITE], 4, false, true);
						//SetWindowText(_T(" 数据标识:") + strSeg[nstrSeg-1]);

						for (n = 0; n < ptRecvQGDW376_2.s_RcvDataBuf[FREME645DATALEN_STARTSITE] - 4; n++)
						{
						    TRACE("\nDATA %d %x\n",n,ptRecvQGDW376_2.s_RcvDataBuf[FREME645DATA_STARTSITE + n]);
							ptRecvQGDW376_2.s_RcvDataBuf[FREME645DATA_STARTSITE + n] -= 0x33;
						}

						SetWindowText(_T("--->成功， 数据: "));
						if (datablockflg)
						{
							for (n = 0; n < 3; n++)
							{
								dataitemlen = (ptRecvQGDW376_2.s_RcvDataBuf[FREME645DATALEN_STARTSITE] - 4) / 3;
								dataitem = m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[FREME645DATA_STARTSITE + n*dataitemlen], dataitemlen, false, true);
								if (m_dotnum != 0)
									dataitem.Insert(dataitemlen * 2 - m_dotnum - 1, _T("."));
								strSeg[nstrSeg++] = dataitem;
								SetWindowText(dataitem + _T(" "));
							}
						}
						else
						{
							dataitemlen = ptRecvQGDW376_2.s_RcvDataBuf[FREME645DATALEN_STARTSITE] - 4;
							dataitem = (m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[FREME645DATA_STARTSITE], dataitemlen, false, true));
							if (m_dotnum != 0)
								dataitem.Insert(dataitemlen * 2 - m_dotnum, _T("."));
							strSeg[nstrSeg++] = dataitem;
							SetWindowText(dataitem);
						}
						SetWindowText(_T("\r\n"));




						gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43, MsgAddrBuf, 0x00, F1, Sendbufdata, 0, ptSendQGDW376_2, ptRecvQGDW376_2);//HOST TO SLACE, CONFIRM FRAME
						ReadNodeStatus = RM_SUCCESS;
/*
                        if (ptRecvQGDW376_2.s_head.s_Msg_Seq == MsgAddrBuf[5] )
						{
							//MsgAddrBuf[5] += 1;
							Sendbufdata[0] = 0;
							Sendbufdata[1] = 0;
							Sendbufdata[2] = 0;
							Sendbufdata[3] = 0;
							ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43, MsgAddrBuf, 0x14, F1, Sendbufdata, 4, ptSendQGDW376_2, ptRecvQGDW376_2);
							ReadNodeStatus = RM_SUCCESS;
						}
						else//00-F1 SEQ ERR
						{
							ReadNodeStatus = RM_00F1SEQERR;

						}
*/
					}
					else//06-F2 SEQ ERR
					{
						ReadNodeStatus = RM_06F2SEQERR;
					}

				}
				else//NO 06-F2 ACK
				{
					if ((ptRecvQGDW376_2.s_head.s_AFN == 0x14) && (ptRecvQGDW376_2.s_head.s_FN == F1))
						ReadNodeStatus = RM_NOACK;
					ReadNodeStatus = RM_NO06F2;
					//SetWindowText(_T("no 06f2"));
				}

			}
			else//NO 14-01 ACK
			{
				ReadNodeStatus = RM_NOACK;
				//				SetWindowText(_T("---->没有14-F1应答\n"));
			}

			if (ReadNodeStatus != RM_SUCCESS)
			{
/*
				if (ReadNodeStatus != RM_NOACK)
				{
					Sendbufdata[0] = 1;
					Sendbufdata[1] = 0;
					Sendbufdata[2] = 0;
					Sendbufdata[3] = 0;
					ack = gSimJzq.HostSendRcv376_2MsgAddrBuf(0x43, MsgAddrBuf, 0x14, F1, Sendbufdata, 4, ptSendQGDW376_2, ptRecvQGDW376_2);
				}
*/
				strtmp.Format(_T("%d"), ReadNodeStatus);


				SetWindowText(_T("--->失败，原因： ") + ErrorCode(ReadNodeStatus) + _T("\r\n"));


				v_snodelist[iIndex].status = 0;
				strSeg[nstrSeg++] = m_tools._buf16tostr16(slaveMAC, 6, false, true);
				strSeg[nstrSeg++] = _T(",,,,") + strtmp;
				m_nReadFail++;
				strn.Format(_T("%d"), m_nReadFail);
				m_RmFail.SetWindowTextW(strn);


			}
			else
			{
				v_snodelist[iIndex].status = 1;
				m_nReadSuccess++;
				strn.Format(_T("%d"), m_nReadSuccess);
				m_RmSuccess.SetWindowTextW(strn);
			}

			for (n = 0; n < nstrSeg - 1; n++)
				strSaveinfo += (strSeg[n] + _T(","));
			strSaveinfo += strSeg[nstrSeg - 1] + _T("\n");

			dlgfile->SaveInfo(strSaveinfo);

			nReadStart++;
            //PrintNodeTable();

		}
		else
		{
			continue;
		}
	}//node 


	SaveFailureNode();


	SetTimer(TIMER_ID_CYCLE, (UINT)(m_fcycle * 1000 * 60), NULL);
	return TRUE;
}




BOOL DlgExtReadMeter::OnInitDialog()
{
	CDialog::OnInitDialog();


	wchar_t   buf[1000];
	CString str;
	CString fname = _T(".\\配置文件\\645数据标识.ini");

	GetPrivateProfileSectionNames(buf, sizeof(buf), fname);

	for (wchar_t* Name = buf; *Name != '\0'; Name += wcslen(Name) + 1)
	{
		str.Format(_T("%s"), Name);
		m_cbtnDi.AddString(str);
	}
	m_cbtnDi.SetCurSel(1);


	m_editReadCycle.SetWindowTextW(_T("0.5"));
	m_editReadLast.SetWindowTextW(_T("60"));

	m_EventID = e_set_status;
	AfxBeginThread(ThreadSwitch, this);

	return TRUE;
}

INT8U DlgExtReadMeter::GetNodeTable(INT32U nTotal)
{
	int ack = -1;
	INT8U Sendbufdata[4];
	INT32U n, i;
	INT32U quotient;
	INT32U remaider;
	s_NodeList s_nodelist_tmp;
	CString cstr;
	INT32U nsave = 0;
	INT8U nodenum = 0x0f;

	v_snodelist.clear();

	//TRACE("\ntotal:%d\n", nTotal);

	quotient = nTotal / nodenum;
	remaider = nTotal - quotient * nodenum;

	for (n = 0; n < quotient; n++)
	{
		Sendbufdata[0] = (INT8U)(01 + n * nodenum) & 0xff;
		Sendbufdata[1] = (INT8U)((01 + n * nodenum) >> 8) & 0xff;
		Sendbufdata[2] = nodenum;
		ack = gSimJzq.HostSendRcv376_2Buf(0x10, F2, Sendbufdata, 3, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);
		if (ack == DACK_SUCESS){
			for (i = 0; i < 0x0f; i++)
			{
				s_nodelist_tmp.node = m_tools._buf16tostr16(&m_ptRecvQGDW376_2.s_RcvDataBuf[3 + i * 8], 6, false, true);
				s_nodelist_tmp.prot_type = m_ptRecvQGDW376_2.s_RcvDataBuf[10 + i * 8] >> 3;
				s_nodelist_tmp.status = 0;
				s_nodelist_tmp.is_met = 0;
				v_snodelist.push_back(s_nodelist_tmp);
				
				


			}
			cstr.Format(_T("段%d保存成功!\r\n"), n);
			SetWindowText(cstr);
			nsave += nodenum;
		}

	}

	Sendbufdata[0] = (INT8U)(01 + quotient * nodenum) & 0xff;
	Sendbufdata[1] = (INT8U)((01 + quotient * nodenum) >> 8) & 0xff;
	Sendbufdata[2] = remaider;
	ack = gSimJzq.HostSendRcv376_2Buf(0x10, F2, Sendbufdata, 3, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);
	if (ack == DACK_SUCESS){
		for (i = 0; i < remaider; i++)
		{
			s_nodelist_tmp.node = m_tools._buf16tostr16(&m_ptRecvQGDW376_2.s_RcvDataBuf[3 + i * 8], 6, false, true);
			s_nodelist_tmp.prot_type = m_ptRecvQGDW376_2.s_RcvDataBuf[10 + i * 8] >> 3;
			s_nodelist_tmp.status = 0;
			s_nodelist_tmp.is_met = 0;
			v_snodelist.push_back(s_nodelist_tmp);
			
		}
		cstr.Format(_T("段%d保存成功!\r\n"), n);
		SetWindowText(cstr);
		nsave += remaider;
	}

	cstr.Format(_T("%d个从节点保存成功!\r\n"), nsave);
	SetWindowText(cstr);
	
	return 0;
}

void DlgExtReadMeter::PrintNodeTable()
{
	CString strtmp;
	CString strseg;

	for (INT32U i = 0; i < v_snodelist.size(); i++)
	{
		strseg.Format(_T(" type: %d is_met: %d status: %d\r\n"), v_snodelist[i].prot_type, v_snodelist[i].is_met, v_snodelist[i].status);
		strtmp = _T(" node: ") + v_snodelist[i].node + strseg;
		SetWindowText(strtmp);
	}
}



UINT DlgExtReadMeter::SaveNodeFile()
{

	GetNodeTable(ReadNodeNumber());

	CString str = _T("");

	DeleteFile(dlgsavenodefile->m_sfilename);

	for (INT32U i = 0; i < v_snodelist.size(); i++)
	{

		str.Format(_T("%d\r\n"), v_snodelist[i].prot_type);
		dlgsavenodefile->SaveInfo(v_snodelist[i].node + _T(",") + str);
	}
	return 0;
}
void DlgExtReadMeter::OnBnClickedButton1()//导出档案
{
	dlgsavenodefile = new Dlgfile(_T("ConfigName = '导出档案'"));

	if (dlgsavenodefile->DoModal() == IDOK)
	{
		m_EventID = e_savenodefile;
		AfxBeginThread(ThreadSwitch, this);
	}
	else
	{
		//AfxMessageBox(_T("取消导出档案！"));
	}

}

UINT DlgExtReadMeter::SyncNodeFile(INT16U NodeNum)
{
	CString str = _T("");

	INT8U *senddatabuf = new INT8U[4000];
	//INT8U senddatabuf[2000];
	INT32U senddatalen = 0;
	INT32U quotient, remainder;
	INT32U loop = 0, n = 0;
	INT16U MACLEN;
    __int64 NodeMAC;

	int ack = -1;
	CTools m_tools;
	CString strNodenum = _T("");
	CString cstr;

	INT32U nsuccess = 0;
	INT32U retrycnt = 0;

	memset((INT8U*)senddatabuf, 0, 4000);
	TRACE("\n mode %d \n", dlgsyncnodefile->m_SyncMdoe);

	if (dlgsyncnodefile->m_TotalNum == 0 || dlgsyncnodefile->m_TotalNum>1016)
    {
		AfxMessageBox(_T("从节点总数量为0或大于1016!"));
		return FALSE;	
    }

	else if (NodeNum == 0)
	{
		AfxMessageBox(_T("从节点数量为0!"));
		return FALSE;
	}

	if (dlgsyncnodefile->m_SyncMdoe == e_SyncFile)
    {
    
	    dlgsyncnodefile->ReadFileLine();
	    cstr.Format(_T("\r\n文件包含%d个从节点\r\n"), dlgsyncnodefile->m_fileline.size());
	    SetWindowText(cstr);
    
	    if (dlgsyncnodefile->m_fileline.size() == 0)
	    {
		    AfxMessageBox(_T("档案文件不存在或档案文件空白！"));
		    return FALSE;
	    }

		if (dlgsyncnodefile->m_fileline.size()<dlgsyncnodefile->m_TotalNum)
            dlgsyncnodefile->m_TotalNum=dlgsyncnodefile->m_fileline.size();        

    }
    else if(dlgsyncnodefile->m_SyncMdoe==e_SyncAuto)
    {

        
    }

    if(dlgsyncnodefile->m_ClearFirst)
    	ack = gSimJzq.HostSendRcv376_2NoBuf_NoAck(0x1, (INT16U)F2);
    else
        ack=DACK_SUCESS;

//	m_ptSendQGDW376_2.s_head.s_AFN = 0x03;
//	m_ptSendQGDW376_2.s_head.s_FN = F10;
//	ack=gSimJzq.Wait3762AckCmpAFNFN(20000, 20, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);

	if (ack == DACK_SUCESS)
	{
		quotient = dlgsyncnodefile->m_TotalNum / NodeNum;
		remainder = dlgsyncnodefile->m_TotalNum - quotient*NodeNum;

		senddatalen = 1 + 7 * NodeNum;
		for (loop = 0; loop < quotient; loop++)
		{

			senddatabuf[0] = (INT8U)NodeNum;
			//TRACE("\n mode %d\n", dlgsyncnodefile->m_SyncMdoe);
			for (n = 0; n < NodeNum; n++)
			{
				if (dlgsyncnodefile->m_SyncMdoe == e_SyncFile)
                {    
				    dlgsyncnodefile->SplitLine(dlgsyncnodefile->m_fileline[n + loop * NodeNum], _T(","));
				    m_tools._str16tobuf16(dlgsyncnodefile->m_linearg[0], &senddatabuf[1 + n * 7], MACLEN, true);
				    senddatabuf[7 + n * 7] = _ttoi(dlgsyncnodefile->m_linearg[1]);
                }
				else if (dlgsyncnodefile->m_SyncMdoe == e_SyncAuto)
                {
					NodeMAC = n + dlgsyncnodefile->m_StartMAC + loop*NodeNum;
					TRACE("\n mac 0x%llx\n",NodeMAC);
                    m_tools.DecToBCD(NodeMAC, &senddatabuf[1+n*7], 6);
                    senddatabuf[7 + n * 7] = 2;
                }
                
			}
		retry_loop:
			gSimJzq.ClrZjqComData();
			ack = gSimJzq.HostSendRcv376_2Buf(0x11, F1, senddatabuf, senddatalen, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);
			if (ack == DACK_SUCESS){
				if (m_ptRecvQGDW376_2.s_head.s_AFN == 0 && m_ptRecvQGDW376_2.s_head.s_FN == F2)
				{

					cstr.Format(_T("帧%d失败,从节点个数：%d,状态错误字：%02x\r\n"), loop, NodeNum, m_ptRecvQGDW376_2.s_RcvDataBuf[0]);
					SetWindowText(cstr);
				}
				else if (m_ptRecvQGDW376_2.s_head.s_AFN == 0 && m_ptRecvQGDW376_2.s_head.s_FN == F1)
				{
					cstr.Format(_T("帧%d成功, 从节点个数：%d\r\n"), loop, NodeNum);
					SetWindowText(cstr);
					nsuccess += NodeNum;
					retrycnt = 0;
				}
				else
				{
					
					
					m_ptSendQGDW376_2.s_head.s_AFN = 0x00;
					ack=gSimJzq.Wait3762AckCmpAFN(10000, 20, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);
					if (ack == DACK_SUCESS)
					{
						cstr.Format(_T("帧%d成功, 从节点个数：%d\r\n"), loop, NodeNum);
						SetWindowText(cstr);
						nsuccess += NodeNum;
					}
					else
					{
						cstr.Format(_T("帧%d错误, afn=%x,fn=%x，超时重发！\r\n"), loop, m_ptRecvQGDW376_2.s_head.s_AFN, m_ptRecvQGDW376_2.s_head.s_FN);
						SetWindowText(cstr);
					
#if 1
					retrycnt++;
					if (retrycnt < 3)
						goto retry_loop;
#endif
					}
				}
			}
			else if (ack == DACK_FAILURE)
			{
				cstr.Format(_T("帧%d错误，应答失败\r\n"), loop);
				SetWindowText(cstr);
				
			}
			Sleep(100);
		}

		retrycnt = 0;

		if (remainder)
		{
			senddatalen = 1 + 7 * remainder;
			senddatabuf[0] = remainder;
			TRACE("\nremaider %d \n", remainder);
			for (n = 0; n < remainder; n++)
			{			

				if (dlgsyncnodefile->m_SyncMdoe == e_SyncFile)
                {    
				    dlgsyncnodefile->SplitLine(dlgsyncnodefile->m_fileline[n + loop * NodeNum], _T(","));
				    m_tools._str16tobuf16(dlgsyncnodefile->m_linearg[0], &senddatabuf[1 + n * 7], MACLEN, true);
				    senddatabuf[7 + n * 7] = _ttoi(dlgsyncnodefile->m_linearg[1]);
                }
				else if (dlgsyncnodefile->m_SyncMdoe == e_SyncAuto)
                {
					NodeMAC = n + dlgsyncnodefile->m_StartMAC + loop*NodeNum;
                    m_tools.DecToBCD(NodeMAC, &senddatabuf[1+n*7], 6);
					TRACE("\n mac 0x%llx\n", NodeMAC);
                    senddatabuf[7 + n * 7] = 2;
                }
			}
		retry_remainder:
			gSimJzq.ClrZjqComData();
			ack = gSimJzq.HostSendRcv376_2Buf(0x11, F1, senddatabuf, senddatalen, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);
			if (ack == DACK_SUCESS)
			{
				if (m_ptRecvQGDW376_2.s_head.s_AFN == 0 && m_ptRecvQGDW376_2.s_head.s_FN == F2)
				{
					cstr.Format(_T("%d失败,从节点个数：%d,状态错误字：%02x\r\n"), loop, remainder, m_ptRecvQGDW376_2.s_RcvDataBuf[0]);
					SetWindowText(_T("帧") + cstr);
					//return FALSE;
				}
				else if (m_ptRecvQGDW376_2.s_head.s_AFN == 0 && m_ptRecvQGDW376_2.s_head.s_FN == F1)
				{
					cstr.Format(_T("%d成功, 从节点个数：%d\r\n"), loop, remainder);
					SetWindowText(_T("帧") + cstr);
					nsuccess += remainder;
					retrycnt = 0;
				}
				else
				{
					m_ptSendQGDW376_2.s_head.s_AFN = 0x00;
					ack = gSimJzq.Wait3762AckCmpAFN(10000, 20, m_ptSendQGDW376_2, m_ptRecvQGDW376_2);
					if (ack == DACK_SUCESS)
					{
						cstr.Format(_T("%d成功, 从节点个数：%d\r\n"), loop, NodeNum);
						SetWindowText(_T("帧") + cstr);
						nsuccess += NodeNum;
					}
					else
					{
						cstr.Format(_T("帧%d错误, afn=%x,fn=%x，超时重发！\r\n"), loop, m_ptRecvQGDW376_2.s_head.s_AFN, m_ptRecvQGDW376_2.s_head.s_FN);
						SetWindowText(cstr);

#if 1
						retrycnt++;
						if (retrycnt < 3)
							goto retry_remainder;
#endif
					}
				}
			}
			else if (ack == DACK_FAILURE)
			{
				cstr.Format(_T("帧%d错误，应答失败r\n"), loop);
				SetWindowText(cstr);
			}
		}

	}
	else
	{
		cstr.Format(_T("参数初始化失败\r\n"));
		SetWindowText(cstr);
	}

	cstr.Format(_T("导入%d个从节点, 成功%d个，失败%d个\r\n"), dlgsyncnodefile->m_TotalNum, nsuccess, dlgsyncnodefile->m_TotalNum - nsuccess);
	SetWindowText(cstr);

	delete senddatabuf;
	return TRUE;
}


void DlgExtReadMeter::OnBnClickedButton7()//导入档案
{
#if 0
	dlgsyncnodefile=new Dlgfile(_T("ConfigName = '导入档案'"));

	if (dlgsyncnodefile->DoModal() == IDOK)
	{
		m_EventID = e_syncnodefile;
		AfxBeginThread(ThreadSwitch, this);
	}
	else
	{
		AfxMessageBox(_T("取消导入档案！"));
	}
#else
	dlgsyncnodefile = new DialogSyncNodeFile(_T("ConfigName = '导入档案'"));



	if (dlgsyncnodefile->DoModal() == IDOK)
	{
		m_EventID = e_syncnodefile;

		//CString strtmp;
		//strtmp.Format(_T("   mode %d"), dlgsyncnodefile->m_SyncMdoe);
		//AfxMessageBox(strtmp);
		AfxBeginThread(ThreadSwitch, this);
	}
	else
	{
		//	AfxMessageBox(_T("取消导入档案！"));
	}

#endif
}



void DlgExtReadMeter::OnBnClickedButton1Rm()//reboot route
{

	m_EventID = e_router_start;
	AfxBeginThread(ThreadSwitch, this);

}



void DlgExtReadMeter::OnBnClickedButton2Rm()//suspend
{
	m_EventID = e_router_suspend;
	AfxBeginThread(ThreadSwitch, this);
}


void DlgExtReadMeter::OnBnClickedButton3Rm()//resume
{

	m_EventID = e_router_resume;
	AfxBeginThread(ThreadSwitch, this);
}



void DlgExtReadMeter::OnBnClickedButton4Rm()//start reading meter by route
{
	// TODO: Add your control notification handler code here

	CString strCycle = _T("");

	CString strTimeLast = _T("");
	CString strDi = _T("");

	m_editReadCycle.GetWindowText(strCycle);

	m_editReadLast.GetWindowText(strTimeLast);
	m_cbtnDi.GetWindowTextW(strDi);

	m_bTerminateButtun = 0;


	if (strCycle == "")
	{
		AfxMessageBox(_T("请设置抄表周期！"));
		return;
	}
	if (strTimeLast == "")
	{
		AfxMessageBox(_T("请设置抄表持续时间！"));
		return;
	}
	if (strDi == "")
	{
		AfxMessageBox(_T("请设置数据标识！"));
		return;
	}

	m_btnStartReadMT.EnableWindow(FALSE);


	MyThread = AfxBeginThread(ThreadReadMeter, this);

}


void DlgExtReadMeter::OnBnClickedButton6Rm()//set files saving path
{
	// TODO: Add your control notification handler code here

	dlgfile->DoModal();

}


void DlgExtReadMeter::OnBnClickedButton5Rm()//stop reading meter
{
	// TODO: Add your control notification handler code here

	KillTimer(TIMER_ID_CYCLE);
	KillTimer(TIMER_ID_LAST);
	m_btnStartReadMT.EnableWindow(true);
	m_bTerminateButtun = 1;

}




static UINT ThreadReadMeter(LPVOID pParam)
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	DlgExtReadMeter *pDlg = (DlgExtReadMeter*)pParam;

	double iCycle = 0;
	CString strCycle = _T("");
	double iTimeLast = 0;
	CString strTimeLast = _T("");
	INT8U CycleRead = 0;//timerID
	CString strDi;
	CString strDi_c;

	INT8U nPos = 0;

	g_cMutex.Lock();

	if (pDlg->m_bSettimer == 0)
	{


		pDlg->m_editReadCycle.GetWindowText(strCycle);
		iCycle = _ttof(strCycle);
		pDlg->m_fcycle = iCycle;

		pDlg->m_editReadLast.GetWindowText(strTimeLast);
		iTimeLast = _ttof(strTimeLast);



		//pDlg->SetTimer(TIMER_ID_CYCLE, (UINT)(iCycle * 1000*60), NULL);

		if (0 != iTimeLast)
		{
			pDlg->SetTimer(TIMER_ID_LAST, (UINT)(iTimeLast * 1000 * 60), NULL);
		}
		pDlg->m_bSettimer = 1;
	}

	pDlg->m_cbtnDi.GetWindowTextW(strDi);
	nPos = strDi.Find(_T("-"));
	pDlg->m_Di = (INT32U)wcstol(strDi.Left(nPos), NULL, 16);
	nPos = strDi.Find(_T("-"), nPos + 1);
	pDlg->m_dotnum = (INT32U)wcstol(strDi.Mid(nPos - 1, 1), NULL, 16);


	pDlg->m_bReadMeterStatus = pDlg->router_status();

	if (pDlg->m_bReadMeterStatus == 0)
	{
		AfxMessageBox(_T("请先重启路由！"));
		pDlg->m_btnStartReadMT.EnableWindow(TRUE);
		return 0;
	}

	//pDlg->GetNodeTable();
	//pDlg->PrintNodeTable();

	pDlg->m_iRound++;
	pDlg->ReadMeter();


	g_cMutex.Unlock();
	AfxEndThread(0);
	return 0;
}


static UINT ThreadSwitch(LPVOID pParam)
{
	DlgExtReadMeter *pDlg = (DlgExtReadMeter*)pParam;

	switch (pDlg->m_EventID)
	{
	case e_nop:
		break;
	case e_syncnodefile:
		//TRACE("\n mode %d \n", pDlg->dlgsyncnodefile->m_SyncMdoe);
		pDlg->SyncNodeFile(pDlg->dlgsyncnodefile->m_NodeNum);
		delete pDlg->dlgsyncnodefile;
		pDlg->dlgsyncnodefile = NULL;
		break;
	case e_savenodefile:
		pDlg->SaveNodeFile();
		delete pDlg->dlgsavenodefile;
		pDlg->dlgsavenodefile = NULL;
		break;
	case e_router_start:
		pDlg->router_start();
		pDlg->router_status();
		break;
	case e_router_suspend:
		pDlg->router_suspend();
		pDlg->router_status();
		break;
	case e_router_resume:
		pDlg->router_resume();
		pDlg->router_status();
		break;
	case e_set_status:
		pDlg->router_status();
		pDlg->m_RmTotal.SetWindowTextW(_T("0"));
		pDlg->m_RmSuccess.SetWindowTextW(_T("0"));
		pDlg->m_RmFail.SetWindowTextW(_T("0"));
		pDlg->m_editRound.SetWindowTextW(_T("0"));
	default:
		break;
	}
	AfxEndThread(0);
	return TRUE;
}
