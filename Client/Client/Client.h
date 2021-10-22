#pragma once

#include <iostream>
#include<string>
#include<vector>
#include<thread>
#include<chrono>
#ifdef _WIN32
#include<winsock.h>
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

class Client
{
public:
	Client(std::string ip, short port);
	void sendToServer(std::string message);
	std::string receiveFromServer();
	void closeSocket();
private:
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN sockaddrIn;
	bool isInitialized = false;
	void errorHandler(std::string message, int id);
};
