// iButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "iButton.h"


// CiButton

IMPLEMENT_DYNAMIC(CiButton, CButton)

CiButton::CiButton()
:m_bOver(false)
, m_bTrans(false)
,m_TransparentColor(RGB(0,255,0))
,m_nTextHeight(0)
, m_nPicWidth(0)
,m_BackColor(0)
, m_nPicHeight(0)
, m_bTextBottom(false)
{
	m_bitMap.m_hObject=NULL;
	m_dcTemp.m_hDC=NULL;
	m_pOldBitmap=NULL;
}

CiButton::~CiButton()
{
	if (m_dcTemp.m_hDC!=NULL)
	{
		m_dcTemp.SelectObject(m_pOldBitmap);
		m_dcTemp.DeleteDC();
	}
}


BEGIN_MESSAGE_MAP(CiButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CiButton ��Ϣ�������


// �����Ի�����
void CiButton::PreSubclassWindow()
{
	ModifyStyle( 0, BS_OWNERDRAW );
	ModifyStyleEx(0,WS_EX_TRANSPARENT);
	CButton::PreSubclassWindow();
}
void CiButton::RelayEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(NULL != m_tooltip.m_hWnd)
	{
		MSG msg;
		msg.hwnd = m_hWnd;
		msg.message = message;
		msg.wParam = wParam;
		msg.lParam = lParam;
		msg.time = 0;
		msg.pt.x = LOWORD(lParam);
		msg.pt.y = HIWORD(lParam);
		m_tooltip.RelayEvent(&msg);
	}
}

// ����ɫ
BOOL CiButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
// ��ť����
bool CiButton::DrawBitmap(CDC* pDC, int nIndex, CRect rect)
{
	if (m_dcTemp.m_hDC==NULL&&m_bitMap.m_hObject!=NULL)
	{
		m_dcTemp.CreateCompatibleDC(pDC);
		m_pOldBitmap = m_dcTemp.SelectObject(&m_bitMap);
	}
	if (m_bTrans)
	{
		pDC->FillSolidRect(&rect,m_BackColor);
		TransparentBlt(pDC->GetSafeHdc(),rect.left,rect.top,rect.Width(),rect.Height(),m_dcTemp.GetSafeHdc(),
			nIndex*m_nPicWidth,0,m_nPicWidth,m_nPicHeight,m_TransparentColor);
	}
	else
	{
		pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&m_dcTemp,
			nIndex*m_nPicWidth,0,m_nPicWidth,m_nPicHeight,SRCCOPY);
	}
	return true;
}
// �Ի�
void CiButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);	// get device context
	if ((GetState() & BST_PUSHED) == BST_PUSHED) // ����
	{
		DrawBitmap(pDC,2,m_PicRect);
	}
	if((ODS_SELECTED & lpDrawItemStruct->itemState) ) // ѡ��
	{
		DrawBitmap(pDC,3,m_PicRect);
	}else
	if (lpDrawItemStruct->itemState&ODS_DISABLED)     // ʧȥ����
	{
		DrawBitmap(pDC,4,m_PicRect);
	} else if (m_bOver) // ������
	{
		DrawBitmap(pDC,1,m_PicRect);
	}
	else 
	{
		if (!m_bOver&&lpDrawItemStruct->itemState&ODS_FOCUS) // ����
		{
			DrawBitmap(pDC,3,m_PicRect);
		}
		else // �뿪->��ͨ
		{
			DrawBitmap(pDC,0,m_PicRect);
		}
	}
	CString szCaption;
	GetWindowText(szCaption);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(szCaption,&m_TextRect,DT_SINGLELINE |DT_CENTER  | DT_VCENTER | DT_END_ELLIPSIS);
}


void CiButton::OnMouseMove(UINT nFlags, CPoint point)
{
	RelayEvent(WM_MOUSEMOVE,(WPARAM)nFlags,MAKELPARAM(LOWORD(point.x),LOWORD(point.y)));
	if (!m_bOver) {
		TRACKMOUSEEVENT t = {
			sizeof(TRACKMOUSEEVENT),
			TME_LEAVE,
			m_hWnd,
			0
		};
		if (::_TrackMouseEvent(&t)) 
		{
			m_bOver = true;
			Invalidate();
		}
	}
	CButton::OnMouseMove(nFlags, point);
}

