# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/04/20 01:00:13 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= so_long

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
MFLAGS	= -framework OpenGL -framework AppKit

FT_DIR	= ./lib/libft
GNL_DIR	= ./lib/libgnl
MLX_DIR	= ./lib/minilibx_opengl
FT		= ft
GNL		= gnl
MLX 	= mlx

INCLUDE = -I ./include

SRC_DIR = ./src
SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/check.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/map.c \
	$(SRC_DIR)/player.c \
	$(SRC_DIR)/utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(FT_DIR)
	$(MAKE) -C $(GNL_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(FT_DIR) -l $(FT) \
		-L$(GNL_DIR) -l $(GNL) \
		-L$(MLX_DIR) -l $(MLX) $(MFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	$(MAKE) clean -C $(FT_DIR)
	$(MAKE) clean -C $(GNL_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(FT_DIR)
	$(MAKE) fclean -C $(GNL_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
