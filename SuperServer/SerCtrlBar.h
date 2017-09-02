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
	// ������ť
	// ���Ʒ���
	CiButton* m_pCtrlSerBt;
	// ��װж�ط���
	CiButton* m_pInUnstallBt;
};
