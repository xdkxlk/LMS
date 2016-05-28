#pragma once
#include "Model.h"
#include <vector>
#include <map>
#include <string>

using namespace std;

//=================CBaseDAO========================
class CBaseDAO
{
public:
	static bool contendiLLegalChar(CString sql);
};

//=================CUserDAO========================
class CUSerDAO : public CBaseDAO
{
public:
	bool getByName(CUser& user, CString name);
	bool getByName(vector<CUser>& userList, CString name);
	bool getByID(CUser& user, int id);
	bool getFriends(vector<CUser>& friendList, const CUser& user);

	bool insert(const CUser& user);
	bool insertFriend(const CUser& userHost, const CUser& userFriend);

	bool delFriend(const CUser& userHost, const CUser& userFriend);
	
private:
	bool genUser(CUser& user, std::vector<std::map<std::string, std::string> > res);
	bool genUserList(std::vector<CUser>& userList, std::vector<std::map<std::string, std::string> > res);
};

//=================CGroupDAO====================
class CGroupDAO : public CBaseDAO
{
public:
	bool insert(const CGroup& group);
	bool quitGroup(const CUser& user, const CGroup& group);
	bool joinGroup(const CUser& user, const CGroup& group);

	bool getGroup(std::vector<CGroup>& groupList, const CString& groupName);
	bool getGroup(CGroup& group, const CString& groupName);
	bool getAllGroup(std::vector<CGroupSum>& groupList);
	bool getGroupUser(std::vector<std::string>& userList, const CString& groupName);
	bool getUserGroup(std::vector<CGroup>& groupList, const CString& userName);

private:
	bool genGroup(CGroup& group, std::vector<std::map<std::string, std::string> > res);
	bool genGroupList(std::vector<CGroup>& groupList, std::vector<std::map<std::string, std::string> > res);
};