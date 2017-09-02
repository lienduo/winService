#pragma once
#include "resource.h"
#include "afxwin.h"
#include "iButton.h"

// CDlgMsg 对话框

class CDlgMsg : public CDialog
{
	DECLARE_DYNAMIC(CDlgMsg)

public:
	CDlgMsg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMsg();

// 对话框数据
	enum { IDD = IDD_DLG_MSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
private:
	CiButton m_OKBt;
	CiButton m_CalBt;
public:
	// 消息
	CString m_szMsg;
	// 标题
	CString m_szCaption;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
