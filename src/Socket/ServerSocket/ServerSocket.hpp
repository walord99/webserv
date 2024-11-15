/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:51:50 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 18:57:27 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Socket.hpp"
#include "global.hpp"

class ServerSocket : public Socket
{
public:
	using Socket::getFD;
	ServerSocket(const short port, Epoll_Wrapper& epoll);
	~ServerSocket();

	class Server_Exception : std::exception{
		private:
			std::string _msg;
		public:
			Server_Exception(const std::string &msg) : _msg(msg) {};
			const char* what(void) const throw() {
				return _msg.c_str();
			};
			virtual ~Server_Exception(void) throw() {};
	};
};
