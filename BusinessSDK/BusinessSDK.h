// BusinessSDK.h : BusinessSDK DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// BusinessSDKApp
// �йش���ʵ�ֵ���Ϣ������� BusinessSDK.cpp
//

class BusinessSDKApp : public CWinApp
{
public:
	BusinessSDKApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
