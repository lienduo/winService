// iFilesList.cpp : 实现文件
//

#include "stdafx.h"
#include "iFilesList.h"


// CiFilesList

IMPLEMENT_DYNAMIC(CiFilesList, CListCtrl)

CiFilesList::CiFilesList()
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_pGdiToken,&gdiplusStartupInput,NULL);//初始化GDI+
}

CiFilesList::~CiFilesList()
{
	GdiplusShutdown(m_pGdiToken);//关闭GDI+
}


BEGIN_MESSAGE_MAP(CiFilesList, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_WM_DROPFILES()
	ON_NOTIFY_REFLECT(NM_CLICK, &CiFilesList::OnNMClick)
END_MESSAGE_MAP()



// CiFilesList 消息处理程序

// 自绘
void CiFilesList::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVCUSTOMDRAW* pLvcd = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
	*pResult = CDRF_DODEFAULT;
	if (pLvcd ->nmcd.dwDrawStage == CDDS_PREPAINT)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (pLvcd ->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if (pLvcd ->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM))
	{
		CDC* pDC = CDC::FromHandle(pLvcd ->nmcd.hdc);
		int nItem = static_cast<int> (pLvcd->nmcd.dwItemSpec);
		int nSubItem = pLvcd->iSubItem;
		if (nSubItem==1)
		{
			DrawSecItem(nItem,pDC);
			*pResult = CDRF_SKIPDEFAULT;
		}
	}
}
// 绘制第三列
void CiFilesList::DrawSecItem(int nItem,CDC *pDC)
{
	CRect rect;
	GetSubItemRect(nItem, 1, LVIR_LABEL, rect);
	// 绘制图标
	if(::GetFileAttributes(GetItemText(nItem,0))!=-1)
	{
		SHFILEINFO   sfi;   
		SHGetFileInfo(GetItemText(nItem,0),0,&sfi,sizeof(sfi),SHGFI_ICON|SHGFI_LARGEICON|SHGFI_USEFILEATTRIBUTES); 
		//pDC->DrawIcon(rect.left,rect.top,sfi.hIcon);
		DrawIconEx(pDC->m_hDC,rect.left,rect.top,sfi.hIcon,rect.Height(),rect.Height(),0,NULL,DI_NORMAL);
		DestroyIcon(sfi.hIcon);//DeleteObject(hIcon);
	}
	rect.left+=rect.Height();
	// 绘制背景
	bool bSelected=LVIS_SELECTED&GetItemState(nItem, LVIS_SELECTED);

	/*pDC->SetBkColor(GetSysColor(COLOR_3DHIGHLIGHT));*/
	pDC->FillSolidRect(rect,GetSysColor(COLOR_3DHIGHLIGHT));// 刷新背景
	if (bSelected)
	{
		pDC->SetTextColor(RGB(130,0,60));
		Graphics graphics(pDC->m_hDC);//GDI+画图
		LinearGradientBrush linGrBrush(
			Point(rect.left,rect.top),Point(rect.left,rect.bottom),//渐变画刷的起点与终点
			Color(100, 200,230,250),Color(100,0,60,80));
		graphics.SetSmoothingMode(SmoothingModeAntiAlias);//反锯齿,让边缘平滑一些
		graphics.FillRectangle(&linGrBrush,rect.left, rect.top+1, rect.Width(), rect.Height()-2);
	}
	else
	{
		pDC->SetTextColor(RGB(0,0,0));
	}
	

	// 绘制文字
	CString strItem=GetItemText(nItem,1);
	if (strItem!=_T(""))
	{
		HDITEM hditem;
		hditem.mask = HDI_FORMAT;
		CHeaderCtrl* pHeadCtrl=GetHeaderCtrl();
		pHeadCtrl->GetItem(1, &hditem);
		int nFmt = hditem.fmt & HDF_JUSTIFYMASK;
		UINT nFormat = DT_VCENTER | DT_SINGLELINE|DT_END_ELLIPSIS;
		if (nFmt == HDF_CENTER)
			nFormat |= DT_CENTER;
		else if (nFmt == HDF_LEFT)
			nFormat |= DT_LEFT;
		else
			nFormat |= DT_RIGHT;
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(strItem, &rect, nFormat);
	}
}
// ------------------------ 接口 ---------------------------

