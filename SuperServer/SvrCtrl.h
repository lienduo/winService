#pragma once

class CSvrCtrl
{
public:
	CSvrCtrl(void);
	~CSvrCtrl(void);
private:
	// ��ʼ��
	typedef bool (*SvrInit)(char* szSerName,char* szSerDisplayName);
	// ��װ����
	typedef bool (*SvrInstall)(char* lpAppName,char* lpRef,char* lpDescription);
	// ״̬�ж�
	typedef bool (*SvrIsStatus)(void);
	// ���÷�������
	typedef bool (*SvrSetServStartType)(int nType) ;
	// ��÷�������
	typedef UINT (*SvrGetServiceStartType)(void);
	// ���÷�������
	typedef bool (*SvrSetDescription)(char* lpDescription);
	// ��÷�������
	typedef char* (*SvrGetDescription)(void);
	// ������ƾ��
	HMODULE m_hSvrCtrl;
	// �����ʼ��
	SvrInit InitSvr;
	// �����Ƿ�װ
	SvrIsStatus Svr_Installed;
	// ��װ����
	SvrInstall InstallSvr;
	// ж�ط���
	SvrIsStatus UninstallSvr;
	// ��������
	SvrIsStatus Svr_Running;
	// ��ͣ
	SvrIsStatus Svr_Paused;
	// ֹͣ
	SvrIsStatus Svr_Stoped;
	// ��ʼ����
	SvrIsStatus StartSvr;
	// ֹͣ����
	SvrIsStatus StopSvr;
	// ��ͣ����
	SvrIsStatus PauseSvr;
	// ��������
	SvrIsStatus ContinueSvr;
	// ���÷�������
	SvrSetServStartType SetSvrType;
	// ��÷�������
	SvrGetServiceStartType GetSvrType;
	// ��������
	SvrSetDescription SetDescription;
	// �������
	SvrGetDescription GetDescription;

public:
	// ����ģ��
	bool Load(void);
	// ��ʼ��
	bool SvrCtr_Init(char* szSerName,char* szSerDisplayName);
	// �жϷ����Ƿ�װ
	bool SvrCtr_IsInstalled(void);
	// ��װ���� �������,��������
	bool SvrCtr_Install(char* lpAppName,char* lpRef=NULL,char* lpDescription=NULL);
	// ж�ط���
	bool SvrCtr_Uninstall(void);
	// �ж��Ƿ�������
	bool SvrCtr_IsRunning(void);
	// �ж��Ƿ�����ͣ
	bool SvrCtr_IsPaused(void);
	// �ж��Ƿ���ֹͣ
	bool SvrCtr_IsStoped(void);
	// ��ʼ����
	bool SvrCtr_StartService(void);
	// ֹͣ����
	bool SvrCtr_StopService(void);
	// ��ͣ����
	bool SvrCtr_PauseService(void);
	// �ָ�����
	bool SvrCtr_ContinueService(void);
	// ���÷�����������
	bool SvrCtr_SetServStartType(int nType) ;
	// ȡ�÷������������
	UINT SvrCtr_GetServiceStartType(void);
	// ���÷���������Ϣ
	bool SvrCtr_SetDescription(char* lpDescription);
	// ��÷���������Ϣ
	char* SvrCtr_GetDescription(void);
};
