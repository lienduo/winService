#pragma once

class CSvrModule
{
public:
	CSvrModule(void);
	~CSvrModule(void);
private:
	static HMODULE GetSelfModuleHandle()
	{
		MEMORY_BASIC_INFORMATION mbi;
		return ((::VirtualQuery(GetSelfModuleHandle,&mbi,sizeof(mbi))!= 0)?(HMODULE) mbi.AllocationBase:NULL);
	}
private:
	typedef int (*BackFun)(void);
	typedef int (*SerInit)(char* ServiceName,BackFun SerStart,BackFun SerStop);
	typedef int (*SetPauseContinue)(BackFun SerPause,BackFun SerContinue);
	typedef int (*RunService)();
	SerInit SvrInit;
	SetPauseContinue SvrSetPauseContinue;
	RunService SvrRunService;
	HMODULE m_hSvrModule;
	char m_szSerName[MAX_PATH];
public:
	// ����ģ��
	bool Load(char* szCmd);
	// ��������(����ͬ�ķ���),������ʾ����(���ڿ���̨��ʾ),����ʼ���к���,ֹͣ����
	int Svr_Init(BackFun SerStart,BackFun SerStop);
	// ������ͣ\����(����ģʽ��ѡ����)
	int Svr_SetPauseContinue(BackFun SerPause,BackFun SerContinue);
	// --------------��ʼ��-------------------

	// ��ʼ����,���ط�0,û�г�ʼ��,���ڷǷ���ģʽ�µ���,true�ڷ���ģʽ�µ��óɹ�
	int Svr_RunService();
};
