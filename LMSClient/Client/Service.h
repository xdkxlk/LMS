#pragma once
#include "Model.h"
#include "json.h"
#include <string>
#include <vector>

using namespace std;

class CBaseService
{
public:
	enum CODE{
		SUCCESS, FAIL, PE
	};

	CBaseService();
	~CBaseService();
	
	static CODE getCode(const string& json);
	static string getMsg(const string& json);
	static Json::Value getData(const string& json);
	static bool sendData(const string& url, Json::Value data, string& resData);
};

//=======================CUserService===========

class CUserService : public CBaseService
{
public:
	CUserService();
	~CUserService();

	//注册
	bool regist(const CString& name, const CString& pass);
	//登陆
	bool login(CString name, CString pass, CUser& user);
	//向朋友发消息
	bool sendMsgToFri(const CString& friendName,const CString& msg, CString* retMsg);
	//向群发消息
	bool sendMsgToGroup(const CString& groupNamw, const CString& msg, CString* retMsg);
	//收盆友消息
	bool getMsgFromFri(string json);
	//收到群组消息
	bool getMsgFromGroup(const Json::Value& json);
	//添加盆友
	bool addFriend(const CString& friendName,const CString& msg,  CString& retMsg);
	//删除盆友
	bool delFriend(const CString& friendName, CString& retMsg);
	//处理远端有人删除了好友关系
	void resolveDelFriendNotify(const Json::Value& json);
	//搜索盆友
	bool searchFriend(const CString& friendName, vector<CString>& friList, CString& retMsg);
	//搜索群组
	bool searchGroup(const CString& groupName, vector<CString>& gList, CString& retMsg);
	//加入群组
	bool joinGroup(const CString& groupName, CString& retMsg);
	//退出群组
	bool quitGroup(const CString& groupName, CString& retMsg);
	//弹窗添加盆友的请求
	void replyAddFriend(const Json::Value& json);
	//向服务器回应添加盆友的请求
	void sendDataReplyAddFriend(const Json::Value& json, bool accept = true);
	//处理添加盆友的服务端的异步响应
	void resolveDataReplyAddFriend(const Json::Value& json);
	//接受处理好友状态信息（上线/下线）
	void updateFriendStatus(const Json::Value& json);
	//查询用户状态
	int getUserStatus(const CString& userName);
	//响应广播
	bool getBroadcast(const Json::Value& json);
};