/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EpollWrapper.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:51:19 by bplante           #+#    #+#             */
/*   Updated: 2024/11/15 00:42:37 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "global.hpp"
#include "Socket.hpp"

class Socket;

class Epoll_Wrapper
{
private:
	int _fd;
	unsigned int _watch_count;
	std::vector<struct epoll_event> _events;

public:
	Epoll_Wrapper(void);
	void add(Socket &sock, int events);
	void remove(Socket &sock);
	const std::vector<struct epoll_event> &wait(void);
	~Epoll_Wrapper(void);

	class Epoll_Exception : public std::exception
	{
	private:
		std::string _message;

	public:
		Epoll_Exception(const std::string &msg) : _message(msg) {};
		const char *what(void) const throw()
		{
			return _message.c_str();
		}
		virtual ~Epoll_Exception(void) throw() {}
	};
};
