/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:51:12 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/24 22:16:57 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	exit_with_err(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	exit(1);
	return ;
}

static void	send_char(pid_t pid, unsigned char c)
{
	int	idx;

	idx = 7;
	while (idx >= 0)
	{
		if (((c >> idx) & 1) == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(50);
		idx--;
	}
}

static void	send_string(pid_t pid, char *str)
{
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	send_char(pid, *str);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
		exit_with_err("./client [pid] [string]");
	pid = ft_atoi(argv[1]);
	if (pid <= 100 || pid > 99999)
		exit_with_err("Invalid pid.\n");
	send_string(pid, argv[2]);
	return (0);
}
