#pragma once
#include "resource.h"
#include "Service.h"
#include "Model.h"
// CDialogLogin 对话框

class CDialogLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLogin)

public:
	CDialogLogin(bool* isSuccess, CUser* pUser, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogLogin();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CUserService m_userService;
public:
	afx_msg void OnBnClickedOk();
	CString m_userNameCtrlVal;
	CString m_passCtrlVal;
	CUser* m_pUser;
	bool* m_isSuccess;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnRegist();
};