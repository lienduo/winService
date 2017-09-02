/*********************************˵��*********************************
1.֧�ֶ��߳� 1~100
2.Ч��(1����)
 A.���߳�:13853ms:72.18657pcs/ms
 B:10�߳�:6661ms:150.1276pcs/ms,
 C.100�߳�:7301ms:136.9675pcs/ms
3.ʹ�÷���
 ����ʹ��ȫ�ֶ���
4.���ϸ��
 �ļ�����,�Զ�����,��������
*********************************˵��*********************************/
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
	// Log·��
	char m_szPath[MAX_PATH];
	// Log·������
	int m_nPath;
	// Log����,�������µ�д��:0,��������,1,һ�����,2:������Ϣ
	int m_nLevel;
	// �ٽ���
	CRITICAL_SECTION  m_cs;
	FILE* pfp;
	// ��ǰСʱ
	int m_CurHour;
public:
	// ����·��
	bool SetPath(char* szPath);
	// ���ü���
	bool SetLevel(int nLevel);
	// дLog
	bool WriteLog(int nLevel,char* Fmt,...);
	// дLog
	bool WriteLog(char* szLogText);
	// ���Log����
	int GetLevel(void);
};
