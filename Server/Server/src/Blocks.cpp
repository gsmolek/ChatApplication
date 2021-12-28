#include "Blocks.h"
std::vector<std::string> Blocks::partitioning(std::string& message, int hash_len, Server::Type type, int size,int n_size, int e_size)
{
	std::vector<std::string> output{};
	//enum Type{ LOGIN, MESSAGE, REQUEST, PUBLIC_KEY_REQUEST ,SIGNATURE_KEY_REQUEST };
	int header_length{};
	std::string header{};
	std::string hash_message_length_string = header_initialization(hash_len, message.length());

	switch (type)
	{
	LOGIN:
		header_length = 22 ;
		header = "001";
		break;
	MESSAGE:
		header_length = 22;
		header = "000";
		break;
	REQUEST:
		break;
	PUBLIC_KEY_REQUEST:
		header_length = 32;
		header = "002";
		break;
	SIGNATURE_KEY_REQUEST:
		header_length = 32;
		header = "003";
		break;
	}
	int number_of_blocks{ static_cast<int>(std::ceil(message.size() / static_cast<double>(size-header_length))) };
	int index;
	for (int i = 0, index = 0; i < number_of_blocks; ++i, ++index)
	{
		std::string header_of_packet = header + hash_message_length_string + "00000";
		output.push_back(message.substr(index, size));
		index += size;
		switch (type)
		{
		MESSAGE:
			std::string total_length{ "00000" };
			std::string offset{ "000" };
			std::string total{ "000" };

			total_length += output.at(i).length();
			offset += std::to_string(i);
			total += std::to_string(number_of_blocks - 1);

			header_of_packet.at(11) = total_length.at(total_length.length() - 5);
			header_of_packet.at(12) = total_length.at(total_length.length() - 4);
			header_of_packet.at(13) = total_length.at(total_length.length() - 3);
			header_of_packet.at(14) = total_length.at(total_length.length() - 2);
			header_of_packet.at(15) = total_length.at(total_length.length() - 1);

			header_of_packet += offset.at(offset.length() - 3);
			header_of_packet += offset.at(offset.length() - 2);
			header_of_packet += offset.at(offset.length() - 1);

			header_of_packet += total.at(total.length() - 3);
			header_of_packet += total.at(total.length() - 2);
			header_of_packet += total.at(total.length() - 1);

			header_of_packet += username_length.at(0);
			header_of_packet += username_length.at(1);
			header_of_packet += username_length.at(2);

			output.at(i) = header_of_packet + output.at(i);
			break;
		REQUEST:
			break;
		PUBLIC_KEY_REQUEST:
			std::string total_length{ "00000" };
			std::string offset{ "000" };
			std::string total{ "000" };
			std::string n_length{ "00000" };
			std::string e_length{ "00000" };
			total_length += output.at(i).length();
			offset += std::to_string(i);
			total += std::to_string(number_of_blocks - 1);

			header_of_packet.at(11) = total_length.at(total_length.length() - 5);
			header_of_packet.at(12) = total_length.at(total_length.length() - 4);
			header_of_packet.at(13) = total_length.at(total_length.length() - 3);
			header_of_packet.at(14) = total_length.at(total_length.length() - 2);
			header_of_packet.at(15) = total_length.at(total_length.length() - 1);

			header_of_packet += offset.at(offset.length() - 3);
			header_of_packet += offset.at(offset.length() - 2);
			header_of_packet += offset.at(offset.length() - 1);

			header_of_packet += total.at(total.length() - 3);
			header_of_packet += total.at(total.length() - 2);
			header_of_packet += total.at(total.length() - 1);

			header_of_packet += n_length.at(n_length.length() - 5);
			header_of_packet += n_length.at(n_length.length() - 4);
			header_of_packet += n_length.at(n_length.length() - 3);
			header_of_packet += n_length.at(n_length.length() - 2);
			header_of_packet += n_length.at(n_length.length() - 1);

			header_of_packet += e_length.at(e_length.length() - 5);
			header_of_packet += e_length.at(e_length.length() - 4);
			header_of_packet += e_length.at(e_length.length() - 3);
			header_of_packet += e_length.at(e_length.length() - 2);
			header_of_packet += e_length.at(e_length.length() - 1);

			header_of_packet += username_length.at(0);
			header_of_packet += username_length.at(1);
			header_of_packet += username_length.at(2);
			output.at(i) = header_of_packet + output.at(i);
			break;
		SIGNATURE_KEY_REQUEST:
			std::string total_length{ "00000" };
			std::string offset{ "000" };
			std::string total{ "000" };
			std::string n_length{ "00000" };
			std::string e_length{ "00000" };
			total_length += output.at(i).length();
			offset += std::to_string(i);
			total += std::to_string(number_of_blocks - 1);

			header_of_packet.at(11) = total_length.at(total_length.length() - 5);
			header_of_packet.at(12) = total_length.at(total_length.length() - 4);
			header_of_packet.at(13) = total_length.at(total_length.length() - 3);
			header_of_packet.at(14) = total_length.at(total_length.length() - 2);
			header_of_packet.at(15) = total_length.at(total_length.length() - 1);

			header_of_packet += offset.at(offset.length() - 3);
			header_of_packet += offset.at(offset.length() - 2);
			header_of_packet += offset.at(offset.length() - 1);

			header_of_packet += total.at(total.length() - 3);
			header_of_packet += total.at(total.length() - 2);
			header_of_packet += total.at(total.length() - 1);

			header_of_packet += n_length.at(n_length.length() - 5);
			header_of_packet += n_length.at(n_length.length() - 4);
			header_of_packet += n_length.at(n_length.length() - 3);
			header_of_packet += n_length.at(n_length.length() - 2);
			header_of_packet += n_length.at(n_length.length() - 1);

			header_of_packet += e_length.at(e_length.length() - 5);
			header_of_packet += e_length.at(e_length.length() - 4);
			header_of_packet += e_length.at(e_length.length() - 3);
			header_of_packet += e_length.at(e_length.length() - 2);
			header_of_packet += e_length.at(e_length.length() - 1);

			header_of_packet += username_length.at(0);
			header_of_packet += username_length.at(1);
			header_of_packet += username_length.at(2);

			output.at(i) = header_of_packet + output.at(i);
			break;
		}
	}
	return output;
}
std::vector<std::string> Blocks::combining(std::vector<std::string> input)
{
	std::vector<std::string> output{};
	int total_length_integer{};
	std::string string_code{};
	std::string message_length{};
	std::string total_length{};
	std::string hash_length{};
	std::string total_packets{};
	std::string username_length{};
	std::string password_length{};
	std::string n_length_message{};
	std::string e_length_message{};
	std::string username_length{};
	std::string username{};
	std::string password{};
	std::string whole_message{};
	string_code = input.at(0).substr(0, 3);


	for(int i = 0 ; i < input.size() ; i++)
	{
		if (string_code == "000")
		{
			if (i == 0)
			{
				message_length = input.at(0).substr(3, 5);
				hash_length = input.at(0).substr(8, 3);
				total_packets = input.at(0).substr(19, 3);
				total_length = input.at(0).substr(11, 5);
				total_length_integer = std::stoi(total_length);
				username_length = input.at(0).substr(22, 3);
				username = input.at(0).substr(25, std::stoi(username_length));
			}
			whole_message += input.at(i).substr(22, total_length_integer);
		}
		else if (string_code == "001")
		{

			if (i == 0)
			{
				message_length = input.at(0).substr(3, 5);
				hash_length = input.at(0).substr(8, 3);
				total_packets = input.at(0).substr(19, 3);
				total_length = input.at(0).substr(11, 5);
				total_length_integer = std::stoi(total_length);
				password_length = input.at(0).substr(16, 3);
				password = input.at(0).substr(22 ,std::stoi(password_length ));
				username_length = input.at(0).substr(19, 3);
				username = input.at(0).substr(22 + std::stoi(password_length), std::stoi(username_length));
			}
			whole_message += input.at(i).substr(22, total_length_integer);
		}
		else if (string_code == "002" || string_code == "003")
		{
			if (i == 0)
			{
				message_length = input.at(0).substr(3, 5);
				hash_length = input.at(0).substr(8, 3);
				total_packets = input.at(0).substr(19, 3);
				total_length = input.at(0).substr(11, 5);
				total_length_integer = std::stoi(total_length);
				n_length_message = input.at(0).substr(22, 5);
				e_length_message = input.at(0).substr(27, 5);
				username_length = input.at(0).substr(32, 3);
				username = input.at(0).substr(35, std::stoi(username_length));
			}
			whole_message += input.at(i).substr(32, total_length_integer);
		}
	}
	
	if (string_code == "000")
	{
		output.push_back(string_code);
		output.push_back(username);
		output.push_back(message_length);
		output.push_back(hash_length);
		output.push_back(whole_message);
	}
	else if (string_code == "001")
	{
		output.push_back(string_code);
		output.push_back(username);
		output.push_back(message_length);
		output.push_back(hash_length);
		output.push_back(password_length);
		output.push_back(username_length);
		output.push_back(whole_message);
	}
	else if (string_code == "002" || string_code == "003")
	{
		output.push_back(string_code);
		output.push_back(username);
		output.push_back(message_length);
		output.push_back(hash_length);
		output.push_back(n_length_message);
		output.push_back(e_length_message);
		output.push_back(whole_message);
	}
	return output;
}
std::string Blocks::header_initialization(int hash_len, int message_length)
{
	std::string output{};
	std::string hash_length{ "000" };
	std::string msg_length{ "00000" };
	std::string hash_value = std::to_string(hash_len);
	std::string msg_value = std::to_string(message_length);

	msg_length += msg_value;
	output += msg_length.at(hash_length.length() - 5);
	output += msg_length.at(hash_length.length() - 4);
	output += msg_length.at(hash_length.length() - 3);
	output += msg_length.at(hash_length.length() - 2);
	output += msg_length.at(hash_length.length() - 1);

	hash_length += hash_value;
	output += hash_length.at(hash_length.length() - 3);
	output += hash_length.at(hash_length.length() - 2);
	output += hash_length.at(hash_length.length() - 1);

	return output;
}