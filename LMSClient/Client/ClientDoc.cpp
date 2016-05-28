
// ClientDoc.cpp : CClientDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CClientDoc ����/����

CClientDoc::CClientDoc()
{
	// TODO:  �ڴ����һ���Թ������

}

CClientDoc::~CClientDoc()
{
}

BOOL CClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CClientDoc ���л�

void CClientDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CClientDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CClientDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CClientDoc ���

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


// CClientDoc ����
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

//����������ѵ�HTMLGen
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