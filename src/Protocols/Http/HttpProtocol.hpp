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

#include "IProtocol.hpp"
#include "map"

class HttpProtocol : public IProtocol
{
	public:
		HttpProtocol();
		HttpProtocol(const  HttpProtocol& other);
		~HttpProtocol(void);
		HttpProtocol& operator=(const HttpProtocol& other);
		
		processAction processInput(std::string &input, std::string **output_loc);

	private: 
		bool isMessageComplete(std::queue<std::string> &input);
};