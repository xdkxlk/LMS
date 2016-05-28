#include "stdafx.h"
#include "Model.h"
#include "StringUtil.h"
#include "JsonUtil.h"
#include "json.h"

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

//==================CUser===========================
CUser::CUser()
{
}


CUser::~CUser()
{
}

CUser::CUser(const CUser& u)
{
	m_id = u.m_id;
	m_userName = u.m_userName;
	m_password = u.m_password;
}

CUser & CUser::operator= (const CUser & u)
{
	m_id = u.m_id;
	m_userName = u.m_userName;
	m_password = u.m_password;
	return *this;
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
		return fromJson(json_object, des);
	}
	return false;
}

bool CUser::fromJson(Json::Value jsonObject, CUser& des)
{
	if (!jsonObject["id"].isNull())
		des.m_id = jsonObject["id"].asInt();
	if (!jsonObject["userName"].isNull())
		des.m_userName = jsonObject["userName"].asCString();
	if (!jsonObject["password"].isNull())
		des.m_password = jsonObject["password"].asCString();
	return true;
}