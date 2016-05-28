// DialgUserAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "DialgUserAdd.h"
#include "afxdialogex.h"


// CDialgUserAdd 对话框

IMPLEMENT_DYNAMIC(CDialgUserAdd, CDialogEx)

CDialgUserAdd::CDialgUserAdd(const CString& tip, CString* msg, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialgUserAdd::IDD, pParent)
	, m_msgVal(_T(""))
	, m_tipVal(_T(""))
{
	m_tipVal = tip;
	m_pMsg = msg;
}

CDialgUserAdd::~CDialgUserAdd()
{
}

void CDialgUserAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERADD_MSG, m_msgVal);
	DDX_Text(pDX, IDC_STATIC_TIP, m_tipVal);
}


BEGIN_MESSAGE_MAP(CDialgUserAdd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialgUserAdd::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialgUserAdd 消息处理程序


void CDialgUserAdd::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	*m_pMsg = m_msgVal;

	CDialogEx::OnOK();
}
