#pragma once
#include "resource.h"
#include "afxwin.h"
#include "Service.h"

// CDialgUserInput �Ի���

class CDialgUserInput : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgUserInput)

public:
	CDialgUserInput(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialgUserInput();

// �Ի�������
	enum { IDD = IDD_DIALOG_USERINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CEdit m_editCtrl;
	CButton m_buttonCtrl;
protected:
	afx_msg LRESULT OnOneUserSelect(WPARAM wParam, LPARAM lParam);
public:
	CUserService m_userService;
	CString m_editCtrlStr;
	CFriend* m_friend;
	CGroup* m_group;

	afx_msg void OnBnClickedButtonDlgInputSend();
protected:
	afx_msg LRESULT OnDisableInput(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnOneGroupSelect(WPARAM wParam, LPARAM lParam);
};
