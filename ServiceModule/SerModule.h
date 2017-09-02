#pragma once
#include <Windows.h>
#include <winsvc.h>
#include <fstream>
#include <locale>
#include <atlstr.h>
#include <atltime.h>

class CSerModule
{
public:
	CSerModule(void);
	~CSerModule(void);
private:
	typedef int (*BackFun)();
	void LogEvent(LPCTSTR pFormat, ...)
	{
		TCHAR    chMsg[512];
		HANDLE  hEventSource;
		LPTSTR  lpszStrings[1];
		va_list pArg;

		va_start(pArg, pFormat);
		_vstprintf_s(chMsg,512, pFormat, pArg);
		va_end(pArg);

		lpszStrings[0] = chMsg;

		/*if (m_bService)
		{*/
		hEventSource = RegisterEventSource(NULL, m_szServiceName);
		if (hEventSource != NULL)
		{
			ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, (LPCTSTR*) &lpszStrings[0], NULL);
			DeregisterEventSource(hEventSource);
		}
		/*}*/
		/*else
		{
		_putts(chMsg);
		}*/
	}
	
private:
	// 服务名
	CString m_szServiceName;
	// 服务显示名
	CString m_strDisplayName;
	// 服务句柄
	SERVICE_STATUS_HANDLE m_hServiceStatus;
	// 服务状态结构
	SERVICE_STATUS m_status;
	//DWORD dwThreadID;
	BackFun m_SerStart;
	BackFun m_SerStop;
	BackFun m_SerPause;
	BackFun m_SerContinue;
	//HANDLE m_handle;
private:
	void SetSerStatus(DWORD dwState);
	void SerMain(DWORD dwArgc, LPTSTR* lpszArgv);
	void Handler(DWORD dwOpcode);
	static void WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
	static void WINAPI SerCtrlHandler(DWORD dwOpcode);
	// 获得服务的显示名
	bool GetSerDisplayName(CString& strName);
public:
	//初始化
	int Init(CString ServiceName,BackFun SerStart,BackFun SerStop);
	// 设置暂停和继续
	int SetPauseContinue(BackFun serPause, BackFun serContinue);
	// 开启服务
	int RunService(void);
};
