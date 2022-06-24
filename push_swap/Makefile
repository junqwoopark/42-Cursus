# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by junkpark          #+#    #+#              #
#    Updated: 2022/06/24 21:22:43 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= ./push_swap_visualizer/bin/push_swap ./push_swap
BONUS	= checker

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
	$(SRC_DIR)/deque_get.c \
	$(SRC_DIR)/deque_find_print.c \
	$(SRC_DIR)/deque_del.c \
	$(SRC_DIR)/push_swap_p.c \
	$(SRC_DIR)/push_swap_r.c \
	$(SRC_DIR)/push_swap_rr.c \
	$(SRC_DIR)/push_swap_s.c \
	$(SRC_DIR)/quick_sort.c \
	$(SRC_DIR)/check.c \
	$(SRC_DIR)/swap.c \
	$(SRC_DIR)/sort_under_five.c

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

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
