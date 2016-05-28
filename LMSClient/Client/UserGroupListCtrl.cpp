#include "stdafx.h"
#include "UserGroupListCtrl.h"
#include "MFCUtil.h"
#include "ConstFile.h"

BEGIN_MESSAGE_MAP(CUserGroupListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CUserGroupListCtrl::OnNMDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CUserGroupListCtrl::OnNMRClick)
	ON_WM_CREATE()
	ON_COMMAND(ID_IDR_GROUP_QUIT, &CUserGroupListCtrl::OnIdrGroupQuit)
	ON_MESSAGE(WM_QUIT_GROUP, &CUserGroupListCtrl::OnQuitGroup)
END_MESSAGE_MAP()

CUserGroupListCtrl::CUserGroupListCtrl()
{
}


CUserGroupListCtrl::~CUserGroupListCtrl()
{
}

void CUserGroupListCtrl::init()
{
	if (CMFCUtil::getActiveDoc() == NULL)
		return;

	DWORD dwStyle = GetExtendedStyle(); //��ȡ��ǰ��չ��ʽ
	dwStyle |= LVS_EX_FULLROWSELECT; //ѡ��ĳ��ʹ���и�����report���ʱ��
	dwStyle |= LVS_EX_GRIDLINES; //�����ߣ�report���ʱ��
	SetExtendedStyle(dwStyle); //������չ���

	CUser* user = &(CMFCUtil::getActiveDoc()->m_user);
	for (int i = 0; i < user->m_groups.size(); i++)
	{
		addGroup(user->m_groups[i]);
	}
}

void CUserGroupListCtrl::addGroup(CGroup* g)
{
	int row = this->InsertItem(this->GetItemCount(), g->m_name);

	this->SetItemData(row, (DWORD_PTR)g);
}

void CUserGroupListCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	int nItem = pNMListView->iItem;
	if (nItem >= 0 && nItem < GetItemCount())//�ж�˫��λ���Ƿ��������ݵ��б�������
	{
		CGroup* g = (CGroup*)GetItemData(nItem);

		::PostMessage(CMFCUtil::getActiveView()->m_hWnd,
			WM_ONE_GROUP_SELECT, (DWORD_PTR)g, NULL);
	}

	*pResult = 0;
}


void CUserGroupListCtrl::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
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


int CUserGroupListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_menu.LoadMenu(IDR_MENU_GROUPLIST_POP);

	return 0;
}


void CUserGroupListCtrl::OnIdrGroupQuit()
{
	// TODO:  �ڴ���������������
	if (m_rclickSelectItem >= 0 && m_rclickSelectItem < GetItemCount())
	{
		CGroup* g = (CGroup*)GetItemData(m_rclickSelectItem);
		CString tip("ȷ���˳�Ⱥ�� ");
		tip += g->m_name;
		int retVal = MessageBox(tip.AllocSysString(), _T("����"), MB_OKCANCEL);
		if (retVal == IDOK)
		{
			::PostMessage(CMFCUtil::getActiveView()->m_hWnd, WM_QUIT_GROUP, (WPARAM)g, NULL);
		}
	}
}


afx_msg LRESULT CUserGroupListCtrl::OnQuitGroup(WPARAM wParam, LPARAM lParam)
{
	CString* groupName = (CString*)wParam;

	int count = GetItemCount();
	for (int i = 0; i < count; i++)
	{
		CString name = GetItemText(i, 0);
		if (name == *groupName)
		{
			DeleteItem(i);
		}
	}

	delete groupName;
	return 0;
}
