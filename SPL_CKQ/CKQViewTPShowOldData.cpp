// CKQViewTPShowOldData.cpp : 实现文件
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "CKQViewTPShowOldData.h"
#include "MainFrm.h"
#include "SimJzq.h"
extern CSimJzq  gSimJzq;

// CCKQViewTPShowOldData

IMPLEMENT_DYNCREATE(CCKQViewTPShowOldData, CFormView)

CCKQViewTPShowOldData::CCKQViewTPShowOldData()
	: CFormView(CCKQViewTPShowOldData::IDD)
{
	m_bOver =false;
	m_bStop = false;
	m_nShowNumb = 0;
	m_fFont = 15;
	m_Scale = 1.0f;
	m_cR = 20;
	m_cRW = 200;
	m_cTBWeith = 50;
	m_cLRWeith = 10;
	m_nAlldataNumb = 0;
	m_nLineType = 0;
	m_bShow = false;
	for(int m = 0 ; m < 10 ; m++)
	{
		m_nOnlineNumb[m] = 0;
	}
}

CCKQViewTPShowOldData::~CCKQViewTPShowOldData()
{
}

void CCKQViewTPShowOldData::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BUTTON_OVER, m_btnOver);
}

BEGIN_MESSAGE_MAP(CCKQViewTPShowOldData, CFormView)
	ON_WM_MOUSEHWHEEL()
	ON_WM_CONTEXTMENU()
	//ON_COMMAND(IDR_OLDMENU_RBTP_HEID, &CCKQViewTPShowOldData::OnIdrOldmenuRbtpHeid)
	//ON_COMMAND(IDR_OLDMENU_RBTP_SHOW, &CCKQViewTPShowOldData::OnIdrOldmenuRbtpShow)
	ON_COMMAND(IDR_OLDRBTP_MESSAGE, &CCKQViewTPShowOldData::OnIdrOldrbtpMessage)
	ON_COMMAND(ID_OLDLINE_ZHI, &CCKQViewTPShowOldData::OnOldlineZhi)
	ON_COMMAND(ID_OLDLINE_ZHIJIAO, &CCKQViewTPShowOldData::OnOldlineZhijiao)
	ON_COMMAND(ID_OLDRBTP_UPDATA, &CCKQViewTPShowOldData::OnOldrbtpUpdata)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CCKQViewTPShowOldData::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_OVER, &CCKQViewTPShowOldData::OnBnClickedButtonOver)
END_MESSAGE_MAP()


// CCKQViewTPShowOldData 诊断

