#include "StdAfx.h"
#include "FileLog.h"
#include <share.h>
#define log_buf_size 1024

CFileLog::CFileLog(void)
: m_nPath(0)
, m_nLevel(1)
, m_CurHour(-1)
{
	// ��ʼ���ٽ���
	InitializeCriticalSection(&m_cs);
	GetModuleFileName(GetSelfModuleHandle(),m_szPath,MAX_PATH );
	int nLen=strlen(m_szPath);
	for (int i=nLen;i>0;i--) //ȥģ����
	{
		if (m_szPath[i]=='\\'||m_szPath[i]=='/')
		{
			strcpy_s(m_szPath+i+1,MAX_PATH-i-1,_T("Log\\"));// ���Log�ļ���
			break;
		}
	}
	m_nPath=strlen(m_szPath);
	pfp=NULL;
}

CFileLog::~CFileLog(void)
{
	if (pfp!=NULL)
	{
		fclose(pfp);
	}
	// �ͷ����ٽ���
	DeleteCriticalSection(&m_cs);
}

// ����·��
bool CFileLog::SetPath(char* szPath)
{
	EnterCriticalSection(&m_cs);
	strcpy_s(m_szPath,MAX_PATH,szPath);
	LeaveCriticalSection(&m_cs);
	return true;
}

// ���ü���
bool CFileLog::SetLevel(int nLevel)
{
	EnterCriticalSection(&m_cs);
	m_nLevel=nLevel;
	LeaveCriticalSection(&m_cs);
	return true;
}

// дLog
bool CFileLog::WriteLog(int nLevel,char* Fmt,...)
{
	EnterCriticalSection(&m_cs);
	if (nLevel>m_nLevel)
	{
		LeaveCriticalSection(&m_cs);
		return true;
	}
	LeaveCriticalSection(&m_cs);
	try
	{
		// ���Fmt��ʽ
		if (!AfxIsValidString(Fmt, -1))
		{
			return false;
		}
		char sztBuf[log_buf_size];
		time_t curTime;
		struct tm mt;
		curTime = time(NULL);
		localtime_s(&mt,&curTime);
		strftime(sztBuf,log_buf_size,"%Y-%m-%d %H:%M:%S Level:",&mt);
		int nLen=strlen(sztBuf);
		sprintf_s(sztBuf+nLen,log_buf_size-nLen,_T("%d,"),nLevel);
		nLen=strlen(sztBuf);
		va_list argptr;          //�����ַ����ĸ�ʽ
		va_start(argptr, Fmt);
		_vsnprintf_s(sztBuf+nLen, log_buf_size-nLen,_TRUNCATE, Fmt, argptr);
		va_end(argptr);
		EnterCriticalSection(&m_cs);
		if(mt.tm_hour!=m_CurHour) // ÿСʱһ��Log�ļ�
		{
			if (GetFileAttributes(m_szPath) != FILE_ATTRIBUTE_DIRECTORY)//Ŀ¼�����ڴ���
			{
				if(!CreateDirectory(m_szPath, NULL))
				{
					LeaveCriticalSection(&m_cs);
					return false;
				}
			}
			m_CurHour=mt.tm_hour;	
			char szLogFile[MAX_PATH]={0};
			strcpy_s(szLogFile,MAX_PATH,m_szPath);
			strftime(szLogFile+m_nPath,MAX_PATH-m_nPath,"%Y%m%d%H.log",&mt);
			if (NULL!=pfp)
			{
				fclose(pfp);
				pfp=NULL;
			}
			pfp=_fsopen(szLogFile, "a",_SH_DENYNO); //����ӵķ�ʽ������ļ�
			if (NULL==pfp)
			{
				LeaveCriticalSection(&m_cs);
				return false;
			}
		}
		fprintf(pfp,"%s\n",sztBuf);
		fflush(pfp);
		LeaveCriticalSection(&m_cs);
	}
	catch (...)
	{
		return false;
	}
	return true;
}
// дLog
bool CFileLog::WriteLog(char* szLogText)
{
	time_t curTime;
	struct tm mt;
	curTime = time(NULL);
	localtime_s(&mt,&curTime);
	EnterCriticalSection(&m_cs);
	if(mt.tm_hour!=m_CurHour) // ÿСʱһ��Log�ļ�
	{
		if (GetFileAttributes(m_szPath) != FILE_ATTRIBUTE_DIRECTORY)//Ŀ¼�����ڴ���
		{
			if(!CreateDirectory(m_szPath, NULL))
			{
				LeaveCriticalSection(&m_cs);
				return false;
			}
		}
		m_CurHour=mt.tm_hour;	
		char szLogFile[MAX_PATH]={0};
		strcpy_s(szLogFile,MAX_PATH,m_szPath);
		strftime(szLogFile+m_nPath,MAX_PATH-m_nPath,"%Y%m%d%H.log",&mt);
		if (NULL!=pfp)
		{
			fclose(pfp);
			pfp=NULL;
		}
		pfp=_fsopen(szLogFile, "a",_SH_DENYNO); //����ӵķ�ʽ������ļ�
		if (NULL==pfp)
		{
			LeaveCriticalSection(&m_cs);
			return false;
		}
	}
	fprintf(pfp,"%s\n",szLogText);
	fflush(pfp);
	LeaveCriticalSection(&m_cs);
	return true;
}
// ���Log����
int CFileLog::GetLevel(void)
{
	int nLevel=0;
	EnterCriticalSection(&m_cs);
	nLevel=m_nLevel;
	LeaveCriticalSection(&m_cs);
	return nLevel;
}
