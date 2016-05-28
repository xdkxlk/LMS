// TabUserPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LMSServer.h"
#include "TabUserPage.h"
#include "afxdialogex.h"


// CTabUserPage �Ի���

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


// CTabUserPage ��Ϣ�������
void CTabUserPage::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	if (m_userListCtrl.m_hWnd != NULL)
		m_userListCtrl.MoveWindow(2, 2, cx - 2, cy - 2);
}

//int CTabUserPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  �ڴ������ר�õĴ�������
//
//
//	return 0;
//}


BOOL CTabUserPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_userListCtrl.init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
