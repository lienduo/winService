#include "StdAfx.h"
#include "iIniOp.h"
#define  BUF_SIZE 32767
#include  <io.h>
#include <stdio.h>

CiIniOp::CiIniOp(void)
{
}

CiIniOp::~CiIniOp(void)
{
}

// 设置Ini文件路径
BOOL CiIniOp::Load(char* szIniFile)
{
	static char szFilePath[_MAX_PATH]={0};
	if (':'!=szIniFile[1])
	{
		if (strlen(szFilePath)==0)
		{
			GetModuleFileName(GetSelfModuleHandle(),szFilePath,MAX_PATH);
			int nLen=strlen(szFilePath);
			for (int i=nLen;i>0;i--)
			{
				if (szFilePath[i]=='\\')
				{
					szFilePath[i+1]='\0';
					break;
				}
			}
		}
		sprintf_s(m_szIniPath,MAX_PATH,_T("%s%s"),szFilePath,szIniFile);
	}
	else
	{
		sprintf_s(m_szIniPath,MAX_PATH,_T("%s"),szIniFile);
	}
	if(_access(m_szIniPath,0)!= -1 )// 判断文件是否存在  
	{
		return TRUE;
	}
	return FALSE;
}

// --------------------遍历----------------------------

// 读取Section
void CiIniOp::ReadSection(char*** pRes, int* nSize)
{
	// 文件大小
	int nfileSize=get_file_size(m_szIniPath);
	nfileSize+=1;
	char** pTemp=new char*[MAX_PATH];// 限制259个Section
	char* pData=new char[nfileSize];
	int nLen=GetPrivateProfileString(NULL,NULL,NULL,pData,BUF_SIZE,m_szIniPath);
	if (nLen==0)
	{
		delete[] pTemp;
		delete[] pData;
		*nSize=0;
		*pRes=NULL;
		return;
	}
	int nPos=0;
	while(nLen-nPos>0)
	{
		pTemp[*nSize+1]=pData+nPos;
		nPos+=strlen(pData+nPos)+1;
		(*nSize)++;
		if (*nSize>=MAX_PATH-1)
		{
			break;
		}
	}
	pTemp[0]=pData;
	*pRes=pTemp+1;// 获取数据
}

// 结束读取Section
void CiIniOp::EndReadSection(char** pRes)
{
	if (pRes!=NULL)
	{
		pRes=pRes-1;
		delete[] pRes[0];
		delete[] pRes;
	}
}

// 获取KeyValue
void CiIniOp::ReadKeyValue(char*** pRes, int* nSize, LPCTSTR lpSection)
{
	// 文件大小
	int nfileSize=get_file_size(m_szIniPath);
	nfileSize+=1;
	char** pTemp=new char*[MAX_PATH]; // 限制Key少于259
	char* pData=new char[nfileSize];
	int nLen=GetPrivateProfileSection(lpSection,pData,BUF_SIZE,m_szIniPath);
	if (nLen==0)
	{
		delete[] pTemp;
		delete[] pData;
		*nSize=0;
		*pRes=NULL;
		return;
	}
	int nPos=0;
	while(nLen-nPos>0)
	{
		pTemp[*nSize+1]=pData+nPos;
		nPos+=strlen(pData+nPos)+1;
		(*nSize)++;
		if (*nSize>=MAX_PATH-1)
		{
			break;
		}
	}
	pTemp[0]=pData;
	*pRes=pTemp+1;
}

// 结束读取KeyValue
void CiIniOp::EndReadKeyValue(char** pRes)
{
	if (pRes!=NULL)
	{
		pRes=pRes-1;
		delete[] pRes[0];
		delete[] pRes;
	}
}
// ----------------------遍历获取Key\Value-------------------
// 获得Key
BOOL CiIniOp::GetKey(char* szKeyVal, char* szKey)
{
	int nLen=strlen(szKeyVal);
	for (int i=0;i<nLen;i++)
	{
		if ('='==szKeyVal[i]) // 查找Key
		{
			strcpy_s(szKey,MAX_PATH,szKeyVal);
			szKey[i]='\0';
			return TRUE;
		}
	}
	return FALSE;
}
// 获得Value
BOOL CiIniOp::GetszValue(char* szKeyVal,char* szValue)
{
	int nLen=strlen(szKeyVal);
	for (int i=0;i<nLen;i++)
	{
		if ('='==szKeyVal[i]) // 查找Key
		{
			strcpy_s(szValue,MAX_PATH,szKeyVal+i+1);
			return TRUE;
		}
	}
	return FALSE;
}

