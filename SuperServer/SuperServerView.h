
// SuperServerView.h : CSuperServerView 类的接口
//


#pragma once
#include "atltypes.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "iButton.h"
#include "dlgserctrl.h"
#include "dlginun.h"
#include "dlglocalmonitor.h"
#include "dlgcfg.h"
#include "DlgTeleMonitor.h"


class CSuperServerView : public CFormView
{
protected: // 仅从序列化创建
	CSuperServerView();
	DECLARE_DYNCREATE(CSuperServerView)

public:
	enum{ IDD = IDD_SUPERSERVER_FORM };

// 属性
public:
	CSuperServerDoc* GetDocument() const;

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用
	// 导航
	afx_msg LRESULT OnClickNavButton(WPARAM wParam, LPARAM lParam);

// 实现
public:
	virtual ~CSuperServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtClearinfo();
private:
	// 设置控件位置
	void SetCtrlPos(int cx=0, int cy=0);
	// 删除当前
	void DelCurDlg();
private:
	// 信息框
	CRect m_RectInfo;
	// Info List
	CListCtrl m_ListCtrl;
	// 清楚信息按钮
	CiButton m_ClearBt;
	// 操作标题
	CString m_szCaption;
	// 当前对话框
	CDialog* m_pCurDlg;
	// 服务控制
	CDlgSerCtrl* m_pDlgSerCtrl;
	// 安装卸载
	CDlgInUn* m_pDlgInUn;
	// 本地监控调试
	CDlgLocalMonitor* m_pDlgLocalMonitor;
	// 配置管理
	CDlgCfg* m_pDlgCfg;
	// 远程监控
	CDlgTeleMonitor* m_pDlgTeleMonitor;
public:
	// 插入信息
	void InserInfo(CString szInfo);
};

#ifndef _DEBUG  // SuperServerView.cpp 中的调试版本
inline CSuperServerDoc* CSuperServerView::GetDocument() const
   { return reinterpret_cast<CSuperServerDoc*>(m_pDocument); }
#endif

