/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:51:19 by akovalev          #+#    #+#             */
/*   Updated: 2024/10/25 20:52:25 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

std::string tokenTypeToString(TokenType type) {
	switch (type) {
		case TokenType::BLOCK_OPEN: return "BLOCK_OPEN";
		case TokenType::BLOCK_CLOSE: return "BLOCK_CLOSE";
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
        "root", "index", "autoindex", "cgi_extension", "cgi_path", "upload_path", 
        "upload_store", "upload_max_file_size", "server"
    };

    std::vector<std::string> multiValueKeys = {
        "allowed_methods", "error_page"
    };

    std::string word;
    while (filepath >> word)
    {
        // Check for semicolon at the end of the word
        if (word.back() == ';')
        {
            // Remove the semicolon from the word and create a semicolon token
            std::string value = word.substr(0, word.size() - 1);
            tokens.push_back(Token(TokenType::KEY_VALUE, value));
            tokens.push_back(Token(TokenType::SEMICOLON, ";"));
            continue; // Move to the next word
        }

        // Handle single-value keys
        if (std::find(singleValueKeys.begin(), singleValueKeys.end(), word) != singleValueKeys.end())
        {
            std::string value;
            if (filepath >> value) // Read the next word
            {
                // Check if the next value is a semicolon
                if (value == ";") {
                    tokens.push_back(Token(TokenType::KEY_VALUE, word, "")); // Store the key with no value
                    tokens.push_back(Token(TokenType::SEMICOLON, value));
                } else {
                    tokens.push_back(Token(TokenType::KEY_VALUE, word, value));
                    if (value.back() == ';') // Check for semicolon in value
                    {
                        // Remove the semicolon and create a semicolon token
                        tokens.push_back(Token(TokenType::SEMICOLON, ";"));
                    } 
                    else
                    {
                        filepath.clear();
                        filepath.unget(); // Put the word back into the stream if not a semicolon
                    }
                }
            }
        }
        // Handle multi-value keys
        else if (std::find(multiValueKeys.begin(), multiValueKeys.end(), word) != multiValueKeys.end())
        {
            std::vector<std::string> values;
            std::string value;

            // Read multiple values until we hit a semicolon or opening brace
            while (filepath >> value && value != "{")
            {
                // Check for semicolon at the end of the value
                if (value.back() == ';') 
                {
                    // Remove the semicolon and store the value
                    values.push_back(value.substr(0, value.size() - 1));
                    tokens.push_back(Token(TokenType::KEY_MULTI_VALUE, word, values));
                    tokens.push_back(Token(TokenType::SEMICOLON, ";")); // Push the semicolon token
                    break; // End the reading for this multi-value key
                } 
                else 
                {
                    values.push_back(value);
                }
            }
            // Add the multi-value token without semicolon if we hit an opening brace
            if (value == "{") 
            {
                tokens.push_back(Token(TokenType::KEY_MULTI_VALUE, word, values));
                tokens.push_back(Token(TokenType::BLOCK_OPEN, value));
            }
        }
        // Handle block opening and closing
        else if (word == "{")
        {
            tokens.push_back(Token(TokenType::BLOCK_OPEN, word));
        }
        else if (word == "}")
        {
            tokens.push_back(Token(TokenType::BLOCK_CLOSE, word));
        }
        // Handle comments
        else if (word == "#")
        {
            tokens.push_back(Token(TokenType::COMMENT, word));
            std::string comment;
            std::getline(filepath, comment);
            tokens.push_back(Token(TokenType::COMMENT, comment));
        }
        // Handle end of file
        else if (word == "EOF")
        {
            tokens.push_back(Token(TokenType::END_OF_FILE, word));
        }
        // Handle unknown tokens
        else
        {
            tokens.push_back(Token(TokenType::UNKNOWN, word));
        }
    }
}





std::vector<ServerBlock> ConfigParser::parseConfig(std::ifstream& filepath)
{
	std::vector<ServerBlock> server_blocks;
	tokenize(_tokens, filepath);
	printTokens(_tokens);
	// for (const auto& token : _tokens) {
	// 	std::cout << token.value << std::endl;
	// }
	
	std::vector<std::string> server_block;
	std::vector<std::string> location_block;

	// for (size_t i = 0; i < _tokens.size(); i++)
	// {
	// 	if (_tokens[i].type == "server")
	// 	{
	// 		server_block = parseServerBlock(_tokens);
	// 	}
	// 	else if (_tokens[i].type == "location")
	// 	{
	// 		location_block = parseLocationBlock(_tokens);
	// 	}
	// }
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

	config.getServerBlocks() = config.parseConfig(file);
	
	return 0;
}