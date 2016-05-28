#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "TabGroupListCtrl.h"
#include "DAO.h"
#include "afxwin.h"

// CTabGroupPage �Ի���

class CTabGroupPage : public CDialogEx
{
	DECLARE_DYNAMIC(CTabGroupPage)

public:
	CTabGroupPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabGroupPage();

// �Ի�������
	enum { IDD = IDD_TABGROUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonGroupAdd();
	CTabGroupListCtrl m_groupListCtrl;
	virtual BOOL OnInitDialog();
private:
	CGroupDAO m_groupDAO;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton m_groupAddBtn;
};
