// DialgGroupSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "DialgGroupSearch.h"
#include "afxdialogex.h"


// CDialgGroupSearch 对话框

IMPLEMENT_DYNAMIC(CDialgGroupSearch, CDialogEx)

CDialgGroupSearch::CDialgGroupSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialgGroupSearch::IDD, pParent)
	, m_inputCtrlVal(_T(""))
{

}

CDialgGroupSearch::~CDialgGroupSearch()
{
}

void CDialgGroupSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GROUPSEARCH_INPUT, m_inputCtrlVal);
	DDX_Control(pDX, IDC_LIST_GROUPSEARCH_RESULT, m_resultListCtrl);
}


BEGIN_MESSAGE_MAP(CDialgGroupSearch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_GROUPSEARCH_SEARCH, &CDialgGroupSearch::OnBnClickedButtonGroupsearchSearch)
END_MESSAGE_MAP()


// CDialgGroupSearch 消息处理程序


void CDialgGroupSearch::OnBnClickedButtonGroupsearchSearch()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	vector<CString> gList;
	CString retMsg;
	if (!m_userService.searchGroup(m_inputCtrlVal, gList, retMsg))
	{
		MessageBox(retMsg.AllocSysString());
		m_inputCtrlVal = "";
		UpdateData(0);
		return;
	}
	m_resultListCtrl.clearListBox();
	m_resultListCtrl.addListBox(gList);
}
