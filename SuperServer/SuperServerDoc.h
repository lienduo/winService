
// SuperServerDoc.h : CSuperServerDoc ��Ľӿ�
//


#pragma once


class CSuperServerDoc : public CDocument
{
protected: // �������л�����
	CSuperServerDoc();
	DECLARE_DYNCREATE(CSuperServerDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CSuperServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


