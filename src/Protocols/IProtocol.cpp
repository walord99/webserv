/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IProtocol.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:32:05 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 20:08:36 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IProtocol.hpp"

IProtocol::IProtocol(void)
{
}

IProtocol::~IProtocol(void)
{
}

IProtocol::IProtocol(const IProtocol &other)
{
	*this = other;
}

IProtocol &IProtocol::operator=(const IProtocol &other)
{
	if (this != &other)
	{
		
	}
	return *this;
}

