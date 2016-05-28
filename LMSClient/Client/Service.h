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

	//ע��
	bool regist(const CString& name, const CString& pass);
	//��½
	bool login(CString name, CString pass, CUser& user);
	//�����ѷ���Ϣ
	bool sendMsgToFri(const CString& friendName,const CString& msg, CString* retMsg);
	//��Ⱥ����Ϣ
	bool sendMsgToGroup(const CString& groupNamw, const CString& msg, CString* retMsg);
	//��������Ϣ
	bool getMsgFromFri(string json);
	//�յ�Ⱥ����Ϣ
	bool getMsgFromGroup(const Json::Value& json);
	//�������
	bool addFriend(const CString& friendName,const CString& msg,  CString& retMsg);
	//ɾ������
	bool delFriend(const CString& friendName, CString& retMsg);
	//����Զ������ɾ���˺��ѹ�ϵ
	void resolveDelFriendNotify(const Json::Value& json);
	//��������
	bool searchFriend(const CString& friendName, vector<CString>& friList, CString& retMsg);
	//����Ⱥ��
	bool searchGroup(const CString& groupName, vector<CString>& gList, CString& retMsg);
	//����Ⱥ��
	bool joinGroup(const CString& groupName, CString& retMsg);
	//�˳�Ⱥ��
	bool quitGroup(const CString& groupName, CString& retMsg);
	//����������ѵ�����
	void replyAddFriend(const Json::Value& json);
	//���������Ӧ������ѵ�����
	void sendDataReplyAddFriend(const Json::Value& json, bool accept = true);
	//����������ѵķ���˵��첽��Ӧ
	void resolveDataReplyAddFriend(const Json::Value& json);
	//���ܴ������״̬��Ϣ������/���ߣ�
	void updateFriendStatus(const Json::Value& json);
	//��ѯ�û�״̬
	int getUserStatus(const CString& userName);
	//��Ӧ�㲥
	bool getBroadcast(const Json::Value& json);
};