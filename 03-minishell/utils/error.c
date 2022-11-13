/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:02:30 by chukim            #+#    #+#             */
/*   Updated: 2022/08/04 14:48:47 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s2, STDERR_FILENO);
	}
	if (s3)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s3, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	print_token_error(char *error_token)
{
	char	*err_msg;

	err_msg = "minishell: syntax error near unexpected token '";
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd(error_token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	g_errno = 258;
}

void	exit_with_err(char *str1, char *str2, int exit_code, int to_exit)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	if (str2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str2, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	g_errno = exit_code;
	if (to_exit)
		exit(g_errno);
}

void	exit_with_err_second(char *str1, char *str2, char *str3, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	if (str2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str2, STDERR_FILENO);
	}
	if (str3)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str3, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	g_errno = exit_code;
}

int	return_with_err(char *str1, char *str2, char *str3, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	if (str2)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str2, STDERR_FILENO);
	}
	if (str3)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(str3, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	return (exit_code);
}
