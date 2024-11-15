/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:31:09 by bplante           #+#    #+#             */
/*   Updated: 2024/11/15 01:25:32 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(std::map<const short, IProtocolFactory *> &port_proto_map)
{
	if (port_proto_map.size() == 0)
		throw Server_Exception("No listed port to listen to\n");
	_epoll = new Epoll_Wrapper();
	for (std::map<const short, IProtocolFactory *>::const_iterator i = port_proto_map.begin(); i != port_proto_map.end(); i++)
	{
		ServerSocket *sock = new ServerSocket(i->first, *_epoll);
		IProtocolFactory *proto = i->second;
		_sock_map.insert(std::make_pair(sock, proto));
	}
}

void Server::run(void)
{
	std::cout << "Sever running" << std::endl;
	bool loop = true;
	while (loop)
	{
		const std::vector<struct epoll_event> events = _epoll->wait();
		if (events.size() != 0)
		{
			std::vector<struct epoll_event>::const_iterator ptr;
			for (ptr = events.begin(); ptr != events.end(); ptr++)
			{
				bool is_in = false;
				for (std::map<ServerSocket *, IProtocolFactory *>::iterator i = _sock_map.begin(); i != _sock_map.end(); i++)
				{
					ServerSocket *sock = i->first;
					if (ptr->data.ptr == sock)
					{
						Connection *connection = new Connection(*sock, *_epoll, i->second->createNew());
						_connections.push_back(connection);
						std::cout << "accepted connection on port " << sock->getPort() << "\n";
						is_in = true;
						break;
					}
				}
				if (is_in)
					continue;
				if (ptr->events & EPOLLIN)
				{
					Connection *con = const_cast<Connection *>(static_cast<const Connection *>(ptr->data.ptr));
					try
					{
						con->recieve();
						con->sendData();
					}
					catch (const std::exception &e)
					{
						std::cout << "client disconnected\n";
						for (std::list<Connection *>::iterator i = _connections.begin(); i != _connections.end(); i++)
						{
							if (*i == con)
							{
								delete *i;
								_connections.erase(i);
								break;
							}
						}
						if (_connections.size() == 0)
							loop = false;
					}
					// {
					// 	std::string msg = cli->recieve();
					// 	_channels[0]->send_to_channel(msg);
					// }
					// catch (const std::exception &e)
					// {
					// 	for (size_t i = 0; i < _clients.size(); i++)
					// 	{
					// 		if (_clients[i] == cli)
					// 		{
					// 			_clients.erase(_clients.begin() + i);
					// 			_channels[0]->remove_client(*cli);
					// 		}
					// 	}
					// }
				}
			}
		}
	}
}

Server::~Server(void)
{
	for (std::list<Connection *>::iterator i = _connections.begin(); i != _connections.end(); i++)
		delete *i;
	for (std::map<ServerSocket *, IProtocolFactory *>::iterator i = _sock_map.begin(); i != _sock_map.end(); i++)
	{
		delete i->first;
	}
	delete _epoll;
}