// DialgBroadcastInput.cpp : 实现文件
//

#include "stdafx.h"
#include "LMSServer.h"
#include "DialgBroadcastInput.h"
#include "afxdialogex.h"


// CDialgBroadcastInput 对话框

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


// CDialgBroadcastInput 消息处理程序


void CDialgBroadcastInput::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	(*m_msg) = m_inputCtrlVal;

	CDialogEx::OnOK();
}
