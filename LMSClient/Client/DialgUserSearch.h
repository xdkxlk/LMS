#pragma once
#include "resource.h"
#include "afxwin.h"
#include "Service.h"
#include "UserSearchDigListBoxCtrl.h"

// CDialgUserSearch �Ի���

class CDialgUserSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgUserSearch)

public:
	CDialgUserSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialgUserSearch();

// �Ի�������
	enum { IDD = IDD_DIALOG_USERSEARCH };
private:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_inputEditCtrl;
	CString m_inputEditCtrlVal;
	CUserSearchDigListBoxCtrl m_resListBoxCtrl;

	CUserService m_userService;

	afx_msg void OnBnClickedButtonUsersearchSearch();
};
