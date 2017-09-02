#include "StdAfx.h"
#include "SerCtrlBar.h"
#include "MainFrm.h"
#include "SuperServerDoc.h"
#include "SuperServerView.h"

CSerCtrlBar::CSerCtrlBar(void)
:m_pCtrlSerBt(NULL)
,m_pInUnstallBt(NULL)
{
	CMainFrame * mfraim = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	if (mfraim != NULL)
	{
		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->PostMessage(WM_SETSTATUSTEXT,NULL,NULL);
	}
}

CSerCtrlBar::~CSerCtrlBar(void)
{
	if (m_pCtrlSerBt!=NULL)
	{
		delete m_pCtrlSerBt;
	}
	if (m_pInUnstallBt!=NULL)
	{
		delete m_pInUnstallBt;
	}
}
BEGIN_MESSAGE_MAP(CSerCtrlBar, CScrollWnd)
	ON_CONTROL_RANGE(BN_CLICKED, 1, 10, OnButtonClick)
	ON_WM_CREATE()
END_MESSAGE_MAP()

int CSerCtrlBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 创建代码
	m_pCtrlSerBt=new CiButton;
	if (m_pCtrlSerBt==NULL)
	{
		return -1;
	}
	int nLeft=40,nHeight=20;
	m_pCtrlSerBt->Create(_T("服务控制"),CRect(nLeft,nHeight,0,0),this,1);
	m_pCtrlSerBt->LoadBitmaps(IDB_SERCTRL);
	m_pCtrlSerBt->SetTextShowBottom();
	m_pCtrlSerBt->SizeToContent();
	m_pCtrlSerBt->SetTransColor(RGB(192,192,192),RGB(213,228,242));
	m_pCtrlSerBt->SetToolTipText("控制服务的开启/停止,暂停/继续.");
	m_pInUnstallBt=new CiButton;
	if (m_pInUnstallBt==NULL)
	{
		return -1;
	}
	nHeight+=nHeight+80;
	m_pInUnstallBt->Create(_T("安装/卸载"),CRect(nLeft,nHeight,0,0),this,2);
	m_pInUnstallBt->LoadBitmaps(IDB_INUNSTALL);
	m_pInUnstallBt->SetTextShowBottom();
	m_pInUnstallBt->SizeToContent();
	m_pInUnstallBt->SetTransColor(RGB(192,192,192),RGB(213,228,242));
	m_pInUnstallBt->SetToolTipText("控制本地服务的安装和卸载.");
	nHeight+=nHeight+80;
	nLeft+=nLeft+64;
	SetScrollWH(nLeft,nHeight);
	return 0;
}

void CSerCtrlBar::OnButtonClick(UINT nID)
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	if (pFrame==NULL)
	{
		return;
	}
	if (nID==1)
	{
		pFrame->SendMessage(WM_SETSTATUSTEXT,(WPARAM)"打开服务控制...",0);
	}else if (nID==2)
	{
		pFrame->SendMessage(WM_SETSTATUSTEXT,(WPARAM)"打开本地服务安装/卸载...",0);
	}
	CSuperServerView* pView=(CSuperServerView*)pFrame->GetActiveView();
	if (pView==NULL)
	{
		return;
	}
	pView->SendMessage(WM_NavButtonClick,nID,0);
}