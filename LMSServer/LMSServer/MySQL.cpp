#include "stdafx.h"
#include "MySQL.h"
#include <fstream>
#include <iostream>
using namespace std;

MYSQL CMySQL::m_MyData;

CMySQL::CMySQL()
{
}


CMySQL::~CMySQL()
{
}

bool CMySQL::MySQLInit(const char* user, const char* password, const char* db, const char* host, int port)
{
	if (0 == mysql_library_init(0, NULL, NULL)) {
		if (NULL != mysql_init(&m_MyData)) {
			return ConnectDataBase(host, user, password, db, port);
		}
	}
	return false;
}
bool CMySQL::MySQLInit(std::string FileName)
{
	ifstream FStream(FileName);
	string User, Password, DataBase, Url;
	int Port;
	FStream >> User >> Password >> DataBase >> Url >> Port;
	FStream.close();
	return MySQLInit(User.c_str(), Password.c_str(), DataBase.c_str(), Url.c_str(), Port);
}
bool CMySQL::setMySQLOption(mysql_option option, std::string arg)
{
	if (0 == mysql_options(&m_MyData, option, arg.c_str())) {
		return true;
	}
	return false;
}
bool CMySQL::ConnectDataBase(const char* host, const char* user, const char* password, const char* db, int port)
{
	if (NULL
		!= mysql_real_connect(&m_MyData, host, user, password, db,
		port, NULL, 0))
		//这里的地址，用户名，密码，端口可以根据自己本地的情况更改
	{
		mysql_query(&m_MyData, "set names gbk");
		return true;
	}
	return false;
}
bool CMySQL::CreatTable(std::string table, std::initializer_list<std::string> columnsql)
{
	string sqlstr;
	//创建一个表
	sqlstr = "CREATE TABLE IF NOT EXISTS " + table;
	sqlstr += " (";
	auto begin = columnsql.begin();
	while (1)
	{
		sqlstr += (*begin);
		begin++;
		if (begin != columnsql.end())
			sqlstr += ",";
		else
			break;
	}
	sqlstr += ");";
	if (0 == mysql_query(&m_MyData, sqlstr.c_str())) {
		return true;
	}
	return false;
}
bool CMySQL::InsertValues(std::string table, std::initializer_list<std::string> field, std::initializer_list<std::string> value)
{
	string sqlstr =
		"insert into `" + table;
	sqlstr += "` (";
	auto begin = field.begin();
	while (1)
	{
		sqlstr += (*begin);
		begin++;
		if (begin != field.end())
			sqlstr += ",";
		else
			break;
	}
	sqlstr += ") values(";
	begin = value.begin();
	while (1)
	{
		sqlstr += "'";
		sqlstr += (*begin);
		sqlstr += "'";
		begin++;
		if (begin != value.end())
			sqlstr += ",";
		else
			break;
	}
	sqlstr += ")";
	if (0 == mysql_query(&m_MyData, sqlstr.c_str())) {
		return true;
	}
	return false;
}
std::vector<std::map<std::string, std::string> > CMySQL::GetResult(std::string sql)
{
	vector<map<string, string> > Out;
	vector<string> ColumName;
	MYSQL_RES *result = NULL;
	if (0 == mysql_query(&m_MyData, sql.c_str())) {
		//一次性取得数据集
		result = mysql_store_result(&m_MyData);
		//取得并打印行数
		int rowcount = mysql_num_rows(result);
		//取得并打印各字段的名称
		unsigned int fieldcount = mysql_num_fields(result);
		MYSQL_FIELD *field = NULL;
		MYSQL_ROW row = NULL;

		for (unsigned int i = 0; i<fieldcount; i++)
		{
			field = mysql_fetch_field_direct(result, i);
			ColumName.push_back(field->name);
		}

		row = mysql_fetch_row(result);
		while (NULL != row)
		{
			map<string, string> Temp;
			for (int i = 0; i<fieldcount; i++)
			{
				char* Str = row[i];
				if (Str == NULL)
					Temp[ColumName[i]] = "";
				else
					Temp[ColumName[i]] = Str;
			}
			row = mysql_fetch_row(result);
			Out.push_back(Temp);
		}
	}
	do
	{
		mysql_free_result(result);
	} while ((0 == mysql_next_result(&m_MyData)));
	return Out;
}

bool CMySQL::ExecuteSql(std::string sql)
{
	if (mysql_query(&m_MyData, sql.c_str()) == 0)
		return true;
	else
		return false;
}

bool CMySQL::DropTable(std::string table)
{
	//删除刚才建的表
	string sqlstr = "DROP TABLE " + table;
	if (0 == mysql_query(&m_MyData, sqlstr.c_str())) {
		return true;
	}
	return false;
}
void CMySQL::FreeMySQL()
{
	mysql_close(&m_MyData);
	mysql_server_end();
}
string CMySQL::ErrorMesg()
{
	const char* ErrorMesg = mysql_error(&m_MyData);
	string str(ErrorMesg);
	return str;
}