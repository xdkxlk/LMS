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
	lStyle = GetWindowLong(m_hWnd, GWL_STYLE); //获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_hWnd, GWL_STYLE, lStyle); //设置style

	DWORD dwStyle = GetExtendedStyle(); //获取当前扩展样式
	dwStyle |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle |= LVS_EX_GRIDLINES; //网格线（report风格时）
	SetExtendedStyle(dwStyle); //设置扩展风格

	InsertColumn(0, _T("群组名"), LVCFMT_LEFT, 200);
	InsertColumn(1, _T("群组总人数"), LVCFMT_LEFT, 200);

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
