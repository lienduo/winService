#pragma once


// CDlgTeleMonitor �Ի���

class CDlgTeleMonitor : public CDialog
{
	DECLARE_DYNAMIC(CDlgTeleMonitor)

public:
	CDlgTeleMonitor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTeleMonitor();

// �Ի�������
	enum { IDD = IDD_DLG_TELEMONITOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CBrush   m_brush;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