#ifdef _DEBUG
void CCKQViewTPShowOldData::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCKQViewTPShowOldData::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CCKQViewTPShowOldData 消息处理程序
void CCKQViewTPShowOldData::OnDraw(CDC* pDC)
{
	int n = 0;
	pDC->SelectObject(&m_cpenXu);//画线
	if (m_nAlldataNumb != 0)
	{
		CRect rect;
		GetClientRect(rect); 
		m_TPDlgShowExplian.MoveWindow(rect.right - 220,rect.top + 50, 200 ,410);
	}
	for (n = 0; n<m_nAlldataNumb ;n++)
	{

		if(m_nLineType == 0)
		{
			if (m_nPointLine[n][1] != 0)
			{
				pDC->MoveTo(m_fCoordinate[m_nPointLine[n][0]][0],m_fCoordinate[m_nPointLine[n][0]][1]);
				pDC->LineTo(m_fCoordinate[m_nPointLine[n][1]][0],m_fCoordinate[m_nPointLine[n][1]][1]);
			}
		}
		else
		{
			if (m_nPointLine[n][1] != 0)
			{
				pDC->MoveTo(m_fCoordinate[m_nPointLine[n][0]][0],m_fCoordinate[m_nPointLine[n][0]][1]);
				pDC->LineTo(m_fCoordinate[m_nPointLine[n][0]][0],(m_fCoordinate[m_nPointLine[n][0]][1] - m_cTBWeith*4/5));
				pDC->LineTo(m_fCoordinate[m_nPointLine[n][1]][0],(m_fCoordinate[m_nPointLine[n][0]][1] - m_cTBWeith*4/5));
				pDC->LineTo(m_fCoordinate[m_nPointLine[n][1]][0],m_fCoordinate[m_nPointLine[n][1]][1]);
			}
		}

	}
	pDC->BeginPath();
	for (n = 1; n<m_nAlldataNumb + 1 ;n++)//画圆形节点
	{
		pDC->SelectObject(&m_BrushAll[m_nPointColor[m_nPointNumb[n-1]]]); 
		pDC->EndPath(); 
		pDC->Ellipse(m_fCoordinate[m_nPointNumb[n-1]][0] - m_cR,m_fCoordinate[m_nPointNumb[n-1]][1] - m_cR,m_fCoordinate[m_nPointNumb[n-1]][0] + m_cR,m_fCoordinate[m_nPointNumb[n-1]][1] + m_cR); 
	}

	pDC->SelectObject(&m_RrushFont);
	pDC->SetBkMode(TRANSPARENT); 
	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));
	lf.lfHeight = -MulDiv(m_fFont, pDC->GetDeviceCaps(LOGPIXELSY), 72);
	lf.lfWeight = FW_NORMAL;
	lf.lfOutPrecision = OUT_TT_ONLY_PRECIS;
	CFont newFont;
	newFont.CreateFontIndirect(&lf);
	pDC->BeginPath();
	pDC->SelectObject(&newFont);
	CString str;
	float fFont = 0;
	for (n = 1; n<m_nAlldataNumb + 1 ;n++)//节点编号 
	{
		str.Format(_T("%d") , m_nPointLine[n - 1][0]);
		switch(str.GetLength())
		{
		case 1:
			fFont = m_cR/4;
			break;
		case 2:
			fFont = m_cR/2;
			break;
		case 3:
			fFont = m_cR*6/7;
			break;
		}
		pDC->TextOut(m_fCoordinate[m_nPointNumb[n-1]][0]- fFont, m_fCoordinate[m_nPointNumb[n-1]][1]- m_cR/2,str);
	}
	pDC->EndPath();
	pDC->FillPath(); 
}
void CCKQViewTPShowOldData::GetPointCoordinate(CString strTableName)
{
	//CString strlist[MODUMAXNUMB];
	CString strAllDatalist[MODUMAXNUMB][6];
	int nNumb = 0 , nAlldataNumb;
	CString strWhere = _T("") ,strAll = _T("");
	int nCeng = 15;
	CString strCeng = _T("");
	int n = 0 , m = 0 , i = 0;
	int nChildNumb = 0;
	float fChildWeith = 0;
	float fWeith[MODUMAXNUMB];
	for(m = 0 ; m < 10 ; m++)
	{
		m_nOnlineNumb[m] = 0;
	}
	m_access.SelectDataFromTable(_T(".\\配置文件\\HistTPShow.accdb") , strTableName , _T("TP_MAC,TP_TEI,TP_PTEI,TP_ROLE,TP_TIER,TP_READSUCCESS") ,_T("") ,m_strlist ,nAlldataNumb);
	m_nAlldataNumb = nAlldataNumb;
	for(n = 0 ; n < nAlldataNumb ; n++)
	{
		m_tools.Split(m_strlist[n] , _T("$") ,strAllDatalist[n] , nNumb);
	}

	for(n = 0 ; n < nAlldataNumb ; n++)
	{
		switch(_ttoi(strAllDatalist[n][3]))
		{
		case 2:
			m_nOnlineNumb[0] += 1;
			break;
		case 3:
			m_nOnlineNumb[1] += 1;
			break;
		case 4:
			m_nOnlineNumb[2] += 1;
			break;
		case 5:
			m_nOnlineNumb[3] += 1;
			break;
		case 6:
			m_nOnlineNumb[4] += 1;
			break;
		case 7:
			m_nOnlineNumb[5] += 1;
			break;
		}
		m_nPointNumb[n] = _ttoi(strAllDatalist[n][1]);
		m_nPointLine[n][0] = _ttoi(strAllDatalist[n][1]);
		m_nPointLine[n][1] = _ttoi(strAllDatalist[n][2]);
		strAll += strAllDatalist[n][4] + _T("$");
	}
	while(true)
	{
		strCeng.Format(_T("%d") , nCeng);
		if(strAll.Find(strCeng) != -1)
		{
			break;
		}
		nCeng -= 1;
	}

	for(i = 0 ; i < nCeng; i++)
	{
		strCeng.Format(_T("%d") , nCeng-i);
		for(n = 0 ; n < nAlldataNumb ; n++)
		{
			nChildNumb = 0;
			fChildWeith = 0;
			if (strAllDatalist[n][4] == strCeng)
			{
				for(m = 0 ; m < nAlldataNumb ; m++)
				{
					if (strAllDatalist[n][1] == strAllDatalist[m][2])
					{
						nChildNumb++; //有nChildNumb个子集
						fChildWeith += m_fPointWeith[_ttoi(strAllDatalist[m][1])];
					}
				}
				if (nChildNumb == 0)
				{
					m_fPointWeith[_ttoi(strAllDatalist[n][1])] = m_cR * 2 + m_cLRWeith;
				}
				else
				{
					m_fPointWeith[_ttoi(strAllDatalist[n][1])] = fChildWeith;
				}
			}
		}
	}



	for (i = 1 ; i < nCeng + 1 ; i++)
	{
		for(m = 0 ; m < MODUMAXNUMB ; m++)
		{
			fWeith[m] = 0;
		}

		for(n = 0 ; n < nAlldataNumb ; n++)
		{
			if (_ttoi(strAllDatalist[n][4]) == i)
			{
				m_nPointColor[_ttoi(strAllDatalist[n][1])] =  _ttoi(strAllDatalist[n][3]);
				m_fCoordinate[_ttoi(strAllDatalist[n][1])][1] = (i)* (m_cTBWeith + 2*m_cR);

				if (_ttoi(strAllDatalist[n][4]) == 1)
				{
					m_fCoordinate[_ttoi(strAllDatalist[n][1])][0] = m_fPointWeith[_ttoi(strAllDatalist[n][1])]/2 + m_cLRWeith ;
				}
				else
				{
					m_fCoordinate[_ttoi(strAllDatalist[n][1])][0] = m_fCoordinate[_ttoi(strAllDatalist[n][2])][0] - m_fPointWeith[_ttoi(strAllDatalist[n][2])]/2 + m_fPointWeith[_ttoi(strAllDatalist[n][1])]/2 + fWeith[_ttoi(strAllDatalist[n][2])];
					fWeith[_ttoi(strAllDatalist[n][2])] += m_fPointWeith[_ttoi(strAllDatalist[n][1])];
				}
			}
		}
	}
	if (nCeng* (m_cTBWeith + 2*m_cR) > m_cy)
	{
		m_cy = (nCeng + 1)* (m_cTBWeith + 2*m_cR);
	}
	if (m_fPointWeith[1] + m_cRW > m_cx)
	{
		m_cx = m_fPointWeith[1] + m_cRW;
	}

	//SetScrollSizes(IDD_DIALOG_TUOPUSHOW , CSize(m_cx, m_cy));
	m_TPDlgShowExplian.GetNumb(m_nOnlineNumb);//更新各个模块个数
	Invalidate();
}

