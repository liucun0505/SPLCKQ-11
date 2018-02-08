#include "StdAfx.h"
#include "LogFile.h"


#include "SPL_CKQ.h"
#include "MainFrm.h"
#include "Tools.h"
CLogFile::CLogFile(void)
{
}


CLogFile::~CLogFile(void)
{
}
char *ReservedStr = "备用";
char *AFNStrBuf[AFN_MAX_NUM]=
{
	"确认∕否认",
	"初始化",
	"数据转发",
	"查询数据",
	"链路接口检测",
	"控制命令",
	"主动上报",//0x06
	// 7    8       9		10		11	12		13		14
	"备用","备用","备用","备用","备用","备用","备用","备用","备用",

	"路由查询",
	"路由设置",
	"路由控制",
	"路由数据转发",
	"路由数据抄读",
	"文件传输",//0x15

	"内部调试",//最后一个字符串 对应AFNF0
};

char *AFN00FnStrBuf[]={"F1：确认","F2：否认"};
char *AFN01FnStrBuf[]={"F1：硬件初始化","F2：参数区初始化","F3：数据区初始化"};
char *AFN02FnStrBuf[]={"F1：数据转发"};
char *Apn03FnStrBuf[]={"F1：读主节点版本信息","F2：读取噪声值","F3：读取从节点侦听信息","F4：读取主节点地址","F5：主节点状态字和通信速率","F6：主节点干扰状态","F7：读取从节点监控最大超时时间","F8：查询无线通信参数","F9：通信延时相关广播通信时长","F10：读取本地通信模块运行模式信息","F11：本地通信模块索引信息"};
char *AFN04FnStrBuf[]={"F1：发送测试","F2：从节点名","本地模块F3：报文通信测试"};
char *Apn05FnStrBuf[]={"F1：设置主节点地址","F2：允许禁止从节点上报","F3：启动广播","F4：设置从节点监控最大超时时间","F5：设置无线通信参数"};
char *AFN06FnStrBuf[]={"F1：上报从节点信息","F2：上报抄读数据","F3：上报工况变动信息","F4：上报从节点信息及设备类型","F5：上报从节点事件"};
char *AFN10FnStrBuf[]={"F1：从节点数量","F2：从节点信息","F3：指定从节点的上一级中继路由信息","F4：路由运行状态","F5：未抄读成功的从节点信息","F6：主动注册的从节点信息","F21:节点拓扑信息","F100:查询网络规模","F101:查询从节点版本信息","F201:查询从节点状态"};
char *AFN11FnStrBuf[]={"F1：添加从节点","F2：删除从节点","F3：设置从节点固定中继路径","F4：设置工作模式","F5：激活从节点主动注册","F6：终止从节点主动注册"};
char *Apn12FnStrBuf[]={"F1：路由重启","F2：路由暂停","F3：路由恢复"};
char *AFN13FnStrBuf[]={"F1：监控从节点"};
char *AFNF0FnStrBuf[]={"F100:读取FLASH数据"};

CFile cfileData;//存储文件
CFile cfileParse;//


void CLogFile::dispSaveFixed1376FrameInfor(UINT8 apn,UINT8 fn,INT8U ctrl,INT8U *pRbuf,INT8 IO)
{
	CString str,str1;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	if (IO == OUTPUT)
	{
		str += _T("->>>>-发出-解析数据:");	
	} 
	else
	{
		str += _T("-<<<<-接收-解析数据:");	
	}
	str1.Format(_T("控制域：%.2x,信息域%.2x %.2x %.2x %.2x %.2x %.2x"),ctrl,pRbuf[0],pRbuf[1],pRbuf[2],pRbuf[3],pRbuf[4],pRbuf[5]);
	str += str1 + getAFNFnStr(apn,fn);
	saveLog_str(DATA_FILE,NOTIME,str);
}

