#pragma once



// CView698 窗体视图
#include "DLT698_45.h"
#include "afxwin.h"
class CView698 : public CFormView
{
	DECLARE_DYNCREATE(CView698)

protected:
	CView698();           // 动态创建所使用的受保护的构造函数
	virtual ~CView698();

public:
	enum { IDD = IDD_DIALOG_698 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	INT8U * m_pbSrcAPDUbuf;
	INT8U * m_pSrcAPDUbuf;
	INT16U m_SrcAPDUlen;
	void _16Daochar(char *testc,INT8U *buf);
	CString _buf16tostr16(INT8U * buf16,int len,bool bKongge,bool bDaoxu);
	void _str16tobuf16(CString str16,INT8U * buf16,INT16U &len);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	
	CEdit m_editShow;
	INT8U BCDtoInteger(INT8U integer, INT8U * pDstbuf , INT8U & Dstlen);
	u_long BCD_Change_Hex(u_long BCDValue);
};


