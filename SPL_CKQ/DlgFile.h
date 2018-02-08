#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include "Tools.h"
// Dlgfile dialog





class Dlgfile : public CDialogEx
{
	DECLARE_DYNAMIC(Dlgfile)

public:
	Dlgfile(CString stWhere,CWnd* pParent = NULL);   // standard constructor
	virtual ~Dlgfile();

	// Dialog Data
	enum { IDD = IDD_DIALOG_EXT_READ_METER };

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

	std::fstream m_file;
	void ReadFileLine();
	void SplitLine(CString line,CString token);
	

	void SetFileName(CString str);
	void SaveInfo(CString strTopLine);
	void FileNameIndexChange();
	afx_msg void OnEnChangeEditFile();
	afx_msg void OnBnClickedButtonOpen();
	BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	CEdit FileName1;
	afx_msg void OnBnClickedOk();
};
