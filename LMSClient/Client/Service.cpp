#include "stdafx.h"
#include "Service.h"
#include "JsonUtil.h"
#include "TCPClient.h"
#include "MFCUtil.h"
#include "StringUtil.h"
#include "ConstFile.h"
#include "DialgUserAddFriendReply.h"
#include "DialgUserAddFriendResult.h"

CBaseService::CBaseService()
{
}


CBaseService::~CBaseService()
{
}

CBaseService::CODE CBaseService::getCode(const string& json)
{
	Json::Value jsonObj;
	CJsonUtil::genJsonVal(json, jsonObj);
	CODE code = (CODE)jsonObj["code"].asInt();
	return code;
}

string CBaseService::getMsg(const string& json)
{
	Json::Value jsonObj;
	CJsonUtil::genJsonVal(json, jsonObj);
	return jsonObj["msg"].asString();
}

Json::Value CBaseService::getData(const string& json)
{
	Json::Value jsonObj;
	CJsonUtil::genJsonVal(json, jsonObj);
	return jsonObj["data"];
}

bool CBaseService::sendData(const string& url, Json::Value data, string& resData)
{
	data["url"] = Json::Value(url);

	return CTCPSender::sendData(CJsonUtil::toString(data), resData);
}

//===========CUserService====================
CUserService::CUserService()
{
}


CUserService::~CUserService()
{
}

/*
收到的数据格式
{
"friends": [
	{"name": "n1", "status": 0},
	{"name":"n2", "status": 1}
	] //0为在线，1在线
	"group": ["group1","group2"]
}
*/
bool CUserService::login(CString name, CString pass, CUser& user)
{
	CUser temp;
	temp.m_userName = name;
	temp.m_password = pass;

	string resData;
	if (!this->sendData("/login", temp.getJson(), resData))
		return false;

	if (this->getCode(resData) != CODE::SUCCESS)
		return false;

	Json::Value jsonObj;
	CJsonUtil::genJsonVal(resData, jsonObj);
	jsonObj = jsonObj["data"];

	user.m_userName = name;
	user.m_password = pass;
	Json::Value friendJsonArray = jsonObj["friends"];
	for (int i = 0; i < friendJsonArray.size(); i++)
	{
		CFriend* fri = new CFriend();
		fri->m_userName = CString(friendJsonArray[i]["name"].asCString());
		fri->m_status = friendJsonArray[i]["status"].asInt();

		user.addFriend(fri);
	}

	Json::Value groupJsonArray = jsonObj["group"];
	for (int i = 0; i < groupJsonArray.size(); i++)
	{
		CGroup* g = new CGroup();
		g->m_name = CString(groupJsonArray[i].asCString());

		user.addGroup(g);
	}

	return true;
}

//发送消息到朋友
bool CUserService::sendMsgToFri(const CString& friendName, const CString& msg, CString* retMsg)
{
	Json::Value jsonObj;

	jsonObj["name"] = Json::Value(CStringUtil::getStdString(friendName));
	jsonObj["msg"] = Json::Value(CStringUtil::getStdString(msg));
	string retStr;

	if (!this->sendData("/sendMsgToFriend", jsonObj, retStr))
	{
		retMsg->Format(_T("发送失败请检查网络"));
		return false;
	}
	if (this->getCode(retStr) != CODE::SUCCESS)
	{
		string t = getMsg(retStr);
		(*retMsg) = CStringUtil::getCString(t);
		return false;
	}

	CMFCUtil::getActiveDoc()->updateFriendHtml(friendName, msg, false);
	CMFCUtil::getActiveView()->flushChat();
	return true;
}

