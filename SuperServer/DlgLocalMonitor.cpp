// DlgLocalMonitor.cpp : 实现文件
//

#include "stdafx.h"
#include "SuperServer.h"
#include "DlgLocalMonitor.h"
#include "MainFrm.h"
#include "SuperServerDoc.h"
#include "SuperServerView.h"
// #include "..\\ServerControl\\ServerControlExp.h"
#include "iIniOp.h"
#include "DlgMsg.h"


// CDlgLocalMonitor 对话框

IMPLEMENT_DYNAMIC(CDlgLocalMonitor, CDialog)

CDlgLocalMonitor::CDlgLocalMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLocalMonitor::IDD, pParent)
	,m_pView(NULL)
{
}

CDlgLocalMonitor::~CDlgLocalMonitor()
{
}

void CDlgLocalMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COB_SERNAME, m_ComSerCtrl);
	DDX_Control(pDX, IDC_BT_SERCTR_START, m_StartBt);
	DDX_Control(pDX, IDC_BT_SERCTR_STOP, m_StopBt);
	DDX_Control(pDX, IDC_BT_SERCTR_PAUSE, m_PauseBt);
	DDX_Control(pDX, IDC_BT_SERCTR_CONTINUE, m_ContinueBt);
}


BEGIN_MESSAGE_MAP(CDlgLocalMonitor, CDialog)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BT_SERCTR_START, &CDlgLocalMonitor::OnBnClickedBtSerctrStart)
	ON_BN_CLICKED(IDC_BT_SERCTR_STOP, &CDlgLocalMonitor::OnBnClickedBtSerctrStop)
	ON_BN_CLICKED(IDC_BT_SERCTR_PAUSE, &CDlgLocalMonitor::OnBnClickedBtSerctrPause)
	ON_BN_CLICKED(IDC_BT_SERCTR_CONTINUE, &CDlgLocalMonitor::OnBnClickedBtSerctrContinue)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COB_SERNAME, &CDlgLocalMonitor::OnCbnSelchangeCobSername)
END_MESSAGE_MAP()


// CDlgLocalMonitor 消息处理程序

BOOL CDlgLocalMonitor::OnEraseBkgnd(CDC* pDC)
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
void CDlgLocalMonitor::OnDestroy()
{
	for (iter=SerMap.begin();iter!=SerMap.end();iter++)
	{
		if (iter->second->GetStatus()==1)
		{
			if (iter->second->GetSerStop()!=NULL)
			{
				iter->second->GetSerStop()();
			}
		}
		if (iter->second->GetStatus()==2)
		{
			if (iter->second->GetSerContinue()!=NULL)
			{
				iter->second->GetSerContinue()();
			}
			if (iter->second->GetSerStop()!=NULL)
			{
				iter->second->GetSerStop()();
			}
		}
		delete iter->second;
	}
	CDialog::OnDestroy();
}

void CDlgLocalMonitor::OnCbnSelchangeCobSername()
{
	CString szSel;
	m_ComSerCtrl.GetLBText(m_ComSerCtrl.GetCurSel(),szSel);
	if (szSel==_T(""))
	{
		return;
	}
	AddMap(szSel.GetBuffer());
}

// 设置按钮状态
void CDlgLocalMonitor::SetBtStatus(void)
{
	GetDlgItem(IDC_BT_SERCTR_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BT_SERCTR_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BT_SERCTR_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BT_SERCTR_CONTINUE)->EnableWindow(FALSE);
	CString szSel;
	m_ComSerCtrl.GetLBText(m_ComSerCtrl.GetCurSel(),szSel);
	if (szSel==_T(""))
	{
		return;
	}
	char szSerName[MAX_PATH];
	char szDisName[MAX_PATH];
	CiIniOp ini;
	ini.Load(_T("Config.ini"));
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
	if(!m_SvrCtrl.SvrCtr_Init(szSerName,szDisName))
	{
		InsertInfo(_T("服务控制模块初始化失败!"));
		return;
	}
	if (m_SvrCtrl.SvrCtr_IsInstalled())
	{
		if (m_SvrCtrl.SvrCtr_IsRunning()||m_SvrCtrl.SvrCtr_IsPaused())
		{
			InsertInfo(_T("服务模式已启动,本地调试需停止服务模式!!"));
			return;
		}
	}
	if (SerMap.count(szSel)==0)
	{
		return;
	}
	switch (SerMap[szSel]->GetStatus())
	{
	case 0: // 停止
		GetDlgItem(IDC_BT_SERCTR_START)->EnableWindow(TRUE);
		break;
	case 1: // 运行
		GetDlgItem(IDC_BT_SERCTR_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BT_SERCTR_PAUSE)->EnableWindow(TRUE);
		break;
	case 2: // 暂停
		GetDlgItem(IDC_BT_SERCTR_CONTINUE)->EnableWindow(TRUE);
		break;
	default:
		break;
	}
}

// 插入信息
void CDlgLocalMonitor::InsertInfo(CString szInfo)
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

