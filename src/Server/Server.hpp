/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:01:06 by bplante           #+#    #+#             */
/*   Updated: 2024/11/20 14:13:04 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "EpollWrapper.hpp"
#include "ServerSocket.hpp"
#include "Connection.hpp"
#include "IProtocol.hpp"
#include "IProtocolFactory.hpp"
#include "list"
#include "map"

class Server
{
private:
	Epoll_Wrapper *_epoll;
	std::list<Connection *> _connections;
	std::map<ServerSocket *, IProtocolFactory *> _sock_map;

public:
	Server(std::map<const short, IProtocolFactory *> &port_proto_map);
	void run(void);
	~Server(void);
	class Server_Exception : public std::exception
	{
	private:
		std::string _message;

	public:
		Server_Exception(const std::string &msg) : _message(msg) {};
		const char *what(void) const throw()
		{
			return _message.c_str();
		}
		virtual ~Server_Exception(void) throw() {}
	};

private:
	int closeConnection(Connection *con);
};