bool CUserService::sendMsgToGroup(const CString& groupNamw, const CString& msg, CString* retMsg)
{
	const CUser& u = CMFCUtil::getActiveDoc()->m_user;
	Json::Value jsonObj;

	jsonObj["name"] = Json::Value(CStringUtil::getStdString(groupNamw));
	jsonObj["msg"] = Json::Value(CStringUtil::getStdString(msg));
	string retStr;

	if (!this->sendData("/sendMsgToGroup", jsonObj, retStr))
	{
		retMsg->Format(_T("发送失败请检查网络"));
		return false;
	}
	if (this->getCode(retStr) != CODE::SUCCESS)
	{
		string t = getMsg(retStr);
		(*retMsg) = CStringUtil::getCString(t);
		return false;
	}

	CMFCUtil::getActiveDoc()->updateGroupHtml(groupNamw, u.m_userName, msg, false);
	CMFCUtil::getActiveView()->flushChat();
	return true;
}

/*
DataSend
{
	"name":"lk"
	"msg" : "XXXX"
}*/
//收到朋友消息
bool CUserService::getMsgFromFri(string json)
{
	Json::Value jsonObj;
	if (!CJsonUtil::genJsonVal(json, jsonObj))
		return false;

	CString friName(jsonObj["name"].asCString());
	CString msg(jsonObj["msg"].asCString());

	if (!CMFCUtil::getActiveDoc()->isFriend(friName))
		return false;

	CFriend* fri = CMFCUtil::getActiveDoc()->getFriend(friName);
	fri->m_msgNum++;

	::PostMessage(CMFCUtil::getMainFrame()->m_wndClassView.m_wndListCtrl.m_hWnd, WM_UPDAT_FRIEND_STATUS,
		(WPARAM)fri, NULL);

	CMFCUtil::getActiveDoc()->updateFriendHtml(friName, msg);
	CMFCUtil::getActiveView()->flushChat();

	return true;
}

/*
sendJson["sendUser"] = Json::Value(CStringUtil::getStdString(user.m_userName));
sendJson["group"] = json["name"];
sendJson["msg"] = json["msg"];
*/
bool CUserService::getMsgFromGroup(const Json::Value& json)
{
	CString sendUser(json["sendUser"].asCString());
	CString group(json["group"].asCString());
	CString msg(json["msg"].asCString());

	CMFCUtil::getActiveDoc()->updateGroupHtml(group, sendUser, msg);
	CMFCUtil::getActiveView()->flushChat();

	return true;
}

void CUserService::resolveDelFriendNotify(const Json::Value& json)
{
	CString* friendName = new CString(json["name"].asCString());

	::PostMessage(CMFCUtil::getActiveView()->m_hWnd, WM_DEL_FRIEND_BACKGROUND,
		(WPARAM)friendName, NULL);
}

bool CUserService::delFriend(const CString& friendName, CString& retMsg)
{
	Json::Value sendJson;
	sendJson["name"] = Json::Value(CStringUtil::getStdString(friendName));

	string retStr;
	if (!this->sendData("/user/delFriend", sendJson, retStr))
	{
		retMsg.Format(_T("请求失败请检查网络"));
		return false;
	}
	string t = getMsg(retStr);
	retMsg = CStringUtil::getCString(t);

	if (this->getCode(retStr) != CODE::SUCCESS)
		return false;

	CMFCUtil::getActiveDoc()->delFriend(CMFCUtil::getActiveDoc()->getFriend(friendName));
	return true;
}

bool CUserService::addFriend(const CString& friendName, const CString& msg, CString& retMsg)
{
	Json::Value sendJson;
	sendJson["name"] = Json::Value(CStringUtil::getStdString(friendName));
	sendJson["msg"] = Json::Value(CStringUtil::getStdString(msg));

	string retStr;
	if (!this->sendData("/user/addFriend", sendJson, retStr))
	{
		retMsg.Format(_T("发送失败请检查网络"));
		return false;
	}

	string t = getMsg(retStr);
	retMsg = CStringUtil::getCString(t);

	if (this->getCode(retStr) != CODE::SUCCESS)
		return false;
	return true;
}

