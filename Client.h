#pragma once
#include<boost/asio/ip/tcp.hpp>
class Client
{
public:
	auto get_native_handle() {return this->socStream->native_handle();}
private:
	boost::asio::ip::tcp::socket* socStream;
	std::string UserName;

};

