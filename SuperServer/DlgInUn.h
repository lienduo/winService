#pragma once
#include "afxwin.h"
#include "iButton.h"
#include "SvrCtrl.h"

// CDlgInUn �Ի���

class CDlgInUn : public CDialog
{
	DECLARE_DYNAMIC(CDlgInUn)

public:
	CDlgInUn(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInUn();

// �Ի�������
	enum { IDD = IDD_DLG_INUNSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCobSername();
};
