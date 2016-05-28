#pragma once
#include "resource.h"

// CDialgUserAdd 对话框

class CDialgUserAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgUserAdd)

public:
	CDialgUserAdd(const CString& tip, CString* msg, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialgUserAdd();

// 对话框数据
	enum { IDD = IDD_DIALOG_USERADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_msgVal;
	CString* m_pMsg;
	CString m_tipVal;
	afx_msg void OnBnClickedOk();
};
