// DlgCfg.cpp : 实现文件
//

#include "stdafx.h"
#include "SuperServer.h"
#include "DlgCfg.h"
#include "DlgMsg.h"

// CDlgCfg 对话框

IMPLEMENT_DYNAMIC(CDlgCfg, CDialog)

CDlgCfg::CDlgCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfg::IDD, pParent)
	, m_szIniPath(_T(""))
	, m_szKey(_T(""))
	, m_szValue(_T(""))
	, m_szSection(_T(""))
{

}

CDlgCfg::~CDlgCfg()
{
}

void CDlgCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_CFG, m_CtrlTree);
	DDX_Text(pDX, IDC_ET_INIPATH, m_szIniPath);
	DDX_Control(pDX, IDC_BT_BROWN, m_BtIniPath);
	DDX_Control(pDX, IDC_BT_SECADD, m_BtSecAdd);
	DDX_Control(pDX, IDC_BT_SECDEL, m_BtSecDel);
	DDX_Text(pDX, IDC_ET_KEYNA, m_szKey);
	DDX_Text(pDX, IDC_ET_VAL, m_szValue);
	DDX_Control(pDX, IDC_BT_KEYADD, m_BtKeyAdd);
	DDX_Control(pDX, IDC_BT_KEYEDIT, m_BtKeyEdit);
	DDX_Control(pDX, IDC_BT_KEYDEL, m_BtKeyDel);
	DDX_Control(pDX, IDC_BT_KEYBROWN, m_BtKeyBrown);
	DDX_Text(pDX, IDC_ET_SECTIONNA, m_szSection);
}


BEGIN_MESSAGE_MAP(CDlgCfg, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BT_BROWN, &CDlgCfg::OnBnClickedBtBrown)
	ON_BN_CLICKED(IDC_BT_SECADD, &CDlgCfg::OnBnClickedBtSecadd)
	ON_BN_CLICKED(IDC_BT_SECDEL, &CDlgCfg::OnBnClickedBtSecdel)
	ON_BN_CLICKED(IDC_BT_KEYADD, &CDlgCfg::OnBnClickedBtKeyadd)
	ON_BN_CLICKED(IDC_BT_KEYEDIT, &CDlgCfg::OnBnClickedBtKeyedit)
	ON_BN_CLICKED(IDC_BT_KEYDEL, &CDlgCfg::OnBnClickedBtKeydel)
	ON_BN_CLICKED(IDC_BT_KEYBROWN, &CDlgCfg::OnBnClickedBtKeybrown)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CFG, &CDlgCfg::OnTvnSelchangedTreeCfg)
END_MESSAGE_MAP()


// CDlgCfg 消息处理程序

BOOL CDlgCfg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,RGB(213,228,242));
	return TRUE;
}

HBRUSH CDlgCfg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC )  //静态文本颜色，并且指定控件ID号
	{
		pDC->SetTextColor(RGB(0,0,0));
		//pDC->SetBkColor(RGB(191,219,255));
		pDC->SetBkMode(TRANSPARENT);
		hbr=(HBRUSH)m_brush;
	}
	return hbr;
}

void CDlgCfg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	LayOut(cx,cy);
}