#if 0
void CLogFile::saveLog_HexBuf(INT8U logfile,INT8U IO,INT8U *pbuf,WORD length)//打印发送帧的16进制字符串
{
	char szANSIString[5000];  
	CString str,strfile;
	CString strA;
	SYSTEMTIME st;
	FILE * file;
	char * pFileName = new char[256];
	GetLocalTime(&st);
	str = _T(".\\日志\\DataFile-");
	strfile.Format(_T("%.4d年%.2d月%.2d日"),st.wYear,st.wMonth,st.wDay);
	strA = str + strfile + _T(".txt");
	str.Format(_T("%.2d:%.2d:%.2d.%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	str += ((IO == OUTPUT)?_T("->>>>-发送-"):_T("-<<<<-接收-")) + m_tools._buf16tostr16(pbuf,length,true) + _T("\r\n")+ _T("\r\n");
	

	USES_CONVERSION;
	pFileName = T2A(strA.GetBuffer(0));
	
	m_tools.AutoMakedir(pFileName);
	
	file=fopen(pFileName,"r");
	if  ( file == NULL )
	{
		file=fopen(pFileName,"a+");
		if (file != NULL)
		{
			fwrite(szANSIString, wcslen(str), 1, file);
			fclose(file);
		}
	}
	else
	{
		fclose(file); 
		file=fopen(pFileName,"a+");
		if (file != NULL)
		{
			fwrite(szANSIString, wcslen(str), 1, file);
			fclose(file);
		}
	}
	delete[] pFileName;
}
#else

void CLogFile::saveLog_HexBuf(INT8U logfile, INT8U IO, INT8U *pbuf, WORD length)//打印发送帧的16进制字符串
{
	char szANSIString[5000];
	CString str, strfile;
	CStringA strA;
	SYSTEMTIME st;
	FILE * file;
	GetLocalTime(&st);
	str = _T(".\\日志\\DataFile-");
	strfile.Format(_T("%.4d年%.2d月%.2d日"), st.wYear, st.wMonth, st.wDay);
	strA = str + strfile + _T(".txt");
	str.Format(_T("%.2d:%.2d:%.2d.%.3d"), st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	str += ((IO == OUTPUT) ? _T("->>>>-发送-") : _T("-<<<<-接收-")) + m_tools._buf16tostr16(pbuf, length, true) + _T("\r\n") + _T("\r\n");

	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, str, -1, szANSIString, sizeof(szANSIString), NULL, NULL);
	file = fopen(strA, "r");
	if (file == NULL)
	{
		file = fopen(strA, "a+");
		if (file != NULL)
		{
			fwrite(szANSIString, wcslen(str), 1, file);
			fclose(file);
		}
	}
	else
	{
		fclose(file);
		file = fopen(strA, "a+");
		if (file != NULL)
		{
			fwrite(szANSIString, wcslen(str), 1, file);
			fclose(file);
		}
	}
}

#endif

//void CLogFile::saveLog_HexBuf(INT8U logfile,INT8U IO,INT8U *pbuf,WORD length)//打印发送帧的16进制字符串
//{
//	// TODO: Add your command handler code here	
//	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
//	CString str,strTemp;
//	CTools m_tool;
//	SYSTEMTIME st;
//	GetLocalTime(&st);
//	str.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
//	str += ((IO == OUTPUT)?_T("->>>>-发送-"):_T("-<<<<-接收-"));
//
//
//	if (cfileData.m_hFile != CFile::hFileNull)
//	{
//		cfileData.Write(str,str.GetLength());
//	}			
//	//pMainDlg->m_flashData.ReplaceSel(str);//编辑框显示		
//	str = m_tool._buf16tostr16(pbuf,length,true);
//	str += _T("\r\n");
//	if (logfile == DATA_FILE)
//	{
//		if (cfileData.m_hFile != CFile::hFileNull)
//		{
//			cfileData.Write(str.GetString(),str.GetLength());
//		} 
//		//pMainDlg->m_flashData.ReplaceSel(str);//编辑框显示
//	}
//	else if (logfile == PARS_FILE)
//	{
//		if  (cfileParse.m_hFile != CFile::hFileNull)
//		{
//			cfileParse.Write(str.GetString(),str.GetLength());
//		}
//		//pMainDlg->m_editKeyMsg.ReplaceSel(str);//编辑框显示
//	}
//
//	//if(pMainDlg->m_flashData.GetWindowTextLength() > 20480)//清空界面
//	//{
//	//	pMainDlg->m_flashData.SetSel(0,-1);
//	//	pMainDlg->m_flashData.Clear();
//	//}
//	//if(pMainDlg->m_editKeyMsg.GetWindowTextLength() > 20480)//清空界面
//	//{
//	//	pMainDlg->m_editKeyMsg.SetSel(0,-1);
//	//	pMainDlg->m_editKeyMsg.Clear();
//	//}
//	//}
//
//}

void CLogFile::saveLog_str(INT8U logfile,INT8U time,CString str,INT8U LineType)
{
	// TODO: Add your command handler code here	
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	CString line;
	if (LineType==0)
	{
		line="";
	}
	else if (LineType==1)
	{
		line="----------------------------------------\r\n";
	}
	else if (LineType==2)
	{
		line="======================================================================\r\n";
	}

	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += ("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	if (logfile == DATA_FILE)
	{
		strTemp+=str;
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(line,line.GetLength());
			cfileData.Write(strTemp,strTemp.GetLength());
			//cfileData.Write(line,line.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel("\r\n"+line+strTemp+line);//编辑框显示		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+=str;
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(line,line.GetLength());
			cfileParse.Write(strTemp,strTemp.GetLength());
			//cfileParse.Write(line,line.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_editKeyMsg.ReplaceSel("\r\n"+line+strTemp);//编辑框显示		
	}

	//if(pMainDlg->m_flashData.GetWindowTextLength() > 40960)//清空界面
	//{
	//	pMainDlg->m_flashData.Clear();
	//}
	//if(pMainDlg->m_editKeyMsg.GetWindowTextLength() > 40960)//清空界面
	//{
	//	pMainDlg->m_editKeyMsg.Clear();
	//}


}
void CLogFile::saveLog_err(INT8U logfile,INT8U time,CString STR,INT8U ack,INT8U classType)
{
	// TODO: Add your command handler code here	
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str.Format(_T("%02x"),ack);
	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+="----";
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += ("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=STR+_T("错误码：")+str;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//编辑框显示		

	}
	else if (logfile == PARS_FILE)//DataIfo
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);//编辑框显示		
	}

}
void CLogFile::saveInformation_send(sPartQGDW376_2CreatFrame &sQGDW376_2HostFrame)//打发送印帧的详细信息
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	UINT8 a_Fn;//=(UINT8)sQGDW376_2HostFrame.s_head.s_FN;
	INT8U pRbuf[6]={0,0,0,0,0,0};//存信息域
	INT8U S;
	ST_Fn pstFn;
	S=(UINT8)(sQGDW376_2HostFrame.s_head.s_FN);
	(&pstFn)->DT1=S;
	(&pstFn)->DT2=sQGDW376_2HostFrame.s_head.s_FN>>8;
	a_Fn=pMainDlg->getFn(pstFn);//取Fn字符串
	for (int i=0;i<5;i++)
	{
		pRbuf[i]=sQGDW376_2HostFrame.s_head.u_msg.s_msgbuf[i];
	}
	pRbuf[5]=sQGDW376_2HostFrame.s_head.s_Msg_Seq;
	dispSaveFixed1376FrameInfor(sQGDW376_2HostFrame.s_head.s_AFN,a_Fn,sQGDW376_2HostFrame.s_head.u_con.s_conByte,pRbuf,OUTPUT);
}

