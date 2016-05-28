// DialgEegist.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "DialgRegist.h"
#include "afxdialogex.h"
#include "Service.h"


// CDialgRegist 对话框

IMPLEMENT_DYNAMIC(CDialgRegist, CDialogEx)

CDialgRegist::CDialgRegist(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialgRegist::IDD, pParent)
	, m_nameInputVal(_T(""))
	, m_passInputVal(_T(""))
	, m_passReInputVal(_T(""))
{

}

CDialgRegist::~CDialgRegist()
{
}

void CDialgRegist::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_REGIST_NAME, m_nameInputVal);
	DDX_Text(pDX, IDC_EDIT_REGIST_PASSWORD, m_passInputVal);
	DDX_Text(pDX, IDC_EDIT_REGIST_PASS_RE, m_passReInputVal);
}


BEGIN_MESSAGE_MAP(CDialgRegist, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialgRegist::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialgRegist 消息处理程序


void CDialgRegist::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	static CUserService service;

	if (m_nameInputVal.Trim() == "" || m_passInputVal.Trim() == "" || m_passReInputVal.Trim() == "")
	{
		MessageBox(_T("输入不可为空"), _T("提示"));
		return;
	}
	if (m_passInputVal != m_passReInputVal)
	{
		MessageBox(_T("密码输入不匹配"), _T("提示"));
		return;
	}
		
	if (!service.regist(m_nameInputVal, m_passInputVal))
	{
		MessageBox(_T("注册失败"), _T("提示"));
		return;
	}
	MessageBox(_T("注册成功"), _T("提示"));
	CDialogEx::OnOK();
}