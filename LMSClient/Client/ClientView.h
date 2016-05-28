
// ClientView.h : CClientView ��Ľӿ�
//

#pragma once
#include "Service.h"
#include "Model.h"

class CClientView : public CHtmlView
{
protected: // �������л�����
	CClientView();
	DECLARE_DYNCREATE(CClientView)

// ����
public:
	CClientDoc* GetDocument() const;

// ����
public:
	void flushChat();
	void init();
private:
	CUserService m_userService;
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnDocumentComplete(LPCTSTR lpszURL);
protected:
	afx_msg LRESULT OnSocketNewMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnOneUserSelect(WPARAM wParam, LPARAM lParam);
public:
	CFriend* m_nowChatShowFriend;
	CGroup* m_nowChatShowGroup;
protected:
	afx_msg LRESULT OnDelFriend(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDelFriendBackground(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnOneGroupSelect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnQuitGroup(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // ClientView.cpp �еĵ��԰汾
inline CClientDoc* CClientView::GetDocument() const
   { return reinterpret_cast<CClientDoc*>(m_pDocument); }
#endif

