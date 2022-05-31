/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:51:12 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/31 20:06:51 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	exit_with_error(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	exit(1);
	return ;
}

void	print_client_pid(void)
{
	ft_putstr_fd("client pid : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
}

void	send_signal(pid_t server_pid, unsigned char c)
{
	int	idx;

	idx = 7;
	while (idx >= 0)
	{
		if (((c >> idx) & 1) == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(100);
		idx--;
	}
}

int	main(int argc, char **argv)
{
	int	server_pid;
	int	idx;

	if (argc != 3)
		exit_with_error("argc is not 3\n");
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 100 || server_pid > 99999)
		exit_with_error("server_pid is invalid\n");
	idx = 0;
	while (argv[2][idx])
	{
		send_signal(server_pid, argv[2][idx]);
		idx++;
	}
	send_signal(server_pid, argv[2][idx]);
}
