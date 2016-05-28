// TabGroupPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LMSServer.h"
#include "TabGroupPage.h"
#include "afxdialogex.h"
#include "DialgGroupAdd.h"

// CTabGroupPage 对话框

IMPLEMENT_DYNAMIC(CTabGroupPage, CDialogEx)

CTabGroupPage::CTabGroupPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabGroupPage::IDD, pParent)
{

}

CTabGroupPage::~CTabGroupPage()
{
}

void CTabGroupPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_GROUP, m_groupListCtrl);
	DDX_Control(pDX, IDC_BUTTON_GROUP_ADD, m_groupAddBtn);
}


BEGIN_MESSAGE_MAP(CTabGroupPage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GROUP_ADD, &CTabGroupPage::OnBnClickedButtonGroupAdd)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTabGroupPage 消息处理程序


void CTabGroupPage::OnBnClickedButtonGroupAdd()
{
	// TODO:  在此添加控件通知处理程序代码
	CGroup g;
	CDialgGroupAdd m_dialgGroupAdd(&g);
	if (m_dialgGroupAdd.DoModal() == IDOK)
	{
		if (m_groupDAO.insert(g))
		{
			CGroupSum gs;
			gs.m_id = -1;
			gs.m_num = 0;
			gs.m_name = g.m_name;
			m_groupListCtrl.addGroup(gs);
		}
	}
}


BOOL CTabGroupPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_groupListCtrl.init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CTabGroupPage::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	CRect rct;
	GetClientRect(rct);
	if (m_groupListCtrl.GetSafeHwnd())
	{
		CRect temp = rct;
		temp.right -= 30;
		m_groupListCtrl.MoveWindow(temp);
	}
	if (m_groupAddBtn.GetSafeHwnd())
	{
		CRect temp = rct;
		temp.left = (temp.right - 20);
		temp.top = temp.bottom - 20;
		m_groupAddBtn.MoveWindow(temp);
	}
}