// ---------------INI 操作-----------------------
// 添加Section
BOOL CiIniOp::AddSection(LPCTSTR szSection,LPCTSTR szKeyValue)
{
	if (szSection==_T(""))
	{
		return FALSE;
	}
	char** pRes=NULL;
	int nSize=0;
	ReadSection(&pRes,&nSize);
	for (int i=0;i<nSize;i++)
	{
		if (_stricmp(szSection,pRes[i])==0)
		{
			EndReadSection(pRes);
			return FALSE;
		}
	}
	EndReadSection(pRes);
	return WritePrivateProfileSection(szSection,szKeyValue,m_szIniPath);
}

// 删除Section
BOOL CiIniOp::DelSection(LPCTSTR szSection)
{
	if (szSection==_T(""))
	{
		return FALSE;
	}
	return WritePrivateProfileSection(szSection,NULL,m_szIniPath);
}

// 添加KeyValue
BOOL CiIniOp::AddKeyValue(LPCTSTR szKey, LPCTSTR szValue, LPCTSTR szSection)
{
	if (szKey==_T("")||szSection==_T(""))
	{
		return FALSE;
	}
	char** pRes=NULL;
	int nSize=0;
	ReadKeyValue(&pRes,&nSize,szSection);
	for (int i=0;i<nSize;i++)
	{
		int nLen=strlen(pRes[i]);
		for (int n=0;n<nLen;n++)
		{
			if ('='==pRes[i][n])
			{
				char szTemp[MAX_PATH];
				strcpy_s(szTemp,MAX_PATH,pRes[i]);
				szTemp[n]='\0';
				if (_stricmp(szKey,szTemp)==0)
				{
					EndReadKeyValue(pRes);
					return FALSE;
				}
				break;
			}
		}
	}
	EndReadKeyValue(pRes);
	return WritePrivateProfileString(szSection,szKey,szValue,m_szIniPath);
}

// 删除Key
BOOL CiIniOp::DelKey(LPCTSTR szKey, LPCTSTR szSection)
{
	if (szKey==_T("")||szSection==_T(""))
	{
		return FALSE;
	}
	// Key是否存在
	BOOL bRes=FALSE;
	char** pRes=NULL;
	int nSize=0;
	ReadKeyValue(&pRes,&nSize,szSection);
	for (int i=0;i<nSize;i++)
	{
		int nLen=strlen(pRes[i]);
		for (int n=0;n<nLen;n++)
		{
			if ('='==pRes[i][n]) // 查找Key
			{
				char szTemp[MAX_PATH];
				strcpy_s(szTemp,MAX_PATH,pRes[i]);
				szTemp[n]='\0';
				if (_stricmp(szKey,szTemp)==0)
				{
					bRes=TRUE;
					break;
				}
				continue;
			}
		}
		if (bRes)
		{
			break;
		}
	}
	EndReadKeyValue(pRes);
	return bRes&&WritePrivateProfileString(szSection,szKey,NULL,m_szIniPath);
}

// 编辑
BOOL CiIniOp::EditValue(LPCTSTR szKey, LPCTSTR szValue, LPCTSTR szSection)
{
	if (szKey==_T("")||szSection==_T(""))
	{
		return FALSE;
	}
	// Key是否存在
	BOOL bRes=FALSE;
	char** pRes=NULL;
	int nSize=0;
	ReadKeyValue(&pRes,&nSize,szSection);
	for (int i=0;i<nSize;i++)
	{
		int nLen=strlen(pRes[i]);
		for (int n=0;n<nLen;n++)
		{
			if ('='==pRes[i][n]) // 查找Key
			{
				char szTemp[MAX_PATH];
				strcpy_s(szTemp,MAX_PATH,pRes[i]);
				szTemp[n]='\0';
				if (_stricmp(szKey,szTemp)==0)
				{
					bRes=TRUE;
					break;
				}
				continue;
			}
		}
		if (bRes)
		{
			break;
		}
	}
	EndReadKeyValue(pRes);
	return bRes&&WritePrivateProfileString(szSection,szKey,szValue,m_szIniPath);
}

// 获得szValue
void CiIniOp::GetValue(char* szValue,LPCTSTR szKey, LPCTSTR szSection, LPCTSTR szDefValue)
{
	GetPrivateProfileString(szSection,szKey,szDefValue,szValue,MAX_PATH,m_szIniPath);
}
// 获得int Value
int CiIniOp::GetValue( LPCTSTR szKey,LPCTSTR szSection,int nDefValue)
{
	return GetPrivateProfileInt(szSection,szKey,nDefValue,m_szIniPath);
}
