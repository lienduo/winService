
// SuperServer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "SuperServer.h"
#include "MainFrm.h"

#include "SuperServerDoc.h"
#include "SuperServerView.h"
#include "FileLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSuperServerApp

BEGIN_MESSAGE_MAP(CSuperServerApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CSuperServerApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CSuperServerApp ����
CString szCmd=_T("");

CSuperServerApp::CSuperServerApp()
:m_pModule(NULL)
,m_pLib(NULL)
{
	m_bHiColorIcons = TRUE;
}
CSuperServerApp::~CSuperServerApp()
{
	if (m_pModule!=NULL)
	{
		delete m_pModule;
		m_pModule=NULL;
	}
	if (m_pLib!=NULL)
	{
		delete m_pLib;
		m_pLib=NULL;

		CFileLog log;
		log.WriteLog(1,_T("%s:Service is stopped!!"),szCmd.GetBuffer());
	}
}
// Ψһ��һ�� CSuperServerApp ����

CSuperServerApp theApp;

// CSuperServerApp ��ʼ��

BOOL CSuperServerApp::InitInstance()
{
	// --------------------------------����ģʽ���в���--------------------------------
	szCmd=m_lpCmdLine;// ����ָʾSection
	if (!szCmd.IsEmpty()) // ��������ģʽ
	{
		CFileLog* pLog=new CFileLog;
		m_pLib=new CSvrLib;
		if (m_pLib==NULL)
		{
			pLog->WriteLog(1,_T("%s:new CSvrLibi error!!"),szCmd.GetBuffer());
			return FALSE;
		}
		m_pModule=new CSvrModule;
		if (m_pModule==NULL)
		{
			pLog->WriteLog(1,_T("%s:new CSvrModule error!!"),szCmd.GetBuffer());
			return FALSE;
		}
		// ����ģ��
		if(!m_pModule->Load(szCmd.GetBuffer()))
		{
			pLog->WriteLog(1,_T("%s:CSvrModule Load error!!"),szCmd.GetBuffer());
			return FALSE;
		}
		// ����Libģ��
		if(!m_pLib->Load(szCmd.GetBuffer()))
		{
			pLog->WriteLog(1,_T("%s:CSvrLibi Load error!!"),szCmd.GetBuffer());
			return FALSE;
		}
		if (m_pLib->GetSerStart()==NULL||m_pLib->GetSerStop()==NULL)
		{
			pLog->WriteLog(1,_T("%s:Cm_pLib->GetSerStart()==NULL||m_pLib->GetSerStop()==NULL error!!"),szCmd.GetBuffer());
			return FALSE;
		}
		if (0!=m_pModule->Svr_Init(m_pLib->GetSerStart(),m_pLib->GetSerStop()))
		{
			pLog->WriteLog(1,_T("%s:Ser_Init is error!!"),szCmd.GetBuffer());
			return FALSE;// ��ʼ������ʧ��
		}
		if (m_pLib->GetSerPause()&&m_pLib->GetSerContinue()!=NULL)
		{
			m_pModule->Svr_SetPauseContinue(m_pLib->GetSerPause(),m_pLib->GetSerContinue());
		}
		delete pLog;
		 return m_pModule->Svr_RunService()==0?TRUE:FALSE;
	}
	// --------------------------------����ģʽ���в���--------------------------------

	// --------------------------------����ģʽ���в���--------------------------------

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("CodeCenter"));
	m_bSaveState = FALSE;
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSuperServerDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CSuperServerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// ����
	//CleanState();
	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->CenterWindow(CWnd::GetDesktopWindow());
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����

	// --------------------------------����ģʽ���в���--------------------------------
	return TRUE;
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CSuperServerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSuperServerApp �Զ������/���淽��

void CSuperServerApp::PreLoadState()
{
	/*BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);*/
}

void CSuperServerApp::LoadCustomState()
{
}

void CSuperServerApp::SaveCustomState()
{
}

// CSuperServerApp ��Ϣ�������
