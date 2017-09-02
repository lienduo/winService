#include "StdAfx.h"
#include "FileLog.h"
#include <share.h>
#define log_buf_size 1024

CFileLog::CFileLog(void)
: m_nPath(0)
, m_nLevel(1)
, m_CurHour(-1)
{
	// 初始化临界区
	InitializeCriticalSection(&m_cs);
	GetModuleFileName(GetSelfModuleHandle(),m_szPath,MAX_PATH );
	int nLen=strlen(m_szPath);
	for (int i=nLen;i>0;i--) //去模块名
	{
		if (m_szPath[i]=='\\'||m_szPath[i]=='/')
		{
			strcpy_s(m_szPath+i+1,MAX_PATH-i-1,_T("Log\\"));// 添加Log文件夹
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
	// 释放里临界区
	DeleteCriticalSection(&m_cs);
}

// 设置路径
bool CFileLog::SetPath(char* szPath)
{
	EnterCriticalSection(&m_cs);
	strcpy_s(m_szPath,MAX_PATH,szPath);
	LeaveCriticalSection(&m_cs);
	return true;
}

// 设置级别
bool CFileLog::SetLevel(int nLevel)
{
	EnterCriticalSection(&m_cs);
	m_nLevel=nLevel;
	LeaveCriticalSection(&m_cs);
	return true;
}

// 写Log
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
		// 检测Fmt格式
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
		va_list argptr;          //分析字符串的格式
		va_start(argptr, Fmt);
		_vsnprintf_s(sztBuf+nLen, log_buf_size-nLen,_TRUNCATE, Fmt, argptr);
		va_end(argptr);
		EnterCriticalSection(&m_cs);
		if(mt.tm_hour!=m_CurHour) // 每小时一个Log文件
		{
			if (GetFileAttributes(m_szPath) != FILE_ATTRIBUTE_DIRECTORY)//目录不存在创建
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
			pfp=_fsopen(szLogFile, "a",_SH_DENYNO); //以添加的方式输出到文件
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
// 写Log
bool CFileLog::WriteLog(char* szLogText)
{
	time_t curTime;
	struct tm mt;
	curTime = time(NULL);
	localtime_s(&mt,&curTime);
	EnterCriticalSection(&m_cs);
	if(mt.tm_hour!=m_CurHour) // 每小时一个Log文件
	{
		if (GetFileAttributes(m_szPath) != FILE_ATTRIBUTE_DIRECTORY)//目录不存在创建
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
		pfp=_fsopen(szLogFile, "a",_SH_DENYNO); //以添加的方式输出到文件
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
// 获得Log级别
int CFileLog::GetLevel(void)
{
	int nLevel=0;
	EnterCriticalSection(&m_cs);
	nLevel=m_nLevel;
	LeaveCriticalSection(&m_cs);
	return nLevel;
}
