#pragma once
#include "afx.h"
#include "json.h"
#include <string>
#include <set>

using namespace std;

class CFriend;
class CGroup;

class CModel
{
public:

	CModel();
	~CModel();
	virtual Json::Value getJson();
	static bool fromJson(CString str, CModel& des);
};

//======================CUser=======================
class CUser : public CModel
{
public:
	CUser();
	CUser(const CUser& u);
	CUser & operator = (const CUser &);
	bool operator< (const CUser& u) const;
	bool operator> (const CUser& u) const;
	bool operator== (const CUser& u) const;
	bool operator!= (const CUser& u) const;
	~CUser();

	bool isFriend(const CString& friName);
	bool delFriend(CFriend* fri);
	bool addFriend(CFriend* fri);
	CFriend* getFriend(const CString& friName);

	CGroup* getGroup(const CString& groupName);
	bool delGroup(CGroup* g);
	bool addGroup(CGroup* g);

	virtual Json::Value getJson();
	static bool fromJson(CString str, CUser& des);
public:
	int m_id;
	CString m_userName;
	CString m_password;
	vector<CFriend*> m_friends;
	vector<CGroup*> m_groups;
};

//===================CFriend===================
class CFriend : public CModel
{
public:
	CFriend();
	CFriend(const CString& name, int status = 0) : m_userName(name), m_status(status){}
	CFriend(const CFriend&);
	CFriend & operator = (const CFriend &);
	bool operator< (const CFriend& fri) const;
	bool operator> (const CFriend& fri) const;
	bool operator== (const CFriend& fri) const;
	bool operator!= (const CFriend& fri) const;

	CString m_userName;
	int m_status;
	int m_msgNum;
};

class CGroup : public CModel
{
public:
	CGroup();
	CGroup(const CString& name) : m_name(name) { }
	CGroup(const CGroup&);
	CGroup & operator = (const CGroup &);
	bool operator< (const CGroup& fri) const;
	bool operator> (const CGroup& fri) const;
	bool operator== (const CGroup& fri) const;
	bool operator!= (const CGroup& fri) const;

	CString m_name;
};