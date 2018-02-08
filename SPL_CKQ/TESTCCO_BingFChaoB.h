#pragma once


// CTESTCCO_BingFChaoB
#include "Tools.h"
#include "CDTL2007.h"


class CTESTCCO_BingFChaoB : public CWnd,public cDTL2007
{
	DECLARE_DYNAMIC(CTESTCCO_BingFChaoB)

public:
	CTESTCCO_BingFChaoB();
	virtual ~CTESTCCO_BingFChaoB();
	void C3762_TEST(HTREEITEM hTree);//方案处理函数
	INT8U BinfFa1_TEST();
	INT8U BinfFa2_TEST();
	INT8U BinfFa3_TEST();
	INT8U BinfFa4_TEST();
	INT8U BinfFa5_TEST();
	INT8U BinfFa6_TEST();
	INT8U QueMeterRunSta();
	INT8U QueDi(TH_IN INT8U Num, TH_OUT INT32U Di);
	CTools m_tool;
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	INT8U m_RunFg;//控制模拟表运行状态字	
};


