#include <iostream>
#include "Server.h"
#include <boost/asio.hpp> 
int main(int args, const char str[]) {
	std::string sbuf = "&UserName=test&CodeRoom=5555555&Text=hello world";
	Server sr;
	std::cout<< sr.create_room() << std::endl;
	return 0;
}