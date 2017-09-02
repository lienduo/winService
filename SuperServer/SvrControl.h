#pragma once
typedef bool (*SvrInit)(char* szSerName,char* szSerDisplayName);
typedef bool (*SvrInstall)(char* lpAppName,char* lpRef,char* lpDescription);
typedef bool (*SvrIsStatus)(void);
typedef bool (*SvrSetServStartType)(int nType) ;
typedef UINT (*SvrGetServiceStartType)(void);
typedef bool (*SvrSetDescription)(char* lpDescription);
typedef char* (*SvrGetDescription)(void);