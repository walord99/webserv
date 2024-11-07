/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_Socket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:31:13 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 20:39:17 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server_Socket.hpp"

Server_Socket::Server_Socket(const short port, Epoll_Wrapper& epoll) : Socket(epoll)
{
	_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (_fd < 0)
		throw Server_Exception("socket() error: " + strerror);
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = htons(port);

	int enable = 1;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
		throw Server_Exception("setsockopt() error: " + strerror);
	if (bind(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1)
		throw Server_Exception("bind() error: " + strerror);
	if (listen(_fd, 128) == -1)
		throw Server_Exception("listen() error: " + strerror);
	_port = port;
	register_to_epoll(EPOLLIN);
}

Server_Socket::~Server_Socket()
{
}