// 生成
BOOL CiFilesList::Create(CWnd* pParentWnd,CRect rect, UINT nID)
{
	DWORD dwStyle = WS_VISIBLE|WS_CHILD|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_NOCOLUMNHEADER|LVS_SINGLESEL/*|LVS_OWNERDRAWFIXED*/; 
	DWORD dwExStyle = /*LVS_EX_GRIDLINES|*/LVS_EX_FULLROWSELECT|/*LVS_EX_INFOTIP|*/WS_EX_ACCEPTFILES;
	if (!CreateEx(dwExStyle, dwStyle,rect, pParentWnd, nID))
	{
		return FALSE;
	}
	// 当鼠标指向某一行时变成手形
	//SetExtendedStyle(dwExStyle);
	SetExtendedStyle(
		LVS_EX_TRACKSELECT | 
		LVS_EX_UNDERLINEHOT |
		LVS_EX_ONECLICKACTIVATE |
		LVS_EX_FULLROWSELECT );

	HCURSOR hCur = ::LoadCursor( NULL,MAKEINTRESOURCE(32649) ); /* IDC_HAND */
	SetHotCursor( hCur );
	// 

	CImageList imageList;
	imageList.Create(22, 22, ILC_COLORDDB|ILC_MASK, 2, 2);
	SetImageList(&imageList, LVSIL_SMALL);
	return TRUE;
}

// 设置高度
void CiFilesList::SetItemHeight(int nHeight)
{
	CImageList imageList;
	imageList.Create(nHeight, nHeight, ILC_COLORDDB|ILC_MASK, 2, 2);
	SetImageList(&imageList, LVSIL_SMALL);
}
// 文件拖放
void CiFilesList::OnDropFiles(HDROP hDropInfo)    
{ 
	char szFilePathName[_MAX_PATH+1]    =    {0};
	//得到文件个数       
	UINT nNumOfFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	for (int i=0 ; i< nNumOfFiles; i++)
	{
		//　得到文件名    
		DragQueryFile(hDropInfo,i, (LPTSTR)szFilePathName, _MAX_PATH);
		CString szLink=ExpandShortcut(szFilePathName);
		if (szLink==_T(""))
		{
			CString fileName=szFilePathName;
			fileName=fileName.Left(fileName.ReverseFind('.'));
			fileName=fileName.Right(fileName.GetLength()-fileName.ReverseFind('\\')-1);
			GetParent()->SendMessage(WM_MYDROPFILES,(WPARAM)szFilePathName,(LPARAM)fileName.GetBuffer());
		}
		else
		{
			CString fileName=szFilePathName;
			fileName=fileName.Left(fileName.ReverseFind('.'));
			fileName=fileName.Right(fileName.GetLength()-fileName.ReverseFind('\\')-1);
			GetParent()->SendMessage(WM_MYDROPFILES,(WPARAM)szLink.GetBuffer(),(LPARAM)fileName.GetBuffer());
		}    
	}
	DragFinish(hDropInfo);
	CListCtrl::OnDropFiles(hDropInfo);    
} 



// 移动项目
bool CiFilesList::MoveItem(bool bUp, int nCount)
{
	POSITION pos =GetFirstSelectedItemPosition();
	int nSel=GetSelectedCount();
	if (nSel==0)
	{
		return false;
	}
	int fPos=GetNextSelectedItem(pos);
	int nCol=GetHeaderCtrl()->GetItemCount();
	CString szTmp;
	if (bUp)
	{
		int nPos=fPos-nCount;
		nPos=nPos>0?nPos:0;
		for(int i=0;i<nSel;i++)
		{
			int nIndex=InsertItem(nPos+i,GetItemText(fPos+i,0));
			for (int n=1;n<nCol;n++)
			{
				SetItemText(nIndex,n,GetItemText(fPos+i+1,n));
			}
			SetItemState(nIndex,LVNI_SELECTED,LVNI_SELECTED);
			DeleteItem(fPos+1+i);
		}
	}
	else
	{
		int nPos=nCount+nSel+fPos;
		nPos=nPos>GetItemCount()?GetItemCount():nPos;
		for(int i=0;i<nSel;i++)
		{
			int nIndex=InsertItem(nPos,GetItemText(fPos,0));
			for (int n=1;n<nCol;n++)
			{
				SetItemText(nIndex,n,GetItemText(fPos,n));
			}
			SetItemState(nIndex,LVNI_SELECTED,LVNI_SELECTED);
			DeleteItem(fPos);
		}

	}
	return false;
}

void CiFilesList::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem==-1)
	{
		return ;
	}
	ShellExecute(NULL,_T("open"),GetItemText(pNMItemActivate->iItem,0),NULL,NULL,SW_NORMAL);
	*pResult = 0;
}
