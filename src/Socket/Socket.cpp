/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:31:11 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 20:41:04 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(Epoll_Wrapper &epoll) : _epoll(epoll)
{
}

void Socket::register_to_epoll(int events)
{
	_epoll.add(*this, events);
	_is_watched = true;
}

int Socket::getFD(void) const
{
	return _fd;
}

short Socket::getPort(void) const
{
	return _port;
}

Socket::~Socket()
{
	if (_is_watched)
		_epoll.remove(*this);
	close(_fd);
}
