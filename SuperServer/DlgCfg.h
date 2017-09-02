#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "iIniOp.h"
#include "iButton.h"


// CDlgCfg 对话框

class CDlgCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgCfg)

public:
	CDlgCfg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCfg();

// 对话框数据
	enum { IDD = IDD_DLG_SERCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtBrown();
	afx_msg void OnBnClickedBtSecadd();
	afx_msg void OnBnClickedBtSecdel();
	afx_msg void OnBnClickedBtKeyadd();
	afx_msg void OnBnClickedBtKeyedit();
	afx_msg void OnBnClickedBtKeydel();
	afx_msg void OnBnClickedBtKeybrown();
	afx_msg void OnTvnSelchangedTreeCfg(NMHDR *pNMHDR, LRESULT *pResult);
private:
	static HMODULE GetSelfModuleHandle()
	{
		MEMORY_BASIC_INFORMATION mbi;
		return ((::VirtualQuery(GetSelfModuleHandle,&mbi,sizeof(mbi))!= 0)?(HMODULE) mbi.AllocationBase:NULL);
	}
	char ToUpper(char ch)
	{
		return ch - 32;
	}


private:
	CBrush   m_brush;
	char m_szSysPath[MAX_PATH];
	CiIniOp m_iniOp;
	CString m_szIniPath;
	CString m_szSection;
	CString m_szKey;
	CString m_szValue;

	CTreeCtrl m_CtrlTree;
	CiButton m_BtIniPath;
	CiButton m_BtSecAdd;
	CiButton m_BtSecDel;
	CiButton m_BtKeyAdd;
	CiButton m_BtKeyEdit;
	CiButton m_BtKeyDel;
	CiButton m_BtKeyBrown;
private:
	// 插入树图
	void InsertTree(void);
	void LayOut(int cx,int cy);
};
