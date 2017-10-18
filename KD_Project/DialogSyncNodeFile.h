#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include "Tools.h"
#include "afxwin.h"
// DialogSyncNodeFile dialog


enum eSyncMode
{
	e_SyncFile,
	e_SyncAuto,
};


class DialogSyncNodeFile : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSyncNodeFile)

public:
	DialogSyncNodeFile(CString stWhere, CWnd* pParent = NULL);   // standard constructor
	virtual ~DialogSyncNodeFile();

	// Dialog Data
	enum { IDD = IDD_DIALOG_EXT_SYNC_NODEFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CEdit FileName;
	CString m_stWhere;
	CString m_sfilename;


	std::vector <CString> m_fileline;


	CString m_linearg[20];

	FILE *m_fp;

	CTools m_tools;
	INT16U m_NodeNum;//node num per frame
	INT16U m_TotalNum;//
	__int64 m_StartMAC;
	INT8U m_SyncMdoe;

	std::fstream m_file;
	void ReadFileLine();
	void SplitLine(CString line, CString token);


	void SetFileName(CString str);
	void SaveInfo(CString strTopLine);
	void FileNameIndexChange();
	afx_msg void OnEnChangeEditFile();
	afx_msg void OnBnClickedButtonOpen();
	BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	CEdit FileName1;
	afx_msg void OnBnClickedOk();
	CEdit m_editNodeNum;
	afx_msg void OnBnClickedRadio2();
	CEdit editStartMAC;
	CEdit editTotalNodeNum;
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio1();
	int m_ClearFirst;
};
