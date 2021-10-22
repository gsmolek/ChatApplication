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