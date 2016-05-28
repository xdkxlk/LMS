#pragma once
#include "Model.h"

// CDialgGroupAdd �Ի���

class CDialgGroupAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgGroupAdd)

public:
	CDialgGroupAdd(CGroup* group, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialgGroupAdd();

// �Ի�������
	enum { IDD = IDD_DIALOG_GROUPADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGroup* m_group;
	CString m_inputCtrlVal;
	afx_msg void OnBnClickedOk();
};
