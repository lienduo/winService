
// SuperServerDoc.cpp : CSuperServerDoc ���ʵ��
//

#include "stdafx.h"
#include "SuperServer.h"

#include "SuperServerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSuperServerDoc

IMPLEMENT_DYNCREATE(CSuperServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CSuperServerDoc, CDocument)
END_MESSAGE_MAP()


// CSuperServerDoc ����/����

CSuperServerDoc::CSuperServerDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CSuperServerDoc::~CSuperServerDoc()
{
}

BOOL CSuperServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CSuperServerDoc ���л�

void CSuperServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CSuperServerDoc ���

#ifdef _DEBUG
void CSuperServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSuperServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSuperServerDoc ����
