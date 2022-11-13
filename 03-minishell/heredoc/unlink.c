/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:38:17 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/04 14:36:01 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_all(t_cmd *cmd)
{
	int		i;
	int		j;
	size_t	tmp_file_cnt;

	i = 0;
	tmp_file_cnt = 0;
	while (cmd[i].token)
	{
		j = 0;
		while (cmd[i].token[j].type)
		{
			if (cmd[i].token[j].type == T_REDIRECT
				&& ft_strcmp(cmd[i].token[j].str, "<<") == 0)
				unlink(cmd[i].token[j + 1].str);
			j++;
		}
		i++;
	}
}
