/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junkpark <junkpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:51:09 by junkpark          #+#    #+#             */
/*   Updated: 2022/07/19 16:04:49 by junkpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	ret;

	ret = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (-1);
		ret = ret * 10 + *str - '0';
		if (ret > 2147483648)
			return (-1);
		else if (ret == 2147483648 && sign == 1)
			return (-1);
		str++;
	}
	if (ret * sign < 0)
		return (-1);
	return (ret * sign);
}

time_t	get_ms_of_day(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

time_t	get_ms_of_passed_time(time_t start)
{
	return ((get_ms_of_day() - start));
}

void	ft_msleep(time_t wait_time)
{
	time_t	start_time;

	start_time = get_ms_of_day();
	while (get_ms_of_passed_time(start_time) < wait_time)
		usleep(1000);
}
