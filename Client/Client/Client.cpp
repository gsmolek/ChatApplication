// Client.cpp : Defines the entry point for the application.
//

#include "Client.h"

using namespace std;

int main()
{
	cout << "Hello." << endl;
	Client c("127.0.0.1", 12345);
	return 0;
}

Client::Client(std::string ip, short port)
{
	#ifdef _WIN32
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
	{
		std::cout << "WSAStartup Error!" << std::endl;
		exit(0);
	}
	std::cout << "WSAStartup Succeded" << std::endl;
	#endif // _WIN32

	Client::clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Client::clientSocket == INVALID_SOCKET)
	{
		std::cout << "Socket creation Error!" << std::endl;
		#ifdef _WIN32
		WSACleanup();
		#endif // _WIN32
		exit(0);
	}

	sockaddrIn.sin_addr.s_addr = inet_addr(ip.c_str());
	sockaddrIn.sin_family = AF_INET;
	sockaddrIn.sin_port = htons(port);

	if (connect(clientSocket, (SOCKADDR*)&sockaddrIn, sizeof sockaddrIn) != 0)
	{
		errorHandler("Socket creation Error!", 1);
	}
	isInitialized = true;
	for (int i = 0; i < 3; ++i)
	{
		Client::sendToServer("yeah\n");
		std::this_thread::sleep_for(std::chrono::seconds(3));
		
	}
		
}

void Client::sendToServer(std::string message)
{
		if (send(clientSocket, message.c_str(), sizeof message.c_str(), 0) < sizeof message.c_str())
		{
			errorHandler("Error in Send!", 1);
		}
}
std::string Client::receiveFromServer()
{
	char buffer[1024] = "";
	recv(clientSocket, buffer, sizeof buffer, 0);
	std::string output = buffer;
	return output;
}

void Client::errorHandler(std::string message, int id)
{
	std::cout << message << "message" << std::endl;
	closeSocket();
	exit(id);
}
void Client::closeSocket()
{
	#ifdef _WIN32
	closesocket(Client::clientSocket);
	WSACleanup();
	#else
	close(serverSocket);
	#endif	
}
