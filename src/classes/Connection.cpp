/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:31:21 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 20:26:57 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"

Connection::Connection(Server_Socket &server, Epoll_Wrapper &epoll, ProtocolInterface *proto) : Socket(epoll), _proto(proto)
{
	socklen_t sock_len = sizeof(struct sockaddr_in);
	_fd = accept(server.getFD(), (struct sockaddr *)&_addr, &sock_len);
	if (_fd == -1)
		throw new std::exception();
	register_to_epoll(EPOLLIN | EPOLLOUT);
	fcntl(_fd, F_SETFL, O_NONBLOCK);
}

Connection::~Connection()
{
}

int Connection::send_msg(const std::string &msg)
{
	int sent_len = send(_fd, msg.c_str(), msg.size(), 0);
	if (sent_len == -1)
		throw std::exception();
	return sent_len;
}

std::string *Connection::recieve(void)
{
	std::string *buff = new std::string(RECV_BUFF_SIZE, 0);

	int rec_len = recv(_fd, (void *)buff->data(), RECV_BUFF_SIZE, 0);
	// TODO: check error from recv
	if (rec_len == 0)
	{
		delete buff;
		throw std::exception();
	}
	buff->resize(rec_len);

	return buff;
}