void CLogFile::saveInformation_rev(TH_OUT sPartQGDW376_2DeCodeFrame &DstDecodeDataFrame)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	UINT8 a_Fn;//=(UINT8)sQGDW376_2HostFrame.s_head.s_FN;
	INT8U pRbuf[6]={0,0,0,0,0,0};
	INT8U S;
	ST_Fn pstFn;
	S=(UINT8)(DstDecodeDataFrame.s_head.s_FN);
	(&pstFn)->DT1=S;
	(&pstFn)->DT2=DstDecodeDataFrame.s_head.s_FN>>8;
	a_Fn=pMainDlg->getFn(pstFn);
	for (int i=0;i<5;i++)
	{
		pRbuf[i]=DstDecodeDataFrame.s_head.u_msg.s_msgbuf[i];
	}
	pRbuf[5]=DstDecodeDataFrame.s_head.s_Msg_Seq;
	dispSaveFixed1376FrameInfor(DstDecodeDataFrame.s_head.s_AFN,a_Fn,DstDecodeDataFrame.s_head.u_con.s_conByte,pRbuf,INPUT_DATA);

}

void CLogFile::saveInformation_645(Stu_Dtl2007 stDtl2007)///打印645帧结构信息
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str,str1;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	//INT8U  s_Con;//控制吗
	str1.Format(_T("控制码:%.2x,DI:%.2x %.2x %.2x %.2x,表地址:%.2x %.2x %.2x %.2x %.2x %.2x"),stDtl2007.s_Con,stDtl2007.s_Di,stDtl2007.s_Di>>8,stDtl2007.s_Di>>16,stDtl2007.s_Di>>24,stDtl2007.s_AmtBuf[0],stDtl2007.s_AmtBuf[1],stDtl2007.s_AmtBuf[2],stDtl2007.s_AmtBuf[3],stDtl2007.s_AmtBuf[4],stDtl2007.s_AmtBuf[5]);
	str += str1+_T("\r\n");
	saveLog_str(DATA_FILE,TIME,str);
}


