#include "stdafx.h"
#define Server_Ctrl_API extern "C" _declspec(dllexport)
#include "ServerControlExp.h"
#include "SerControl.h"
CSerControl serContrl;

Server_Ctrl_API bool Svr_InitContrl(char* szSerName,char* szSerDisplayName)
{
	return serContrl.Init(szSerName,szSerDisplayName);
}
//判断服务是否安装
Server_Ctrl_API bool Svr_IsInstalled(void)
{
	return serContrl.IsInstalled();
}
//安装服务
Server_Ctrl_API bool Svr_Install(char* lpAppName,char* lpRef,char* lpDescription)
{
	return serContrl.Install(lpAppName,lpRef,lpDescription);
}
//卸载服务
Server_Ctrl_API bool Svr_Uninstall(void)
{
	return serContrl.Uninstall();
}
//判断是否在运行
Server_Ctrl_API bool Svr_IsRunning(void)
{
	return serContrl.IsRunning();
}
// 判断是否在暂停
Server_Ctrl_API bool Svr_IsPaused(void)
{
	return serContrl.IsPaused();
}
// 判断是否在停止
Server_Ctrl_API bool Svr_IsStoped(void)
{
	return serContrl.IsStoped();
}
//开始服务
Server_Ctrl_API bool Svr_StartService(void)
{
	return serContrl.Start();
}
//停止服务
Server_Ctrl_API bool Svr_StopService(void)
{
	return serContrl.Stop();
}
// 暂停服务
Server_Ctrl_API bool Svr_PauseService(void)
{
	return serContrl.PauseService();
}
//恢复服务
Server_Ctrl_API bool Svr_ContinueService(void)
{
	return serContrl.ContinueService();
}
// 设置服务启动类型
Server_Ctrl_API bool Svr_SetServStartType(int nType) 
{
	return serContrl.SetServStartType(nType);
}
// 取得服务的启动类型
Server_Ctrl_API UINT Svr_GetServiceStartType(void)
{
	return serContrl.GetServiceStartType();
}
// 设置服务描述信息
Server_Ctrl_API bool Svr_SetDescription(char* lpDescription)
{
	return serContrl.SetDescription(lpDescription);
}
// 获得服务描述信息
Server_Ctrl_API char* Svr_GetDescription(void)
{
	return serContrl.GetDescription().GetBuffer();
}