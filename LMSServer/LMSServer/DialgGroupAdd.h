#pragma once
#include "Model.h"

// CDialgGroupAdd 对话框

class CDialgGroupAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgGroupAdd)

public:
	CDialgGroupAdd(CGroup* group, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialgGroupAdd();

// 对话框数据
	enum { IDD = IDD_DIALOG_GROUPADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CGroup* m_group;
	CString m_inputCtrlVal;
	afx_msg void OnBnClickedOk();
};
