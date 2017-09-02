#pragma once
#include "scrollwnd.h"
#include "iButton.h"

class CMonitorBar :
	public CScrollWnd
{
public:
	CMonitorBar(void);
	~CMonitorBar(void);
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonClick(UINT nID);
private:
	CiButton* m_pFastMonintor;
	CiButton* m_pLocalMonitor;
public:
};
