/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerBlock.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:45:23 by akovalev          #+#    #+#             */
/*   Updated: 2024/10/29 20:09:12 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerBlock.hpp"

ServerBlock::ServerBlock(/* args */)
{
}

ServerBlock::~ServerBlock()
{
}

std::vector<std::string> ServerBlock::getServerNames() const
{
	return _server_names;
}

int ServerBlock::getListen() const
{
	return _listen;
}

std::vector<LocationBlock> ServerBlock::getLocations() const
{
	return _locations;
}

std::map<int, std::string> ServerBlock::getErrorPages() const
{
	return _error_pages;
}

std::string ServerBlock::getHost() const
{
	return _host;
}

std::string ServerBlock::getClientMaxBodySize() const
{
	return _client_max_body_size;
}

void ServerBlock::setServerNames(const std::vector<std::string>& server_names)
{
	_server_names = server_names;
}

void ServerBlock::setListen(int listen)
{
	_listen = listen;
}

void ServerBlock::setLocations(const std::vector<LocationBlock>& locations)
{
	_locations = locations;
}

void ServerBlock::setErrorPages(const std::map<int, std::string>& error_pages)
{
	_error_pages = error_pages;
}

void ServerBlock::setHost(const std::string& host)
{
	_host = host;
}

void ServerBlock::setClientMaxBodySize(const std::string& client_max_body_size)
{
	_client_max_body_size = client_max_body_size;
}
