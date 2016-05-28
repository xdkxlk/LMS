#pragma once
#include <vector>
#include "Service.h"

using namespace std;

class CUserSearchDigListBoxCtrl : public CListBox
{
public:
	CUserSearchDigListBoxCtrl();
	~CUserSearchDigListBoxCtrl();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLbnDblclk();

public:
	void clearListBox();
	void addListBox(const vector<CString>& friendNameList);
private:
	CUserService m_userService;
};