#pragma once

class CSvrCtrl
{
public:
	CSvrCtrl(void);
	~CSvrCtrl(void);
private:
	// 初始化
	typedef bool (*SvrInit)(char* szSerName,char* szSerDisplayName);
	// 安装服务
	typedef bool (*SvrInstall)(char* lpAppName,char* lpRef,char* lpDescription);
	// 状态判断
	typedef bool (*SvrIsStatus)(void);
	// 设置服务类型
	typedef bool (*SvrSetServStartType)(int nType) ;
	// 获得服务类型
	typedef UINT (*SvrGetServiceStartType)(void);
	// 设置服务描述
	typedef bool (*SvrSetDescription)(char* lpDescription);
	// 获得服务描述
	typedef char* (*SvrGetDescription)(void);
	// 服务控制句柄
	HMODULE m_hSvrCtrl;
	// 服务初始化
	SvrInit InitSvr;
	// 服务是否安装
	SvrIsStatus Svr_Installed;
	// 安装服务
	SvrInstall InstallSvr;
	// 卸载服务
	SvrIsStatus UninstallSvr;
	// 正在运行
	SvrIsStatus Svr_Running;
	// 暂停
	SvrIsStatus Svr_Paused;
	// 停止
	SvrIsStatus Svr_Stoped;
	// 开始服务
	SvrIsStatus StartSvr;
	// 停止服务
	SvrIsStatus StopSvr;
	// 暂停服务
	SvrIsStatus PauseSvr;
	// 继续服务
	SvrIsStatus ContinueSvr;
	// 设置服务类型
	SvrSetServStartType SetSvrType;
	// 获得服务类型
	SvrGetServiceStartType GetSvrType;
	// 设置描述
	SvrSetDescription SetDescription;
	// 获得描述
	SvrGetDescription GetDescription;

public:
	// 加载模块
	bool Load(void);
	// 初始化
	bool SvrCtr_Init(char* szSerName,char* szSerDisplayName);
	// 判断服务是否安装
	bool SvrCtr_IsInstalled(void);
	// 安装服务 程序参数,服务描述
	bool SvrCtr_Install(char* lpAppName,char* lpRef=NULL,char* lpDescription=NULL);
	// 卸载服务
	bool SvrCtr_Uninstall(void);
	// 判断是否在运行
	bool SvrCtr_IsRunning(void);
	// 判断是否在暂停
	bool SvrCtr_IsPaused(void);
	// 判断是否在停止
	bool SvrCtr_IsStoped(void);
	// 开始服务
	bool SvrCtr_StartService(void);
	// 停止服务
	bool SvrCtr_StopService(void);
	// 暂停服务
	bool SvrCtr_PauseService(void);
	// 恢复服务
	bool SvrCtr_ContinueService(void);
	// 设置服务启动类型
	bool SvrCtr_SetServStartType(int nType) ;
	// 取得服务的启动类型
	UINT SvrCtr_GetServiceStartType(void);
	// 设置服务描述信息
	bool SvrCtr_SetDescription(char* lpDescription);
	// 获得服务描述信息
	char* SvrCtr_GetDescription(void);
};
