#pragma once
#include "afxwin.h"
#include <map>
#include "iButton.h"
#include "SvrCtrl.h"
#include "SvrLib.h"


// CDlgLocalMonitor 对话框

class CDlgLocalMonitor : public CDialog
{
	DECLARE_DYNAMIC(CDlgLocalMonitor)

public:
	CDlgLocalMonitor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLocalMonitor();

// 对话框数据
	enum { IDD = IDD_DLG_LOCALMONITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
	// 插入信息
	void InsertInfo(CString szInfo);
	// 设置按钮状态
	void SetBtStatus(void);
	// 加载ComBox
	void LoadComBox(void);
private:
	char m_szSysPath[MAX_PATH];
	CView* m_pView;
	CComboBox m_ComSerCtrl;
	CiButton m_StartBt;
	CiButton m_StopBt;
	CiButton m_PauseBt;
	CiButton m_ContinueBt;
	// 服务控制
	CSvrCtrl m_SvrCtrl;
	std::map<CString,CSvrLib*> SerMap;
	std::map<CString,CSvrLib*>::iterator iter;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	// 加入Map
	void AddMap(char* szSection);
	afx_msg void OnCbnSelchangeCobSername();
};
