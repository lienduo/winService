
// SuperServer.cpp : 定义应用程序的类行为。
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
	// 基于文件的标准文档命令
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CSuperServerApp 构造
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
// 唯一的一个 CSuperServerApp 对象

CSuperServerApp theApp;

// CSuperServerApp 初始化

BOOL CSuperServerApp::InitInstance()
{
	// --------------------------------服务模式运行部分--------------------------------
	szCmd=m_lpCmdLine;// 参数指示Section
	if (!szCmd.IsEmpty()) // 服务运行模式
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
		// 加载模块
		if(!m_pModule->Load(szCmd.GetBuffer()))
		{
			pLog->WriteLog(1,_T("%s:CSvrModule Load error!!"),szCmd.GetBuffer());
			return FALSE;
		}
		// 加载Lib模块
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
			return FALSE;// 初始化服务失败
		}
		if (m_pLib->GetSerPause()&&m_pLib->GetSerContinue()!=NULL)
		{
			m_pModule->Svr_SetPauseContinue(m_pLib->GetSerPause(),m_pLib->GetSerContinue());
		}
		delete pLog;
		 return m_pModule->Svr_RunService()==0?TRUE:FALSE;
	}
	// --------------------------------服务模式运行部分--------------------------------

	// --------------------------------桌面模式运行部分--------------------------------

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("CodeCenter"));
	m_bSaveState = FALSE;
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSuperServerDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CSuperServerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 清理
	//CleanState();
	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->CenterWindow(CWnd::GetDesktopWindow());
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生

	// --------------------------------桌面模式运行部分--------------------------------
	return TRUE;
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// 用于运行对话框的应用程序命令
void CSuperServerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSuperServerApp 自定义加载/保存方法

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

// CSuperServerApp 消息处理程序
