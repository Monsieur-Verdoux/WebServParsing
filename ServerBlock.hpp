/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerBlock.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:53:25 by akovalev          #+#    #+#             */
/*   Updated: 2024/10/25 20:54:27 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERBLOCK_HPP
#define SERVERBLOCK_HPP

#include <iostream>
#include <vector>
#include <map>
#include "LocationBlock.hpp"

class ServerBlock
{
private:
	std::vector<std::string> _server_names;
	int _listen; //port
	std::vector<LocationBlock> _locations;
	std::map<int, std::string> _error_pages;
	std::string _host; // IP address, e.g. 127.0.0.1
	std::string _proxy_pass; // maybe better in location block
	std::string _client_max_body_size; //maybe long?
	
	/* data */
public:
	ServerBlock(/* args */);
	~ServerBlock();
};


#endif