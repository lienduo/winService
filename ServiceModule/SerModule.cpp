#include "StdAfx.h"
#include "SerModule.h"
#include "FileLog.h"

extern CSerModule Module;

CSerModule::CSerModule(void)
:m_szServiceName(_T(""))
,m_hServiceStatus(NULL)
,m_SerPause(NULL)
,m_SerContinue(NULL)
, m_strDisplayName(_T(""))
{

	m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	m_status.dwCurrentState = SERVICE_STOPPED;
	m_status.dwControlsAccepted = 0;
	m_status.dwWin32ExitCode = S_OK;
	m_status.dwServiceSpecificExitCode = 0;
	m_status.dwCheckPoint = 0;
	m_status.dwWaitHint = 0;
	m_status.dwControlsAccepted = (SERVICE_ACCEPT_STOP|SERVICE_ACCEPT_SHUTDOWN);
}

CSerModule::~CSerModule(void)
{
}

// ����״̬
void CSerModule::SetSerStatus(DWORD dwState)
{
	m_status.dwCurrentState = dwState;
	::SetServiceStatus(m_hServiceStatus, &m_status);
}

void WINAPI CSerModule::ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	Module.SerMain(dwArgc, lpszArgv);
}
inline void CSerModule::SerMain(DWORD /* dwArgc */, LPTSTR* /* lpszArgv */)
{
	m_hServiceStatus = RegisterServiceCtrlHandler(m_szServiceName,SerCtrlHandler);
	CFileLog log;
	if (m_hServiceStatus == NULL)
	{
		//LogEvent(_T("Handler not installed"));
		log.WriteLog(1,_T("%s:Service Handler not installed!"),m_strDisplayName.GetBuffer());
		return;
	}
	//���з�����
	if (m_SerStart!=NULL)
	{
		log.WriteLog(1,_T("%s:is Starting Service...."),m_strDisplayName.GetBuffer());
		SetSerStatus(SERVICE_START_PENDING);
		if(0==m_SerStart())
		{
			SetSerStatus(SERVICE_RUNNING);
			log.WriteLog(1,_T("%s:Service is running..."),m_strDisplayName.GetBuffer());
		}
		else
		{
			log.WriteLog(1,_T("%s:Service Start Error!!"),m_strDisplayName.GetBuffer());
			SetSerStatus(SERVICE_STOPPED);
		}
	}
}
void WINAPI CSerModule::SerCtrlHandler(DWORD dwOpcode)
{
	Module.Handler(dwOpcode); 
}
inline void CSerModule::Handler(DWORD dwOpcode)
{
	CFileLog log;
	switch (dwOpcode)
	{
	case SERVICE_CONTROL_SHUTDOWN:
	case SERVICE_CONTROL_STOP:
		{
			if (m_SerStop!=NULL)
			{
				SetSerStatus(SERVICE_STOP_PENDING);
				if(0==m_SerStop())
				{
					SetSerStatus(SERVICE_STOPPED);
					log.WriteLog(1,_T("%s:Service Stoped successfully!"),m_strDisplayName.GetBuffer());
				}
				else
				{
					log.WriteLog(1,_T("%s:Service Stop Error!"),m_strDisplayName.GetBuffer());
				}
			}
		}
		break;
	case SERVICE_CONTROL_PAUSE:
		if (m_SerPause!=NULL)
		{
			SetSerStatus(SERVICE_PAUSE_PENDING);
			if(0==m_SerPause())
			{
				SetSerStatus(SERVICE_PAUSED);
				log.WriteLog(1,_T("%s:Service Paused successfully!!"),m_strDisplayName.GetBuffer());
			}
			else
			{
				log.WriteLog(1,_T("%s:Service Pause Error!!"),m_strDisplayName.GetBuffer());
			}
		}
		break;
	case SERVICE_CONTROL_CONTINUE:
		if (m_SerContinue!=NULL)
		{
			SetSerStatus(SERVICE_START_PENDING);
			if(0==m_SerContinue())
			{
				SetSerStatus(SERVICE_RUNNING);
				log.WriteLog(1,_T("%s:Service Continue successfully!!"),m_strDisplayName.GetBuffer());
			}
			else
			{
				log.WriteLog(1,_T("%s:Service Continue Error!!"),m_strDisplayName.GetBuffer());
			}
		}
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;

	default:
		log.WriteLog(1,_T("%s:Bad service request!!"),m_strDisplayName.GetBuffer());
		break;
	}
}

// ��÷������ʾ��
bool CSerModule::GetSerDisplayName(CString& strName)
{
	SC_HANDLE hSC = ::OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// �򿪷���
	SC_HANDLE hSvc = ::OpenService( hSC, m_szServiceName,SERVICE_ALL_ACCESS);
	if( hSvc == NULL)
	{
		::CloseServiceHandle( hSC);
		return false;
	}
	LPQUERY_SERVICE_CONFIG ServicesInfo=(LPQUERY_SERVICE_CONFIG) LocalAlloc(LPTR, 2048);//�����ڴ�
	DWORD     nResumeHandle = 0;
	if(QueryServiceConfig(hSvc,ServicesInfo,2048,&nResumeHandle))//��ѯ��������;
	{
		strName=ServicesInfo->lpDisplayName;
	}
	LocalFree(ServicesInfo);
	::CloseServiceHandle( hSvc);
	::CloseServiceHandle( hSC);
	return true;
}
//-------------------------�ӿ�---------------------------

//�����ʼ��
int CSerModule::Init(CString ServiceName,BackFun SerStart,BackFun SerStop)
{
	if (m_szServiceName.CompareNoCase(ServiceName)==0)
	{
		return -1; //�Ѿ���ʼ��
	}
	m_szServiceName=ServiceName;
	m_SerStart=SerStart;
	m_SerStop=SerStop;
	return GetSerDisplayName(m_strDisplayName)?0:-1;
}

// ������ͣ�ͼ���
int CSerModule::SetPauseContinue(BackFun serPause, BackFun serContinue)
{
	if (m_SerPause!=NULL)
	{
		return -1;
	}
	m_SerPause=serPause;
	m_SerContinue=serContinue;
	m_status.dwControlsAccepted |=SERVICE_ACCEPT_PAUSE_CONTINUE;
	return 0;
}

// ��������
int CSerModule::RunService(void)
{
	if (m_szServiceName.IsEmpty())
	{
		return -1;
	}
	//�ж��Ƿ��Ƿ���������,���򷵻�True����������,���򷵻�false.
	SERVICE_TABLE_ENTRY st[] =
	{
		{m_szServiceName.GetBuffer(), ServiceMain },
		{ NULL, NULL }
	};
	return ::StartServiceCtrlDispatcher(st)?0:-1;//�Ƿ���ڸ÷��񲻴��ڷ���-1
}
