
// SuperServerView.h : CSuperServerView ��Ľӿ�
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
protected: // �������л�����
	CSuperServerView();
	DECLARE_DYNCREATE(CSuperServerView)

public:
	enum{ IDD = IDD_SUPERSERVER_FORM };

// ����
public:
	CSuperServerDoc* GetDocument() const;

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���
	// ����
	afx_msg LRESULT OnClickNavButton(WPARAM wParam, LPARAM lParam);

// ʵ��
public:
	virtual ~CSuperServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtClearinfo();
private:
	// ���ÿؼ�λ��
	void SetCtrlPos(int cx=0, int cy=0);
	// ɾ����ǰ
	void DelCurDlg();
private:
	// ��Ϣ��
	CRect m_RectInfo;
	// Info List
	CListCtrl m_ListCtrl;
	// �����Ϣ��ť
	CiButton m_ClearBt;
	// ��������
	CString m_szCaption;
	// ��ǰ�Ի���
	CDialog* m_pCurDlg;
	// �������
	CDlgSerCtrl* m_pDlgSerCtrl;
	// ��װж��
	CDlgInUn* m_pDlgInUn;
	// ���ؼ�ص���
	CDlgLocalMonitor* m_pDlgLocalMonitor;
	// ���ù���
	CDlgCfg* m_pDlgCfg;
	// Զ�̼��
	CDlgTeleMonitor* m_pDlgTeleMonitor;
public:
	// ������Ϣ
	void InserInfo(CString szInfo);
};

#ifndef _DEBUG  // SuperServerView.cpp �еĵ��԰汾
inline CSuperServerDoc* CSuperServerView::GetDocument() const
   { return reinterpret_cast<CSuperServerDoc*>(m_pDocument); }
#endif

