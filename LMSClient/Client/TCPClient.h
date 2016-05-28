#pragma once
#include <WinSock2.h>
#include <string>
#include "Model.h"
#include <map>
#include "Service.h"

using namespace std;


class CWinSocket
{
public:
	static bool initEnviornment();
	static void cleanEnviornment();

	static WSADATA m_ws;
};


class CTCPSender
{
public:
	static bool connect();
	static void close();
	static bool sendData(const string& data, string& returnData);

public:
	static const int MAXDATASIZE;

	static SOCKET m_clientScoket;
	static SOCKADDR_IN m_serAddr;
};


class CTCPClient
{
public:
	CTCPClient();
	~CTCPClient();

	static CTCPClient* getInstance();

	bool startClient(Json::Value signData);
	LRESULT OnSocket(WPARAM wParam, LPARAM lParam);
private:
	CUserService m_userService;

	bool sign(Json::Value signData);
	void dataResolve(const Json::Value& json);
public:
	static const int MAXDATASIZE;

	SOCKET m_clientScoket;
	SOCKADDR_IN m_serAddr;
};