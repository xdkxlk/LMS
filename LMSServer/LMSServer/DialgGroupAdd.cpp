// DialgGroupAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "LMSServer.h"
#include "DialgGroupAdd.h"
#include "afxdialogex.h"


// CDialgGroupAdd 对话框

IMPLEMENT_DYNAMIC(CDialgGroupAdd, CDialogEx)

CDialgGroupAdd::CDialgGroupAdd(CGroup* group, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialgGroupAdd::IDD, pParent)
	, m_inputCtrlVal(_T(""))
{
	m_group = group;
}

CDialgGroupAdd::~CDialgGroupAdd()
{
}

void CDialgGroupAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_GRUOPADD_INPUT, m_inputCtrlVal);
}


BEGIN_MESSAGE_MAP(CDialgGroupAdd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialgGroupAdd::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialgGroupAdd 消息处理程序


void CDialgGroupAdd::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	m_group->m_name = m_inputCtrlVal;

	CDialogEx::OnOK();
}
