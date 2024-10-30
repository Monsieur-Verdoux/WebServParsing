/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationBlock.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:46:15 by akovalev          #+#    #+#             */
/*   Updated: 2024/10/30 19:47:49 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONBLOCK_HPP
#define LOCATIONBLOCK_HPP

#include <iostream>
#include <vector>
#include <map>

class LocationBlock
{
	private:
		std::string _location; // /path/to/resource
		std::string _root; // /var/www/html
		std::string _index; // index.html
		std::string _autoindex; // on | off
		std::string _cgi_extension;	// .php, .py, .pl, .rb
		std::string _cgi_path; // /usr/bin/php-cgi
		std::string _upload_path; // /var/www/html/uploads
		std::string _upload_store; // on | off
		std::string _upload_max_file_size; // 1M
		std::string _upload_max_files; // 10
		std::string _upload_file_extensions; // .jpg, .jpeg, .png, .gif
		std::string _proxy_pass; // http://
		std::map<int, std::string> _error_pages;
		std::vector<std::string> _limit_except;
	public:
		LocationBlock(/* args */);
		~LocationBlock();
		std::string getLocation() const;
		std::string getRoot() const;
		std::string getIndex() const;
		std::string getAutoindex() const;
		std::string getCgiExtension() const;
		std::string getCgiPath() const;
		std::string getUploadPath() const;
		std::string getUploadStore() const;
		std::string getUploadMaxFileSize() const;
		std::string getUploadMaxFiles() const;
		std::string getUploadFileExtensions() const;
		std::string getProxyPass() const;
		std::map<int, std::string> getErrorPages() const;
		void setLocation(const std::string& location);
		void setRoot(const std::string& root);
		void setIndex(const std::string& index);
		void setAutoindex(const std::string& autoindex);
		void setCgiExtension(const std::string& cgi_extension);
		void setCgiPath(const std::string& cgi_path);
		void setUploadPath(const std::string& upload_path);
		void setUploadStore(const std::string& upload_store);
		void setUploadMaxFileSize(const std::string& upload_max_file_size);
		void setUploadMaxFiles(const std::string& upload_max_files);
		void setUploadFileExtensions(const std::string& upload_file_extensions);
		void setProxyPass(const std::string& proxy_pass);
		void setErrorPage(int code, const std::string& page);
		void printLocationBlock();
		void setLimitExcept(const std::vector<std::string>& values);
};

#endif