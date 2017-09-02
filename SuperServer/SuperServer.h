
// SuperServer.h : SuperServer 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "SvrModule.h"
#include "SvrLib.h"

// CSuperServerApp:
// 有关此类的实现，请参阅 SuperServer.cpp
//

class CSuperServerApp : public CWinAppEx
{
public:
	CSuperServerApp();
	~CSuperServerApp();


// 重写
public:
	virtual BOOL InitInstance();
	// 保存
	/*virtual BOOL LoadWindowPlacement(CRect& rectNormalPosition, int& nFflags, int& nShowCmd)
	{
		return FALSE;
	}
	virtual BOOL StoreWindowPlacement(const CRect& rectNormalPosition, int nFflags, int nShowCmd)
	{
		return FALSE;
	}*/

// 实现
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
