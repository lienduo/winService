#include "stdafx.h"
#define Service_COp_API extern "C" _declspec(dllexport)
#include "ServiceExp.h"
#include "SerModule.h"
CSerModule Module;
//��ʼ������
Service_COp_API int Ser_Init(char* ServiceName,BackFun SerStart,BackFun SerStop)
{
	return Module.Init(ServiceName,SerStart,SerStop);
}
// ������ͣ\����
Service_COp_API int Ser_SetPauseContinue(BackFun SerPause,BackFun SerContinue)
{
	return Module.SetPauseContinue(SerPause,SerContinue);
}
// ���з���
Service_COp_API int Ser_RunService()
{
	return Module.RunService();
}