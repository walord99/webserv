/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:51:15 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 19:11:18 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "global.hpp"
#include "Epoll_Wrapper.hpp"
#include "Socket.hpp"
#include "Server_Socket.hpp"
#include "queue"
#include "ProtocolInterface.hpp"

class Connection : public Socket
{
public:
	std::queue<std::string> _read_buffer;
	std::queue<std::string> _write_buffer;
	ProtocolInterface *_proto;
	
public:
	using Socket::getFD;
	Connection(Server_Socket& server, Epoll_Wrapper& epoll, ProtocolInterface *proto);
	int send_msg(const std::string& msg);
	std::string *recieve(void);
	virtual ~Connection();

};
