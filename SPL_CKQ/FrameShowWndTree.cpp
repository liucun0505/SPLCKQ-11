// FrameShowWndTree.cpp : 实现文件
//

#include "stdafx.h"
#include "SPL_CKQ.h"
#include "FrameShowWndTree.h"
#include "MainFrm.h"

// CFrameShowWndTree

IMPLEMENT_DYNAMIC(CFrameShowWndTree, CDockablePane)

CFrameShowWndTree::CFrameShowWndTree()
{

}

CFrameShowWndTree::~CFrameShowWndTree()
{
}


BEGIN_MESSAGE_MAP(CFrameShowWndTree, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CFrameShowWndTree 消息处理程序

void CFrameShowWndTree::InsertItemToTreeList(CString strTableName)
{

	//pView=(ShowNetTreeView*)m_cSplitter.GetPane(0,0);//放在OnCreate函数里
	m_treeData.DeleteAllItems();
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strTP_TIER = _T("");
	int nCeng = 15;//最大层15
	HTREEITEM m_hTree[500];
	CString strCeng = _T("");
	CString str_n = _T("");
	CString str_nodeNum = _T("");
	CString strAllDatalist[500][6];
	CString f_strDatalist[6][500];
	int nNumb = 0 , nAlldataNumb;
	int n = 0 , m = 0 , i = 0;
	m_access.SelectDataFromTable(pMain->m_PeiZhi_db/*_T(".\\配置文件\\HistTPShow.accdb")*/, strTableName , _T("TP_MAC,TP_TEI,TP_PTEI,TP_ROLE,TP_TIER,TP_READSUCCESS") ,_T("") ,m_strlist ,nAlldataNumb);
	if(nAlldataNumb>0){
		for(n = 0 ; n < nAlldataNumb ; n++)
		{
			m_tools.Split(m_strlist[n] , _T("$") ,strAllDatalist[n] , nNumb);
		}
		//获取各个信息列
		for(n = 0 ; n < nAlldataNumb ; n++)
		{
			f_strDatalist[0][n]= strAllDatalist[n][0];//
			f_strDatalist[1][n]= strAllDatalist[n][1];
			f_strDatalist[2][n]= strAllDatalist[n][2];
			f_strDatalist[3][n]= strAllDatalist[n][3];
			f_strDatalist[4][n]= strAllDatalist[n][4];
			f_strDatalist[5][n]= strAllDatalist[n][5];
			strTP_TIER+=strAllDatalist[n][4] + _T("$");
		}
		//获取本次最大层级
		while(true)
		{
			strCeng.Format(_T("%d") , nCeng);
			if(strTP_TIER.Find(strCeng) != -1)
			{
				break;
			}
			nCeng-= 1;
		}
		str_nodeNum.Format(_T("%d") , nAlldataNumb-1);
		for(n = 0 ; n < nCeng ; n++)//每次处理一层
		{
			for(m = 0 ; m < nAlldataNumb ; m++)
			{
		        str_n.Format(_T("%d") , n+1);
				if(f_strDatalist[4][m]==str_n){
					if(str_n==_T("1")){
						m_hTree[_ttoi(f_strDatalist[1][m])] = m_treeData.InsertItem(_T("（TEI：")+f_strDatalist[1][m]+_T("）")+f_strDatalist[0][m]+_T("（入网STA数量：")+str_nodeNum+_T("）"), 0, 0);
					}
					else{
						m_hTree[_ttoi(f_strDatalist[1][m])]=m_treeData.InsertItem(_T("（TEI：")+f_strDatalist[1][m]+_T("）")+f_strDatalist[0][m],n,n,m_hTree[_ttoi(f_strDatalist[2][m])],TVI_LAST);
					}
				}
			}
		}

		HTREEITEM hTreeItem=m_treeData.GetRootItem();
		MyExpandTree(hTreeItem);

	}
}
void CFrameShowWndTree::MyExpandTree(HTREEITEM hTreeItem)  
{  
	//hTreeItem=pView->GetTreeCtrl().GetRootItem();
    if(!m_treeData.ItemHasChildren(hTreeItem))//如果树控件根节点没有子节点则返回  
    {  
        return;  
    }  
    HTREEITEM hNextItem = m_treeData.GetChildItem(hTreeItem);//若树控件的根节点有子节点则获取根节点的子节点  
    while (hNextItem != NULL)//若有  
    {  
        MyExpandTree(hNextItem);//递归，展开子节点下的所有子节点  
        hNextItem = m_treeData.GetNextItem(hNextItem, TVGN_NEXT);//获取根节点的下一个子节点  
    }  
    m_treeData.Expand(hTreeItem,TVE_EXPAND);//展开节点  
} 


int CFrameShowWndTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
		CRect rect;
	CRect rect1;
	GetClientRect(rect1);
	ScreenToClient(&rect);
	m_treeData.Create(TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS ,rect1,this,IDC_TREEDATAMSG); 
	HICON hIcon[15];      // 图标句柄数组 
	hIcon[0] = theApp.LoadIcon(IDI_CCO2); 
	hIcon[1] = theApp.LoadIcon(IDI_ZONGSE); 
	hIcon[2] = theApp.LoadIcon(IDI_LVSE); 
	hIcon[3] = theApp.LoadIcon(IDI_LANSE); 
	hIcon[4] = theApp.LoadIcon(IDI_YELLO); 
	hIcon[5] = theApp.LoadIcon(IDI_BAISE);
	    // 创建图像序列CImageList对象   
    m_imageList1.Create(16, 16, ILC_COLOR32, 6, 6);   
    // 将三个图标添加到图像序列   
    for (int i=0; i<6; i++)   
    {   
        m_imageList1.Add(hIcon[i]);   
    }
	CRect rectDummy;
	rectDummy.SetRectEmpty(); 
	m_treeData.SetImageList(&m_imageList1, TVSIL_NORMAL);
	m_treeData.ShowWindow(SW_SHOW);
	return 0;
}


void CFrameShowWndTree::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CDockablePane::OnSize(nType, cx, cy);
	if (GetSafeHwnd() == NULL)  
	{
		return;
	}
	CRect rectClient;
	GetClientRect(rectClient); 
	m_treeData.SetWindowPos(NULL, rectClient.left, rectClient.top  + 1, rectClient.Width(), rectClient.Height()  - 1, SWP_NOACTIVATE | SWP_NOZORDER);
}
