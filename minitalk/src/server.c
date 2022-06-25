/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:00:38 by junkpark          #+#    #+#             */
/*   Updated: 2022/06/24 22:16:25 by junkpark         ###   ########.fr       */
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
	else if (signum == SIGUSR2)
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

int	main(void)
{
	print_pid();
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
	return (0);
}
