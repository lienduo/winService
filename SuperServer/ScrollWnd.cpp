// ScrollWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "SuperServer.h"
#include "ScrollWnd.h"


// CScrollWnd

IMPLEMENT_DYNAMIC(CScrollWnd, CWnd)

CScrollWnd::CScrollWnd()
: m_cx(200)
, m_cy(300)
, m_xFistChange(false)
,m_yFistChange(false)
{

}

CScrollWnd::~CScrollWnd()
{
}


BEGIN_MESSAGE_MAP(CScrollWnd, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CScrollWnd 消息处理程序


// 背景色设置
BOOL CScrollWnd::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(213,228,242));
	return TRUE;
	// return CWnd::OnEraseBkgnd(pDC);
}

int CScrollWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

BOOL CScrollWnd::Create(CWnd* pParentWnd,CRect rect)
{
	DWORD dwStyle =WS_VISIBLE|WS_CHILD;
	if(!CWnd::Create(NULL,NULL,dwStyle,rect,pParentWnd,0))
	{
		return FALSE;
	}
	return TRUE;
}

// 水平滚动
void CScrollWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
	int nCurPos=scrollinfo.nPos;
	int nTrack=0;
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		ScrollWindow((scrollinfo.nPos-scrollinfo.nMin)*10,0);
		scrollinfo.nPos = scrollinfo.nMin;
		SetScrollInfo(SB_HORZ,&scrollinfo);
		break;

	case SB_RIGHT:      // Scroll to far right.
		ScrollWindow((scrollinfo.nPos-scrollinfo.nMax)*10,0);
		scrollinfo.nPos = scrollinfo.nMax;
		SetScrollInfo(SB_HORZ,&scrollinfo);
		break;

	case SB_ENDSCROLL:   // End scroll.
		break;

	case SB_LINELEFT:      // Scroll left.
		{
			scrollinfo.nPos -= 5;
			if (scrollinfo.nPos<scrollinfo.nMin)
			{
				scrollinfo.nPos = scrollinfo.nMin;
				SetScrollInfo(SB_HORZ,&scrollinfo);
				ScrollWindow(nCurPos,0);
				break;
			}
			SetScrollInfo(SB_HORZ,&scrollinfo);
			ScrollWindow(5,0);
		}
		break;

	case SB_LINERIGHT:   // Scroll right.
		{
			scrollinfo.nPos += 5;
			nTrack=scrollinfo.nMax-scrollinfo.nPage+1;
			if (scrollinfo.nPos>nTrack)
			{
				ScrollWindow(scrollinfo.nPos-5-nTrack,0);
				scrollinfo.nPos = nTrack;
				SetScrollInfo(SB_HORZ,&scrollinfo);
				break;
			}
			SetScrollInfo(SB_HORZ,&scrollinfo);
			ScrollWindow(-5,0);
		}
		break;

	case SB_PAGELEFT:    // Scroll one page left.
		{
			scrollinfo.nPos -= 5;
			if (scrollinfo.nPos<scrollinfo.nMin)
			{
				scrollinfo.nPos = scrollinfo.nMin;
				break;
			}
			SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
			ScrollWindow(5,0);
		}
		break;

	case SB_PAGERIGHT:      // Scroll one page right.
		{
			scrollinfo.nPos += 5;
			nTrack=scrollinfo.nMax-scrollinfo.nPage+1;
			if (scrollinfo.nPos>nTrack)
			{
				ScrollWindow(scrollinfo.nPos-5-nTrack,0);
				scrollinfo.nPos =nTrack;
				SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
				break;
			}
			SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
			ScrollWindow(-5,0);
		}
		break;

	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		break;

	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		ScrollWindow((scrollinfo.nPos-nPos),0);
		scrollinfo.nPos = nPos;
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
		break;
	}

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

