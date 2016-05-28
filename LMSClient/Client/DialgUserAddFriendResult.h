#pragma once
#include "resource.h"

// CDialgUserAddFriendResult 对话框

class CDialgUserAddFriendResult : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgUserAddFriendResult)

public:
	CDialgUserAddFriendResult(CString tip, CString msg, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialgUserAddFriendResult();

// 对话框数据
	enum { IDD = IDD_DIALOG_USERADDFRIENDREPLY_REMOTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_tipVal;
	CString m_msgEditVal;
};
