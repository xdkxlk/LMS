#pragma once
#include "resource.h"
#include "Service.h"

// CDialgUserAddFriendReply 对话框

class CDialgUserAddFriendReply : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgUserAddFriendReply)

public:
	CDialgUserAddFriendReply(CString name, CString msg, Json::Value json, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialgUserAddFriendReply();

// 对话框数据
	enum { IDD = IDD_DIALOG_USERADDFRIENDREPLY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
