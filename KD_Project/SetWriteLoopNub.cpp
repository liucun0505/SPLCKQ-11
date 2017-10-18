// SetWriteLoopNub.cpp : implementation file
//

#include "stdafx.h"
#include "KD_Project.h"
#include "SetWriteLoopNub.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetWriteLoopNub dialog


CSetWriteLoopNub::CSetWriteLoopNub(CWnd* pParent /*=NULL*/)
	: CDialog(CSetWriteLoopNub::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetWriteLoopNub)
	m_strNum = _T("1");
	//}}AFX_DATA_INIT
}


void CSetWriteLoopNub::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetWriteLoopNub)
	DDX_Text(pDX, IDC_EDIT1, m_strNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetWriteLoopNub, CDialog)
	//{{AFX_MSG_MAP(CSetWriteLoopNub)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetWriteLoopNub message handlers

BOOL CSetWriteLoopNub::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(m_strName);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
