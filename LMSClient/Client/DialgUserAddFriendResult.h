#pragma once
#include "resource.h"

// CDialgUserAddFriendResult �Ի���

class CDialgUserAddFriendResult : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgUserAddFriendResult)

public:
	CDialgUserAddFriendResult(CString tip, CString msg, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialgUserAddFriendResult();

// �Ի�������
	enum { IDD = IDD_DIALOG_USERADDFRIENDREPLY_REMOTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_tipVal;
	CString m_msgEditVal;
};
