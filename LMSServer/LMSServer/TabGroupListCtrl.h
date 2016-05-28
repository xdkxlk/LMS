#pragma once
#include "afxcmn.h"
#include "DAO.h"

class CTabGroupListCtrl :
	public CListCtrl
{
public:
	CTabGroupListCtrl();
	~CTabGroupListCtrl();

	void init();
	void addGroup(CGroupSum group);

private:
	CGroupDAO m_groupDAO;
	vector<CGroupSum> m_gList;
public:
	DECLARE_MESSAGE_MAP()
protected:
	afx_msg LRESULT OnUpdatGroupNum(WPARAM wParam, LPARAM lParam);
};