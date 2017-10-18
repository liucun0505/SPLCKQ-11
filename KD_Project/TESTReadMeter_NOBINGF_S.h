#pragma once


// CTESTReadMeter_NOBINGF_S
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "TEST_ReadMeterPublic.h"
class CTESTReadMeter_NOBINGF_S : public CWnd,public CTEST_ReadMeterPublic
{
	DECLARE_DYNAMIC(CTESTReadMeter_NOBINGF_S)

public:
	CTESTReadMeter_NOBINGF_S();
	virtual ~CTESTReadMeter_NOBINGF_S();
	void C3762_TEST(HTREEITEM hTree);//方案处理函数
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
};


