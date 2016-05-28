#include "stdafx.h"
#include "TabUserPageListCtrl.h"
#include "ConstFile.h"
#include "MFCUtil.h"
#include "StringUtil.h"
#include <WinSock2.h>
#include "DialgBroadcastInput.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(CTabUserPageListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CTabUserPageListCtrl::OnNMRClick)
	ON_MESSAGE(WM_NEW_USER, &CTabUserPageListCtrl::OnNewUser)
	ON_MESSAGE(WM_USER_LEAVE, &CTabUserPageListCtrl::OnUserLeave)
//	ON_WM_CREATE()
ON_COMMAND(ID_IDR_USER_BRODCAST, &CTabUserPageListCtrl::OnIdrUserBrodcast)
ON_COMMAND(ID_IDR_USER_FORCE, &CTabUserPageListCtrl::OnIdrUserForce)
END_MESSAGE_MAP()

CTabUserPageListCtrl::CTabUserPageListCtrl()
{
}

CTabUserPageListCtrl::~CTabUserPageListCtrl()
{
}

void CTabUserPageListCtrl::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
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

void CTabUserPageListCtrl::init()
{
	m_menu.LoadMenu(IDR_MENU_USERLIST);

	LONG lStyle;
	lStyle = GetWindowLong(m_hWnd, GWL_STYLE); //获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_hWnd, GWL_STYLE, lStyle); //设置style

	DWORD dwStyle = GetExtendedStyle(); //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES; //网格线（report风格时）
	SetExtendedStyle(dwStyle); //设置扩展风格

	InsertColumn(0, _T("用户名"), LVCFMT_LEFT, 200);
	InsertColumn(1, _T("IP地址"), LVCFMT_LEFT, 200);
	InsertColumn(2, _T("端口"), LVCFMT_LEFT, 200);
}

afx_msg LRESULT CTabUserPageListCtrl::OnNewUser(WPARAM wParam, LPARAM lParam)
{
	SOCKET_INFORMATION* info = (SOCKET_INFORMATION*)wParam;
	CUser user;

	if (CMFCUtil::getActiveDoc()->m_userSession.getUser(info, user))
	{
		addUser(info, user);
	}
	return 0;
}

afx_msg LRESULT CTabUserPageListCtrl::OnUserLeave(WPARAM wParam, LPARAM lParam)
{
	SOCKET_INFORMATION* info = (SOCKET_INFORMATION*)wParam;

	auto index = m_data.begin();
	for (; index != m_data.end(); index++)
	{
		if ((*index).socketInfo == info)
			break;
	}
	if (index != m_data.end())
	{
		DeleteItem(index->row);
		index = m_data.erase(index);
		for (; index != m_data.end(); index++)
		{
			(*index).row--;
		}
	}
	return 0;
}


void CTabUserPageListCtrl::addUser(SOCKET_INFORMATION* info, const CUser& user)
{
	int row = InsertItem(this->GetItemCount(), user.m_userName);

	SetItemText(row, 1, CStringUtil::getLPSTR(inet_ntoa(info->Addr.sin_addr)));
	SetItemText(row, 2, CStringUtil::getLPSTR(CStringUtil::fromNum(ntohs(info->Addr.sin_port)).c_str()));
	SetItemData(row, (DWORD_PTR)info);

	RowData data;
	data.socketInfo = info;
	data.row = row;
	m_data.push_back(data);
}

//int CTabUserPageListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码
//	m_menu.LoadMenu(IDR_MENU_USERLIST);
//
//	return 0;
//}


void CTabUserPageListCtrl::OnIdrUserBrodcast()
{
	// TODO:  在此添加命令处理程序代码
	CString msg;
	CDialgBroadcastInput dialg(&msg);
	if (dialg.DoModal() == IDOK)
	{
		m_userController.broadCast(msg);
	}
}


void CTabUserPageListCtrl::OnIdrUserForce()
{
	// TODO:  在此添加命令处理程序代码
	if (m_rclickSelectItem >= 0 && m_rclickSelectItem < GetItemCount())
	{
		CString name = GetItemText(m_rclickSelectItem, 0);
		CString tip("确认强制下线用户：");
		tip += name;
		if (MessageBox(tip.AllocSysString(), _T("警告"), MB_OKCANCEL) == IDOK)
		{
			CTCPServer::getInstance()->forceOffLine(name);
		}
	}
}
