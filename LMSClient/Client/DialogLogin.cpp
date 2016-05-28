// DialogLogin.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "DialogLogin.h"
#include "afxdialogex.h"
#include "DialgRegist.h"


// CDialogLogin 对话框

IMPLEMENT_DYNAMIC(CDialogLogin, CDialogEx)

CDialogLogin::CDialogLogin(bool* isSuccess, CUser* pUser, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogLogin::IDD, pParent)
	, m_userNameCtrlVal(_T(""))
	, m_passCtrlVal(_T(""))
{
	m_isSuccess = isSuccess;
	m_pUser = pUser;
}

CDialogLogin::~CDialogLogin()
{
}

void CDialogLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_userNameCtrlVal);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_passCtrlVal);
}


BEGIN_MESSAGE_MAP(CDialogLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogLogin::OnBnClickedOk)
	ON_BN_CLICKED(ID_BTN_REGIST, &CDialogLogin::OnBnClickedBtnRegist)
END_MESSAGE_MAP()


// CDialogLogin 消息处理程序

void CDialogLogin::OnBnClickedOk()
{
	this->UpdateData();

	if (m_userNameCtrlVal.Trim() == "" || m_passCtrlVal.Trim() == "")
	{
		(*m_isSuccess) = false;
		CDialogEx::OnOK();
		return;
	}

	// TODO:  在此添加控件通知处理程序代码
	if (m_userService.login(m_userNameCtrlVal, m_passCtrlVal, *m_pUser))
	{
		(*m_isSuccess) = true;
	}
	else
	{
		(*m_isSuccess) = false;
	}
	CDialogEx::OnOK();
}

void CDialogLogin::OnBnClickedBtnRegist()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialgRegist dialg;
	dialg.DoModal();
}
