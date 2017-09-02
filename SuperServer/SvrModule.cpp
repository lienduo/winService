#include "StdAfx.h"
#include "SvrModule.h"

CSvrModule::CSvrModule(void)
:m_hSvrModule(NULL)
{
}

CSvrModule::~CSvrModule(void)
{
	if (m_hSvrModule!=NULL)
	{
		FreeLibrary(m_hSvrModule);
	}
}

// 加载模块
bool CSvrModule::Load(char* szCmd)
{
	char szSysPath[MAX_PATH];
	GetModuleFileName(GetSelfModuleHandle(), szSysPath,MAX_PATH);
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
	m_hSvrModule=LoadLibrary(_T("ServiceModule.dll"));
	if (m_hSvrModule==NULL)
	{
		return false;
	}
	SvrInit=(SerInit)GetProcAddress(m_hSvrModule,_T("Ser_Init"));

	SvrSetPauseContinue=(SetPauseContinue)GetProcAddress(m_hSvrModule,_T("Ser_SetPauseContinue"));
	SvrRunService=(RunService)GetProcAddress(m_hSvrModule,_T("Ser_RunService"));
	strcat_s(szSysPath,_T("Config.ini"));
	GetPrivateProfileString(szCmd,_T("SerName"),_T(""),m_szSerName,MAX_PATH,szSysPath);
	if (m_szSerName[0]=='\0')
	{
		return false;
	}
	return true;
}
// 服务名称(区别不同的服务),服务显示名称(用于控制台显示),服务开始运行函数,停止函数
int CSvrModule::Svr_Init(BackFun SerStart,BackFun SerStop)
{
	return SvrInit==NULL?-1:SvrInit(m_szSerName,SerStart,SerStop);
}
// 设置暂停\继续(服务模式可选设置)
int CSvrModule::Svr_SetPauseContinue(BackFun SerPause,BackFun SerContinue)
{
	return SvrSetPauseContinue==NULL?-1:SvrSetPauseContinue(SerPause,SerContinue);
}
// --------------初始化-------------------

// 开始服务,返回非0,没有初始化,或在非服务模式下调用,true在服务模式下调用成功
int CSvrModule::Svr_RunService()
{
	return SvrRunService==NULL?-1:SvrRunService();
}
