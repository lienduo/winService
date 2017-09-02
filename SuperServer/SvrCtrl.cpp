#include "StdAfx.h"
#include "SvrCtrl.h"

CSvrCtrl::CSvrCtrl(void)
:m_hSvrCtrl(NULL)
,InitSvr(NULL)
,Svr_Installed(NULL)
,InstallSvr(NULL)
,UninstallSvr(NULL)
,Svr_Running(NULL)
,Svr_Paused(NULL)
,Svr_Stoped(NULL)
,StartSvr(NULL)
,StopSvr(NULL)
,PauseSvr(NULL)
,ContinueSvr(NULL)
,SetSvrType(NULL)
,GetSvrType(NULL)
,SetDescription(NULL)
,GetDescription(NULL)
{
}

CSvrCtrl::~CSvrCtrl(void)
{
	if (m_hSvrCtrl!=NULL)
	{
		FreeLibrary(m_hSvrCtrl);
	}
}

// 加载模块
bool CSvrCtrl::Load(void)
{
	char szSysPath[MAX_PATH];
	GetModuleFileName(NULL, szSysPath,MAX_PATH);
	int nLen=strlen(szSysPath);
	for (int i=nLen;i>0;i--)
	{
		if (szSysPath[i]=='\\')
		{
			szSysPath[i+1]='\0';
			break;
		}
	}
	SetDllDirectory(szSysPath);
	m_hSvrCtrl=LoadLibrary(_T("ServerControl.dll"));
	if (m_hSvrCtrl==NULL)
	{
		return false;
	}
	InitSvr=(SvrInit)GetProcAddress(m_hSvrCtrl,_T("Svr_InitContrl"));
	Svr_Installed=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_IsInstalled"));
	// 安装服务
	InstallSvr=(SvrInstall)GetProcAddress(m_hSvrCtrl,_T("Svr_Install"));
	// 卸载服务
	UninstallSvr=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_Uninstall"));
	// 正在运行
	Svr_Running=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_IsRunning"));
	// 暂停
	Svr_Paused=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_IsPaused"));
	// 停止
	Svr_Stoped=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_IsStoped"));
	// 开始服务
	StartSvr=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_StartService"));
	// 停止服务
	StopSvr=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_StopService"));
	// 暂停服务
	PauseSvr=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_PauseService"));
	// 继续服务
	ContinueSvr=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_ContinueService"));
	// 设置服务类型
	SetSvrType=(SvrSetServStartType)GetProcAddress(m_hSvrCtrl,_T("Svr_SetServStartType"));
	// 获得服务类型
	GetSvrType=(SvrGetServiceStartType)GetProcAddress(m_hSvrCtrl,_T("Svr_GetServiceStartType"));
	// 设置描述
	SetDescription=(SvrSetDescription)GetProcAddress(m_hSvrCtrl,_T("Svr_SetDescription"));
	// 获得描述
	GetDescription=(SvrGetDescription)GetProcAddress(m_hSvrCtrl,_T("Svr_GetDescription"));
	return true;
}
// 初始化
bool CSvrCtrl::SvrCtr_Init(char* szSerName,char* szSerDisplayName)
{
	return InitSvr==NULL?false:InitSvr(szSerName,szSerDisplayName);
}
// 判断服务是否安装
bool CSvrCtrl::SvrCtr_IsInstalled(void)
{
	return Svr_Installed==NULL?false:Svr_Installed();
}
// 安装服务 程序参数,服务描述
bool CSvrCtrl::SvrCtr_Install(char* lpAppName,char* lpRef,char* lpDescription)
{
	return InstallSvr==NULL?false:InstallSvr(lpAppName,lpRef,lpDescription);
}
// 卸载服务
bool CSvrCtrl::SvrCtr_Uninstall(void)
{
	return UninstallSvr==NULL?false:UninstallSvr();
}
// 判断是否在运行
bool CSvrCtrl::SvrCtr_IsRunning(void)
{
	return Svr_Running==NULL?false:Svr_Running();
}
// 判断是否在暂停
bool CSvrCtrl::SvrCtr_IsPaused(void)
{
	return Svr_Paused==NULL?false:Svr_Paused();
}
// 判断是否在停止
bool CSvrCtrl::SvrCtr_IsStoped(void)
{
	return Svr_Stoped==NULL?false:Svr_Stoped();
}
// 开始服务
bool CSvrCtrl::SvrCtr_StartService(void)
{
	return StartSvr==NULL?false:StartSvr();
}
// 停止服务
bool CSvrCtrl::SvrCtr_StopService(void)
{
	return StopSvr==NULL?false:StopSvr();
}
// 暂停服务
bool CSvrCtrl::SvrCtr_PauseService(void)
{
	return PauseSvr==NULL?false:PauseSvr();
}
// 恢复服务
bool CSvrCtrl::SvrCtr_ContinueService(void)
{
	return ContinueSvr==NULL?false:ContinueSvr();
}
// 设置服务启动类型
bool CSvrCtrl::SvrCtr_SetServStartType(int nType) 
{
	return SetSvrType==NULL?false:SetSvrType(nType);
}
// 取得服务的启动类型
UINT CSvrCtrl::SvrCtr_GetServiceStartType(void)
{
	return GetSvrType==NULL?-1:GetSvrType();
}
// 设置服务描述信息
bool CSvrCtrl::SvrCtr_SetDescription(char* lpDescription)
{
	return SetDescription==NULL?false:SetDescription(lpDescription);
}
// 获得服务描述信息
char* CSvrCtrl::SvrCtr_GetDescription(void)
{
	return GetDescription==NULL?NULL:GetDescription();
}