CString CLogFile::getAFNFnStr(unsigned char AFN, unsigned char fn)
{
	CString str,FnStr;
	char *pbuf;
	if(AFN == AFNF0)		pbuf = AFNStrBuf[AFN_MAX_NUM-1];
	else if(AFN <= 0x15)	pbuf = AFNStrBuf[AFN];
	else					pbuf = ReservedStr;

	str.Format(_T("AFN=%.2XH:%s,"),AFN,pbuf);
	if (AFN == AFN00)
	{
		if (fn <= F2)FnStr.Format(_T("%s,"),AFN00FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr); 
	}else if (AFN == AFN01)
	{
		if (fn <= F3)FnStr.Format(_T("%s,"),AFN01FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr);
	}else if (AFN == AFN02)
	{
		if (fn <= F1)FnStr.Format(_T("%s "),AFN02FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s "),ReservedStr);
	}else if (AFN == AFN03)
	{
		if (fn <= F11)FnStr.Format(_T("%s,"),Apn03FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr);
	}else if (AFN == AFN04)
	{
		if (fn <= F3)FnStr.Format(_T("%s,"),AFN04FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr);
	}else if (AFN == AFN05)
	{
		if (fn <= F6)FnStr.Format(_T("%s,"),Apn05FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr);
	}else if (AFN == AFN06)
	{
		if (fn <= F5)FnStr.Format(_T("%s,"),AFN06FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr);
	}else if (AFN == AFN10)
	{
		if (fn==21)
		{
			fn=7;
		}
		if (fn==100)
		{
			fn=8;
		}
		if (fn==101)
		{
			fn=9;
		}
		if (fn==102)
		{
			fn=10;
		}
		if (fn <= F201)FnStr.Format(_T("%s,"),AFN10FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s,"),ReservedStr);
	}else if (AFN == AFN11)
	{
		if (fn <= F6)FnStr.Format(_T("%s "),AFN11FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s "),ReservedStr);
	}else if (AFN == AFN13)
	{
		if (fn <= F1)FnStr.Format(_T("%s "),AFN13FnStrBuf[fn-1]); 
		else		 FnStr.Format(_T("%s "),ReservedStr);
	}
	else if (AFN == AFNF0)
	{
		if (fn <= F100)	FnStr.Format(_T("%s "),AFNF0FnStrBuf[0]); 
		else			FnStr.Format(_T("%s "),ReservedStr);
	}else			 FnStr.Format(_T("%s "),ReservedStr);
	
	return str+FnStr;
	//return "";
}

void CLogFile::saveLog_testresult(INT8U logfile,INT8U time,CString str,INT8U ack,INT8U LineType)
{

  if(ack == DACK_SUCESS)
   {
	    saveLog_str(logfile,TIME,str+_T("成功"),LineType);
   }
   else
   {
	   saveLog_err(logfile,TIME,str,ack);
   }
}
void CLogFile::saveLog_testresult_AfnFn(INT8U Afn,INT16U Fn,INT8U logfile,INT8U time,CString str,INT8U ack,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	 CString tmpstr;
	 ST_Fn pstFn;
	 UINT8 a_Fn;
	 (&pstFn)->DT1=Fn;
	 (&pstFn)->DT2=Fn>>8;
	 a_Fn=pMainDlg->getFn(pstFn);//取Fn字符串
	 tmpstr += getAFNFnStr(Afn,a_Fn);
	 tmpstr += str;
	 saveLog_testresult(logfile,time,tmpstr,ack,classType);
}

void CLogFile::saveLog_StaCnt(INT16U  sucesscnt,INT16U failcnt,INT8U logfile,INT8U time,CString str,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str1.Format(_T("：成功次数_%u,失败次数_%u,"),sucesscnt,failcnt);
	str1=str+str1;
	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=str1;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//编辑框显示		

	}
	else if (logfile == PARS_FILE)//DataIfo
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);//编辑框显示		
	}
}

