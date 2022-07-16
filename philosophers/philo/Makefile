# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/07/16 21:12:55 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
INCLUDE = -I ./include

SRC_DIR = ./src
SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/philosophers.c \
	$(SRC_DIR)/observing.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
