#include "StdAfx.h"
#include "ConfigBar.h"
#include "resource.h"
#include "MainFrm.h"
#include "SuperServerDoc.h"
#include "SuperServerView.h"

CConfigBar::CConfigBar(void)
:m_pSerCfig(NULL)
//,m_pComCfig(NULL)
{
}

CConfigBar::~CConfigBar(void)
{
	/*if (m_pComCfig!=NULL)
	{
		delete m_pComCfig;
	}*/
	if (m_pSerCfig!=NULL)
	{
		delete m_pSerCfig;
	}
}
BEGIN_MESSAGE_MAP(CConfigBar, CScrollWnd)
	ON_WM_CREATE()
	ON_CONTROL_RANGE(BN_CLICKED, 21, 30, OnButtonClick)
END_MESSAGE_MAP()

int CConfigBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_pSerCfig=new CiButton;
	if (m_pSerCfig==NULL)
	{
		return -1;
	}
	int nLeft=40,nHeight=20;
	m_pSerCfig->Create(_T("服务配置"),CRect(nLeft,nHeight,0,0),this,21);
	m_pSerCfig->LoadBitmaps(IDB_CFGSER);
	m_pSerCfig->SetTextShowBottom();
	m_pSerCfig->SizeToContent();
	m_pSerCfig->SetTransColor(RGB(192,192,192),RGB(213,228,242));
	m_pSerCfig->SetToolTipText("配置本地服务参数.");

	//m_pComCfig=new CiButton;
	//if (m_pComCfig==NULL)
	//{
	//	return -1;
	//}
	//nHeight+=nHeight+80;
	//m_pComCfig->Create(_T("配置"),CRect(nLeft,nHeight,0,0),this,22);
	//m_pComCfig->LoadBitmaps(IDB_CFGCOM);
	//m_pComCfig->SetTextShowBottom();
	//m_pComCfig->SizeToContent();
	//m_pComCfig->SetTransColor(RGB(192,192,192),RGB(213,228,242));
	//m_pComCfig->SetToolTipText("修改其他配置参数.");
	nHeight+=nHeight+80;
	nLeft+=nLeft+64;
	SetScrollWH(nLeft,nHeight);
	return 0;
}
void CConfigBar::OnButtonClick(UINT nID)
{
	CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	if (pFrame==NULL)
	{
		return;
	}
	if (nID==20)
	{
		pFrame->SendMessage(WM_SETSTATUSTEXT,(WPARAM)"打开本地服务配置管理...",0);
	}else if (nID==21)
	{
		pFrame->SendMessage(WM_SETSTATUSTEXT,(WPARAM)"打开配置管理...",0);
	}
	CSuperServerView* pView=(CSuperServerView*)pFrame->GetActiveView();
	if (pView==NULL)
	{
		return;
	}
	pView->SendMessage(WM_NavButtonClick,nID,0);
}