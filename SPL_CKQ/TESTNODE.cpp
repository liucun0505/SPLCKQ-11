// TESTNODE.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTNODE.h"
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


IMPLEMENT_DYNAMIC(CTESTNODE, CWnd)

CTESTNODE::CTESTNODE()
{

}

CTESTNODE::~CTESTNODE()
{
}


BEGIN_MESSAGE_MAP(CTESTNODE, CWnd)
END_MESSAGE_MAP()



// CTESTNODE message handlers

UINT8 NODE_RAMACKLIST[2048][6];//存添加的从节点地址列表
UINT8 NODE_READDELLIST[2048][6];//存添加删除后读到的从节点地址列表
UINT8 FALSH_ACKNODELIST[2048][6];//存FLASH里的从节点地址列表
BYTE m_add_nod_num;
//初步预料每次增加的节点数
CString m_start_nod_addr;
UINT64 m_l64AutoTestAddrCounter;//起始地址，起始也是实际写入地址（不断累加，当前值为一些如地址+1）64bit的地址表现形式
BYTE m_protocol_type;
BYTE m_nodNumPerframe_Set;
//设定的每帧节点数量
BYTE gB_nodNumThisFrame;//当前发送帧的节点数量

ST_ADD_DEL_NOD_TEST stADelNodTest;
#define READ_SN_BEGIN 1
#define RESEND_CHANCE_TIMES 2
#define ADD_NODE_NUM_MAX 200

#define FLASH_START_ADDR 0x2000

