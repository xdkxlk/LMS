#pragma once
#include "Model.h"
#include <map>
#include "Controller.h"
#include <vector>

using namespace std;

class CUserSession
{
public:
	CUserSession();
	~CUserSession();
	bool getUser(vector<CUser>& userList);
	bool getUser(SOCKET_INFORMATION* socket, CUser& user);
	bool isOnLine(CUser user);
	bool isOnLine(const CString& userName);
	bool isOnLine(SOCKET_INFORMATION* socket);
	bool forceOffLine(const CString& userName);
	void bindSocket(CUser user, SOCKET_INFORMATION* socket);
	void freeSocket(SOCKET_INFORMATION* socket);
	SOCKET_INFORMATION* getUserSocketInfo(const CString& name);
	SOCKET_INFORMATION* getUserSocketInfo(const CUser& user);
private:
	map<CUser, SOCKET_INFORMATION*> m_userScoket;
	map<SOCKET_INFORMATION*, CUser> m_scoketUser;
};