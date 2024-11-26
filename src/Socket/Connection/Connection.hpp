/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:51:15 by bplante           #+#    #+#             */
/*   Updated: 2024/11/18 19:03:55 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "global.hpp"
#include "EpollWrapper.hpp"
#include "Socket.hpp"
#include "ServerSocket.hpp"
#include "queue"
#include "IProtocol.hpp"

class Connection : public Socket
{
private:
	std::queue<std::string *> _write_buffer;
	std::queue<std::string *> _read_buffer;
	IProtocol *_proto;
	
	
public:
	using Socket::getFD;
	Connection(ServerSocket& server, Epoll_Wrapper& epoll, IProtocol *proto);
	int sendData(void);
	int recieve(void);
	virtual ~Connection();

};
