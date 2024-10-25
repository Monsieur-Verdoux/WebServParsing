/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationBlock.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:46:15 by akovalev          #+#    #+#             */
/*   Updated: 2024/10/24 20:01:42 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONBLOCK_HPP
#define LOCATIONBLOCK_HPP

#include <iostream>
#include <vector>
#include <map>

class LocationBlock
{
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
};

#endif