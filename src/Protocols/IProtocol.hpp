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
			CLOSE,
			CONTINUE,
		};

		enum outputAction {
			MORE_DATA,
			OVER,
			NOT_READY,
			NO_OUTPUT
		};

		IProtocol(void);		
		IProtocol(const IProtocol &other);
		virtual ~IProtocol(void);
		IProtocol& operator=(const IProtocol& other);
		virtual processAction processInput(std::string &input) = 0;
		/**
		 * @brief tells the protocol that output is ready and to form a response
		 * 
		 * @param out_loc location to store the allocated string pointer into
		 * @param recommended_size use recommended size for big files to not clog memory
		 * @return outputAction 
		 */
		virtual outputAction output(std::string **out_loc) = 0;
};