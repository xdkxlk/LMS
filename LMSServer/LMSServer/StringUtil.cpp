#include "stdafx.h"
#include "StringUtil.h"
#include <regex>
#include <string.h>
#include <sstream>

using namespace std;

CStringUtil::CStringUtil()
{
}


CStringUtil::~CStringUtil()
{
}

std::string CStringUtil::getStdString(CString str)
{
	CStringW strw = str.Trim();
	CStringA stra(strw.GetBuffer(0));
	strw.ReleaseBuffer();
	std::string data = stra.GetBuffer(0);
	stra.ReleaseBuffer();

	return data;
}

CString CStringUtil::getCString(std::string str)
{
	return CString(str.c_str());
}

bool CStringUtil::strMatch(CString str, std::string regex)
{
	const std::regex pattern(regex);

	bool match = std::regex_match(CStringUtil::getStdString(str), pattern);

	return match;
}

int CStringUtil::toInt(const string& str)
{
	return atoi(str.c_str());
}

string CStringUtil::fromNum(int num)
{
	stringstream stream;
	stream << num;

	string str;
	stream >> str;
	return str;
}

LPCTSTR CStringUtil::getLPSTR(const char * str)
{
	int num = MultiByteToWideChar(0, 0, str, -1, NULL, 0);
	wchar_t *wide = new wchar_t[num];
	MultiByteToWideChar(0, 0, str, -1, wide, num);

	return wide;
}