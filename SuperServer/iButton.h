/**************************˵��**************************
1.ͼ��˳�򼰲ο�:1)����,2)����(ͼ��+ǳ�Ƶ�ɫ),3)����(ͼ��+��Ƶ�ɫ+����ο�),
 4.ѡ��(ͼ��+ǳ�Ƶ�ɫ+����ο�),5)ʧЧ(��ɫͼ��)
**************************˵��**************************/

#pragma once


// CiButton

class CiButton : public CButton
{
	DECLARE_DYNAMIC(CiButton)

public:
	CiButton();
	virtual ~CiButton();

protected:
	DECLARE_MESSAGE_MAP()
private:
	typedef	enum TextType
	{
		Text_NO,
		Text_Bottom_Down,
	};
	//LVBKIMAGE m_bkImage;
	CBitmap m_bitMap;
	// �������������
	bool m_bOver;
	// ͸��
	bool m_bTrans;
	COLORREF m_TransparentColor,m_BackColor;
	// ������ʾ
	CToolTipCtrl m_tooltip;
	// ����߶�
	int m_nTextHeight;
	// ����ͼƬ���
	int m_nPicWidth;
	// ͼƬ�߶�
	int m_nPicHeight;
	// ͼƬ��
	CRect m_PicRect;
	// ������
	CRect m_TextRect;
	CDC m_dcTemp;
	CBitmap* m_pOldBitmap;
	// ���־ӵ���ʾ
	bool m_bTextBottom;
private:
	bool DrawBitmap(CDC* pDC,int nIndex, CRect rect);
	void RelayEvent(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	// ����
	virtual BOOL Create(LPCTSTR lpszCaption,CRect rect, CWnd* pParentWnd, UINT nID);
	// ����ͼ��
	bool LoadBitmaps(int nImage,int nWidth=0);
	// ����ͼ��
	bool LoadBitmaps(CString szImage,int nWidth=0);
	// ���ù�����ʾ�ı�
	void SetToolTipText(CString szText);
	// ���ù�����ʾ�ı�����ǰ��ɫ
	void SetToolTipColor(COLORREF crText, COLORREF crBkgnd);
	// ����͸��ɫ
	void SetTransColor(COLORREF TransColor,COLORREF BkColor);
	// ��ť�ߴ���ӦͼƬ
	void SizeToContent(void);
	// ����������ʾ��ʽ
	void SetTextShowBottom();
};


