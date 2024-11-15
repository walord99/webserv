/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IProtocol.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:45:30 by bplante           #+#    #+#             */
/*   Updated: 2024/11/13 20:13:45 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "global.hpp"
#include "queue"

class IProtocol
{
	private:

	public:
		enum processAction {
			INCOMPLETE_INPUT,
			NO_OUTPUT,
			CLOSE,
			OUTPUT
		};

		IProtocol(void);		
		IProtocol(const IProtocol &other);
		virtual ~IProtocol(void);
		IProtocol& operator=(const IProtocol& other);
		virtual processAction processInput(std::string &input, std::string **output_loc) = 0;
};