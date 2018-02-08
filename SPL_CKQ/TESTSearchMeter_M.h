#pragma once


// CTESTSearchMeter_M
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
#include "TESTSearchMeter_S.h"
class CTESTSearchMeter_M : public CWnd,public CSearchAmtPublic
{
	DECLARE_DYNAMIC(CTESTSearchMeter_M)

public:
	CTESTSearchMeter_M();
	virtual ~CTESTSearchMeter_M();
	void C3762_TEST(HTREEITEM hTree);//方案处理函数
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
	INT8U TestInCmd(void);
	//	单采集器、不白名单内搜表【模拟】
    INT8U TestCjqNoNetList(INT8U vSrcCnt );
	//	采集器不响应启动、查询、停止搜表命令【模拟】
     INT8U TestCjqNoAck(void );
	 //	全STA的搜表测试【模拟】
      INT8U  TestSearchAllSta(INT16U vSrcCnt,INT8U ackType);
	  	 //	全采集器的搜表测试【模拟】
     INT8U  TestSearchAllCjq(INT16U vSrcCnt);
	 //	混合模式的搜表测试【模拟】
	 INT8U  TestSearchStaCjq(INT16U vSrcCnt);
	 //全STA的MAC地址影射测试【模拟】
	 INT8U  TestMACAllSta(INT16U vSrcCnt);
	 INT8U CmpMacIsOk(INT16U AmtBp,INT16U MacBp,INT32U WaitTimeS);
	 //全采集器的MAC地址影射测试【模拟】vSrcCnt指采集器块数，每块32只
     INT8U TestMACAllCjq(INT16U vSrcCnt);
	 //1混合模式的MAC地址影射测试【模拟】
     INT8U TestMACStaCjq(INT16U vSrcCnt);
	 //MAC地址重复影射测试【模拟】
     INT8U TestMACRePeat(void);
};


