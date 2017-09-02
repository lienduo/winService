#pragma once
#ifdef Server_Ctrl_API
#else
#pragma comment(lib,"ServerControl.lib")
#define Server_Ctrl_API extern "C" _declspec(dllimport)
#endif
enum ServType // ������������
{
	SERV_BOOT_START=0x00000000,
	SERV_SYSTEM_START,
	SERV_AUTO_START,   // �Զ�
	SERV_DEMAND_START, // �ֶ�
	SERV_DISABLED,     //��ֹ
};
// ��ʼ��
Server_Ctrl_API bool Svr_InitContrl(char* szSerName,char* szSerDisplayName);
// �жϷ����Ƿ�װ
Server_Ctrl_API bool Svr_IsInstalled(void);
// ��װ���� �������,��������
Server_Ctrl_API bool Svr_Install(char* lpAppName,char* lpRef=NULL,char* lpDescription=NULL);
// ж�ط���
Server_Ctrl_API bool Svr_Uninstall(void);
// �ж��Ƿ�������
Server_Ctrl_API bool Svr_IsRunning(void);
// �ж��Ƿ�����ͣ
Server_Ctrl_API bool Svr_IsPaused(void);
// �ж��Ƿ���ֹͣ
Server_Ctrl_API bool Svr_IsStoped(void);
// ��ʼ����
Server_Ctrl_API bool Svr_StartService(void);
// ֹͣ����
Server_Ctrl_API bool Svr_StopService(void);
// ��ͣ����
Server_Ctrl_API bool Svr_PauseService(void);
// �ָ�����
Server_Ctrl_API bool Svr_ContinueService(void);
// ���÷�����������
Server_Ctrl_API bool Svr_SetServStartType(int nType) ;
// ȡ�÷������������
Server_Ctrl_API UINT Svr_GetServiceStartType(void);
// ���÷���������Ϣ
Server_Ctrl_API bool Svr_SetDescription(char* lpDescription);
// ��÷���������Ϣ
Server_Ctrl_API char* Svr_GetDescription(void);