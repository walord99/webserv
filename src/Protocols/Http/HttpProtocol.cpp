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

HttpProtocol::HttpProtocol(void) : IProtocol()
{
}

HttpProtocol::~HttpProtocol(void)
{
}

HttpProtocol::HttpProtocol(const HttpProtocol &other) : IProtocol()
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

IProtocol::processAction HttpProtocol::processInput(std::string &input, std::string **output_loc)
{
	(void)input;
	// int method;
	// int major_version;
	// int minor_version;
	// std::map<std::string, std::string> header_fields;
	*output_loc = new std::string("HTTP/1.1 404 Not Found\r\nContent-Length: 4\r\n\r\ncum\n\r\n\r\n");
	return IProtocol::OUTPUT;
}
