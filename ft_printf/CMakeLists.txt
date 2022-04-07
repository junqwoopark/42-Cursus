cmake_minimum_required(VERSION 3.20)
project(ft_printf C)

set(CMAKE_C_STANDARD 99)

add_executable(ft_printf main.c
        libft/ft_atoi.c
        libft/ft_bzero.c
        libft/ft_calloc.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_isprint.c
        libft/ft_itoa.c
        libft/ft_lstadd_back.c
        libft/ft_lstadd_front.c
        ft_lstclear.c
        ft_lstdelone.c
        ft_lstier.c
        ft_lstlast.c
        ft_lstmap.c
        ft_lstnew.c
        ft_lstsize.c
        ft_memchr.c
        ft_memcmp.c
        ft_memcpy.c
        ft_memmove.c
        ft_memset.c
        ft_putchar_fd.c
        ft_putendl_fd.c
        ft_putnbr_fd.c
        ft_putstr_fd.c
        ft_split.c
        ft_strchr.c
        ft_strdup.c
        ft_striteri.c
        ft_strjoin.c
        ft_strlcat.c
        ft_strlcpy.c
        ft_strlen.c
        ft_strmapi.c
        ft_strncmp.c
        ft_strnstr.c
        ft_strrchr.c
        ft_strtrim.c
        ft_substr.c
        ft_tolower.c
        ft_toupper.c
        libft.h)
