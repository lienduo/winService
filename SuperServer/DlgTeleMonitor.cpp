// DlgTeleMonitor.cpp : 实现文件
//

#include "stdafx.h"
#include "SuperServer.h"
#include "DlgTeleMonitor.h"


// CDlgTeleMonitor 对话框

IMPLEMENT_DYNAMIC(CDlgTeleMonitor, CDialog)

CDlgTeleMonitor::CDlgTeleMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTeleMonitor::IDD, pParent)
{

}

CDlgTeleMonitor::~CDlgTeleMonitor()
{
}

void CDlgTeleMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTeleMonitor, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgTeleMonitor 消息处理程序

HBRUSH CDlgTeleMonitor::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)  //静态文本颜色，并且指定控件ID号
	{
		pDC->SetTextColor(RGB(0,0,0));
		//pDC->SetBkColor(RGB(191,219,255));
		pDC->SetBkMode(TRANSPARENT);
		hbr=(HBRUSH)m_brush;
	}
	if (nCtlColor==CTLCOLOR_DLG)
	{
		hbr=(HBRUSH)m_brush;
	}
	return hbr;
}
BOOL CDlgTeleMonitor::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_brush.CreateSolidBrush(RGB(213,228,242));
	return TRUE;
}


BOOL CDlgTeleMonitor::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(213,228,242));
	CPen NewPen;
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor =RGB(255,0,0);
	NewPen.CreatePen(PS_DOT|PS_GEOMETRIC|PS_ENDCAP_ROUND, 5, &logBrush);
	CPen *pOldPen=pDC->SelectObject(&NewPen);
	pDC->SelectStockObject(NULL_BRUSH); 
	pDC->Rectangle(rect);
	pDC->SelectObject(pOldPen); 
	return TRUE;
}
