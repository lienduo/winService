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
	// 加载模块
	bool Load(char* szCmd);
	// 服务名称(区别不同的服务),服务显示名称(用于控制台显示),服务开始运行函数,停止函数
	int Svr_Init(BackFun SerStart,BackFun SerStop);
	// 设置暂停\继续(服务模式可选设置)
	int Svr_SetPauseContinue(BackFun SerPause,BackFun SerContinue);
	// --------------初始化-------------------

	// 开始服务,返回非0,没有初始化,或在非服务模式下调用,true在服务模式下调用成功
	int Svr_RunService();
};
