
// SuperServerDoc.cpp : CSuperServerDoc 类的实现
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


// CSuperServerDoc 构造/析构

CSuperServerDoc::CSuperServerDoc()
{
	// TODO: 在此添加一次性构造代码

}

CSuperServerDoc::~CSuperServerDoc()
{
}

BOOL CSuperServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CSuperServerDoc 序列化

void CSuperServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CSuperServerDoc 诊断

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


// CSuperServerDoc 命令
