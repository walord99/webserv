/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:51:42 by bplante           #+#    #+#             */
/*   Updated: 2024/11/04 23:15:42 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iostream"
#include "string"
#include "cstring"
#include "cstdlib"
#include "unistd.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "fcntl.h"
#include "netdb.h"
#include "sys/epoll.h"
#include "cstdio"
#include <vector>
#include "exception"
#include "cerrno"

#define RECV_BUFF_SIZE 4096 
#define strerror std::string(std::strerror(errno))
