#pragma once
#include "afxcmn.h"
#include "Model.h"
#include "Controller.h"
#include <vector>
#include "Controller.h"

using namespace std;

class CTabUserPageListCtrl :	public CListCtrl
{
public:
	CTabUserPageListCtrl();
	~CTabUserPageListCtrl();
	void addUser(SOCKET_INFORMATION* info, const CUser& user);
	void init();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	afx_msg LRESULT OnNewUser(WPARAM wParam, LPARAM lParam);
public:
	afx_msg LRESULT OnUserLeave(WPARAM wParam, LPARAM lParam);
private:
	typedef struct{
		SOCKET_INFORMATION* socketInfo;
		int row;
	}RowData;
	//SOCKET DATA同表项的关联，int 为哪一行
	vector<RowData> m_data;
	CMenu m_menu;
	int m_rclickSelectItem;
	CUserController m_userController;
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnIdrUserBrodcast();
	afx_msg void OnIdrUserForce();
};