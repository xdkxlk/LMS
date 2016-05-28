// DialgEegist.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "DialgRegist.h"
#include "afxdialogex.h"
#include "Service.h"


// CDialgRegist �Ի���

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


// CDialgRegist ��Ϣ�������


void CDialgRegist::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	static CUserService service;

	if (m_nameInputVal.Trim() == "" || m_passInputVal.Trim() == "" || m_passReInputVal.Trim() == "")
	{
		MessageBox(_T("���벻��Ϊ��"), _T("��ʾ"));
		return;
	}
	if (m_passInputVal != m_passReInputVal)
	{
		MessageBox(_T("�������벻ƥ��"), _T("��ʾ"));
		return;
	}
		
	if (!service.regist(m_nameInputVal, m_passInputVal))
	{
		MessageBox(_T("ע��ʧ��"), _T("��ʾ"));
		return;
	}
	MessageBox(_T("ע��ɹ�"), _T("��ʾ"));
	CDialogEx::OnOK();
}