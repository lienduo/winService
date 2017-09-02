// DlgMsg.cpp : 实现文件
//

#include "stdafx.h"
#include "SuperServer.h"
#include "DlgMsg.h"


// CDlgMsg 对话框

IMPLEMENT_DYNAMIC(CDlgMsg, CDialog)

CDlgMsg::CDlgMsg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMsg::IDD, pParent)
	, m_szMsg(_T(""))
	, m_szCaption(_T("系统提示..."))
{
}

CDlgMsg::~CDlgMsg()
{
}

void CDlgMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_OKBt);
	DDX_Control(pDX, IDCANCEL, m_CalBt);
}


BEGIN_MESSAGE_MAP(CDlgMsg, CDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgMsg 消息处理程序

void CDlgMsg::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	if (m_szMsg!=_T(""))
	{
		CRect rect;
		GetClientRect(&rect);
		rect.top+=35;
		rect.left+=25;
		rect.right-=25;
		rect.bottom-=30;
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(m_szMsg,&rect,DT_WORDBREAK | DT_EDITCONTROL |DT_LEFT  | DT_VCENTER | DT_END_ELLIPSIS);
	}
}

BOOL CDlgMsg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(213,228,242));
	return TRUE;
}
BOOL CDlgMsg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 初始化
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	if(hIcon)
	{
		SendMessage(WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	}
	SetWindowText(m_szCaption);
	m_OKBt.LoadBitmaps(IDB_DEFBUTTON,88);
	m_CalBt.LoadBitmaps(IDB_DEFBUTTON,88);
	return TRUE;
}