// 加入Map
void CDlgLocalMonitor::AddMap(char* szSection)
{
	if (SerMap.count(szSection)>0)
	{
		return;
	}
	CSvrLib* pLib=new CSvrLib;
	if (pLib!=NULL)
	{
		pLib->Load(szSection);
		SerMap[szSection]=pLib;
	}
}
// 加载ComBox
void CDlgLocalMonitor::LoadComBox(void)
{
	SerMap.clear();
	m_ComSerCtrl.ResetContent();
	CiIniOp ini;
	if (!ini.Load(_T("Config.ini")))
	{
		InsertInfo(_T("打开服务配置文件失败!!"));
		return;
	}
	char** pSec=NULL;
	int nSec=0,nkey=0;
	ini.ReadSection(&pSec,&nSec);
	for (int i=0;i<nSec;i++)
	{
		m_ComSerCtrl.AddString(pSec[i]);
	}
	ini.EndReadSection(pSec);
	m_ComSerCtrl.SetCurSel(0);
}
BOOL CDlgLocalMonitor::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 初始化
	GetModuleFileName(GetSelfModuleHandle(),m_szSysPath,MAX_PATH);
	int nLen=strlen(m_szSysPath);
	for (int i=nLen;i>0;i--)
	{
		if (m_szSysPath[i]=='\\')
		{
			m_szSysPath[i+1]='\0';
			break;
		}
	}
	m_SvrCtrl.Load();
	LoadComBox();
	CString szSel;
	m_ComSerCtrl.GetLBText(m_ComSerCtrl.GetCurSel(),szSel);
	if (szSel==_T(""))
	{
		return TRUE;
	}
	AddMap(szSel.GetBuffer());
	m_StartBt.LoadBitmaps(IDB_DEFBUTTON,88);
	m_StopBt.LoadBitmaps(IDB_DEFBUTTON,88);
	m_PauseBt.LoadBitmaps(IDB_DEFBUTTON,88);
	m_ContinueBt.LoadBitmaps(IDB_DEFBUTTON,88);
	SetBtStatus();
	return TRUE;
}
// 启动服务
void CDlgLocalMonitor::OnBnClickedBtSerctrStart()
{
	CString szSel;
	m_ComSerCtrl.GetLBText(m_ComSerCtrl.GetCurSel(),szSel);
	if (szSel==_T(""))
	{
		return;
	}
	if (SerMap.count(szSel)==0)
	{
		return;
	}
	if (SerMap[szSel]->GetSerStart()!=NULL)
	{
		if (0==SerMap[szSel]->GetSerStart()())
		{
			InsertInfo(_T("开始服务(一般模式)成功..."));
			SetBtStatus();
		}
		else
		{
			InsertInfo(_T("开始服务(一般模式)失败!!!!"));
		}
	}
	else
	{
		InsertInfo(_T("开始服务(一般模式)失败!!!!"));
	}
}
// 停止服务
void CDlgLocalMonitor::OnBnClickedBtSerctrStop()
{
	CString szSel;
	m_ComSerCtrl.GetLBText(m_ComSerCtrl.GetCurSel(),szSel);
	if (szSel==_T(""))
	{
		return;
	}
	if (SerMap.count(szSel)==0)
	{
		return;
	}
	if (SerMap[szSel]->GetSerStop()!=NULL)
	{
		if (0==SerMap[szSel]->GetSerStop()())
		{
			InsertInfo(_T("停止服务(一般模式)成功."));
			SetBtStatus();
		}
		else
		{
			InsertInfo(_T("停止服务(一般模式)失败!"));
		}
	}
	else
	{
		InsertInfo(_T("停止服务(一般模式)失败!"));
	}
}
// 暂停服务
void CDlgLocalMonitor::OnBnClickedBtSerctrPause()
{
	CString szSel;
	m_ComSerCtrl.GetLBText(m_ComSerCtrl.GetCurSel(),szSel);
	if (szSel==_T(""))
	{
		return;
	}
	if (SerMap.count(szSel)==0)
	{
		return;
	}
	if (SerMap[szSel]->GetSerPause()!=NULL)
	{
		if (0==SerMap[szSel]->GetSerPause()())
		{
			InsertInfo(_T("暂停服务(一般模式)成功."));
			SetBtStatus();
		}
		else
		{
			InsertInfo(_T("暂停服务(一般模式)失败!"));
		}
	}
	else
	{
		InsertInfo(_T("暂停服务(一般模式)失败!"));
	}
}
// 继续服务
void CDlgLocalMonitor::OnBnClickedBtSerctrContinue()
{
	CString szSel;
	m_ComSerCtrl.GetLBText(m_ComSerCtrl.GetCurSel(),szSel);
	if (szSel==_T(""))
	{
		return;
	}
	if (SerMap.count(szSel)==0)
	{
		return;
	}
	if (SerMap[szSel]->GetSerContinue()!=NULL)
	{
		if (0==SerMap[szSel]->GetSerContinue()())
		{
			InsertInfo(_T("继续服务(一般模式)成功."));
			SetBtStatus();
		}
		else
		{
			InsertInfo(_T("继续服务(一般模式)失败!"));
		}
	}
	else
	{
		InsertInfo(_T("继续服务(一般模式)失败!"));
	}
}
