# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/04/17 17:54:32 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libftprintf.a

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

AR		= ar
ARFLAGS = -rcs


FT_DIR	= ./lib/libft
LIBFT	= libft.a

INCLUDE = -I ./include

SRC_DIR = ./src
SRC = \
	$(SRC_DIR)/ft_printf.c \
	$(SRC_DIR)/ft_put_char.c \
	$(SRC_DIR)/ft_put_int_base.c \
	$(SRC_DIR)/ft_put_ptr.c \
	$(SRC_DIR)/ft_put_str.c \
	$(SRC_DIR)/ft_put_ul_base.c \
	$(SRC_DIR)/is_null_ptr.c \
	$(SRC_DIR)/parse_format.c \
	$(SRC_DIR)/print_format.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(FT_DIR)
	cp $(FT_DIR)/$(LIBFT) ./$(NAME)
	$(AR) $(ARFLAGS) $@ $^

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
