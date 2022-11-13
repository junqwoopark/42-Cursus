/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 15:27:32 by chukim            #+#    #+#             */
/*   Updated: 2022/08/04 20:19:03 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit_str(char *str)
{
	size_t	i;
	char	*tmp;

	tmp = ft_strtrim(str, "\f\r \t\v");
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			free(tmp);
			return (0);
		}
		i++;
	}
	free(tmp);
	return (1);
}

int	ft_isoverflow_str(char *str)
{
	unsigned long long	res;
	int					i;
	int					sign;
	char				*tmp;

	res = 0;
	i = 0;
	sign = 1;
	tmp = ft_strtrim(str, "\f\r \t\v");
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		if (res > 9223372036854775807)
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

void	exit_errno(void)
{
	printf("exit\n");
	exit(g_errno);
}

void	ft_exit(t_cmd *cmd)
{
	if (cmd->argc == 1)
		exit_errno();
	else if (cmd->argc == 2 && ft_isdigit_str(cmd->argv[1])
		&& !ft_isoverflow_str(cmd->argv[1]))
		g_errno = ft_atoi(cmd->argv[1]);
	else if (cmd->argc > 2 && ft_isdigit_str(cmd->argv[1])
		&& !ft_isoverflow_str(cmd->argv[1]))
	{
		printf("exit\n");
		exit_with_err("exit", "too many arguments", 1, 0);
		return ;
	}
	else
	{
		printf("exit\n");
		exit_with_err(cmd->argv[1], "numeric argument required", 255, 1);
	}
	exit_errno();
}

void	ft_exit_multiple_cmd(t_cmd *cmd)
{
	if (cmd->argc == 1)
		exit(g_errno);
	else if (cmd->argc == 2 && ft_isdigit_str(cmd->argv[1]))
		g_errno = ft_atoi(cmd->argv[1]);
	else if (cmd->argc > 2 && ft_isdigit_str(cmd->argv[1]))
	{
		exit_with_err("exit", "too many arguments", 1, 0);
		return ;
	}
	else
		exit_with_err(cmd->argv[1], "numeric argument required", 255, 1);
	exit(g_errno);
}
