// DlgInUn.cpp : 实现文件
//

#include "stdafx.h"
#include "SuperServer.h"
#include "DlgInUn.h"
#include "MainFrm.h"
#include "SuperServerDoc.h"
#include "SuperServerView.h"
// #include "..\\ServerControl\\ServerControlExp.h"
#include "iIniOp.h"
#include "DlgMsg.h"


// CDlgInUn 对话框

IMPLEMENT_DYNAMIC(CDlgInUn, CDialog)

CDlgInUn::CDlgInUn(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInUn::IDD, pParent)
	,m_pView(NULL)
{

}

CDlgInUn::~CDlgInUn()
{
}

void CDlgInUn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COB_SERNAME, m_ComSerCtrl);
	DDX_Control(pDX, IDC_BT_INUN_INSTALL, m_BtInstall);
	DDX_Control(pDX, IDC_BT_INUN_UNSTALL, m_BtUnstall);
}


BEGIN_MESSAGE_MAP(CDlgInUn, CDialog)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BT_INUN_INSTALL, &CDlgInUn::OnBnClickedBtInunInstall)
	ON_BN_CLICKED(IDC_BT_INUN_UNSTALL, &CDlgInUn::OnBnClickedBtInunUnstall)
	ON_CBN_SELCHANGE(IDC_COB_SERNAME, &CDlgInUn::OnCbnSelchangeCobSername)
END_MESSAGE_MAP()


// CDlgInUn 消息处理程序

BOOL CDlgInUn::OnEraseBkgnd(CDC* pDC)
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
void CDlgInUn::SetBtStatus(void)
{
	CString szSel;
	m_ComSerCtrl.GetLBText(m_ComSerCtrl.GetCurSel(),szSel);
	if (szSel==_T(""))
	{
		return;
	}
	GetDlgItem(IDC_BT_INUN_INSTALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BT_INUN_UNSTALL)->EnableWindow(FALSE);
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
	if (!m_SvrCtrl.SvrCtr_Init(szSerName,szDisName))
	{
		InsertInfo(_T("服务控制模块没有加载!"));
		return;
	}
	if (m_SvrCtrl.SvrCtr_IsInstalled())
	{
		if (m_SvrCtrl.SvrCtr_IsStoped())
		{
			GetDlgItem(IDC_BT_INUN_UNSTALL)->EnableWindow(TRUE);
		}
	}
	else
	{
		GetDlgItem(IDC_BT_INUN_INSTALL)->EnableWindow(TRUE);
	}
}

// 插入信息
void CDlgInUn::InsertInfo(CString szInfo)
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
void CDlgInUn::LoadComBox(void)
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

BOOL CDlgInUn::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 初始化
	m_BtInstall.LoadBitmaps(IDB_DEFBUTTON,88);
	m_BtUnstall.LoadBitmaps(IDB_DEFBUTTON,88);
	if(!m_SvrCtrl.Load())
	{
		return FALSE;
	}
	LoadComBox();
	SetBtStatus();
	return TRUE;
}

void CDlgInUn::OnCbnSelchangeCobSername()
{
	SetBtStatus();
}
// 安装
void CDlgInUn::OnBnClickedBtInunInstall()
{
	CString szSel;
	m_ComSerCtrl.GetLBText(m_ComSerCtrl.GetCurSel(),szSel);
	if (szSel==_T(""))
	{
		InsertInfo(_T("没有选择服务!"));
		return;
	}
	CiIniOp ini;
	if (!ini.Load(_T("Config.ini")))
	{
		InsertInfo(_T("打开服务配置文件失败!!"));
		return;
	}
	char szDescription[MAX_PATH];
	ini.GetValue(szDescription,_T("SerDescription"),szSel.GetBuffer());
	CString szFilePath;
	GetModuleFileName(NULL, szFilePath.GetBuffer(MAX_PATH), _MAX_PATH);
	szFilePath.ReleaseBuffer();
	if (m_SvrCtrl.SvrCtr_Install(szFilePath.GetBuffer(),szSel.GetBuffer(),szDescription))
	{
		SetBtStatus();
		InsertInfo(_T("服务安装成功"));
	}
}
// 卸载
void CDlgInUn::OnBnClickedBtInunUnstall()
{
	if (m_SvrCtrl.SvrCtr_Uninstall())
	{
		SetBtStatus();
		InsertInfo(_T("服务卸载成功!"));
	}
}

