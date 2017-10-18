#pragma once


// CDlgCKQUpdataTime 对话框

class CDlgCKQUpdataTime : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCKQUpdataTime)

public:
	CDlgCKQUpdataTime(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCKQUpdataTime();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTime;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
