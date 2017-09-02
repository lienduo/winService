// DlgSerCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SuperServer.h"
#include "DlgSerCtrl.h"
#include "MainFrm.h"
#include "SuperServerDoc.h"
#include "SuperServerView.h"
#include "iIniOp.h"
#include "DlgMsg.h"


// CDlgSerCtrl �Ի���

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


// CDlgSerCtrl ��Ϣ�������

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

// ���ð�ť״̬
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
		InsertInfo(_T("�򿪷��������ļ�ʧ��!!"));
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

// ������Ϣ
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
// ����ComBox
void CDlgSerCtrl::LoadComBox(void)
{
	m_ComSerCtrl.ResetContent();
	CiIniOp ini;
	if (!ini.Load(_T("Config.ini")))
	{
		InsertInfo(_T("�򿪷��������ļ�ʧ��!!"));
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
// ���ķ���
void CDlgSerCtrl::OnCbnSelchangeCobSername()
{
	SetBtStatus();
}
BOOL CDlgSerCtrl::OnInitDialog()
{
	CDialog::OnInitDialog();
	// ��ʼ��
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

// ��������
void CDlgSerCtrl::OnBnClickedBtSerctrStart()
{
	if (m_SvrCtrl.SvrCtr_StartService())
	{
		SetBtStatus();
		InsertInfo(_T("��������ɹ�!"));
	}
	else
	{
		SetBtStatus();
		InsertInfo(_T("��������ʧ��!"));
	}
}
// ֹͣ����
void CDlgSerCtrl::OnBnClickedBtSerctrStop()
{
	CDlgMsg dlg;
	dlg.m_szCaption=_T("ϵͳ��ʾ...");
	dlg.m_szMsg=_T("���Ƿ�Ҫֹͣ������?");
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
		InsertInfo("ֹͣ����ɹ�!");
	}
}
// ��ͣ����
void CDlgSerCtrl::OnBnClickedBtSerctrPause()
{
	if (m_SvrCtrl.SvrCtr_PauseService())
	{
		SetBtStatus();
		InsertInfo("��ͣ����ɹ�!");
	}
}
// ��������
void CDlgSerCtrl::OnBnClickedBtSerctrContinue()
{
	if (m_SvrCtrl.SvrCtr_ContinueService())
	{
		SetBtStatus();
		InsertInfo("��������ɹ�!");
	}
}



