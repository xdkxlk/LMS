#pragma once


// CDialgBroadcastInput �Ի���

class CDialgBroadcastInput : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgBroadcastInput)

public:
	CDialgBroadcastInput(CString* msg, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialgBroadcastInput();

// �Ի�������
	enum { IDD = IDD_DIALOG_BROADCAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_inputCtrlVal;
	CString* m_msg;
	afx_msg void OnBnClickedOk();
};
