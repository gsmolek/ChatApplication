#include<vector>
#include<string>
#include<cmath>
#include "Server.h"
class Blocks
{
private:
	static std::string username{ "server" };
	static std::string username_length{ "006" };
	static std::vector<std::string> partitioning(std::string& message,int hash_len,Server::Type type, int size ,int n_size, int e_size);
	static std::vector<std::string> combining(std::vector<std::string> input);
	static std::string header_initialization(int hash_len, int message_length);
};