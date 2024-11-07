#include "global.hpp"
#include "Epoll_Wrapper.hpp"
#include "Server_Socket.hpp"
#include "Server.hpp"
#include "HttpProtocol.hpp"

int main(void)
{
	std::map<const short, ProtocolInterface *> port_proto_map;
	port_proto_map.insert(std::make_pair(6969, new HttpProtocol()));
	port_proto_map.insert(std::make_pair(6000, new HttpProtocol()));
	//TODO add a protol factory for state based protocols
	//Move socket and epoll create to server run to be able to use settings functions
	try{
	Server serv(port_proto_map);
	serv.run();
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}
