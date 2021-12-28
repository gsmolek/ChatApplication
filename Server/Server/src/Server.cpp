#include "server.h"
#include "mySQLConnect.h"
#include "DigitalSignature.h"

/*
* TO-DO:
* thread that removes closed connections from container
* insert information into the sql tables'
*/
void Server::processingRequests(const Server::clientInfo& clientInfo, const std::string& ip, const std::string& port)
{
	char buffer[BUFFER_SIZE]{};
	int id = -1;
	unsigned short count = 0;
	int result;
	std::string message{};
	std::stringstream stringStream;


	int message_length;
	int hash_length;
	int password_length;
	int username_length;

	stringStream << std::this_thread::get_id();
	id = std::stoi(stringStream.str());
	boolean flag = true;
	while (flag)
	{
		//count++;
		result = recv(clientInfo.socketFd, (char *)buffer, sizeof buffer, 0);
		if (result > 0 ) 
		{
			//message = "";
			if(result < BUFFER_SIZE)
				buffer[result] = '\0';
			message.append(buffer);
			std::cout << message << "\n" << std::endl;
			/*
					statment = "SELECT e_signature,n_signature,IP FROM users WHERE PRUserName = '";
					statment += user_name;
					statment += "'";
					std::vector<std::string> result = mySQLconnection.get_multiple_values(statment);
					boost::multiprecision::cpp_int e = boost::multiprecision::cpp_int{ result.at(0)};
					boost::multiprecision::cpp_int n = boost::multiprecision::cpp_int{ result.at(1) };
					std::string ip = result.at(2);
					*/
			
			//Decryption needed before we can retrieve the code of the message
			message = Rsa::static_decryption(message, d, n);
			std::string code = message.substr(0, 3);
			/*
			*
			*	static bool validate
			*	(boost::function<std::string(const std::string& hash,
			*	boost::multiprecision::cpp_int&,
			*	boost::multiprecision::cpp_int&)> signing_function,
			*	boost::multiprecision::cpp_int n, boost::multiprecision::cpp_int e,
			*	std::function<std::string(const std::string&)> hash,
			*	const std::string& message_recieved,
			*	const std::string& hash_recieved);
			* 
			*/
			if (code == "001")
			{
				//needs to be decrypted!
				message_length = std::stoi(message.substr(3,5));
				hash_length = std::stoi(message.substr(8, 3));
				password_length = std::stoi(message.substr(16, 3));
				username_length = std::stoi(message.substr(19, 3));

				std::string password = message.substr(22, password_length);
				std::string username = message.substr(22 + password_length, username_length);
				std::string hash = message.substr(22 + message_length, hash_length);
				DigitalSignature::validate(hash,Rsa::static_encryption)
				//hash needs to be decrypted inorder to compare
			}
			else if (code == "002")
			{

			}
			std::string message = "";

			send(clientInfo.socketFd, message.c_str(), sizeof message.c_str(), 0);
		}
		else if (result <= 0)
		{
			unsigned int count = 0;
			for (auto& vec : Server::clients)
			{
				if (vec.ip == clientInfo.ip && vec.name == clientInfo.name)
				{
					Server::clients.erase(Server::clients.begin()+count);
					Server::threads.erase(id);
					flag = false;
					break;
				}
			}
			if (flag == false)
			{
				break;
			}
		}


	}
	
	/*
	* TO-DO:
	* create the protocol between the client and the server.
	*/
}


