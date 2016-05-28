#pragma once
#include "afx.h"
#include "json.h"

class CModel
{
public:

	CModel();
	~CModel();
	virtual Json::Value getJson();
	static bool fromJson(CString str, CModel& des);
};

//===============CGroup===============
class CGroup : public CModel
{
public:
	int m_id;
	CString m_name;
};

class CGroupSum : public CGroup
{
public:
	int m_num;
};

//=====================CUser=======================
class CUser : public CModel
{
public:
	CUser();
	CUser(const CUser& u);
	~CUser();
	CUser & operator = (const CUser &);
	bool operator<(const CUser& u) const;
	bool operator>(const CUser& u) const;
	bool operator==(const CUser& u) const;
	bool operator!=(const CUser& u) const;

	virtual Json::Value getJson();
	static bool fromJson(CString str, CUser& des);
	static bool fromJson(Json::Value jsonObject, CUser& des);
public:
	int m_id;
	CString m_userName;
	CString m_password;
};