#pragma once
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "TabUserPageListCtrl.h"

// CTabUserPage �Ի���

class CTabUserPage : public CDialogEx
{
	DECLARE_DYNAMIC(CTabUserPage)

public:
	CTabUserPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabUserPage();

// �Ի�������
	enum { IDD = IDD_TABUSERPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CTabUserPageListCtrl m_userListCtrl;
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
