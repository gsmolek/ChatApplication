#include "mySQLConnect.h"

mySQLConnect::mySQLConnect(std::string ip, std::string port, std::string username, std::string password)
{
	mySqlDriver = sql::mysql::get_driver_instance();
	std::string temp;
	temp = "tcp://" + ip + ":" + port;
	const sql::SQLString host = temp;
	const sql::SQLString user = username;
	const sql::SQLString pass = password;
	try {
		connection = mySqlDriver->connect(host, user, pass);
		connection->setSchema("server");
	}
	catch (sql::SQLException& e)
	{
		std::cout <<"#ERROR: " << e.what();
		std::cout <<"(MySQL error code: "<<e.getErrorCode();
		std::cout << ",SQLState: " << e.getSQLState() << " )" << std::endl;
	}
}
void mySQLConnect::close()
{
	delete connection;
}

std::string mySQLConnect::get_single_value(std::string query)
{
	try
	{
		sql::Statement* stmt;
		sql::ResultSet* res;
		stmt = connection->createStatement();
		res = stmt->executeQuery(query);
		res->next();
		std::string output = res->getString(1);
		delete res;
		delete stmt;
		return output;
	}
	catch (sql::SQLException& e)
	{
		print_exception(e);
		return "0";
	}
	
}
std::vector<std::string> mySQLConnect::get_multiple_values(std::string query)
{
	std::vector<std::string> output;
	try
	{
		sql::Statement* stmt;
		sql::ResultSet* res;
		stmt = connection->createStatement();
		res = stmt->executeQuery(query);
		
		while (res->next())
		{
			output.push_back(res->getString(1));
		}
		delete res;
		delete stmt;
		return output;
	}
	catch (sql::SQLException& e)
	{
		print_exception(e);
		return output;
	}

}

std::string mySQLConnect::get_username(std::string username)
{
	try 
	{
		sql::Statement* stmt;
		sql::ResultSet* res;
		std::string statment = "SELECT PasswordHash FROM users WHERE PRUserName = '";
		statment += username;
		statment += "'";
		stmt = connection->createStatement();
		res = stmt->executeQuery(statment);
		res->next();
		statment = res->getString(1);
		delete res;
		delete stmt;
		return statment;
	}
	catch (sql::SQLException& e)
	{
		print_exception(e);
		return "failed";
	}
	
}

void mySQLConnect::print_exception(sql::SQLException& e)
{
	std::cout << "# ERR: SQLException in " << __FILE__;
	std::cout << "(" << "EXAMPLE_FUNCTION" << ") on line " << __LINE__ << std::endl;

	/* Use what() (derived from std::runtime_error) to fetch the error message */

	std::cout << "# ERR: " << e.what();
	std::cout << " (MySQL error code: " << e.getErrorCode();
	std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
}