void CDlgCfg::LayOut(int cx,int cy)
{
	if (m_CtrlTree.GetSafeHwnd()==NULL)
	{
		return;
	}
	m_CtrlTree.SetWindowPos(NULL,1,1,cx/2-2,cy-2,SWP_NOACTIVATE);
	GetDlgItem(IDC_ST_INIPATH)->SetWindowPos(NULL,cx/2+4,30,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	GetDlgItem(IDC_ET_INIPATH)->SetWindowPos(NULL,cx/2+37,27,cx/2-38,24,SWP_NOACTIVATE);
	m_BtIniPath.SetWindowPos(NULL,cx-80,54,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	GetDlgItem(IDC_ST_SECTION)->SetWindowPos(NULL,cx/2+2,100,cx/2-4,120,SWP_NOACTIVATE);
	GetDlgItem(IDC_ST_SECNA)->SetWindowPos(NULL,cx/2+4,150,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	GetDlgItem(IDC_ET_SECTIONNA)->SetWindowPos(NULL,cx/2+37,148,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	m_BtSecAdd.SetWindowPos(NULL,cx/2+200,132,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	m_BtSecDel.SetWindowPos(NULL,cx/2+200,162,0,0,SWP_NOACTIVATE|SWP_NOSIZE);

	GetDlgItem(IDC_ST_KEYVAL)->SetWindowPos(NULL,cx/2+2,232,cx/2-4,168,SWP_NOACTIVATE);
	GetDlgItem(IDC_ST_KEY)->SetWindowPos(NULL,cx/2+4,260,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	GetDlgItem(IDC_ST_VAL)->SetWindowPos(NULL,cx/2+4,300,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	GetDlgItem(IDC_ET_KEYNA)->SetWindowPos(NULL,cx/2+37,258,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	GetDlgItem(IDC_ET_VAL)->SetWindowPos(NULL,cx/2+37,298,cx/2-38,24,SWP_NOACTIVATE);
	m_BtKeyBrown.SetWindowPos(NULL,cx-80,325,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	m_BtKeyAdd.SetWindowPos(NULL,cx/2+60,335,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	m_BtKeyEdit.SetWindowPos(NULL,cx/2+60,365,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
	m_BtKeyDel.SetWindowPos(NULL,cx/2+140,348,0,0,SWP_NOACTIVATE|SWP_NOSIZE);
}
// 插入树图
void CDlgCfg::InsertTree(void)
{
	m_CtrlTree.DeleteAllItems();
	CString szSection,szKeyValue;
	char** pRes=NULL;
	int nSize=0;
	m_iniOp.ReadSection(&pRes,&nSize);
	for (int i=0;i<nSize;i++)
	{
		char** pKey=NULL;
		int nLen=0;
		HTREEITEM hCurrent=m_CtrlTree.InsertItem(pRes[i],0,0,0);
		m_iniOp.ReadKeyValue(&pKey,&nLen,pRes[i]);
		for (int n=0;n<nLen;n++)
		{
			m_CtrlTree.InsertItem(pKey[n],0,0,hCurrent);
		}
		m_iniOp.EndReadKeyValue(pKey);
	}
	m_iniOp.EndReadSection(pRes);
}
BOOL CDlgCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 初始化
	m_brush.CreateSolidBrush(RGB(213,228,242));
	GetModuleFileName(GetSelfModuleHandle(), m_szSysPath,MAX_PATH);
	int nLen=strlen(m_szSysPath);
	for (int i=nLen;i>0;i--)
	{
		if (m_szSysPath[i]=='\\')
		{
			m_szSysPath[i+1]='\0';
			break;
		}
	}
	m_szIniPath=m_szSysPath;
	m_szIniPath+=_T("Config.ini");
	UpdateData(FALSE);
	m_iniOp.Load(m_szIniPath.GetBuffer());
	InsertTree();
	// 按钮加载
	m_BtIniPath.LoadBitmaps(IDB_DEFBUTTON,88);
	m_BtSecAdd.LoadBitmaps(IDB_DEFBUTTON,88);;
	m_BtSecDel.LoadBitmaps(IDB_DEFBUTTON,88);;
	m_BtKeyAdd.LoadBitmaps(IDB_DEFBUTTON,88);;
	m_BtKeyEdit.LoadBitmaps(IDB_DEFBUTTON,88);;
	m_BtKeyDel.LoadBitmaps(IDB_DEFBUTTON,88);;
	m_BtKeyBrown.LoadBitmaps(IDB_DEFBUTTON,88);;
	return TRUE;
}

// 浏览Ini文件
void CDlgCfg::OnBnClickedBtBrown()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR
		,_T("INI文件 (*.INI)|*.INI||"), this);
	if(IDOK==dlg.DoModal())
	{

		m_szIniPath=dlg.GetPathName();
		UpdateData(FALSE);
		m_iniOp.Load(m_szIniPath.GetBuffer());
		InsertTree();
	}
}
// KeyValue浏览
void CDlgCfg::OnBnClickedBtKeybrown()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR
		,_T("所有文件 (*.*)|*.*||"), this);
	if(IDOK==dlg.DoModal())
	{

		m_szValue=dlg.GetPathName();
		m_szValue.Replace(m_szSysPath,_T(""));
		UpdateData(FALSE);
	}
}
void CDlgCfg::OnTvnSelchangedTreeCfg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	HTREEITEM hItem=pNMTreeView->itemNew.hItem;
	if (hItem!=NULL)
	{
		HTREEITEM hParItem=m_CtrlTree.GetParentItem(hItem);
		if (hParItem==NULL)
		{
			m_szSection=m_CtrlTree.GetItemText(hItem);
		}
		else
		{
			CString szTmp=m_CtrlTree.GetItemText(hItem);
			m_szKey=szTmp.Left(szTmp.Find('='));
			m_szValue = szTmp.Mid(szTmp.Find('=') + 1);
		}
		UpdateData(FALSE);
	}
	*pResult = 0;
}
// 添加Section
void CDlgCfg::OnBnClickedBtSecadd()
{
	UpdateData();
	if (m_szSection==_T(""))
	{
		return;
	}
	if(m_iniOp.AddSection(m_szSection))
	{
		m_CtrlTree.InsertItem(m_szSection,0,0,0);
	}
}
// 删除Section
void CDlgCfg::OnBnClickedBtSecdel()
{
	HTREEITEM hItem=m_CtrlTree.GetSelectedItem();
	if (hItem==NULL)
	{
		return;
	}
	if (m_CtrlTree.GetParentItem(hItem)!=NULL)
	{
		return;
	}
	CDlgMsg dlg;
	dlg.m_szMsg=_T("您确定删除:")+m_szSection+_T(" ?");
	if (IDOK!=dlg.DoModal())
	{
		return;
	}
	if (m_iniOp.DelSection(m_CtrlTree.GetItemText(hItem)))
	{
		m_szSection=_T("");
		UpdateData();
		m_CtrlTree.DeleteItem(hItem);
	}
}
// 添加KeyValue
void CDlgCfg::OnBnClickedBtKeyadd()
{
	HTREEITEM hItem=m_CtrlTree.GetSelectedItem();
	if (hItem==NULL)
	{
		return;
	}
	HTREEITEM hParItem=m_CtrlTree.GetParentItem(hItem);
	if (hParItem!=NULL)
	{
		hItem=hParItem;
	}
	UpdateData();
	if(m_iniOp.AddKeyValue(m_szKey,m_szValue,m_CtrlTree.GetItemText(hItem)))
	{
		m_CtrlTree.InsertItem(m_szKey+_T("=")+m_szValue,0,0,hItem);
		m_CtrlTree.Expand(hItem,TVE_EXPAND);
	}
}
// 修改KeyValue
void CDlgCfg::OnBnClickedBtKeyedit()
{
	HTREEITEM hItem=m_CtrlTree.GetSelectedItem();
	if (hItem==NULL)
	{
		return;
	}
	HTREEITEM hParItem=m_CtrlTree.GetParentItem(hItem);
	if (hParItem==NULL)
	{
		return;
	}
	UpdateData();
	if (m_iniOp.EditValue(m_szKey,m_szValue,m_CtrlTree.GetItemText(hParItem)))
	{
		m_CtrlTree.SetItemText(hItem,m_szKey+_T("=")+m_szValue);
	}
}
// 删除KeyValue
void CDlgCfg::OnBnClickedBtKeydel()
{
	HTREEITEM hItem=m_CtrlTree.GetSelectedItem();
	if (hItem==NULL)
	{
		return;
	}
	HTREEITEM hParItem=m_CtrlTree.GetParentItem(hItem);
	if (hParItem==NULL)
	{
		return;
	}
	CDlgMsg dlg;
	dlg.m_szMsg=_T("您确定删除:")+m_szKey+_T(" ?");
	if (IDOK!=dlg.DoModal())
	{
		return;
	}
	if (m_iniOp.DelKey(m_szKey,m_CtrlTree.GetItemText(hParItem)))
	{
		m_szKey=_T("");
		m_szValue=_T("");
		UpdateData(FALSE);
		m_CtrlTree.DeleteItem(hItem);
	}
}


