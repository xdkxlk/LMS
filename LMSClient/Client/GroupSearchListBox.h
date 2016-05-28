#pragma once
#include "afxwin.h"
#include <vector>
#include "Service.h"

using namespace std;

class CGroupSearchListBox :
	public CListBox
{
public:
	CGroupSearchListBox();
	~CGroupSearchListBox();

	void clearListBox();
	void addListBox(const vector<CString>& nameList);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLbnDblclk();

private:
	CUserService m_userService;
};

