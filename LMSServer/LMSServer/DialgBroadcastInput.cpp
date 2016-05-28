// DialgBroadcastInput.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LMSServer.h"
#include "DialgBroadcastInput.h"
#include "afxdialogex.h"


// CDialgBroadcastInput �Ի���

IMPLEMENT_DYNAMIC(CDialgBroadcastInput, CDialogEx)

CDialgBroadcastInput::CDialgBroadcastInput(CString* msg, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialgBroadcastInput::IDD, pParent)
	, m_inputCtrlVal(_T(""))
{
	m_msg = msg;
}

CDialgBroadcastInput::~CDialgBroadcastInput()
{
}

void CDialgBroadcastInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BROAD_INPUT, m_inputCtrlVal);
}


BEGIN_MESSAGE_MAP(CDialgBroadcastInput, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialgBroadcastInput::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialgBroadcastInput ��Ϣ�������


void CDialgBroadcastInput::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	(*m_msg) = m_inputCtrlVal;

	CDialogEx::OnOK();
}
