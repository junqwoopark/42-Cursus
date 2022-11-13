/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 13:35:52 by chukim            #+#    #+#             */
/*   Updated: 2022/08/04 15:17:13 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *cmd)
{
	t_env	*current;

	if (cmd->argc >= 2)
	{
		print_err("env", cmd->argv[1], "too many arguments");
		g_errno = 127;
		return ;
	}
	current = cmd->envp_copy;
	while (current->next != NULL)
	{
		if ((current->value != NULL))
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	g_errno = 0;
}
