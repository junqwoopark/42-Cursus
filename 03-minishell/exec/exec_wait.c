/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:49:54 by junkpark          #+#    #+#             */
/*   Updated: 2022/08/04 20:51:26 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_last_process(pid_t pid, int *flag)
{
	int	status;

	status = 0;
	*flag = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_errno = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			printf("^C\n");
			g_errno = WTERMSIG(status) + 128;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			printf("^\\Quit: 3\n");
			*flag = 1;
			g_errno = WTERMSIG(status) + 128;
		}
	}
}

void	wait_child_process(pid_t pid)
{
	int	status;
	int	flag;

	wait_last_process(pid, &flag);
	status = 0;
	while (wait(&status) != -1)
		;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			printf("^C\n");
		else if (WTERMSIG(status) == SIGQUIT)
		{
			if (!flag)
				printf("^\\");
		}
	}
}
