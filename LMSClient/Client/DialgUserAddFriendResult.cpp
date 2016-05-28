// DialgUserAddFriendResult.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "DialgUserAddFriendResult.h"
#include "afxdialogex.h"


// CDialgUserAddFriendResult 对话框

IMPLEMENT_DYNAMIC(CDialgUserAddFriendResult, CDialogEx)

CDialgUserAddFriendResult::CDialgUserAddFriendResult(CString tip, CString msg, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialgUserAddFriendResult::IDD, pParent)
	, m_tipVal(tip)
	, m_msgEditVal(msg)
{

}

CDialgUserAddFriendResult::~CDialgUserAddFriendResult()
{
}

void CDialgUserAddFriendResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_DIALOG_USERADDFRIENDREPLY_REMOTE, m_tipVal);
	DDX_Text(pDX, IDC_EDIT_DIALOG_USERADDFRIENDREPLY_MSG, m_msgEditVal);
}


BEGIN_MESSAGE_MAP(CDialgUserAddFriendResult, CDialogEx)
END_MESSAGE_MAP()


// CDialgUserAddFriendResult 消息处理程序
