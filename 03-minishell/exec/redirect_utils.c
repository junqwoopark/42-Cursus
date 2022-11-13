/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:00:30 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/04 20:30:06 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in(t_cmd *cmd)
{
	int		fd;
	size_t	i;

	i = 0;
	while (cmd->token[i].type)
	{
		if (cmd->token[i].type == T_REDIRECT
			&& (ft_strcmp(cmd->token[i].str, "<") == 0
				|| ft_strcmp(cmd->token[i].str, "<<") == 0))
			fd = open(cmd->token[i + 1].str, O_RDONLY);
		if (fd == -1)
		{
			print_err("minishell", cmd->token[i + 1].str, strerror(errno));
			return (1);
			break ;
		}
		ft_dup2(fd, STDIN_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	redirect_out(t_cmd *cmd)
{
	int		fd;
	size_t	i;

	i = 0;
	while (cmd->token[i].type)
	{
		if (cmd->token[i].type == T_REDIRECT
			&& ft_strcmp(cmd->token[i].str, ">>") == 0)
			fd = open(
					cmd->token[i + 1].str, O_WRONLY | O_CREAT | O_APPEND, 420);
		else if (cmd->token[i].type == T_REDIRECT
			&& ft_strcmp(cmd->token[i].str, ">") == 0)
			fd = open(cmd->token[i + 1].str, O_WRONLY | O_CREAT | O_TRUNC, 420);
		if (fd == -1)
		{
			print_err("minishell", cmd->token[i + 1].str, strerror(errno));
			return (1);
			break ;
		}
		ft_dup2(fd, STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
