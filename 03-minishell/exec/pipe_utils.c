/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:01:34 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/03 16:02:07 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe(int *read_pipe, int *write_pipe)
{
	read_pipe[0] = 0;
	read_pipe[1] = -1;
	write_pipe[0] = -1;
	write_pipe[1] = 1;
}

void	update_pipe(int *read_pipe, int *write_pipe, int i, int cnt_of_cmd)
{
	if (0 < i && i + 1 <= cnt_of_cmd)
	{
		read_pipe[READ] = write_pipe[READ];
		read_pipe[WRITE] = write_pipe[WRITE];
	}
	if (i + 1 == cnt_of_cmd)
	{
		write_pipe[READ] = -1;
		write_pipe[WRITE] = STDOUT_FILENO;
	}
	if (0 <= i && i + 1 < cnt_of_cmd)
		pipe(write_pipe);
}
