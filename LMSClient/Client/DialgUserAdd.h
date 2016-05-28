#pragma once
#include "resource.h"

// CDialgUserAdd �Ի���

class CDialgUserAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgUserAdd)

public:
	CDialgUserAdd(const CString& tip, CString* msg, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialgUserAdd();

// �Ի�������
	enum { IDD = IDD_DIALOG_USERADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_msgVal;
	CString* m_pMsg;
	CString m_tipVal;
	afx_msg void OnBnClickedOk();
};
