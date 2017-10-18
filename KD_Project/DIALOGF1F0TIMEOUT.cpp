// DIALOGF1F0TIMEOUT.cpp : implementation file
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DIALOGF1F0TIMEOUT.h"
#include "afxdialogex.h"


// CDIALOGF1F0TIMEOUT dialog

IMPLEMENT_DYNAMIC(CDIALOGF1F0TIMEOUT, CDialogEx)

CDIALOGF1F0TIMEOUT::CDIALOGF1F0TIMEOUT(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDIALOGF1F0TIMEOUT::IDD, pParent)
{

}

CDIALOGF1F0TIMEOUT::~CDIALOGF1F0TIMEOUT()
{
}

void CDIALOGF1F0TIMEOUT::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE, m_timeout);
}


BEGIN_MESSAGE_MAP(CDIALOGF1F0TIMEOUT, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDIALOGF1F0TIMEOUT::OnBnClickedOk)
END_MESSAGE_MAP()


// CDIALOGF1F0TIMEOUT message handlers


BOOL CDIALOGF1F0TIMEOUT::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	m_timeout.SetWindowTextW(_T("10"));

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDIALOGF1F0TIMEOUT::OnBnClickedOk()
{
	CString cstr;
	m_timeout.GetWindowText(cstr);

	itimeout = _ttol(cstr);

	CDialogEx::OnOK();
}
