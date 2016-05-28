#include "stdafx.h"
#include "TabGroupListCtrl.h"
#include "ConstFile.h"
#include "DAO.h"
#include "StringUtil.h"

BEGIN_MESSAGE_MAP(CTabGroupListCtrl, CListCtrl)
	ON_MESSAGE(WM_UPDAT_GROUP_NUM, &CTabGroupListCtrl::OnUpdatGroupNum)
END_MESSAGE_MAP()

CTabGroupListCtrl::CTabGroupListCtrl()
{
}


CTabGroupListCtrl::~CTabGroupListCtrl()
{
}

void CTabGroupListCtrl::init()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_hWnd, GWL_STYLE); //��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_hWnd, GWL_STYLE, lStyle); //����style

	DWORD dwStyle = GetExtendedStyle(); //��ȡ��ǰ��չ��ʽ
	dwStyle |= LVS_EX_FULLROWSELECT; //ѡ��ĳ��ʹ���и�����report���ʱ��
	dwStyle |= LVS_EX_GRIDLINES; //�����ߣ�report���ʱ��
	SetExtendedStyle(dwStyle); //������չ���

	InsertColumn(0, _T("Ⱥ����"), LVCFMT_LEFT, 200);
	InsertColumn(1, _T("Ⱥ��������"), LVCFMT_LEFT, 200);

	vector<CGroupSum> gList;
	m_groupDAO.getAllGroup(gList);
	for (int i = 0; i < gList.size(); i++)
	{
		addGroup(gList[i]);
	}
}

void CTabGroupListCtrl::addGroup(CGroupSum group)
{
	m_gList.push_back(group);
	int row = InsertItem(this->GetItemCount(), group.m_name);

	CString str;
	str.Format(_T("%d"), group.m_num);
	SetItemText(row, 1, str);
	SetItemData(row, (DWORD)(m_gList.size() - 1));
}

afx_msg LRESULT CTabGroupListCtrl::OnUpdatGroupNum(WPARAM wParam, LPARAM lParam)
{
	CString* groupName = (CString*)wParam;
	int type = lParam;

	for (int i = 0; i < GetItemCount(); i++)
	{
		if (GetItemText(i, 0) == *groupName)
		{
			int num = CStringUtil::toInt(CStringUtil::getStdString(GetItemText(i, 1)));
			if (type == 0)
			{
				num++;
			}
			else
			{
				num--;
			}
			CString numStr;
			numStr.Format(_T("%d"), num);
			SetItemText(i, 1, numStr);
			break;
		}
	}

	delete groupName;
	return 0;
}
