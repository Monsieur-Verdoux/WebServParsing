/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerBlock.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:53:25 by akovalev          #+#    #+#             */
/*   Updated: 2024/10/29 20:06:46 by akovalev         ###   ########.fr       */
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
	std::string _client_max_body_size; //maybe long?
public:
	ServerBlock(/* args */);
	~ServerBlock();
	std::vector<std::string> getServerNames() const;
	int getListen() const;
	std::vector<LocationBlock> getLocations() const;
	std::map<int, std::string> getErrorPages() const;
	std::string getHost() const;
	std::string getClientMaxBodySize() const;
	void setServerNames(const std::vector<std::string>& server_names);
	void setListen(int listen);
	void setLocations(const std::vector<LocationBlock>& locations);
	void setErrorPages(const std::map<int, std::string>& error_pages);
	void setHost(const std::string& host);
	void setClientMaxBodySize(const std::string& client_max_body_size);
};


#endif