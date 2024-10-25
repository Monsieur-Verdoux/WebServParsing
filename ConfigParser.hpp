/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:39:10 by akovalev          #+#    #+#             */
/*   Updated: 2024/10/25 20:35:53 by akovalev         ###   ########.fr       */
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
	BLOCK_OPEN,    // '{'
	BLOCK_CLOSE,   // '}'
	SEMICOLON,     // ';'
	COMMENT,       // Comment lines
	END_OF_FILE,    // Indicates the end of the input
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
	std::vector<std::string> parseServerBlock(std::vector<std::string>& tokens);
	std::vector<std::string> parseLocationBlock(std::vector<std::string>& tokens);
};

#endif