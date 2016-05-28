// TabGroupPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LMSServer.h"
#include "TabGroupPage.h"
#include "afxdialogex.h"
#include "DialgGroupAdd.h"

// CTabGroupPage �Ի���

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


// CTabGroupPage ��Ϣ�������


void CTabGroupPage::OnBnClickedButtonGroupAdd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_groupListCtrl.init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CTabGroupPage::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
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
