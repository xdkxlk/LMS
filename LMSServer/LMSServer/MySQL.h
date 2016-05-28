#pragma once
#include <string>
#include <map>
#include <vector>
#include <WinSock2.h>
#include <mysql.h>

/*
最后一定要调用FreeMySQL();
*/
class CMySQL
{
public:
	//初始化MySQL
	static bool MySQLInit(const char* user, const char* password, const char* db, const char* host = "localhost", int port = 3306);
	/*
	初始化MySQ（从配置文件加载）
	配置文件结构（config.ini）：
	数据库用户名
	数据密码
	数据库名
	数据库根URL（如果是本地数据库则是 localhost）
	数据库端口号（如果没有更改MySQL默认是 3306）
	*/
	static bool MySQLInit(std::string FileName = "config.ini");
	//设置MySQL设置
	static bool setMySQLOption(mysql_option option, std::string sql);
	//连接数据库，返回是否成功
	static bool ConnectDataBase(const char* host, const char* user, const char* password, const char* db, int port = 3306);
	static bool CreatTable(std::string table, std::initializer_list<std::string> columnsql);
	//插入表，field为插入的列的名字的列表，value为对应的值的列表
	static bool InsertValues(std::string table, std::initializer_list<std::string> field, std::initializer_list<std::string> value);
	//查询表，返回一个map（列标签，这一列元素所组成的vector）
	static std::vector<std::map<std::string, std::string> > GetResult(std::string sql);

	static bool ExecuteSql(std::string sql);
	//删除表
	static bool DropTable(std::string table);
	//释放MySQL
	static void FreeMySQL();
	static std::string ErrorMesg();
	CMySQL();
	CMySQL(const CMySQL& MySQL) = delete;
	~CMySQL();
private:
	static MYSQL m_MyData;
};
