/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ProtocolInterface.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:45:30 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 20:08:47 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "global.hpp"
#include "queue"

class ProtocolInterface
{
	private:

	public:
		ProtocolInterface(void);		
		ProtocolInterface(const ProtocolInterface &other);
		virtual ~ProtocolInterface(void);
		ProtocolInterface& operator=(const ProtocolInterface& other);
		virtual std::string *processInput(std::queue<std::string> &input) = 0;

};