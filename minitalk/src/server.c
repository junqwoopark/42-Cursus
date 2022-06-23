/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:00:38 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/23 21:44:24 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_info	g_info;

static void	handler(int signum)
{
	if (signum == SIGUSR1)
	{
		g_info.c |= 0;
		g_info.idx++;
	}
	else
	{
		g_info.c |= 1;
		g_info.idx++;
	}
	if (g_info.idx == 8)
	{
		if (g_info.c == 0)
			ft_putchar_fd('\n', 1);
		ft_putchar_fd(g_info.c, 1);
		g_info.c = 0;
		g_info.idx = 0;
	}
	g_info.c <<= 1;
}

static void	print_pid(void)
{
	ft_putstr_fd("PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	return ;
}

int	main(void)
{
	print_pid();
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
	return (0);
}
