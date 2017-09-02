#pragma once
#include "afxwin.h"
#include "iButton.h"
#include "SvrCtrl.h"

// CDlgInUn 对话框

class CDlgInUn : public CDialog
{
	DECLARE_DYNAMIC(CDlgInUn)

public:
	CDlgInUn(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInUn();

// 对话框数据
	enum { IDD = IDD_DLG_INUNSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedBtInunInstall();
	afx_msg void OnBnClickedBtInunUnstall();
private:
	CView* m_pView;
	CComboBox m_ComSerCtrl;
	CiButton m_BtInstall;
	CiButton m_BtUnstall;
	// 服务控制
	CSvrCtrl m_SvrCtrl;
private:
	// 插入信息
	void InsertInfo(CString szInfo);
	// 设置按钮状态
	void SetBtStatus(void);
	// 加载ComBox
	void LoadComBox(void);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCobSername();
};
