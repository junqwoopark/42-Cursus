# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/06/02 14:55:05 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

INCLUDE = -I ./include

SRC_DIR = ./src
SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/utils.c \

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