void CCKQViewTPShowOldData::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CRect rect;
	GetClientRect(rect); 
	m_cx=rect.right;
	m_cy=rect.bottom;
	SetScrollSizes(IDD_DIALOG_TUOPUSHOW_OLD , CSize(m_cx, m_cy));

	m_btnOver.MoveWindow(rect.right - 50, 10, 50, 20);
	m_btnStop.MoveWindow(rect.right - 110, 10, 50, 20);
	m_ctrlProgress.MoveWindow(rect.right - 420 ,10 ,300, 20);
	m_btnStop.ShowWindow(SW_HIDE);
	m_btnOver.ShowWindow(SW_HIDE);
	m_ctrlProgress.ShowWindow(SW_HIDE);
	m_gw13762.SetMainAdd(pMain->m_HostNodeAddress);
	gSimJzq.SetMainAdd(pMain->m_HostNodeAddress);
	m_RrushFont.CreateSolidBrush(RGB(128,0,64));//编号颜色
	m_BrushAll[2].CreateSolidBrush(RGB(255,0,0));//CC0
	m_BrushAll[3].CreateSolidBrush(RGB(255,128,128));//U_CCO
	m_BrushAll[4].CreateSolidBrush(RGB(0,255,0));//STA
	m_BrushAll[5].CreateSolidBrush(RGB(128,255,128));//U_STA
	m_BrushAll[6].CreateSolidBrush(RGB(255,128,64));//PCO
	m_BrushAll[7].CreateSolidBrush(RGB(192,192,192));//掉线
	m_cpenXu.CreatePen(PS_SOLID,1,RGB(128,0,64));//线的颜色
	int m = 0 ;
	for(m = 0 ; m < MODUMAXNUMB ; m++)
	{
		m_nPointColor[m] = 0;
		m_fPointWeith[m] = 0;
		m_fCoordinate[m][0] = 0;
		m_fCoordinate[m][1] = 0;
		m_strlist[m] = _T("");
		m_nPointLine[m][0] = 0;
		m_nPointLine[m][1] = 0;
		m_nPointNumb[m] = 0;
	}
	for(m = 0 ; m < 10 ; m++)
	{
		m_nOnlineNumb[m] = 0;
	}
	m_DlgOldTPMessage.Create(IDD_DIALOG_OLDTPMSG,this);
	m_TPDlgJDMsg.Create(IDD_DIALOG_TPSHOW_JDMSG,this);
	m_TPDlgJDMsg.SetWindowPos(NULL,0,0,1,1,SWP_HIDEWINDOW);
	m_TPDlgShowExplian.Create(IDD_DIALOG_TPSHOW_EXPLIAN,this);
	m_TPDlgShowExplian.SetWindowPos(NULL,rect.right - 220,rect.top + 50, 200 ,410,SWP_HIDEWINDOW);

	
	// TODO: 在此添加专用代码和/或调用基类
}

