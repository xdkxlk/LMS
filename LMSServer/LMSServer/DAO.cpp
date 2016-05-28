#include "stdafx.h"
#include "DAO.h"
#include "MySQL.h"
#include "StringUtil.h"

using namespace std;

//=================CBaseDAO========================
bool CBaseDAO::contendiLLegalChar(CString sql)
{
	return CStringUtil::strMatch(sql, "[~`!@#$%^&*()=\\.?]");
}

//=================CUserDAO========================
bool CUSerDAO::getByName(CUser& user, CString name)
{
	if (contendiLLegalChar(name))
		return false;
	vector<map<string, string> > res;
	res = CMySQL::GetResult("SELECT * FROM user  u WHERE u.user_name='" +
		CStringUtil::getStdString(name) + "'");
	return genUser(user, res);
}

bool CUSerDAO::getByName(vector<CUser>& userList, CString name)
{
	if (contendiLLegalChar(name))
		return false;
	vector<map<string, string> > res;
	res = CMySQL::GetResult("SELECT * FROM user  u WHERE u.user_name LIKE '%" +
		CStringUtil::getStdString(name) + "%'");
	return genUserList(userList, res);
}

bool CUSerDAO::insert(const CUser& user)
{
	if (contendiLLegalChar(user.m_userName) || contendiLLegalChar(user.m_password))
		return false;
	return CMySQL::InsertValues("user"
		, { "user_name", "password" }
		, { CStringUtil::getStdString(user.m_userName), CStringUtil::getStdString(user.m_password) });
}

bool CUSerDAO::insertFriend(const CUser& userHost, const CUser& userFriend)
{
	bool flag = CMySQL::InsertValues("user_friend"
		, { "user_host_id", "user_friend_id" }
	, { CStringUtil::fromNum(userHost.m_id), CStringUtil::fromNum(userFriend.m_id) });
	if (flag)
	{
		return CMySQL::InsertValues("user_friend"
			, { "user_host_id", "user_friend_id" }
		, { CStringUtil::fromNum(userFriend.m_id), CStringUtil::fromNum(userHost.m_id) });
	}
	return false;
}
bool CUSerDAO::delFriend(const CUser& userHost, const CUser& userFriend)
{
	string hostID = CStringUtil::fromNum(userHost.m_id);
	string friID = CStringUtil::fromNum(userFriend.m_id);

	string sql = "DELETE FROM user_friend WHERE user_host_id = ";
	sql += hostID;
	sql += " AND user_friend_id = ";
	sql += friID;
	sql += " OR user_host_id = ";
	sql += friID;
	sql += " AND user_friend_id = ";
	sql += hostID;

	return CMySQL::ExecuteSql(sql);
}

bool CUSerDAO::genUser(CUser& user, vector<map<string, string> > res)
{
	if (res.empty())
		return false;
	user.m_id = CStringUtil::toInt(res[0]["id"]);
	user.m_userName = CStringUtil::getCString(res[0]["user_name"]);
	user.m_password = CStringUtil::getCString(res[0]["password"]);
	return true;
}

bool CUSerDAO::genUserList(std::vector<CUser>& userList, vector<map<string, string> > res)
{
	for (auto s : res)
	{
		CUser user;
		user.m_id = CStringUtil::toInt(s["id"]);
		user.m_userName = CStringUtil::getCString(s["user_name"]);
		user.m_password = CStringUtil::getCString(s["password"]);
		userList.push_back(user);
	}
	return true;
}

bool CUSerDAO::getByID(CUser& user, int id)
{
	string sql = "SELECT * FROM user  u WHERE u.id=";
	sql += CStringUtil::fromNum(id);

	auto res = CMySQL::GetResult(sql);
	return genUser(user, res);
}

bool CUSerDAO::getFriends(vector<CUser>& friendList, const CUser& user)
{
	string sql = "SELECT u2.* FROM `user` u1, `user` u2, user_friend uf WHERE u1.id=uf.user_host_id AND u2.id=uf.user_friend_id AND u1.id=";
	sql += CStringUtil::fromNum(user.m_id);

	auto res = CMySQL::GetResult(sql);
	return genUserList(friendList, res);
}

