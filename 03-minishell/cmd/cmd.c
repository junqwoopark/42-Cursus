/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:20:09 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/04 16:29:05 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*set_argc(t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	size_t	argc;

	i = 0;
	while (cmd[i].token)
	{
		j = 0;
		argc = 0;
		while (cmd[i].token[j].type)
		{
			if (cmd[i].token[j].type == T_WORD)
				argc += 1;
			j++;
		}
		cmd[i].argc = argc;
		i++;
	}
	return (cmd);
}

t_cmd	*set_argv(t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (cmd[i].token)
	{
		j = 0;
		k = 0;
		cmd[i].argv = ft_calloc(cmd[i].argc + 1, sizeof(char *));
		while (cmd[i].token[j].type)
		{
			if (cmd[i].token[j].type == T_WORD)
			{
				cmd[i].argv[k] = cmd[i].token[j].str;
				k++;
			}
			j++;
		}
		i++;
	}
	return (cmd);
}

t_cmd	*init_cmd(t_cmd *cmd, t_token *token,
	t_env *envp_copy, char **envp_copy_arr)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	cnt_of_cmd;

	cnt_of_cmd = get_cnt_of_pipe(token) + 1;
	i = 0;
	j = 0;
	while (i < cnt_of_cmd)
	{
		k = 0;
		while (token[j + k].type != T_PIPE && token[j + k].type)
			k++;
		if (token[j + k].type == T_PIPE)
		{
			token[j + k].type = T_NULL;
			k++;
		}
		cmd[i].token = &(token[j]);
		cmd[i].envp_copy = envp_copy;
		cmd[i].envp_copy_arr = envp_copy_arr;
		j += k;
		i++;
	}
	return (cmd);
}

t_cmd	*get_cmd(t_token *token, t_env *envp_copy, char **envp_copy_arr)
{
	t_cmd	*cmd;
	size_t	cnt_of_cmd;

	cnt_of_cmd = get_cnt_of_pipe(token) + 1;
	cmd = ft_calloc(cnt_of_cmd + 1, sizeof(t_cmd));
	cmd = init_cmd(cmd, token, envp_copy, envp_copy_arr);
	cmd = set_argc(cmd);
	cmd = set_argv(cmd);
	return (cmd);
}
