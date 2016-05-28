#pragma once


// CDialgBroadcastInput 对话框

class CDialgBroadcastInput : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgBroadcastInput)

public:
	CDialgBroadcastInput(CString* msg, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialgBroadcastInput();

// 对话框数据
	enum { IDD = IDD_DIALOG_BROADCAST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_inputCtrlVal;
	CString* m_msg;
	afx_msg void OnBnClickedOk();
};
