#pragma once
#include "resource.h"
#include "Service.h"

// CDialgUserAddFriendReply �Ի���

class CDialgUserAddFriendReply : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgUserAddFriendReply)

public:
	CDialgUserAddFriendReply(CString name, CString msg, Json::Value json, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialgUserAddFriendReply();

// �Ի�������
	enum { IDD = IDD_DIALOG_USERADDFRIENDREPLY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_staticTipVal;
	CString m_msgEditCtrlVal;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();

private:
	Json::Value m_json;
	CUserService m_userService;
public:
	CString m_repMsgVal;
};
