/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Epoll_Wrapper.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:31:18 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 17:20:26 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Epoll_Wrapper.hpp"

Epoll_Wrapper::Epoll_Wrapper(void) : _watch_count(0)
{
	_fd = epoll_create(1);
	if (_fd == -1)
		throw Epoll_Exception("epoll_create() error: " + strerror);
	_events.reserve(5);
}

void Epoll_Wrapper::add(Socket& sock, int events)
{
	struct epoll_event ep;
	ep.data.ptr = &sock;
	ep.events = events;
	if (epoll_ctl(_fd, EPOLL_CTL_ADD, sock.getFD(), &ep) == -1)
		throw Epoll_Exception("epoll_ctl() add error: " + strerror);
	_watch_count++;
}

void Epoll_Wrapper::remove(Socket &sock)
{
	if (epoll_ctl(_fd, EPOLL_CTL_DEL, sock.getFD(), NULL) == -1)
		throw Epoll_Exception("epoll_ctl() del error: " + strerror);
	_watch_count--;
}

const std::vector<struct epoll_event>& Epoll_Wrapper::wait(void)
{
	_events.resize(_watch_count);
	int event_count = epoll_wait(_fd, &_events[0], _watch_count, -1);
	if (event_count == -1)
		throw Epoll_Exception("epoll_wait() error: " + strerror);
	_events.resize(event_count);
	return _events;
}

Epoll_Wrapper::~Epoll_Wrapper(void)
{
	close(_fd);
}