
// SuperServerView.cpp : CSuperServerView ���ʵ��
//

#include "stdafx.h"
#include "SuperServer.h"

#include "SuperServerDoc.h"
#include "SuperServerView.h"
#include "DlgMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSuperServerView

IMPLEMENT_DYNCREATE(CSuperServerView, CFormView)

BEGIN_MESSAGE_MAP(CSuperServerView, CFormView)
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_NavButtonClick, OnClickNavButton)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BT_CLEARINFO, &CSuperServerView::OnBnClickedBtClearinfo)
END_MESSAGE_MAP()

// CSuperServerView ����/����

CSuperServerView::CSuperServerView()
	: CFormView(CSuperServerView::IDD)
	, m_szCaption(_T(""))
	, m_pCurDlg(NULL)
	,m_pDlgSerCtrl(NULL)
	,m_pDlgInUn(NULL)
	,m_pDlgLocalMonitor(NULL)
	,m_pDlgCfg(NULL)
	,m_pDlgTeleMonitor(NULL)
{
	// TODO: �ڴ˴���ӹ������

}

CSuperServerView::~CSuperServerView()
{
	if (m_pCurDlg!=NULL)
	{
		DelCurDlg();
	}
}

void CSuperServerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INFO, m_ListCtrl);
	DDX_Control(pDX, IDC_BT_CLEARINFO, m_ClearBt);
}

BOOL CSuperServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	/*cs.cx=800;
	cs.cy=600;*/
	return CFormView::PreCreateWindow(cs);
}

void CSuperServerView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSuperServerView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CSuperServerView ���

#ifdef _DEBUG
void CSuperServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSuperServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSuperServerDoc* CSuperServerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSuperServerDoc)));
	return (CSuperServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CSuperServerView ��Ϣ�������

// ������Ϣ
void CSuperServerView::InserInfo(CString szInfo)
{
	int nItem = m_ListCtrl.GetItemCount();
	if (nItem>=100)
	{
		while(m_ListCtrl.DeleteItem(0));
		nItem=0;
	}
	CString str;
	str.Format(_T("%d"),nItem+1);
	m_ListCtrl.InsertItem(nItem, str);
	m_ListCtrl.SetItemText(nItem, 1, CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S")));
	m_ListCtrl.SetItemText(nItem, 2, szInfo);
	m_ListCtrl.EnsureVisible(nItem,FALSE);
}

BOOL CSuperServerView::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(213,228,242));
	if (m_ListCtrl.GetSafeHwnd()==NULL)
	{
		return TRUE;
	}
	m_ListCtrl.GetWindowRect(&rect);
	ScreenToClient(&rect);
	rect.top-=5;
	rect.left-=5;
	rect.right+=5;
	rect.bottom+=5;
	CPen NewPen;
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor =RGB(255,0,0);
	NewPen.CreatePen(PS_DOT|PS_GEOMETRIC|PS_ENDCAP_ROUND, 4, &logBrush);
	CPen *pOldPen=pDC->SelectObject(&NewPen);
	pDC->SelectStockObject(NULL_BRUSH); 
	pDC->Rectangle(rect);
	rect.top-=60;
	rect.bottom=rect.top+25;
	rect.left+=90;
	rect.right-=90;
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(160,10,10));
	pDC->DrawText(_T("**************������Ϣ**************"),
		&rect,DT_SINGLELINE |DT_CENTER  | DT_VCENTER | DT_END_ELLIPSIS);
	m_RectInfo=rect;
	m_RectInfo.top+=25;
	m_RectInfo.left+=30;
	m_RectInfo.bottom=m_RectInfo.top+25;
	m_RectInfo.right-=30;
	pDC->DrawText(_T("-------")+m_szCaption,
		&m_RectInfo,DT_SINGLELINE |DT_CENTER  | DT_VCENTER | DT_END_ELLIPSIS);
	//m_RectInfo=
	pDC->SelectObject(pOldPen); 
	return TRUE; //CFormView::OnEraseBkgnd(pDC);
}
void CSuperServerView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	SetCtrlPos(cx,cy);
}
// �����Ϣ

