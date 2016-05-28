#include "stdafx.h"
#include "GroupSearchListBox.h"
#include "ConstFile.h"
#include "MFCUtil.h"

BEGIN_MESSAGE_MAP(CGroupSearchListBox, CListBox)
	ON_CONTROL_REFLECT(LBN_DBLCLK, &CGroupSearchListBox::OnLbnDblclk)
END_MESSAGE_MAP()

CGroupSearchListBox::CGroupSearchListBox()
{
}


CGroupSearchListBox::~CGroupSearchListBox()
{
}

void CGroupSearchListBox::clearListBox()
{
	while (this->GetCount())
		this->DeleteString(0);
}

void CGroupSearchListBox::addListBox(const vector<CString>& nameList)
{
	for (int i = 0; i < nameList.size(); i++)
	{
		int index = this->AddString(nameList[i].AllocSysString());
	}
}

void CGroupSearchListBox::OnLbnDblclk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i = this->GetCurSel();
	if (i >= 0)
	{
		CString* text = new CString();
		this->GetText(i, *text);

		int resVal = MessageBox(CString("ȷ���������Ⱥ��\"") + *text + CString("\"��"), _T("����Ⱥ��"), MB_OKCANCEL);
		if (resVal == IDOK)
		{
			CString retMsg;
			if (!m_userService.joinGroup(*text, retMsg))
			{
				MessageBox(retMsg.AllocSysString());
				delete text;
				return;
			}
			MessageBox(_T("����ɹ�"));
		}
	}
}
