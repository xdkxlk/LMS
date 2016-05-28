#include "stdafx.h"
#include "Model.h"
#include "StringUtil.h"
#include "JsonUtil.h"

CModel::CModel()
{
}


CModel::~CModel()
{
}

Json::Value CModel::getJson()
{
	Json::Value json;
	return json;
}

bool CModel::fromJson(CString str, CModel& des)
{
	return true;
}


//=================CUser====================
CUser::CUser()
{
}


CUser::~CUser()
{
}

CUser::CUser(const CUser& u)
{
	m_userName = u.m_userName;
	m_password = u.m_password;
	for (int i = 0; i < u.m_friends.size(); i++)
	{
		m_friends.push_back(u.m_friends[i]);
	}
	for (int i = 0; i < u.m_groups.size(); i++)
	{
		m_groups.push_back(u.m_groups[i]);
	}
}

CUser & CUser::operator = (const CUser & u)
{
	m_userName = u.m_userName;
	m_password = u.m_password;
	for (int i = 0; i < u.m_friends.size(); i++)
	{
		m_friends.push_back(u.m_friends[i]);
	}
	for (int i = 0; i < u.m_groups.size(); i++)
	{
		m_groups.push_back(u.m_groups[i]);
	}
	return *this;
}

Json::Value CUser::getJson()
{
	Json::Value json = CModel::getJson();

	json["id"] = Json::Value(m_id);
	json["userName"] = Json::Value(CStringUtil::getStdString(m_userName));
	json["password"] = Json::Value(CStringUtil::getStdString(m_password));

	return json;
}

bool CUser::fromJson(CString str, CUser& des)
{
	if (CModel::fromJson(str, des))
	{
		Json::Value json_object;
		if (!CJsonUtil::genJsonVal(str, json_object))
			return false;
		if (!json_object["id"].isNull())
			des.m_id = json_object["id"].asInt();
		if (!json_object["userName"].isNull())
			des.m_userName = json_object["userName"].asCString();
		if (!json_object["password"].isNull())
			des.m_userName = json_object["password"].asCString();
		return true;
	}
	return false;
}

bool CUser::isFriend(const CString& friName)
{
	return getFriend(friName) != NULL;
}

bool CUser::delFriend(CFriend* fri)
{
	for (auto index = m_friends.begin(); index != m_friends.end(); index++)
	{
		if ((*index)->m_userName == fri->m_userName)
		{
			delete (*index);
			m_friends.erase(index);
			return true;
		}
	}
	return false;
}

CGroup* CUser::getGroup(const CString& groupName)
{
	for (int i = 0; i < m_groups.size(); i++)
	{
		if (m_groups[i]->m_name == groupName)
			return m_groups[i];
	}
	return NULL;
}

bool CUser::addGroup(CGroup* g)
{
	if (getFriend(g->m_name) != NULL)
		return false;

	m_groups.push_back(g);
	return true;
}

bool CUser::delGroup(CGroup* g)
{
	for (auto index = m_groups.begin(); index != m_groups.end(); index++)
	{
		if ((*index)->m_name == g->m_name)
		{
			delete (*index);
			m_groups.erase(index);
			return true;
		}
	}
	return false;
}

bool CUser::addFriend(CFriend* fri)
{
	if (getFriend(fri->m_userName) != NULL)
		return false;

	m_friends.push_back(fri);
	return true;
}

CFriend* CUser::getFriend(const CString& friName)
{
	for (int i = 0; i < m_friends.size(); i++)
	{
		if (m_friends[i]->m_userName == friName)
			return m_friends[i];
	}
	return NULL;
}

bool CUser::operator< (const CUser& u) const
{
	return m_userName<u.m_userName;
}

bool CUser::operator>(const CUser& u) const
{
	return m_userName>u.m_userName;
}

bool CUser::operator== (const CUser& u) const
{
	return m_userName == u.m_userName;
}

bool CUser::operator!= (const CUser& u) const
{
	return !(*this == u);
}

//========================CFriend=====================
CFriend::CFriend()
{
	m_msgNum = 0;
}

CFriend::CFriend(const CFriend& f)
{
	m_userName = f.m_userName;
	m_status = f.m_status;
	m_msgNum = f.m_msgNum;
}

CFriend & CFriend::operator = (const CFriend &f)
{
	m_userName = f.m_userName;
	m_status = f.m_status;
	m_msgNum = f.m_msgNum;
	return *this;
}

bool CFriend::operator< (const CFriend& fri) const
{
	return m_userName<fri.m_userName;
}

bool CFriend::operator>(const CFriend& fri) const
{
	return m_userName>fri.m_userName;
}

bool CFriend::operator== (const CFriend& fri) const
{
	return m_userName == fri.m_userName;
}

bool CFriend::operator!= (const CFriend& fri) const
{
	return !(*this == fri);
}

//=====================================
CGroup::CGroup()
{

}

CGroup::CGroup(const CGroup& g)
{
	m_name = g.m_name;
}

CGroup & CGroup::operator = (const CGroup &f)
{
	m_name = f.m_name;
	return *this;
}

bool CGroup::operator< (const CGroup& fri) const
{
	return m_name<fri.m_name;
}

bool CGroup::operator>(const CGroup& fri) const
{
	return m_name>fri.m_name;
}

bool CGroup::operator== (const CGroup& fri) const
{
	return m_name == fri.m_name;
}

bool CGroup::operator!= (const CGroup& fri) const
{
	return !(*this == fri);
}
