#include "stdafx.h"
#include "UserFriendListCtrl.h"
#include "MFCUtil.h"
#include "ConstFile.h"

BEGIN_MESSAGE_MAP(CUserFriendListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CUserFriendListCtrl::OnNMDblclk)
	ON_MESSAGE(WM_NEW_FRIEND_ADDED, &CUserFriendListCtrl::OnNewFriendAdded)
	ON_MESSAGE(WM_UPDAT_FRIEND_STATUS, &CUserFriendListCtrl::OnUpdatFriendStatus)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CUserFriendListCtrl::OnNMRClick)
	ON_COMMAND(ID_POP_USERLIST_POPMENU_DELETEUSER, &CUserFriendListCtrl::OnPopUserlistPopmenuDeleteuser)
	ON_WM_CREATE()
	ON_MESSAGE(WM_DEL_FRIEND, &CUserFriendListCtrl::OnDelFriend)
END_MESSAGE_MAP()

CUserFriendListCtrl::CUserFriendListCtrl()
{
}


CUserFriendListCtrl::~CUserFriendListCtrl()
{
}

void CUserFriendListCtrl::init()
{
	if (CMFCUtil::getActiveDoc() == NULL)
		return;

	DWORD dwStyle = GetExtendedStyle(); //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES; //网格线（report风格时）
	SetExtendedStyle(dwStyle); //设置扩展风格

	CUser* user = &(CMFCUtil::getActiveDoc()->m_user);
	for (int i = 0; i < user->m_friends.size(); i++)
	{
		addUser(user->m_friends[i]);
	}
}

void CUserFriendListCtrl::addUser(CFriend* fri)
{
	int row = this->InsertItem(this->GetItemCount(), fri->m_userName);
	if (fri->m_status == 1)
	{
		SetItemText(row, 1, _T("在线"));
	}
	else
	{
		SetItemText(row, 1, _T("离线"));
	}
	if (fri->m_msgNum != 0)
	{
		CString num;
		num.Format(_T("%d"), fri->m_msgNum);
		SetItemText(row, 2, num);
	}

	this->SetItemData(row, (DWORD_PTR)fri);
}


void CUserFriendListCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	int nItem = pNMListView->iItem;
	if (nItem >= 0 && nItem < GetItemCount())//判断双击位置是否在有数据的列表项上面
	{
		CFriend* fri = (CFriend*)GetItemData(nItem);

		fri->m_msgNum = 0;
		SetItemText(nItem, 2, _T(""));

		::PostMessage(CMFCUtil::getActiveView()->m_hWnd,
			WM_ONE_USER_SELECT, (DWORD_PTR)fri, NULL);
	}

	*pResult = 0;
}


afx_msg LRESULT CUserFriendListCtrl::OnNewFriendAdded(WPARAM wParam, LPARAM lParam)
{
	CFriend* fri = (CFriend*)wParam;

	int count = GetItemCount();
	for (int i = 0; i < count; i++)
	{
		CString name = GetItemText(i, 0);
		if (name == fri->m_userName)
			return 0;
	}

	addUser(fri);
	return 0;
}


afx_msg LRESULT CUserFriendListCtrl::OnUpdatFriendStatus(WPARAM wParam, LPARAM lParam)
{
	CFriend* fri = (CFriend*)wParam;

	int count = GetItemCount();
	for (int i = 0; i < count; i++)
	{
		CString name = GetItemText(i, 0);
		if (name == fri->m_userName)
		{
			if (fri->m_status == 1)
			{
				SetItemText(i, 1, _T("在线"));
			}
			else
			{
				SetItemText(i, 1, _T("离线"));
			}
			if (fri->m_msgNum == 0)
				SetItemText(i, 2, _T(""));
			else
			{
				CString num;
				num.Format(_T("%d"), fri->m_msgNum);
				SetItemText(i, 2, num);
			}
			break;
		}
	}
	return 0;
}


void CUserFriendListCtrl::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	m_rclickSelectItem = pNMListView->iItem;

	//防止在空白区点击弹出菜单  
	if (GetSelectedCount() <= 0)
	{
		return;
	}

	//下面的这段代码, 不单单适应于ListCtrl  
	CMenu *pPopup;
	pPopup = m_menu.GetSubMenu(0);

	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //鼠标位置  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);

	*pResult = 0;
}


void CUserFriendListCtrl::OnPopUserlistPopmenuDeleteuser()
{
	// TODO:  在此添加命令处理程序代码
	if (m_rclickSelectItem >= 0 && m_rclickSelectItem < GetItemCount())
	{
		CFriend* fri = (CFriend*)GetItemData(m_rclickSelectItem);
		CString tip("确定删除好友 ");
		tip += fri->m_userName;
		int retVal = MessageBox(tip.AllocSysString(), _T("警告"), MB_OKCANCEL);
		if (retVal == IDOK)
		{
			::PostMessage(CMFCUtil::getActiveView()->m_hWnd, WM_DEL_FRIEND, (WPARAM)fri, NULL);
		}
	}
}


int CUserFriendListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_menu.LoadMenu(IDR_MENU_USERLIST_POPMENU);

	return 0;
}


afx_msg LRESULT CUserFriendListCtrl::OnDelFriend(WPARAM wParam, LPARAM lParam)
{
	CString* friendName = (CString*)wParam;

	int count = GetItemCount();
	for (int i = 0; i < count; i++)
	{
		CString name = GetItemText(i, 0);
		if (name == *friendName)
		{
			DeleteItem(i);
		}
	}

	delete friendName;
	return 0;
}
