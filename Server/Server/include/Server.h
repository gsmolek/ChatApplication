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
#include<rsa.h>
#include<sha256.h>

#include <boost/multiprecision/cpp_int.hpp>
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


#ifdef _WIN32
#include<winsock2.h>
#include<Windows.h>
#include <ws2tcpip.h>
#elif __linux__
#include<sys/socket.h>
#include<arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include<unistd.h>
#include<stdlib.h>
#endif

class Server
{
public:
	Server(int port);
	~Server();
	void closeSocket(bool terminate);
	int getPort()
	{
		return port;
	}

private:
	struct clientInfo
	{
		std::string name;
		std::string ip;
		unsigned short port;
		SOCKET socketFd;
		sockaddr_in sockaddrIn;
	};
	struct threadsInfo
	{
		bool isRunning;
		int id;
		std::thread threadFunction;
	};

#ifdef _WIN32
	WSADATA wsaData;
#endif
	SOCKET serverSocket;
	SOCKET clientSocket;
	sockaddr_in service;
	sockaddr_in clientTemp;
	std::map<int, Server::threadsInfo> threads;
	std::vector<clientInfo> clients;
	bool acceptFlag = true;
	bool isActive = false;
	int port;
	int mainThreadId;
	void closeThreads();
	void errorHandler(std::string message, int exitNo);
	void processingRequests(Server::clientInfo info, std::string ip, std::string port);
	void mainThread();
	void createSocket();
	void bindSocket();
	void listenToSocket();
	void commandsThread();
};
