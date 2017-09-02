#include "stdafx.h"
#define Server_Ctrl_API extern "C" _declspec(dllexport)
#include "ServerControlExp.h"
#include "SerControl.h"
CSerControl serContrl;

Server_Ctrl_API bool Svr_InitContrl(char* szSerName,char* szSerDisplayName)
{
	return serContrl.Init(szSerName,szSerDisplayName);
}
//�жϷ����Ƿ�װ
Server_Ctrl_API bool Svr_IsInstalled(void)
{
	return serContrl.IsInstalled();
}
//��װ����
Server_Ctrl_API bool Svr_Install(char* lpAppName,char* lpRef,char* lpDescription)
{
	return serContrl.Install(lpAppName,lpRef,lpDescription);
}
//ж�ط���
Server_Ctrl_API bool Svr_Uninstall(void)
{
	return serContrl.Uninstall();
}
//�ж��Ƿ�������
Server_Ctrl_API bool Svr_IsRunning(void)
{
	return serContrl.IsRunning();
}
// �ж��Ƿ�����ͣ
Server_Ctrl_API bool Svr_IsPaused(void)
{
	return serContrl.IsPaused();
}
// �ж��Ƿ���ֹͣ
Server_Ctrl_API bool Svr_IsStoped(void)
{
	return serContrl.IsStoped();
}
//��ʼ����
Server_Ctrl_API bool Svr_StartService(void)
{
	return serContrl.Start();
}
//ֹͣ����
Server_Ctrl_API bool Svr_StopService(void)
{
	return serContrl.Stop();
}
// ��ͣ����
Server_Ctrl_API bool Svr_PauseService(void)
{
	return serContrl.PauseService();
}
//�ָ�����
Server_Ctrl_API bool Svr_ContinueService(void)
{
	return serContrl.ContinueService();
}
// ���÷�����������
Server_Ctrl_API bool Svr_SetServStartType(int nType) 
{
	return serContrl.SetServStartType(nType);
}
// ȡ�÷������������
Server_Ctrl_API UINT Svr_GetServiceStartType(void)
{
	return serContrl.GetServiceStartType();
}
// ���÷���������Ϣ
Server_Ctrl_API bool Svr_SetDescription(char* lpDescription)
{
	return serContrl.SetDescription(lpDescription);
}
// ��÷���������Ϣ
Server_Ctrl_API char* Svr_GetDescription(void)
{
	return serContrl.GetDescription().GetBuffer();
}