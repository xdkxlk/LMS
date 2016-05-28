#include "stdafx.h"
#include "UserSession.h"
#include "UUIDUtil.h"

//===========================================
CUserSession::CUserSession()
{
}


CUserSession::~CUserSession()
{
}

bool CUserSession::getUser(vector<CUser>& userList)
{
	for (auto index = m_scoketUser.begin(); index != m_scoketUser.end(); index++)
	{
		userList.push_back(index->second);
	}
	return true;
}

bool CUserSession::getUser(SOCKET_INFORMATION* socket, CUser& user)
{
	map<SOCKET_INFORMATION*, CUser>::iterator suIndex = m_scoketUser.find(socket);
	if (suIndex != m_scoketUser.end())
	{
		user = suIndex->second;
		return true;
	}
	return false;
}

bool CUserSession::isOnLine(const CString& userName)
{
	CUser u;
	u.m_userName = userName;
	return isOnLine(u);
}

bool CUserSession::isOnLine(CUser user)
{
	map<CUser, SOCKET_INFORMATION*>::iterator usIndex = m_userScoket.find(user);
	if (usIndex != m_userScoket.end())
	{
		return true;
	}
	return false;
}

bool CUserSession::isOnLine(SOCKET_INFORMATION* socket)
{
	map<SOCKET_INFORMATION*, CUser>::iterator suIndex = m_scoketUser.find(socket);
	if (suIndex != m_scoketUser.end())
	{
		return true;
	}
	return false;
}

void CUserSession::bindSocket(CUser user, SOCKET_INFORMATION* socket)
{
	m_userScoket[user] = socket;
	m_scoketUser[socket] = user;
}

void CUserSession::freeSocket(SOCKET_INFORMATION* socket)
{
	map<SOCKET_INFORMATION*, CUser>::iterator suIndex = m_scoketUser.find(socket);
	if (suIndex != m_scoketUser.end())
	{
		map<CUser, SOCKET_INFORMATION*>::iterator usIndex = m_userScoket.find(suIndex->second);
		m_userScoket.erase(usIndex);
		m_scoketUser.erase(suIndex);
	}
}

SOCKET_INFORMATION* CUserSession::getUserSocketInfo(const CString& name)
{
	CUser u;
	u.m_userName = name;
	return getUserSocketInfo(u);
}

SOCKET_INFORMATION* CUserSession::getUserSocketInfo(const CUser& user)
{
	auto index = m_userScoket.find(user);
	if (index != m_userScoket.end())
	{
		return index->second;
	}
	return NULL;
}