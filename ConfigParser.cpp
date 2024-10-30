	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2024/10/24 18:51:19 by akovalev          #+#    #+#             */
	/*   Updated: 2024/10/29 19:36:22 by akovalev         ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "ConfigParser.hpp"	

	ConfigParser::ConfigParser(/* args */)
	{
	}

	ConfigParser::~ConfigParser()
	{
	}

	std::vector<ServerBlock> ConfigParser::getServerBlocks() const
	{
		return _server_blocks;
	}

	std::string tokenTypeToString(TokenType type) {
		switch (type) {
			case TokenType::OPEN: return "OPEN";
			case TokenType::CLOSE: return "CLOSE";
			case TokenType::SEMICOLON: return "SEMICOLON";
			case TokenType::COMMENT: return "COMMENT";
			case TokenType::END_OF_FILE: return "END_OF_FILE";
			default: return "UNKNOWN";	
		}
	}

	void printTokens(const std::vector<Token>& tokens) {

		int i = 0;
		for (const Token& token : tokens) {

			std::cout << "Token " << i++ << ": ";
			if (token.type == TokenType::KEY_VALUE) {
				std::cout << "KEY_VALUE: " << token.key << " " << token.values[0] << std::endl;
			}
			else if (token.type == TokenType::KEY_MULTI_VALUE) {
				std::cout << "KEY_MULTI_VALUE: " << token.key << " ";
				for (const std::string& val : token.values) {
					std::cout << val << " ";
				}
				std::cout << std::endl;
			}
			else {
				std::cout << tokenTypeToString(token.type) << ": " << token.values[0] << std::endl;
			}
		}
	}


	void ConfigParser::unexpectedToken(size_t i)
	{
		std::cout << "Issue at token " << i	<< " " << tokenTypeToString(_tokens[i].type) << std::endl;
		printServerConfig();
		throw std::runtime_error("Unexpected token");
	}

	void ConfigParser::parseServerBlock(size_t index)
	{
		bool serverBlockOpened = false;
		_server_blocks.push_back(ServerBlock());
		std::cout << "Parsing server block at index " << index << std::endl;
		index++;
		if (_tokens[index].type != TokenType::OPEN)
			unexpectedToken(index);
		for (size_t i = index; i < _tokens.size(); i++)
		{
			if (_tokens[i].type == TokenType::OPEN)
			{
				if (serverBlockOpened)
					unexpectedToken(i);
				std::cout << "Opening server block" << std::endl;
				serverBlockOpened = true;
			}
			else if (_tokens[i].type == TokenType::CLOSE)
			{
				if (!serverBlockOpened)
					unexpectedToken(i);
				std::cout << "Closing server block" << std::endl;
				printServerConfig();
				break;
			}
			else if (_tokens[i].key == "server_name")
			{
				_server_blocks[_server_blocks.size() - 1].setServerName(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "listen")
			{
				_server_blocks[_server_blocks.size() - 1].setListen(std::stoi(_tokens[i].values[0]));
			}
			else if (_tokens[i].key == "client_max_body_size")
			{
				_server_blocks[_server_blocks.size() - 1].setClientMaxBodySize(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "host")
			{
				_server_blocks[_server_blocks.size() - 1].setHost(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "error_page")
			{
				_server_blocks[_server_blocks.size() - 1].setErrorPage(std::stoi(_tokens[i].values[0]), _tokens[i].values[1]);
			}
			else if (_tokens[i].key == "location")
			{
				parseLocationBlock(i);
			}
			else if (_tokens[i].type == TokenType::COMMENT)
			{
				continue;
			}
			else if (_tokens[i].type == TokenType::SEMICOLON)
			{
				if (_tokens[i - 1].type != TokenType::KEY_VALUE && _tokens[i - 1].type != TokenType::KEY_MULTI_VALUE)
					unexpectedToken	(i);
			}
			else
			{
				unexpectedToken(i);
			}
		}
	}

	void ConfigParser::parseLocationBlock(size_t index)
	{
		bool locationBlockOpened = false;

		if ((_tokens[index].values[0] == ""))
		{
			std::cout << "Location block is empty" << std::endl;
			unexpectedToken(index);
		}
		else if (_tokens[index].values[0].back() != '/')
		{
			std::cout << "Location block does not end with /" << std::endl;
			unexpectedToken(index);
		}
		index++;
		if (_tokens[index].type != TokenType::OPEN)
			unexpectedToken(index);
		for (size_t i = index; i < _tokens.size(); i++)
		{
			std::cout << "We are at " << i << std::endl;
			if (_tokens[i].type == TokenType::OPEN)
			{
				if (locationBlockOpened)
					unexpectedToken(i);
				std::cout << "Opening location block" << std::endl;
				locationBlockOpened = true;
			}
			else if (_tokens[i].type == TokenType::CLOSE)
			{
				if (!locationBlockOpened)
					unexpectedToken(i);
				std::cout << "Closing location block" << std::endl;
				break;
			}
			else if (_tokens[i].key == "root")
			{
				_server_blocks[_server_blocks.size() - 1].getLocations().back().setRoot(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "index")
			{
				_server_blocks[_server_blocks.size() - 1].getLocations().back().setIndex(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "autoindex")
			{
				_server_blocks[_server_blocks.size() - 1].getLocations().back().setAutoindex(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "cgi_pass")
			{
				_server_blocks[_server_blocks.size() - 1].getLocations().back().setCgiPath(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "upload_path")
			{
				_server_blocks[_server_blocks.size() - 1].getLocations().back().setUploadPath(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "upload_store")
			{
				_server_blocks[_server_blocks.size() - 1].getLocations().back().setUploadStore(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "upload_max_file_size")
			{
				_server_blocks[_server_blocks.size() - 1].getLocations().back().setUploadMaxFileSize(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "upload_max_files")
			{
				_server_blocks[_server_blocks.size() - 1].getLocations().back().setUploadMaxFiles(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "upload_file_extensions")
			{
				_server_blocks[_server_blocks.size() - 1].getLocations().back().setUploadFileExtensions(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "proxy_pass")
			{
				_server_blocks[_server_blocks.size() - 1].getLocations().back().setProxyPass(_tokens[i].values[0]);
			}
			else if (_tokens[i].key == "error_page")
			{
				_server_blocks[_server_blocks.size() - 1].getLocations().back().setErrorPage(std::stoi(_tokens[i].values[0]), _tokens[i].values[1]);
			}
			else if (_tokens[i].key == "cgi_ext")
				{
					_server_blocks[_server_blocks.size() - 1].getLocations().back().setCgiExtension(_tokens[i].values[0]);
				}
			else if (_tokens[i].key == "limit_except")
			{
				std::vector<std::string> values;
				for (size_t j = 0; j < _tokens[i].values.size(); j++)
				{
					values.push_back(_tokens[i].values[j]);
				}
				_server_blocks[_server_blocks.size() - 1].getLocations().back().setLimitExcept(values);
			}
			else if
			(_tokens[i].type == TokenType::COMMENT)
			{
				continue;
			}
			else if (_tokens[i].type == TokenType::SEMICOLON)
			{
				if (_tokens[i - 1].type != TokenType::KEY_VALUE && _tokens[i - 1].type != TokenType::KEY_MULTI_VALUE)
					unexpectedToken(i);
			}
			else
			{
				unexpectedToken(i);
			}
		return;
	}
	}



	void ConfigParser::tokenize(std::vector<Token>& tokens, std::ifstream& filepath)
	{
		std::vector<std::string> singleValueKeys = {
			"server_name", "location", "listen", "client_max_body_size", "proxy_pass", 
			"root", "index", "autoindex", "cgi_pass", "upload_path", 
			"upload_store", "upload_max_file_size", "server", "host", "alias", "return"
		};

		std::vector<std::string> multiValueKeys = {
			"limit_except", "cgi_ext", "error_page"
		};

		std::string word;
		while (filepath >> word)
		{
			//std::cout << word << std::endl;
			if (word  == "{")
			{
				tokens.push_back(Token(TokenType::OPEN, word));
			}
			else if (word == "}")
			{
				tokens.push_back(Token(TokenType::CLOSE, word));
			}
			else if (word == ";")
			{
				tokens.push_back(Token(TokenType::SEMICOLON, word));
			}
			else if (word == "#" || word.front() == '#')
			{
				if (word.front() == '#')
				{	
					std::string comment;
					std::getline(filepath, comment);
					tokens.push_back(Token(TokenType::COMMENT, (word + comment)));
				}
				else {
					tokens.push_back(Token(TokenType::COMMENT, word));
					std::string comment;
					std::getline(filepath, comment);
					tokens.push_back(Token(TokenType::COMMENT, comment));
				}
			}
			else if (word == "EOF")
			{
				tokens.push_back(Token(TokenType::END_OF_FILE, word));
			}
			else if (std::find(singleValueKeys.begin(), singleValueKeys.end(), word) != singleValueKeys.end())
			{
				std::string value;
				if (word == "server")
				{
					tokens.push_back(Token(TokenType::KEY_VALUE, word, ""));
				}
				else if (filepath >> value)
				{
					if (value.back() == ';')
					{
						tokens.push_back(Token(TokenType::KEY_VALUE, word, (value.substr(0, value.size() - 1))));
						tokens.push_back(Token(TokenType::SEMICOLON, ";")); 
					}
					else if (word == "location")
					{
						tokens.push_back(Token(TokenType::KEY_VALUE, word, value));
					}
					else
						unexpectedToken(tokens.size());
				}
			}
			else if (std::find(multiValueKeys.begin(), multiValueKeys.end(), word) != multiValueKeys.end())
			{
				std::vector<std::string> values;
				std::string value;
				while (filepath >> value && value != "{")
				{
					if (value.back() == ';')
					{
						values.push_back(value.substr(0, value.size() - 1));
						tokens.push_back(Token(TokenType::KEY_MULTI_VALUE, word, values));
						tokens.push_back(Token(TokenType::SEMICOLON, ";"));
						break;
					}
					else
					{
						values.push_back(value);
					}
				}
				if (value == "{")
				{
					tokens.push_back(Token(TokenType::KEY_MULTI_VALUE, word, values));
					tokens.push_back(Token(TokenType::OPEN, value));
				}
			}		
			else
			{
				tokens.push_back(Token(TokenType::UNKNOWN, word));
				printTokens(tokens);
				throw std::runtime_error("Unknown token");
			}
			
		}
	}

	std::vector<ServerBlock> ConfigParser::parseConfig(std::ifstream& filepath)
	{
		tokenize(_tokens, filepath);
		printTokens(_tokens);
	
		for (size_t i = 0; i < _tokens.size(); i++)
		{
			std::cout << "We are at " << _tokens[i].key << std::endl;
			while (_tokens[i].type == TokenType::COMMENT)
				i++;
			if (_tokens[i].key != "server")
			{
				std::cout << "Issue at token " << i	<< " " << tokenTypeToString(_tokens[i].type) << std::endl;
				throw std::runtime_error("Expected 'server' block");
			}
			else
				parseServerBlock(i);
		}
		return _server_blocks;
	}

	void ConfigParser::printServerConfig()
	{
		for (const ServerBlock& server : _server_blocks)
		{
			std::cout << "Server names: ";
			for (const std::string& name : server.getServerNames())
			{
				std::cout << name << " ";
			}
			std::cout << std::endl;
			std::cout << "Listen: " << server.getListen() << std::endl;
			std::cout << "Client max body size: " << server.getClientMaxBodySize() << std::endl;
			std::cout << "Host: " << server.getHost() << std::endl;
			std::cout << "Error pages: " << std::endl;
			for (const auto& page : server.getErrorPages())
			{
				std::cout << page.first << " " << page.second << " " << std::endl;
			}

		}
	}

	int main()
	{
		ConfigParser config;
		std::ifstream file("config/webserv.conf");;
		if(!file.is_open())
		{
			std::cerr << "Error: could not open file" << std::endl;
			return 1;
		}
		try
		{
			config.getServerBlocks() = config.parseConfig(file);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		return 0;
	}