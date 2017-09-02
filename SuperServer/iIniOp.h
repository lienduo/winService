#pragma once
#include <sys/stat.h>

class CiIniOp
{
public:
	CiIniOp(void);
	~CiIniOp(void);
private:
	unsigned long get_file_size(const char *filename)
	{
		struct _stat buf;
		if(_stat(filename, &buf)<0)
		{
			return 0;
		}
		return (unsigned long)buf.st_size;
	}
	static HMODULE GetSelfModuleHandle()
	{
		MEMORY_BASIC_INFORMATION mbi;
		return ((::VirtualQuery(GetSelfModuleHandle,&mbi,sizeof(mbi))!= 0)?(HMODULE) mbi.AllocationBase:NULL);
	} 
	char m_szIniPath[MAX_PATH];
public:

	// 设置Ini文件路径
	BOOL Load(char* szIniFile);
	// --------------遍历操作-------------------
	// 读取Section
	void ReadSection(char*** pRes, int* nSize);
	// 结束读取Section
	void EndReadSection(char** pRes);
	// 获取KeyValue
	void ReadKeyValue(char*** pRes, int* nSize, LPCTSTR lpSection);
	// 结束读取KeyValue
	void EndReadKeyValue(char** pRes);

	// 获得Key
	BOOL GetKey(char* szKeyVal,char* szKey);
	// 获得Value
	BOOL GetszValue(char* szKeyVal,char* szValue);
	// -------------------INI操作----------------------
	// 添加Section
	BOOL AddSection(LPCTSTR szSection,LPCTSTR szKeyValue=_T(""));
	// 删除Section
	BOOL DelSection(LPCTSTR szSection);
	// 添加KeyValue
	BOOL AddKeyValue(LPCTSTR szKey, LPCTSTR szValue, LPCTSTR szSection);
	// 删除Key
	BOOL DelKey(LPCTSTR szKey, LPCTSTR szSection);
	// 编辑
	BOOL EditValue(LPCTSTR szKey, LPCTSTR szValue, LPCTSTR szSection);
	// 获得szValue
	void GetValue(char* szValue,LPCTSTR szKey, LPCTSTR szSection,LPCTSTR szDefValue=_T(""));
	// 获得int Value
	int GetValue( LPCTSTR szKey,LPCTSTR szSection,int nDefValue=0);
};
