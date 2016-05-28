#include "stdafx.h"
#include "JsonUtil.h"
#include "StringUtil.h"

CJsonUtil::CJsonUtil()
{
}


CJsonUtil::~CJsonUtil()
{
}

bool CJsonUtil::genJsonVal(CString str, Json::Value& val)
{
	Json::Reader reader;
	return reader.parse(CStringUtil::getStdString(str), val);
}

bool CJsonUtil::genJsonVal(const string& str, Json::Value& val)
{
	Json::Reader reader;
	return reader.parse(str, val);
}

string CJsonUtil::toString(Json::Value val)
{
	Json::FastWriter fast_writer;
	return fast_writer.write(val);
}

Json::Value CJsonUtil::genJsonVal(const string& str)
{
	Json::Value val;
	Json::Reader reader;
	reader.parse(str, val);
	return val;
}