BOOL CCKQViewTPShowOldData::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 此功能要求 Windows Vista 或更高版本。
	// _WIN32_WINNT 符号必须 >= 0x0600。
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static float upLimit = 10.0f;
	static float downLinit = 0.04f;
	static float fUp = 1.1;
	static float fDown = 0.9f;
	bool bChange = true ;
	int n = 0;
	if(zDelta > 0 && m_Scale <= upLimit)
	{
		m_cx *= fUp;
		m_cy *= fUp;
		m_cR *= fUp;
		m_cTBWeith *= fUp;
		m_cLRWeith *= fUp;
		m_cRW *= fUp;
		m_fFont *= fUp;
		for( n = 1 ; n < m_nAlldataNumb + 1 ; n++)
		{
			m_fCoordinate[m_nPointNumb[n-1]][0] *= fUp;
			m_fCoordinate[m_nPointNumb[n-1]][1] *= fUp;
		}
		bChange = true;
	}
	else if(zDelta < 0 && m_Scale >= downLinit)
	{
		m_cx /= fUp;
		m_cy /= fUp;
		m_cR /= fUp;
		m_cTBWeith /= fUp;
		m_cLRWeith /= fUp;
		m_cRW /= fUp;
		if (m_fFont != 1)
		{
			m_fFont /= fUp;
		}
		for( n = 1 ; n < m_nAlldataNumb + 1 ; n++)
		{
			m_fCoordinate[m_nPointNumb[n-1]][0] /= fUp;
			m_fCoordinate[m_nPointNumb[n-1]][1] /= fUp;
		}
		bChange = false;
	}
	this->Invalidate();
	SetScrollSizes(IDD_DIALOG_TUOPUSHOW_OLD , CSize(m_cx, m_cy));
	return CFormView::OnMouseWheel(nFlags, zDelta, pt);
}
void CCKQViewTPShowOldData::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU_OLDRBTP));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}

