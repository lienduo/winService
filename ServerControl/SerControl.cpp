#include "StdAfx.h"
#include "SerControl.h"

CSerControl::CSerControl(void)
: m_szServiceName(_T(""))
, m_szServiceDisplayName(_T(""))
{
}

CSerControl::~CSerControl(void)
{
}

// ��ʼ����������
bool CSerControl::Init(CString szSerName,CString szServiceDisplayName)
{
	m_szServiceName=szSerName;
	if (szServiceDisplayName==_T(""))
	{
		szServiceDisplayName=szSerName;
	}
	m_szServiceDisplayName=szServiceDisplayName;
	return true;
}
bool CSerControl::IsInstalled()
{
	bool bResult = false;

	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if (hSCM != NULL)
	{
		SC_HANDLE hService = OpenService(hSCM, m_szServiceName, SERVICE_QUERY_CONFIG);
		if (hService != NULL)
		{
			bResult = true;
			::CloseServiceHandle(hService);
		}
		::CloseServiceHandle(hSCM);
	}
	return bResult;
}

bool CSerControl::Install(CString szAppFileName,CString szRef,CString szDescription)
{
	if (IsInstalled())
	{
		return true;
	}

	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hSCM == NULL)
	{
		return false;
	}
	if (szRef!=_T(""))
	{
		szAppFileName+=_T(" ")+szRef;
	}
	SC_HANDLE hService = ::CreateService(
		hSCM, m_szServiceName, m_szServiceDisplayName,
		SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
		SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
		szAppFileName, NULL, NULL,NULL /*_T("RPCSS\0")*/, NULL, NULL);

	if (hService == NULL)
	{
		::CloseServiceHandle(hSCM);
		return false;
	}

	::CloseServiceHandle(hService);
	::CloseServiceHandle(hSCM);
	if (_T("")!=szDescription)
	{
		SetDescription(szDescription.GetBuffer());// ��������
	}
	return true;
}

bool CSerControl::Uninstall()
{
	if(!IsInstalled())
	{
		return true;
	}

	SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

	if(hSCM == NULL)
	{
		return false;
	}

	SC_HANDLE hService = OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);

	if(hService == NULL)
	{
		::CloseServiceHandle(hSCM);
		return false;
	}
	SERVICE_STATUS status;
	::ControlService(hService, SERVICE_CONTROL_STOP, &status);

	BOOL bDelete = ::DeleteService(hService);
	::CloseServiceHandle(hService);
	::CloseServiceHandle(hSCM);
	return bDelete?true:false;
}
//��ѯ�Ƿ���
bool CSerControl::IsRunning()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// �򿪷���
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// ��÷����״̬
	SERVICE_STATUS status;
	if( QueryServiceStatus( hSvc, &status) == false)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	CloseServiceHandle( hSvc);
	CloseServiceHandle( hSC);
	if( status.dwCurrentState == SERVICE_RUNNING)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// �ж��Ƿ�������ͣ
bool CSerControl::IsPaused()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// �򿪷���
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// ��÷����״̬
	SERVICE_STATUS status;
	if( QueryServiceStatus( hSvc, &status) == false)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	CloseServiceHandle( hSvc);
	CloseServiceHandle( hSC);
	if( status.dwCurrentState == SERVICE_PAUSED)
	{
		return true;
	}
	else
	{
		return false;
	}
}
// �ж��Ƿ�����ֹͣ
bool CSerControl::IsStoped()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// �򿪷���
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// ��÷����״̬
	SERVICE_STATUS status;
	if( QueryServiceStatus( hSvc, &status) == false)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	CloseServiceHandle( hSvc);
	CloseServiceHandle( hSC);
	if( status.dwCurrentState == SERVICE_STOPPED)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//��������
