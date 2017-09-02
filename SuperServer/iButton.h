/**************************说明**************************
1.图标顺序及参考:1)正常,2)进入(图标+浅黄底色),3)按下(图标+深黄底色+虚矩形框),
 4.选中(图标+浅黄底色+虚矩形框),5)失效(灰色图标)
**************************说明**************************/

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
	// 鼠标盘旋在上面
	bool m_bOver;
	// 透明
	bool m_bTrans;
	COLORREF m_TransparentColor,m_BackColor;
	// 工具提示
	CToolTipCtrl m_tooltip;
	// 字体高度
	int m_nTextHeight;
	// 单张图片宽度
	int m_nPicWidth;
	// 图片高度
	int m_nPicHeight;
	// 图片区
	CRect m_PicRect;
	// 文字区
	CRect m_TextRect;
	CDC m_dcTemp;
	CBitmap* m_pOldBitmap;
	// 文字居底显示
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
	// 生成
	virtual BOOL Create(LPCTSTR lpszCaption,CRect rect, CWnd* pParentWnd, UINT nID);
	// 加载图像
	bool LoadBitmaps(int nImage,int nWidth=0);
	// 加载图像
	bool LoadBitmaps(CString szImage,int nWidth=0);
	// 设置工具提示文本
	void SetToolTipText(CString szText);
	// 设置工具提示文本背景前景色
	void SetToolTipColor(COLORREF crText, COLORREF crBkgnd);
	// 设置透明色
	void SetTransColor(COLORREF TransColor,COLORREF BkColor);
	// 按钮尺寸适应图片
	void SizeToContent(void);
	// 设置文字显示方式
	void SetTextShowBottom();
};


