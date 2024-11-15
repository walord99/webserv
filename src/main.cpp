/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bplante <benplante99@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:52:27 by bplante           #+#    #+#             */
/*   Updated: 2024/11/15 01:26:45 by bplante          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.hpp"
#include "EpollWrapper.hpp"
#include "ServerSocket.hpp"
#include "Server.hpp"
#include "HttpFactory.hpp"

int main(void)
{
	std::map<const short, IProtocolFactory *> port_proto_map;
	port_proto_map.insert(std::make_pair(6969, new HttpFactory()));
	port_proto_map.insert(std::make_pair(6000, new HttpFactory()));
	//TODO add a protol factory for state based protocols
	//Move socket and epoll create to server run to be able to use settings functions
	try{
	Server serv(port_proto_map);
	serv.run();
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	for (std::map<const short, IProtocolFactory *>::iterator i = port_proto_map.begin(); i != port_proto_map.end(); i++)
		delete i->second;
}
