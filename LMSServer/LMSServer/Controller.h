#pragma once
#include "json.h"
#include "Model.h"
#include "Service.h"
#include <WinSock2.h>
#include <string>
#include "ConstFile.h"

// 保存套接字信息
class SOCKET_INFORMATION
{
public:
	CHAR Buffer[2048];				// 发送和接收数据的套接字
	WSABUF DataBuf;								// 定义数据的内容和长度
	SOCKET Socket;				//同步套接字，用于接受客户端请求，一发送一响应
	SOCKADDR_IN Addr;
	SOCKET_INFORMATION *MessagerSenderSocket;	//指想另外一个SOCKET_INFORMATION，此结构用于服务端主动向客户端发送数据
	SOCKET_INFORMATION *Next;		// 向一个套接字信息
};
//=========================================================

class CBaseController
{
public:
	enum CODE{
		SUCCESS, FAIL, PE, NOLOGIN
	};

	//判断是否已经登陆
	static bool hasBeenLogin(SOCKET_INFORMATION* socket);
	//获得从UserSession中user
	static bool getUser(SOCKET_INFORMATION* socket, CUser& user);
	/*
	所有返回值通过此方法加工，最终格式
	{
		"code": 0,
		"msg": "XXXX",
		"data": { } //data里面为实际的数据
	}
	*/
	//返回数据，code状态，msg附加信息
	static Json::Value returnData(CODE code, Json::Value json = Json::Value::null, string msg = "");
	//主动发送数据给客户端
	bool sendDataToCliend(const string& url, Json::Value data, const CString& destName);
	//主动发送数据给客户端，如果不在线，则保存在Redis中，再下次客户上线时发送
	bool sendDataToClientHavOffline(const string& url, Json::Value data, const CString& destName);
	//判断是否为主动发送给客户端的请求的客户端的响应（判断是否包含 actID，以前的数据actData保存在CRedis中）
	bool isCallBack(const Json::Value& data, Json::Value& actData);

	static  const Json::Value c_fail;
	static  const Json::Value c_success;
	static  const Json::Value c_persentError;
	static  const Json::Value c_noLogin;
	static  const Json::Value c_notReply;
};

//==========CUserController=======================
class CUserController : public CBaseController
{
public:
	/*
	url: /regsit
	{
	"name": "lk",
	"password": "password"
	}
	{
	}
	*/
	//注册
	Json::Value regist(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url : /login
	接受的数据
	{
		"userName": "lk",
		"password": "1"
	}
	返回的数据
	{
		"friends": [
			{"n1", 0},{"n2",1}
		] //0为不在线，1在线
		"group": ["group1","group2"]
	}
	*/
	//功能1：登陆。
	//功能2：绑定客户端消息接收socket（但这两个都会验证客户端身份，如果同步通信Scoket已经存在，则认为为异步Socket绑定）
	Json::Value login(Json::Value json, SOCKET_INFORMATION* socket);
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
	Json::Value getUserStatus(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /broadCast
	{
	"msg" : "message"
	}
	*/
	//广播
	bool broadCast(const CString& msg);
	/*
	url: /friendStatus
	{
		"name": "lk",
		"status": 0 //0为不在线，1在线
	}
	*/
	//通知其朋友，此用户的在线状态（在hostUser登陆和登出时调用）
	void notifyFriendOnlineStatus(const CUser& hostUser, bool onLine = true);
	/*
	url: /user/searchPeo
	{
		"name": "lk"
	}
	{
		"names": ["n1","n2"]
	}
	*/
	//用户搜索（加好友，模糊查询，在线好友）
	Json::Value searchPeo(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /user/addFriend
	{
		"name":"lk"
	}
	{
		
	}
	*/
	//添加好友
	Json::Value addFriend(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /user/delFriend
	{
		"name": "lk"
	}
	*/
	//删除好友
	Json::Value delFriend(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /sendMsgToFriend
	接受的数据
	{
	"name": "lk'sfriend",
	"msg":"XXXXX"
	}
	返回的数据
	{

	}
	*/
	//发送消息给好友
	Json::Value sendMsgToFriend(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /sendMsgToGroup
	接受的数据
	{
	"name": "lk'sGroup",
	"msg":"XXXXX"
	}
	*/
	Json::Value sendMsgToGroup(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /searchGroup
	{
	"name": "groupName"
	}
	{
	"names": ["g1","g2"]
	}
	*/
	Json::Value searchGroup(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /joinGroup
	{
	"name": "groupName"
	}
	*/
	Json::Value joinGroup(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /quitGroup
	{
	"name": "groupName"
	}
	*/
	Json::Value quitGroup(Json::Value json, SOCKET_INFORMATION* socket);
private:
	/*
	url: /user/addFriend
	{
		"actID":"UUIDXXXX"
		"name":"hostUser"
	}
	*/
	//主动给客户端发消息，提交好友请求
	bool sendAddFriendMsgToClien(const CString& userHost, const CString& userFriend, const CString& msg);
	/*
	url: /offLineData 用于表示是离线数据
	发送的数据格式
	{
	"url":"/offLineData",
	"data": [{ }, { }]
	}
	Redis中离线数据以json保存
	key : userName
	value:
	{
	"data":[
	{ },{ }
	]
	}
	*/
	//发送此用户的离线数据（前题，客户端的异步消息端已经连接）
	void sendOfflineMsg(const CUser& user, SOCKET_INFORMATION* asyncSocket);

	CUserService m_userService;
};

//===========================================================
class CTCPServer : public CWnd
{
public:
	CTCPServer();
	~CTCPServer();
	static CTCPServer* getInstance();
	void startServer();
	//强制用户下线
	void forceOffLine(const CString& userName);
	bool sendData(SOCKET_INFORMATION* sockInfo, Json::Value data, bool socketIsMsgSender = false);
	LRESULT OnSocket(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
protected:

public:
	void initEnviornment();
	void cleanEnviornment();
	void DelSocketInformation(SOCKET_INFORMATION* info);
	void CreateSocketInformation(SOCKET s, SOCKADDR_IN addr);
	void FreeAll();
	SOCKET_INFORMATION* GetSocketInformation(SOCKET s);

	const int BACKLOG = 5;
	const int PORT = 8080;
	const int MAXDATASIZE = 2048;

	SOCKET m_severScoket;
	SOCKADDR_IN my_addr;
	SOCKET_INFORMATION* SocketInfoList;	// 所有套接字信息的列表
	WSADATA m_ws;

private:
	Json::Value dataResolve(const std::string& data, SOCKET_INFORMATION* socket);

	CUserController m_userController;
};