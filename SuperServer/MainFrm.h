
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "Resource.h"
#include "SerCtrlBar.h"
#include "MonitorBar.h"
#include "ConfigBar.h"

class COutlookBar : public CMFCOutlookBar
{
	virtual BOOL AllowShowOnPaneMenu() const { return TRUE; }
	virtual void GetPaneName(CString& strName) const { BOOL bNameValid = strName.LoadString(IDS_OUTLOOKBAR); ASSERT(bNameValid); }
};

class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	//CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	COutlookBar       m_wndNavigationBar;
	// �������
	CSerCtrlBar m_wndSerControl;
	// ״̬���
	CMonitorBar m_wndMonitorBar;
	// ���ù���
	CConfigBar  m_wndConfigBar;
private:
	// ��ǩ����
	BOOL SetActiveTab(CMFCOutlookBar* pbar, CWnd * pwnd);
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg LRESULT OnSetStatusText(WPARAM wParam, LPARAM lParam);
	BOOL CreateOutlookBar(CMFCOutlookBar& bar, UINT uiID, int nInitialWidth);
	afx_msg void OnSerCtrl();
	afx_msg void OnSerShowhide();
	afx_msg void OnSerMonitor();
	afx_msg void OnSerCfig();
};


