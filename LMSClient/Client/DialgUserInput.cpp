// DialgUserInput.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "DialgUserInput.h"
#include "afxdialogex.h"
#include "ConstFile.h"

// CDialgUserInput 对话框

IMPLEMENT_DYNAMIC(CDialgUserInput, CDialogEx)

CDialgUserInput::CDialgUserInput(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialgUserInput::IDD, pParent)
	, m_editCtrlStr(_T(""))
{

}

CDialgUserInput::~CDialgUserInput()
{
}

void CDialgUserInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DLG_INPUT, m_editCtrl);
	DDX_Control(pDX, IDC_BUTTON_DLG_INPUT_SEND, m_buttonCtrl);
	DDX_Text(pDX, IDC_EDIT_DLG_INPUT, m_editCtrlStr);
}


BEGIN_MESSAGE_MAP(CDialgUserInput, CDialogEx)
	ON_WM_SIZE()
	ON_MESSAGE(WM_ONE_USER_SELECT, &CDialgUserInput::OnOneUserSelect)
	ON_BN_CLICKED(IDC_BUTTON_DLG_INPUT_SEND, &CDialgUserInput::OnBnClickedButtonDlgInputSend)
	ON_MESSAGE(WM_DISABLE_INPUT, &CDialgUserInput::OnDisableInput)
	ON_MESSAGE(WM_ONE_GROUP_SELECT, &CDialgUserInput::OnOneGroupSelect)
END_MESSAGE_MAP()


// CDialgUserInput 消息处理程序

void CDialgUserInput::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	CRect rct;
	GetClientRect(rct);
	if (m_editCtrl.GetSafeHwnd())
	{
		CRect temp = rct;
		temp.right -= 120;
		m_editCtrl.MoveWindow(temp);
	}
	if (m_buttonCtrl.GetSafeHwnd())
	{
		CRect temp = rct;
		temp.left = (temp.right - 100);
		temp.top = temp.bottom - 50;
		m_buttonCtrl.MoveWindow(temp);
	}
}


afx_msg LRESULT CDialgUserInput::OnOneUserSelect(WPARAM wParam, LPARAM lParam)
{
	m_group = NULL;
	m_friend = (CFriend*)wParam;

	m_editCtrl.EnableWindow();
	m_buttonCtrl.EnableWindow();

	return 0;
}


void CDialgUserInput::OnBnClickedButtonDlgInputSend()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	CString retMsg;
	if (m_friend != NULL)
	{
		if (!m_userService.sendMsgToFri(m_friend->m_userName, m_editCtrlStr, &retMsg))
		{
			MessageBox(retMsg.AllocSysString());
		}
	}
	else if (m_group != NULL)
	{
		if (!m_userService.sendMsgToGroup(m_group->m_name , m_editCtrlStr, &retMsg))
		{
			MessageBox(retMsg.AllocSysString());
		}
	}
	m_editCtrlStr = "";
	UpdateData(false);
}

afx_msg LRESULT CDialgUserInput::OnDisableInput(WPARAM wParam, LPARAM lParam)
{
	m_friend = NULL;
	m_group = NULL;

	m_editCtrl.EnableWindow(0);
	m_buttonCtrl.EnableWindow(0);
	return 0;
}


afx_msg LRESULT CDialgUserInput::OnOneGroupSelect(WPARAM wParam, LPARAM lParam)
{
	m_friend = NULL;
	m_group = (CGroup*)wParam;

	m_editCtrl.EnableWindow();
	m_buttonCtrl.EnableWindow();
	return 0;
}
