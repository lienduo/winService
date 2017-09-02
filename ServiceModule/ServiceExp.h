/************************************************************************
一个进程一个服务
同一个程序可以通过不同的启动参数,启动不同的服务

服务模式函数和非服务模式函数
************************************************************************/

#pragma once
#ifdef Service_COp_API
#else
#pragma comment(lib,"ServiceModule.lib")
#define Service_COp_API extern "C" _declspec(dllimport)
#endif

typedef int (*BackFun)(void);

// --------------初始化-------------------
// 服务名称(区别不同的服务),服务显示名称(用于控制台显示),服务开始运行函数,停止函数
Service_COp_API int Ser_Init(char* ServiceName,BackFun SerStart,BackFun SerStop);
// 设置暂停\继续(服务模式可选设置)
Service_COp_API int Ser_SetPauseContinue(BackFun SerPause,BackFun SerContinue);
// --------------初始化-------------------

// 开始服务,返回非0,没有初始化,或在非服务模式下调用,true在服务模式下调用成功
Service_COp_API int Ser_RunService();
// ----------------服务模式-----------------------