bool CUserService::searchFriend(const CString& friendName, vector<CString>& friList, CString& retMsg)
{
	Json::Value sendJson;
	sendJson["name"] = Json::Value(CStringUtil::getStdString(friendName));

	string retStr;
	if (!this->sendData("/user/searchPeo", sendJson, retStr))
	{
		retMsg.Format(_T("发送失败请检查网络"));
		return false;
	}
	if (this->getCode(retStr) != CODE::SUCCESS)
	{
		string t = getMsg(retStr);
		retMsg = CStringUtil::getCString(t);
		return false;
	}

	Json::Value retJson = this->getData(retStr);
	Json::Value namesJsonArray = retJson["names"];
	for (int i = 0; i < namesJsonArray.size(); i++)
	{
		CString freNamesData(namesJsonArray[i].asCString());
		friList.push_back(freNamesData);
	}
	return true;
}

/*
{
"actID":"UUIDXXXX",
"hostName":"hostUser",
"friendName":"friendName",
"msg":"附加信息"
}
*/
void CUserService::replyAddFriend(const Json::Value& json)
{
	CString hostName(json["hostName"].asCString());
	CString friendName(json["friendName"].asCString());
	CString msg(json["msg"].asCString());

	CDialgUserAddFriendReply dialg(hostName, msg, json);
	dialg.DoModal();
}
/*
url : /user/addFriend
{
"actID":"UUIDXXXX",
"hostName":"hostUser",
"friendName":"friendName",
"msg":"附加信息"
}
{
	"actID" : "UUIDxxxx",
		"reply" : 0 //拒绝加朋友 1//同意加朋友
		"msg" : "附加信息"
}*/
void CUserService::sendDataReplyAddFriend(const Json::Value& json, bool accept)
{
	Json::Value dataJson;
	dataJson["actID"] = json["actID"];
	dataJson["msg"] = json["msg"];
	if (accept)
		dataJson["reply"] = Json::Value(1);
	else
		dataJson["reply"] = Json::Value(0);

	string retStr;
	if (!this->sendData("/user/addFriend", dataJson, retStr))
	{
		return;
	}
	if (this->getCode(retStr) == CODE::SUCCESS && accept)
	{
		CFriend* fri = new CFriend();
		fri->m_userName = CString(json["hostName"].asCString());
		fri->m_status = getUserStatus(fri->m_userName);
		CMFCUtil::getActiveDoc()->addFriend(fri);

		::PostMessage(CMFCUtil::getMainFrame()->m_wndClassView.m_wndListCtrl.m_hWnd, WM_NEW_FRIEND_ADDED,
			(WPARAM)fri, NULL);
		return;
	}
}

/*
url : /user/addFriend/reply
{
"hostName" : "XXX",
"friendName": "lk"
"reply" : 0 //拒绝加朋友 1//同意加朋友
"msg":"附加信息，拒绝/接受原因"
}
*/
void CUserService::resolveDataReplyAddFriend(const Json::Value& json)
{
	CString hostName(json["hostName"].asCString());
	CString friendName(json["friendName"].asCString());
	CString msg(json["msg"].asCString());
	int reply = json["reply"].asInt();

	CString tip = friendName;
	if (reply == 1)
	{
		tip += CString("接受了");

		CFriend* fri = new CFriend();
		fri->m_userName = friendName;
		fri->m_status = getUserStatus(fri->m_userName);
		CMFCUtil::getActiveDoc()->addFriend(fri);
		::PostMessage(CMFCUtil::getMainFrame()->m_wndClassView.m_wndListCtrl.m_hWnd, WM_NEW_FRIEND_ADDED,
			(WPARAM)fri, NULL);
	}
	else
	{
		tip += CString("拒绝了");
	}
	tip += CString("您添加好友的请求");

	CDialgUserAddFriendResult dialg(tip, msg);
	dialg.DoModal();
}

