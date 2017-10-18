// TESTAFN14_S.cpp : implementation file
//

#include "stdafx.h"
#include "ImitateMeter.h"
#include "TESTAFN14_S.h"
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

// CTESTAFN14_S

IMPLEMENT_DYNAMIC(CTESTAFN14_S, CWnd)

CTESTAFN14_S::CTESTAFN14_S()
{

}

CTESTAFN14_S::~CTESTAFN14_S()
{
}


BEGIN_MESSAGE_MAP(CTESTAFN14_S, CWnd)
END_MESSAGE_MAP()
void CTESTAFN14_S::C3762_TEST(HTREEITEM hTree)
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
	if(allfailcnt == 0)
		plog.saveLog_testresult(DATA_FILE,TIME,"总结果： ",DACK_SUCESS,2);
	else
		plog.saveLog_testresult(DATA_FILE,TIME,"总结果： ",DACK_FAILURE,2);
}


// CTESTAFN14_S message handlers


