// DlgSerCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "SuperServer.h"
#include "DlgSerCtrl.h"
#include "MainFrm.h"
#include "SuperServerDoc.h"
#include "SuperServerView.h"
#include "iIniOp.h"
#include "DlgMsg.h"


// CDlgSerCtrl 对话框

IMPLEMENT_DYNAMIC(CDlgSerCtrl, CDialog)

CDlgSerCtrl::CDlgSerCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSerCtrl::IDD, pParent)
	,m_pView(NULL)
{

}

CDlgSerCtrl::~CDlgSerCtrl()
{
}

void CDlgSerCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COB_SERNAME, m_ComSerCtrl);
	DDX_Control(pDX, IDC_BT_SERCTR_START, m_StartBt);
	DDX_Control(pDX, IDC_BT_SERCTR_STOP, m_StopBt);
	DDX_Control(pDX, IDC_BT_SERCTR_PAUSE, m_PauseBt);
	DDX_Control(pDX, IDC_BT_SERCTR_CONTINUE, m_ContinueBt);
}


BEGIN_MESSAGE_MAP(CDlgSerCtrl, CDialog)
	ON_BN_CLICKED(IDC_BT_SERCTR_START, &CDlgSerCtrl::OnBnClickedBtSerctrStart)
	ON_BN_CLICKED(IDC_BT_SERCTR_STOP, &CDlgSerCtrl::OnBnClickedBtSerctrStop)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BT_SERCTR_PAUSE, &CDlgSerCtrl::OnBnClickedBtSerctrPause)
	ON_BN_CLICKED(IDC_BT_SERCTR_CONTINUE, &CDlgSerCtrl::OnBnClickedBtSerctrContinue)
	ON_CBN_SELCHANGE(IDC_COB_SERNAME, &CDlgSerCtrl::OnCbnSelchangeCobSername)
END_MESSAGE_MAP()


// CDlgSerCtrl 消息处理程序

BOOL CDlgSerCtrl::OnEraseBkgnd(CDC* pDC)
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

// 设置按钮状态
void CDlgSerCtrl::SetBtStatus(void)
{
	CString szSel;
	m_ComSerCtrl.GetLBText(m_ComSerCtrl.GetCurSel(),szSel);
	if (szSel==_T(""))
	{
		return;
	}
	GetDlgItem(IDC_BT_SERCTR_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BT_SERCTR_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BT_SERCTR_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BT_SERCTR_CONTINUE)->EnableWindow(FALSE);
	char szSerName[MAX_PATH];
	char szDisName[MAX_PATH];
	CiIniOp ini;
	if (!ini.Load(_T("Config.ini")))
	{
		InsertInfo(_T("打开服务配置文件失败!!"));
		return;
	}
	ini.GetValue(szSerName,_T("SerName"),szSel.GetBuffer());
	if (szSerName[0]=='\0')
	{
		return;
	}
	ini.GetValue(szDisName,_T("SerDisplayName"),szSel.GetBuffer());
	if (szDisName[0]=='\0')
	{
		return;
	}
	m_SvrCtrl.SvrCtr_Init(szSerName,szDisName);
	if (m_SvrCtrl.SvrCtr_IsInstalled())
	{
		if (m_SvrCtrl.SvrCtr_IsRunning())
		{
			GetDlgItem(IDC_BT_SERCTR_STOP)->EnableWindow(TRUE);
			GetDlgItem(IDC_BT_SERCTR_PAUSE)->EnableWindow(TRUE);
		}
		else if (m_SvrCtrl.SvrCtr_IsPaused())
		{
			GetDlgItem(IDC_BT_SERCTR_CONTINUE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BT_SERCTR_STOP)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_BT_SERCTR_START)->EnableWindow(TRUE);
		}
		
	}
}

// 插入信息
void CDlgSerCtrl::InsertInfo(CString szInfo)
{
	if (m_pView==NULL)
	{
		CMainFrame* pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
		if (pFrame==NULL)
		{
			return;
		}
		m_pView=pFrame->GetActiveView();
		if (m_pView==NULL)
		{
			return;
		}
	}
	((CSuperServerView*)m_pView)->InserInfo(szInfo);
}
// 加载ComBox
void CDlgSerCtrl::LoadComBox(void)
{
	m_ComSerCtrl.ResetContent();
	CiIniOp ini;
	if (!ini.Load(_T("Config.ini")))
	{
		InsertInfo(_T("打开服务配置文件失败!!"));
		return;
	}
	char** pSec=NULL;
	int nSec=0;
	ini.ReadSection(&pSec,&nSec);
	for (int i=0;i<nSec;i++)
	{
		m_ComSerCtrl.AddString(pSec[i]);
	}
	ini.EndReadSection(pSec);
	m_ComSerCtrl.SetCurSel(0);
}
// 更改服务
void CDlgSerCtrl::OnCbnSelchangeCobSername()
{
	SetBtStatus();
}
BOOL CDlgSerCtrl::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 初始化
	if(!m_SvrCtrl.Load())
	{
		return FALSE;
	}
	
	LoadComBox();
	SetBtStatus();
	m_StartBt.LoadBitmaps(IDB_DEFBUTTON,88);
	m_StopBt.LoadBitmaps(IDB_DEFBUTTON,88);
	m_PauseBt.LoadBitmaps(IDB_DEFBUTTON,88);
	m_ContinueBt.LoadBitmaps(IDB_DEFBUTTON,88);

	return TRUE;
}

// 启动服务
void CDlgSerCtrl::OnBnClickedBtSerctrStart()
{
	if (m_SvrCtrl.SvrCtr_StartService())
	{
		SetBtStatus();
		InsertInfo(_T("启动服务成功!"));
	}
	else
	{
		SetBtStatus();
		InsertInfo(_T("启动服务失败!"));
	}
}
// 停止服务
void CDlgSerCtrl::OnBnClickedBtSerctrStop()
{
	CDlgMsg dlg;
	dlg.m_szCaption=_T("系统提示...");
	dlg.m_szMsg=_T("您是否要停止本服务?");
	if (IDOK!=dlg.DoModal())
	{
		return;
	}
	if (m_SvrCtrl.SvrCtr_IsPaused())
	{
		m_SvrCtrl.SvrCtr_ContinueService();
	}
	if (m_SvrCtrl.SvrCtr_StopService())
	{
		SetBtStatus();
		InsertInfo("停止服务成功!");
	}
}
// 暂停服务
void CDlgSerCtrl::OnBnClickedBtSerctrPause()
{
	if (m_SvrCtrl.SvrCtr_PauseService())
	{
		SetBtStatus();
		InsertInfo("暂停服务成功!");
	}
}
// 继续服务
void CDlgSerCtrl::OnBnClickedBtSerctrContinue()
{
	if (m_SvrCtrl.SvrCtr_ContinueService())
	{
		SetBtStatus();
		InsertInfo("继续服务成功!");
	}
}



