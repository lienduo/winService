#pragma once
#include "resource.h"
#include "afxwin.h"
#include "iButton.h"

// CDlgMsg �Ի���

class CDlgMsg : public CDialog
{
	DECLARE_DYNAMIC(CDlgMsg)

public:
	CDlgMsg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMsg();

// �Ի�������
	enum { IDD = IDD_DLG_MSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
protected:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
private:
	CiButton m_OKBt;
	CiButton m_CalBt;
public:
	// ��Ϣ
	CString m_szMsg;
	// ����
	CString m_szCaption;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
