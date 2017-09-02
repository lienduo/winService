#pragma once
#include "atltypes.h"
#include "afxwin.h"
#include "iButton.h"
#include "SvrCtrl.h"

// CDlgSerCtrl 对话框

class CDlgSerCtrl : public CDialog
{
	DECLARE_DYNAMIC(CDlgSerCtrl)

public:
	CDlgSerCtrl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSerCtrl();

// 对话框数据
	enum { IDD = IDD_DLG_SERCTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtSerctrStart();
	afx_msg void OnBnClickedBtSerctrStop();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedBtSerctrPause();
	afx_msg void OnBnClickedBtSerctrContinue();
	afx_msg void OnCbnSelchangeCobSername();
private:
	CView* m_pView;
	CComboBox m_ComSerCtrl;
	CiButton m_StartBt;
	CiButton m_StopBt;
	CiButton m_PauseBt;
	CiButton m_ContinueBt;
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
};
