/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:31:09 by bplante           #+#    #+#             */
/*   Updated: 2024/11/20 14:48:33 by bplante          ###   ########.fr       */
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
				bool has_closed = false;
				if (ptr->events & EPOLLIN)
				{
					Connection *con = const_cast<Connection *>(static_cast<const Connection *>(ptr->data.ptr));
					try
					{
						if (con->recieve() == -1)
						{
							if (closeConnection(con) == 0)
								has_closed = true;
							if (_connections.size() == 0)
								loop = false;
						}
					}
					catch (const std::exception &e)
					{
						std::cout << "client disconnected\n";
						if (closeConnection(con) == 0)
							has_closed = true;
						if (_connections.size() == 0)
							loop = false;
					}
				}
				if (ptr->events & EPOLLOUT && has_closed == false)
				{
					Connection *con = const_cast<Connection *>(static_cast<const Connection *>(ptr->data.ptr));
					con->sendData();
				}
			}
		}
	}
}

int Server::closeConnection(Connection *con)
{
	for (std::list<Connection *>::iterator i = _connections.begin(); i != _connections.end(); i++)
	{
		if (*i == con)
		{
			delete *i;
			_connections.erase(i);
			return 0;
		}
	}
	return -1;
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