//void CCKQViewTPShowOldData::OnIdrOldmenuRbtpHeid()
//{
//	m_TPDlgShowExplian.ShowWindow(SW_HIDE);
//}
//void CCKQViewTPShowOldData::OnIdrOldmenuRbtpShow()
//{
//	m_TPDlgShowExplian.GetNumb(m_nOnlineNumb);
//	m_TPDlgShowExplian.ShowWindow(SW_SHOW);
//}
void CCKQViewTPShowOldData::OnOldlineZhi()
{
	m_nLineType = 0;
	this->Invalidate();
}
void CCKQViewTPShowOldData::OnOldlineZhijiao()
{
	m_nLineType = 1;
	this->Invalidate();
}


void CCKQViewTPShowOldData::OnIdrOldrbtpMessage()
{
	CRect rect;
	GetClientRect(rect); 
	m_DlgOldTPMessage.SetWindowPos(NULL,rect.left,rect.top,rect.right,rect.bottom,SWP_SHOWWINDOW);
	m_DlgOldTPMessage.ShowWindow(SW_SHOWMAXIMIZED);
	m_ctrlProgress.ShowWindow(SW_HIDE);
	m_btnOver.ShowWindow(SW_HIDE);
	m_btnStop.ShowWindow(SW_HIDE);
	m_TPDlgShowExplian.ShowWindow(SW_HIDE);
	
}
DWORD WINAPI ThreadOldTP (PVOID pParam) 
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CCKQViewTPShowOldData * pView = (CCKQViewTPShowOldData *)pParam;
	pView->m_btnStop.ShowWindow(SW_SHOW);
	pView->m_btnOver.ShowWindow(SW_SHOW);
	pView->m_ctrlProgress.ShowWindow(SW_SHOW);
	pView->m_ctrlProgress.SetRange(0 , pView->m_nShowNumb);
	for(int n = 0 ; n < pView->m_nShowNumb; n++)
	{
		if (pView->m_bOver)
		{
			pView->m_btnStop.SetWindowText(_T("暂停"));
			pView->m_bOver = false;
			pView->m_ctrlProgress.SetPos(0);
			return 0;
		}
		while(pView->m_bStop)
		{
			Sleep(500);
		}
		pView->m_ctrlProgress.SetPos(n + 1);
		pView->GetPointCoordinate(pView->m_strShowlist[n]);
		Sleep(1000);
	}
	return 0;
}
void CCKQViewTPShowOldData::OnOldrbtpUpdata()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nShowNumb == 0)
	{
		AfxMessageBox(_T("请先选择历史拓扑图"));
		return;
	}
	m_bOver = false;
	m_hThreadsend=CreateThread (NULL,0,ThreadOldTP,this,0,NULL);
	CloseHandle(m_hThreadsend);
}
void CCKQViewTPShowOldData::OnBnClickedButtonStop()
{
	CString strName;
	m_btnStop.GetWindowText(strName);
	if (strName == "暂停")
	{
		m_bStop = true;
		m_btnStop.SetWindowText(_T("继续"));
	}
	else
	{
		m_bStop = false;
		m_btnStop.SetWindowText(_T("暂停"));
	}
}


void CCKQViewTPShowOldData::OnBnClickedButtonOver()
{
	m_bOver = true;
}
