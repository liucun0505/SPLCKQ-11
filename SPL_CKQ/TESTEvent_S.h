#pragma once


// CTESTEvent_S
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
#include "TESTEvent_M.h"
class CTESTEvent_S : public CWnd,public CEventPublic
{
	DECLARE_DYNAMIC(CTESTEvent_S)
	
public:
	CTESTEvent_S();
	virtual ~CTESTEvent_S();
	void C3762_TEST(HTREEITEM hTree);//方案处理函数
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
};


