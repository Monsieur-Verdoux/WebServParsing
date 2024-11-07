/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationBlock.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:33:46 by akovalev          #+#    #+#             */
/*   Updated: 2024/11/07 22:31:50 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationBlock.hpp"

LocationBlock::LocationBlock(/* args */)
{
}

LocationBlock::LocationBlock(std::string location)
{
	_location = location;
}

LocationBlock::~LocationBlock()
{
}

std::string LocationBlock::getLocation() const
{
	return _location;
}

std::string LocationBlock::getRoot() const
{
	return _root;
}

std::string LocationBlock::getIndex() const
{
	return _index;
}

bool LocationBlock::getAutoindex() const
{
	return _autoindex;
}

std::string LocationBlock::getCgiExtension() const
{
	return _cgi_extension;
}

std::string LocationBlock::getCgiPath() const
{
	return _cgi_path;
}

std::string LocationBlock::getUploadPath() const
{
	return _upload_path;
}

std::string LocationBlock::getProxyPass() const
{
	return _proxy_pass;
}

std::map<int, std::string> LocationBlock::getErrorPages() const
{
	return _error_pages;
}

std::string LocationBlock::getReturn() const
{
	return _return;
}

std::string LocationBlock::getAlias() const
{
	return _alias;
}	

size_t LocationBlock::getClientMaxBodySize() const
{
	return _client_max_body_size;
}

std::vector<std::string> LocationBlock::getLimitExcept() const
{
	return _limit_except;
}

void LocationBlock::setClientMaxBodySize(std::string& client_max_body_size)
{
	if (client_max_body_size.empty() || !std::all_of(client_max_body_size.begin(), client_max_body_size.end(), ::isdigit)) 
		throw std::invalid_argument("incorrent client_max_body_size format");
	else
		_client_max_body_size = std::stoi(client_max_body_size);
}

void LocationBlock::setAlias(const std::string& alias)
{
	_alias = alias;
}

void LocationBlock::setReturn(const std::string& return_val)
{
	_return = return_val;
}

void LocationBlock::setLocation(const std::string& location)
{
	_location = location;

}

void LocationBlock::setRoot(const std::string& root)
{
	_root = root;
}

void LocationBlock::setIndex(const std::string& index)
{
	_index = index;
}

void LocationBlock::setAutoindex(const std::string& autoindex)
{
	if (autoindex == "on")
		_autoindex = true;
	else if (autoindex == "off")
		_autoindex = false;
	else
		throw std::invalid_argument("incorrect autoindex format");
}

void LocationBlock::setCgiExtension(const std::string& cgi_extension)
{
	_cgi_extension = cgi_extension;
}

void LocationBlock::setCgiPath(const std::string& cgi_path)
{
	_cgi_path = cgi_path;
}

void LocationBlock::setUploadPath(const std::string& upload_path)
{
	_upload_path = upload_path;
}

void LocationBlock::setProxyPass(const std::string& proxy_pass)
{
	_proxy_pass = proxy_pass;
}	
void LocationBlock::setErrorPage(int code, const std::string& page)
{
	_error_pages[code] = page;
}

void LocationBlock::setLimitExcept(const std::vector<std::string>& values)
{
	for (size_t i = 0; i < values.size(); i++)
	{
		_limit_except.push_back(values[i]);
	}
}
void LocationBlock::printLocationBlock()
{
	std::cout << "--------------------------------" << std::endl;
	
	if (_autoindex)
	std::cout << "Autoindex: on" << std::endl;
	else
	std::cout << "Autoindex: off" << std::endl;
	
	if (!_location.empty())
		std::cout << "Location: " << _location << std::endl;
	if (!_root.empty())
	std::cout << "Root: " << _root << std::endl;
	if (!_index.empty())
	std::cout << "Index: " << _index << std::endl;

	if (!_cgi_extension.empty())
	std::cout << "Cgi extension: " << _cgi_extension << std::endl;
	if (!_cgi_path.empty())
	std::cout << "Cgi path: " << _cgi_path << std::endl;
	if (!_upload_path.empty())
	std::cout << "Upload path: " << _upload_path << std::endl;

	if (!_proxy_pass.empty())
	std::cout << "Proxy pass: " << _proxy_pass << std::endl;
	if (!_return.empty())
	std::cout << "Return: " << _return << std::endl;
	if (!_alias.empty())
	std::cout << "Alias: " << _alias << std::endl;
	if (_client_max_body_size)
	std::cout << "Client max body size: " << _client_max_body_size << std::endl;
	if (!_limit_except.empty())
	{
		std::cout << "Limit except: ";
		for (const std::string& val : _limit_except)
		{
			std::cout << val << " ";
		}
		std::cout << std::endl;
	}
	if (!_error_pages.empty())
	{
		std::cout << "Error pages: " << std::endl;
		for (const auto& page : _error_pages)
		{
			std::cout << page.first << " " << page.second << std::endl;
		}
	}
}