#include "Server.h"


void Server::run()
{
	boost::asio::ip::tcp::acceptor acceptor(this->context);
	std::string hostName = boost::asio::ip::host_name();
	boost::asio::ip::tcp::resolver resolver(this->context);
	auto ip = resolver.resolve(hostName);
}

void Server::log_error(boost::system::error_code ex)//good
{
	std::cout << boost::posix_time::second_clock::local_time() << " : " << ex.message() << std::endl;
}

std::string Server::create_room() //good work
{
	std::cout << "Enter user name: "<<std::endl;
	std::string userName;
	std::cin >> userName;
	std::string room_code = generateUniqueCode(8);
	return room_code;
}

void Server::log_errors()
{
	for (auto& element : this->vec_ex) {
		std::cout << element<< std::endl;
	}
}

void Server::read_data(boost::asio::ip::tcp::socket& socket)
{

}

void Server::accept_conection(boost::asio::ip::tcp::acceptor& acceptor)
{
		boost::asio::ip::tcp::socket* socket = new boost::asio::ip::tcp::socket(this->context);
		acceptor.async_accept(*socket, [this,&socket, &acceptor](boost::system::error_code ex) {
			if (!ex) {
				handle_socket(socket);
			}
			else {
				this->log_error(ex);
			}
			accept_conection(acceptor);
		});
}

void Server::handle_socket(boost::asio::ip::tcp::socket* socket)
{
	std::vector<char> fbuf(1024 * 10);
	std::string sbuf;
	sbuf.reserve(1024 * 10);
	//read socket
	socket->async_read_some(boost::asio::buffer(sbuf), [&](boost::system::error_code ex,std::size_t length){
		if (!ex) {
			for (int i = 0; i < length; i++) {	
			#ifdef DEBUG
				std::cout << sbuf[i];
			#else
			
			#endif // DEBUG

			}
		}
		else {
			this->log_error(ex);
		}
	});
	std::string room_keys = generateUniqueCode(8);
	std::vector<boost::asio::ip::tcp::socket*> vec = {socket};
	this->tableConnects.emplace(room_keys, vec);

}

std::string Server::generateUniqueCode(int length) //good work
{
		const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		const int charsetSize = sizeof(charset) - 1;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, charsetSize - 1);

		std::string code;
		code.reserve(length);

		for (int i = 0; i < length; ++i) {
			code += charset[dist(gen)];
		}

		if (this->tableConnects.find(code) == this->tableConnects.end()) {
			return code;
		}
		else {
			return generateUniqueCode(length);
		}
		return code;
	
}

std::vector<boost::asio::ip::tcp::socket*>* Server::get_users_on_room_code(std::string roomCode)
{
	auto element = this->tableConnects.find(roomCode);
	if (element != this->tableConnects.end()) {
		return &(*element).second;
	}
	else {
		return new std::vector<boost::asio::ip::tcp::socket*>;
	}

}
