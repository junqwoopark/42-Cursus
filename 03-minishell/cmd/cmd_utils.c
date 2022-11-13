/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 21:48:00 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/03 13:59:44 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_cnt_of_pipe(t_token *token)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (token[i].type)
	{
		if (token[i].type == T_PIPE)
			cnt++;
		i++;
	}
	return (cnt);
}
