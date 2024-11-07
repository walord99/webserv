/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:01:06 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 20:35:38 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Epoll_Wrapper.hpp"
#include "Server_Socket.hpp"
#include "Connection.hpp"
#include "ProtocolInterface.hpp"
#include "list"
#include "map"

class Server
{
private:
	Epoll_Wrapper *_epoll;
	std::list<Connection *> _connections;
	std::map<Server_Socket *, ProtocolInterface *> _sock_map;

public:
	Server(std::map<const short, ProtocolInterface *> &port_proto_map);
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
};
