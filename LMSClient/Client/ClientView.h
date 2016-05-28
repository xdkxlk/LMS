
// ClientView.h : CClientView 类的接口
//

#pragma once
#include "Service.h"
#include "Model.h"

class CClientView : public CHtmlView
{
protected: // 仅从序列化创建
	CClientView();
	DECLARE_DYNCREATE(CClientView)

// 特性
public:
	CClientDoc* GetDocument() const;

// 操作
public:
	void flushChat();
	void init();
private:
	CUserService m_userService;
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CClientView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // ClientView.cpp 中的调试版本
inline CClientDoc* CClientView::GetDocument() const
   { return reinterpret_cast<CClientDoc*>(m_pDocument); }
#endif

