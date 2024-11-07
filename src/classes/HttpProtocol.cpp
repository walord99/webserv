/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpProtocol.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:36:44 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 18:10:14 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpProtocol.hpp"

HttpProtocol::HttpProtocol(void) : ProtocolInterface()
{
}

HttpProtocol::~HttpProtocol(void)
{
}

HttpProtocol::HttpProtocol(const HttpProtocol &other) : ProtocolInterface()
{
	*this = other;
}

HttpProtocol &HttpProtocol::operator=(const HttpProtocol &other)
{
	if (this != &other)
	{
		
	}
	return *this;
}

std::string *HttpProtocol::processInput(std::queue<std::string> &input)
{
	(void)input;
	// int method;
	// int major_version;
	// int minor_version;
	// std::map<std::string, std::string> header_fields;
	std::string *ret = new std::string("HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
	return ret;
}
