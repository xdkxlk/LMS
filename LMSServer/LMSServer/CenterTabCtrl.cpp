#include "stdafx.h"
#include "CenterTabCtrl.h"
#include "resource.h"

CCenterTabCtrl::CCenterTabCtrl()
{
}


CCenterTabCtrl::~CCenterTabCtrl()
{
}

void CCenterTabCtrl::OnInitial()
{
	this->InsertItem(0, _T("�����û�"));
	this->InsertItem(1, _T("�û�Ⱥ��"));
	//����������ҳ
	m_tabUserPage.Create(IDD_TABUSERPAGE, this);
	m_tabGroupPage.Create(IDD_TABGROUP, this);
	//����ҳ���λ����m_tablist�ؼ���Χ��
	CRect rc;
	this->GetClientRect(rc);
	rc.top += 21;
	rc.bottom -= 1;
	rc.left += 1;
	rc.right -= 1;
	m_tabUserPage.MoveWindow(rc);
	m_tabGroupPage.MoveWindow(rc);
	m_tabUserPage.ShowWindow(SW_SHOW);
	this->SetCurSel(0);
}

void CCenterTabCtrl::OnTcnSelchangeCentertab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int curSel = this->GetCurSel();
	switch (curSel)
	{
	case 0:
		m_tabUserPage.ShowWindow(TRUE);
		m_tabGroupPage.ShowWindow(FALSE);
		break;
	case 1:
		m_tabUserPage.ShowWindow(FALSE);
		m_tabGroupPage.ShowWindow(TRUE);
		break;
	default:
		break;
	}
}
BEGIN_MESSAGE_MAP(CCenterTabCtrl, CTabCtrl)
	ON_WM_SIZE()
END_MESSAGE_MAP()


void CCenterTabCtrl::OnSize(UINT nType, int cx, int cy)
{
	CTabCtrl::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	CRect rc;
	this->GetClientRect(rc);
	rc.top += 21;
	rc.bottom -= 1;
	rc.left += 1;
	rc.right -= 1;

	if (m_tabUserPage.m_hWnd!=NULL)
		m_tabUserPage.MoveWindow(rc);
	if (m_tabGroupPage.m_hWnd != NULL)
		m_tabGroupPage.MoveWindow(rc);
}