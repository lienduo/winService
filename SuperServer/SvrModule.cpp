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

// ����ģ��
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
// ��������(����ͬ�ķ���),������ʾ����(���ڿ���̨��ʾ),����ʼ���к���,ֹͣ����
int CSvrModule::Svr_Init(BackFun SerStart,BackFun SerStop)
{
	return SvrInit==NULL?-1:SvrInit(m_szSerName,SerStart,SerStop);
}
// ������ͣ\����(����ģʽ��ѡ����)
int CSvrModule::Svr_SetPauseContinue(BackFun SerPause,BackFun SerContinue)
{
	return SvrSetPauseContinue==NULL?-1:SvrSetPauseContinue(SerPause,SerContinue);
}
// --------------��ʼ��-------------------

// ��ʼ����,���ط�0,û�г�ʼ��,���ڷǷ���ģʽ�µ���,true�ڷ���ģʽ�µ��óɹ�
int CSvrModule::Svr_RunService()
{
	return SvrRunService==NULL?-1:SvrRunService();
}