void CSuperServerView::OnBnClickedBtClearinfo()
{
	while(m_ListCtrl.DeleteItem(0));
}
// ����
LRESULT CSuperServerView::OnClickNavButton(WPARAM wParam, LPARAM lParam)
{
	m_ListCtrl.ShowWindow(SW_SHOW);
	m_ClearBt.ShowWindow(SW_SHOW);
	switch ((int)wParam)
	{
	case 1: // �������
		{
			if (m_pDlgSerCtrl==NULL)
			{
				if (m_pCurDlg!=NULL)
				{
					DelCurDlg();
				}
				m_pDlgSerCtrl=new CDlgSerCtrl;
				m_pDlgSerCtrl->Create(CDlgSerCtrl::IDD,this);
				m_pDlgSerCtrl->ShowWindow(SW_SHOW);
				m_pCurDlg=m_pDlgSerCtrl;
				m_szCaption=_T("�������");
				InvalidateRect(&m_RectInfo);
				SetCtrlPos();
			}
		}
		break;
	case 2: // ����װ/ж��
		{
			if (m_pDlgInUn==NULL)
			{
				if (m_pCurDlg!=NULL)
				{
					DelCurDlg();
				}
				m_pDlgInUn=new CDlgInUn;
				m_pDlgInUn->Create(CDlgInUn::IDD,this);
				m_pDlgInUn->ShowWindow(SW_SHOW);
				m_pCurDlg=m_pDlgInUn;
				m_szCaption=_T("����װ/ж��");
				InvalidateRect(&m_RectInfo);
				SetCtrlPos();
			}
		}
		break;
	case 11:// ���ؼ��
		{
			if (m_pDlgLocalMonitor==NULL)
			{
				if (m_pCurDlg!=NULL)
				{
					DelCurDlg();
				}
				m_pDlgLocalMonitor=new CDlgLocalMonitor;
				m_pDlgLocalMonitor->Create(CDlgLocalMonitor::IDD,this);
				m_pDlgLocalMonitor->ShowWindow(SW_SHOW);
				m_pCurDlg=m_pDlgLocalMonitor;
				m_szCaption=_T("���ؼ��");
				InvalidateRect(&m_RectInfo);
				SetCtrlPos();
			}
		}
		break;
	case 12:// Զ�̼��
		{
			if (m_pDlgTeleMonitor==NULL)
			{
				if (m_pCurDlg!=NULL)
				{
					DelCurDlg();
				}
				m_pDlgTeleMonitor=new CDlgTeleMonitor;
				m_pDlgTeleMonitor->Create(CDlgTeleMonitor::IDD,this);
				m_pDlgTeleMonitor->ShowWindow(SW_SHOW);
				m_pCurDlg=m_pDlgTeleMonitor;
				m_szCaption=_T("Զ�̼��");
				InvalidateRect(&m_RectInfo);
				SetCtrlPos();
			}
		}
		break;
	case 21:// ��������
		{
			if (m_pDlgCfg==NULL)
			{
				if (m_pCurDlg!=NULL)
				{
					DelCurDlg();
				}
				m_pDlgCfg=new CDlgCfg;
				m_pDlgCfg->Create(CDlgCfg::IDD,this);
				m_pDlgCfg->ShowWindow(SW_SHOW);
				m_pCurDlg=m_pDlgCfg;
				SetCtrlPos();
			}
			m_ListCtrl.ShowWindow(SW_HIDE);
			m_ClearBt.ShowWindow(SW_HIDE);
		}
		break;
	case 22:// ��������
		{
		}
		break;
	default:
		break;
	}
	return 0;
}
// ��ʼ���ؼ�
void CSuperServerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();
	m_ListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP);
	m_ListCtrl.SetBkColor(RGB(213,228,242));
	m_ListCtrl.SetTextBkColor(RGB(213,228,242));
	m_ListCtrl.InsertColumn(0,_T("ID"),LVCFMT_CENTER,50);
	m_ListCtrl.InsertColumn(1,_T("ʱ��"),LVCFMT_CENTER,130);
	m_ListCtrl.InsertColumn(2,_T("��Ϣ"),LVCFMT_LEFT,480);

	// �����ť
	m_ClearBt.LoadBitmaps(IDB_DEFBUTTON,88);
	SetCtrlPos();
}

