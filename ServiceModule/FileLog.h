/*********************************说明*********************************
1.支持多线程 1~100
2.效率(1百万)
 A.单线程:13853ms:72.18657pcs/ms
 B:10线程:6661ms:150.1276pcs/ms,
 C.100线程:7301ms:136.9675pcs/ms
3.使用方法
 可以使用全局对象
4.编程细节
 文件常开,自动推送,串行推入
*********************************说明*********************************/
#pragma once

class CFileLog
{
public:
	CFileLog(void);
	~CFileLog(void);
private:
	static HMODULE GetSelfModuleHandle()
	{
		MEMORY_BASIC_INFORMATION mbi;
		return ((::VirtualQuery(GetSelfModuleHandle,&mbi,sizeof(mbi))!= 0)?(HMODULE) mbi.AllocationBase:NULL);
	}
private:
	// Log路径
	char m_szPath[MAX_PATH];
	// Log路径长度
	int m_nPath;
	// Log级别,级别以下的写入:0,致命错误,1,一般错误,2:调试信息
	int m_nLevel;
	// 临界区
	CRITICAL_SECTION  m_cs;
	FILE* pfp;
	// 当前小时
	int m_CurHour;
public:
	// 设置路径
	bool SetPath(char* szPath);
	// 设置级别
	bool SetLevel(int nLevel);
	// 写Log
	bool WriteLog(int nLevel,char* Fmt,...);
	// 写Log
	bool WriteLog(char* szLogText);
	// 获得Log级别
	int GetLevel(void);
};
