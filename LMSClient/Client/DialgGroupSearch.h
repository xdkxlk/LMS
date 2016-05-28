#pragma once
#include "afxwin.h"
#include "Service.h"
#include "GroupSearchListBox.h"
// CDialgGroupSearch 对话框

class CDialgGroupSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgGroupSearch)

public:
	CDialgGroupSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialgGroupSearch();

	CUserService m_userService;
// 对话框数据
	enum { IDD = IDD_DIALOG_GROUPSEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_inputCtrlVal;
	CGroupSearchListBox m_resultListCtrl;
	afx_msg void OnBnClickedButtonGroupsearchSearch();
};