bool CSerControl::Start()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// �򿪷���
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// ��÷����״̬
	SERVICE_STATUS status;
	if( QueryServiceStatus( hSvc, &status) == FALSE)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	if( status.dwCurrentState == SERVICE_RUNNING)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return true;
	}
	else if( status.dwCurrentState == SERVICE_STOPPED)
	{
		// ��������
		if( ::StartService( hSvc, NULL, NULL) == FALSE)
		{
			CloseServiceHandle( hSvc);
			CloseServiceHandle( hSC);
			return false;
		}
		// �ȴ���������
		for (int i=0;i<5;i++)
		{
			if (!QueryServiceStatus( hSvc, &status))
			{
				CloseServiceHandle( hSvc);
				CloseServiceHandle( hSC);
				return false;
			}
			Sleep( status.dwWaitHint);
			if( status.dwCurrentState == SERVICE_RUNNING)
			{
				CloseServiceHandle( hSvc);
				CloseServiceHandle( hSC);
				return true;
			}
		}
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	return false;
}
//�رշ���
bool CSerControl::Stop()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// �򿪷���
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// ��÷����״̬
	SERVICE_STATUS status;
	if( QueryServiceStatus( hSvc, &status) == FALSE)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	//�������ֹͣ״̬���������񣬷���ֹͣ����
	if( status.dwCurrentState == SERVICE_RUNNING)
	{
		// ֹͣ����
		if( ::ControlService( hSvc, 
			SERVICE_CONTROL_STOP, &status) == FALSE)
		{
			CloseServiceHandle( hSvc);
			CloseServiceHandle( hSC);
			return false;
		}
		// �ȴ�����ֹͣ
		for(int i=0;i<5;i++)
		{
			if (QueryServiceStatus( hSvc, &status)!=TRUE)
			{
				CloseServiceHandle( hSvc);
				CloseServiceHandle( hSC);
				return false;
			}
			Sleep( status.dwWaitHint);
			if( status.dwCurrentState == SERVICE_STOPPED)
			{
				CloseServiceHandle( hSvc);
				CloseServiceHandle( hSC);
				return true;
			}
		}
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	else if( status.dwCurrentState == SERVICE_STOPPED)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return true;
	}
	return false;
}
// ��ͣ����
bool CSerControl::PauseService()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// �򿪷���
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,SERVICE_ALL_ACCESS);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// ��÷����״̬
	SERVICE_STATUS status;
	if(QueryServiceStatus( hSvc, &status) == false)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	//�����������״̬����ͣ����
	if(status.dwCurrentState == SERVICE_RUNNING)
	{
		// ֹͣ����
		if( ::ControlService( hSvc,SERVICE_CONTROL_PAUSE, &status) == FALSE)
		{
			CloseServiceHandle( hSvc);
			CloseServiceHandle( hSC);
			return false;
		}
		// �ȴ�����ֹͣ
		for(int i=0;i<3;i++)
		{
			if (QueryServiceStatus( hSvc, &status)!=TRUE)
			{
				CloseServiceHandle( hSvc);
				CloseServiceHandle( hSC);
				return false;
			}
			Sleep( status.dwWaitHint);
			if( status.dwCurrentState == SERVICE_PAUSED)
			{
				CloseServiceHandle( hSvc);
				CloseServiceHandle( hSC);
				return true;
			}
		}
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	else if(status.dwCurrentState == SERVICE_PAUSED||status.dwCurrentState == SERVICE_STOPPED)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return true;
	}
	CloseServiceHandle( hSvc);
	CloseServiceHandle( hSC);
	return false;
}
//�ָ�����
bool CSerControl::ContinueService()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// �򿪷���
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,SERVICE_ALL_ACCESS);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// ��÷����״̬
	SERVICE_STATUS status;
	if(QueryServiceStatus( hSvc, &status) == false)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	if(status.dwCurrentState == SERVICE_PAUSED)
	{
		// ֹͣ����
		if( ::ControlService( hSvc,SERVICE_CONTROL_CONTINUE, &status) == FALSE)
		{
			CloseServiceHandle( hSvc);
			CloseServiceHandle( hSC);
			return false;
		}
		// �ȴ�����ֹͣ
		for(int i=0;i<3;i++)
		{
			if (QueryServiceStatus( hSvc, &status)!=TRUE)
			{
				CloseServiceHandle( hSvc);
				CloseServiceHandle( hSC);
				return false;
			}
			Sleep( status.dwWaitHint);
			if( status.dwCurrentState == SERVICE_RUNNING)
			{
				CloseServiceHandle( hSvc);
				CloseServiceHandle( hSC);
				return true;
			}
		}
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	else if(status.dwCurrentState == SERVICE_RUNNING)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return true;
	}
	CloseServiceHandle( hSvc);
	CloseServiceHandle( hSC);
	return false;
}

