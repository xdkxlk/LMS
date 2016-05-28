#pragma once
#include "afxwin.h"
#include "Service.h"
#include "GroupSearchListBox.h"
// CDialgGroupSearch �Ի���

class CDialgGroupSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgGroupSearch)

public:
	CDialgGroupSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialgGroupSearch();

	CUserService m_userService;
// �Ի�������
	enum { IDD = IDD_DIALOG_GROUPSEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_inputCtrlVal;
	CGroupSearchListBox m_resultListCtrl;
	afx_msg void OnBnClickedButtonGroupsearchSearch();
};
