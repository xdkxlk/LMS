// DialogLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "DialogLogin.h"
#include "afxdialogex.h"
#include "DialgRegist.h"


// CDialogLogin �Ի���

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


// CDialogLogin ��Ϣ�������

void CDialogLogin::OnBnClickedOk()
{
	this->UpdateData();

	if (m_userNameCtrlVal.Trim() == "" || m_passCtrlVal.Trim() == "")
	{
		(*m_isSuccess) = false;
		CDialogEx::OnOK();
		return;
	}

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialgRegist dialg;
	dialg.DoModal();
}
