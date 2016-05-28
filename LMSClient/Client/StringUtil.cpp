#include "stdafx.h"
#include "StringUtil.h"
#include <regex>

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