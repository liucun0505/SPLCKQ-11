// addmactest.cpp : 实现文件
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "addmactest.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "RightTabView.h"
// addmactest 对话框

IMPLEMENT_DYNAMIC(addmactest, CDialogEx)

addmactest::addmactest(CWnd* pParent /*=NULL*/)
	: CDialogEx(addmactest::IDD, pParent)
	, m_MAC(_T(""))
	, m_TYPE(_T(""))
	, m_TEI(_T(""))
{

}

addmactest::~addmactest()
{
}

void addmactest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_MAC);
	DDV_MaxChars(pDX, m_MAC, 12);
	DDX_Text(pDX, IDC_EDIT2, m_TYPE);
	DDV_MaxChars(pDX, m_TYPE, 1);
	DDX_Text(pDX, IDC_EDIT3, m_TEI);
	DDV_MaxChars(pDX, m_TEI, 6);
	DDX_Control(pDX, IDC_CHECK1, m_ch);
}


BEGIN_MESSAGE_MAP(addmactest, CDialogEx)
	ON_BN_CLICKED(IDOK, &addmactest::OnBnClickedOk)
END_MESSAGE_MAP()


// addmactest 消息处理程序


void addmactest::OnBnClickedOk()
{
	//// TODO: 在此添加控件通知处理程序代码
	if(n_ChooseDlg==1){
		CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
		CFrameSetNet * pChildFrm =  ( CFrameSetNet *) pMain->GetActiveFrame();
		CRightTabView *  pTabView =( CRightTabView *) pChildFrm->m_wndSplitter.GetPane(0 , 1);
		//pTabView->SetActiveView(2);
		CCKQViewTabErrMet * pViewTabErrMet = (CCKQViewTabErrMet *)pTabView->GetActiveView();
		UpdateData(TRUE);
		pViewTabErrMet->InsertMetMsg(m_MAC,m_TYPE,m_TEI);
	}
	else if(n_ChooseDlg==2){
		CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
		CFrameSetNet * pChildFrm =  ( CFrameSetNet *) pMain->GetActiveFrame();
		CRightTabView *  pTabView =( CRightTabView *) pChildFrm->m_wndSplitter.GetPane(0 , 1);
		//pTabView->SetActiveView(2);
		CCKQViewUpdata * pViewTabUpdata  = (CCKQViewUpdata *)pTabView->GetActiveView();
		UpdateData(TRUE);
		pViewTabUpdata->InsertMetMsg(m_MAC,m_TYPE,m_TEI);
	}
	if(m_ch.GetCheck()==1){
		//UpdateData(FALSE);   
	}
	else{
	  CDialogEx::OnOK();
	}
}

