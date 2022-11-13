/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 15:57:04 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/03 16:09:44 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_cnt_of_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i].token)
		i++;
	return (i);
}