void CiButton::OnMouseLeave()
{
	m_bOver = false;
	Invalidate();
	CButton::OnMouseLeave();
}

// ----------------------------�ӿ�----------------------------
// ��̬����
BOOL CiButton::Create(LPCTSTR lpszCaption,CRect rect, CWnd* pParentWnd, UINT nID)
{
	DWORD dwStyle=WS_CHILD|WS_VISIBLE;
	if (!CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID))
	{
		return FALSE;
	}
	return TRUE;
}
// ���ù�����ʾ�ı�
void CiButton::SetToolTipText(CString szText)
{
	if(m_tooltip.m_hWnd==NULL)
	{
		if(m_tooltip.Create(this))
		{
			if(m_tooltip.AddTool(this, (LPCTSTR)szText))
			{
				m_tooltip.Activate(1);
			}
		}
	} 
	else 
	{
		m_tooltip.UpdateTipText((LPCTSTR)szText,this);
	}
}
// �����ı�����ǰ��ɫ
void CiButton::SetToolTipColor(COLORREF crText, COLORREF crBkgnd)
{
	if(m_tooltip.m_hWnd != NULL)
	{
		m_tooltip.SetTipTextColor(crText);
		m_tooltip.SetTipBkColor(crBkgnd);
	}
}
// ����ͼ��
bool CiButton::LoadBitmaps(int nImage,int nWidth)
{
	m_bitMap.DeleteObject();
	m_bitMap.LoadBitmap(nImage);
	if (m_bitMap.m_hObject==NULL)
	{
		return false;
	}
	BITMAP bitmap;
	m_bitMap.GetBitmap(&bitmap);
	//GetObject(hImage,sizeof(BITMAP),&bitmap);
	m_nPicHeight=bitmap.bmHeight;
	m_nPicWidth=nWidth==0?bitmap.bmHeight:nWidth;
	// ����߶�
	CClientDC dc(this);
	TEXTMETRIC TextM;
	dc.GetTextMetrics(&TextM);
	m_nTextHeight=TextM.tmHeight;
	// ����
	GetClientRect(&m_PicRect);
	m_TextRect=m_PicRect;
	return true;
}
// ����ͼ��
bool CiButton::LoadBitmaps(CString szImage,int nWidth)
{
	m_bitMap.DeleteObject();
	if(!m_bitMap.Attach((HBITMAP)::LoadImage(NULL,szImage,
		IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION|LR_LOADFROMFILE|LR_DEFAULTSIZE)))
	{
		return false;
	}
	BITMAP bitmap;
	m_bitMap.GetBitmap(&bitmap);
	//GetObject(hImage,sizeof(BITMAP),&bitmap);
	m_nPicHeight=bitmap.bmHeight;
	m_nPicWidth=nWidth==0?bitmap.bmHeight:nWidth;
	// ����߶�
	CClientDC dc(this);
	TEXTMETRIC TextM;
	dc.GetTextMetrics(&TextM);
	m_nTextHeight=TextM.tmHeight;
	// ����
	GetClientRect(&m_PicRect);
	m_TextRect=m_PicRect;
	return true;
}

// ����������ʾ��ʽ
void CiButton::SetTextShowBottom()
{
	GetClientRect(&m_PicRect);
	m_TextRect=m_PicRect;
	m_PicRect.bottom-=m_nTextHeight;
	m_TextRect.top=m_PicRect.bottom;
	m_bTextBottom=true;
}
// ����͸��ɫ

void CiButton::SetTransColor(COLORREF TransColor,COLORREF BkColor)
{
	m_bTrans=true;
	m_TransparentColor=TransColor;
	m_BackColor=BkColor;
}

// ��ť�ߴ���ӦͼƬ
void CiButton::SizeToContent(void)
{
	if (m_bitMap.m_hObject==NULL)
	{
		return;
	}
	int nHeight=m_nPicHeight;
	m_PicRect.bottom=nHeight;
	m_PicRect.right=m_nPicWidth;
	if (m_bTextBottom)
	{
		nHeight+=m_nTextHeight;
		m_TextRect.right=m_nPicWidth;
		m_TextRect.top=m_PicRect.bottom;
		m_TextRect.bottom=nHeight;
	}
	SetWindowPos(NULL, 0, 0, m_nPicWidth,nHeight,SWP_NOMOVE|SWP_NOZORDER|SWP_NOREDRAW|SWP_NOACTIVATE);
}
