/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:52:04 by bplante           #+#    #+#             */
/*   Updated: 2024/11/15 00:42:34 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "global.hpp"
#include "EpollWrapper.hpp"

class Epoll_Wrapper;

class Socket
{
protected:
	short _port;
	int _fd;
	Epoll_Wrapper &_epoll;
	struct sockaddr_in _addr;
	

private:
	bool _is_watched;

public:
	Socket(Epoll_Wrapper& epoll);
	virtual ~Socket();
	int getFD(void) const;
	short getPort(void) const;

protected:
	void register_to_epoll(int events);
};
