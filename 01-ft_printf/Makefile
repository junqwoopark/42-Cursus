# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 17:48:50 by junkpark          #+#    #+#              #
#    Updated: 2022/04/07 18:10:36 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror
SRC = \
ft_printf.c \
ft_printf_utils.c \
ft_printf_print_str.c \
ft_printf_print_nums.c
OBJ = $(SRC:.c=.o)
INCLUDES = -I ./includes

all : $(NAME)

$(NAME) : $(OBJ) libft
	cp libft/libft.a ./$(NAME)
	ar rsc $(NAME) $(OBJ)

%.o: %.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)

# libft compile
libft :
	@$(MAKE) -C ./libft all

clean :
	@$(MAKE) -C ./libft clean
	@rm -rf $(OBJ)
fclean : clean
	@$(MAKE) -C ./libft fclean
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re libft

# CC = gcc
# CFLAGS = -Wall -Wextra -Werror
# NAME = libftprintf.a
# HEADER = ft_printf.h

# LIBFT = \
# ./libft/ft_atoi.c \
# ./libft/ft_bzero.c \
# ./libft/libft/ft_calloc.c \
# ./libft/ft_isalnum.c \
# ./libft/ft_isalpha.c \
# ./libft/ft_isascii.c \
# ./libft/ft_isdigit.c \
# ./libft/ft_isprint.c \
# ./libft/ft_itoa.c \
# ./libft/ft_memchr.c \
# ./libft/ft_memcmp.c \
# ./libft/ft_memcpy.c \
# ./libft/ft_memmove.c \
# ./libft/ft_memset.c \
# ./libft/ft_putchar_fd.c \
# ./libft/ft_putendl_fd.c \
# ./libft/ft_putnbr_fd.c \
# ./libft/ft_putstr_fd.c \
# ./libft/ft_split.c \
# ./libft/ft_strchr.c \
# ./libft/ft_strdup.c \
# ./libft/ft_strjoin.c \
# ./libft/ft_strlcat.c \
# ./libft/ft_strlcpy.c \
# ./libft/ft_strlen.c \
# ./libft/ft_strmapi.c \
# ./libft/ft_strncmp.c \
# ./libft/ft_strnstr.c \
# ./libft/ft_strrchr.c \
# ./libft/ft_strtrim.c \
# ./libft/ft_substr.c \
# ./libft/ft_tolower.c \
# ./libft/ft_striteri.c \
# ./libft/ft_toupper.c

# SRCS = \
# ./ft_printf_print_nums.c \
# ./ft_printf_print_str.c \
# ./ft_printf_utils.c \
# ./ft_printf.c

# OBJS = $(SRCS:.c=.o)
# BONUS_OBJS = $(BONUSES:.c=.o)

# all: $(NAME)

# $(NAME): $(OBJS)

# bonus: $(OBJS) $(BONUS_OBJS)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c -o $@ $^
# 	ar crsu $(NAME) $@

# clean:
# 	rm -f $(OBJS) $(BONUS_OBJS)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all bonus clean fclean re
