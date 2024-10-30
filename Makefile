# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalev <akovalev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/30 14:04:58 by akovalev          #+#    #+#              #
#    Updated: 2024/10/30 19:38:47 by akovalev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ConfigParser
CFLAGS := 
SRC := ConfigParser.cpp ServerBlock.cpp LocationBlock.cpp
OBJ := $(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	@c++ $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@c++ $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

cl: all clean

.PHONY: all, clean, fclean, re