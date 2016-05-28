#pragma once
#include "afxcmn.h"
#include "TabUserPage.h"
#include "TabGroupPage.h"

class CCenterTabCtrl : public CTabCtrl
{
public:
	CCenterTabCtrl();
	~CCenterTabCtrl();

	void OnInitial();

	CTabUserPage m_tabUserPage;
	CTabGroupPage m_tabGroupPage;
	void OnTcnSelchangeCentertab(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
};