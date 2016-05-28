// TabUserPage.cpp : 实现文件
//

#include "stdafx.h"
#include "LMSServer.h"
#include "TabUserPage.h"
#include "afxdialogex.h"


// CTabUserPage 对话框

IMPLEMENT_DYNAMIC(CTabUserPage, CDialogEx)

CTabUserPage::CTabUserPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTabUserPage::IDD, pParent)
{

}

CTabUserPage::~CTabUserPage()
{
}

void CTabUserPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USERLIST, m_userListCtrl);
}


BEGIN_MESSAGE_MAP(CTabUserPage, CDialogEx)
	ON_WM_SIZE()
//	ON_WM_CREATE()
END_MESSAGE_MAP()


// CTabUserPage 消息处理程序
void CTabUserPage::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	if (m_userListCtrl.m_hWnd != NULL)
		m_userListCtrl.MoveWindow(2, 2, cx - 2, cy - 2);
}

//int CTabUserPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码
//
//
//	return 0;
//}


BOOL CTabUserPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_userListCtrl.init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
