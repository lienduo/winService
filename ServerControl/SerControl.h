#pragma once
#include <winsvc.h>
class CSerControl
{
public:
	CSerControl(void);
	~CSerControl(void);
	// ��������
	CString m_szServiceName;
	// ������ʾ����
	CString m_szServiceDisplayName;
public:
	// ��ʼ����������
	bool Init(CString szSerName,CString szServiceDisplayName=_T(""));
	// �ж��Ƿ��Ѱ�װ
	bool IsInstalled();
	// ��װ
	bool Install(CString szAppFileName,CString szRef=_T("")/*����*/,CString szDescription=_T(""));
	// ж��
	bool Uninstall();
	// �ж��Ƿ���������
	bool IsRunning();
	// �ж��Ƿ�������ͣ
	bool IsPaused();
	// �ж��Ƿ�����ֹͣ
	bool IsStoped();
	// ��ʼ
	bool Start();
	// ֹͣ
	bool Stop();
	// ��ͣ����
	bool PauseService();
	//�ָ�����
	bool ContinueService();
	// ȡ�÷������������
	UINT GetServiceStartType() ;
	// ���÷�������
	bool SetServStartType(UINT nType);
	// ���÷���������Ϣ
	bool SetDescription(CString szDescription);
	// ��÷���������Ϣ
	CString GetDescription();
	// ��÷������ʾ��
	bool GetSerDisplayName(CString& strName);
};
