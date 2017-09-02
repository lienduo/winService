#pragma once
#include "afxwin.h"
#include <map>
#include "iButton.h"
#include "SvrCtrl.h"
#include "SvrLib.h"


// CDlgLocalMonitor �Ի���

class CDlgLocalMonitor : public CDialog
{
	DECLARE_DYNAMIC(CDlgLocalMonitor)

public:
	CDlgLocalMonitor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLocalMonitor();

// �Ի�������
	enum { IDD = IDD_DLG_LOCALMONITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedBtSerctrStart();
	afx_msg void OnBnClickedBtSerctrStop();
	afx_msg void OnBnClickedBtSerctrPause();
	afx_msg void OnBnClickedBtSerctrContinue();
private:
	static HMODULE GetSelfModuleHandle()
	{
		MEMORY_BASIC_INFORMATION mbi;
		return ((::VirtualQuery(GetSelfModuleHandle,&mbi,sizeof(mbi))!= 0)?(HMODULE) mbi.AllocationBase:NULL);
	} 
	// ������Ϣ
	void InsertInfo(CString szInfo);
	// ���ð�ť״̬
	void SetBtStatus(void);
	// ����ComBox
	void LoadComBox(void);
private:
	char m_szSysPath[MAX_PATH];
	CView* m_pView;
	CComboBox m_ComSerCtrl;
	CiButton m_StartBt;
	CiButton m_StopBt;
	CiButton m_PauseBt;
	CiButton m_ContinueBt;
	// �������
	CSvrCtrl m_SvrCtrl;
	std::map<CString,CSvrLib*> SerMap;
	std::map<CString,CSvrLib*>::iterator iter;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	// ����Map
	void AddMap(char* szSection);
	afx_msg void OnCbnSelchangeCobSername();
};
