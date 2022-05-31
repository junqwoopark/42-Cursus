# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/05/31 20:43:09 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= server client

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

FT_DIR	= ./lib/libft
GNL_DIR	= ./lib/libgnl
FT		= ft
GNL		= gnl

INCLUDE = -I ./include

SERVER_SRC_DIR = ./server_src
SERVER_SRC = \
	$(SERVER_SRC_DIR)/server_main.c \

CLIENT_SRC_DIR = ./client_src
CLIENT_SRC = \
	$(CLIENT_SRC_DIR)/client_main.c


SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

all: $(NAME)

server: $(SERVER_OBJ)
	$(MAKE) -C $(FT_DIR)
	$(MAKE) -C $(GNL_DIR)
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(FT_DIR) -l $(FT) \
		-L$(GNL_DIR) -l $(GNL)

client: $(CLIENT_OBJ)
	$(MAKE) -C $(FT_DIR)
	$(MAKE) -C $(GNL_DIR)
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(FT_DIR) -l $(FT) \
		-L$(GNL_DIR) -l $(GNL) \

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	$(MAKE) clean -C $(FT_DIR)
	$(MAKE) clean -C $(GNL_DIR)
	rm -f $(SERVER_OBJ)
	rm -f $(CLIENT_OBJ)

fclean: clean
	$(MAKE) fclean -C $(FT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