// ���÷�������
bool CSerControl::SetServStartType(UINT nType)
{
	UINT nOldType=GetServiceStartType();
	if (nType==nOldType)
	{
		return true;
	}
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL) //Open SCManager Error!
	{
		return false;
	}
	// �򿪷���
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,SERVICE_ALL_ACCESS);
	if( hSvc == NULL) // Open Service Error
	{
		CloseServiceHandle( hSC);
		return false;
	}
	bool bRes=false;
	if (ChangeServiceConfig(hSvc, SERVICE_NO_CHANGE, \
		nType, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL)  )
	{
		bRes=true;
	}
	CloseServiceHandle( hSvc);
	CloseServiceHandle( hSC);
	return bRes;
}
// ȡ�÷������������
UINT CSerControl::GetServiceStartType() 
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return -1;
	}
	// �򿪷���
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,SERVICE_ALL_ACCESS);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return -1;
	}
	LPQUERY_SERVICE_CONFIG lpServiceConfig = (LPQUERY_SERVICE_CONFIG)new BYTE[1024] ;
	DWORD dwByteNeeded ;
	if ( !QueryServiceConfig (hSvc, lpServiceConfig, 1024, &dwByteNeeded ) )
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return -1 ;
	}

	UINT nServiceType = lpServiceConfig->dwStartType ;
	CloseServiceHandle( hSvc);
	CloseServiceHandle( hSC);
	delete lpServiceConfig ;
	return nServiceType ;
}
// ���÷���������Ϣ
bool CSerControl::SetDescription(CString szDescription) 
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		MessageBox(GetForegroundWindow(),  m_szServiceDisplayName+_T(" Open SCManager Error!"),_T("System Infomation"), MB_OK|MB_ICONINFORMATION);
		return false;
	}
	// �򿪷���
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,SERVICE_ALL_ACCESS);
	if( hSvc == NULL)
	{
		MessageBox(GetForegroundWindow(),  m_szServiceDisplayName+_T(" Open Service Error!"),_T("System Infomation"), MB_OK|MB_ICONINFORMATION);
		CloseServiceHandle( hSC);
		return false;
	}
	SERVICE_DESCRIPTION sd;
	sd.lpDescription = szDescription.GetBuffer();
	if( !ChangeServiceConfig2(
		hSvc,                 // handle to service
		SERVICE_CONFIG_DESCRIPTION, // change: description
		&sd) )                      // new description
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	else
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return true;
	}
	return false;
}
// ��÷���������Ϣ
CString CSerControl::GetDescription(/*char* lpDescription*/) 
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return _T("");
	}
	// �򿪷���
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,SERVICE_ALL_ACCESS);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return _T("");
	}
	LPSERVICE_DESCRIPTION lpsd;
	DWORD dwBytesNeeded=0, cbBufSize=0,dwError;
	if( !QueryServiceConfig2( 
		hSvc, 
		SERVICE_CONFIG_DESCRIPTION,
		NULL, 
		0, 
		&dwBytesNeeded))
	{
		dwError = GetLastError();
		if( ERROR_INSUFFICIENT_BUFFER == dwError )
		{
			cbBufSize = dwBytesNeeded;
			lpsd = (LPSERVICE_DESCRIPTION) LocalAlloc(LMEM_FIXED, cbBufSize);
		}
		else
		{
			CloseServiceHandle( hSvc);
			CloseServiceHandle( hSC);
			return _T("");
		}
	}

	if( !QueryServiceConfig2( hSvc, 
		SERVICE_CONFIG_DESCRIPTION,
		(LPBYTE) lpsd, 
		cbBufSize, 
		&dwBytesNeeded))                      // new description
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return _T("");
	}
	else
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return lpsd->lpDescription;
	}
	return _T("");
}
// ��÷������ʾ��
bool CSerControl::GetSerDisplayName(CString& strName)
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// �򿪷���
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,SERVICE_ALL_ACCESS);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	LPQUERY_SERVICE_CONFIG ServicesInfo=(LPQUERY_SERVICE_CONFIG) LocalAlloc(LPTR, 2048);//�����ڴ�
	DWORD     nResumeHandle = 0;
	if(QueryServiceConfig(hSvc,ServicesInfo,2048,&nResumeHandle))//��ѯ��������;
	{
		strName=ServicesInfo->lpDisplayName;
	}
	LocalFree(ServicesInfo);
	CloseServiceHandle( hSvc);
	CloseServiceHandle( hSC);
	return true;
}