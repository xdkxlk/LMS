
// ClientView.cpp : CClientView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Client.h"
#endif

#include "ClientDoc.h"
#include "ClientView.h"
#include "MFCUtil.h"
#include "ConstFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientView

IMPLEMENT_DYNCREATE(CClientView, CHtmlView)

BEGIN_MESSAGE_MAP(CClientView, CHtmlView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_MESSAGE(WM_SOCKET_NEW_MESSAGE, &CClientView::OnSocketNewMessage)
	ON_MESSAGE(WM_ONE_USER_SELECT, &CClientView::OnOneUserSelect)
	ON_MESSAGE(WM_DEL_FRIEND, &CClientView::OnDelFriend)
	ON_MESSAGE(WM_DEL_FRIEND_BACKGROUND, &CClientView::OnDelFriendBackground)
	ON_MESSAGE(WM_ONE_GROUP_SELECT, &CClientView::OnOneGroupSelect)
	ON_MESSAGE(WM_QUIT_GROUP, &CClientView::OnQuitGroup)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CClientView 构造/析构

CClientView::CClientView()
{
	// TODO:  在此处添加构造代码
	m_nowChatShowFriend = NULL;
	m_nowChatShowGroup = NULL;
}

CClientView::~CClientView()
{
}

BOOL CClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CHtmlView::PreCreateWindow(cs);
}

void CClientView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	CMFCUtil::getMainFrame()->init();

	Navigate2(_T("about:blank"), NULL, NULL, NULL, NULL);
}

void CClientView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CClientView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CClientView 诊断

#ifdef _DEBUG
void CClientView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CClientView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CClientDoc* CClientView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClientDoc)));
	return (CClientDoc*)m_pDocument;
}
#endif //_DEBUG


// CClientView 消息处理程序

void CClientView::OnDocumentComplete(LPCTSTR lpszURL)
{
	// TODO:  在此添加专用代码和/或调用基类

	CHtmlView::OnDocumentComplete(lpszURL);
}

void CClientView::init()
{

}

void CClientView::flushChat()
{
	if (m_nowChatShowFriend != NULL)
	{
		CClientDoc* doc = GetDocument();
		CHtmlGenerator* htmlGen = doc->getFriendHtml(m_nowChatShowFriend);

		IHTMLDocument2* htmlDoc = (IHTMLDocument2*)GetHtmlDocument();
		htmlGen->flush(htmlDoc);
	}
	else if (m_nowChatShowGroup != NULL)
	{
		CClientDoc* doc = GetDocument();
		CHtmlGenerator* htmlGen = doc->getGroupHtml(m_nowChatShowGroup);

		IHTMLDocument2* htmlDoc = (IHTMLDocument2*)GetHtmlDocument();
		htmlGen->flush(htmlDoc);
	}
	else
	{
		Navigate2(_T("about:blank"), NULL, NULL, NULL, NULL);
	}
}

afx_msg LRESULT CClientView::OnSocketNewMessage(WPARAM wParam, LPARAM lParam)
{
	string *retData = (string*)wParam;

	m_userService.getMsgFromFri(*retData);

	delete retData;
	return 0;
}


afx_msg LRESULT CClientView::OnOneUserSelect(WPARAM wParam, LPARAM lParam)
{
	CFriend* f = (CFriend*)wParam;
	m_nowChatShowGroup = NULL;
	if (m_nowChatShowFriend != f)
	{
		m_nowChatShowFriend = f;
		flushChat();
	}
	::PostMessage(CMFCUtil::getMainFrame()->m_wndOutput.m_wndInput.m_hWnd,
		WM_ONE_USER_SELECT, wParam, NULL);

	return 0;
}

afx_msg LRESULT CClientView::OnOneGroupSelect(WPARAM wParam, LPARAM lParam)
{
	CGroup* g = (CGroup*)wParam;
	m_nowChatShowFriend = NULL;
	if (m_nowChatShowGroup != g)
	{
		m_nowChatShowGroup = g;
		flushChat();
	}
	::PostMessage(CMFCUtil::getMainFrame()->m_wndOutput.m_wndInput.m_hWnd,
		WM_ONE_GROUP_SELECT, wParam, NULL);

	return 0;
}

afx_msg LRESULT CClientView::OnDelFriend(WPARAM wParam, LPARAM lParam)
{
	CString retMsg;
	CFriend* fri = (CFriend*)wParam;
	CString* friendName = new CString(fri->m_userName);

	bool nameEqual = ((m_nowChatShowFriend != NULL) &&
		(m_nowChatShowFriend->m_userName == *friendName));
	if (m_userService.delFriend(fri->m_userName, retMsg))
	{
		if (nameEqual)
		{
			m_nowChatShowFriend = NULL;
			flushChat();
			::PostMessage(CMFCUtil::getMainFrame()->m_wndOutput.m_wndInput.m_hWnd,
				WM_DISABLE_INPUT, NULL, NULL);
		}
		::PostMessage(CMFCUtil::getMainFrame()->m_wndClassView.m_wndListCtrl.m_hWnd,
			WM_DEL_FRIEND, (WPARAM)friendName, NULL);
	}
	else
	{
		MessageBox(retMsg.AllocSysString());
	}
	return 0;
}


afx_msg LRESULT CClientView::OnDelFriendBackground(WPARAM wParam, LPARAM lParam)
{
	CString* friendName = (CString*)wParam;
	CString* postMsgPar = new CString(*friendName);
	bool nameEqual = ((m_nowChatShowFriend != NULL) && 
										(m_nowChatShowFriend->m_userName == *friendName));

	::PostMessage(CMFCUtil::getMainFrame()->m_wndClassView.m_wndListCtrl.m_hWnd,
		WM_DEL_FRIEND, (WPARAM)postMsgPar, NULL);
	if (GetDocument()->delFriend(CMFCUtil::getActiveDoc()->getFriend(*friendName)))
	{
		if (nameEqual)
		{
			m_nowChatShowFriend = NULL;
			flushChat();
			::PostMessage(CMFCUtil::getMainFrame()->m_wndOutput.m_wndInput.m_hWnd,
				WM_DISABLE_INPUT, NULL, NULL);
		}
	}
	delete friendName;
	return 0;
}

afx_msg LRESULT CClientView::OnQuitGroup(WPARAM wParam, LPARAM lParam)
{
	CString retMsg;
	CGroup* g = (CGroup*)wParam;
	CString* groupName = new CString(g->m_name);

	bool nameEqual = ((m_nowChatShowGroup != NULL) &&
		(m_nowChatShowGroup->m_name == *groupName));
	if (m_userService.quitGroup(g->m_name, retMsg))
	{
		if (nameEqual)
		{
			m_nowChatShowGroup = NULL;
			flushChat();
			::PostMessage(CMFCUtil::getMainFrame()->m_wndOutput.m_wndInput.m_hWnd,
				WM_DISABLE_INPUT, NULL, NULL);
		}
		::PostMessage(CMFCUtil::getMainFrame()->m_wndFileView.m_wndGroupView.m_hWnd,
			WM_QUIT_GROUP, (WPARAM)groupName, NULL);
	}
	else
	{
		MessageBox(retMsg.AllocSysString());
	}
	return 0;
}


void CClientView::OnDestroy()
{
	CHtmlView::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	GetDocument()->free();
}
