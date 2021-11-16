# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 22:26:02 by junkpark          #+#    #+#              #
#    Updated: 2021/11/16 13:46:29 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
AFLAGS = rc
CFLAGS = -Wall -Wextra -Werror
SRCS = *.c
OBJECTS = $(SRCS:.c=.o)

all : $(NAME)
clean :
	rm -rf $(OBJECTS)
fclean : clean
	rm -rf $(NAME)
re : fclean all

$(NAME) : $(OBJECTS)
	ar $(AFLAGS) $@ $?
%.o : %.c
	$(CC) $(CFLAGS) -c $?
