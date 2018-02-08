#pragma once


// CTESTInterChangEability_STA
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
class CTESTInterChangEability_STA : public CWnd
{
	DECLARE_DYNAMIC(CTESTInterChangEability_STA)

public:
	CTESTInterChangEability_STA();
	virtual ~CTESTInterChangEability_STA();
	void C3762_TEST(HTREEITEM hTree);//方案处理函数
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
};