Server::~Server()
{
	closeSocket(true);
}
void Server::mainThread()
{
	createSocket();
	bindSocket();
	listenToSocket();
	Server::isActive = true;
	while (true)
	{
		if (isActive)
		{
			char hostname[NI_MAXHOST];
			char servInfo[NI_MAXSERV];
			int clientTempSize = sizeof Server::clientTemp;
			std::string ipString, portString;
			std::stringstream stringStream;
			Server::clientInfo clientInfoTemp;

			Server::threadsInfo threadsInfoTemp;
			clientSocket = accept(Server::serverSocket, (SOCKADDR*)&clientTemp, &(clientTempSize));
			if (!isActive && clientSocket == INVALID_SOCKET)
			{
				std::cout << "Accept disabled!" << std::endl;
				continue;
			}
			clientInfoTemp.socketFd = clientSocket;

			getnameinfo((SOCKADDR*)&clientTemp, sizeof SOCKADDR, hostname, NI_MAXHOST, servInfo, NI_MAXSERV, NI_NUMERICSERV);
			
			clientInfoTemp.name = hostname;
			clientInfoTemp.sockaddrIn = clientTemp;
			clientInfoTemp.ip = inet_ntoa(clientInfoTemp.sockaddrIn.sin_addr);
			
			int len = sizeof clientTemp;
			 getsockname(clientSocket, (SOCKADDR*)&clientTemp, &len);
			 clientInfoTemp.port = ntohs(clientTemp.sin_port);
			std::cout << "service port" << clientInfoTemp.port << std::endl;
	
			ipString = clientInfoTemp.ip;
			portString = std::to_string(clientInfoTemp.port);

			clients.push_back((clientInfoTemp));

			std::thread newThread(&Server::processingRequests, this, clientInfoTemp, std::move(ipString), std::move(portString));
			newThread.detach();

			stringStream << newThread.get_id();
			threadsInfoTemp.threadFunction = std::move(newThread);
			threadsInfoTemp.isRunning = true;
			threadsInfoTemp.id = std::stoi(stringStream.str());
			Server::threads.insert({ threadsInfoTemp.id, std::move(threadsInfoTemp) });
		}
		
	}
}
void Server::createSocket()//1
{
	Server::serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Server::serverSocket == INVALID_SOCKET)
	{
		std::cout << "Socket creation Error!" << std::endl;
		#ifdef _WIN32
		WSACleanup();
		#endif // _WIN32
		exit(0);
	}
}
void Server::bindSocket()//2
{
	Server::service.sin_family = AF_INET;
	Server::service.sin_addr.s_addr = INADDR_ANY;
	Server::service.sin_port = htons(port);
	if (bind(Server::serverSocket, (SOCKADDR*)&(Server::service), sizeof(Server::service)) == SOCKET_ERROR)
	{
		Server::errorHandler("Socket binding error!", 1);
	}
}
void Server::listenToSocket()//3
{
	if (listen(Server::serverSocket, SOMAXCONN) != 0)
	{
		Server::errorHandler("Socket listening error!", 2);
	}
}
void Server::commandsThread()
{
	std::cout << "##Server## ";
	while (true)
	{
		std::string firstInput, secondInput, thirdInput;
		std::cin >> firstInput;
		if (firstInput == "help")
		{
			std::cout << "		---HELP---" << std::endl;
			std::cout << "	1. getport - The server port for connections." << std::endl;
			std::cout << "	2. userno - The number of user connnect with their information." << std::endl;
			std::cout << "	3. isactive - is the server accepts connection." << std::endl;
			std::cout << "	4. pause - pause accepting requests." << std::endl;
			std::cout << "	5. start - start accepting requests again." << std::endl;
			std::cout << "	6. exit - close the sockets and exit the program." << std::endl;
			std::cout << "		---------" << std::endl;
			/*
			* TO-DO:
			* add all the available commands
			*/
		}
		else if (firstInput == "exit")
		{
			Server::errorHandler("", 1);
			return;
		}
		else if (firstInput == "getport")
		{
			std::cout << "		---PORT---" << std::endl;
			std::cout << "	Port used : " << Server::port << std::endl;
			std::cout << "		----------" << std::endl;
		}
		else if (firstInput == "usersno")
		{
			std::cout << "		---USERS---" << std::endl;
			std::cout << "	There are  " << Server::clients.size() << " clients connected." << std::endl;
			int i = 0;
			for (auto& c : Server::clients)
				std::cout << i << ". " << c.name << " " << c.ip << " " << c.port << std::endl;
			std::cout << "		-----------" << std::endl;
		}
		else if (firstInput == "isactive")
		{
			std::cout << "		---ACTIVE STATUS---" << std::endl;
			std::string temp;
			if (isActive)
			{
				temp = "	active.";
			}
			else if (!isActive)
			{
				temp = "	inactive.";
			}
			std::cout << "	accepting connections is currently " << temp << std::endl;
			std::cout << "		-------------------" << std::endl;

		}
		else if(firstInput == "pause")
		{
			if (isActive) 
			{
				isActive = false;
				closeSocket(false);
				std::cout << "	Accepting connections is diasbled" << std::endl;
			}
			else
			{
				std::cout << "	The socket is already paused." << std::endl;
			}
		}
		else if (firstInput == "start")
		{
			if (!isActive)
			{
				createSocket();
				bindSocket();
				listenToSocket();
				isActive = true;
				std::cout << "	Ready for connections." << std::endl;
			}
			else
			{
				std::cout << "	The socket is already running." << std::endl;
			}
		}
		else if (firstInput == "dbstatus")
		{
			try {

	
			}
			catch (std::exception e) {
				std::cout << e.what() << "\n" << std::endl;
			}
		}
		else {
			std::cout << "	There is no command";
			std::cout << " \"" << firstInput << "\"" << ". Try \"help\" for more information." << std::endl;

		}
		std::cout << "##Server## ";
	}
}

Server::Server(const int port)
{
	Server::port = port;
	Server::threadsInfo mainThreadInfo;
	Server::threadsInfo commandThreadInfo;
	std::stringstream stringStream;
	#ifdef _WIN32
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
	{
		std::cout << "WSAStartup faild!" << std::endl;
	}
	#endif // _WIN32
	mySQLconnection = mySQLConnect("127.0.0.1","3306", "root", "1234");
	std::thread commandT(&Server::commandsThread, this);
	commandT.detach();
	commandThreadInfo.isRunning = true;
	stringStream << commandT.get_id();
	commandThreadInfo.id = std::stoi(stringStream.str());
	commandThreadInfo.threadFunction = std::move(commandT);
	Server::threads.insert({ commandThreadInfo.id, std::move(commandThreadInfo)});
	std::string tr{};
	tr += n.str();
	tr += e.str();
	tr += gsm::Sha256::hash_value(tr);
	std::cout << "tr length: " << tr.length() << std::endl;
	//tr = DigitalSignature::signing(Rsa::static_encryption, gsm::Sha256::hash_value, this->n, this->d, tr);
	std::cout << "tr: " << tr << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	//Rsa::static_decryption(tr, e, n);
	tr = Rsa::char_string_to_ascii_value_string(tr);
	std::cout << "tr: " << std::endl;
	std::cout << "tr: " << std::endl;
	std::cout << "tr: " << tr << std::endl;
	std::cout << "tr length: " << tr.length() << std::endl;
	mainThread();
}
void Server::closeSocket(bool terminate)
{
	#ifdef _WIN32
	closesocket(Server::serverSocket);
	closesocket(Server::clientSocket);
	if (terminate) 
	{
		WSACleanup();
	}
	#else
	close(Server::serverSocket);
	#endif // _WIN32
}

void Server::closeThreads()
{
	for (const auto &p : threads)
	{
		p.second.threadFunction.~thread();
	}
	threads.clear();
}

void Server::errorHandler(const std::string& message, const int exitNo)
{
	std::cout << message << std::endl;
	closeSocket(true);
	closeThreads();
	exit(exitNo);
}


int main()
{

	Server server(5555);

}
