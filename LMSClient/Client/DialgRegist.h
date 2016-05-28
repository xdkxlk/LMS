#pragma once


// CDialgRegist 对话框

class CDialgRegist : public CDialogEx
{
	DECLARE_DYNAMIC(CDialgRegist)

public:
	CDialgRegist(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialgRegist();

// 对话框数据
	enum { IDD = IDD_DIALOG_REGIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_nameInputVal;
	CString m_passInputVal;
	CString m_passReInputVal;
	afx_msg void OnBnClickedOk();
};
