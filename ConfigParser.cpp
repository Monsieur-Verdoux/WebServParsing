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
		for (const Token& token : tokens) {
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

	std::vector<std::string> ConfigParser::parseServerBlock(std::vector<std::string>& tokens)
	{
		std::vector<std::string> server_block;
		tokens.shrink_to_fit();
		// parse server block
		// return server_block
		return server_block;
	}

	std::vector<std::string> ConfigParser::parseLocationBlock(std::vector<std::string>& tokens)
	{
		std::vector<std::string> location_block;
		tokens.shrink_to_fit();
		// parse location block
		// return location_block
		return location_block;
	}

	#include <algorithm>
	#include <sstream>

	void ConfigParser::tokenize(std::vector<Token>& tokens, std::ifstream& filepath)
	{
		std::vector<std::string> singleValueKeys = {
			"server_name", "location", "listen", "client_max_body_size", "proxy_pass", 
			"root", "index", "autoindex", "cgi_ext", "cgi_pass", "upload_path", 
			"upload_store", "upload_max_file_size", "server", "host", "alias", "return"
		};

		std::vector<std::string> multiValueKeys = {
			"limit_except", "error_page"
		};

		std::string word;
		while (filepath >> word)
		{
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
				if (filepath >> value)
				{
					if (value.back() == ';')
					{
						tokens.push_back(Token(TokenType::KEY_VALUE, word, (value.substr(0, value.size() - 1))));
						tokens.push_back(Token(TokenType::SEMICOLON, ";")); 
					}
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
				throw std::runtime_error("Unknown token");
			}
			
		}
	}

	std::vector<ServerBlock> ConfigParser::parseConfig(std::ifstream& filepath)
	{
		std::vector<ServerBlock> server_blocks;
		tokenize(_tokens, filepath);
		printTokens(_tokens);
		
		std::vector<std::string> server_block;
		std::vector<std::string> location_block;
		return server_blocks;
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