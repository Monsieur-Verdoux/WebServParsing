/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationBlock.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:33:46 by akovalev          #+#    #+#             */
/*   Updated: 2024/10/30 19:47:52 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationBlock.hpp"

LocationBlock::LocationBlock(/* args */)
{
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
	_limit_except = values;
}
void LocationBlock::printLocationBlock()
{
	std::cout << "Location: " << _location << std::endl;
	std::cout << "Root: " << _root << std::endl;
	std::cout << "Index: " << _index << std::endl;
	std::cout << "Autoindex: " << _autoindex << std::endl;
	std::cout << "Cgi extension: " << _cgi_extension << std::endl;
	std::cout << "Cgi path: " << _cgi_path << std::endl;
	std::cout << "Upload path: " << _upload_path << std::endl;
	std::cout << "Upload store: " << _upload_store << std::endl;
	std::cout << "Upload max file size: " << _upload_max_file_size << std::endl;
	std::cout << "Upload max files: " << _upload_max_files << std::endl;
	std::cout << "Upload file extensions: " << _upload_file_extensions << std::endl;
	std::cout << "Proxy pass: " << _proxy_pass << std::endl;
	std::cout << "Error pages: " << std::endl;
	for (const auto& page : _error_pages)
	{
		std::cout << page.first << " " << page.second << std::endl;
	}
}