//===========CGroupDAO==========================
bool CGroupDAO::insert(const CGroup& group)
{
	bool flag = CMySQL::InsertValues("group", { "name"}	, { CStringUtil::getStdString(group.m_name)} );
	return flag;
}

bool CGroupDAO::getAllGroup(std::vector<CGroupSum>& groupList)
{
	string sql = "SELECT g.id, g.`name`, COUNT(DISTINCT ug.user_id) AS num FROM user_group ug, `group` g WHERE ug.group_id = g.id GROUP BY g.id";
	vector<map<string, string> > res;

	res = CMySQL::GetResult(sql);

	for (auto s : res)
	{
		CGroupSum group;
		group.m_id = CStringUtil::toInt(s["id"]);
		group.m_name = CStringUtil::getCString(s["name"]);
		group.m_num = CStringUtil::toInt(s["num"]);
		groupList.push_back(group);
	}
	return true;
}

bool CGroupDAO::getGroupUser(std::vector<std::string>& userList, const CString& groupName)
{
	string sql = "SELECT u.user_name FROM `group` g, `user` u, user_group ug WHERE ug.user_id=u.id AND ug.group_id=g.id AND g.`name`='";
	sql += CStringUtil::getStdString(groupName);
	sql += "'";
	vector<map<string, string> > res;

	res = CMySQL::GetResult(sql);

	for (auto s : res)
	{
		userList.push_back(s["user_name"]);
	}
	return true;
}

bool CGroupDAO::getUserGroup(std::vector<CGroup>& groupList, const CString& userName)
{
	string sql = "SELECT g.id, g.`name` FROM `group` g, `user` u, user_group ug WHERE ug.user_id=u.id AND ug.group_id=g.id AND u.user_name='";
	sql += CStringUtil::getStdString(userName);
	sql += "'";
	vector<map<string, string> > res;

	res = CMySQL::GetResult(sql);
	return genGroupList(groupList, res);
}

bool CGroupDAO::genGroup(CGroup& group, std::vector<std::map<std::string, std::string> > res)
{
	if (res.empty())
		return false;
	group.m_id = CStringUtil::toInt(res[0]["id"]);
	group.m_name = CStringUtil::getCString(res[0]["name"]);

	return true;
}

bool CGroupDAO::genGroupList(std::vector<CGroup>& groupList, std::vector<std::map<std::string, std::string> > res)
{
	for (auto s : res)
	{
		CGroup group;
		group.m_id = CStringUtil::toInt(s["id"]);
		group.m_name = CStringUtil::getCString(s["name"]);
		groupList.push_back(group);
	}
	return true;
}

bool CGroupDAO::joinGroup(const CUser& user, const CGroup& group)
{
	bool flag = CMySQL::InsertValues("user_group", { "user_id", "group_id" },
	{ CStringUtil::fromNum(user.m_id), CStringUtil::fromNum(group.m_id) });

	return flag;
}

bool CGroupDAO::getGroup(std::vector<CGroup>& groupList, const CString& groupName)
{
	string sql = "SELECT g.* FROM `group` g WHERE g.`name` LIKE '%";
	sql += CStringUtil::getStdString(groupName);
	sql += "%'";
	vector<map<string, string> > res;

	res = CMySQL::GetResult(sql);
	return genGroupList(groupList, res);
}

bool CGroupDAO::getGroup(CGroup& group, const CString& groupName)
{
	string sql = "SELECT g.* FROM `group` g WHERE g.`name` = '";
	sql += CStringUtil::getStdString(groupName);
	sql += "'";
	vector<map<string, string> > res;

	res = CMySQL::GetResult(sql);
	return genGroup(group, res);
}

bool CGroupDAO::quitGroup(const CUser& user, const CGroup& group)
{
	string sql = "DELETE FROM user_group WHERE user_id = ";
	sql += CStringUtil::fromNum(user.m_id);
	sql += " AND group_id = ";
	sql += CStringUtil::fromNum(group.m_id);

	return CMySQL::ExecuteSql(sql);
}