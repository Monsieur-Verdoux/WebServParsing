/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:39:10 by akovalev          #+#    #+#             */
/*   Updated: 2024/10/29 20:13:31 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <iostream>
#include <vector>
#include <map>
#include "ServerBlock.hpp"
#include <fstream>

enum class TokenType {
	KEY_VALUE,
	KEY_MULTI_VALUE,
	OPEN,
	CLOSE,
	SEMICOLON,
	COMMENT,
	END_OF_FILE,
	UNKNOWN
};

struct Token {
	TokenType type;
	std::string key;
	std::vector<std::string> values;  

	// Constructor for KEY_VALUE tokens (single value)
	Token(TokenType t, const std::string& k, const std::string& v) 
		: type(t), key(k), values{v} {}

	// Constructor for KEY_MULTI_VALUE tokens (multiple values)
	Token(TokenType t, const std::string& k, const std::vector<std::string>& vals)
		: type(t), key(k), values(vals) {}

	// Constructor for other token types
	Token(TokenType t, const std::string& val) 
		: type(t), key(""), values{val} {}
};

class ConfigParser
{
private:
	std::vector<ServerBlock> _server_blocks;
	std::vector<Token> _tokens;
public:
	ConfigParser(/* args */);
	~ConfigParser();
	std::vector<ServerBlock> parseConfig(std::ifstream& filepath);
	std::vector<ServerBlock> getServerBlocks() const;
	void tokenize(std::vector<Token>& tokens, std::ifstream& filepath);
	void parseServerBlock(Token& token);
	void parseLocationBlock(Token& token);
	void printServerConfig();
};

#endif