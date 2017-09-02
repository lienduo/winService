#pragma once


// CScrollWnd

class CScrollWnd : public CWnd
{
	DECLARE_DYNAMIC(CScrollWnd)

public:
	CScrollWnd();
	virtual ~CScrollWnd();

protected:
	DECLARE_MESSAGE_MAP()
private:
	// ���ù�����
	void SetScroll(int cx, int cy);
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	COLORREF m_BackColor;	// ����ɫ
	// ���
	int m_cx;
	// �߶�
	int m_cy;
	// ������Сʱ���������߳�������,������������,�����Ǿ��Ե�
	bool m_xFistChange;
	bool m_yFistChange;
public:
	// ����
	virtual BOOL Create(CWnd* pParentWnd,CRect rect);
	// ���ù�������
	void SetScrollWH(int nWith, int nHeight);
};


