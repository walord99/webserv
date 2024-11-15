/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpFactory.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:16:00 by bplante           #+#    #+#             */
/*   Updated: 2024/11/13 20:23:52 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IProtocolFactory.hpp"
#include "HttpProtocol.hpp"

class HttpFactory : public IProtocolFactory
{
	private:
	public:
		HttpFactory(void);
		HttpFactory(const  HttpFactory& other);
		~HttpFactory(void);
		HttpFactory& operator=(const HttpFactory& other);
		IProtocol *createNew(void);
};