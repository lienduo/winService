// ServiceModule.h : ServiceModule DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CServiceModuleApp
// �йش���ʵ�ֵ���Ϣ������� ServiceModule.cpp
//

class CServiceModuleApp : public CWinApp
{
public:
	CServiceModuleApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};