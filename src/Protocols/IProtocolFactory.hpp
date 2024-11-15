/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IProtocolFactory.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:14:33 by bplante           #+#    #+#             */
/*   Updated: 2024/11/13 23:26:04 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IProtocol.hpp"

class IProtocolFactory
{
	private:

	public:
		IProtocolFactory(void);
		IProtocolFactory(const  IProtocolFactory& other);
		virtual ~IProtocolFactory(void);
		IProtocolFactory& operator=(const IProtocolFactory& other);
		virtual IProtocol *createNew(void) = 0;
};