void CLogFile::saveLog_StaBuf8(INT8U  *vSrcBuf,INT16U Cnt,INT8U logfile,INT8U time,CString str,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	INT16U suc_cnt = 0;
	for (INT16U i=0;i<Cnt;i++)
	{
		str1.Format(_T("%d,"),vSrcBuf[i]);
		str+=str1;
		if(vSrcBuf[i] == 1)
		{
			suc_cnt++;
		}
	}
	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}	
	strTemp +=str;
	if (logfile == DATA_FILE)
	{
		str = "";
		strTemp+= _T("\r\n");
		strTemp +=_T("总数：");
		str1.Format(_T("%d"),Cnt);
		strTemp +=str1;
		strTemp +=_T(" 成功数：");
		str1.Format(_T("%d"),suc_cnt);
		strTemp +=str1;
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//编辑框显示		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);//编辑框显示		
	}
}
void CLogFile::saveLog_StaBuf16(INT16U  *vSrcBuf,INT16U Cnt,INT8U logfile,INT8U time,CString str,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	for (INT16U i=0;i<Cnt;i++)
	{
		str1.Format(_T("%u,"),vSrcBuf[i]);
		str+=str1;
	}
	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=str;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//编辑框显示		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);//编辑框显示		
	}
}
void CLogFile::saveLog_StaBuf32(INT32U  *vSrcBuf,INT16U Cnt,INT8U logfile,INT8U time,CString str,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	for (INT16U i=0;i<Cnt;i++)
	{
		str1.Format(_T("%u,"),vSrcBuf[i]);
		str+=str1;
	}
	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=str;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//编辑框显示		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);//编辑框显示		
	}
}
void CLogFile::saveLog_testresultALL_AfnFn(INT8U Afn,INT16U Fn,INT8U time,CString str,INT8U ack,INT8U classType)
{
	saveLog_testresult_AfnFn(Afn,Fn,DATA_FILE,time,str,ack,classType);
	saveLog_testresult_AfnFn(Afn,Fn,PARS_FILE,time,str,ack,classType);
}
void CLogFile::saveLog_testresultAll(INT8U time,CString str,INT8U ack,INT8U classType)
{
	saveLog_testresult(DATA_FILE,time,str,ack,classType);
	saveLog_testresult(PARS_FILE,time,str,ack,classType);
}
void CLogFile::saveLog_strAll(INT8U time,CString str,INT8U LineType)
{
	saveLog_str(DATA_FILE,time,str,LineType);
	saveLog_str(PARS_FILE,time,str,LineType);
}

void CLogFile::saveLog_BingF(INT8U logfile,INT8U time,CString str,sBinFa376_2_HostMsg BeifenMSg,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1,str2,str3,str4,str_s;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str1.Format(_T("s_Seq:%d,"),BeifenMSg.s_Seq);
	for (INT8U i=0;i<16;i++)
	{
		str_s.Format(_T("ackFg:%d,"),BeifenMSg.ackFg[i]);
		str2+=str_s;
	}
	str3.Format(_T("di645cnt:%d,"),BeifenMSg.di645cnt);
	for (INT8U i=0;i<16;i++)
	{
		str_s.Format(_T("di645Buf:%u,"),BeifenMSg.di645Buf[i]);
		str4+=str_s;
	}
	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=str+str1+str2+str3+str4;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//编辑框显示		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);
	}

}

