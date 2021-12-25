#pragma once

#include <iostream>
#include <sstream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<string>
#include<vector>
#include<thread>
#include<chrono>
#include<map>
#include<rsa.h>
#include<sha256.h>
#include<mySQLConnect.h>
#include<cmath>

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
	Rsa rsa;

	boost::multiprecision::cpp_int n{ "20526766413795073776754021273959414186564998880159985618870658181689441888484130763277389830428692528202488992850869808640159588725297406273481320336942630855144500627473825226625951519157939019067104740005250022497092815361703109519347397643958970872943285476778018240125393132105054692669578962863440894603836489597198326894764981211539494593024618464042234006822899281519309445068742950046664237747630826665724665379406896640927819922688745585693716772517155708251843681268099717010790743892359116080401707809828186428628374576398698878603151231260696914863207145913365327930099137255910263733972825828496007533747" };
	boost::multiprecision::cpp_int e{ "438814270853093994085182747074266407295061167680798662233005953928739227816300271445412071924669188444568349316823207638498671216467817937805801770837289" };
	boost::multiprecision::cpp_int d{ "14954664479091906365074472130063554121547518494341392395511209707012820009533261683466978409071967471085426790421536767975922796291579108943189365070658163839547966694033582815644656973971705401606834443201853767905106070482541528199748749557855315976369425623143163706245611118620252137211560661201486905500342808585588524183602455930329276003961639525979755579680340352047622146135822208052917160582546172404712292197442600475041907002286977201775276311475597187357439459858596710872079746696675167071015005344390343209657494967605762303426407507296596290580324547073568725580269693480176791345488839030127224171417" };
	boost::multiprecision::cpp_int signatureN{ "268658839346776570701449808586126236276902261649586210335305293805337824233034456122012050560964587379477301083698531217157684736058410029551204238799276693615008556610894054024717884920296898024623671611592505029436597800191260974881148905776345381324890450355999375347079779836004897987755168349196037403" };
	boost::multiprecision::cpp_int signatureE{ "102109316002566617147266568114795843851931608888049895681020676278928903464459" };
	boost::multiprecision::cpp_int signatureD{ "46586000483966342709639582571395583021144232157953462039587751554547462485607007698215861874330608599802656687954516789100416353382805176127845129262017172323867745233676663613749122681688472691027433224840681489521750860679921991897840321017725349616184889883533028261303817252606987077523478382463740107" };
	mySQLConnect mySQLconnection;
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
	void errorHandler(const std::string& message,const int exitNo);
	void processingRequests(const Server::clientInfo& info,const std::string& ip, const std::string& port);
	void mainThread();
	void createSocket();
	void bindSocket();
	void listenToSocket();
	void commandsThread();
	void codeOperations(int code, std::string message);
	std::string digital_signing(const std::string& message, const std::string& code);
	std::string check_digital_signing(const std::string& message);
	std::vector<std::string> partitioning(const int size, const std::string& input);
	std::vector<std::string> padding(int size_to_add, std::string& input);
};
