#pragma once
#include "json.h"
#include "Model.h"
#include "Service.h"
#include <WinSock2.h>
#include <string>
#include "ConstFile.h"

// �����׽�����Ϣ
class SOCKET_INFORMATION
{
public:
	CHAR Buffer[2048];				// ���ͺͽ������ݵ��׽���
	WSABUF DataBuf;								// �������ݵ����ݺͳ���
	SOCKET Socket;				//ͬ���׽��֣����ڽ��ܿͻ�������һ����һ��Ӧ
	SOCKADDR_IN Addr;
	SOCKET_INFORMATION *MessagerSenderSocket;	//ָ������һ��SOCKET_INFORMATION���˽ṹ���ڷ����������ͻ��˷�������
	SOCKET_INFORMATION *Next;		// ��һ���׽�����Ϣ
};
//=========================================================

class CBaseController
{
public:
	enum CODE{
		SUCCESS, FAIL, PE, NOLOGIN
	};

	//�ж��Ƿ��Ѿ���½
	static bool hasBeenLogin(SOCKET_INFORMATION* socket);
	//��ô�UserSession��user
	static bool getUser(SOCKET_INFORMATION* socket, CUser& user);
	/*
	���з���ֵͨ���˷����ӹ������ո�ʽ
	{
		"code": 0,
		"msg": "XXXX",
		"data": { } //data����Ϊʵ�ʵ�����
	}
	*/
	//�������ݣ�code״̬��msg������Ϣ
	static Json::Value returnData(CODE code, Json::Value json = Json::Value::null, string msg = "");
	//�����������ݸ��ͻ���
	bool sendDataToCliend(const string& url, Json::Value data, const CString& destName);
	//�����������ݸ��ͻ��ˣ���������ߣ��򱣴���Redis�У����´οͻ�����ʱ����
	bool sendDataToClientHavOffline(const string& url, Json::Value data, const CString& destName);
	//�ж��Ƿ�Ϊ�������͸��ͻ��˵�����Ŀͻ��˵���Ӧ���ж��Ƿ���� actID����ǰ������actData������CRedis�У�
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
	//ע��
	Json::Value regist(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url : /login
	���ܵ�����
	{
		"userName": "lk",
		"password": "1"
	}
	���ص�����
	{
		"friends": [
			{"n1", 0},{"n2",1}
		] //0Ϊ�����ߣ�1����
		"group": ["group1","group2"]
	}
	*/
	//����1����½��
	//����2���󶨿ͻ�����Ϣ����socket����������������֤�ͻ�����ݣ����ͬ��ͨ��Scoket�Ѿ����ڣ�����ΪΪ�첽Socket�󶨣�
	Json::Value login(Json::Value json, SOCKET_INFORMATION* socket);
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
	Json::Value getUserStatus(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /broadCast
	{
	"msg" : "message"
	}
	*/
	//�㲥
	bool broadCast(const CString& msg);
	/*
	url: /friendStatus
	{
		"name": "lk",
		"status": 0 //0Ϊ�����ߣ�1����
	}
	*/
	//֪ͨ�����ѣ����û�������״̬����hostUser��½�͵ǳ�ʱ���ã�
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
	//�û��������Ӻ��ѣ�ģ����ѯ�����ߺ��ѣ�
	Json::Value searchPeo(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /user/addFriend
	{
		"name":"lk"
	}
	{
		
	}
	*/
	//��Ӻ���
	Json::Value addFriend(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /user/delFriend
	{
		"name": "lk"
	}
	*/
	//ɾ������
	Json::Value delFriend(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /sendMsgToFriend
	���ܵ�����
	{
	"name": "lk'sfriend",
	"msg":"XXXXX"
	}
	���ص�����
	{

	}
	*/
	//������Ϣ������
	Json::Value sendMsgToFriend(Json::Value json, SOCKET_INFORMATION* socket);
	/*
	url: /sendMsgToGroup
	���ܵ�����
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
	//�������ͻ��˷���Ϣ���ύ��������
	bool sendAddFriendMsgToClien(const CString& userHost, const CString& userFriend, const CString& msg);
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
	//���ʹ��û����������ݣ�ǰ�⣬�ͻ��˵��첽��Ϣ���Ѿ����ӣ�
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
	//ǿ���û�����
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
	SOCKET_INFORMATION* SocketInfoList;	// �����׽�����Ϣ���б�
	WSADATA m_ws;

private:
	Json::Value dataResolve(const std::string& data, SOCKET_INFORMATION* socket);

	CUserController m_userController;
};