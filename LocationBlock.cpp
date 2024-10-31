/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationBlock.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:33:46 by akovalev          #+#    #+#             */
/*   Updated: 2024/10/31 18:16:39 by akovalev         ###   ########.fr       */
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

std::string LocationBlock::getAutoindex() const
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

std::string LocationBlock::getUploadStore() const
{
	return _upload_store;
}

std::string LocationBlock::getUploadMaxFileSize() const
{
	return _upload_max_file_size;
}

std::string LocationBlock::getUploadMaxFiles() const
{
	return _upload_max_files;
}

std::string LocationBlock::getUploadFileExtensions() const
{
	return _upload_file_extensions;
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

std::string LocationBlock::getClientMaxBodySize() const
{
	return _client_max_body_size;
}

std::vector<std::string> LocationBlock::getLimitExcept() const
{
	return _limit_except;
}

void LocationBlock::setClientMaxBodySize(const std::string& client_max_body_size)
{
	_client_max_body_size = client_max_body_size;
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
	_autoindex = autoindex;
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

void LocationBlock::setUploadStore(const std::string& upload_store)
{
	_upload_store = upload_store;
}

void LocationBlock::setUploadMaxFileSize(const std::string& upload_max_file_size)
{
	_upload_max_file_size = upload_max_file_size;
}

void LocationBlock::setUploadMaxFiles(const std::string& upload_max_files)
{
	_upload_max_files = upload_max_files;
}

void LocationBlock::setUploadFileExtensions(const std::string& upload_file_extensions)
{
	_upload_file_extensions = upload_file_extensions;
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
	if (!_location.empty())
		std::cout << "Location: " << _location << std::endl;
	if (!_root.empty())
	std::cout << "Root: " << _root << std::endl;
	if (!_index.empty())
	std::cout << "Index: " << _index << std::endl;
	if (!_autoindex.empty())
	std::cout << "Autoindex: " << _autoindex << std::endl;
	if (!_cgi_extension.empty())
	std::cout << "Cgi extension: " << _cgi_extension << std::endl;
	if (!_cgi_path.empty())
	std::cout << "Cgi path: " << _cgi_path << std::endl;
	if (!_upload_path.empty())
	std::cout << "Upload path: " << _upload_path << std::endl;
	if (!_upload_store.empty())
	std::cout << "Upload store: " << _upload_store << std::endl;
	if (!_upload_max_file_size.empty())
	std::cout << "Upload max file size: " << _upload_max_file_size << std::endl;
	if (!_upload_max_files.empty())
	std::cout << "Upload max files: " << _upload_max_files << std::endl;
	if (!_upload_file_extensions.empty())
	std::cout << "Upload file extensions: " << _upload_file_extensions << std::endl;
	if (!_proxy_pass.empty())
	std::cout << "Proxy pass: " << _proxy_pass << std::endl;
	if (!_return.empty())
	std::cout << "Return: " << _return << std::endl;
	if (!_alias.empty())
	std::cout << "Alias: " << _alias << std::endl;
	if (!_client_max_body_size.empty())
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