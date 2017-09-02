#include "StdAfx.h"
#include "SvrLib.h"
#include "FileLog.h"

CSvrLib::CSvrLib(void)
:m_hSvrLib(NULL)
,m_SerStart(NULL)
,m_SerStop(NULL)
,m_SerPause(NULL)
,m_SerContinue(NULL)
,m_GetStatus(NULL)
{
}

CSvrLib::~CSvrLib(void)
{
	if (m_hSvrLib!=NULL)
	{
		FreeLibrary(m_hSvrLib);
	}
}

// 加载服务Lib
bool CSvrLib::Load(char* szCmd)
{
	if (szCmd==NULL)
	{
		return false;
	}
	// 获取INI配置
	CFileLog* pLog=new CFileLog;
	char szSysPath[MAX_PATH];
	GetModuleFileName(GetSelfModuleHandle(),szSysPath,MAX_PATH);
	int nLen=strlen(szSysPath);
	for (int i=nLen;i>0;i--)
	{
		if (szSysPath[i]=='\\')
		{
			szSysPath[i+1]='\0';
			break;
		}
	}
	char szIniFile[MAX_PATH];
	sprintf_s(szIniFile,MAX_PATH,_T("%s%s"),szSysPath,_T("Config.ini"));
	char szDllName[MAX_PATH];
	char szDllPath[MAX_PATH];
	GetPrivateProfileString(szCmd,_T("LibPath"),_T(""),szDllPath,MAX_PATH,szIniFile);
	if (szDllPath[0]=='\0')
	{
		if (pLog!=NULL)
		{
			pLog->WriteLog(1,_T("%s:%s is empty!!"),szCmd,_T("LibPath"));
			delete pLog;
			pLog=NULL;
		}
		return false;
	}
	if (szDllPath[1]!=':') // 完整路径
	{
		sprintf_s(szDllName,MAX_PATH,_T("%s%s"),szSysPath,szDllPath);
		strcpy_s(szDllPath,MAX_PATH,szDllName);
	}
	nLen=strlen(szDllPath);
	for (int i=nLen;i>0;i--)
	{
		if (szDllPath[i]=='\\')
		{
			strcpy_s(szDllName,MAX_PATH,szDllPath+i+1);
			szDllPath[i+1]='\0';
			SetDllDirectory(szDllPath);
			break;
		}
	}
	// 加载LibDll
	m_hSvrLib=LoadLibrary(szDllName);
	if (m_hSvrLib==NULL)
	{
		if (pLog!=NULL)
		{
			pLog->WriteLog(1,_T("%s:LibPath Path:%s,Name:%s,LoadLibrary Fail!!"),szCmd,szDllPath,szDllName);
			delete pLog;
			pLog=NULL;
		}
		return false;
	}
	// 开始和停止
	GetPrivateProfileString(szCmd,_T("SerStart"),_T(""),szDllName,MAX_PATH,szIniFile);
	if (szDllName[0]=='\0')
	{
		if (pLog!=NULL)
		{
			pLog->WriteLog(1,_T("%s:%s is empty!!"),szCmd,_T("SerStart"));
			delete pLog;
			pLog=NULL;
		}
		return FALSE;
	}
	m_SerStart=(BackFun)GetProcAddress(m_hSvrLib,szDllName);
	if (m_SerStart==NULL)
	{
		if (pLog!=NULL)
		{
			pLog->WriteLog(1,_T("%s:%s GetProcAddress Fail!!"),szCmd,_T("SerStart"));
			delete pLog;
			pLog=NULL;
		}
		return FALSE;
	}

	GetPrivateProfileString(szCmd,_T("SerStop"),_T(""),szDllName,MAX_PATH,szIniFile);
	if (szDllName[0]=='\0')
	{
		if (pLog!=NULL)
		{
			pLog->WriteLog(1,_T("%s:%s is empty!!"),szCmd,_T("SerStop"));
			delete pLog;
			pLog=NULL;
		}
		return FALSE;
	}
	m_SerStop=(BackFun)GetProcAddress(m_hSvrLib,szDllName);
	if (m_SerStop==NULL)
	{
		if (pLog!=NULL)
		{
			pLog->WriteLog(1,_T("%s:%s GetProcAddress Fail!!"),szCmd,_T("SerStop"));
			delete pLog;
			pLog=NULL;
		}
		return FALSE;
	}
	// 暂停和继续
	GetPrivateProfileString(szCmd,_T("SerPause"),_T(""),szDllName,MAX_PATH,szIniFile);
	if (szDllName[0]!='\0')
	{
		m_SerPause=(BackFun)GetProcAddress(m_hSvrLib,szDllName);
		if (m_SerPause!=NULL)
		{
			GetPrivateProfileString(szCmd,_T("SerContinue"),_T(""),szDllName,MAX_PATH,szIniFile);
			if (szDllName[0]!='\0')
			{
				m_SerContinue=(BackFun)GetProcAddress(m_hSvrLib,szDllName);
				if (NULL==m_SerContinue)
				{
					if (pLog!=NULL)
					{
						pLog->WriteLog(1,_T("%s:%s GetProcAddress Fail!!"),szCmd,_T("SerContinue"));
					}
				}
			}
			else
			{
				if (pLog!=NULL)
				{
					pLog->WriteLog(1,_T("%s:%s is Empty!!"),szCmd,_T("SerContinue"));
				}
			}
		}
		else
		{
			if (pLog!=NULL)
			{
				pLog->WriteLog(1,_T("%s:%s GetProcAddress Fail!!"),szCmd,_T("SerPause"));
			}
		}
	}
	else
	{
		if (pLog!=NULL)
		{
			pLog->WriteLog(1,_T("%s:%s is Empty!!"),szCmd,_T("SerPause"));
		}
	}
	// 服务状态
	GetPrivateProfileString(szCmd,_T("SerStatus"),_T(""),szDllName,MAX_PATH,szIniFile);
	if (szDllName[0]!='\0')
	{
		m_GetStatus=(BackFun)GetProcAddress(m_hSvrLib,szDllName);
		if (NULL==m_GetStatus)
		{
			if (pLog!=NULL)
			{
				pLog->WriteLog(1,_T("%s:%s GetProcAddress Fail!!"),szCmd,_T("SerStatus"));
			}
		}
	}
	else
	{
		if (pLog!=NULL)
		{
			pLog->WriteLog(1,_T("%s:%s is Empty!!"),szCmd,_T("SerStatus"));
		}
	}
	if (pLog!=NULL)
	{
		delete pLog;
		pLog=NULL;
	}
	return true;
}
CSvrLib::BackFun CSvrLib::GetSerStart()
{
	return m_SerStart;
}
CSvrLib::BackFun CSvrLib::GetSerPause()
{
	return m_SerPause;
}
CSvrLib::BackFun CSvrLib::GetSerContinue()
{
	return m_SerContinue;
}
CSvrLib::BackFun CSvrLib::GetSerStop()
{
	return m_SerStop;
}
int CSvrLib::GetStatus()
{
	return m_GetStatus!=NULL?m_GetStatus():-1;
}