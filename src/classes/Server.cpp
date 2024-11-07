/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:31:09 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 20:42:36 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(std::map<const short, ProtocolInterface *> &port_proto_map)
{
	if (port_proto_map.size() == 0)
		throw Server_Exception("No listed port to listen to\n");
	_epoll = new Epoll_Wrapper();
	for (std::map<const short, ProtocolInterface *>::const_iterator i = port_proto_map.begin(); i != port_proto_map.end(); i++)
	{
		Server_Socket *sock = new Server_Socket(i->first, *_epoll);
		ProtocolInterface *proto = i->second;
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
				for (std::map<Server_Socket *, ProtocolInterface *>::iterator i = _sock_map.begin(); i != _sock_map.end(); i++)
				{
					Server_Socket *sock = i->first;
					if (ptr->data.ptr == sock)
					{
						Connection *connection = new Connection(*sock, *_epoll, i->second);
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
						std::string *msg = con->recieve();
						std::cout << *msg;
						delete msg;
						con->send_msg("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
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
	for (std::map<Server_Socket *, ProtocolInterface *>::iterator i = _sock_map.begin(); i != _sock_map.end(); i++)
	{
		delete i->first;
	}
	delete _epoll;
}