#include "stdafx.h"
#include "Service.h"

bool CUserService::login(CUser& user)
{
	CUser cerUser;
	if (!m_userDAO.getByName(cerUser,user.m_userName))
		return false;
	if (cerUser.m_password == user.m_password)
	{
		user = cerUser;
		return true;
	}
	return false;
}

bool CUserService::searchPeo(vector<CUser>& userList, CString name)
{
	return m_userDAO.getByName(userList, name);
}

bool CUserService::getFriends(vector<CUser>& userList, CUser user)
{
	return m_userDAO.getFriends(userList, user);
}

bool CUserService::delFriend(const CUser& userHost, const CString& friendName)
{
	CUser fri;
	if (!m_userDAO.getByName(fri, friendName))
		return false;
	return m_userDAO.delFriend(userHost, fri);
}

bool CUserService::addFriend(const CUser& userHost, const CUser& userFriend)
{
	if (userHost.m_userName == userFriend.m_userName)
		return false;
	return m_userDAO.insertFriend(userHost, userFriend);
}

bool CUserService::addFriend(const CUser& userHost, const CString& friendName)
{
	CUser fri;
	if (!m_userDAO.getByName(fri, friendName))
		return false;
	return addFriend(userHost, fri);
}

bool CUserService::addFriend(const CString& userName, const CString& friendName)
{
	CUser user;
	if (!m_userDAO.getByName(user, userName))
		return false;
	return addFriend(user, friendName);
}

bool CUserService::isHisFriend(const CUser& userHost, const CString& friendName)
{
	vector<CUser> frList;
	if (!getFriends(frList, userHost))
		return true;
	for (CUser u : frList)
	{
		if (u.m_userName == friendName)
			return true;
	}
	return false;
}

bool CUserService::getGroupUser(std::vector<std::string>& userList, const CString& groupName)
{
	return m_groupDAO.getGroupUser(userList, groupName);
}

bool CUserService::getUserGroup(std::vector<CGroup>& groupList, const CString& userName)
{
	return m_groupDAO.getUserGroup(groupList, userName);
}

bool CUserService::isInGroup(const CUser& userHost, const CString& groupName)
{
	vector<CGroup> groupList;
	getUserGroup(groupList, userHost.m_userName);

	for (int i = 0; i < groupList.size(); i++)
	{
		if (groupList[i].m_name == groupName)
			return true;
	}
	return false;
}

bool CUserService::joinGroup(const CUser& userHost, const CString& groupName)
{
	CGroup g;
	if (!m_groupDAO.getGroup(g, groupName))
		return false;
	return m_groupDAO.joinGroup(userHost, g);
}

bool CUserService::searchGroup(vector<CGroup>& groupList, CString name)
{
	return m_groupDAO.getGroup(groupList, name);
}

bool CUserService::quitGroup(const CUser& userHost, const CString& groupName)
{
	CGroup g;
	if (!m_groupDAO.getGroup(g, groupName))
		return false;
	return m_groupDAO.quitGroup(userHost, g);
}

bool CUserService::regist(const CUser& user)
{
	return m_userDAO.insert(user);
}

bool CUserService::searchPeo(CUser& user, CString name)
{
	return m_userDAO.getByName(user, name);
}