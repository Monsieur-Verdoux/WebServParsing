/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerBlock.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:53:25 by akovalev          #+#    #+#             */
/*   Updated: 2024/11/07 22:15:03 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERBLOCK_HPP
#define SERVERBLOCK_HPP

#include <iostream>
#include <vector>
#include <map>
#include "LocationBlock.hpp"
#include <stdint.h>
#include <string>
#include <algorithm>

class ServerBlock
{
private:
	std::vector<std::string> _server_names;
	uint16_t _listen; //port, range 1-65535
	std::vector<LocationBlock> _locations;
	std::map<int, std::string> _error_pages;
	std::string _host; // IP address, e.g. 127.0.0.1
	size_t _client_max_body_size; // size in bytes, needs to be converted if in human-readable format
public:
	ServerBlock(/* args */);
	~ServerBlock();
	std::vector<std::string> getServerNames() const;
	int getListen() const;
	std::vector<LocationBlock>& getLocations();	
	std::map<int, std::string> getErrorPages() const;
	std::string getHost() const;
	size_t getClientMaxBodySize() const;
	void setServerName(const std::string& server_name);
	void setListen(int listen);
	void setLocations(const std::vector<LocationBlock>& locations);
	void setErrorPage(int code, const std::string& page);
	void setHost(const std::string& host);
	void setClientMaxBodySize(std::string& client_max_body_size);
};


#endif