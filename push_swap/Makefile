# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/05/07 20:08:13 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= push_swap

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g

FT_DIR	= ./lib/libft
FT		= ft

INCLUDE = -I ./include

SRC_DIR = ./src
SRC = \
	main.c \
	$(SRC_DIR)/deque_pop.c \
	$(SRC_DIR)/deque_push.c \
	$(SRC_DIR)/deque_utils.c \
	$(SRC_DIR)/deque_find_print_data.c \
	$(SRC_DIR)/push_swap_p.c \
	$(SRC_DIR)/push_swap_r.c \
	$(SRC_DIR)/push_swap_rr.c \
	$(SRC_DIR)/push_swap_s.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(FT_DIR)
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(FT_DIR) -l $(FT)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	$(MAKE) clean -C $(FT_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(FT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
