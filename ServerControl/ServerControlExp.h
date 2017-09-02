#pragma once
#ifdef Server_Ctrl_API
#else
#pragma comment(lib,"ServerControl.lib")
#define Server_Ctrl_API extern "C" _declspec(dllimport)
#endif
enum ServType // 服务启动类型
{
	SERV_BOOT_START=0x00000000,
	SERV_SYSTEM_START,
	SERV_AUTO_START,   // 自动
	SERV_DEMAND_START, // 手动
	SERV_DISABLED,     //禁止
};
// 初始化
Server_Ctrl_API bool Svr_InitContrl(char* szSerName,char* szSerDisplayName);
// 判断服务是否安装
Server_Ctrl_API bool Svr_IsInstalled(void);
// 安装服务 程序参数,服务描述
Server_Ctrl_API bool Svr_Install(char* lpAppName,char* lpRef=NULL,char* lpDescription=NULL);
// 卸载服务
Server_Ctrl_API bool Svr_Uninstall(void);
// 判断是否在运行
Server_Ctrl_API bool Svr_IsRunning(void);
// 判断是否在暂停
Server_Ctrl_API bool Svr_IsPaused(void);
// 判断是否在停止
Server_Ctrl_API bool Svr_IsStoped(void);
// 开始服务
Server_Ctrl_API bool Svr_StartService(void);
// 停止服务
Server_Ctrl_API bool Svr_StopService(void);
// 暂停服务
Server_Ctrl_API bool Svr_PauseService(void);
// 恢复服务
Server_Ctrl_API bool Svr_ContinueService(void);
// 设置服务启动类型
Server_Ctrl_API bool Svr_SetServStartType(int nType) ;
// 取得服务的启动类型
Server_Ctrl_API UINT Svr_GetServiceStartType(void);
// 设置服务描述信息
Server_Ctrl_API bool Svr_SetDescription(char* lpDescription);
// 获得服务描述信息
Server_Ctrl_API char* Svr_GetDescription(void);