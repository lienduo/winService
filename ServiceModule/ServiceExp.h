/************************************************************************
һ������һ������
ͬһ���������ͨ����ͬ����������,������ͬ�ķ���

����ģʽ�����ͷǷ���ģʽ����
************************************************************************/

#pragma once
#ifdef Service_COp_API
#else
#pragma comment(lib,"ServiceModule.lib")
#define Service_COp_API extern "C" _declspec(dllimport)
#endif

typedef int (*BackFun)(void);

// --------------��ʼ��-------------------
// ��������(����ͬ�ķ���),������ʾ����(���ڿ���̨��ʾ),����ʼ���к���,ֹͣ����
Service_COp_API int Ser_Init(char* ServiceName,BackFun SerStart,BackFun SerStop);
// ������ͣ\����(����ģʽ��ѡ����)
Service_COp_API int Ser_SetPauseContinue(BackFun SerPause,BackFun SerContinue);
// --------------��ʼ��-------------------

// ��ʼ����,���ط�0,û�г�ʼ��,���ڷǷ���ģʽ�µ���,true�ڷ���ģʽ�µ��óɹ�
Service_COp_API int Ser_RunService();
// ----------------����ģʽ-----------------------
