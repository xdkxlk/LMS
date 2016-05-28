#pragma once
#include "json.h"
#include <string>

using namespace std;

class CJsonUtil
{
public:
	CJsonUtil();
	~CJsonUtil();

	static bool genJsonVal(CString str, Json::Value& val);
	static bool genJsonVal(const string& str, Json::Value& val);
	static string toString(Json::Value val);
};