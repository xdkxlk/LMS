#include "stdafx.h"
#include "TCPClient.h"
#include "ConstFile.h"
#include "MFCUtil.h"
#include "JsonUtil.h"

WSADATA CWinSocket::m_ws;

bool CWinSocket::initEnviornment()
{
	WSAStartup(MAKEWORD(2, 2), &m_ws);

	return true;
}

void CWinSocket::cleanEnviornment()
{
	WSACleanup();
}

//========================CTCPSender================
const int CTCPSender::MAXDATASIZE = 2048;
SOCKET CTCPSender::m_clientScoket;
SOCKADDR_IN CTCPSender::m_serAddr;

bool CTCPSender::connect()
{
	m_serAddr.sin_family = AF_INET;
	m_serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	m_serAddr.sin_port = htons(8080);

	m_clientScoket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_clientScoket == SOCKET_ERROR)
	{
		return false;
	}
	if (::connect(m_clientScoket, (SOCKADDR*)&m_serAddr, sizeof(m_serAddr)) == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}

void CTCPSender::close()
{
	closesocket(m_clientScoket);
}

bool CTCPSender::sendData(const string& data, string& returnData)
{
	int retVal = send(m_clientScoket, data.c_str(), data.length(), 0);
	if (retVal == SOCKET_ERROR)
	{
		return false;
	}
	char buff[MAXDATASIZE] = { '\0' };
	retVal = recv(m_clientScoket, buff, MAXDATASIZE, 0);
	returnData = buff;
	return true;
}

//========================CTCPClient===================
const int CTCPClient::MAXDATASIZE = 2048;

CTCPClient::CTCPClient()
{
	closesocket(m_clientScoket);
}


CTCPClient::~CTCPClient()
{
	
}

CTCPClient* CTCPClient::getInstance()
{
	static CTCPClient client;
	return &client;
}

bool CTCPClient::startClient(Json::Value signData)
{
	m_serAddr.sin_family = AF_INET;
	m_serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	m_serAddr.sin_port = htons(8080);

	m_clientScoket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_clientScoket == SOCKET_ERROR)
	{
		return false;
	}
	if (connect(m_clientScoket, (SOCKADDR*)&m_serAddr, sizeof(m_serAddr)) == SOCKET_ERROR)
	{
		return false;
	}

	if (!sign(signData))
		return false;

	HWND hWnd = AfxGetMainWnd()->GetSafeHwnd();
	int rest = WSAAsyncSelect(m_clientScoket, hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	if (rest == SOCKET_ERROR)
		return false;
	return true;
}

LRESULT CTCPClient::OnSocket(WPARAM wParam, LPARAM lParam)
{
	char buf[2048];
	int Rec;
	string* str;
	Json::Value json;
	string url;

	if (WSAGETSELECTERROR(lParam))			// 判断套接字是否错误
	{
		return 0;
	}
	else
	{
		switch (WSAGETSELECTEVENT(lParam))	// 判断消息类型
		{
		case FD_CLOSE:
			AfxMessageBox(_T("系统已强制使您下线"));
			CMFCUtil::getMainFrame()->PostMessageW(WM_CLOSE);
			break;
		case FD_READ:			// 处理FD_READ消息
			Rec = recv(m_clientScoket, buf, MAXDATASIZE, 0);	// 接收数据
			buf[Rec] = '\0';

			CJsonUtil::genJsonVal(string(buf), json);
			if (!json["url"].isNull())
			{
				url = json["url"].asString();
				if (url == "/offLineData")
				{
					for (int i = 0; i < json["data"].size(); i++)
					{
						dataResolve(json["data"][i]);
					}
				}
				else{
					dataResolve(json);
				}
			}
			/*
			Json::Value res = this->dataResolve(string(buf), SocketInfo);
			string strRes = CJsonUtil::toString(res);
			send(SocketInfo->Socket, strRes.c_str(), strRes.length(), 0);*/
			break;
		default:
			break;
		}
	}
	return 0;
}

void CTCPClient::dataResolve(const Json::Value& json)
{
	string url = json["url"].asString();
	if (url == "/user/addFriend")
		m_userService.replyAddFriend(json);
	else if (url == "/user/addFriend/reply")
		m_userService.resolveDataReplyAddFriend(json);
	else if (url == "/friendStatus")
		m_userService.updateFriendStatus(json);
	else if (url == "/user/delFriend/notify")
		m_userService.resolveDelFriendNotify(json);
	else if (url == "/groupMsg")
		m_userService.getMsgFromGroup(json);
	else if (url == "/broadCast")
		m_userService.getBroadcast(json);
	else if (url == "/sendMsgToFriend")
	{
		string* str = new string(CJsonUtil::toString(json));

		::PostMessage(CMFCUtil::getActiveView()->m_hWnd, WM_SOCKET_NEW_MESSAGE, (WPARAM)str, 0);
	}
}

bool CTCPClient::sign(Json::Value signData)
{
	signData["url"] = Json::Value("/login");
	string data = CJsonUtil::toString(signData);

	int retVal = send(m_clientScoket, data.c_str(), data.length(), 0);
	if (retVal == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}