/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpProtocol.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:28:42 by bplante           #+#    #+#             */
/*   Updated: 2024/11/06 18:18:13 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ProtocolInterface.hpp"
#include "map"

class HttpProtocol : public ProtocolInterface
{
	public:
		HttpProtocol();
		HttpProtocol(const  HttpProtocol& other);
		~HttpProtocol(void);
		HttpProtocol& operator=(const HttpProtocol& other);
		
		std::string *processInput(std::queue<std::string> &input);

	private: 
		bool isMessageComplete(std::queue<std::string> &input);
};