/*
url: /friendStatus
{
"name": "lk",
"status": 0 //0为不在线，1在线
}
*/
void CUserService::updateFriendStatus(const Json::Value& json)
{
	CString friendName(json["name"].asCString());
	int status = json["status"].asInt();

	CFriend* fri = CMFCUtil::getActiveDoc()->getFriend(friendName);
	if (fri == NULL)
		return;
	fri->m_status = status;

	::PostMessage(CMFCUtil::getMainFrame()->m_wndClassView.m_wndListCtrl.m_hWnd, WM_UPDAT_FRIEND_STATUS,
		(WPARAM)fri, NULL);
}

//搜索群组
bool CUserService::searchGroup(const CString& groupName, vector<CString>& gList, CString& retMsg)
{
	Json::Value dataJson;
	dataJson["name"] = Json::Value(CStringUtil::getStdString(groupName));

	string retStr;
	if (!this->sendData("/searchGroup", dataJson, retStr))
	{
		return false;
	}

	if (this->getCode(retStr) == CODE::SUCCESS)
	{
		Json::Value retJson = this->getData(retStr);
		Json::Value namesJsonArray = retJson["names"];
		for (int i = 0; i < namesJsonArray.size(); i++)
		{
			CString names(namesJsonArray[i].asCString());
			gList.push_back(names);
		}
		return true;
	}
	return false;
}

/*
url: /joinGroup
{
"name": "groupName"
}
*/
bool CUserService::joinGroup(const CString& groupName, CString& retMsg)
{
	Json::Value sendJson;
	sendJson["name"] = Json::Value(CStringUtil::getStdString(groupName));

	string retStr;
	if (!this->sendData("/joinGroup", sendJson, retStr))
	{
		retMsg.Format(_T("发送失败请检查网络"));
		return false;
	}

	string t = getMsg(retStr);
	retMsg = CStringUtil::getCString(t);

	if (this->getCode(retStr) != CODE::SUCCESS)
		return false;

	CGroup* g = new CGroup();
	g->m_name = groupName;
	CMFCUtil::getActiveDoc()->addGroup(g);
	CMFCUtil::getMainFrame()->m_wndFileView.m_wndGroupView.addGroup(g);
	return true;
}

/*
url: /quitGroup
{
"name": "groupName"
}
*/
bool CUserService::quitGroup(const CString& groupName, CString& retMsg)
{
	Json::Value sendJson;
	sendJson["name"] = Json::Value(CStringUtil::getStdString(groupName));

	string retStr;
	if (!this->sendData("/quitGroup", sendJson, retStr))
	{
		retMsg.Format(_T("请求失败请检查网络"));
		return false;
	}
	string t = getMsg(retStr);
	retMsg = CStringUtil::getCString(t);

	if (this->getCode(retStr) != CODE::SUCCESS)
		return false;

	CMFCUtil::getActiveDoc()->delGroup(CMFCUtil::getActiveDoc()->getGroup(groupName));
	return true;
}

/*
url: /getUserStatus
{
"name":"lk"
}
{
"status":0  //0为不在线，1在线
}
*/
//获得用户状态（是否在线）
int CUserService::getUserStatus(const CString& userName)
{
	Json::Value sendJson;
	sendJson["name"] = Json::Value(CStringUtil::getStdString(userName));

	string retStr;
	if (!this->sendData("/getUserStatus", sendJson, retStr))
	{
		return 0;
	}

	if (this->getCode(retStr) != CODE::SUCCESS)
		return 0;

	Json::Value data = this->getData(retStr);
	return data["status"].asInt();
}

/*
url: /broadCast
{
"msg" : "message"
}
*/
bool CUserService::getBroadcast(const Json::Value& json)
{
	CString msg(json["msg"].asCString());

	AfxMessageBox(msg.AllocSysString());
	return true;
}

bool CUserService::regist(const CString& name, const CString& pass)
{
	Json::Value sendData;
	sendData["name"] = Json::Value(CStringUtil::getStdString(name));
	sendData["password"] = Json::Value(CStringUtil::getStdString(pass));

	string retStr;
	if (!this->sendData("/regist", sendData, retStr))
	{
		return 0;
	}

	if (this->getCode(retStr) == CODE::SUCCESS)
		return true;

	return false;
}