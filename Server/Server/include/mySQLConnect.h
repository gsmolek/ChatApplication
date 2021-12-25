#pragma once

#include <iostream>
#include <sstream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<vector>
#include<thread>
#include<chrono>
#include<map>
#include <mysql/jdbc.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/build_config.h>
#include <jdbc/cppconn/config.h>
#include <jdbc/cppconn/connection.h>
#include <jdbc/cppconn/datatype.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/metadata.h>
#include <jdbc/cppconn/parameter_metadata.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/resultset_metadata.h>
#include <jdbc/cppconn/sqlstring.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/variant.h>
#include <jdbc/cppconn/version_info.h>
#include <jdbc/cppconn/warning.h>

#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>

class mySQLConnect {
public:
	mySQLConnect()
	{
		mySQLConnect("127.0.0.1","3306", "root", "1234");
	};
	mySQLConnect(std::string ip, std::string port, std::string username, std::string password);
	void close();
	std::string get_single_value(std::string query);
	std::vector<std::string> get_multiple_values(std::string query);
	std::string get_username(std::string username);
private:
	sql::mysql::MySQL_Driver* mySqlDriver;
	void print_exception(sql::SQLException& e);
	sql::Connection* connection;
	
};
