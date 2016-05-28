
// ClientDoc.h : CClientDoc 类的接口
//
#pragma once
#include "Model.h"
#include <map>
#include "HtmlGenerator.h"

using namespace std;

class CClientDoc : public CDocument
{
protected: // 仅从序列化创建
	CClientDoc();
	DECLARE_DYNCREATE(CClientDoc)

// 特性
public:
	CUser m_user;
	map<CFriend*, CHtmlGenerator*> m_friendChat;
	map<CGroup*, CHtmlGenerator*> m_groupChat;
// 操作
public:
	void init(const CUser& user);
	bool isFriend(const CString& name);
	bool delFriend(CFriend* frien);
	void addFriend(CFriend* frien);
	void addFriendHtmlGen(CFriend* frien);
	CFriend* getFriend(const CString& friendName);
	void updateFriendHtml(const CString& frienName, const CString& msg, bool isRemote = true);
	CHtmlGenerator* getFriendHtml(CFriend* frien);
	CHtmlGenerator* getFriendHtml(const CString& friName);

	bool delGroup(CGroup* g);
	void addGroup(CGroup* g);
	void addGroupHtmlGen(CGroup* g);
	CGroup* getGroup(const CString& groupName);
	void updateGroupHtml(const CString& gName, const CString& userName, const CString& msg, bool isRemote = true);
	CHtmlGenerator* getGroupHtml(CGroup* g);
	CHtmlGenerator* getGroupHtml(const CString& gName);

	void free();
	// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CClientDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
