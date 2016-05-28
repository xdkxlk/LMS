#pragma once
#include "DAO.h"

//===================CUserService===================
class CUserService
{
public:
	bool regist(const CUser& user);
	bool login(CUser& user);
	bool searchPeo(CUser& user, CString name);
	bool searchPeo(vector<CUser>& userList, CString name);
	bool getFriends(vector<CUser>& userList, CUser user);
	bool delFriend(const CUser& userHost, const CString& friendName);
	bool addFriend(const CUser& userHost, const CUser& userFriend);
	bool addFriend(const CUser& userHost, const CString& friendName);
	bool addFriend(const CString& userName, const CString& friendName);
	bool isHisFriend(const CUser& userHost, const CString& friendName);

	bool isInGroup(const CUser& userHost, const CString& groupName);
	bool joinGroup(const CUser& userHost, const CString& groupName);
	bool quitGroup(const CUser& userHost, const CString& groupName);
	bool searchGroup(vector<CGroup>& groupList, CString name);
	bool getGroupUser(std::vector<std::string>& userList, const CString& groupName);
	bool getUserGroup(std::vector<CGroup>& groupList, const CString& userName);
private:
	CUSerDAO m_userDAO;
	CGroupDAO m_groupDAO;
};

class CGroupService
{
public:
	
};