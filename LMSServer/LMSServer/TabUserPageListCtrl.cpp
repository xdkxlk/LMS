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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	m_rclickSelectItem = pNMListView->iItem;

	//��ֹ�ڿհ�����������˵�  
	if (GetSelectedCount() <= 0)
	{
		return;
	}

	//�������δ���, ��������Ӧ��ListCtrl  
	CMenu *pPopup;
	pPopup = m_menu.GetSubMenu(0);

	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��  
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, myPoint.x, myPoint.y, this);

	*pResult = 0;
}

void CTabUserPageListCtrl::init()
{
	m_menu.LoadMenu(IDR_MENU_USERLIST);

	LONG lStyle;
	lStyle = GetWindowLong(m_hWnd, GWL_STYLE); //��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_hWnd, GWL_STYLE, lStyle); //����style

	DWORD dwStyle = GetExtendedStyle(); //��ȡ��ǰ��չ��ʽ
	dwStyle |= LVS_EX_FULLROWSELECT; //ѡ��ĳ��ʹ���и�����report���ʱ��
	dwStyle |= LVS_EX_GRIDLINES; //�����ߣ�report���ʱ��
	SetExtendedStyle(dwStyle); //������չ���

	InsertColumn(0, _T("�û���"), LVCFMT_LEFT, 200);
	InsertColumn(1, _T("IP��ַ"), LVCFMT_LEFT, 200);
	InsertColumn(2, _T("�˿�"), LVCFMT_LEFT, 200);
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
//	// TODO:  �ڴ������ר�õĴ�������
//	m_menu.LoadMenu(IDR_MENU_USERLIST);
//
//	return 0;
//}


void CTabUserPageListCtrl::OnIdrUserBrodcast()
{
	// TODO:  �ڴ���������������
	CString msg;
	CDialgBroadcastInput dialg(&msg);
	if (dialg.DoModal() == IDOK)
	{
		m_userController.broadCast(msg);
	}
}


void CTabUserPageListCtrl::OnIdrUserForce()
{
	// TODO:  �ڴ���������������
	if (m_rclickSelectItem >= 0 && m_rclickSelectItem < GetItemCount())
	{
		CString name = GetItemText(m_rclickSelectItem, 0);
		CString tip("ȷ��ǿ�������û���");
		tip += name;
		if (MessageBox(tip.AllocSysString(), _T("����"), MB_OKCANCEL) == IDOK)
		{
			CTCPServer::getInstance()->forceOffLine(name);
		}
	}
}
