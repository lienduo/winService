#pragma once
#include "scrollwnd.h"
#include "iButton.h"

class CConfigBar :
	public CScrollWnd
{
public:
	CConfigBar(void);
	~CConfigBar(void);
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonClick(UINT nID);
private:
	CiButton* m_pSerCfig;
	//CiButton* m_pComCfig;
};
