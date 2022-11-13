# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by junkpark          #+#    #+#              #
#    Updated: 2022/06/25 09:36:33 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= server client

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

FT_DIR	= ./lib/libft
FT		= ft

INCLUDE = -I ./include
SRC = ./src

SERVER_SRC = \
	$(SRC)/server.c
CLIENT_SRC = \
	$(SRC)/client.c


SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

all: $(NAME)

server: $(SERVER_OBJ)
	$(MAKE) -C $(FT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(FT_DIR) -l $(FT)

client: $(CLIENT_OBJ)
	$(MAKE) -C $(FT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(FT_DIR) -l $(FT)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	$(MAKE) clean -C $(FT_DIR)
	rm -f $(SERVER_OBJ)
	rm -f $(CLIENT_OBJ)

fclean: clean
	$(MAKE) fclean -C $(FT_DIR)
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
