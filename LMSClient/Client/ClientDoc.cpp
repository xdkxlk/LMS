
// ClientDoc.cpp : CClientDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Client.h"
#endif

#include "ClientDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CClientDoc

IMPLEMENT_DYNCREATE(CClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CClientDoc, CDocument)
END_MESSAGE_MAP()


// CClientDoc 构造/析构

CClientDoc::CClientDoc()
{
	// TODO:  在此添加一次性构造代码

}

CClientDoc::~CClientDoc()
{
}

BOOL CClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CClientDoc 序列化

void CClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CClientDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CClientDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CClientDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CClientDoc 诊断

#ifdef _DEBUG
void CClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CClientDoc 命令
void CClientDoc::init(const CUser& user)
{
	SetTitle(user.m_userName.AllocSysString());
	m_user = user;
	for (int i = 0; i < m_user.m_friends.size(); i++)
	{
		addFriendHtmlGen(m_user.m_friends[i]);
	}
	for (int i = 0; i < m_user.m_groups.size(); i++)
	{
		addGroupHtmlGen(m_user.m_groups[i]);
	}
}

bool CClientDoc::isFriend(const CString& name)
{
	return m_user.isFriend(name);
}

bool CClientDoc::delFriend(CFriend* frien)
{
	if (frien == NULL)
		return false;
	for (auto index = m_friendChat.begin(); index != m_friendChat.end(); index++)
	{
		if (index->first->m_userName == frien->m_userName)
		{
			delete index->second;
			m_friendChat.erase(index);
			m_user.delFriend(frien);
			return true;
		}
	}
	return false;
}

void CClientDoc::addFriend(CFriend* frien)
{
	if (frien == NULL)
		return;
	if (m_user.addFriend(frien))
		addFriendHtmlGen(frien);
}

void CClientDoc::addFriendHtmlGen(CFriend* frien)
{
	if (frien == NULL)
		return;
	m_friendChat[frien] = new CHtmlGenerator();
}

CFriend* CClientDoc::getFriend(const CString& friendName)
{
	return m_user.getFriend(friendName);
}

CHtmlGenerator* CClientDoc::getFriendHtml(CFriend* frien)
{
	if (frien == NULL)
		return NULL;
	if (m_friendChat.find(frien) != m_friendChat.end())
	{
		return m_friendChat[frien];
	}
	return NULL;
}

CHtmlGenerator* CClientDoc::getFriendHtml(const CString& friName)
{
	for (auto index = m_friendChat.begin(); index != m_friendChat.end(); index++)
	{
		if (index->first->m_userName == friName)
		{
			return index->second;
		}
	}
	return NULL;
}

//更新与此朋友的HTMLGen
void CClientDoc::updateFriendHtml(const CString& frienName, const CString& msg, bool isRemote)
{
	CHtmlGenerator* htmlGen = getFriendHtml(frienName);
	if (htmlGen == NULL)
		return;

	if (isRemote)
		htmlGen->addMsg(frienName, msg, CHtmlData::HTMLDATATYPE::OTHER);
	else
		htmlGen->addMsg(m_user.m_userName, msg, CHtmlData::HTMLDATATYPE::USER);
}

bool CClientDoc::delGroup(CGroup* g)
{
	if (g == NULL)
		return false;
	for (auto index = m_groupChat.begin(); index != m_groupChat.end(); index++)
	{
		if (index->first->m_name == g->m_name)
		{
			delete index->second;
			m_groupChat.erase(index);
			m_user.delGroup(g);
			return true;
		}
	}
	return false;
}

void CClientDoc::addGroup(CGroup* g)
{
	if (g == NULL)
		return;
	if (m_user.addGroup(g))
		addGroupHtmlGen(g);
}

void CClientDoc::addGroupHtmlGen(CGroup* g)
{
	if (g == NULL)
		return;
	m_groupChat[g] = new CHtmlGenerator();
}

CGroup* CClientDoc::getGroup(const CString& groupName)
{
	return m_user.getGroup(groupName);
}

void CClientDoc::updateGroupHtml(const CString& gName, const CString& userName, const CString& msg, bool isRemote)
{
	CHtmlGenerator* htmlGen = getGroupHtml(gName);
	if (htmlGen == NULL)
		return;

	if (isRemote)
		htmlGen->addMsg(userName, msg, CHtmlData::HTMLDATATYPE::OTHER);
	else
		htmlGen->addMsg(m_user.m_userName, msg, CHtmlData::HTMLDATATYPE::USER);
}

CHtmlGenerator* CClientDoc::getGroupHtml(CGroup* g)
{
	if (g == NULL)
		return NULL;
	if (m_groupChat.find(g) != m_groupChat.end())
	{
		return m_groupChat[g];
	}
	return NULL;
}

CHtmlGenerator* CClientDoc::getGroupHtml(const CString& gName)
{
	for (auto index = m_groupChat.begin(); index != m_groupChat.end(); index++)
	{
		if (index->first->m_name == gName)
		{
			return index->second;
		}
	}
	return NULL;
}

void CClientDoc::free()
{
	for (auto index = m_groupChat.begin(); index != m_groupChat.end(); index++)
	{
		delete index->second;
		delete index->first;
	}
	for (auto index = m_friendChat.begin(); index != m_friendChat.end(); index++)
	{
		delete index->second;
		delete index->first;
	}
}