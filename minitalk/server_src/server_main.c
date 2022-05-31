/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:00:38 by junkpark          #+#    #+#             */
/*   Updated: 2022/05/31 20:43:42 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int				tmp;
int				idx;

void	handler(int signum)
{
	if (signum == SIGUSR1)
	{
		tmp |= 0;
		idx++;
		// ft_putnbr_fd(tmp, 1);
		// ft_putchar_fd('\n', 1);
	}
	else
	{
		tmp |= 1;
		idx++;
		// ft_putnbr_fd(tmp, 1);
		// ft_putchar_fd('\n', 1);
	}
	if (idx == 8)
	{
		if (tmp == 0)
			ft_putchar_fd('\n', 1);
		ft_putchar_fd(tmp, 1);
		tmp = 0;
		idx = 0;
	}
	tmp <<= 1;
}

int	main(void)
{
	ft_putstr_fd("server_pid : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
	{
		pause();
	}
}
