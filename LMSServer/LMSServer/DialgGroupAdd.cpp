// DialgGroupAdd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LMSServer.h"
#include "DialgGroupAdd.h"
#include "afxdialogex.h"


// CDialgGroupAdd �Ի���

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


// CDialgGroupAdd ��Ϣ�������


void CDialgGroupAdd::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	m_group->m_name = m_inputCtrlVal;

	CDialogEx::OnOK();
}
