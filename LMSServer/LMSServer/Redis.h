#pragma once
#include <map>
#include <string>
#include "json.h"

using namespace std;

class CRedis
{
public:
	static string put(Json::Value val);
	static void put(string key, Json::Value val);
	static Json::Value get(string key);
	static void del(string key);

	static map<string, Json::Value> c_data;
};