// ���ÿؼ�λ��
void CSuperServerView::SetCtrlPos(int cx, int cy)
{
	if (m_ListCtrl.GetSafeHwnd()==NULL)
	{
		return;
	}
	if (cx==0)
	{
		CRect rect;
		GetClientRect(&rect);
		cx=rect.Width();
		cy=rect.Height();
	}
	
	BOOL bHasHorzBar=FALSE,bHasVertBar=FALSE;
	CheckScrollBars(bHasHorzBar,bHasVertBar);
	if (bHasHorzBar)
	{
		// ˮƽ
		SCROLLINFO scrollinfo;
		GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
		cx=scrollinfo.nMax;
	}
	if (bHasVertBar)
	{
		// ��ֱ
		SCROLLINFO scrollinfo;
		GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		cy=scrollinfo.nMax;
	}
	m_ListCtrl.SetWindowPos(NULL,12,70,cx-24,cy-220,SWP_NOACTIVATE);
	m_ClearBt.SetWindowPos(NULL,cx-100,15,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	CRect rect;
	if (m_pDlgSerCtrl!=NULL)
	{
		m_pDlgSerCtrl->GetClientRect(&rect);
		m_pDlgSerCtrl->SetWindowPos(NULL,(cx-rect.Width())/2,cy-rect.Height(),0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	}
	if (m_pDlgInUn!=NULL)
	{
		m_pDlgInUn->GetClientRect(&rect);
		m_pDlgInUn->SetWindowPos(NULL,(cx-rect.Width())/2,cy-rect.Height(),0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	}
	if (m_pDlgLocalMonitor!=NULL)
	{
		m_pDlgLocalMonitor->GetClientRect(&rect);
		m_pDlgLocalMonitor->SetWindowPos(NULL,(cx-rect.Width())/2,cy-rect.Height(),0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	}
	if (m_pDlgTeleMonitor!=NULL)
	{
		m_pDlgTeleMonitor->GetClientRect(&rect);
		m_pDlgTeleMonitor->SetWindowPos(NULL,(cx-rect.Width())/2,cy-rect.Height(),0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	}
	if (m_pDlgCfg!=NULL)
	{
		m_pDlgCfg->SetWindowPos(NULL,1,1,cx-2,cy-2,SWP_NOACTIVATE);
	}
}


// ɾ����ǰ
void CSuperServerView::DelCurDlg()
{
	if (m_pCurDlg==NULL)
	{
		return;
	}
	if (m_pCurDlg==m_pDlgSerCtrl)
	{
		delete m_pDlgSerCtrl;
		m_pDlgSerCtrl=NULL;
	}
	if (m_pCurDlg==m_pDlgInUn)
	{
		delete m_pDlgInUn;
		m_pDlgInUn=NULL;
	}
	if (m_pCurDlg==m_pDlgLocalMonitor)
	{
		delete m_pDlgLocalMonitor;
		m_pDlgLocalMonitor=NULL;
	}
	if (m_pCurDlg==m_pDlgTeleMonitor)
	{
		delete m_pDlgTeleMonitor;
		m_pDlgTeleMonitor=NULL;
	}
	if (m_pCurDlg==m_pDlgCfg)
	{
		delete m_pDlgCfg;
		m_pDlgCfg=NULL;
	}
}
