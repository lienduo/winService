#include "StdAfx.h"
#include "MonitorBar.h"
#include "resource.h"
#include "MainFrm.h"
#include "SuperServerDoc.h"
#include "SuperServerView.h"

CMonitorBar::CMonitorBar(void)
:m_pFastMonintor(NULL)
,m_pLocalMonitor(NULL)
{
}

CMonitorBar::~CMonitorBar(void)
{
	if (m_pLocalMonitor!=NULL)
	{
		delete m_pLocalMonitor;
	}
	if (m_pFastMonintor!=NULL)
	{
		delete m_pFastMonintor;
	}
}
BEGIN_MESSAGE_MAP(CMonitorBar, CScrollWnd)
	ON_WM_CREATE()
	ON_CONTROL_RANGE(BN_CLICKED, 11, 20, OnButtonClick)
END_MESSAGE_MAP()

int CMonitorBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_pLocalMonitor=new CiButton;
	if (m_pLocalMonitor==NULL)
	{
		return -1;
	}
	int nLeft=40,nHeight=20;
	m_pLocalMonitor->Create(_T("本地监控"),CRect(nLeft,nHeight,10,10),this,11);
	m_pLocalMonitor->LoadBitmaps(IDB_MONITORLOCAL);
	m_pLocalMonitor->SetTextShowBottom();
	m_pLocalMonitor->SizeToContent();
	m_pLocalMonitor->SetTransColor(RGB(192,192,192),RGB(213,228,242));
	m_pLocalMonitor->SetToolTipText("监控本地服务状态.");
	m_pFastMonintor=new CiButton;
	if (m_pFastMonintor==NULL)
	{
		return -1;
	}
	nHeight+=nHeight+80;
	m_pFastMonintor->Create(_T("远程监控"),CRect(nLeft,nHeight,0,0),this,12);
	m_pFastMonintor->LoadBitmaps(IDB_MONITORFAST);
	m_pFastMonintor->SetTextShowBottom();
	m_pFastMonintor->SizeToContent();
	m_pFastMonintor->SetTransColor(RGB(192,192,192),RGB(213,228,242));
	m_pFastMonintor->SetToolTipText("监控远程服务状态.");
	nHeight+=nHeight+80;
	nLeft+=nLeft+64;
	SetScrollWH(nLeft,nHeight);

	return 0;
}
void CMonitorBar::OnButtonClick(UINT nID)
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	if (pFrame==NULL)
	{
		return;
	}
	if (nID==11)
	{
		pFrame->SendMessage(WM_SETSTATUSTEXT,(WPARAM)"打开本地服务监控...",0);
	}else if (nID==12)
	{
		pFrame->SendMessage(WM_SETSTATUSTEXT,(WPARAM)"打开远程服务监控...",0);
	}
	CSuperServerView* pView=(CSuperServerView*)pFrame->GetActiveView();
	if (pView==NULL)
	{
		return;
	}
	pView->SendMessage(WM_NavButtonClick,nID,0);
}