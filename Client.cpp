#include "Client.h"

void Client::send_massage()
{
	for (auto el : ourConnections) {
		std::vector<char> fbuf(1024);
		el->async_write_some(boost::asio::buffer(fbuf.data(), fbuf.size()), [&](boost::system::error_code ex) {
			if (!ex) {
			#ifdef DEBUG

			#endif // DEBUG

			}
			else{
			}
			});
		}
}
