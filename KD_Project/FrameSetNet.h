#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

// 带有拆分器的 CFrameSetNet 框架

class CFrameSetNet : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CFrameSetNet)
protected:
	CFrameSetNet();           // 动态创建所使用的受保护的构造函数
	virtual ~CFrameSetNet();

protected:
	//virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	DECLARE_MESSAGE_MAP()
public:

	CSplitterWnd m_wndSplitter;
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
//	afx_msg void OnIdrRbmenuMeterr();
};


