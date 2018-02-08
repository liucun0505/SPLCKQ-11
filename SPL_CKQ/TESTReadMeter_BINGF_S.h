#pragma once


// CTESTReadMeter_BINGF_S
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
class CTESTReadMeter_BINGF_S : public CWnd
{
	DECLARE_DYNAMIC(CTESTReadMeter_BINGF_S)

public:
	CTESTReadMeter_BINGF_S();
	virtual ~CTESTReadMeter_BINGF_S();
	void C3762_TEST(HTREEITEM hTree);//方案处理函数
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
};