void CLogFile::saveLog_NoAckMsg(INT8U logfile,INT8U time,CString str,sNoAckDiMsg  ackMsg,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1,str2,str3,str_s;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str1.Format(_T("s_Di:%u,"),ackMsg.s_Di);
	for (INT8U i=0;i<4;i++)
	{
		str_s.Format(_T("s_Time:%u,"),ackMsg.s_Time[i]);
		str2+=str_s;
	}
	str3.Format(_T("s_RcvCnt:%d,"),ackMsg.s_RcvCnt);

	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=str+str1+str2+str3;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//编辑框显示		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);
	}


}
void CLogFile::saveLog_ClkSta(sAckTimeSta *timeclk376,INT16U Cnt,INT8U logfile,INT8U time,CString str,INT8U classType)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	WORD length;
	CString strTemp,str1,str2,str3,str4;
	CTools m_tool;
	SYSTEMTIME st;
	GetLocalTime(&st);
	str1.Format(_T("SEQ:%d,"),timeclk376->s_Seq);
	str2.Format(_T("是否返回:%d,"),timeclk376->ackFg);
	str3.Format(_T("数据格式:%d,"),timeclk376->dataack);
	str4.Format(_T("间隔时间:%u,"),timeclk376->timeclk);

	for(INT8U m = 0; m<classType; m++)
	{
		strTemp+=_T("----");
	}
	if (time== TIME)
	{
		strTemp.Format(_T("%.2d:%.2d:%.2d:%.3d"),st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
		strTemp += _T("->>>>");
	}
	else if (time== NOTIME)
	{
	}
	strTemp +=str+str1+str2+str3+str4;
	if (logfile == DATA_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileData.m_hFile != CFile::hFileNull)
		{
			cfileData.Write(strTemp,strTemp.GetLength());
		}			
		//if(displayComData)
		//pMainDlg->m_flashData.ReplaceSel(strTemp);//编辑框显示		

	}
	else if (logfile == PARS_FILE)
	{
		strTemp+= _T("\r\n");
		if (cfileParse.m_hFile != CFile::hFileNull)
		{
			cfileParse.Write(strTemp,strTemp.GetLength());
		}
		//pMainDlg->m_editKeyMsg.ReplaceSel(strTemp);
	}

}

INT8U ChangeAmtBps(INT32U bps)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	DCB dcb;
	CString strBaud;
	//GetCommState(pMainDlg->m_hCom645,&dcb);
	//dcb.BaudRate=bps;  //传输速率
	//if(SetCommState(pMainDlg->m_hCom645,&dcb))
	//{
	//	return 1;
	//}
	return 0;
}
INT32U  QueAmtBps(void)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	DCB dcb;
	//GetCommState(pMainDlg->m_hCom645,&dcb);
	return dcb.BaudRate;  //传输速率
}

// 弹出消息窗口自动关闭，需要指出的是，Windows 2000的user32.dll没有导出这个函数。   
//#ifdef UNICODE  
//#define MessageBoxTimeout MessageBoxTimeoutW  
//#else  
//#define MessageBoxTimeout MessageBoxTimeoutA  
//#endif  
extern "C"  
{
	int WINAPI MessageBoxTimeoutA(IN HWND hWnd, IN LPCSTR lpText, IN LPCSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);  
	int WINAPI MessageBoxTimeoutW(IN HWND hWnd, IN LPCWSTR lpText, IN LPCWSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);  
}; 
void MessageBoxDelayTime(CString str,INT32U time)
{
	CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString string;
	string.Format(_T("%d"), time); //将变量组装到字符串中
    //MessageBoxTimeoutA(pMainDlg->GetSafeHwnd(), _T(str+"\r\n"+string+"秒后自动关闭！"), _T("延时对话框"),  MB_ICONINFORMATION, GetSystemDefaultLangID(),1000*time);  

}
