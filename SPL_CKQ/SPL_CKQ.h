
// SPL_CKQ.h : SPL_CKQ 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

#include "User_gDefine.h"

// CSPL_CKQApp:
// 有关此类的实现，请参阅 SPL_CKQ.cpp
//

class CSPL_CKQApp : public CWinAppEx
{
public:
	CSPL_CKQApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	CMultiDocTemplate * m_pDocTemplate;
	CMultiDocTemplate * m_pDocTemp3762;
	CMultiDocTemplate * m_pDocTemp698;
// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSPL_CKQApp theApp;
