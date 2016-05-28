// DialgUserSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "DialgUserSearch.h"
#include "afxdialogex.h"


// CDialgUserSearch �Ի���

IMPLEMENT_DYNAMIC(CDialgUserSearch, CDialogEx)

CDialgUserSearch::CDialgUserSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialgUserSearch::IDD, pParent)
	, m_inputEditCtrlVal(_T(""))
{

}

CDialgUserSearch::~CDialgUserSearch()
{
}

void CDialgUserSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USERSEARCH_INPUT, m_inputEditCtrl);
	DDX_Text(pDX, IDC_EDIT_USERSEARCH_INPUT, m_inputEditCtrlVal);
	DDX_Control(pDX, IDC_LIST_USERSEARCH_RESULT, m_resListBoxCtrl);
}


BEGIN_MESSAGE_MAP(CDialgUserSearch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_USERSEARCH_SEARCH, &CDialgUserSearch::OnBnClickedButtonUsersearchSearch)
END_MESSAGE_MAP()


// CDialgUserSearch ��Ϣ�������


void CDialgUserSearch::OnBnClickedButtonUsersearchSearch()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	vector<CString> friList;
	CString retMsg;
	if (!m_userService.searchFriend(m_inputEditCtrlVal, friList, retMsg))
	{
		MessageBox(retMsg.AllocSysString());
		m_inputEditCtrlVal = "";
		UpdateData(0);
		return;
	}
	m_resListBoxCtrl.clearListBox();
	m_resListBoxCtrl.addListBox(friList);
}