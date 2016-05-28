#pragma once
#include "afxcmn.h"
#include "Model.h"
#include "Service.h"

class CUserFriendListCtrl :
	public CListCtrl
{
public:
	CUserFriendListCtrl();
	~CUserFriendListCtrl();

	void init();
	void addUser(CFriend* fri);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	CMenu m_menu;
	int m_rclickSelectItem;
	CUserService m_userService;

	afx_msg LRESULT OnNewFriendAdded(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUpdatFriendStatus(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPopUserlistPopmenuDeleteuser();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
	afx_msg LRESULT OnDelFriend(WPARAM wParam, LPARAM lParam);
};