#include "stdafx.h"
#include "Controller.h"
#include "JsonUtil.h"
#include "MFCUtil.h"
#include "StringUtil.h"
#include "UserSession.h"
#include "LMSServerDoc.h"
#include "Redis.h"

CUserSession* getUserSession()
{
	CLMSServerDoc* doc = CMFCUtil::getActiveDoc();
	return &doc->m_userSession;
}

CTCPServer::CTCPServer()
{
	initEnviornment();
}

CTCPServer::~CTCPServer()
{
	cleanEnviornment();
}

BEGIN_MESSAGE_MAP(CTCPServer, CWnd)

END_MESSAGE_MAP()

CTCPServer* CTCPServer::getInstance()
{
	static CTCPServer server;
	return &server;
}

void CTCPServer::initEnviornment()
{
	WSAStartup(MAKEWORD(2, 2), &m_ws);
}

void CTCPServer::cleanEnviornment()
{
	closesocket(m_severScoket);
	WSACleanup();
}

void CTCPServer::startServer()
{
	// �����׽���
	m_severScoket = socket(AF_INET, SOCK_STREAM, 0);
	// ����ʹ��Window���ڽ���FD_ACCEPT�¼���Ϣ
	WSAAsyncSelect(m_severScoket, AfxGetMainWnd()->GetSafeHwnd(), WM_SOCKET, FD_ACCEPT);
	// ���õ�ַ�Ͷ˿�
	my_addr.sin_family = AF_INET;			/* Э��������INET	*/
	my_addr.sin_port = htons(PORT);		/* ��MYPORT�˿�	*/
	my_addr.sin_addr.s_addr = INADDR_ANY;	/* ����IP			*/
	// ���׽���sockaddr�󶨵�my_addr
	if (bind(m_severScoket, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == SOCKET_ERROR)
		return;

	// ����ָ�����׽���
	listen(m_severScoket, BACKLOG);
}

LRESULT CTCPServer::OnSocket(WPARAM wParam, LPARAM lParam)
{
	CUser user;
	CUserSession* session;
	SOCKET_INFORMATION* SocketInfo;	// �׽�����Ϣ
	SOCKET Accept;
	char buf[2048];
	int len;

	if (WSAGETSELECTERROR(lParam))			// �ж��׽����Ƿ����
	{
		return 0;
	}
	else
	{
		switch (WSAGETSELECTEVENT(lParam))	// �ж���Ϣ����
		{
		case FD_ACCEPT:		// ����FD_ACCEPT��Ϣ
			// �������Կͻ��˵����ӣ�Accept����ͻ��˽���ͨ�ŵ��׽���
			SOCKADDR_IN addr;
			len = sizeof(addr);
			if ((Accept = accept(wParam, (sockaddr*)&addr, &len)) == INVALID_SOCKET)
			{
				break;
			}
			// ΪAccept�����׽�����Ϣ
			CreateSocketInformation(Accept, addr);
			// ΪAccept�׽��ֶ���FD_READ��FD_WRITE��FD_CLOSE��Ϣ
			WSAAsyncSelect(Accept, AfxGetMainWnd()->GetSafeHwnd(), WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
			break;
		case FD_CLOSE:
			SocketInfo = GetSocketInformation(wParam);
			session = &(CMFCUtil::getActiveDoc()->m_userSession);

			if (session->getUser(SocketInfo, user))
			{
				m_userController.notifyFriendOnlineStatus(user, false);
			}
			session->freeSocket(SocketInfo);

			CMFCUtil::getActiveView()->m_centerTabCtrl.m_tabUserPage.m_userListCtrl.OnUserLeave((WPARAM)SocketInfo, NULL);

			DelSocketInformation(SocketInfo->MessagerSenderSocket);
			DelSocketInformation(SocketInfo);
			break;
		case FD_READ:			// ����FD_READ��Ϣ
			SocketInfo = GetSocketInformation(wParam);						// ��ȡ�׽�����Ϣ
			int Rec = recv(SocketInfo->Socket, buf, MAXDATASIZE, 0);	// ��������
			buf[Rec] = '\0';

			Json::Value res = this->dataResolve(string(buf), SocketInfo);
			if (res == CBaseController::c_notReply)
				break;

			string strRes = CJsonUtil::toString(res);
			send(SocketInfo->Socket, strRes.c_str(), strRes.length(), 0);
			break;
		}
	}
	return 0;
}

bool CTCPServer::sendData(SOCKET_INFORMATION* sockInfo, Json::Value data, bool socketIsMsgSender)
{
	string strRes = CJsonUtil::toString(data);
	int ret;
	if (!socketIsMsgSender)
		ret = send(sockInfo->MessagerSenderSocket->Socket, strRes.c_str(), strRes.length(), 0);
	else
		ret = send(sockInfo->Socket, strRes.c_str(), strRes.length(), 0);
	return ret != SOCKET_ERROR;
}

Json::Value CTCPServer::dataResolve(const string& data, SOCKET_INFORMATION* socket)
{
	Json::Value json = CJsonUtil::genJsonVal(data);
	Json::Value res;
	if (json["url"].isNull())
		return CBaseController::c_fail;

	string url = json["url"].asString();
	if (url == "/login")
	{
		res = m_userController.login(json, socket);
	}
	else if (url == "/regist")
	{
		res = m_userController.regist(json, socket);
	}
	else
	{
		if (!CBaseController::hasBeenLogin(socket))
			return CBaseController::c_noLogin;
		if (url == "/user/searchPeo")
			res = m_userController.searchPeo(json, socket);
		else if (url == "/sendMsgToFriend")
			res = m_userController.sendMsgToFriend(json, socket);
		else if (url == "/user/addFriend")
			res = m_userController.addFriend(json, socket);
		else if (url == "/user/delFriend")
			res = m_userController.delFriend(json, socket);
		else if (url == "/sendMsgToGroup")
			res = m_userController.sendMsgToGroup(json, socket);
		else if (url == "/searchGroup")
			res = m_userController.searchGroup(json, socket);
		else if (url == "/joinGroup")
			res = m_userController.joinGroup(json, socket);
		else if (url == "/quitGroup")
			res = m_userController.quitGroup(json, socket);
		else if (url == "/getUserStatus")
			res = m_userController.getUserStatus(json, socket);
		else
			res = CBaseController::c_persentError;
	}
	return res;
}

void CTCPServer::CreateSocketInformation(SOCKET s, SOCKADDR_IN addr)
{
	SOCKET_INFORMATION* SI;
	// ����ռ�
	if ((SI = (SOCKET_INFORMATION*)GlobalAlloc(GPTR,
		sizeof(SOCKET_INFORMATION))) == NULL)
	{
		return;
	}
	// ����SI�ṹ�������
	SI->Addr = addr;
	SI->Socket = s;
	SI->Next = SocketInfoList;		// Nextָ����ǰ��SocketInfoList
	SocketInfoList = SI;					// ��SI�ŵ�SocketInfoList�ĵ�1λ
}

// ��ȡָ���׽���s��Ӧ��SOCKET_INFORMATION����
SOCKET_INFORMATION* CTCPServer::GetSocketInformation(SOCKET s)
{
	SOCKET_INFORMATION *SI = SocketInfoList;
	while (SI)
	{
		if (SI->Socket == s)
			return SI;

		SI = SI->Next;
	}
	return NULL;
}

void CTCPServer::DelSocketInformation(SOCKET_INFORMATION* info)
{
	if (info == NULL)
		return;
	SOCKET_INFORMATION *SI = SocketInfoList;
	SOCKET_INFORMATION* pre = SI;
	if (SocketInfoList->Socket == info->Socket)
	{
		SocketInfoList = info->Next;
		GlobalFree(info);
		return;
	}
	while (SI)
	{
		if (SI->Next && SI->Next->Socket == info->Socket)
		{
			SI->Next = info->Next;
			GlobalFree(info);
			return;
		}
		SI = SI->Next;
	}
}

void CTCPServer::FreeAll()
{
	SOCKET_INFORMATION *SI = SocketInfoList;
	while (SI)
	{
		SOCKET_INFORMATION *next = SI->Next;
		closesocket(SI->Socket);
		GlobalFree(SI);
		SI = next;
	}
	SocketInfoList = NULL;
}

void CTCPServer::forceOffLine(const CString& userName)
{
	SOCKET_INFORMATION* sInfo = getUserSession()->getUserSocketInfo(userName);
	if (sInfo != NULL)
	{
		closesocket(sInfo->MessagerSenderSocket->Socket);
		closesocket(sInfo->Socket);

		CUser user;
		if (getUserSession()->getUser(sInfo, user))
		{
			m_userController.notifyFriendOnlineStatus(user, false);
		}
		getUserSession()->freeSocket(sInfo);

		CMFCUtil::getActiveView()->m_centerTabCtrl.m_tabUserPage.m_userListCtrl.OnUserLeave((WPARAM)sInfo, NULL);

		DelSocketInformation(sInfo->MessagerSenderSocket);
		DelSocketInformation(sInfo);
	}
}

//=====================CBaseController=======================================
const Json::Value CBaseController::c_notReply = CJsonUtil::genJsonVal("{\"code\":-1}");
const Json::Value CBaseController::c_success = CJsonUtil::genJsonVal("{\"code\":0}");
const Json::Value CBaseController::c_fail = CJsonUtil::genJsonVal("{\"code\":1}");
const Json::Value CBaseController::c_persentError = CJsonUtil::genJsonVal("{\"code\":2}");
const Json::Value CBaseController::c_noLogin = CJsonUtil::genJsonVal("{\"code\":3}");

/*
{
	"code": 0,
	"msg": "XXXX",
	"data": { }
}
*/
Json::Value CBaseController::returnData(CODE code, Json::Value json, string msg)
{
	Json::Value res;
	switch (code)
	{
	case SUCCESS:
		res = c_success;
		break;
	case FAIL:
		res = c_fail;
		break;
	case PE:
		res = c_persentError;
		break;
	default:
		break;
	}
	res["msg"] = Json::Value(msg);
	res["data"] = json;
	return res;
}

bool CBaseController::hasBeenLogin(SOCKET_INFORMATION* socket)
{
	CLMSServerDoc* doc = CMFCUtil::getActiveDoc();
	return doc->m_userSession.isOnLine(socket);
}

bool CBaseController::getUser(SOCKET_INFORMATION* socket, CUser& user)
{
	CLMSServerDoc* doc = CMFCUtil::getActiveDoc();
	return doc->m_userSession.getUser(socket, user);
}

bool CBaseController::sendDataToCliend(const string& url, Json::Value data, const CString& destName)
{
	SOCKET_INFORMATION* sockInfo = getUserSession()->getUserSocketInfo(destName);
	if (sockInfo == NULL)
		return false;
	data["url"] = Json::Value(url);

	return CTCPServer::getInstance()->sendData(sockInfo, data);
}

bool CBaseController::sendDataToClientHavOffline(const string& url, Json::Value data, const CString& destName)
{
	if (!sendDataToCliend(url, data, destName))
	{
		string key = CStringUtil::getStdString(destName);
		Json::Value restoreData = CRedis::get(key);
		data["url"] = Json::Value(url);
		restoreData["data"].append(data);
		CRedis::put(key, restoreData);
		return false;
	}
	return true;
}

bool CBaseController::isCallBack(const Json::Value& data, Json::Value& actData)
{
	if (!data["actID"].isNull())
	{
		string key = data["actID"].asString();
		actData = CRedis::get(key);
		CRedis::del(key);
		return true;
	}
	return false;
}

//==========CUserController=======================

/*
url: /regsit
{
"name": "lk",
"password": "password"
}
{
}
*/
//ע��
Json::Value CUserController::regist(Json::Value json, SOCKET_INFORMATION* socket)
{
	CUser user;
	CString name(json["name"].asCString());
	CString password(json["password"].asCString());
	user.m_userName = name;
	user.m_password = password;

	CUser oldUser;
	if (m_userService.searchPeo(oldUser, name))
		return this->c_fail;
	
	if (m_userService.regist(user))
		return this->c_success;
	return this->c_fail;
}
/*
{
	"userName": "lk",
	"password": "1"
}
{
		"friends": [
			{"name": "n1", "status": 0},
			{"name":"n2", "status": 1}
		] //0Ϊ���ߣ�1����
		"group": ["group1","group2"]
}
*/
Json::Value CUserController::login(Json::Value json, SOCKET_INFORMATION* socket)
{
	CUser user;
	if (CUser::fromJson(json, user))
	{
		if (m_userService.login(user))
		{
			CLMSServerDoc* doc = CMFCUtil::getActiveDoc();
			if (!doc->m_userSession.isOnLine(user))
			{
				doc->m_userSession.bindSocket(user, socket);
				vector<CUser> userList;
				if (!m_userService.getFriends(userList, user))
					return this->c_fail;

				Json::Value res;
				for (int i = 0; i < userList.size(); i++)
				{
					Json::Value friendJson;
					friendJson["name"] = Json::Value(CStringUtil::getStdString(userList[i].m_userName));
					if (getUserSession()->isOnLine(userList[i].m_userName))
					{
						friendJson["status"] = Json::Value(1);
					}
					else
					{
						friendJson["status"] = Json::Value(0);
					}
					res["friends"].append(friendJson);
				}

				vector<CGroup> userGroup;
				m_userService.getUserGroup(userGroup, user.m_userName);
				for (int i = 0; i < userGroup.size(); i++)
				{
					res["group"].append(Json::Value(CStringUtil::getStdString(userGroup[i].m_name)));
				}

				this->notifyFriendOnlineStatus(user);
				::PostMessage(CMFCUtil::getActiveView()->m_centerTabCtrl.m_tabUserPage.m_userListCtrl.m_hWnd
					, WM_NEW_USER, (WPARAM)socket, 0);
				return this->returnData(CODE::SUCCESS, res);
			}
			else
			{
				SOCKET_INFORMATION* sockInfo = getUserSession()->getUserSocketInfo(user);
				if (sockInfo != socket && sockInfo->MessagerSenderSocket == NULL)
				{
					sockInfo->MessagerSenderSocket = socket;
					sendOfflineMsg(user, socket);
					return this->c_notReply;
				}
				return this->c_fail;
			}
		}
	}
	return this->c_fail;
}
/*
url: /friendStatus
{
"name": "lk",
"status": 0 //0Ϊ�����ߣ�1����
}
*/
//֪ͨ�����ѣ����û�������״̬����hostUser��½�͵ǳ�ʱ���ã�
void CUserController::notifyFriendOnlineStatus(const CUser& hostUser, bool onLine)
{
	vector<CUser> userList;
	if (!m_userService.getFriends(userList, hostUser))
		return;
	Json::Value sendJson;
	sendJson["name"] = Json::Value(CStringUtil::getStdString(hostUser.m_userName));
	if (onLine)
	{
		sendJson["status"] = Json::Value(1);
	}
	else
	{
		sendJson["status"] = Json::Value(0);
	}

	for (CUser friendUser : userList)
	{
		this->sendDataToCliend("/friendStatus", sendJson, friendUser.m_userName);
	}
}

/*
url: /offLineData ���ڱ�ʾ����������
���͵����ݸ�ʽ
{
	"url":"/offLineData",
	"data": [{ }, { }]
}
Redis������������json����
key : userName
value:
{
	"data":[
		{ },{ }
	]
}
*/
void CUserController::sendOfflineMsg(const CUser& user, SOCKET_INFORMATION* asyncSocket)
{
	string key = CStringUtil::getStdString(user.m_userName);
	Json::Value val = CRedis::get(key);
	CRedis::del(key);
	if (!val.isNull())
	{
		val["url"] = Json::Value("/offLineData");
		CTCPServer::getInstance()->sendData(asyncSocket, val, true);
	}
}

/*
{
	"name": "lk"
}
{
	"names": ["n1","n2"]
}
*/
Json::Value CUserController::searchPeo(Json::Value json, SOCKET_INFORMATION* socket)
{
	CUser user;
	if (!this->hasBeenLogin(socket))
		return this->c_fail;
	Json::Value namJsonObj = json["name"];
	if (namJsonObj.isNull())
		return this->c_persentError;
	vector<CUser> userList;
	if (!m_userService.searchPeo(userList, CString(namJsonObj.asCString())))
		return this->c_fail;
	
	Json::Value res;
	for (int i = 0; i < userList.size(); i++)
	{
		res["names"].append(CStringUtil::getStdString(userList[i].m_userName));
	}
	return this->returnData(CODE::SUCCESS, res);
}

/*
url: /user/delFriend
{
"name": "lk"
}
*/
//ɾ������
Json::Value CUserController::delFriend(Json::Value json, SOCKET_INFORMATION* socket)
{
	CUser user;
	if (!this->getUser(socket, user))
		return this->c_fail;

	CString friendName(json["name"].asCString());
	if (m_userService.delFriend(user, friendName))
	{
		Json::Value notifyData;
		notifyData["name"] = Json::Value(CStringUtil::getStdString(user.m_userName));
		this->sendDataToCliend("/user/delFriend/notify", notifyData, friendName);
		return this->c_success;
	}
	return this->c_fail;
}

/*
url: /user/addFriend
�����������ݸ�ʽ
{
	"name":"lk"
	"msg":"������Ϣ����֤��Ϣ"
}
���������Ϊ���ϴ�������ѵ���Ӧ������ĸ�ʽ
{
	"actID" : "UUIDxxxx",
	"reply" : 0 //�ܾ������� 1//ͬ�������
	"msg" : "������Ϣ���ܾ�/����ԭ��" 
}
ͬʱ��Redis����ϴ�host�û�������ѵĲ���������Ӧ
url : /user/addFriend/reply
{
	"hostName" : "XXX",
	"friendName": "lk"
	"reply" : 0 //�ܾ������� 1//ͬ�������
	"msg":"������Ϣ���ܾ�/����ԭ��"
}
���Դ�Redis�л�õ�����Ϊ
{
	"hostName" : "XXX",
	"friendName": "lk"
	"msg":"������Ϣ����֤��Ϣ"
}
*/
//��Ӻ���
Json::Value CUserController::addFriend(Json::Value json, SOCKET_INFORMATION* socket)
{
	Json::Value prevData;
	if (isCallBack(json, prevData))
	{
		string actID = json["actID"].asString();
		int reply = json["reply"].asInt();
		CString msg(json["msg"].asCString());

		CString hostName(prevData["hostName"].asCString());
		CString friendName(prevData["friendName"].asCString());
		if (reply == 1)
		{
			if (!m_userService.addFriend(hostName, friendName))
				return this->returnData(CODE::FAIL, Json::Value::null, "���ʧ��");
		}

		Json::Value retJson = prevData;
		retJson["msg"] = json["msg"];
		retJson["reply"] = Json::Value(reply);
		this->sendDataToClientHavOffline("/user/addFriend/reply", retJson, hostName);
		return this->c_success;
	}

	CUser user;
	if (!this->getUser(socket, user))
		return this->c_fail;

	Json::Value nameJson = json["name"];
	Json::Value msgJson = json["msg"];
	CString msg("");
	if (nameJson.isNull())
		return this->c_persentError;
	if (!msgJson.isNull())
		msg = msgJson.asCString();

	CString friName(nameJson.asCString());
	if (friName == user.m_userName)
		return this->returnData(CODE::FAIL, Json::Value::null, "��������Լ�Ϊ����");
	if (m_userService.isHisFriend(user, friName))
		return this->returnData(CODE::FAIL, Json::Value::null, "���Ѿ������ĺ�����");
	if (!sendAddFriendMsgToClien(user.m_userName, friName, msg))
		return this->returnData(CODE::FAIL, Json::Value::null, "��Ӻ���ʧ�ܣ����Ѳ�����");
	return this->returnData(CODE::SUCCESS, Json::Value::null, "��ȴ����ѵĻ�Ӧ");
}

/*
url: /user/addFriend
{
"actID":"UUIDXXXX",
"hostName":"hostUser",
"friendName":"friendName",
"msg":"������Ϣ"
}
*/
//�������ͻ��˷���Ϣ���ύ��������
bool CUserController::sendAddFriendMsgToClien(const CString& userHost, const CString& userFriend, const CString& msg)
{
	Json::Value jsonObj;
	jsonObj["hostName"] = Json::Value(CStringUtil::getStdString(userHost));
	jsonObj["friendName"] = Json::Value(CStringUtil::getStdString(userFriend));
	jsonObj["msg"] = Json::Value(CStringUtil::getStdString(msg));
	string key =  CRedis::put(jsonObj);
	jsonObj["actID"] = Json::Value(key);

	this->sendDataToClientHavOffline("/user/addFriend", jsonObj, userFriend);
	return true;
}

/*
Receive
{
	"name": "lk'sfriend",
	"msg":"XXXXX"
}
Return
{
	
}
DataSend
{
	url : /sendMsgToFriend
	"name":"lk"
	"msg":"XXXX"
}
*/
Json::Value CUserController::sendMsgToFriend(Json::Value json, SOCKET_INFORMATION* socket)
{
	CUser user;
	if (!this->getUser(socket, user))
	{
		return this->returnData(CODE::FAIL, Json::Value::null, "δ��¼");
	}
	vector<CUser> userFriList;
	if (!m_userService.getFriends(userFriList, user))
		return false;

	CString friName(json["name"].asCString());
	CString msg(json["msg"].asCString());
	Json::Value dataSend = json;
	dataSend["name"] = Json::Value(CStringUtil::getStdString(user.m_userName));
	for (auto u : userFriList)
	{
		if (u.m_userName == friName)
		{
			if (this->sendDataToClientHavOffline("/sendMsgToFriend", dataSend, friName))
				return this->returnData(CODE::SUCCESS);

			return this->c_success;
		}
	}
	return this->returnData(CODE::FAIL, Json::Value::null, "�޴˺���");
}

/*
url: /sendMsgToGroup
���ܵ�����
{
"name": "lk'sGroup",
"msg":"XXXXX"
}
*/
Json::Value CUserController::sendMsgToGroup(Json::Value json, SOCKET_INFORMATION* socket)
{
	CUser user;
	if (!this->getUser(socket, user))
	{
		return this->returnData(CODE::FAIL, Json::Value::null, "δ��¼");
	}

	CString groupName(json["name"].asCString());
	CString msg(json["msg"].asCString());

	Json::Value sendJson;
	sendJson["sendUser"] = Json::Value(CStringUtil::getStdString(user.m_userName));
	sendJson["group"] = json["name"];
	sendJson["msg"] = json["msg"];
	
	vector<string> userList;
	m_userService.getGroupUser(userList, groupName);
	string nowUserStringName = CStringUtil::getStdString(user.m_userName);
	for (auto userName : userList)
	{
		if (userName != nowUserStringName)
			this->sendDataToCliend("/groupMsg", sendJson, CStringUtil::getCString(userName));
	}
	return this->c_success;
}

/*
url: /searchGroup
{
"name": "groupName"
}
*/
Json::Value CUserController::searchGroup(Json::Value json, SOCKET_INFORMATION* socket)
{
	CString groupName(json["name"].asCString());

	vector<CGroup> groupList;
	if (m_userService.searchGroup(groupList, groupName))
	{
		Json::Value resJson;
		for (int i = 0; i < groupList.size(); i++)
		{
			resJson["names"].append(Json::Value(CStringUtil::getStdString(groupList[i].m_name)));
		}
		return this->returnData(CODE::SUCCESS, resJson);
	}
	return this->c_fail;
}

/*
url: /joinGroup
{
"name": "groupName"
}
*/
Json::Value CUserController::joinGroup(Json::Value json, SOCKET_INFORMATION* socket)
{
	CUser user;
	if (!this->getUser(socket, user))
	{
		return this->returnData(CODE::FAIL, Json::Value::null, "δ��¼");
	}

	CString groupName(json["name"].asCString());
	if (m_userService.isInGroup(user, groupName))
		return this->returnData(CODE::FAIL, Json::Value::null, "�����ڴ�Ⱥ��");

	if (m_userService.joinGroup(user, groupName))
	{
		CString* pName = new CString(groupName);
		::PostMessage(CMFCUtil::getActiveView()->m_centerTabCtrl.m_tabGroupPage.m_groupListCtrl.m_hWnd,
			WM_UPDAT_GROUP_NUM, (WPARAM)pName, 0);
		return this->c_success;
	}
	return this->c_fail;
}

/*
url: /quitGroup
{
"name": "groupName"
}
*/
Json::Value CUserController::quitGroup(Json::Value json, SOCKET_INFORMATION* socket)
{
	CUser user;
	if (!this->getUser(socket, user))
	{
		return this->returnData(CODE::FAIL, Json::Value::null, "δ��¼");
	}

	CString groupName(json["name"].asCString());
	if (m_userService.quitGroup(user, groupName))
	{
		CString* pName = new CString(groupName);
		::PostMessage(CMFCUtil::getActiveView()->m_centerTabCtrl.m_tabGroupPage.m_groupListCtrl.m_hWnd,
			WM_UPDAT_GROUP_NUM, (WPARAM)pName, 1);
		return this->c_success;
	}
	return this->returnData(CODE::FAIL, Json::Value::null, "�˳�ʧ��");
}

/*
url: /getUserStatus
{
"name":"lk"
}
{
"status":0  //0Ϊ�����ߣ�1����
}
*/
//����û�״̬���Ƿ����ߣ�
Json::Value CUserController::getUserStatus(Json::Value json, SOCKET_INFORMATION* socket)
{
	CString userName(json["name"].asCString());

	Json::Value reJson;
	if (getUserSession()->isOnLine(userName))
	{
		reJson["status"] = Json::Value(1);
		return this->returnData(CODE::SUCCESS, reJson);
	}
	else
	{
		reJson["status"] = Json::Value(0);
		return this->returnData(CODE::SUCCESS, reJson);
	}
}

bool CUserController::broadCast(const CString& msg)
{
	vector<CUser> userList;
	getUserSession()->getUser(userList);

	Json::Value sendData;
	sendData["msg"] = Json::Value(CStringUtil::getStdString(msg));

	for (int i = 0; i < userList.size(); i++)
	{
		this->sendDataToCliend("/broadCast", sendData, userList[i].m_userName);
	}
	return true;
}