/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:12:50 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/04 17:06:00 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token **token)
{
	size_t	i;

	i = 0;
	while ((*token)[i].str)
	{
		free((*token)[i].str);
		i++;
	}
	free((*token)[i].str);
	free(*token);
}

void	free_envp_copy_arr(char ***envp_copy_arr)
{
	size_t	i;

	i = 0;
	while ((*envp_copy_arr)[i])
	{
		free((*envp_copy_arr)[i]);
		i++;
	}
	free((*envp_copy_arr)[i]);
	free((*envp_copy_arr));
}

void	free_cmd(t_cmd **cmd)
{
	size_t	i;

	i = 0;
	while ((*cmd)[i].token)
	{
		free((*cmd)[i].argv);
		i++;
	}
	free((*cmd)[i].argv);
	free(*cmd);
}

void	free_env_path(char ***env_path)
{
	size_t	i;

	i = 0;
	while ((*env_path)[i])
	{
		free((*env_path)[i]);
		i++;
	}
	free((*env_path)[i]);
	free(*env_path);
}
