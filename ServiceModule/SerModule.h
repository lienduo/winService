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
	// ������
	CString m_szServiceName;
	// ������ʾ��
	CString m_strDisplayName;
	// ������
	SERVICE_STATUS_HANDLE m_hServiceStatus;
	// ����״̬�ṹ
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
	// ��÷������ʾ��
	bool GetSerDisplayName(CString& strName);
public:
	//��ʼ��
	int Init(CString ServiceName,BackFun SerStart,BackFun SerStop);
	// ������ͣ�ͼ���
	int SetPauseContinue(BackFun serPause, BackFun serContinue);
	// ��������
	int RunService(void);
};
