#pragma once
#include <boost/asio.hpp>
#include <map>
#include <vector>
#include<iostream>
#include<random>
#include<boost/date_time.hpp>

#define DEBUG

class Server
{
public:
	void run();
	void log_error(boost::system::error_code ex);
	std::string create_room();
private:

	std::map<std::string, std::vector<boost::asio::ip::tcp::socket*>> tableConnects;
	boost::asio::io_context context;
	std::vector<std::string> vec_ex;

private:

	void log_errors();
	void read_data(boost::asio::ip::tcp::socket& socket);
	void accept_conection(boost::asio::ip::tcp::acceptor& acceptor);
	void handle_socket(boost::asio::ip::tcp::socket* socket);
	std::string generateUniqueCode(int length);
	std::vector<boost::asio::ip::tcp::socket*>* get_users_on_room_code(std::string roomCode);
};

