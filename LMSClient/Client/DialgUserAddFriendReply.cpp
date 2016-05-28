// DialgUserAddFriendReply.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "DialgUserAddFriendReply.h"
#include "afxdialogex.h"
#include "StringUtil.h"

// CDialgUserAddFriendReply 对话框

IMPLEMENT_DYNAMIC(CDialgUserAddFriendReply, CDialogEx)

CDialgUserAddFriendReply::CDialgUserAddFriendReply(CString name, CString msg, Json::Value json, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialgUserAddFriendReply::IDD, pParent)
	, m_staticTipVal(name)
	, m_msgEditCtrlVal(msg)
	, m_repMsgVal(_T(""))
{
	m_staticTipVal += CString(" 请求添加好友，您是否同意");
	m_json = json;
}

CDialgUserAddFriendReply::~CDialgUserAddFriendReply()
{
}

void CDialgUserAddFriendReply::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_DIALOG_USERADDFRIENDREPLY, m_staticTipVal);
	DDX_Text(pDX, IDC_EDIT_DIALOG_USERADDFRIENDREPLY_MSG, m_msgEditCtrlVal);
	DDX_Text(pDX, IDC_EDIT_DIALOG_USERADDFRIENDREPLY_REPLY_MSG, m_repMsgVal);
}


BEGIN_MESSAGE_MAP(CDialgUserAddFriendReply, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CDialgUserAddFriendReply::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CDialgUserAddFriendReply::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialgUserAddFriendReply 消息处理程序


void CDialgUserAddFriendReply::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	m_json["msg"] = Json::Value(CStringUtil::getStdString(m_repMsgVal));

	m_userService.sendDataReplyAddFriend(m_json, false);
	CDialogEx::OnCancel();
}


void CDialgUserAddFriendReply::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();
	m_json["msg"] = Json::Value(CStringUtil::getStdString(m_repMsgVal));

	m_userService.sendDataReplyAddFriend(m_json, true);
	CDialogEx::OnOK();
}