/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProtocolInterface.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:32:05 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 20:08:36 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ProtocolInterface.hpp"

ProtocolInterface::ProtocolInterface(void)
{
}

ProtocolInterface::~ProtocolInterface(void)
{
}

ProtocolInterface::ProtocolInterface(const ProtocolInterface &other)
{
	*this = other;
}

ProtocolInterface &ProtocolInterface::operator=(const ProtocolInterface &other)
{
	if (this != &other)
	{
		
	}
	return *this;
}
