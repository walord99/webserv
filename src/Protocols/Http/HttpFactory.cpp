/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpFactory.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:18:22 by bplante           #+#    #+#             */
/*   Updated: 2024/11/13 23:28:28 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpFactory.hpp"

HttpFactory::HttpFactory(void) : IProtocolFactory()
{
}

HttpFactory::~HttpFactory(void)
{
}

HttpFactory::HttpFactory(const HttpFactory &other) : IProtocolFactory()
{
	*this = other;
}

HttpFactory &HttpFactory::operator=(const HttpFactory &other)
{
	if (this != &other)
	{
	}
	return *this;
}

IProtocol *HttpFactory::createNew(void)
{
	return new HttpProtocol();
}