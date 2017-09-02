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

// 初始化服务名称
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
		SetDescription(szDescription.GetBuffer());// 服务描述
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
//查询是否开启
bool CSerControl::IsRunning()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// 打开服务。
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// 获得服务的状态
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
// 判断是否正在暂停
bool CSerControl::IsPaused()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// 打开服务。
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// 获得服务的状态
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
// 判断是否正在停止
bool CSerControl::IsStoped()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// 打开服务。
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// 获得服务的状态
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
//开启服务
bool CSerControl::Start()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// 打开服务。
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// 获得服务的状态
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
		// 启动服务
		if( ::StartService( hSvc, NULL, NULL) == FALSE)
		{
			CloseServiceHandle( hSvc);
			CloseServiceHandle( hSC);
			return false;
		}
		// 等待服务启动
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
//关闭服务
bool CSerControl::Stop()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// 打开服务。
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,
		SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// 获得服务的状态
	SERVICE_STATUS status;
	if( QueryServiceStatus( hSvc, &status) == FALSE)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	//如果处于停止状态则启动服务，否则停止服务。
	if( status.dwCurrentState == SERVICE_RUNNING)
	{
		// 停止服务
		if( ::ControlService( hSvc, 
			SERVICE_CONTROL_STOP, &status) == FALSE)
		{
			CloseServiceHandle( hSvc);
			CloseServiceHandle( hSC);
			return false;
		}
		// 等待服务停止
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
// 暂停服务
bool CSerControl::PauseService()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// 打开服务。
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,SERVICE_ALL_ACCESS);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// 获得服务的状态
	SERVICE_STATUS status;
	if(QueryServiceStatus( hSvc, &status) == false)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	//如果处于启动状态，暂停服务。
	if(status.dwCurrentState == SERVICE_RUNNING)
	{
		// 停止服务
		if( ::ControlService( hSvc,SERVICE_CONTROL_PAUSE, &status) == FALSE)
		{
			CloseServiceHandle( hSvc);
			CloseServiceHandle( hSC);
			return false;
		}
		// 等待服务停止
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
//恢复服务
bool CSerControl::ContinueService()
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// 打开服务。
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,SERVICE_ALL_ACCESS);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	// 获得服务的状态
	SERVICE_STATUS status;
	if(QueryServiceStatus( hSvc, &status) == false)
	{
		CloseServiceHandle( hSvc);
		CloseServiceHandle( hSC);
		return false;
	}
	if(status.dwCurrentState == SERVICE_PAUSED)
	{
		// 停止服务
		if( ::ControlService( hSvc,SERVICE_CONTROL_CONTINUE, &status) == FALSE)
		{
			CloseServiceHandle( hSvc);
			CloseServiceHandle( hSC);
			return false;
		}
		// 等待服务停止
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

// 设置服务类型
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
	// 打开服务。
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
// 取得服务的启动类型
UINT CSerControl::GetServiceStartType() 
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return -1;
	}
	// 打开服务。
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
// 设置服务描述信息
bool CSerControl::SetDescription(CString szDescription) 
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		MessageBox(GetForegroundWindow(),  m_szServiceDisplayName+_T(" Open SCManager Error!"),_T("System Infomation"), MB_OK|MB_ICONINFORMATION);
		return false;
	}
	// 打开服务。
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
// 获得服务描述信息
CString CSerControl::GetDescription(/*char* lpDescription*/) 
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return _T("");
	}
	// 打开服务。
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
// 获得服务的显示名
bool CSerControl::GetSerDisplayName(CString& strName)
{
	SC_HANDLE hSC = OpenSCManager( NULL, 
		NULL, GENERIC_EXECUTE);
	if( hSC == NULL)
	{
		return false;
	}
	// 打开服务。
	SC_HANDLE hSvc = OpenService( hSC, m_szServiceName,SERVICE_ALL_ACCESS);
	if( hSvc == NULL)
	{
		CloseServiceHandle( hSC);
		return false;
	}
	LPQUERY_SERVICE_CONFIG ServicesInfo=(LPQUERY_SERVICE_CONFIG) LocalAlloc(LPTR, 2048);//分配内存
	DWORD     nResumeHandle = 0;
	if(QueryServiceConfig(hSvc,ServicesInfo,2048,&nResumeHandle))//查询服务配置;
	{
		strName=ServicesInfo->lpDisplayName;
	}
	LocalFree(ServicesInfo);
	CloseServiceHandle( hSvc);
	CloseServiceHandle( hSC);
	return true;
}