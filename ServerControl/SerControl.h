#pragma once
#include <winsvc.h>
class CSerControl
{
public:
	CSerControl(void);
	~CSerControl(void);
	// 服务名称
	CString m_szServiceName;
	// 服务显示名称
	CString m_szServiceDisplayName;
public:
	// 初始化服务名称
	bool Init(CString szSerName,CString szServiceDisplayName=_T(""));
	// 判断是否已安装
	bool IsInstalled();
	// 安装
	bool Install(CString szAppFileName,CString szRef=_T("")/*参数*/,CString szDescription=_T(""));
	// 卸载
	bool Uninstall();
	// 判断是否正在运行
	bool IsRunning();
	// 判断是否正在暂停
	bool IsPaused();
	// 判断是否正在停止
	bool IsStoped();
	// 开始
	bool Start();
	// 停止
	bool Stop();
	// 暂停服务
	bool PauseService();
	//恢复服务
	bool ContinueService();
	// 取得服务的启动类型
	UINT GetServiceStartType() ;
	// 设置服务类型
	bool SetServStartType(UINT nType);
	// 设置服务描述信息
	bool SetDescription(CString szDescription);
	// 获得服务描述信息
	CString GetDescription();
	// 获得服务的显示名
	bool GetSerDisplayName(CString& strName);
};
