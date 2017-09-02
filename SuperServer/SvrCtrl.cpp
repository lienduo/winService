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

// ����ģ��
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
	// ��װ����
	InstallSvr=(SvrInstall)GetProcAddress(m_hSvrCtrl,_T("Svr_Install"));
	// ж�ط���
	UninstallSvr=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_Uninstall"));
	// ��������
	Svr_Running=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_IsRunning"));
	// ��ͣ
	Svr_Paused=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_IsPaused"));
	// ֹͣ
	Svr_Stoped=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_IsStoped"));
	// ��ʼ����
	StartSvr=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_StartService"));
	// ֹͣ����
	StopSvr=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_StopService"));
	// ��ͣ����
	PauseSvr=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_PauseService"));
	// ��������
	ContinueSvr=(SvrIsStatus)GetProcAddress(m_hSvrCtrl,_T("Svr_ContinueService"));
	// ���÷�������
	SetSvrType=(SvrSetServStartType)GetProcAddress(m_hSvrCtrl,_T("Svr_SetServStartType"));
	// ��÷�������
	GetSvrType=(SvrGetServiceStartType)GetProcAddress(m_hSvrCtrl,_T("Svr_GetServiceStartType"));
	// ��������
	SetDescription=(SvrSetDescription)GetProcAddress(m_hSvrCtrl,_T("Svr_SetDescription"));
	// �������
	GetDescription=(SvrGetDescription)GetProcAddress(m_hSvrCtrl,_T("Svr_GetDescription"));
	return true;
}
// ��ʼ��
bool CSvrCtrl::SvrCtr_Init(char* szSerName,char* szSerDisplayName)
{
	return InitSvr==NULL?false:InitSvr(szSerName,szSerDisplayName);
}
// �жϷ����Ƿ�װ
bool CSvrCtrl::SvrCtr_IsInstalled(void)
{
	return Svr_Installed==NULL?false:Svr_Installed();
}
// ��װ���� �������,��������
bool CSvrCtrl::SvrCtr_Install(char* lpAppName,char* lpRef,char* lpDescription)
{
	return InstallSvr==NULL?false:InstallSvr(lpAppName,lpRef,lpDescription);
}
// ж�ط���
bool CSvrCtrl::SvrCtr_Uninstall(void)
{
	return UninstallSvr==NULL?false:UninstallSvr();
}
// �ж��Ƿ�������
bool CSvrCtrl::SvrCtr_IsRunning(void)
{
	return Svr_Running==NULL?false:Svr_Running();
}
// �ж��Ƿ�����ͣ
bool CSvrCtrl::SvrCtr_IsPaused(void)
{
	return Svr_Paused==NULL?false:Svr_Paused();
}
// �ж��Ƿ���ֹͣ
bool CSvrCtrl::SvrCtr_IsStoped(void)
{
	return Svr_Stoped==NULL?false:Svr_Stoped();
}
// ��ʼ����
bool CSvrCtrl::SvrCtr_StartService(void)
{
	return StartSvr==NULL?false:StartSvr();
}
// ֹͣ����
bool CSvrCtrl::SvrCtr_StopService(void)
{
	return StopSvr==NULL?false:StopSvr();
}
// ��ͣ����
bool CSvrCtrl::SvrCtr_PauseService(void)
{
	return PauseSvr==NULL?false:PauseSvr();
}
// �ָ�����
bool CSvrCtrl::SvrCtr_ContinueService(void)
{
	return ContinueSvr==NULL?false:ContinueSvr();
}
// ���÷�����������
bool CSvrCtrl::SvrCtr_SetServStartType(int nType) 
{
	return SetSvrType==NULL?false:SetSvrType(nType);
}
// ȡ�÷������������
UINT CSvrCtrl::SvrCtr_GetServiceStartType(void)
{
	return GetSvrType==NULL?-1:GetSvrType();
}
// ���÷���������Ϣ
bool CSvrCtrl::SvrCtr_SetDescription(char* lpDescription)
{
	return SetDescription==NULL?false:SetDescription(lpDescription);
}
// ��÷���������Ϣ
char* CSvrCtrl::SvrCtr_GetDescription(void)
{
	return GetDescription==NULL?NULL:GetDescription();
}