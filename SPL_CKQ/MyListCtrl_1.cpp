// MyListCtrl_1.cpp : 实现文件
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "MyListCtrl_1.h"


// MyListCtrl_1

IMPLEMENT_DYNAMIC(MyListCtrl_1, CListCtrl)

MyListCtrl_1::MyListCtrl_1()
{

}

MyListCtrl_1::~MyListCtrl_1()
{
}


BEGIN_MESSAGE_MAP(MyListCtrl_1, CListCtrl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()



// MyListCtrl_1 消息处理程序




void MyListCtrl_1::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{

	// TODO:  添加您的代码以绘制指定项

	CDC* pDC = CDC::FromHandle(lpDIS->hDC); 
	
	LVITEM lvi = {0}; 
	lvi.mask = LVIF_STATE;//|LVIF_IMAGE; 
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED ; 
	lvi.iItem = lpDIS->itemID; 
	BOOL bGet = GetItem(&lvi); 
	
	BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)||((lvi.state & LVIS_SELECTED) && 
		((GetFocus() == this)|| (GetStyle() & LVS_SHOWSELALWAYS)))); 
	
	// 画文本背景 
	CRect rcBack = lpDIS->rcItem; 
	pDC->SetBkMode(TRANSPARENT); 
	if( bHighlight ) 
	{ 
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT)); 
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT)); 
		
		pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_HIGHLIGHT))); 
	} 
	else 
	{ 
		CString str = _T("");
		str = GetItemText(lpDIS->itemID,1);
		pDC->SetTextColor(RGB(0, 0, 255));	
	} 
		//设置字体颜色 
	CString str; 
	
	//得到焦点大小 
	CRect rcFocus = lpDIS->rcItem; 
	rcFocus.DeflateRect(1,1,1,1); 
	
	if (lpDIS->itemAction & ODA_DRAWENTIRE) 
	{ 
		//写文本 
		CString szText; 
		for (int i = 0; i < 20; i++) 
		{ 
			CRect rcItem; 
			if ( !GetSubItemRect(lpDIS->itemID, i, LVIR_LABEL, rcItem )) 
				continue; 
			szText = GetItemText( lpDIS->itemID, i ); 
			rcItem.left += 5;
			rcItem.right -= 1; 

			if(i==4){
				CString str2 = GetItemText(lpDIS->itemID,5);
				if (str2 == "成功"||str2 == "参数初始化成功")
				{
					pDC->SetTextColor(RGB(0,255,0));
				}
				if (str2 == "失败"||str2 == "参数初始化失败")
				{
					pDC->SetTextColor(0x0000FF);
				}
			}

			pDC->DrawText(szText, lstrlen(szText), &rcItem, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE);
		} 
	}
}


void MyListCtrl_1::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	//CMenu menu;//
 //   VERIFY(menu.LoadMenu(IDR_MENUMSGMET));
	//CMenu* pPopup = menu.GetSubMenu(0);
	//ASSERT(pPopup != NULL);
	//CWnd* pWndPopupOwner = this;

	//while (pWndPopupOwner->GetStyle() & WS_CHILD)
	//	pWndPopupOwner = pWndPopupOwner->GetParent();

	//pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
	//	pWndPopupOwner);
}
