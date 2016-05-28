#pragma once
#include <string>
#include <map>
#include <vector>
#include <WinSock2.h>
#include <mysql.h>

/*
���һ��Ҫ����FreeMySQL();
*/
class CMySQL
{
public:
	//��ʼ��MySQL
	static bool MySQLInit(const char* user, const char* password, const char* db, const char* host = "localhost", int port = 3306);
	/*
	��ʼ��MySQ���������ļ����أ�
	�����ļ��ṹ��config.ini����
	���ݿ��û���
	��������
	���ݿ���
	���ݿ��URL������Ǳ������ݿ����� localhost��
	���ݿ�˿ںţ����û�и���MySQLĬ���� 3306��
	*/
	static bool MySQLInit(std::string FileName = "config.ini");
	//����MySQL����
	static bool setMySQLOption(mysql_option option, std::string sql);
	//�������ݿ⣬�����Ƿ�ɹ�
	static bool ConnectDataBase(const char* host, const char* user, const char* password, const char* db, int port = 3306);
	static bool CreatTable(std::string table, std::initializer_list<std::string> columnsql);
	//�����fieldΪ������е����ֵ��б�valueΪ��Ӧ��ֵ���б�
	static bool InsertValues(std::string table, std::initializer_list<std::string> field, std::initializer_list<std::string> value);
	//��ѯ������һ��map���б�ǩ����һ��Ԫ������ɵ�vector��
	static std::vector<std::map<std::string, std::string> > GetResult(std::string sql);

	static bool ExecuteSql(std::string sql);
	//ɾ����
	static bool DropTable(std::string table);
	//�ͷ�MySQL
	static void FreeMySQL();
	static std::string ErrorMesg();
	CMySQL();
	CMySQL(const CMySQL& MySQL) = delete;
	~CMySQL();
private:
	static MYSQL m_MyData;
};
