#pragma once
#include <string>

class CStringUtil
{
public:
	CStringUtil();
	~CStringUtil();

	static std::string getStdString(CString str);

	static CString getCString(std::string str);

	static bool strMatch(CString str, std::string regex);
};

