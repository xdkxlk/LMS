#pragma once


// CDialgRegist �Ի���

class CDialgRegist : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgRegist)

public:
	CDialgRegist(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialgRegist();

// �Ի�������
	enum { IDD = IDD_DIALOG_REGIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_nameInputVal;
	CString m_passInputVal;
	CString m_passReInputVal;
	afx_msg void OnBnClickedOk();
};
