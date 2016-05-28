#include "stdafx.h"
#include "UserSearchDigListBoxCtrl.h"
#include "DialgUserAdd.h"

CUserSearchDigListBoxCtrl::CUserSearchDigListBoxCtrl()
{
}


CUserSearchDigListBoxCtrl::~CUserSearchDigListBoxCtrl()
{
}
BEGIN_MESSAGE_MAP(CUserSearchDigListBoxCtrl, CListBox)
	ON_CONTROL_REFLECT(LBN_DBLCLK, &CUserSearchDigListBoxCtrl::OnLbnDblclk)
END_MESSAGE_MAP()


void CUserSearchDigListBoxCtrl::clearListBox()
{
	while (this->GetCount())
		this->DeleteString(0);
}

void CUserSearchDigListBoxCtrl::addListBox(const vector<CString>& friendNameList)
{
	for (int i = 0; i < friendNameList.size(); i++)
	{
		int index = this->AddString(friendNameList[i].AllocSysString());
	}
}

void CUserSearchDigListBoxCtrl::OnLbnDblclk()
{
	int i = this->GetCurSel();
	if (i >= 0)
	{
		CString text;
		this->GetText(i, text);

		CString msg;
		CDialgUserAdd dialgAdd(CString("ȷ��������Ӻ���\"") + text + CString("\"��"), &msg);
		int resVal = dialgAdd.DoModal();
		if (resVal == IDOK)
		{
			CString retMsg;
			m_userService.addFriend(text, msg, retMsg);
			MessageBox(retMsg.AllocSysString());
		}
	}
}
