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

	// ����Ini�ļ�·��
	BOOL Load(char* szIniFile);
	// --------------��������-------------------
	// ��ȡSection
	void ReadSection(char*** pRes, int* nSize);
	// ������ȡSection
	void EndReadSection(char** pRes);
	// ��ȡKeyValue
	void ReadKeyValue(char*** pRes, int* nSize, LPCTSTR lpSection);
	// ������ȡKeyValue
	void EndReadKeyValue(char** pRes);

	// ���Key
	BOOL GetKey(char* szKeyVal,char* szKey);
	// ���Value
	BOOL GetszValue(char* szKeyVal,char* szValue);
	// -------------------INI����----------------------
	// ���Section
	BOOL AddSection(LPCTSTR szSection,LPCTSTR szKeyValue=_T(""));
	// ɾ��Section
	BOOL DelSection(LPCTSTR szSection);
	// ���KeyValue
	BOOL AddKeyValue(LPCTSTR szKey, LPCTSTR szValue, LPCTSTR szSection);
	// ɾ��Key
	BOOL DelKey(LPCTSTR szKey, LPCTSTR szSection);
	// �༭
	BOOL EditValue(LPCTSTR szKey, LPCTSTR szValue, LPCTSTR szSection);
	// ���szValue
	void GetValue(char* szValue,LPCTSTR szKey, LPCTSTR szSection,LPCTSTR szDefValue=_T(""));
	// ���int Value
	int GetValue( LPCTSTR szKey,LPCTSTR szSection,int nDefValue=0);
};
