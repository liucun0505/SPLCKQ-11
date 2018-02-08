#pragma once


// CDlg13762Frame 对话框

class CDlg13762Frame : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg13762Frame)

public:
	CDlg13762Frame(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg13762Frame();

// 对话框数据
	enum { IDD = IDD_DIALOG_13862 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
	CRect m_cRect;
	void UpDataData();
	void KongjianSize(int nID, int cx, int cy, bool bComb = false);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CComboBox m_combC1;
	CComboBox m_combC2;
	CComboBox m_combC3;
	CComboBox m_combM1;
	CComboBox m_combM2;
	CComboBox m_combM3;
	CComboBox m_combM4;
	CComboBox m_combM5;
	CComboBox m_combM6;
	CComboBox m_combM9;
	CComboBox m_combM7;
	CComboBox m_combM8;
	CEdit m_editA1;
	CEdit m_editA2;
	CEdit m_editA3;
	CEdit m_editFN;
	CEdit m_editM1;
	CEdit m_editM2;
	CEdit m_editData;
	CComboBox m_combAFN;
};
