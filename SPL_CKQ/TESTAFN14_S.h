#pragma once


// CTESTAFN14_S
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
#include "TESTCCO_AFN14.h"
class CTESTAFN14_S : public CWnd, public CAFN14ReadMeterFun
{
	DECLARE_DYNAMIC(CTESTAFN14_S)

public:
	CTESTAFN14_S();
	virtual ~CTESTAFN14_S();
	void C3762_TEST(HTREEITEM hTree);//方案处理函数
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
};


