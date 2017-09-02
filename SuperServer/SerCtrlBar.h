#pragma once
#include "scrollwnd.h"
#include "iButton.h"

class CSerCtrlBar :
	public CScrollWnd
{
public:
	CSerCtrlBar(void);
	~CSerCtrlBar(void);
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnButtonClick(UINT nID);
private:
	// 导航按钮
	// 控制服务
	CiButton* m_pCtrlSerBt;
	// 安装卸载服务
	CiButton* m_pInUnstallBt;
};
