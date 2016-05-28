#pragma once
#include <string>

using namespace std;

class CUUIDUtil
{
public:
	CUUIDUtil();
	~CUUIDUtil();

	static string genUUID();
};

