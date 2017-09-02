
// SuperServer.h : SuperServer Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "SvrModule.h"
#include "SvrLib.h"

// CSuperServerApp:
// �йش����ʵ�֣������ SuperServer.cpp
//

class CSuperServerApp : public CWinAppEx
{
public:
	CSuperServerApp();
	~CSuperServerApp();


// ��д
public:
	virtual BOOL InitInstance();
	// ����
	/*virtual BOOL LoadWindowPlacement(CRect& rectNormalPosition, int& nFflags, int& nShowCmd)
	{
		return FALSE;
	}
	virtual BOOL StoreWindowPlacement(const CRect& rectNormalPosition, int nFflags, int nShowCmd)
	{
		return FALSE;
	}*/

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
private:
	typedef int (*BackFun)();
	CSvrModule* m_pModule;
	CSvrLib*    m_pLib;
};

extern CSuperServerApp theApp;
