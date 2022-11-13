# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 10:31:15 by chukim            #+#    #+#              #
#    Updated: 2022/08/04 20:51:54 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFTDIR = ./libft

# # 제 컴퓨터에서 실행하기 위한 경로입니다.
# INCLUDES =	-I /opt/homebrew/opt/readline/include \
# 			-I ./libft/ \
# 			-I .
# LIBS	 = 	-lreadline -L /opt/homebrew/opt/readline/lib/ \
# 			-lhistory -L /opt/homebrew/opt/readline/lib/ \
# 			-L ./libft/ -lft

INCLUDES =	-I ~/goinfre/.brew/opt/readline/include \
			-I ./libft/ \
			-I .
LIBS	 = 	-lreadline -L ~/goinfre/.brew/opt/readline/lib/ \
			-lhistory -L ~/goinfre/.brew/opt/readline/lib/ \
			-L ./libft/ -lft

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
AR = ar rcs
RM = rm -f

SRCS =	minishell.c \
		./builtins/echo.c \
		./builtins/export.c \
		./builtins/export_utils.c \
		./builtins/unset.c \
		./builtins/cd.c \
		./builtins/env.c \
		./builtins/pwd.c \
		./builtins/exit.c \
		./cmd/cmd.c \
		./cmd/cmd_utils.c \
		./env/env.c \
		./env/env_utils.c \
		./exec/exec.c \
		./exec/exec_utils.c \
		./exec/exec_wait.c \
		./exec/path_utils.c \
		./exec/pipe_utils.c \
		./exec/redirect_utils.c \
		./exec/run_utils.c \
		./exec/file_utils.c \
		./heredoc/heredoc.c \
		./heredoc/heredoc_utils.c \
		./heredoc/unlink.c \
		./parser/parse.c \
		./parser/parse_utils.c \
		./parser/token_utils.c \
		./parser/expand.c \
		./parser/expand_utils.c \
		./parser/big_utils.c \
		./utils/signal.c \
		./utils/error.c \
		./utils/free.c \
		./utils/print.c \

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

$(NAME) : $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $^ -o $@

all : $(NAME)

clean :
	make -C $(LIBFTDIR) clean
	$(RM) $(OBJS)

fclean : clean
	make -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re : clean all

.PHONY : all clean fclean re
