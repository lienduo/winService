#pragma once
class CSvrLib
{
public:
	CSvrLib(void);
	~CSvrLib(void);
private:
	static HMODULE GetSelfModuleHandle()
	{
		MEMORY_BASIC_INFORMATION mbi;
		return ((::VirtualQuery(GetSelfModuleHandle,&mbi,sizeof(mbi))!= 0)?(HMODULE) mbi.AllocationBase:NULL);
	}
private:
	typedef int (*BackFun)();
	// 服务句柄
	HMODULE m_hSvrLib;
	BackFun m_SerStart;
	BackFun m_SerPause;
	BackFun m_SerContinue;
	BackFun m_SerStop;
	BackFun m_GetStatus;
public:
	// 加载服务Lib
	bool Load(char* szCmd);
	BackFun GetSerStart();
	BackFun GetSerPause();
	BackFun GetSerContinue();
	BackFun GetSerStop();
	int GetStatus();
};
