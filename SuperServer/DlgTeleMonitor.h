#pragma once


// CDlgTeleMonitor 对话框

class CDlgTeleMonitor : public CDialog
{
	DECLARE_DYNAMIC(CDlgTeleMonitor)

public:
	CDlgTeleMonitor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTeleMonitor();

// 对话框数据
	enum { IDD = IDD_DLG_TELEMONITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CBrush   m_brush;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
