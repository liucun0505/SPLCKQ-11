#pragma once


// CMainTestFrame 框架

class CMainTestFrame : public CMDIFrameWnd
{
	DECLARE_DYNCREATE(CMainTestFrame)
protected:
	CMainTestFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CMainTestFrame();

protected:
	DECLARE_MESSAGE_MAP()
};


