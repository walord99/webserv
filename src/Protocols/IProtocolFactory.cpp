/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IProtocolFactory.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:15:41 by bplante           #+#    #+#             */
/*   Updated: 2024/11/13 23:27:13 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IProtocolFactory.hpp"

IProtocolFactory::IProtocolFactory(void)
{
}

IProtocolFactory::~IProtocolFactory(void)
{
}

IProtocolFactory::IProtocolFactory(const IProtocolFactory &other)
{
	*this = other;
}

IProtocolFactory &IProtocolFactory::operator=(const IProtocolFactory &other)
{
	if (this != &other)
	{
		
	}
	return *this;
}
