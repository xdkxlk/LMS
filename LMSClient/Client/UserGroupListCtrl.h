#pragma once
#include "afxcmn.h"
#include "Model.h"

class CUserGroupListCtrl :
	public CListCtrl
{
public:
	CUserGroupListCtrl();
	~CUserGroupListCtrl();

	void init();
	void addGroup(CGroup* g);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);

private:
	CMenu m_menu;
	int m_rclickSelectItem;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnIdrGroupQuit();
protected:
	afx_msg LRESULT OnQuitGroup(WPARAM wParam, LPARAM lParam);
};