void CTESTNODE::C3762_TEST(HTREEITEM hTree)
{
	CImitateMeterDlg * pMainDlg = (CImitateMeterDlg *)theApp.m_pMainWnd;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
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
	INT8U allSucesscnt = 0;
	INT8U allfailcnt = 0;;
	INT8U resucnt=0;
	INT8U refailcnt=0;
	WORD i,j,wNumOf1K_flash,loopMax;//1kflash数据的数目
	UINT64 k;
	bool btestResult  = false;
	CString str;
	INT8U tmpbuf[12];
	INT16U st_seq = 1;
	Hex16ToBuf2(st_seq,tmpbuf);
	tmpbuf[2] = 1;

	CTime startTime,endTime;

	startTime = CTime::GetCurrentTime();

	memset(&pMainDlg->stRecvNodInfor,0,sizeof(ST_RECV_NOD_INFOR));

	ack = gSimJzq.Router_PaRst();


	//增加节点参数初始化 
	m_l64AutoTestAddrCounter = AUTO_TEST_START_NOD_ADDR;//地址累加器赋初始值1
	m_protocol_type = DLT645_2007;//2
	m_nodNumPerframe_Set = ADD_NODE_NUM_MAX;//设定的每帧节点数量200
	//增加删除节点结构体初始化
	stADelNodTest.del_node_num = DEL_SALVE_NODE_NUM_IN_ADT;//100
	i = ((ADD_SALVE_NODE_NUM_IN_ADT - DEL_SALVE_NODE_NUM_IN_ADT)>>1);//在中间删除
	stADelNodTest.before_del_pos = (BYTE)i;//50
	stADelNodTest.after_del_pos = i + DEL_SALVE_NODE_NUM_IN_ADT + 1;//151
	stADelNodTest.nodCounter    = AUTO_TEST_START_NOD_ADDR;//1
	while (hNextItem)
	{
		strName = pMainDlg->m_treeProject.GetItemText(hNextItem);
		if (pMainDlg->m_treeProject.GetCheck(hNextItem))
		{
			switch(atol(strName.Mid(0,2)))
			{
			   case 1://无删除  增加1024  读1024
				plog.saveLog_strAll(TIME,"开始测试："+strName,2);
				for (;stADelNodTest.nodCounter - 1 < MAX_NOD_NUM;)
				{
					plog.saveLog_strAll(TIME,"开始：增加节点",1);
					str.Format("从%d个节点基础上，添加节点\r\n",stADelNodTest.nodCounter -1);
					pMainDlg->m_flashData.ReplaceSel(str);
					///////////////////////////增加节点////////////////////////////////
					ack=addNode(atol(strName.Mid(0,2)));//增加一个节点，addNode函数中 会根据数据量多包发送，每包发送的时候会有超时等待，所以这里无需等待
					plog.saveLog_testresultAll(TIME,"结果" ,ack,0);
					plog.saveLog_strAll(NOTIME,"",1);
				}
				if(m_l64AutoTestAddrCounter >= MAX_NOD_NUM)
				{
					plog.saveLog_strAll(TIME,"开始：读取节点数量",1);
					str.Format("读取%d个节点的--节点信息\r\n",stADelNodTest.nodCounter -1);
					pMainDlg->m_flashData.ReplaceSel(str);
					plog.saveLog_str(DATA_FILE,TIME,str);
					j = 0;
					ack =gSimJzq.HostSendRcv376_2NoBuf(0x10,F1,sQGDW376_2HostFrame,DstDecodeDataFrame,1);//读取从节点数量
					INT16U cnt= Buf2ToHex16(&DstDecodeDataFrame.s_RcvDataBuf[0]);
					plog.saveLog_testresultAll(TIME,"结果" ,ack,0);
					plog.saveLog_strAll(NOTIME,"",1);
			
					//////////////////////////读取节点信息并解析判断//////////////////////////////////////////
					pMainDlg->stRecvNodInfor.wSlaveNodRdSN = READ_SN_BEGIN;//每次都是从序号0开始读取从节点信息
					pMainDlg->stRecvNodInfor.wSumCurrentNodNum = 0;//当前节点数累加值复位
					pMainDlg->stRecvNodInfor.wAddrPos = 0;//每次重新读取信息的时候，节点地址写入的缓存区指针需要复位
					pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum = pMainDlg->stRecvNodInfor.wTotlaNodNum;//全部都需要读

					j = 0;
					plog.saveLog_strAll(TIME,"开始：读节点信息",1);
					for (; (pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum); )
					{
						if(pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum <= MAX_READ_NUM) //计算此次需要读取的节点数量
						{
							pMainDlg->stRecvNodInfor.byRdNodNumNow =(BYTE) pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum;
						}
						else
						{
							pMainDlg->stRecvNodInfor.byRdNodNumNow = MAX_READ_NUM;				
						}
						//sendData2Module(AFN10,F2,LAUNCH);//读取节点信息 每次最大读255	
						WORD wdata;//起始序号
						BYTE bydata;//读取数量
						INT8U buf10f2[3];
						wdata = pMainDlg->stRecvNodInfor.wSlaveNodRdSN;
						bydata = pMainDlg->stRecvNodInfor.byRdNodNumNow;
						buf10f2[0] = (BYTE)wdata;
						buf10f2[1] = (BYTE)(wdata>>8);
						buf10f2[2]= bydata;

						ack =gSimJzq.HostSendRcv376_2Buf(0x10,F2,buf10f2,3,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
						if (ack == DACK_SUCESS)
						{
							j = 0;
							pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum -= pMainDlg->stRecvNodInfor.byRdNodNumNow;//更新剩余需要读取的节点数
							pMainDlg->stRecvNodInfor.wSlaveNodRdSN += pMainDlg->stRecvNodInfor.byRdNodNumNow;//更新读取节点序号
						}
					}
					plog.saveLog_testresultAll(TIME,"结果" ,ack,0);
					plog.saveLog_strAll(NOTIME,"",1);
					//pMainDlg->m_flashData.ReplaceSel(_T("所有节点信息比对结束\r\n"));//编辑框显示
					//数据全部读取完毕之后进行的判断

				}

				///////////////////////////读取FLASH数据并进行比对/////////////////////////////////////////////////

				plog.saveLog_strAll(TIME,"开始：读flash上节点信息",1);
				if(atol(strName.Mid(0,2))== 1)
				{
					k = m_l64AutoTestAddrCounter - 1;//实际写入了多少个节点（地址和写入数据量是对应的)
					wNumOf1K_flash = (WORD)((k % NOD_NUM_OF_1KFLASH == 0)?(k >> 6):((k>>6)+1));
				}else
				{
					wNumOf1K_flash = 24;//固定读取24K数据，因为单片机存储机制可能造成数据在FLASH里面不是顺序的//(WORD)((k % NOD_NUM_OF_1KFLASH == 0)?(k >> 6):((k>>6)+1));
				}
				pMainDlg->m_u32ReadFlashAddr = FLASH_START_ADDR;
				pMainDlg->stFlashInfor.wAddrPos = 0;
				k = 0;
				for (j=0; j<wNumOf1K_flash;)
				{						
					DWORD nsize;
					WORD wReadSize;
					UINT8 buf0f100[6];
					int num_0f100=0;
					//m_u32ReadFlashAddr = 0x12345678;
					memcpy(&buf0f100[num_0f100],&pMainDlg->m_u32ReadFlashAddr,4);
					for (i=0;i<4;i++)
					{
						num_0f100+=1;
					}
					wReadSize = FLASH_READ_LENGTH;
					memcpy(&buf0f100[num_0f100],&wReadSize,2);
					for (i=0;i<2;i++)
					{
						num_0f100+=1;;
					}
					//写入解析日志
					str.Format(_T("起始地址：0x%.8X,读取长度:%d"),pMainDlg->m_u32ReadFlashAddr,wReadSize);
					plog.saveLog_str(DATA_FILE,TIME,str);
					ack =gSimJzq.HostSendRcv376_2Buf(0xF0,F100,buf0f100,num_0f100,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
					if (ack==DACK_SUCESS)
					{
						pMainDlg->m_u32ReadFlashAddr += FLASH_READ_LENGTH;//每次地址偏移1024字节
						plog.saveLog_str(DATA_FILE,TIME,"读取成功地址偏移1024字节");
						k = 0;
					}
					else
					{
						k++;
							if((k < RESEND_CHANCE_TIMES))	
							{
								//pMainDlg->m_flashData.ReplaceSel(_T("！！！读取FLASH失败\r\n"));//编辑框显示
								plog.saveLog_str(DATA_FILE,TIME,"！！！读取FLASH失败");
								continue;//j++ 需要放到最后，否则这里循环过来会造成J++
							} 
					}
					j++;
				}
				plog.saveLog_strAll(TIME,"结束：读flash上节点信息",1);
				//数据全部读取完毕之后进行的判断
				//if (!pMainDlg->stFlashInfor.wAddrPos)
				//{
				//	pMainDlg->m_flashData.ReplaceSel(_T("检测到：添加节点后，FLASH节点的写入指针为0"));//编辑框显示
				//	//AfxMessageBox("检测到：添加节点后，FLASH节点的写入指针为0");
				//
				//}else if (pMainDlg->stFlashInfor.wAddrPos + 1 != stADelNodTest.nodCounter)
				//{
				//	pMainDlg->m_flashData.ReplaceSel(_T("检测到：FLASH测试:模块返回的FLASH上的有效从节点数量的总和实际发出的节点总数不一致"));//编辑框显示
				//	//AfxMessageBox("检测到：FLASH测试:模块返回的FLASH上的有效从节点数量的总和实际发出的节点总数不一致");
				//}else if (atol(strName.Mid(0,2))== 1)
				//{
				//	if (pMainDlg->stFlashInfor.U64FlashAddrs[pMainDlg->stFlashInfor.wAddrPos-1] !=  stADelNodTest.nodCounter - 1)
				//	{
				//		pMainDlg->m_flashData.ReplaceSel(_T("检测到：最后一个FLASH节点的地址不是写入的最后一个地址"));
				//		//AfxMessageBox("检测到：最后一个FLASH节点的地址不是写入的最后一个地址");
				//	}
				//}
					///////////////////////////////测试流程控制/////////////////////////////////////

					str = _T("添加-");
					str += _T("-读取 从节点测试完成，\r\n-----------------------请进行下一步------------------------\r\n请给模块!!!重新上电!!//等待模块正常运行后，进行复位后再进行后面测试流程");
				//plog.saveLog_str(DATA_FILE,TIME,"结束测试："+strName);
				plog.saveLog_testresultAll(TIME,strName+"结果：",ack,2);
			break;

			//if (m_hThreadsend==NULL)//用于中途停止测试
			//{
			//	break;
			//}
			case 2://有删除  增200 删100  直到有1024个节点 并比对flash地址存储
				plog.saveLog_strAll(TIME,"开始测试："+strName,2);
				for (;stADelNodTest.nodCounter - 1 < MAX_NOD_NUM;)
				{
					if(m_hThreadsend==NULL)//用于中途停止测试
					{
						break;
					}
					plog.saveLog_strAll(TIME,"开始：增加节点",1);
					str.Format("在%d个节点基础上，添加节点，首地址为%d\r\n",stADelNodTest.nodCounter - 1,m_l64AutoTestAddrCounter);
					plog.saveLog_str(DATA_FILE,TIME,str);
					///////////////////////////增加节点////////////////////////////////
					ack=addNode(atol(strName.Mid(0,2)));//增加一个节点，addNode函数中 会根据数据量多包发送，每包发送的时候会有超时等待，所以这里无需等待
					if (ack== DACK_SUCESS)
					{
						plog.saveLog_strAll(TIME,"结果：成功",0);
						plog.saveLog_strAll(NOTIME,"",1);
					}
					else
					{
						
						plog.saveLog_strAll(TIME,"结果：失败。测试停止检查原因！",0);
						plog.saveLog_strAll(TIME,"",1);
						m_hThreadsend==NULL;
						break;
					}

						plog.saveLog_strAll(TIME,"开始：删除节点",1);
						if (stADelNodTest.nodCounter < MAX_NOD_NUM)//最后124个节点不再删除
						{
							if(m_hThreadsend==NULL)//用于中途停止测试
							{
								break;
							}
							//sendData2Module(AFN11,F2,LAUNCH);//删除节点数
							//IsErrAppear();
							BYTE j;
							int num_11f2=0;
							UINT8 buf11f2[4096];
							CString str1,str2,str3;
							buf11f2[num_11f2++] = stADelNodTest.del_node_num;
							//写入解析日志
							Sleep(1000);
							LONG64 addr64,u64Data;
							addr64 = ((m_l64AutoTestAddrCounter - 1)/ADD_SALVE_NODE_NUM_IN_ADT -1)*ADD_SALVE_NODE_NUM_IN_ADT + stADelNodTest.before_del_pos+1;
							str.Format(_T("本帧删除从节点数量：%d，删除的节点初始地址为：%d--地址列表为："),stADelNodTest.del_node_num,addr64);
							for (i = 0; i < stADelNodTest.del_node_num; i++)
							{					
								//写入解析日志
								str1.Format(_T("%I64d,"),addr64);
								str+= str1;

								u64Data = addr64;
								for (j=0; j<6; j++)//set 6 byte addr
								{
									//低字节数据放在前面 
									buf11f2[num_11f2++] = (((u64Data%100)/10)<<4)+(u64Data%10);
									u64Data /= 100;
								}
								addr64++;//地址累加					
							}
							stADelNodTest.nodCounter -= stADelNodTest.del_node_num;	
							plog.saveLog_str(DATA_FILE,TIME,str);
							plog.saveLog_str(DATA_FILE,NOTIME,"");
							ack =gSimJzq.HostSendRcv376_2Buf(0x11,F2,buf11f2,num_11f2,sQGDW376_2HostFrame,DstDecodeDataFrame,1);//删除从节点信息
							plog.saveLog_testresultAll(TIME,"结果" ,ack,0);
							plog.saveLog_strAll(NOTIME,"",1);
							//else
							//{
							//	plog.saveLog_strAll(TIME,"删除步骤失败,停止测试检查原因！",1);
							//	m_hThreadsend==NULL;
							//	break;
							//}//!!!!为什么确认帧返回失败
						}else 
						{
							plog.saveLog_strAll(TIME,"最后124个节点不进行删除工作",0);
							plog.saveLog_strAll(NOTIME,"",1);
						}
		//}//-----

					plog.saveLog_strAll(TIME,"开始读取节点数量操作",1);
					j = 0;
					ack =gSimJzq.HostSendRcv376_2NoBuf(0x10,F1,sQGDW376_2HostFrame,DstDecodeDataFrame,1);//读取从节点数量
					INT16U cnt= Buf2ToHex16(&DstDecodeDataFrame.s_RcvDataBuf[0]);
					if(ack == DACK_SUCESS)
					{	
						str.Format("数量：%u", cnt);
						pMainDlg->stRecvNodInfor.wTotlaNodNum = cnt;
						plog.saveLog_strAll(TIME,"结果：成功。节点数为"+str,0);
						plog.saveLog_strAll(NOTIME,"",1);
					}

					//////////////////////////读取节点信息并解析判断//////////////////////////////////////////
					pMainDlg->stRecvNodInfor.wSlaveNodRdSN = READ_SN_BEGIN;//每次都是从序号0开始读取从节点信息
					pMainDlg->stRecvNodInfor.wSumCurrentNodNum = 0;//当前节点数累加值复位
					pMainDlg->stRecvNodInfor.wAddrPos = 0;//每次重新读取信息的时候，节点地址写入的缓存区指针需要复位
					pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum = pMainDlg->stRecvNodInfor.wTotlaNodNum;//全部都需要读

					j = 0;
					plog.saveLog_strAll(TIME,"开始：读节点信息",1);
					for (; (pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum); )
					{
						if(m_hThreadsend==NULL)//用于中途停止测试
						{
							break;
						}
						if(pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum <= MAX_READ_NUM) //计算此次需要读取的节点数量
						{
							pMainDlg->stRecvNodInfor.byRdNodNumNow =(BYTE) pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum;
						}
						else
						{
							pMainDlg->stRecvNodInfor.byRdNodNumNow = MAX_READ_NUM;				
						}
						//sendData2Module(AFN10,F2,LAUNCH);//读取节点信息 每次最大读255	
						WORD wdata;//起始序号
						BYTE bydata;//读取数量
						INT8U buf10f2[3];
						wdata = pMainDlg->stRecvNodInfor.wSlaveNodRdSN;
						bydata = pMainDlg->stRecvNodInfor.byRdNodNumNow;
						buf10f2[0] = (BYTE)wdata;
						buf10f2[1] = (BYTE)(wdata>>8);
						buf10f2[2]= bydata;
						ack =gSimJzq.HostSendRcv376_2Buf(0x10,F2,buf10f2,3,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
						if (ack == DACK_SUCESS)
						{
							j = 0;
							INT16U cnt= Buf2ToHex16(&DstDecodeDataFrame.s_RcvDataBuf[0]);
							//plog.saveLog_HexBuf(DATA_FILE,TIME,DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen);
							//Sleep(20000);
							pMainDlg->stRecvNodInfor.wNeedReadNodTotalNum -= pMainDlg->stRecvNodInfor.byRdNodNumNow;//更新剩余需要读取的节点数
							pMainDlg->stRecvNodInfor.wSlaveNodRdSN += pMainDlg->stRecvNodInfor.byRdNodNumNow;//更新读取节点序号
						}
					}
					plog.saveLog_testresultAll(TIME,"结果" ,ack,0);
					plog.saveLog_strAll(NOTIME,"",1);


				///////////////////////////读取FLASH数据并进行比对/////////////////////////////////////////////////

				plog.saveLog_strAll(TIME,"开始:读FLASH上的所有节点的节点信息",1);
				k = m_l64AutoTestAddrCounter - 1;//实际写入了多少个节点（地址和写入数据量是对应的)
				wNumOf1K_flash = (WORD)((k % NOD_NUM_OF_1KFLASH == 0)?(k >> 6):((k>>6)+1));
				//wNumOf1K_flash = 24;//固定读取24K数据，因为单片机存储机制可能造成数据在FLASH里面不是顺序的//(WORD)((k % NOD_NUM_OF_1KFLASH == 0)?(k >> 6):((k>>6)+1));
				pMainDlg->m_u32ReadFlashAddr = FLASH_START_ADDR;
				pMainDlg->stFlashInfor.wAddrPos = 0;
				k = 0;
				int list=0;
				
				for (j=0; j<wNumOf1K_flash;)
				{	
					int SIX=6;
					if(m_hThreadsend==NULL)//用于中途停止测试
					{
						break;
					}
					DWORD nsize;
					WORD wReadSize;
					INT8U buf0f100[6];
					int num_0f100=0;
					memcpy(&buf0f100[num_0f100],&pMainDlg->m_u32ReadFlashAddr,4);
					for (i=0;i<4;i++)
					{
						num_0f100+=1;
					}
					wReadSize = FLASH_READ_LENGTH;
					memcpy(&buf0f100[num_0f100],&wReadSize,2);
					for (i=0;i<2;i++)
					{
						num_0f100+=1;;
					}
					//写入解析日志
					str.Format(_T("起始地址：0x%.8X,读取长度：%d,读取数量:64"),pMainDlg->m_u32ReadFlashAddr,wReadSize);
					plog.saveLog_str(DATA_FILE,TIME,str);
					ack =gSimJzq.HostSendRcv376_2Buf(0xF0,F100,buf0f100,num_0f100,sQGDW376_2HostFrame,DstDecodeDataFrame,1);
					if (ack==DACK_SUCESS)
					{
						for (int h=0;h<64;h++)
						{
							for(int p=0;p<6;p++)
							{
								FALSH_ACKNODELIST[list][p]=DstDecodeDataFrame.s_RcvDataBuf[p+SIX];
							}
							list++;
							SIX+=16;
						}
						pMainDlg->m_u32ReadFlashAddr += FLASH_READ_LENGTH;//每次地址偏移1024字节
						plog.saveLog_str(DATA_FILE,TIME,"读取64个成功，地址偏移1024字节");
						//plog.saveLog_HexBuf(DATA_FILE,TIME,DstDecodeDataFrame.s_RcvDataBuf,DstDecodeDataFrame.s_RcvDataLen);
						plog.saveLog_str(DATA_FILE,NOTIME,"");

						k = 0;
					}
					else
					{
						k++;
						if((k < RESEND_CHANCE_TIMES))	
						{
							//pMainDlg->m_flashData.ReplaceSel(_T("！！！读取FLASH失败\r\n"));//编辑框显示
							plog.saveLog_str(DATA_FILE,TIME,"读取FLASH失败,停止测试");
							m_hThreadsend==NULL;
							if(m_hThreadsend==NULL)//用于中途停止测试
							{
								break;
							}
							continue;//j++ 需要放到最后，否则这里循环过来会造成J++
						} 
					}
					j++;
				}

				plog.saveLog_strAll(TIME,"结果：成功！读取FLASH信息结束",0);
				if (NODE_RAMACKLIST[list][0]==FALSH_ACKNODELIST[list][0])
				{
					plog.saveLog_strAll(TIME,"地址比对成功",0);
					plog.saveLog_strAll(NOTIME,"",1);
				}
				else
				{
					plog.saveLog_strAll(TIME,"地址比对失败请检查原因！测试停止",0);
					plog.saveLog_strAll(NOTIME,"",1);
					break;
				}
           }

				///////////////////////////////结束/////////////////////////////////////

				str = _T("添加--删除");
				str += _T("-读取 从节点测试完成，\r\n-----------------------请进行下一步------------------------\r\n");			
				plog.saveLog_testresultAll(TIME,strName+"测试结束！结果：",ack,0);
				plog.saveLog_strAll(NOTIME,"",2);
				break;
			default:
				break;
				}
		}
		hNextItem = pMainDlg->m_treeProject.GetNextItem(hNextItem,TVGN_NEXTVISIBLE);	
	}

}

int L=0;

INT8U CTESTNODE::addNode(int tpe) 
{
	CImitateMeterDlg * pMainDlg = (CImitateMeterDlg *)theApp.m_pMainWnd;
	// TODO: Add your command handler code here
	BYTE total_nod_num = 0,i;//需要发送的总节点数
	UINT64 addr_counter_be4Send;//每次发送前的起始地址记录，防止接收串口数据错误的时候，重发用
	WORD NodNum;
	INT8U ack;
	//if (tpe==1)//autoTest == AUTO_TEST)
	//{
	//	m_add_nod_num = ADD_NODE_NUM_MAX;//每次最大增加的节点数
	//} 
	//else
	//{
	//	m_l64AutoTestAddrCounter = _ttoi64(m_start_nod_addr);//0
	//}
	m_add_nod_num = ADD_NODE_NUM_MAX;//每次最大增加的节点数
	i=0;

	//
	if (tpe==1)
	{
		if (m_l64AutoTestAddrCounter - 1 + m_add_nod_num <= MAX_NOD_NUM)total_nod_num = m_add_nod_num;
		else														    total_nod_num = (BYTE) (MAX_NOD_NUM - (m_l64AutoTestAddrCounter-1));
	} 
	else
	{
		if (stADelNodTest.nodCounter - 1 + m_add_nod_num <= MAX_NOD_NUM)total_nod_num = m_add_nod_num;
		else														    total_nod_num = (BYTE) (MAX_NOD_NUM - (stADelNodTest.nodCounter-1));

	}

	for (;total_nod_num>0;)
	{		
		if (total_nod_num >= m_nodNumPerframe_Set)
		{			
			gB_nodNumThisFrame = m_nodNumPerframe_Set;total_nod_num -= m_nodNumPerframe_Set;
		}else
		{
			gB_nodNumThisFrame = total_nod_num;
			total_nod_num  = 0;
		}
		addr_counter_be4Send = m_l64AutoTestAddrCounter;
		NodNum = stADelNodTest.nodCounter;
		BYTE j;
		CString str1,str2;
		UINT8 buf[4096];
     	//写入解析日志
		str1.Format(_T("本帧添加从节点数量:%d"),gB_nodNumThisFrame);
		int s=0;
		buf[s]=gB_nodNumThisFrame;
		s++;
		//写入解析日志
		str1+= _T("写入的地址为和协议类型：");
		LONG64 addr64;
		//添加从节点地址 
		for (i = 0; i < gB_nodNumThisFrame; i++)
		{
			addr64 = m_l64AutoTestAddrCounter;
			//写入解析日志
			str2.Format(_T("%I64d,"),m_l64AutoTestAddrCounter);
			str1+=str2;

			//写入解析日志
			str2.Format(_T("%d  "),m_protocol_type);
			str1+=str2;
			for (j=0; j<6; j++)//set 6 byte addr
			{
				//低字节数据放在前面 
				buf[s++] = (((addr64%100)/10)<<4)+(addr64%10);
				NODE_RAMACKLIST[L][j] = (((addr64%100)/10)<<4)+(addr64%10);
				//stFrame.CS += BufRecv[stFrame.L++];
				addr64 /= 100;
			}
			L++;
			buf[s++] = m_protocol_type;//协议类型
			//BufToBuf(&buf[1+n*7],addr64+m_protocol_type,7);
			m_l64AutoTestAddrCounter++;//地址累加
			stADelNodTest.nodCounter++;
			//stFrame.CS += BufRecv[stFrame.L++];
		}
		plog.saveLog_str(DATA_FILE,TIME,str1);
		plog.saveLog_str(DATA_FILE,NOTIME,"");

		ack = gSimJzq.HostSendRcv376_2Buf_NoAck(0x11,F1,buf,s);//添加节点

		if(ack == DACK_SUCESS)
		{
			return ack;
		}
		if(m_l64AutoTestAddrCounter > MAX_NOD_ADDR) break;//超出6字节BCD码的地址范围		
	}
	//	
	return ack;
}
