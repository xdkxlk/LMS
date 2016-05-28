// DialgUserAddFriendReply.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Client.h"
#include "DialgUserAddFriendReply.h"
#include "afxdialogex.h"
#include "StringUtil.h"

// CDialgUserAddFriendReply �Ի���

IMPLEMENT_DYNAMIC(CDialgUserAddFriendReply, CDialogEx)

CDialgUserAddFriendReply::CDialgUserAddFriendReply(CString name, CString msg, Json::Value json, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialgUserAddFriendReply::IDD, pParent)
	, m_staticTipVal(name)
	, m_msgEditCtrlVal(msg)
	, m_repMsgVal(_T(""))
{
	m_staticTipVal += CString(" ������Ӻ��ѣ����Ƿ�ͬ��");
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


// CDialgUserAddFriendReply ��Ϣ�������


void CDialgUserAddFriendReply::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	m_json["msg"] = Json::Value(CStringUtil::getStdString(m_repMsgVal));

	m_userService.sendDataReplyAddFriend(m_json, false);
	CDialogEx::OnCancel();
}


void CDialgUserAddFriendReply::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	m_json["msg"] = Json::Value(CStringUtil::getStdString(m_repMsgVal));

	m_userService.sendDataReplyAddFriend(m_json, true);
	CDialogEx::OnOK();
}