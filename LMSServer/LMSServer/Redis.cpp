#include "stdafx.h"
#include "Redis.h"
#include "UUIDUtil.h"

map<string, Json::Value> CRedis::c_data;

string CRedis::put(Json::Value val)
{
	string key = CUUIDUtil::genUUID();
	put(key, val);
	return key;
}

void CRedis::put(string key, Json::Value val)
{
	c_data[key] = val;
}

Json::Value CRedis::get(string key)
{
	auto index = c_data.find(key);
	if (index != c_data.end())
		return index->second;
	return Json::Value::null;
}

void CRedis::del(string key)
{
	auto index = c_data.find(key);
	if (index != c_data.end())
		c_data.erase(index);
}