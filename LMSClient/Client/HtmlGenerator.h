#pragma once
#include <vector>

using namespace std;

class CHtmlData
{
public:
	enum HTMLDATATYPE{
		OTHER, USER
	};
	HTMLDATATYPE m_type;
	CString m_name;
	CString m_message;
	CTime m_time;
};

class CHtmlGenerator
{
public:
	CHtmlGenerator();
	~CHtmlGenerator();

	void flush(IHTMLDocument2* document);
	void addMsg(const CString& name, const CString& msg, CHtmlData::HTMLDATATYPE type);

public:
	CString m_htmlBuff;
	vector<CHtmlData> m_htmlData;

	static const CString c_bodyHead;
	static const CString c_buttom;
	static const CString c_head;
private:
	CString getHtml();
};