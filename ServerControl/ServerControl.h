// ServerControl.h : ServerControl DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CServerControlApp
// �йش���ʵ�ֵ���Ϣ������� ServerControl.cpp
//

class CServerControlApp : public CWinApp
{
public:
	CServerControlApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
