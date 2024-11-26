/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:31:21 by bplante           #+#    #+#             */
/*   Updated: 2024/11/22 14:42:18 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connection.hpp"

Connection::Connection(ServerSocket &server, Epoll_Wrapper &epoll, IProtocol *proto) : Socket(epoll), _proto(proto)
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
	delete _proto;
}

int Connection::sendData(void)
{
	std::string *buff;
	if (_write_buffer.size() == 0)
	{
		if (_proto->output(&buff) != IProtocol::NO_OUTPUT)
		{
			_write_buffer.push(buff);
		}
		else
			return 0;
	}
	int string_len = _write_buffer.front()->size();
	int sent_len = send(_fd, _write_buffer.front()->c_str(), string_len, 0);
	// TODO handle sigpipe signal
	if (sent_len == -1)
		throw std::exception();
	if (sent_len != string_len)
	{
		_write_buffer.front()->replace(sent_len - 1, string_len, *_write_buffer.front(), string_len - sent_len);
		_write_buffer.front()->resize(string_len - sent_len);
	}
	else
	{
		delete _write_buffer.front();
		_write_buffer.pop();
	}
	return 0;
}

//TODO stop reading input if client isnt reading output, possible timout
int Connection::recieve(void)
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
	if (_proto->processInput(*buff) == IProtocol::CLOSE)
	{
		return -1;
		delete buff;
	}
	delete buff;
	return 0;
}
