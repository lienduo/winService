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
	// 设置滚动条
	void SetScroll(int cx, int cy);
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	COLORREF m_BackColor;	// 背景色
	// 宽度
	int m_cx;
	// 高度
	int m_cy;
	// 调整大小时候有两个线程起作用,用以区分限制,但不是绝对的
	bool m_xFistChange;
	bool m_yFistChange;
public:
	// 生成
	virtual BOOL Create(CWnd* pParentWnd,CRect rect);
	// 设置滚动距离
	void SetScrollWH(int nWith, int nHeight);
};