// 竖直滚动
void CScrollWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
	int nCurPos=scrollinfo.nPos;
	int nTrack=0;
	switch (nSBCode)
	{
	case SB_BOTTOM:
		ScrollWindow(0,scrollinfo.nPos-scrollinfo.nMax);
		scrollinfo.nPos = scrollinfo.nMax;
		SetScrollInfo(SB_VERT,&scrollinfo);
		break;
	case SB_TOP:
		ScrollWindow(0,scrollinfo.nPos-scrollinfo.nMin);
		scrollinfo.nPos = scrollinfo.nMin;
		SetScrollInfo(SB_VERT,&scrollinfo);
		break;
	case SB_LINEUP:
		scrollinfo.nPos -= 5;
		if (scrollinfo.nPos<scrollinfo.nMin)
		{
			scrollinfo.nPos = scrollinfo.nMin;
			SetScrollInfo(SB_VERT,&scrollinfo);
			ScrollWindow(0,nCurPos);
			break;
		}
		SetScrollInfo(SB_VERT,&scrollinfo);
		ScrollWindow(0,5);
		break;
	case SB_LINEDOWN:
		{
			scrollinfo.nPos += 5;
			nTrack=scrollinfo.nMax-scrollinfo.nPage+1;
			if (scrollinfo.nPos>nTrack)
			{
				ScrollWindow(0,scrollinfo.nPos-5-nTrack);
				scrollinfo.nPos =nTrack;
				SetScrollInfo(SB_VERT,&scrollinfo);
				break;
			}
			SetScrollInfo(SB_VERT,&scrollinfo);
			ScrollWindow(0,-5);
		}
		break;
	case SB_PAGEUP:
		scrollinfo.nPos -= 5;
		if (scrollinfo.nPos<scrollinfo.nMin)
		{
			scrollinfo.nPos = scrollinfo.nMin;
			break;
		}
		SetScrollInfo(SB_VERT,&scrollinfo);
		ScrollWindow(0,5);
		break;
	case SB_PAGEDOWN:
		{
			scrollinfo.nPos += 5;
			nTrack=scrollinfo.nMax-scrollinfo.nPage+1;
			if (scrollinfo.nPos>nTrack)
			{
				ScrollWindow(0,scrollinfo.nPos-5-nTrack);
				scrollinfo.nPos=nTrack;
				SetScrollInfo(SB_VERT,&scrollinfo);
				break;
			}
			SetScrollInfo(SB_VERT,&scrollinfo);
			ScrollWindow(0,-5);
		}
		break;
	case SB_ENDSCROLL:
		// MessageBox("SB_ENDSCROLL");
		break;
	case SB_THUMBPOSITION:
		// ScrollWindow(0,(scrollinfo.nPos-nPos)*10);
		// scrollinfo.nPos = nPos;
		// SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		break;
	case SB_THUMBTRACK:
		ScrollWindow(0,scrollinfo.nPos-nPos);
		scrollinfo.nPos = nPos;
		SetScrollInfo(SB_VERT,&scrollinfo);
		break;
	}
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

// 设置滚动条
void CScrollWnd::SetScroll(int cx, int cy)
{
	SCROLLINFO scrollinfo;
	scrollinfo.fMask=SIF_ALL;
	scrollinfo.cbSize = sizeof (scrollinfo) ;
	GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);// 水平滚动条
	scrollinfo.nMin=0;
	scrollinfo.nMax=m_cx;
	scrollinfo.nPage=cx;
	if (!m_xFistChange&&scrollinfo.nPos!=0&&cx>m_cx)
	{
		m_xFistChange=true;
		ScrollWindow(scrollinfo.nPos,0);
		scrollinfo.nPos=0;
		SetScrollInfo(SB_HORZ,&scrollinfo);
	}
	else
	{
		m_xFistChange=false;
		SetScrollInfo(SB_HORZ,&scrollinfo);
	}
	GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);// 竖直滚动条
	scrollinfo.nMax=m_cy;
	scrollinfo.nPage=cy;
	if (!m_yFistChange&&scrollinfo.nPos!=0&&cy>m_cy)
	{
		m_yFistChange=true;
		ScrollWindow(0,scrollinfo.nPos);
		scrollinfo.nPos=0;
		SetScrollInfo(SB_VERT,&scrollinfo);
	}
	else
	{
		m_yFistChange=false;
		SetScrollInfo(SB_VERT,&scrollinfo);
	}
}

void CScrollWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	SetScroll(cx,cy);
}

// 设置滚动距离
void CScrollWnd::SetScrollWH(int nWidth, int nHeight)
{
	m_cx=nWidth;
	m_cy=nHeight;
}
