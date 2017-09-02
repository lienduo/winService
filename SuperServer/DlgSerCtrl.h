#pragma once
#include "atltypes.h"
#include "afxwin.h"
#include "iButton.h"
#include "SvrCtrl.h"

// CDlgSerCtrl �Ի���

class CDlgSerCtrl : public CDialog
{
	DECLARE_DYNAMIC(CDlgSerCtrl)

public:
	CDlgSerCtrl(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSerCtrl();

// �Ի�������
	enum { IDD = IDD_DLG_SERCTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// �������
	CSvrCtrl m_SvrCtrl;
private:
	// ������Ϣ
	void InsertInfo(CString szInfo);
	// ���ð�ť״̬
	void SetBtStatus(void);
	// ����ComBox
	void LoadComBox(void);
public:
};
